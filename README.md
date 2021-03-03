# GraphLib

This is a toy library providing functionality for storing OSM maps as graphs, for modifying the graphs, and for finding shortest paths in the graph based on any user defined metric.

Installation of the library is through cmake:

1. place library source files into some folder /path/to/folder/GraphLib (you can use e.g. git clone https://github.com/sebastian-stark/GraphLib.git from folder /path/to/folder for this)
2. cd /path/to/folder/
3. mkdir build
4. cd build
5. cmake -DCMAKE_INSTALL_PREFIX=/path/to/install/dir ../GraphLib
6. make install
7. optionally set an environment variable to GRAPH_LIB_DIR=/path/to/install/dir

The library GraphLib requires libosmium >=2.15.4 and ZLIB >=1.2.11 installed in paths where they can be found by cmake. These libraries can e.g. be installed through a package manager.

The doxygen generated documentation of GraphLib can be found in the doc folder.

For examples for usage of GraphLib, see the /tests folder.
