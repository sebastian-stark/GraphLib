<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>mainpage.dox</name>
    <path>/home/sst/code/GraphLib/GraphLib/doc/</path>
    <filename>mainpage_8dox.html</filename>
  </compound>
  <compound kind="file">
    <name>graph.h</name>
    <path>/home/sst/code/GraphLib/GraphLib/include/graph_lib/</path>
    <filename>graph_8h.html</filename>
    <class kind="class">GraphLib::WayJunctions</class>
    <class kind="class">GraphLib::ReadOSM</class>
    <class kind="class">GraphLib::Edge</class>
    <class kind="class">GraphLib::Graph</class>
    <namespace>GraphLib</namespace>
    <member kind="enumeration">
      <type></type>
      <name>Direction</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>a5bf5516c3b23da8f7af1226afab50a5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>both</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>a5bf5516c3b23da8f7af1226afab50a5aaa2ad91d07f4899e1731dfca5bada28bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>forward</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>a5bf5516c3b23da8f7af1226afab50a5aa4f1993b4fb95a1522bbfd6e8eb2ba733</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>backward</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>a5bf5516c3b23da8f7af1226afab50a5aae89cdf25233e0343c3828ce740db6a73</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>none</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>a5bf5516c3b23da8f7af1226afab50a5aac4ab236595bdf9359fe00a9d8a62f243</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>typedefs.h</name>
    <path>/home/sst/code/GraphLib/GraphLib/include/graph_lib/</path>
    <filename>typedefs_8h.html</filename>
    <namespace>GraphLib</namespace>
    <member kind="typedef">
      <type>osmium::object_id_type</type>
      <name>Node</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>a93d9cfaf86aae4dac4542492e675fec8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; double, double &gt;</type>
      <name>coordinate_t</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>aedce1a218e8997c889ed4a2e30ba23a9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GraphLib::Edge</name>
    <filename>class_graph_lib_1_1_edge.html</filename>
    <member kind="function">
      <type></type>
      <name>Edge</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>afe94bd989f0d22ace5ae9cfb2e7d7686</anchor>
      <arglist>(const Node node_1, const Node node_2, const std::vector&lt; coordinate_t &gt; &amp;coordinates, const Direction direction=Direction::both)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_user_flag</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>a848b1216268d43a79dd1a0fcbae166e1</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset_user_flag</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>a42c2c76c3cf78be1ab318612cb5b05ce</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Node</type>
      <name>get_node_1</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>a85ff4ef7cf27bf4076a65071c901ea81</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Node</type>
      <name>get_node_2</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>abe43908e9e800fabfe6e41b3704759af</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; coordinate_t &gt; &amp;</type>
      <name>get_coordinates</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>a1cb6b49834a87c27f54e82a141876431</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Direction</type>
      <name>get_direction</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>a0e6f08c306d109ba35eab742eaf3dba9</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_direction</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>a126cb65cc3d9af7bad99d4ce3a472ab8</anchor>
      <arglist>(const Direction direction) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>get_user_flag</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>afc4a997a6f729101d8570f825bc7f387</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>get_length</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>adc79ef6f59b91f139a8795e290bc0d8a</anchor>
      <arglist>(const std::function&lt; double(const coordinate_t &amp;, const coordinate_t &amp;)&gt; &amp;metric) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>flip_edge</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>ac16ea5914d26c1c7283739a5c7c91f5f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Node</type>
      <name>node_1</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>a832274adf1038129b5242e0bb2c8b13e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Node</type>
      <name>node_2</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>aed2f7e2694a120b809a1bce761dfea29</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; coordinate_t &gt;</type>
      <name>coordinates</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>a83765300e5223435c4aba672060e28c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Direction</type>
      <name>direction</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>a5c7e1a7035fd436b47525483697d5f5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>user_flag</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>aa2eefe27efb6d9cb02c3155de7115d62</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Graph</name>
      <anchorfile>class_graph_lib_1_1_edge.html</anchorfile>
      <anchor>afab89afd724f1b07b1aaad6bdc61c47a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GraphLib::Graph</name>
    <filename>class_graph_lib_1_1_graph.html</filename>
    <member kind="function">
      <type></type>
      <name>Graph</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>aca7f98e3f4acd61ca612750ffb64543f</anchor>
      <arglist>(const std::function&lt; double(const coordinate_t &amp;, const coordinate_t &amp;)&gt; metric)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_metric</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>a130b4b82cca0ca986c220d2532bcc479</anchor>
      <arglist>(const std::function&lt; double(const coordinate_t &amp;, const coordinate_t &amp;)&gt; metric)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_edge</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>aeb13a8c4f1d861dcd62aa72cb2b505b1</anchor>
      <arglist>(const Node node_1, const Node node_2, std::vector&lt; coordinate_t &gt; coordinates, Direction direction=Direction::both)</arglist>
    </member>
    <member kind="function">
      <type>std::list&lt; Edge &gt;::iterator</type>
      <name>begin</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>a3e592bff23dd764067af391d91fd59b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::list&lt; Edge &gt;::iterator</type>
      <name>end</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>a1f23adba10adb5712c0bde84d24d154e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>remove_flagged_edges</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>ac619f84a3fe16cd25b4e5279d215cfd0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write_svg</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>af10505c386680bdb79efa0dc5b0f7f5d</anchor>
      <arglist>(const std::string file_name, const std::function&lt; coordinate_t(const coordinate_t &amp;)&gt; &amp;coordinate_transform=[](const coordinate_t &amp;p) -&gt; coordinate_t{return p;}, const bool highlight_flagged_edges=false, const double width=1000.0) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>read_graph_from_osm</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>accc2fe03dcb9ad88dd5dbee1d8fb17c1</anchor>
      <arglist>(const std::string file_name, const std::function&lt; bool(const osmium::Way &amp;)&gt; &amp;include_way, const std::function&lt; bool(const osmium::NodeRef &amp;)&gt; &amp;include_node, const bool remove_dead_ends=false)</arglist>
    </member>
    <member kind="function">
      <type>std::list&lt; std::pair&lt; const Edge *, Direction &gt; &gt;</type>
      <name>compute_shortest_path</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>accf1e69b32cd4644bc7291337be9d8a6</anchor>
      <arglist>(const Node node_1, const Node node_2) const</arglist>
    </member>
    <member kind="function">
      <type>Node</type>
      <name>get_closest_node</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>a648d1bfbd8a9c70b41be6c4bf846ad6a</anchor>
      <arglist>(const coordinate_t p, const std::set&lt; Node &gt; nodes_ignore=std::set&lt; Node &gt;()) const</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>get_degree</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>a635d70d0608d1f1293758db509707832</anchor>
      <arglist>(const Node node) const</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>get_n_nodes</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>a1e38ef4ff5888cec1b03b250e102bb52</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>get_n_edges</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>a57b4def7d2dad543ac2d347be43d7c5a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::list&lt; Edge &gt;</type>
      <name>edges</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>af1d98d86195763d4252d2bbbc2489f90</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::unordered_map&lt; Node, std::set&lt; Edge * &gt; &gt;</type>
      <name>nodes</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>ad51721d9af94391bbc63332404867848</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::function&lt; double(const coordinate_t &amp;, const coordinate_t &amp;)&gt;</type>
      <name>metric</name>
      <anchorfile>class_graph_lib_1_1_graph.html</anchorfile>
      <anchor>a90a90d7364f268d51f05dffd002c3ef7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GraphLib::ReadOSM</name>
    <filename>class_graph_lib_1_1_read_o_s_m.html</filename>
    <member kind="function">
      <type></type>
      <name>ReadOSM</name>
      <anchorfile>class_graph_lib_1_1_read_o_s_m.html</anchorfile>
      <anchor>aef838502cbd33ab503530a04ac3ed2fd</anchor>
      <arglist>(Graph &amp;graph, const std::set&lt; Node &gt; &amp;intermediate_nodes, const std::function&lt; bool(const osmium::Way &amp;)&gt; include_way, const std::function&lt; bool(const osmium::NodeRef &amp;)&gt; include_node)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>way</name>
      <anchorfile>class_graph_lib_1_1_read_o_s_m.html</anchorfile>
      <anchor>a0ec277731dcc05f028ff3dc4610d31f4</anchor>
      <arglist>(const osmium::Way &amp;way)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Graph &amp;</type>
      <name>graph</name>
      <anchorfile>class_graph_lib_1_1_read_o_s_m.html</anchorfile>
      <anchor>ad20a9a3f700b05a6dd773f9b2509921e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const std::set&lt; Node &gt; &amp;</type>
      <name>intermediate_nodes</name>
      <anchorfile>class_graph_lib_1_1_read_o_s_m.html</anchorfile>
      <anchor>a9587fcdde3a6deac62d083a9bd6bee2e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::function&lt; bool(const osmium::Way &amp;)&gt;</type>
      <name>include_way</name>
      <anchorfile>class_graph_lib_1_1_read_o_s_m.html</anchorfile>
      <anchor>a7f545b229c9a2c1b405173fc1c9421a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::function&lt; bool(const osmium::NodeRef &amp;)&gt;</type>
      <name>include_node</name>
      <anchorfile>class_graph_lib_1_1_read_o_s_m.html</anchorfile>
      <anchor>adeb79afc63e819bf550a35cd373516f7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GraphLib::WayJunctions</name>
    <filename>class_graph_lib_1_1_way_junctions.html</filename>
    <member kind="function">
      <type></type>
      <name>WayJunctions</name>
      <anchorfile>class_graph_lib_1_1_way_junctions.html</anchorfile>
      <anchor>a54b9df3d0bca06ee0b5f5626bc892c76</anchor>
      <arglist>(const std::function&lt; bool(const osmium::Way &amp;)&gt; include_way)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>way</name>
      <anchorfile>class_graph_lib_1_1_way_junctions.html</anchorfile>
      <anchor>a948192ecc9beb95cd641afc28dba4235</anchor>
      <arglist>(const osmium::Way &amp;way)</arglist>
    </member>
    <member kind="function">
      <type>std::set&lt; Node &gt;</type>
      <name>get_intermediate_nodes</name>
      <anchorfile>class_graph_lib_1_1_way_junctions.html</anchorfile>
      <anchor>aa3a6752f0c1c8a3a1d422794739d9316</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::unordered_map&lt; Node, short unsigned int &gt;</type>
      <name>node_counts</name>
      <anchorfile>class_graph_lib_1_1_way_junctions.html</anchorfile>
      <anchor>ad67c3801e21aa9fd780bf833f8d9280c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::function&lt; bool(const osmium::Way &amp;)&gt;</type>
      <name>include_way</name>
      <anchorfile>class_graph_lib_1_1_way_junctions.html</anchorfile>
      <anchor>a612c2fc6cef171ec1004947225b2045e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>initialized</name>
      <anchorfile>class_graph_lib_1_1_way_junctions.html</anchorfile>
      <anchor>a4ba2b390ceaddbbd500343639ad9aadf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>GraphLib</name>
    <filename>namespace_graph_lib.html</filename>
    <class kind="class">GraphLib::Edge</class>
    <class kind="class">GraphLib::Graph</class>
    <class kind="class">GraphLib::ReadOSM</class>
    <class kind="class">GraphLib::WayJunctions</class>
    <member kind="typedef">
      <type>osmium::object_id_type</type>
      <name>Node</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>a93d9cfaf86aae4dac4542492e675fec8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; double, double &gt;</type>
      <name>coordinate_t</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>aedce1a218e8997c889ed4a2e30ba23a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Direction</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>a5bf5516c3b23da8f7af1226afab50a5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>both</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>a5bf5516c3b23da8f7af1226afab50a5aaa2ad91d07f4899e1731dfca5bada28bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>forward</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>a5bf5516c3b23da8f7af1226afab50a5aa4f1993b4fb95a1522bbfd6e8eb2ba733</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>backward</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>a5bf5516c3b23da8f7af1226afab50a5aae89cdf25233e0343c3828ce740db6a73</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>none</name>
      <anchorfile>namespace_graph_lib.html</anchorfile>
      <anchor>a5bf5516c3b23da8f7af1226afab50a5aac4ab236595bdf9359fe00a9d8a62f243</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>GraphLib library</title>
    <filename>index</filename>
  </compound>
</tagfile>
