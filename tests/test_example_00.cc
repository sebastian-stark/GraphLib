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

int main(int argc, char *argv[])
{

	initlog(argc, argv);

	const double lat = 51.05871;
	const double lon = 13.77054;
	const double r = 1.0;
	const string file = "example_map.osm.pbf";

	const double r_earth = 6371.0;
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

	const map<string, set<string>> exclude_tags = { {"bicycle", {"no", "dismount"}}, {"area", {"yes"}}, {"access", {"no", "private"}}};
	const map<string, set<string>> include_tags = { {"highway", {"residential", "trunk", "primary", "secondary", "tertiary", "unclassified", "trunk_link", "primary_link", "secondary_link", "tertiary_link", "living_street", "road"}} };
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
	};

	Graph graph(standard_metric);

	graph.read_graph_from_osm(file, include_way, include_node, false);

	graph_lib_log << graph.get_n_edges() << endl;
	graph_lib_log << graph.get_n_nodes() << endl << endl;
	const auto direction_to_string = [&](const Direction& direction) -> string
	{
		if(direction == Direction::backward)
			return "backward";
		else if(direction == Direction::forward)
			return "forward";
		else if(direction == Direction::both)
			return "both";
		else
			return "none";
	};
	for(const auto& edge : graph)
		graph_lib_log << edge.get_node_1() << " " << edge.get_node_2() << " " << direction_to_string(edge.get_direction()) << " " << edge.get_length(standard_metric) << endl;

	return stoplog(argc, argv);
}