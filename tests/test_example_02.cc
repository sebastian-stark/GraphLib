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

	const auto metric = [&](const coordinate_t& p_1, const coordinate_t& p_2) -> double
	{
		const double dx = p_1.first - p_2.first;
		const double dy = p_1.second -p_2.second;
		return sqrt(dx * dx + dy * dy);
	};

	Graph graph(metric);

	graph.add_edge(1, 0, {{1.0, 2.0},{0.0, 1.0}}, Direction::both);
	graph.add_edge(0, 7, {{0.0, 1.0},{1.0, 0.0}}, Direction::both);
	graph.add_edge(1, 7, {{1.0, 2.0},{1.0, 0.0}}, Direction::both);
	graph.add_edge(1, 2, {{1.0, 2.0},{2.0, 2.0}}, Direction::both);
	graph.add_edge(7, 6, {{1.0, 0.0},{2.0, 0.0}}, Direction::both);
	graph.add_edge(8, 7, {{2.0, 1.0},{1.0, 0.0}}, Direction::forward);
	graph.add_edge(6, 8, {{2.0, 0.0},{2.0, 1.0}}, Direction::both);
	graph.add_edge(2, 8, {{2.0, 2.0},{2.0, 1.0}}, Direction::both);
	graph.add_edge(6, 5, {{2.0, 0.0},{3.0, 0.0}}, Direction::backward);
	graph.add_edge(2, 5, {{2.0, 2.0},{3.0, 0.0}}, Direction::forward);
	graph.add_edge(2, 3, {{2.0, 2.0},{3.0, 2.0}}, Direction::backward);
	graph.add_edge(5, 3, {{3.0, 0.0},{3.0, 2.0}}, Direction::both);
	graph.add_edge(3, 4, {{3.0, 2.0},{4.0, 1.0}}, Direction::both);
	graph.add_edge(5, 4, {{3.0, 0.0},{4.0, 1.0}}, Direction::backward);

	auto shortest_path = graph.compute_shortest_path(0, 4);

	double distance = 0.0;
	for(auto e : shortest_path)
	{
		if(e.second == Direction::forward)
			graph_lib_log << e.first->get_node_1() << " -> " << e.first->get_node_2() << " (forward edge traversal)" << endl;
		else
			graph_lib_log << e.first->get_node_2() << " -> " << e.first->get_node_1() << " (backward edge traversal)" << endl;
		distance += e.first->get_length(metric);
	}
	graph_lib_log << endl << "Total distance = " << distance << endl;

	return stoplog(argc, argv);
}
