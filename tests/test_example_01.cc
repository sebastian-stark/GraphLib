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

#include "tests.h"
#include <string>

#include <graph_lib/graph.h>

using namespace std;
using namespace GraphLib;

/**
 * Test extracting way data from an *.osm.pbf file, converting these data into a graph, and finally computing the shortest distance between two given nodes.
 * Data within a circle of radius r=2 km around a center point with latitude 51.05871° and longitude 13.77054° are taken into account.
 */
int main(int argc, char *argv[])
{

	// initialize logging
	initlog(argc, argv);

	// input parameters
	const double lat = 51.05871;				// latitude of center point
	const double lon = 13.77054;				// longitude of center point
	const double r = 2.0;						// radius of circle within which data is extracted (km)
	const string file = "example_map.osm.pbf";	// input file
	const double r_earth = 6371.0;				// mean radius of earth (km)

	// metric for computation of distances between two points (given in latitude, longitude)
	const auto standard_metric = [&](const coordinate_t& p_1, const coordinate_t& p_2) -> double
	{
		const double delta_lat = (p_1.first - p_2.first) * M_PI / 180.0;
		const double delta_lon = (p_1.second - p_2.second) * M_PI / 180.0;
		const double lat_1_r = p_1.first * M_PI / 180.0;
		const double lat_2_r = p_1.second * M_PI / 180.0;
		const double a = pow(sin(0.5 * delta_lat), 2.0) + pow(sin(0.5 * delta_lon), 2.0) * cos(lat_1_r) * cos(lat_2_r);
		const double c = 2.0 * asin(sqrt(a));
		return r_earth * c;
	};

	// function determining which ways to include into the graph
	// (if a way is tagged with any of the tag/key combinations contained in include_tags, it is included into the considerations,
	//  unless the way also involves a tag/key combination contained in exclude_tags)
	const map<string, set<string>> include_tags = { {"highway", {"residential", "trunk", "primary", "secondary", "tertiary", "unclassified", "trunk_link", "primary_link", "secondary_link", "tertiary_link", "living_street", "road"}} };
	const map<string, set<string>> exclude_tags = { {"bicycle", {"no", "dismount"}}, {"area", {"yes"}}, {"access", {"no", "private"}}};
	const auto include_way = [&](const osmium::Way& way) -> bool
	{
		bool include = false;
		for(const osmium::Tag& t : way.tags())
		{
			const auto t_it_ex = exclude_tags.find(string(t.key()));
			if( (t_it_ex != exclude_tags.end()) && (t_it_ex->second.find(string(t.value())) != t_it_ex->second.end()) )
				return false;
			const auto t_it_in = include_tags.find(string(t.key()));
			if( (t_it_in != include_tags.end()) && (t_it_in->second.find(string(t.value())) != t_it_in->second.end()) )
				include = true;
		}
		return include;
	};

	// function determining which nodes to include into the graph (here: only those which are less than 2 km away from the center point)
	const auto include_node = [&](const osmium::NodeRef& node) -> bool
	{
		const double delta_lat = (node.lat() - lat) * M_PI / 180.0;
		const double delta_lon = (node.lon() - lon) * M_PI / 180.0;
		const double lat_1_r = lat * M_PI / 180.0;
		const double lat_2_r = node.lat() * M_PI / 180.0;
		const double a = pow(sin(0.5 * delta_lat), 2.0) + pow(sin(0.5 * delta_lon), 2.0) * cos(lat_1_r) * cos(lat_2_r);
		const double c = 2.0 * asin(sqrt(a));
		const double d = r_earth * c;
		if( (d < r) && (d > 0.001)) // safety distance around origin to later avoid potential issues with singular metric
			return true;
		else
			return false;
		return true;
	};

	// azimuthal projection used for writing graph and computed route into svg file
	const auto azimuthal_projection = [&](const coordinate_t& p) -> coordinate_t
	{
		coordinate_t p_r, res;
		const double lat_r = lat * M_PI / 180.0;
		const double lon_r = lon * M_PI / 180.0;
		p_r.first = p.first * M_PI / 180.0;
		p_r.second = p.second * M_PI / 180.0;
		const double c = acos( sin(lat_r) * sin(p_r.first) + cos(lat_r) * cos(p_r.first) * cos(p_r.second - lon_r) );
		const double k = r_earth * c / sin(c);
		res.first = k * cos(p_r.first) * sin(p_r.second - lon_r);
		res.second = k * ( cos(lat_r) * sin(p_r.first) - sin(lat_r) * cos(p_r.first) * cos(p_r.second - lon_r) );
		return res;
	};

	// set up graph
	Graph graph(standard_metric);

	// read in file
	graph.read_graph_from_osm(file, include_way, include_node, false);

	// compute shortest path between two nodes
	list<pair<const Edge*, Direction>> shortest_path;
	const Node start_node = graph.get_closest_node(make_pair(51.08684, 13.74289));
	const Node end_node = graph.get_closest_node(make_pair(51.04196, 13.81309));
	shortest_path = graph.compute_shortest_path(start_node, end_node);

	// flag the computed path and write to svg
	// (here this ends up in the log file - if the log file is renamed from test_example_01_.log into test_example_01_.svg, it can be viewed with an appropriate viewer)
	for(const auto& edge : shortest_path)
		edge.first->set_user_flag();
	graph.write_svg(graph_lib_log, azimuthal_projection, true);

	// stop logging
	return stoplog(argc, argv);
}
