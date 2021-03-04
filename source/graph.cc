// --------------------------------------------------------------------------
// Copyright (C) 2021 by Sebastian Stark
//
// This file is part of GraphLib
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include <graph_lib/graph.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <tuple>
#include <limits>
#include <bits/stdc++.h>

#include <osmium/io/pbf_input.hpp>
#include <osmium/io/gzip_compression.hpp>
#include <osmium/visitor.hpp>
#include <osmium/index/map/sparse_mem_array.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>

using namespace std;

namespace GraphLib
{

	WayJunctions::WayJunctions(	const function<bool(const osmium::Way&)> include_way)
	:
	include_way(include_way)
	{
	}

	void
	WayJunctions::way(const osmium::Way& way)
	{
		initialized = true;
		if( include_way(way) )
		{

			auto n_begin = way.nodes().begin();
			auto n_end = way.nodes().end();
			for(auto n = n_begin; n != n_end; ++n)
			{

				if(node_counts.find(n->ref()) == node_counts.end())
					node_counts[n->ref()] = 1;
				else
					node_counts[n->ref()] = node_counts[n->ref()] + 1;
			}
		}
		return;
	}

	set<Node>
	WayJunctions::get_intermediate_nodes()
	const
	{
		assert(("Tried to call WayJunctions::get_intermediate_nodes() without applying an osmium reader first.", initialized == true));
		set<Node> graph_nodes;
		for(const auto& node : node_counts)
		{
			if(node.second > 1)
				graph_nodes.insert(node.first);
		}
		node_counts.clear();
		initialized = false;
		return graph_nodes;
	}

	ReadOSM::ReadOSM(	Graph&											graph,
						const set<Node>&								intermediate_nodes,
						const function<bool(const osmium::Way&)>		include_way,
						const function<bool(const osmium::NodeRef&)>	include_node)
	:
	graph(graph),
	intermediate_nodes(intermediate_nodes),
	include_way(include_way),
	include_node(include_node)
	{
	}

	void
	ReadOSM::way(const osmium::Way& way)
	{
		if( include_way(way) )
		{
			// figure out direction of the way
			Direction direction = Direction::both;
			for(const osmium::Tag& t : way.tags())
			{
				if(string(t.key()) == "oneway")
				{
					if( (string(t.value()) == "yes") || (string(t.value()) == "1") || (string(t.value()) == "true") )
						direction = Direction::forward;
					else if ( string(t.value()) == "-1" )
						direction = Direction::backward;
					else
						direction = Direction::both;
				}
			}

			vector<coordinate_t> coordinates;
			bool edge_started = false;
			Node n_start, n_end;
			for (const auto& n : way.nodes())
			{
				if(include_node(n))
				{
					if(!edge_started)
					{
						edge_started = true;
						n_start = n.ref();
					}

					coordinates.push_back(make_pair(n.lat(), n.lon()));

					if(intermediate_nodes.find(n.ref()) != intermediate_nodes.end())
					{
						if(coordinates.size() > 1)
						{
							// Todo: Circles are completely ignored here. It should be tried to break up circles into two edges if there are three nodes at least
							if(n_start != n.ref())
							{
								graph.add_edge(n_start, n.ref(), coordinates, direction);
							}
							coordinates.clear();
							coordinates.push_back(make_pair(n.lat(), n.lon()));
						}
						n_start = n.ref();
					}
					n_end = n.ref();
				}
			}
			// Todo: Circles are completely ignored here. It should be tried to break up circles into two edges if there are three nodes at least
			if( (coordinates.size() > 1) && (n_start != n_end) )
			{
				graph.add_edge(n_start, n_end, coordinates, direction);
			}

		}
		return;
	}

	Edge::Edge(	const Node					node_1,
				const Node					node_2,
				const vector<coordinate_t>&	coordinates,
				const Direction				direction)
	:
	node_1(node_1),
	node_2(node_2),
	coordinates(coordinates),
	direction(direction)
	{
	}

	void
	Edge::set_user_flag()
	const
	{
		user_flag = true;
		return;
	}

	void
	Edge::reset_user_flag()
	const
	{
		user_flag = false;
		return;
	}

	Node
	Edge::get_node_1()
	const
	{
		return node_1;
	}

	Node
	Edge::get_node_2()
	const
	{
		return node_2;
	}

	const vector<coordinate_t>&
	Edge::get_coordinates()
	const
	{
		return coordinates;
	}

	Direction
	Edge::get_direction()
	const
	{
		return direction;
	}

	void
	Edge::set_direction(const Direction direction)
	const
	{
		this->direction = direction;
	}


	double
	Edge::get_length(const function<double(const coordinate_t&, const coordinate_t&)>& metric)
	const
	{
		double length = 0.0;
		for(unsigned int m = 1; m < coordinates.size(); ++m)
			length += metric(coordinates[m], coordinates[m-1]);
		assert(("There is an edge in the graph having infinite length.", isfinite(length)));
		return length;
	}

	bool
	Edge::get_user_flag()
	const
	{
		return user_flag;
	}

	void
	Edge::flip_edge()
	{
		const auto node_1_old = node_1;
		node_1 = node_2;
		node_2 = node_1_old;

		if(direction == Direction::forward)
			direction = Direction::backward;
		else if(direction == Direction::backward)
			direction = Direction::forward;

		reverse(coordinates.begin(),coordinates.end());

		return;
	}

	Graph::Graph(const function<double(const coordinate_t&, const coordinate_t&)> metric)
	:
	metric(metric)
	{
	}

	void
	Graph::set_metric(const function<double(const coordinate_t&, const coordinate_t&)> metric)
	{
		this->metric = metric;
	}

	void
	Graph::add_edge(const Node				node_1,
					const Node				node_2,
					vector<coordinate_t>	coordinates,
					Direction				direction)
	{
		assert( ("An edge in the graph is not allowed to be associated with the same node at both ends.", node_1 != node_2) );
		auto edge = edges.insert(edges.end(), Edge(node_1, node_2, coordinates, direction));
		nodes[node_1].insert(&(*edge));
		nodes[node_2].insert(&(*edge));
		return;
	}

	list<Edge>::iterator
	Graph::begin()
	{
		return edges.begin();
	}

	list<Edge>::iterator
	Graph::end()
	{
		return edges.end();
	}

	void
	Graph::remove_flagged_edges()
	{
		auto edge = edges.begin();
		while(edge != edges.end())
		{
			if(edge->user_flag)
			{
				// first remove edge association with nodes
				const Node node_1 = edge->node_1;
				const Node node_2 = edge->node_2;
				nodes[node_1].erase(&(*edge));
				nodes[node_2].erase(&(*edge));
				// if this results in an isolated node: remove the node as well
				if(nodes[node_1].empty())
					nodes.erase(node_1);
				if(nodes[node_2].empty())
					nodes.erase(node_2);
				// now remove the edge from the graph
				edge = edges.erase(edge);
			}
			else
				++edge;
		}
		return;
	}

	void
	Graph::write_svg(	ofstream&											output_stream,
						const function<coordinate_t(const coordinate_t&)>&	coordinate_transform,
						const bool 											highlight_flagged_edges,
						const double										width)
	const
	{
		// first pass: figure out the "dimensions" of the graph to be written
		double x_min = numeric_limits<double>::max();
		double x_max = -x_min;
		double y_min = x_min;
		double y_max = -x_min;
		coordinate_t transformed_point;
		for(const auto& edge : edges)
		{
			for(const auto point : edge.coordinates)
			{
				transformed_point = coordinate_transform(point);
				if(transformed_point.first > x_max)
					x_max = transformed_point.first;
				if(transformed_point.first < x_min)
					x_min = transformed_point.first;
				if(transformed_point.second > y_max)
					y_max = transformed_point.second;
				if(transformed_point.second < y_min)
					y_min = transformed_point.second;
			}
		}

		// second pass: write the svg
		const double offset_x = -x_min;
		const double offset_y = -y_min;

		assert(("Tried to write a figure with zero width.", x_max + offset_x > 0.0));
		const double scale = width / (x_max + offset_x);
		const double height = scale * (y_max + offset_y);
		assert(("Tried to write a figure with zero height.", height > 0.0));

		// transformation of coordinates necessary for svg output
		auto scale_transform = [&](coordinate_t coordinate) -> coordinate_t
		{
			return make_pair(scale * (coordinate.first + offset_x), height - scale * (coordinate.second + offset_y));
		};

		// lambda simplifying the svg output
		auto prop_str = [](const string tag_open, const set<pair<const string, const string>> props, const string tag_close = "") -> string
		{
			string res = "<" + tag_open + " ";
			for(const auto& prop : props)
				res += prop.first + "=" + "\"" + prop.second + "\"" + " ";
			res += tag_close + ">";
			return res;
		};

		output_stream << prop_str( "svg", { {"width", to_string(width) + "px"}, {"height", to_string(height) + "px"} }) << endl;
		output_stream << prop_str( "rect", { {"x", "0"}, {"y", "0"}, {"width", to_string(width)}, {"height", to_string(height)}, {"fill", "white"} }, "/") << endl;
		string postponed_edges = "";
		for(const auto& edge : edges)
		{
			const string color = edge.get_user_flag() ? "red" : "black";

			string points = "";
			for(unsigned int m = 0; m < edge.coordinates.size(); ++m)
			{
				const auto p = scale_transform(coordinate_transform(edge.coordinates[m]));
				points += to_string(p.first) + "," + to_string(p.second) + " ";
			}
			if(edge.get_user_flag())
				postponed_edges += prop_str( "polyline", { {"points", points}, {"fill", "none"}, {"stroke", color}, {"stroke-width", "2"} }, "/") + "\n";
			else
				output_stream << prop_str( "polyline", { {"points", points}, {"fill", "none"}, {"stroke", color} }, "/") << endl;
		}
		output_stream << postponed_edges;
		output_stream << "</svg>" << endl;

		return;
	}

	void
	Graph::write_svg(	const string 										file_name,
						const function<coordinate_t(const coordinate_t&)>&	coordinate_transform,
						const bool 											highlight_flagged_edges,
						const double										 width)
	const
	{
		ofstream svg_file;
		svg_file.open(file_name.c_str());
		write_svg(svg_file, coordinate_transform, highlight_flagged_edges, width);
		svg_file.close();
	}

	void
	Graph::read_graph_from_osm( const string 									file_name,
								const function<bool(const osmium::Way&)>& 		include_way,
								const function<bool(const osmium::NodeRef&)>& 	include_node,
								const bool										remove_dead_ends)
	{
		// first find out, which ways need to be split into several edges
		osmium::io::Reader osm_reader_1{file_name.c_str(), osmium::osm_entity_bits::way};
		WayJunctions way_junctions(include_way);
		osmium::apply(osm_reader_1, way_junctions);
		osm_reader_1.close();
		const auto intermediate_nodes = way_junctions.get_intermediate_nodes();

		// now do the actual work and read the data in
		osmium::io::Reader reader_2{file_name.c_str(), osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};
		using index_type = osmium::index::map::SparseMemArray<osmium::unsigned_object_id_type, osmium::Location>;
		index_type index;
		osmium::handler::NodeLocationsForWays<index_type> location_handler{index};
		ReadOSM read_osm(*this, intermediate_nodes, include_way, include_node);
		osmium::apply(reader_2, location_handler, read_osm);
		reader_2.close();

		// clean up the graph a bit (join edges at nodes where just two edges meet and remove dead ends if requested)
		for(;;)
		{
			// join edges at nodes where just two edges meet
			bool continue_loop = false;
			for(const auto& node : nodes)
			{
				if(node.second.size() == 2)
				{
					auto& edge_1 = **(node.second.begin());
					auto& edge_2 = **(++node.second.begin());
					if(edge_1.node_1 == node.first)
						edge_1.flip_edge();
					if(edge_2.node_2 == node.first)
						edge_2.flip_edge();

					const Node node_1_joined_edge = edge_1.node_1;
					const Node node_2_joined_edge = edge_2.node_2;

					if(node_1_joined_edge == node_2_joined_edge)
						continue;

					Direction direction_joined_edge = Direction::both;
					if(edge_1.direction == edge_2.direction)
						direction_joined_edge = edge_1.direction;
					else if( (edge_1.direction == Direction::none) || (edge_2.direction == Direction::none) )
						direction_joined_edge = Direction::none;
					else if( (edge_1.direction == Direction::forward) && (edge_2.direction == Direction::backward) )
						direction_joined_edge = Direction::none;
					else if( (edge_1.direction == Direction::backward) && (edge_2.direction == Direction::forward) )
						direction_joined_edge = Direction::none;
					else if( (edge_1.direction == Direction::forward) || (edge_2.direction == Direction::forward) )
						direction_joined_edge = Direction::forward;
					else if( (edge_1.direction == Direction::backward) || (edge_2.direction == Direction::backward) )
						direction_joined_edge = Direction::backward;

					vector<coordinate_t> coordinates_joined_edge = edge_1.coordinates;
					coordinates_joined_edge.insert( coordinates_joined_edge.end(), edge_2.coordinates.begin(), edge_2.coordinates.end() );

					if(direction_joined_edge != Direction::none)
						add_edge(node_1_joined_edge, node_2_joined_edge, coordinates_joined_edge, direction_joined_edge);

					edge_1.set_user_flag();
					edge_2.set_user_flag();

					continue_loop = true;
				}
			}
			remove_flagged_edges();

			// remove dead ends if requested
			if(remove_dead_ends)
			{
				for(const auto& node : nodes)
				{
					if(node.second.size() == 1)
					{
						(*(node.second.begin()))->set_user_flag();
						continue_loop = true;
					}
				}
				remove_flagged_edges();
			}

			if(continue_loop == false)
				break;
		}
		return;
	}

	list<pair<const Edge*, Direction>>
	Graph::compute_shortest_path(	const Node node_1,
									const Node node_2)
	const
	{
		assert(("Source node not found in graph.", nodes.find(node_1) != nodes.end()));
		assert(("Destination node not found in graph.", nodes.find(node_2) != nodes.end()));

		// Dijkstra algorithm essentially taken from https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
		// The way this is done here is certainly not very efficient.

		// map between node and pair of [current value of total distance to node, (predecessor node, edge)]
		unordered_map<Node, pair<double, pair<Node, const Edge*>>> total_distance_predecessor;

		// priority queue sorted by total distance (each element of the queue consists of total distance and node index)
		priority_queue< pair<double, Node>, vector <pair<double, Node>> , greater<pair<double, Node>> > priority_queue;

		// initialize
		for(const auto& n : nodes)
			total_distance_predecessor.insert( make_pair(n.first, make_pair(numeric_limits<double>::max(), make_pair(node_1, nullptr))) );
		total_distance_predecessor[node_1] = make_pair(0.0, make_pair(node_1, nullptr));
		priority_queue.push(make_pair(0.0, node_1));

		// lambda for updating distance and priority queue
		const auto update_distance_priority_queue = [&](const Node current, const Node adjacent, const double weight, const Edge* edge) -> void
		{
			const double old_weight = total_distance_predecessor[current].first;
			if(total_distance_predecessor[adjacent].first > old_weight + weight)
			{
				total_distance_predecessor[adjacent].first = old_weight + weight;
				total_distance_predecessor[adjacent].second.first = current;
				total_distance_predecessor[adjacent].second.second = edge;
				priority_queue.push(make_pair(old_weight + weight, adjacent));
			}
		};

		// the actual computation loop
		while(!priority_queue.empty())
		{
			const Node current = priority_queue.top().second;
			if(current == node_2)
				break;
			priority_queue.pop();
			const auto& edges = (*(nodes.find(current))).second;
			for(const auto e : edges)
			{
				if( (e->node_1 == current) && ( (e->direction == Direction::forward) || (e->direction == Direction::both) ) )
					update_distance_priority_queue(current, e->node_2, e->get_length(metric), e);
				else if( (e->node_2 == current) && ( (e->direction == Direction::backward) || (e->direction == Direction::both) ) )
					update_distance_priority_queue(current, e->node_1, e->get_length(metric), e);
			}
		}

		// write the shortest path
		list<pair<const Edge*, Direction>> shortest_path;
		Node node_curr = node_2;
		for(;;)
		{
			const Edge* edge_curr = total_distance_predecessor[node_curr].second.second;
			if(edge_curr == nullptr)
				break;
			node_curr = total_distance_predecessor[node_curr].second.first;
			assert( (node_curr == edge_curr->node_1) || (node_curr == edge_curr->node_2));
			if(node_curr == edge_curr->node_1)
				shortest_path.push_front(make_pair(edge_curr, Direction::forward));
			else
				shortest_path.push_front(make_pair(edge_curr, Direction::backward));
			if(node_curr == node_1)
				break;
		}

		return shortest_path;

	}

	void
	Graph::write_gpx(	ofstream& 									output_stream,
						const list<pair<const Edge*, Direction>>&	route,
						const string								track_name)
	const
	{
		output_stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		output_stream << "<gpx version=\"1.0\">\n";
		output_stream << "<name>" << track_name << "</name>\n";
		output_stream << "<trk>\n";
		output_stream << "<name>" << track_name << "</name>\n";
		output_stream << "<number>1</number>\n";
		output_stream << "<trkseg>\n";
		for(const auto& edge : route)
		{
			if(edge.second == Direction::forward)
			{
				auto coord_it = edge.first->coordinates.begin();
				for(;;)
				{
					output_stream << "<trkpt lat=\"" << coord_it->first << "\" lon=\"" << coord_it->second << "\"></trkpt>\n";
					++coord_it;
					if(coord_it == edge.first->coordinates.end())
						break;
				}
			}
			else
			{
				auto coord_it = (--edge.first->coordinates.end());
				for(;;)
				{
					output_stream << "<trkpt lat=\"" << coord_it->first << "\" lon=\"" << coord_it->second << "\"></trkpt>\n";
					if(coord_it == edge.first->coordinates.begin())
						break;
					--coord_it;
				}
			}
		}
		output_stream << "</trkseg>\n";
		output_stream << "</trk>\n";
		output_stream << "</gpx>\n";
	}

	void
	Graph::write_gpx(	const string 								file_name,
						const list<pair<const Edge*, Direction>>&	route,
						const string								track_name)
	const
	{
		ofstream gpx_file;
		gpx_file.open(file_name.c_str());
		write_gpx(gpx_file, route, track_name);
		gpx_file.close();
	}

	Node
	Graph::get_closest_node(const coordinate_t	p,
							const set<Node> 	nodes_ignore)
	const
	{
		double min_dist = numeric_limits<double>::max();
		Node min_node;
		for(const auto& edge : edges)
		{
			const double d_1 = metric(p, edge.coordinates.front());
			if(d_1 < min_dist)
			{
				if(nodes_ignore.find(edge.node_1) == nodes_ignore.end())
				{
					min_dist = d_1;
					min_node = edge.node_1;
				}
			}
			const double d_2 = metric(p, edge.coordinates.back());
			if(d_2 < min_dist)
			{
				if(nodes_ignore.find(edge.node_2) == nodes_ignore.end())
				{
					min_dist = d_2;
					min_node = edge.node_2;
				}
			}
		}
		return min_node;
	}

	unsigned int
	Graph::get_degree(const Node node)
	const
	{
		if(nodes.find(node) != nodes.end())
			return nodes.find(node)->second.size();
		else
			return 0;
	}

	unsigned int
	Graph::get_n_nodes()
	const
	{
		return nodes.size();
	}

	unsigned int
	Graph::get_n_edges()
	const
	{
		return edges.size();
	}

}
