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

#ifndef INCLUDE_GRAPH_LIB_GRAPH_H_
#define INCLUDE_GRAPH_LIB_GRAPH_H_

#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <list>
#include <string>

#include <osmium/handler.hpp>
#include <osmium/osm/way.hpp>

#include <graph_lib/typedefs.h>

namespace GraphLib
{

class Graph;

/**
 * enum indicating the direction of a way (both: way can be accessed in both directions, forward/backward: way can only be accessed in forward/backward direction, no: no access allowed)
 */
enum Direction{both, forward, backward, none};

/**
 * Osmium handler for finding intermediate nodes on ways corresponding to junctions, which, therefore, become nodes in the graph
 */
class WayJunctions : public osmium::handler::Handler
{
private:

	/**
	 * map between node number and number of times this node appears in the ways
	 */
	mutable
	std::unordered_map<Node, short unsigned int>
	node_counts;

	/**
	 * Function deciding whether to take a way into consideration or to ignore it (if @p true is returned by the function, the way is taken into consideration)
	 */
	std::function<bool(const osmium::Way&)>
	include_way;

	mutable
	bool initialized = false;

public:

	/**
	 * Constructor
	 *
	 * @param[in]	include_way		WayJunctions::include_way
	 */
	WayJunctions(const std::function<bool(const osmium::Way&)> include_way);

	/**
	 * Function handling the node information of an individual node
	 *
	 * @param[in]	way		the current way
	 */
	void
	way(const osmium::Way& way);

	/**
	 * @return 	The nodes where ways must be split
	 *
	 * 			Each call to this function must be preceded by application of an osmium reader.
	 */
	std::set<Node>
	get_intermediate_nodes()
	const;
};

/**
 * Osmium handler for reading in an OSM file and setting up a corresponding graph
 */
class ReadOSM : public osmium::handler::Handler
{
private:

	/**
	 * the graph into which the content of the file is read
	 */
	Graph&
	graph;

	/**
	 * a set of nodes, at which ways need to be split into several edges (due to the presence of junctions)
	 */
	const
	std::set<Node>&
	intermediate_nodes;

	/**
	 * Function deciding whether to take a way into consideration or to ignore it (if @p true is returned by the function, the way is taken into consideration)
	 */
	std::function<bool(const osmium::Way&)>
	include_way;

	/**
	 * Function deciding whether to take a node into consideration or to ignore it (if @p true is returned by the function, the node is taken into consideration)
	 */
	std::function<bool(const osmium::NodeRef&)>
	include_node;

public:

	/**
	 * Constructor
	 *
	 * @param[in]	graph				WayJunctions::graph
	 *
	 * @param[in]	intermediate_nodes	WayJunctions::intermediate_nodes
	 *
	 * @param[in]	include_way			WayJunctions::include_way
	 *
	 * @param[in]	include_node		WayJunctions::include_node
	 */
	ReadOSM(Graph&												graph,
			const std::set<Node>&								intermediate_nodes,
			const std::function<bool(const osmium::Way&)>		include_way,
			const std::function<bool(const osmium::NodeRef&)>	include_node);

	/**
	 * Function handling the node information of an individual node
	 *
	 * @param[in]	way		the current way
	 */
	void
	way(const osmium::Way& way);
};


/**
 * Class defining an edge in the graph
 */
class Edge
{
private:

	/**
	 * first node assoicated with the edge
	 */
	Node
	node_1;

	/**
	 * second node associated with the edge
	 */
	Node
	node_2;

	/**
	 * A vector of (x,y) pairs forming the edge.
	 * The first element in the vector corresponds to the "location" of Edge::node_1.
	 * The last element in the vector corresponds to the "location" of Edge::node_2.
	 * The other elements in the vector describe the "shape" of the edge as one goes from Edge::node_1 to Edge::node_2.
	 */
	std::vector<coordinate_t>
	coordinates;

	/**
	 * Direction of the edge (may be modified through public member function)
	 */
	mutable
	Direction
	direction = Direction::both;

	/**
	 * flag, which may be set by the user to indicate that the edge participates in some collective
	 * operation on the edges of the graph (like removal of all flagged edges)
	 */
	mutable
	bool
	user_flag = false;

	/**
	 *  make Graph a friend of Edge
	 */
	friend class Graph;

public:

	/**
	 * Constructor
	 *
	 * @param[in]	node_1		the first node making up the edge
	 *
	 * @param[in]	node_2		the second node making up the edge
	 *
	 * @param[in]	coordinates	the coordinates describing the geometry of the edge when going from @p node_1 to @p node_2
	 *
	 * @param[in]	direction	the direction of the edge
	 */
	Edge(	const Node							node_1,
			const Node							node_2,
			const std::vector<coordinate_t>&	coordinates,
			const Direction						direction = Direction::both);

	/**
	 * Flag the edge
	 */
	void
	set_user_flag()
	const;

	/**
	 * Unflag the edge
	 */
	void
	reset_user_flag()
	const;

	/**
	 * @return	node 1 of the edge
	 */
	Node
	get_node_1()
	const;

	/**
	 * @return	node 2 of the edge
	 */
	Node
	get_node_2()
	const;

	/**
	 * @return reference to the coordinates defining the geometry of the edge
	 */
	const std::vector<coordinate_t>&
	get_coordinates()
	const;

	/**
	 * @return The direction flag of the edge
	 */
	Direction
	get_direction()
	const;

	void
	set_direction(const Direction direction)
	const;

	/**
	 * @return whether the edge is currently flagged
	 */
	bool
	get_user_flag()
	const;

	/**
	 * Compute the length of the edge using Edge::coordinates and the specified metric
	 *
	 * @param[in]	metric	The given metric function
	 *
	 * @return				The length of the edge
	 */
	double
	get_length(const std::function<double(const coordinate_t&, const coordinate_t&)>& metric)
	const;

	/**
	 * reverses the direction of an edge
	 */
	void
	flip_edge();
};

/**
 * Class managing a graph, with each edge being associated with geometrical information about its shape.
 */
class Graph
{
private:

	/**
	 * List containing the edges of the graph.
	 */
	std::list<Edge>
	edges;

	/**
	 * Map between the nodes of the graph and a set of edges associated with each node.
	 * Using a map offers flexibility for adding new nodes/edges, removing nodes/edges and lookup of certain nodes.
	 * In particular, no assumption of a contiguous node numbering is necessary with this approach.
	 */
	std::unordered_map<Node, std::set<Edge*>>
	nodes;

	/**
	 * The metric used for the graph
	 */
	std::function<double(const coordinate_t&, const coordinate_t&)>
	metric;

public:

	/**
	 * Constructor
	 *
	 * @param[in]	metric	The metric to be used to determine distances along edges of the graph
	 */
	Graph(const std::function<double(const coordinate_t&, const coordinate_t&)> metric);

	/**
	 * Change the metric of the graph
	 *
	 * @param[in]	metric	The new metric function
	 */
	void
	set_metric(const std::function<double(const coordinate_t&, const coordinate_t&)> metric);

	/**
	 * Add an edge.
	 *
	 * @param[in]	node_1		the first node making up the edge
	 *
	 * @param[in]	node_2		the second node making up the edge
	 *
	 * @param[in]	coordinates	the coordinates describing the geometry of the edge when going from @p node_1 to @p node_2
	 *
	 * @param[in]	direction	the direction of the edge
	 */
	void
	add_edge(	const Node					node_1,
				const Node					node_2,
				std::vector<coordinate_t>	coordinates,
				Direction					direction = Direction::both);

	/**
	 * begin iterator over the edges of the Graph
	 *
	 * @return		begin iterator
	 */
	std::list<Edge>::iterator
	begin();

	/**
	 * end iterator over the edges of the Graph
	 *
	 * @return		end iterator
	 */
	std::list<Edge>::iterator
	end();

	/**
	 * This removes all edges from the Graph, which have been flagged before.
	 * If one ends up with an isolated node (i.e., a not not being associated with any edges), this node is removed as well.
	 */
	void
	remove_flagged_edges();

	/**
	 * Write the graph to the specified svg file
	 *
	 * @param[in]	file_name				The file name of the svg file (including the extension)
	 *
	 * @param[in]	coordinate_transform	A transformation applied to the coordinates defining the geometry of the graph edges before writing the svg.
	 * 										If e.g. the coordinates of the graph edges represent longitude and latitude, this defines the projection to planar coordinates
	 *
	 * @param[in]	highlight_flagged_edges	If @p true, flagged edges are drawn red
	 *
	 * @param[in]	width					The width of the svg in px
	 */
	void
	write_svg(	const std::string 										file_name,
				const std::function<coordinate_t(const coordinate_t&)>&	coordinate_transform = [](const coordinate_t& p) -> coordinate_t{return p;},
				const bool 												highlight_flagged_edges = false,
				const double 											width = 1000.0)
	const;

	/**
	 * Read the graph from an .osm.pbf file.
	 * The reading process will also "clean up" the graph, such that nodes of degree 2 are generally eliminated (the corresponding edges are joined).
	 *
	 * @param[in]	file_name			file (including path and extension)
	 *
	 * @param[in]	include_way			function deciding whether to take a way into consideration or to ignore it (if @p true is returned by the function, the way is taken into consideration)
	 *
	 * @param[in]	include_node		function deciding whether to take a node into consideration or to ignore it (if @p true is returned by the function, the node is taken into consideration)
	 *
	 * @param[in]	remove_dead_ends	if @p true, all nodes associated with only a single edge are removed (together with the corresponding edges). I.e., no "dead ends" are kept in the graph
	 */
	void
	read_graph_from_osm(const std::string 									file_name,
						const std::function<bool(const osmium::Way&)>& 		include_way,
						const std::function<bool(const osmium::NodeRef&)>&	include_node,
						const bool											remove_dead_ends = false);

	/**
	 * Function calculating shortest path between @p node_1 and @p node_2 based on Dijkstra's algorithm.
	 *
	 * @param[in]	node_1	Start node
	 *
	 * @param[in]	node_2	End node
	 *
	 * @return				List of pairs of edges and directions. Describes the shortest path from @p node_1 to @p node_2. If no path is found, an empty list is returned.
	 */
	std::list<std::pair<const Edge*, Direction>>
	compute_shortest_path(	const Node node_1,
							const Node node_2)
	const;

	/**
	 * Return the node closest to @p, while ignoring all nodes stored in @p p_ignore.
	 *
	 * @param[in]	p				The coordinates of the point to which the closest node is to be found
	 *
	 * @param[in]	nodes_ignore	A set of nodes to be ignored during the search
	 */
	Node
	get_closest_node(	const coordinate_t 		p,
						const std::set<Node> 	nodes_ignore = std::set<Node>())
	const;

	/**
	 * Return the degree of a node (not considering direction of edges)
	 *
	 * @param[in]	node	The node index
	 *
	 * @return				The degree of @p node
	 */
	unsigned int
	get_degree(const Node node)
	const;

	/**
	 * @return	The number of nodes involved in the graph
	 */
	unsigned int
	get_n_nodes()
	const;

	/**
	 * @return	The number of edges involved in the graph
	 */
	unsigned int
	get_n_edges()
	const;


};

}


#endif /* INCLUDE_GRAPH_LIB_GRAPH_H_ */
