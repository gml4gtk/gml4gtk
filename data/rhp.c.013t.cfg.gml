# graph generated with GCC 10.1
graph
[
  directed 1


# function number 2
	node [ id 1 graphics [ fill "#ffffff" ] label "rhp_version ()
ENTRY" ]

	node [ id 2 graphics [ fill "#ffffff" ] label "rhp_version ()
EXIT" ]

	node [ id 3 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
D.4340 = &quot;1.6&quot;;
" ]

	node [ id 4 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
&lt;L0&gt;:
return D.4340;
" ]

	edge [ source 1 target 3 graphics [ fill "#0000ff" ] ] 
	edge [ source 3 target 4 graphics [ fill "#0000ff" ] ] 
	edge [ source 4 target 2 graphics [ fill "#000000" ] ] 


# function number 3
	node [ id 5 graphics [ fill "#ffffff" ] label "rhp_init ()
ENTRY" ]

	node [ id 6 graphics [ fill "#ffffff" ] label "rhp_init ()
EXIT" ]

	node [ id 7 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
rhp_inited.0_1 = rhp_inited;
if (rhp_inited.0_1 != 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 8 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): rhp_deinit() not done and doing it now shouldnothappen!\n&quot;, &amp;__FUNCTION__);
rhp_deinit ();
" ]

	node [ id 9 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_logstream = 0B;
rhp_dolog = 0;
rhp_logname = 0B;
if (logname != 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 10 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
_2 = MEM[(const char *)logname];
if (_2 == 0)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 11 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
stdout.1_3 = stdout;
rhp_logstream = stdout.1_3;
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 12 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
_4 = fopen (logname, &quot;wb&quot;);
rhp_logstream = _4;
rhp_logstream.2_5 = rhp_logstream;
if (rhp_logstream.2_5 == 0B)
  goto &lt;bb 8&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 13 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
stdout.3_6 = stdout;
rhp_logstream = stdout.3_6;
" ]

	node [ id 14 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_dolog = loglevel;
rhp_log (&quot;%s(): starting logfile!\n&quot;, &amp;__FUNCTION__);
" ]

	node [ id 15 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
_7 = rhp_sp_new (1);
rhp_sp_master_node_list = _7;
_8 = rhp_sp_new (1);
rhp_sp_master_edge_list = _8;
rhp_uniq_nodenum = 0;
rhp_uniq_edgenum = 0;
rhp_number_of_nodes = 0;
rhp_number_of_edges = 0;
rhp_number_of_isolated_nodes = 0;
_9 = rhp_sp_new (1);
rhp_sp_between_layers = _9;
rhp_maxlevel = 0;
rhp_nlevels = 0;
rhp_crossings = -1;
rhp_start_crossings = -1;
rhp_best_crossings_order = 0B;
rhp_getlayoutdata = 0B;
rhp_improvements = 0;
rhp_notimprovements = 0;
rhp_log (&quot;%s(): sizeof (int) is %d bytes (expect 4)\n&quot;, &amp;__FUNCTION__, 4);
rhp_log (&quot;%s(): sizeof (long long) is %d bytes (expect 8)\n&quot;, &amp;__FUNCTION__, 8);
rhp_log (&quot;%s(): sizeof (int64_t) is %d bytes (expect 8)\n&quot;, &amp;__FUNCTION__, 8);
rhp_log (&quot;%s(): sizeof (intptr_t) is %d bytes (expect 8)\n&quot;, &amp;__FUNCTION__, 8);
rhp_log (&quot;%s(): sizeof (struct rhp_spn) is %d bytes\n&quot;, &amp;__FUNCTION__, 32);
rhp_log (&quot;%s(): sizeof (struct rhp_sp) is %d bytes\n&quot;, &amp;__FUNCTION__, 16);
rhp_log (&quot;%s(): sizeof (struct rhpnode) is %d bytes\n&quot;, &amp;__FUNCTION__, 80);
rhp_log (&quot;%s(): sizeof (struct rhpedge) is %d bytes\n&quot;, &amp;__FUNCTION__, 56);
rhp_log (&quot;%s(): sizeof (struct rhplevel) is %d bytes\n&quot;, &amp;__FUNCTION__, 16);
rhp_log (&quot;%s(): sizeof (struct rhp_inter_layer_struct) is %d bytes\n&quot;, &amp;__FUNCTION__, 24);
rhp_log (&quot;%s(): sizeof (struct rhp_order_struct) is %d bytes\n&quot;, &amp;__FUNCTION__, 24);
rhp_inited = 1;
" ]

	node [ id 16 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
&lt;L9&gt;:
return;
" ]

	edge [ source 5 target 7 graphics [ fill "#0000ff" ] ] 
	edge [ source 7 target 8 graphics [ fill "#000000" ] ] 
	edge [ source 7 target 9 graphics [ fill "#000000" ] ] 
	edge [ source 8 target 9 graphics [ fill "#0000ff" ] ] 
	edge [ source 9 target 10 graphics [ fill "#000000" ] ] 
	edge [ source 9 target 15 graphics [ fill "#000000" ] ] 
	edge [ source 10 target 11 graphics [ fill "#000000" ] ] 
	edge [ source 10 target 12 graphics [ fill "#000000" ] ] 
	edge [ source 11 target 14 graphics [ fill "#0000ff" ] ] 
	edge [ source 12 target 13 graphics [ fill "#000000" ] ] 
	edge [ source 12 target 14 graphics [ fill "#000000" ] ] 
	edge [ source 13 target 14 graphics [ fill "#0000ff" ] ] 
	edge [ source 14 target 15 graphics [ fill "#0000ff" ] ] 
	edge [ source 15 target 16 graphics [ fill "#0000ff" ] ] 
	edge [ source 16 target 6 graphics [ fill "#000000" ] ] 


# function number 4
	node [ id 29 graphics [ fill "#ffffff" ] label "rhp_deinit ()
ENTRY" ]

	node [ id 30 graphics [ fill "#ffffff" ] label "rhp_deinit ()
EXIT" ]

	node [ id 31 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
rhp_inited.4_1 = rhp_inited;
if (rhp_inited.4_1 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 32 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() must be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 33 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_log (&quot;%s():\n&quot;, &amp;__FUNCTION__);
rhp_empty_best_crossings_order ();
rhp_empty_sp_layers ();
rhp_empty_sp_between_layers ();
rhp_empty_sp_master_node_list ();
rhp_empty_sp_master_edge_list ();
rhp_sp_layers.5_2 = rhp_sp_layers;
_3 = rhp_sp_delete (rhp_sp_layers.5_2);
rhp_sp_layers = _3;
rhp_best_crossings_order.6_4 = rhp_best_crossings_order;
if (rhp_best_crossings_order.6_4 != 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 34 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_best_crossings_order.7_5 = rhp_best_crossings_order;
_6 = rhp_free (rhp_best_crossings_order.7_5, &amp;__FUNCTION__, 735);
rhp_best_crossings_order = _6;
" ]

	node [ id 35 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_sp_master_node_list.8_7 = rhp_sp_master_node_list;
_8 = rhp_sp_delete (rhp_sp_master_node_list.8_7);
rhp_sp_master_node_list = _8;
rhp_sp_master_edge_list.9_9 = rhp_sp_master_edge_list;
_10 = rhp_sp_delete (rhp_sp_master_edge_list.9_9);
rhp_sp_master_edge_list = _10;
rhp_sp_master_node_list_sorted.10_11 = rhp_sp_master_node_list_sorted;
_12 = rhp_sp_delete (rhp_sp_master_node_list_sorted.10_11);
rhp_sp_master_node_list_sorted = _12;
rhp_sp_between_layers.11_13 = rhp_sp_between_layers;
_14 = rhp_sp_delete (rhp_sp_between_layers.11_13);
rhp_sp_between_layers = _14;
rhp_uniq_nodenum = 0;
rhp_uniq_edgenum = 0;
rhp_number_of_nodes = 0;
rhp_number_of_edges = 0;
rhp_number_of_isolated_nodes = 0;
rhp_maxlevel = 0;
rhp_nlevels = 0;
rhp_crossings = -1;
rhp_start_crossings = -1;
rhp_getlayoutdata = 0B;
rhp_improvements = 0;
rhp_notimprovements = 0;
rhp_n_malloc.12_15 = rhp_n_malloc;
rhp_n_free.13_16 = rhp_n_free;
if (rhp_n_malloc.12_15 != rhp_n_free.13_16)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 36 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_dolog.14_17 = rhp_dolog;
if (rhp_dolog.14_17 &gt; 1)
  goto &lt;bb 8&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 37 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
rhp_n_malloc.15_18 = rhp_n_malloc;
rhp_n_free.16_19 = rhp_n_free;
_20 = rhp_n_malloc.15_18 - rhp_n_free.16_19;
rhp_n_free.17_21 = rhp_n_free;
rhp_n_malloc.18_22 = rhp_n_malloc;
rhp_log (&quot;%s(): done %lu malloc and %lu free and delta is %li shouldnothappen!\n&quot;, &amp;__FUNCTION__, rhp_n_malloc.18_22, rhp_n_free.17_21, _20);
" ]

	node [ id 38 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_n_malloc = 0;
rhp_n_free = 0;
rhp_dolog.19_23 = rhp_dolog;
if (rhp_dolog.19_23 != 0)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 39 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
rhp_log (&quot;%s(): closing logfile\n&quot;, &amp;__FUNCTION__);
rhp_logname.20_24 = rhp_logname;
if (rhp_logname.20_24 != 0B)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 40 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
rhp_logstream.21_25 = rhp_logstream;
fclose (rhp_logstream.21_25);
rhp_logname = 0B;
" ]

	node [ id 41 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
rhp_dolog = 0;
rhp_inited = 0;
" ]

	node [ id 42 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
&lt;L12&gt;:
return;
" ]

	edge [ source 29 target 31 graphics [ fill "#0000ff" ] ] 
	edge [ source 31 target 32 graphics [ fill "#000000" ] ] 
	edge [ source 31 target 33 graphics [ fill "#000000" ] ] 
	edge [ source 32 target 42 graphics [ fill "#0000ff" ] ] 
	edge [ source 33 target 34 graphics [ fill "#000000" ] ] 
	edge [ source 33 target 35 graphics [ fill "#000000" ] ] 
	edge [ source 34 target 35 graphics [ fill "#0000ff" ] ] 
	edge [ source 35 target 36 graphics [ fill "#000000" ] ] 
	edge [ source 35 target 38 graphics [ fill "#000000" ] ] 
	edge [ source 36 target 37 graphics [ fill "#000000" ] ] 
	edge [ source 36 target 38 graphics [ fill "#000000" ] ] 
	edge [ source 37 target 38 graphics [ fill "#0000ff" ] ] 
	edge [ source 38 target 39 graphics [ fill "#000000" ] ] 
	edge [ source 38 target 41 graphics [ fill "#000000" ] ] 
	edge [ source 39 target 40 graphics [ fill "#000000" ] ] 
	edge [ source 39 target 41 graphics [ fill "#000000" ] ] 
	edge [ source 40 target 41 graphics [ fill "#0000ff" ] ] 
	edge [ source 41 target 42 graphics [ fill "#0000ff" ] ] 
	edge [ source 42 target 30 graphics [ fill "#000000" ] ] 


# function number 5
	node [ id 57 graphics [ fill "#ffffff" ] label "rhp_addnode ()
ENTRY" ]

	node [ id 58 graphics [ fill "#ffffff" ] label "rhp_addnode ()
EXIT" ]

	node [ id 59 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
nn = 0B;
rhp_inited.22_1 = rhp_inited;
if (rhp_inited.22_1 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 60 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() mus be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4367 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 61 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
if (num &lt; 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 62 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_log (&quot;%s(): number %d is below zero and node skipped shouldnothappen!\n&quot;, &amp;__FUNCTION__, num);
D.4367 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 63 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
if (level &lt; 0)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 64 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_log (&quot;%s(): level %d is below zero and node skipped shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
D.4367 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 65 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
_2 = (long long int) num;
rhp_sp_master_node_list.23_3 = rhp_sp_master_node_list;
spn = rhp_sp_lookup (rhp_sp_master_node_list.23_3, _2);
if (spn != 0B)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 66 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_log (&quot;%s(): node number %d already existed, skipped this add shouldnothappen!\n&quot;, &amp;__FUNCTION__, num);
D.4367 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 67 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
nn = rhp_malloc (80, &amp;__FUNCTION__, 842);
rhp_uniq_nodenum.24_4 = rhp_uniq_nodenum;
nn-&gt;num = rhp_uniq_nodenum.24_4;
rhp_uniq_nodenum.25_5 = rhp_uniq_nodenum;
_6 = rhp_uniq_nodenum.25_5 + 1;
rhp_uniq_nodenum = _6;
nn-&gt;innum = num;
nn-&gt;level = level;
nn-&gt;data = data;
nn.26_7 = (long long int) nn;
_8 = (long long int) num;
rhp_sp_master_node_list.27_9 = rhp_sp_master_node_list;
rhp_sp_insert (rhp_sp_master_node_list.27_9, _8, nn.26_7);
rhp_maxlevel.28_10 = rhp_maxlevel;
if (level &gt;= rhp_maxlevel.28_10)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 68 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
rhp_maxlevel = level;
rhp_maxlevel.29_11 = rhp_maxlevel;
_12 = rhp_maxlevel.29_11 + 1;
rhp_nlevels = _12;
" ]

	node [ id 69 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
rhp_maxlevel.30_13 = rhp_maxlevel;
rhp_log (&quot;%s(): added node %d level %d data=%p now maxlevel=%d\n&quot;, &amp;__FUNCTION__, num, level, data, rhp_maxlevel.30_13);
D.4367 = 0;
" ]

	node [ id 70 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
&lt;L10&gt;:
return D.4367;
" ]

	edge [ source 57 target 59 graphics [ fill "#0000ff" ] ] 
	edge [ source 59 target 60 graphics [ fill "#000000" ] ] 
	edge [ source 59 target 61 graphics [ fill "#000000" ] ] 
	edge [ source 60 target 70 graphics [ fill "#0000ff" ] ] 
	edge [ source 61 target 62 graphics [ fill "#000000" ] ] 
	edge [ source 61 target 63 graphics [ fill "#000000" ] ] 
	edge [ source 62 target 70 graphics [ fill "#0000ff" ] ] 
	edge [ source 63 target 64 graphics [ fill "#000000" ] ] 
	edge [ source 63 target 65 graphics [ fill "#000000" ] ] 
	edge [ source 64 target 70 graphics [ fill "#0000ff" ] ] 
	edge [ source 65 target 66 graphics [ fill "#000000" ] ] 
	edge [ source 65 target 67 graphics [ fill "#000000" ] ] 
	edge [ source 66 target 70 graphics [ fill "#0000ff" ] ] 
	edge [ source 67 target 68 graphics [ fill "#000000" ] ] 
	edge [ source 67 target 69 graphics [ fill "#000000" ] ] 
	edge [ source 68 target 69 graphics [ fill "#0000ff" ] ] 
	edge [ source 69 target 70 graphics [ fill "#0000ff" ] ] 
	edge [ source 70 target 58 graphics [ fill "#000000" ] ] 


# function number 6
	node [ id 85 graphics [ fill "#ffffff" ] label "rhp_addedge ()
ENTRY" ]

	node [ id 86 graphics [ fill "#ffffff" ] label "rhp_addedge ()
EXIT" ]

	node [ id 87 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
spnf = 0B;
spnt = 0B;
fn = 0B;
tn = 0B;
ne = 0B;
edgelen = 0;
rhp_inited.31_1 = rhp_inited;
if (rhp_inited.31_1 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 88 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() mus be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4379 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 89 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_sp_master_node_list.32_2 = rhp_sp_master_node_list;
_3 = rhp_sp_has_data (rhp_sp_master_node_list.32_2);
if (_3 == 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 90 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_log (&quot;%s(): there are no nodes in database skipping edge %d-&gt;%d shouldnothappen!\n&quot;, &amp;__FUNCTION__, fnode, tnode);
D.4379 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 91 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
if (num &lt; 0)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 92 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_log (&quot;%s(): number %d is below zero and edge skipped shouldnothappen!\n&quot;, &amp;__FUNCTION__, num);
D.4379 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 93 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
if (fnode &lt; 0)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 94 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_log (&quot;%s(): from node number %d is below zero and edge skipped shouldnothappen!\n&quot;, &amp;__FUNCTION__, fnode);
D.4379 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 95 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
if (tnode &lt; 0)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 96 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
rhp_log (&quot;%s(): to node number %d is below zero and edge skipped shouldnothappen!\n&quot;, &amp;__FUNCTION__, tnode);
D.4379 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 97 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
_4 = (long long int) num;
rhp_sp_master_edge_list.33_5 = rhp_sp_master_edge_list;
spn = rhp_sp_lookup (rhp_sp_master_edge_list.33_5, _4);
if (spn != 0B)
  goto &lt;bb 13&gt;; [INV]
else
  goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 98 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
rhp_log (&quot;%s(): edge number %d does already exists from %d-&gt;%d and skipped shouldnothappen!\n&quot;, &amp;__FUNCTION__, num, fnode, tnode);
D.4379 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 99 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
_6 = (long long int) fnode;
rhp_sp_master_node_list.34_7 = rhp_sp_master_node_list;
spnf = rhp_sp_lookup (rhp_sp_master_node_list.34_7, _6);
if (spnf == 0B)
  goto &lt;bb 15&gt;; [INV]
else
  goto &lt;bb 16&gt;; [INV]
" ]

	node [ id 100 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
rhp_log (&quot;%s(): from node %d is not in database in edge from %d-&gt;%d and skipped shouldnothappen!\n&quot;, &amp;__FUNCTION__, fnode, fnode, tnode);
D.4379 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 101 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
_8 = spnf-&gt;value;
fn = (struct rhpnode *) _8;
_9 = (long long int) tnode;
rhp_sp_master_node_list.35_10 = rhp_sp_master_node_list;
spnt = rhp_sp_lookup (rhp_sp_master_node_list.35_10, _9);
if (spnt == 0B)
  goto &lt;bb 17&gt;; [INV]
else
  goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 102 graphics [ fill "#d3d3d3" ] label "&lt;bb 17&gt;:
rhp_log (&quot;%s(): to node %d is not in database in edge from %d-&gt;%d and skipped shouldnothappen!\n&quot;, &amp;__FUNCTION__, tnode, fnode, tnode);
D.4379 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 103 graphics [ fill "#d3d3d3" ] label "&lt;bb 18&gt;:
_11 = spnt-&gt;value;
tn = (struct rhpnode *) _11;
_12 = tn-&gt;level;
_13 = fn-&gt;level;
edgelen = _12 - _13;
if (edgelen != 1)
  goto &lt;bb 19&gt;; [INV]
else
  goto &lt;bb 20&gt;; [INV]
" ]

	node [ id 104 graphics [ fill "#d3d3d3" ] label "&lt;bb 19&gt;:
_14 = tn-&gt;level;
_15 = fn-&gt;level;
rhp_log (&quot;%s(): edge len is %d at %d-&gt;%d from level %d-&gt;%d and should be 1 shouldnothappen!\n&quot;, &amp;__FUNCTION__, edgelen, fnode, tnode, _15, _14);
D.4379 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 105 graphics [ fill "#d3d3d3" ] label "&lt;bb 20&gt;:
_16 = tn-&gt;level;
_17 = fn-&gt;level;
if (_16 &lt; _17)
  goto &lt;bb 21&gt;; [INV]
else
  goto &lt;bb 22&gt;; [INV]
" ]

	node [ id 106 graphics [ fill "#d3d3d3" ] label "&lt;bb 21&gt;:
_18 = tn-&gt;level;
_19 = fn-&gt;level;
rhp_log (&quot;%s(): edge len %d at %d-&gt;%d from level %d-&gt;%d should be downward shouldnothappen!\n&quot;, &amp;__FUNCTION__, edgelen, fnode, tnode, _19, _18);
D.4379 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 107 graphics [ fill "#d3d3d3" ] label "&lt;bb 22&gt;:
ne = rhp_malloc (56, &amp;__FUNCTION__, 962);
rhp_uniq_edgenum.36_20 = rhp_uniq_edgenum;
ne-&gt;num = rhp_uniq_edgenum.36_20;
rhp_uniq_edgenum.37_21 = rhp_uniq_edgenum;
_22 = rhp_uniq_edgenum.37_21 + 1;
rhp_uniq_edgenum = _22;
ne-&gt;innum = num;
ne-&gt;fn = fn;
ne-&gt;tn = tn;
ne-&gt;data = data;
ne-&gt;up_node = tn;
ne-&gt;down_node = fn;
ne-&gt;crossings = 0;
ne.38_23 = (long long int) ne;
_24 = (long long int) num;
rhp_sp_master_edge_list.39_25 = rhp_sp_master_edge_list;
rhp_sp_insert (rhp_sp_master_edge_list.39_25, _24, ne.38_23);
rhp_log (&quot;%s(): added edge %d from node %d to node %d data=%p\n&quot;, &amp;__FUNCTION__, num, fnode, tnode, data);
D.4379 = 0;
" ]

	node [ id 108 graphics [ fill "#d3d3d3" ] label "&lt;bb 23&gt;:
&lt;L20&gt;:
return D.4379;
" ]

	edge [ source 85 target 87 graphics [ fill "#0000ff" ] ] 
	edge [ source 87 target 88 graphics [ fill "#000000" ] ] 
	edge [ source 87 target 89 graphics [ fill "#000000" ] ] 
	edge [ source 88 target 108 graphics [ fill "#0000ff" ] ] 
	edge [ source 89 target 90 graphics [ fill "#000000" ] ] 
	edge [ source 89 target 91 graphics [ fill "#000000" ] ] 
	edge [ source 90 target 108 graphics [ fill "#0000ff" ] ] 
	edge [ source 91 target 92 graphics [ fill "#000000" ] ] 
	edge [ source 91 target 93 graphics [ fill "#000000" ] ] 
	edge [ source 92 target 108 graphics [ fill "#0000ff" ] ] 
	edge [ source 93 target 94 graphics [ fill "#000000" ] ] 
	edge [ source 93 target 95 graphics [ fill "#000000" ] ] 
	edge [ source 94 target 108 graphics [ fill "#0000ff" ] ] 
	edge [ source 95 target 96 graphics [ fill "#000000" ] ] 
	edge [ source 95 target 97 graphics [ fill "#000000" ] ] 
	edge [ source 96 target 108 graphics [ fill "#0000ff" ] ] 
	edge [ source 97 target 98 graphics [ fill "#000000" ] ] 
	edge [ source 97 target 99 graphics [ fill "#000000" ] ] 
	edge [ source 98 target 108 graphics [ fill "#0000ff" ] ] 
	edge [ source 99 target 100 graphics [ fill "#000000" ] ] 
	edge [ source 99 target 101 graphics [ fill "#000000" ] ] 
	edge [ source 100 target 108 graphics [ fill "#0000ff" ] ] 
	edge [ source 101 target 102 graphics [ fill "#000000" ] ] 
	edge [ source 101 target 103 graphics [ fill "#000000" ] ] 
	edge [ source 102 target 108 graphics [ fill "#0000ff" ] ] 
	edge [ source 103 target 104 graphics [ fill "#000000" ] ] 
	edge [ source 103 target 105 graphics [ fill "#000000" ] ] 
	edge [ source 104 target 108 graphics [ fill "#0000ff" ] ] 
	edge [ source 105 target 106 graphics [ fill "#000000" ] ] 
	edge [ source 105 target 107 graphics [ fill "#000000" ] ] 
	edge [ source 106 target 108 graphics [ fill "#0000ff" ] ] 
	edge [ source 107 target 108 graphics [ fill "#0000ff" ] ] 
	edge [ source 108 target 86 graphics [ fill "#000000" ] ] 


# function number 7
	node [ id 133 graphics [ fill "#ffffff" ] label "rhp_layout ()
ENTRY" ]

	node [ id 134 graphics [ fill "#ffffff" ] label "rhp_layout ()
EXIT" ]

	node [ id 135 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
redu = 0;
" ]

	node [ id 136 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
if (nodeweightadjust != 0)
  goto &lt;bb 4&gt;; [INV]
else
  goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 137 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_adjustweight = 1;
goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 138 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_adjustweight = 0;
" ]

	node [ id 139 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_adjustweight.40_1 = rhp_adjustweight;
rhp_log (&quot;%s(): start with rhp_adjustweight %d\n&quot;, &amp;__FUNCTION__, rhp_adjustweight.40_1);
rhp_inited.41_2 = rhp_inited;
if (rhp_inited.41_2 == 0)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 140 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_log (&quot;%s(): first rhp_init() must be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 16&gt;; [INV]
" ]

	node [ id 141 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
rhp_sp_master_node_list.42_3 = rhp_sp_master_node_list;
_4 = rhp_sp_has_data (rhp_sp_master_node_list.42_3);
if (_4 == 0)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 142 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_log (&quot;%s(): there is no node data shouldnothappen!\n&quot;, &amp;__FUNCTION__);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 16&gt;; [INV]
" ]

	node [ id 143 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
rhp_improvements = 0;
rhp_notimprovements = 0;
rhp_crossings.43_5 = rhp_crossings;
rhp_start_crossings.44_6 = rhp_start_crossings;
rhp_log (&quot;%s(): setting initial edge crossings is %li %li\n&quot;, &amp;__FUNCTION__, rhp_start_crossings.44_6, rhp_crossings.43_5);
_7 = rhp_initial_crossings ();
rhp_crossings = _7;
rhp_crossings.45_8 = rhp_crossings;
rhp_start_crossings.46_9 = rhp_start_crossings;
rhp_log (&quot;%s(): configured initial edge crossings is %li %li\n&quot;, &amp;__FUNCTION__, rhp_start_crossings.46_9, rhp_crossings.45_8);
rhp_order_init ();
rhp_start_crossings.47_10 = rhp_start_crossings;
if (rhp_start_crossings.47_10 != 0)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 144 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
rhp_barycenter ();
" ]

	node [ id 145 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
rhp_start_crossings.48_11 = rhp_start_crossings;
if (rhp_start_crossings.48_11 != 0)
  goto &lt;bb 13&gt;; [INV]
else
  goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 146 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
rhp_crossings.49_12 = rhp_crossings;
_13 = rhp_crossings.49_12 * 100;
rhp_start_crossings.50_14 = rhp_start_crossings;
redu = _13 / rhp_start_crossings.50_14;
redu = 100 - redu;
goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 147 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
redu = 0;
" ]

	node [ id 148 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
rhp_sorted_nodelist ();
rhp_start_crossings.51_15 = rhp_start_crossings;
rhp_iter.52_16 = rhp_iter;
rhp_crossings.53_17 = rhp_crossings;
rhp_log (&quot;%s(): end and final edge crossings is %li after %d iterations and started with %li crossings reducing edge crossings with %lu percent\n&quot;, &amp;__FUNCTION__, rhp_crossings.53_17, rhp_iter.52_16, rhp_start_crossings.51_15, redu);
" ]

	node [ id 149 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
&lt;L14&gt;:
return;
" ]

	edge [ source 133 target 135 graphics [ fill "#0000ff" ] ] 
	edge [ source 135 target 136 graphics [ fill "#0000ff" ] ] 
	edge [ source 136 target 137 graphics [ fill "#000000" ] ] 
	edge [ source 136 target 138 graphics [ fill "#000000" ] ] 
	edge [ source 137 target 139 graphics [ fill "#0000ff" ] ] 
	edge [ source 138 target 139 graphics [ fill "#0000ff" ] ] 
	edge [ source 139 target 140 graphics [ fill "#000000" ] ] 
	edge [ source 139 target 141 graphics [ fill "#000000" ] ] 
	edge [ source 140 target 149 graphics [ fill "#0000ff" ] ] 
	edge [ source 141 target 142 graphics [ fill "#000000" ] ] 
	edge [ source 141 target 143 graphics [ fill "#000000" ] ] 
	edge [ source 142 target 149 graphics [ fill "#0000ff" ] ] 
	edge [ source 143 target 144 graphics [ fill "#000000" ] ] 
	edge [ source 143 target 145 graphics [ fill "#000000" ] ] 
	edge [ source 144 target 145 graphics [ fill "#0000ff" ] ] 
	edge [ source 145 target 146 graphics [ fill "#000000" ] ] 
	edge [ source 145 target 147 graphics [ fill "#000000" ] ] 
	edge [ source 146 target 148 graphics [ fill "#0000ff" ] ] 
	edge [ source 147 target 148 graphics [ fill "#0000ff" ] ] 
	edge [ source 148 target 149 graphics [ fill "#0000ff" ] ] 
	edge [ source 149 target 134 graphics [ fill "#000000" ] ] 


# function number 8
	node [ id 167 graphics [ fill "#ffffff" ] label "rhp_layout_callback ()
ENTRY" ]

	node [ id 168 graphics [ fill "#ffffff" ] label "rhp_layout_callback ()
EXIT" ]

	node [ id 169 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
if (getlayoutdata == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 170 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): no callback routine shouldnothappen!\n&quot;, &amp;__FUNCTION__);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 171 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_getlayoutdata = getlayoutdata;
" ]

	node [ id 172 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
&lt;L2&gt;:
return;
" ]

	edge [ source 167 target 169 graphics [ fill "#0000ff" ] ] 
	edge [ source 169 target 170 graphics [ fill "#000000" ] ] 
	edge [ source 169 target 171 graphics [ fill "#000000" ] ] 
	edge [ source 170 target 172 graphics [ fill "#0000ff" ] ] 
	edge [ source 171 target 172 graphics [ fill "#0000ff" ] ] 
	edge [ source 172 target 168 graphics [ fill "#000000" ] ] 
	node [ id 179 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
if (spn != 0B)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 180 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
_5 = spn-&gt;value;
nd = (struct rhpnode *) _5;
_6 = nd-&gt;position;
_7 = nd-&gt;level;
_8 = nd-&gt;innum;
rhp_log (&quot;%s(): node %d level %d pos %d\n&quot;, &amp;__FUNCTION__, _8, _7, _6);
_9 = nd-&gt;data;
_10 = nd-&gt;position;
_11 = nd-&gt;level;
_12 = nd-&gt;innum;
status = getnodedata (_12, _11, _10, _9);
if (status != 0)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 181 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
_13 = spn-&gt;key;
rhp_sp_master_node_list_sorted.57_14 = rhp_sp_master_node_list_sorted;
spn = rhp_sp_next (rhp_sp_master_node_list_sorted.57_14, _13);
" ]



# function number 9
	node [ id 182 graphics [ fill "#ffffff" ] label "rhp_node_foreach ()
ENTRY" ]

	node [ id 183 graphics [ fill "#ffffff" ] label "rhp_node_foreach ()
EXIT" ]

	node [ id 184 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
nd = 0B;
status = 0;
rhp_inited.54_1 = rhp_inited;
if (rhp_inited.54_1 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 185 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() must be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4419 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 186 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
if (getnodedata == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 187 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4419 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 188 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_sp_master_node_list_sorted.55_2 = rhp_sp_master_node_list_sorted;
_3 = rhp_sp_has_data (rhp_sp_master_node_list_sorted.55_2);
if (_3 == 0)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 189 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
D.4419 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 190 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
status = 0;
rhp_sp_master_node_list_sorted.56_4 = rhp_sp_master_node_list_sorted;
spn = rhp_sp_min (rhp_sp_master_node_list_sorted.56_4);
goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 191 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 192 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
D.4419 = status;
" ]

	node [ id 193 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
&lt;L11&gt;:
return D.4419;
" ]

	edge [ source 182 target 184 graphics [ fill "#0000ff" ] ] 
	edge [ source 184 target 185 graphics [ fill "#000000" ] ] 
	edge [ source 184 target 186 graphics [ fill "#000000" ] ] 
	edge [ source 185 target 193 graphics [ fill "#0000ff" ] ] 
	edge [ source 186 target 187 graphics [ fill "#000000" ] ] 
	edge [ source 186 target 188 graphics [ fill "#000000" ] ] 
	edge [ source 187 target 193 graphics [ fill "#0000ff" ] ] 
	edge [ source 188 target 189 graphics [ fill "#000000" ] ] 
	edge [ source 188 target 190 graphics [ fill "#000000" ] ] 
	edge [ source 189 target 193 graphics [ fill "#0000ff" ] ] 
	edge [ source 190 target 179 graphics [ fill "#0000ff" ] ] 
	edge [ source 180 target 191 graphics [ fill "#000000" ] ] 
	edge [ source 180 target 181 graphics [ fill "#000000" ] ] 
	edge [ source 191 target 192 graphics [ fill "#0000ff" ] ] 
	edge [ source 181 target 179 graphics [ fill "#0000ff" ] ] 
	edge [ source 179 target 180 graphics [ fill "#000000" ] ] 
	edge [ source 179 target 192 graphics [ fill "#000000" ] ] 
	edge [ source 192 target 193 graphics [ fill "#0000ff" ] ] 
	edge [ source 193 target 183 graphics [ fill "#000000" ] ] 


# function number 10
	node [ id 209 graphics [ fill "#ffffff" ] label "rhp_node_get_level ()
ENTRY" ]

	node [ id 210 graphics [ fill "#ffffff" ] label "rhp_node_get_level ()
EXIT" ]

	node [ id 211 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
nd = 0B;
rhp_inited.58_1 = rhp_inited;
if (rhp_inited.58_1 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 212 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() must be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4429 = -1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 213 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_sp_master_node_list.59_2 = rhp_sp_master_node_list;
_3 = rhp_sp_has_data (rhp_sp_master_node_list.59_2);
if (_3 == 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 214 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4429 = -1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 215 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_4 = (long long int) num;
rhp_sp_master_node_list.60_5 = rhp_sp_master_node_list;
spn = rhp_sp_lookup (rhp_sp_master_node_list.60_5, _4);
if (spn == 0B)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 216 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_log (&quot;%s(): could not find node %d in master_node_list!\n&quot;, &amp;__FUNCTION__, num);
D.4429 = -1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 217 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
_6 = spn-&gt;value;
nd = (struct rhpnode *) _6;
_7 = nd-&gt;position;
_8 = nd-&gt;level;
_9 = nd-&gt;innum;
rhp_log (&quot;%s(): node %d level %d pos %d\n&quot;, &amp;__FUNCTION__, _9, _8, _7);
D.4429 = nd-&gt;level;
" ]

	node [ id 218 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
&lt;L6&gt;:
return D.4429;
" ]

	edge [ source 209 target 211 graphics [ fill "#0000ff" ] ] 
	edge [ source 211 target 212 graphics [ fill "#000000" ] ] 
	edge [ source 211 target 213 graphics [ fill "#000000" ] ] 
	edge [ source 212 target 218 graphics [ fill "#0000ff" ] ] 
	edge [ source 213 target 214 graphics [ fill "#000000" ] ] 
	edge [ source 213 target 215 graphics [ fill "#000000" ] ] 
	edge [ source 214 target 218 graphics [ fill "#0000ff" ] ] 
	edge [ source 215 target 216 graphics [ fill "#000000" ] ] 
	edge [ source 215 target 217 graphics [ fill "#000000" ] ] 
	edge [ source 216 target 218 graphics [ fill "#0000ff" ] ] 
	edge [ source 217 target 218 graphics [ fill "#0000ff" ] ] 
	edge [ source 218 target 210 graphics [ fill "#000000" ] ] 


# function number 11
	node [ id 229 graphics [ fill "#ffffff" ] label "rhp_node_get_position ()
ENTRY" ]

	node [ id 230 graphics [ fill "#ffffff" ] label "rhp_node_get_position ()
EXIT" ]

	node [ id 231 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
nd = 0B;
rhp_inited.61_1 = rhp_inited;
if (rhp_inited.61_1 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 232 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() must be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4437 = -1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 233 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_sp_master_node_list.62_2 = rhp_sp_master_node_list;
_3 = rhp_sp_has_data (rhp_sp_master_node_list.62_2);
if (_3 == 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 234 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4437 = -1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 235 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_4 = (long long int) num;
rhp_sp_master_node_list.63_5 = rhp_sp_master_node_list;
spn = rhp_sp_lookup (rhp_sp_master_node_list.63_5, _4);
if (spn == 0B)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 236 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_log (&quot;%s(): could not find node %d in master_node_list!\n&quot;, &amp;__FUNCTION__, num);
D.4437 = -1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 237 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
_6 = spn-&gt;value;
nd = (struct rhpnode *) _6;
_7 = nd-&gt;position;
_8 = nd-&gt;level;
_9 = nd-&gt;innum;
rhp_log (&quot;%s(): node %d level %d pos %d\n&quot;, &amp;__FUNCTION__, _9, _8, _7);
D.4437 = nd-&gt;position;
" ]

	node [ id 238 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
&lt;L6&gt;:
return D.4437;
" ]

	edge [ source 229 target 231 graphics [ fill "#0000ff" ] ] 
	edge [ source 231 target 232 graphics [ fill "#000000" ] ] 
	edge [ source 231 target 233 graphics [ fill "#000000" ] ] 
	edge [ source 232 target 238 graphics [ fill "#0000ff" ] ] 
	edge [ source 233 target 234 graphics [ fill "#000000" ] ] 
	edge [ source 233 target 235 graphics [ fill "#000000" ] ] 
	edge [ source 234 target 238 graphics [ fill "#0000ff" ] ] 
	edge [ source 235 target 236 graphics [ fill "#000000" ] ] 
	edge [ source 235 target 237 graphics [ fill "#000000" ] ] 
	edge [ source 236 target 238 graphics [ fill "#0000ff" ] ] 
	edge [ source 237 target 238 graphics [ fill "#0000ff" ] ] 
	edge [ source 238 target 230 graphics [ fill "#000000" ] ] 


# function number 12
	node [ id 249 graphics [ fill "#ffffff" ] label "rhp_node_get_data ()
ENTRY" ]

	node [ id 250 graphics [ fill "#ffffff" ] label "rhp_node_get_data ()
EXIT" ]

	node [ id 251 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
nd = 0B;
rhp_inited.64_1 = rhp_inited;
if (rhp_inited.64_1 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 252 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() must be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4445 = -1B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 253 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_sp_master_node_list.65_2 = rhp_sp_master_node_list;
_3 = rhp_sp_has_data (rhp_sp_master_node_list.65_2);
if (_3 == 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 254 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4445 = -1B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 255 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_4 = (long long int) num;
rhp_sp_master_node_list.66_5 = rhp_sp_master_node_list;
spn = rhp_sp_lookup (rhp_sp_master_node_list.66_5, _4);
if (spn == 0B)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 256 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_log (&quot;%s(): could not find node %d in master_node_list!\n&quot;, &amp;__FUNCTION__, num);
D.4445 = -1B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 257 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
_6 = spn-&gt;value;
nd = (struct rhpnode *) _6;
_7 = nd-&gt;position;
_8 = nd-&gt;level;
_9 = nd-&gt;innum;
rhp_log (&quot;%s(): node %d level %d pos %d\n&quot;, &amp;__FUNCTION__, _9, _8, _7);
D.4445 = nd-&gt;data;
" ]

	node [ id 258 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
&lt;L6&gt;:
return D.4445;
" ]

	edge [ source 249 target 251 graphics [ fill "#0000ff" ] ] 
	edge [ source 251 target 252 graphics [ fill "#000000" ] ] 
	edge [ source 251 target 253 graphics [ fill "#000000" ] ] 
	edge [ source 252 target 258 graphics [ fill "#0000ff" ] ] 
	edge [ source 253 target 254 graphics [ fill "#000000" ] ] 
	edge [ source 253 target 255 graphics [ fill "#000000" ] ] 
	edge [ source 254 target 258 graphics [ fill "#0000ff" ] ] 
	edge [ source 255 target 256 graphics [ fill "#000000" ] ] 
	edge [ source 255 target 257 graphics [ fill "#000000" ] ] 
	edge [ source 256 target 258 graphics [ fill "#0000ff" ] ] 
	edge [ source 257 target 258 graphics [ fill "#0000ff" ] ] 
	edge [ source 258 target 250 graphics [ fill "#000000" ] ] 
	node [ id 269 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
if (spn != 0B)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 270 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
_5 = spn-&gt;value;
ed = (struct rhpedge *) _5;
_6 = ed-&gt;data;
_7 = ed-&gt;crossings;
_8 = ed-&gt;tn;
_9 = _8-&gt;position;
_10 = ed-&gt;tn;
_11 = _10-&gt;level;
_12 = ed-&gt;tn;
_13 = _12-&gt;innum;
_14 = ed-&gt;fn;
_15 = _14-&gt;position;
_16 = ed-&gt;fn;
_17 = _16-&gt;level;
_18 = ed-&gt;fn;
_19 = _18-&gt;innum;
_20 = ed-&gt;innum;
status = getedgedata (_20, _19, _17, _15, _13, _11, _9, _7, _6);
if (status != 0)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 271 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
_21 = spn-&gt;key;
rhp_sp_master_edge_list.70_22 = rhp_sp_master_edge_list;
spn = rhp_sp_next (rhp_sp_master_edge_list.70_22, _21);
" ]



# function number 13
	node [ id 272 graphics [ fill "#ffffff" ] label "rhp_edge_foreach ()
ENTRY" ]

	node [ id 273 graphics [ fill "#ffffff" ] label "rhp_edge_foreach ()
EXIT" ]

	node [ id 274 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
ed = 0B;
status = 0;
rhp_inited.67_1 = rhp_inited;
if (rhp_inited.67_1 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 275 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() must be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4453 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 276 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
if (getedgedata == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 277 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4453 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 278 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_sp_master_edge_list.68_2 = rhp_sp_master_edge_list;
_3 = rhp_sp_has_data (rhp_sp_master_edge_list.68_2);
if (_3 == 0)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 279 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
D.4453 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 280 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
status = 0;
rhp_sp_master_edge_list.69_4 = rhp_sp_master_edge_list;
spn = rhp_sp_min (rhp_sp_master_edge_list.69_4);
goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 281 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 282 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
D.4453 = status;
" ]

	node [ id 283 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
&lt;L11&gt;:
return D.4453;
" ]

	edge [ source 272 target 274 graphics [ fill "#0000ff" ] ] 
	edge [ source 274 target 275 graphics [ fill "#000000" ] ] 
	edge [ source 274 target 276 graphics [ fill "#000000" ] ] 
	edge [ source 275 target 283 graphics [ fill "#0000ff" ] ] 
	edge [ source 276 target 277 graphics [ fill "#000000" ] ] 
	edge [ source 276 target 278 graphics [ fill "#000000" ] ] 
	edge [ source 277 target 283 graphics [ fill "#0000ff" ] ] 
	edge [ source 278 target 279 graphics [ fill "#000000" ] ] 
	edge [ source 278 target 280 graphics [ fill "#000000" ] ] 
	edge [ source 279 target 283 graphics [ fill "#0000ff" ] ] 
	edge [ source 280 target 269 graphics [ fill "#0000ff" ] ] 
	edge [ source 270 target 281 graphics [ fill "#000000" ] ] 
	edge [ source 270 target 271 graphics [ fill "#000000" ] ] 
	edge [ source 281 target 282 graphics [ fill "#0000ff" ] ] 
	edge [ source 271 target 269 graphics [ fill "#0000ff" ] ] 
	edge [ source 269 target 270 graphics [ fill "#000000" ] ] 
	edge [ source 269 target 282 graphics [ fill "#000000" ] ] 
	edge [ source 282 target 283 graphics [ fill "#0000ff" ] ] 
	edge [ source 283 target 273 graphics [ fill "#000000" ] ] 


# function number 14
	node [ id 299 graphics [ fill "#ffffff" ] label "rhp_initial_crossings ()
ENTRY" ]

	node [ id 300 graphics [ fill "#ffffff" ] label "rhp_initial_crossings ()
EXIT" ]

	node [ id 301 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
rhp_start_crossings.71_1 = rhp_start_crossings;
rhp_log (&quot;%s(): start crossings %li\n&quot;, &amp;__FUNCTION__, rhp_start_crossings.71_1);
rhp_inited.72_2 = rhp_inited;
if (rhp_inited.72_2 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 302 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() must be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4463 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 303 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_sp_master_node_list.73_3 = rhp_sp_master_node_list;
_4 = rhp_sp_has_data (rhp_sp_master_node_list.73_3);
if (_4 == 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 304 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_log (&quot;%s(): no nodes shouldnothappen!\n&quot;, &amp;__FUNCTION__);
rhp_start_crossings = 0;
D.4463 = rhp_start_crossings;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 305 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_sp_master_edge_list.74_5 = rhp_sp_master_edge_list;
_6 = rhp_sp_has_data (rhp_sp_master_edge_list.74_5);
if (_6 == 0)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 306 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_start_crossings = 0;
" ]

	node [ id 307 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
rhp_start_crossings.75_7 = rhp_start_crossings;
if (rhp_start_crossings.75_7 &gt;= 0)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 308 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_start_crossings.76_8 = rhp_start_crossings;
rhp_log (&quot;%s(): already inited start crossings %li\n&quot;, &amp;__FUNCTION__, rhp_start_crossings.76_8);
D.4463 = rhp_start_crossings;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 309 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
rhp_log (&quot;%s(): allocate layers\n&quot;, &amp;__FUNCTION__);
rhp_allocatelayers ();
rhp_allocateadjacencylists ();
_9 = rhp_countisolatednodes ();
rhp_number_of_isolated_nodes = _9;
rhp_number_of_isolated_nodes.77_10 = rhp_number_of_isolated_nodes;
_11 = (long int) rhp_number_of_isolated_nodes.77_10;
rhp_log (&quot;%s(): %li single nodes\n&quot;, &amp;__FUNCTION__, _11);
rhp_initcrossings ();
rhp_updateallcrossings ();
_12 = rhp_numberofcrossings ();
rhp_start_crossings = _12;
rhp_number_of_nodes.78_13 = rhp_number_of_nodes;
_14 = (long unsigned int) rhp_number_of_nodes.78_13;
_15 = _14 * 80;
rhp_log (&quot;%s(): using %lu bytes for the node data core part\n&quot;, &amp;__FUNCTION__, _15);
rhp_number_of_edges.79_16 = rhp_number_of_edges;
_17 = (long unsigned int) rhp_number_of_edges.79_16;
_18 = _17 * 56;
rhp_log (&quot;%s(): using %lu bytes for the edge data\n&quot;, &amp;__FUNCTION__, _18);
D.4463 = rhp_start_crossings;
" ]

	node [ id 310 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
&lt;L8&gt;:
return D.4463;
" ]

	edge [ source 299 target 301 graphics [ fill "#0000ff" ] ] 
	edge [ source 301 target 302 graphics [ fill "#000000" ] ] 
	edge [ source 301 target 303 graphics [ fill "#000000" ] ] 
	edge [ source 302 target 310 graphics [ fill "#0000ff" ] ] 
	edge [ source 303 target 304 graphics [ fill "#000000" ] ] 
	edge [ source 303 target 305 graphics [ fill "#000000" ] ] 
	edge [ source 304 target 310 graphics [ fill "#0000ff" ] ] 
	edge [ source 305 target 306 graphics [ fill "#000000" ] ] 
	edge [ source 305 target 307 graphics [ fill "#000000" ] ] 
	edge [ source 306 target 307 graphics [ fill "#0000ff" ] ] 
	edge [ source 307 target 308 graphics [ fill "#000000" ] ] 
	edge [ source 307 target 309 graphics [ fill "#000000" ] ] 
	edge [ source 308 target 310 graphics [ fill "#0000ff" ] ] 
	edge [ source 309 target 310 graphics [ fill "#0000ff" ] ] 
	edge [ source 310 target 300 graphics [ fill "#000000" ] ] 


# function number 15
	node [ id 323 graphics [ fill "#ffffff" ] label "rhp_current_crossings ()
ENTRY" ]

	node [ id 324 graphics [ fill "#ffffff" ] label "rhp_current_crossings ()
EXIT" ]

	node [ id 325 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
rhp_inited.80_1 = rhp_inited;
if (rhp_inited.80_1 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 326 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() must be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4473 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 327 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_sp_master_node_list.81_2 = rhp_sp_master_node_list;
_3 = rhp_sp_has_data (rhp_sp_master_node_list.81_2);
if (_3 == 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 328 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_log (&quot;%s(): no nodes shouldnothappen!\n&quot;, &amp;__FUNCTION__);
rhp_crossings = 0;
D.4473 = rhp_crossings;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 329 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_sp_master_edge_list.82_4 = rhp_sp_master_edge_list;
_5 = rhp_sp_has_data (rhp_sp_master_edge_list.82_4);
if (_5 == 0)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 330 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_crossings = 0;
D.4473 = rhp_crossings;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 331 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
rhp_start_crossings.83_6 = rhp_start_crossings;
if (rhp_start_crossings.83_6 &lt; 0)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 332 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
_7 = rhp_initial_crossings ();
rhp_crossings = _7;
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 333 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
rhp_number_of_edges.84_8 = rhp_number_of_edges;
if (rhp_number_of_edges.84_8 == 1)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 334 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
rhp_crossings = 0;
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 335 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
rhp_crossings = 0;
rhp_updateallcrossings ();
_9 = rhp_numberofcrossings ();
rhp_crossings = _9;
" ]

	node [ id 336 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
D.4473 = rhp_crossings;
" ]

	node [ id 337 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
&lt;L12&gt;:
return D.4473;
" ]

	edge [ source 323 target 325 graphics [ fill "#0000ff" ] ] 
	edge [ source 325 target 326 graphics [ fill "#000000" ] ] 
	edge [ source 325 target 327 graphics [ fill "#000000" ] ] 
	edge [ source 326 target 337 graphics [ fill "#0000ff" ] ] 
	edge [ source 327 target 328 graphics [ fill "#000000" ] ] 
	edge [ source 327 target 329 graphics [ fill "#000000" ] ] 
	edge [ source 328 target 337 graphics [ fill "#0000ff" ] ] 
	edge [ source 329 target 330 graphics [ fill "#000000" ] ] 
	edge [ source 329 target 331 graphics [ fill "#000000" ] ] 
	edge [ source 330 target 337 graphics [ fill "#0000ff" ] ] 
	edge [ source 331 target 332 graphics [ fill "#000000" ] ] 
	edge [ source 331 target 333 graphics [ fill "#000000" ] ] 
	edge [ source 332 target 336 graphics [ fill "#0000ff" ] ] 
	edge [ source 333 target 334 graphics [ fill "#000000" ] ] 
	edge [ source 333 target 335 graphics [ fill "#000000" ] ] 
	edge [ source 334 target 336 graphics [ fill "#0000ff" ] ] 
	edge [ source 335 target 336 graphics [ fill "#0000ff" ] ] 
	edge [ source 336 target 337 graphics [ fill "#0000ff" ] ] 
	edge [ source 337 target 324 graphics [ fill "#000000" ] ] 


# function number 16
	node [ id 353 graphics [ fill "#ffffff" ] label "rhp_current_crossings_at_level ()
ENTRY" ]

	node [ id 354 graphics [ fill "#ffffff" ] label "rhp_current_crossings_at_level ()
EXIT" ]

	node [ id 355 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
is = 0B;
rhp_inited.85_1 = rhp_inited;
if (rhp_inited.85_1 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 356 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() must be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4487 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 17&gt;; [INV]
" ]

	node [ id 357 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_sp_master_node_list.86_2 = rhp_sp_master_node_list;
_3 = rhp_sp_has_data (rhp_sp_master_node_list.86_2);
if (_3 == 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 358 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_log (&quot;%s(): no nodes shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4487 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 17&gt;; [INV]
" ]

	node [ id 359 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
if (level &lt; 0)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 360 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_log (&quot;%s(): level %d is below 0 shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
D.4487 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 17&gt;; [INV]
" ]

	node [ id 361 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
rhp_maxlevel.87_4 = rhp_maxlevel;
if (level &gt; rhp_maxlevel.87_4)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 362 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_maxlevel.88_5 = rhp_maxlevel;
rhp_log (&quot;%s(): level %d is above max level %dshouldnothappen!\n&quot;, &amp;__FUNCTION__, level, rhp_maxlevel.88_5);
D.4487 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 17&gt;; [INV]
" ]

	node [ id 363 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
rhp_sp_between_layers.89_6 = rhp_sp_between_layers;
_7 = rhp_sp_has_data (rhp_sp_between_layers.89_6);
if (_7 == 0)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 364 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
D.4487 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 17&gt;; [INV]
" ]

	node [ id 365 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
rhp_nlevels.90_8 = rhp_nlevels;
if (rhp_nlevels.90_8 == 0)
  goto &lt;bb 13&gt;; [INV]
else
  goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 366 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
rhp_log (&quot;%s(): no levels shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4487 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 17&gt;; [INV]
" ]

	node [ id 367 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
_9 = (long long int) level;
rhp_sp_between_layers.91_10 = rhp_sp_between_layers;
spn = rhp_sp_lookup (rhp_sp_between_layers.91_10, _9);
if (spn != 0B)
  goto &lt;bb 15&gt;; [INV]
else
  goto &lt;bb 16&gt;; [INV]
" ]

	node [ id 368 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
_11 = spn-&gt;value;
is = (struct rhp_inter_layer_struct *) _11;
D.4487 = is-&gt;number_of_crossings;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 17&gt;; [INV]
" ]

	node [ id 369 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
rhp_log (&quot;%s(): could not get data for level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
D.4487 = 0;
" ]

	node [ id 370 graphics [ fill "#d3d3d3" ] label "&lt;bb 17&gt;:
&lt;L14&gt;:
return D.4487;
" ]

	edge [ source 353 target 355 graphics [ fill "#0000ff" ] ] 
	edge [ source 355 target 356 graphics [ fill "#000000" ] ] 
	edge [ source 355 target 357 graphics [ fill "#000000" ] ] 
	edge [ source 356 target 370 graphics [ fill "#0000ff" ] ] 
	edge [ source 357 target 358 graphics [ fill "#000000" ] ] 
	edge [ source 357 target 359 graphics [ fill "#000000" ] ] 
	edge [ source 358 target 370 graphics [ fill "#0000ff" ] ] 
	edge [ source 359 target 360 graphics [ fill "#000000" ] ] 
	edge [ source 359 target 361 graphics [ fill "#000000" ] ] 
	edge [ source 360 target 370 graphics [ fill "#0000ff" ] ] 
	edge [ source 361 target 362 graphics [ fill "#000000" ] ] 
	edge [ source 361 target 363 graphics [ fill "#000000" ] ] 
	edge [ source 362 target 370 graphics [ fill "#0000ff" ] ] 
	edge [ source 363 target 364 graphics [ fill "#000000" ] ] 
	edge [ source 363 target 365 graphics [ fill "#000000" ] ] 
	edge [ source 364 target 370 graphics [ fill "#0000ff" ] ] 
	edge [ source 365 target 366 graphics [ fill "#000000" ] ] 
	edge [ source 365 target 367 graphics [ fill "#000000" ] ] 
	edge [ source 366 target 370 graphics [ fill "#0000ff" ] ] 
	edge [ source 367 target 368 graphics [ fill "#000000" ] ] 
	edge [ source 367 target 369 graphics [ fill "#000000" ] ] 
	edge [ source 368 target 370 graphics [ fill "#0000ff" ] ] 
	edge [ source 369 target 370 graphics [ fill "#0000ff" ] ] 
	edge [ source 370 target 354 graphics [ fill "#000000" ] ] 


# function number 17
	node [ id 389 graphics [ fill "#ffffff" ] label "rhp_nodes_in_level ()
ENTRY" ]

	node [ id 390 graphics [ fill "#ffffff" ] label "rhp_nodes_in_level ()
EXIT" ]

	node [ id 391 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
rl = 0B;
rhp_inited.92_1 = rhp_inited;
if (rhp_inited.92_1 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 392 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() must be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4503 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 393 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_sp_master_node_list.93_2 = rhp_sp_master_node_list;
_3 = rhp_sp_has_data (rhp_sp_master_node_list.93_2);
if (_3 == 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 394 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_log (&quot;%s(): no nodes shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4503 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 395 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
if (level &lt; 0)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 396 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_log (&quot;%s(): level %d is below 0 shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
D.4503 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 397 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
rhp_maxlevel.94_4 = rhp_maxlevel;
if (level &gt; rhp_maxlevel.94_4)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 398 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_maxlevel.95_5 = rhp_maxlevel;
rhp_log (&quot;%s(): level %d is above max level %dshouldnothappen!\n&quot;, &amp;__FUNCTION__, level, rhp_maxlevel.95_5);
D.4503 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 399 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
rhp_sp_layers.96_6 = rhp_sp_layers;
_7 = rhp_sp_has_data (rhp_sp_layers.96_6);
if (_7 == 0)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 400 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
D.4503 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 401 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
_8 = (long long int) level;
rhp_sp_layers.97_9 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.97_9, _8);
if (spn != 0B)
  goto &lt;bb 13&gt;; [INV]
else
  goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 402 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
_10 = spn-&gt;value;
rl = (struct rhplevel *) _10;
D.4503 = rl-&gt;number_of_nodes;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 403 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
rhp_log (&quot;%s(): could not find data for level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
D.4503 = 0;
" ]

	node [ id 404 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
&lt;L12&gt;:
return D.4503;
" ]

	edge [ source 389 target 391 graphics [ fill "#0000ff" ] ] 
	edge [ source 391 target 392 graphics [ fill "#000000" ] ] 
	edge [ source 391 target 393 graphics [ fill "#000000" ] ] 
	edge [ source 392 target 404 graphics [ fill "#0000ff" ] ] 
	edge [ source 393 target 394 graphics [ fill "#000000" ] ] 
	edge [ source 393 target 395 graphics [ fill "#000000" ] ] 
	edge [ source 394 target 404 graphics [ fill "#0000ff" ] ] 
	edge [ source 395 target 396 graphics [ fill "#000000" ] ] 
	edge [ source 395 target 397 graphics [ fill "#000000" ] ] 
	edge [ source 396 target 404 graphics [ fill "#0000ff" ] ] 
	edge [ source 397 target 398 graphics [ fill "#000000" ] ] 
	edge [ source 397 target 399 graphics [ fill "#000000" ] ] 
	edge [ source 398 target 404 graphics [ fill "#0000ff" ] ] 
	edge [ source 399 target 400 graphics [ fill "#000000" ] ] 
	edge [ source 399 target 401 graphics [ fill "#000000" ] ] 
	edge [ source 400 target 404 graphics [ fill "#0000ff" ] ] 
	edge [ source 401 target 402 graphics [ fill "#000000" ] ] 
	edge [ source 401 target 403 graphics [ fill "#000000" ] ] 
	edge [ source 402 target 404 graphics [ fill "#0000ff" ] ] 
	edge [ source 403 target 404 graphics [ fill "#0000ff" ] ] 
	edge [ source 404 target 390 graphics [ fill "#000000" ] ] 
	node [ id 421 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
if (spn != 0B)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 422 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
c = c + 1;
_5 = spn-&gt;key;
rhp_sp_master_node_list.101_6 = rhp_sp_master_node_list;
spn = rhp_sp_next (rhp_sp_master_node_list.101_6, _5);
" ]



# function number 18
	node [ id 423 graphics [ fill "#ffffff" ] label "rhp_nodes_in_layout ()
ENTRY" ]

	node [ id 424 graphics [ fill "#ffffff" ] label "rhp_nodes_in_layout ()
EXIT" ]

	node [ id 425 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
c = 0;
spn = 0B;
rhp_inited.98_1 = rhp_inited;
if (rhp_inited.98_1 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 426 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() must be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4517 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 427 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_sp_master_node_list.99_2 = rhp_sp_master_node_list;
_3 = rhp_sp_has_data (rhp_sp_master_node_list.99_2);
if (_3 == 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 428 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4517 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 429 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
c = 0;
rhp_sp_master_node_list.100_4 = rhp_sp_master_node_list;
spn = rhp_sp_min (rhp_sp_master_node_list.100_4);
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 430 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
D.4517 = c;
" ]

	node [ id 431 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
&lt;L7&gt;:
return D.4517;
" ]

	edge [ source 423 target 425 graphics [ fill "#0000ff" ] ] 
	edge [ source 425 target 426 graphics [ fill "#000000" ] ] 
	edge [ source 425 target 427 graphics [ fill "#000000" ] ] 
	edge [ source 426 target 431 graphics [ fill "#0000ff" ] ] 
	edge [ source 427 target 428 graphics [ fill "#000000" ] ] 
	edge [ source 427 target 429 graphics [ fill "#000000" ] ] 
	edge [ source 428 target 431 graphics [ fill "#0000ff" ] ] 
	edge [ source 429 target 421 graphics [ fill "#0000ff" ] ] 
	edge [ source 422 target 421 graphics [ fill "#0000ff" ] ] 
	edge [ source 421 target 422 graphics [ fill "#000000" ] ] 
	edge [ source 421 target 430 graphics [ fill "#000000" ] ] 
	edge [ source 430 target 431 graphics [ fill "#0000ff" ] ] 
	edge [ source 431 target 424 graphics [ fill "#000000" ] ] 
	node [ id 443 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
if (spn != 0B)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 444 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
c = c + 1;
_5 = spn-&gt;key;
rhp_sp_master_edge_list.105_6 = rhp_sp_master_edge_list;
spn = rhp_sp_next (rhp_sp_master_edge_list.105_6, _5);
" ]



# function number 19
	node [ id 445 graphics [ fill "#ffffff" ] label "rhp_edges_in_layout ()
ENTRY" ]

	node [ id 446 graphics [ fill "#ffffff" ] label "rhp_edges_in_layout ()
EXIT" ]

	node [ id 447 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
c = 0;
spn = 0B;
rhp_inited.102_1 = rhp_inited;
if (rhp_inited.102_1 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 448 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): first rhp_init() must be done shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4523 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 449 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_sp_master_edge_list.103_2 = rhp_sp_master_edge_list;
_3 = rhp_sp_has_data (rhp_sp_master_edge_list.103_2);
if (_3 == 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 450 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4523 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 451 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
c = 0;
rhp_sp_master_edge_list.104_4 = rhp_sp_master_edge_list;
spn = rhp_sp_min (rhp_sp_master_edge_list.104_4);
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 452 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
D.4523 = c;
" ]

	node [ id 453 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
&lt;L7&gt;:
return D.4523;
" ]

	edge [ source 445 target 447 graphics [ fill "#0000ff" ] ] 
	edge [ source 447 target 448 graphics [ fill "#000000" ] ] 
	edge [ source 447 target 449 graphics [ fill "#000000" ] ] 
	edge [ source 448 target 453 graphics [ fill "#0000ff" ] ] 
	edge [ source 449 target 450 graphics [ fill "#000000" ] ] 
	edge [ source 449 target 451 graphics [ fill "#000000" ] ] 
	edge [ source 450 target 453 graphics [ fill "#0000ff" ] ] 
	edge [ source 451 target 443 graphics [ fill "#0000ff" ] ] 
	edge [ source 444 target 443 graphics [ fill "#0000ff" ] ] 
	edge [ source 443 target 444 graphics [ fill "#000000" ] ] 
	edge [ source 443 target 452 graphics [ fill "#000000" ] ] 
	edge [ source 452 target 453 graphics [ fill "#0000ff" ] ] 
	edge [ source 453 target 446 graphics [ fill "#000000" ] ] 


# function number 20
	node [ id 465 graphics [ fill "#ffffff" ] label "rhp_free ()
ENTRY" ]

	node [ id 466 graphics [ fill "#ffffff" ] label "rhp_free ()
EXIT" ]

	node [ id 467 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
if (ptr == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 468 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): nil ptr from %s line %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, func, line);
D.4529 = 0B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 469 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
if (ptr != 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 470 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
myfree (ptr, func, line);
rhp_n_free.106_1 = rhp_n_free;
_2 = rhp_n_free.106_1 + 1;
rhp_n_free = _2;
rhp_dolog.107_3 = rhp_dolog;
if (rhp_dolog.107_3 &gt; 1)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 471 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_log (&quot;%p\t%s\tline %d\trhp_free()\tmemtrace\n&quot;, ptr, func, line);
" ]

	node [ id 472 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
D.4529 = 0B;
" ]

	node [ id 473 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
&lt;L6&gt;:
return D.4529;
" ]

	edge [ source 465 target 467 graphics [ fill "#0000ff" ] ] 
	edge [ source 467 target 468 graphics [ fill "#000000" ] ] 
	edge [ source 467 target 469 graphics [ fill "#000000" ] ] 
	edge [ source 468 target 473 graphics [ fill "#0000ff" ] ] 
	edge [ source 469 target 470 graphics [ fill "#000000" ] ] 
	edge [ source 469 target 472 graphics [ fill "#000000" ] ] 
	edge [ source 470 target 471 graphics [ fill "#000000" ] ] 
	edge [ source 470 target 472 graphics [ fill "#000000" ] ] 
	edge [ source 471 target 472 graphics [ fill "#0000ff" ] ] 
	edge [ source 472 target 473 graphics [ fill "#0000ff" ] ] 
	edge [ source 473 target 466 graphics [ fill "#000000" ] ] 


# function number 21
	node [ id 483 graphics [ fill "#ffffff" ] label "rhp_malloc ()
ENTRY" ]

	node [ id 484 graphics [ fill "#ffffff" ] label "rhp_malloc ()
EXIT" ]

	node [ id 485 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
ptr = 0B;
if (n == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 486 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): 0 bytes to malloc from %s line %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, func, line);
D.4537 = 0B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 487 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_n_malloc.108_1 = rhp_n_malloc;
_2 = rhp_n_malloc.108_1 + 1;
rhp_n_malloc = _2;
ptr = mymalloc (n, func, line);
rhp_dolog.109_3 = rhp_dolog;
if (rhp_dolog.109_3 &gt; 1)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 488 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_log (&quot;%p\t%s\tline %d\trhp_malloc(%lu)\tmemtrace\n&quot;, ptr, func, line, n);
" ]

	node [ id 489 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
D.4537 = ptr;
" ]

	node [ id 490 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
&lt;L4&gt;:
return D.4537;
" ]

	edge [ source 483 target 485 graphics [ fill "#0000ff" ] ] 
	edge [ source 485 target 486 graphics [ fill "#000000" ] ] 
	edge [ source 485 target 487 graphics [ fill "#000000" ] ] 
	edge [ source 486 target 490 graphics [ fill "#0000ff" ] ] 
	edge [ source 487 target 488 graphics [ fill "#000000" ] ] 
	edge [ source 487 target 489 graphics [ fill "#000000" ] ] 
	edge [ source 488 target 489 graphics [ fill "#0000ff" ] ] 
	edge [ source 489 target 490 graphics [ fill "#0000ff" ] ] 
	edge [ source 490 target 484 graphics [ fill "#000000" ] ] 


# function number 22
	node [ id 499 graphics [ fill "#ffffff" ] label "rhp_sp_new ()
ENTRY" ]

	node [ id 500 graphics [ fill "#ffffff" ] label "rhp_sp_new ()
EXIT" ]

	node [ id 501 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
newsp = 0B;
newsp = rhp_malloc (16, &amp;__FUNCTION__, 1651);
newsp-&gt;root = 0B;
newsp-&gt;delval = delval;
D.4541 = newsp;
" ]

	node [ id 502 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
&lt;L0&gt;:
return D.4541;
" ]

	edge [ source 499 target 501 graphics [ fill "#0000ff" ] ] 
	edge [ source 501 target 502 graphics [ fill "#0000ff" ] ] 
	edge [ source 502 target 500 graphics [ fill "#000000" ] ] 


# function number 23
	node [ id 507 graphics [ fill "#ffffff" ] label "rhp_sp_has_data ()
ENTRY" ]

	node [ id 508 graphics [ fill "#ffffff" ] label "rhp_sp_has_data ()
EXIT" ]

	node [ id 509 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
if (sp == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 510 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
D.4545 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 511 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_1 = sp-&gt;root;
if (_1 == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 512 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4545 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 513 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
D.4545 = 1;
" ]

	node [ id 514 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
&lt;L4&gt;:
return D.4545;
" ]

	edge [ source 507 target 509 graphics [ fill "#0000ff" ] ] 
	edge [ source 509 target 510 graphics [ fill "#000000" ] ] 
	edge [ source 509 target 511 graphics [ fill "#000000" ] ] 
	edge [ source 510 target 514 graphics [ fill "#0000ff" ] ] 
	edge [ source 511 target 512 graphics [ fill "#000000" ] ] 
	edge [ source 511 target 513 graphics [ fill "#000000" ] ] 
	edge [ source 512 target 514 graphics [ fill "#0000ff" ] ] 
	edge [ source 513 target 514 graphics [ fill "#0000ff" ] ] 
	edge [ source 514 target 508 graphics [ fill "#000000" ] ] 
	node [ id 523 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
_2 = nspn-&gt;l;
if (_2 != 0B)
  goto &lt;bb 8&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 524 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
nspn = nspn-&gt;l;
" ]



# function number 24
	node [ id 525 graphics [ fill "#ffffff" ] label "rhp_sp_min ()
ENTRY" ]

	node [ id 526 graphics [ fill "#ffffff" ] label "rhp_sp_min ()
EXIT" ]

	node [ id 527 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
nspn = 0B;
if (sp == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 528 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
D.4551 = 0B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 529 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_1 = sp-&gt;root;
if (_1 == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 530 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4551 = 0B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 531 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
nspn = sp-&gt;root;
if (nspn != 0B)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 532 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 533 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
D.4551 = nspn;
" ]

	node [ id 534 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
&lt;L9&gt;:
return D.4551;
" ]

	edge [ source 525 target 527 graphics [ fill "#0000ff" ] ] 
	edge [ source 527 target 528 graphics [ fill "#000000" ] ] 
	edge [ source 527 target 529 graphics [ fill "#000000" ] ] 
	edge [ source 528 target 534 graphics [ fill "#0000ff" ] ] 
	edge [ source 529 target 530 graphics [ fill "#000000" ] ] 
	edge [ source 529 target 531 graphics [ fill "#000000" ] ] 
	edge [ source 530 target 534 graphics [ fill "#0000ff" ] ] 
	edge [ source 531 target 532 graphics [ fill "#000000" ] ] 
	edge [ source 531 target 533 graphics [ fill "#000000" ] ] 
	edge [ source 532 target 523 graphics [ fill "#0000ff" ] ] 
	edge [ source 524 target 523 graphics [ fill "#0000ff" ] ] 
	edge [ source 523 target 524 graphics [ fill "#000000" ] ] 
	edge [ source 523 target 533 graphics [ fill "#000000" ] ] 
	edge [ source 533 target 534 graphics [ fill "#0000ff" ] ] 
	edge [ source 534 target 526 graphics [ fill "#000000" ] ] 


# function number 25
	node [ id 547 graphics [ fill "#ffffff" ] label "rhp_sp_insert ()
ENTRY" ]

	node [ id 548 graphics [ fill "#ffffff" ] label "rhp_sp_insert ()
EXIT" ]

	node [ id 549 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
newspn = 0B;
if (sp == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 550 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 19&gt;; [INV]
" ]

	node [ id 551 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_1 = sp-&gt;root;
if (_1 == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 552 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
newspn = rhp_malloc (32, &amp;__FUNCTION__, 1731);
sp-&gt;root = newspn;
_2 = sp-&gt;root;
_2-&gt;l = 0B;
_3 = sp-&gt;root;
_3-&gt;r = 0B;
_4 = sp-&gt;root;
_4-&gt;key = key;
_5 = sp-&gt;root;
_5-&gt;value = value;
rhp_verbose.110_6 = rhp_verbose;
if (rhp_verbose.110_6 != 0)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 553 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_7 = sp-&gt;root;
_8 = _7-&gt;key;
_9 = (long unsigned int) _8;
_10 = sp-&gt;root;
rhp_log (&quot;%s(): sp (%p) sp-&gt;root (%p) is %li at first entry\n&quot;, &amp;__FUNCTION__, sp, _10, _9);
" ]

	node [ id 554 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 19&gt;; [INV]
" ]

	node [ id 555 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
rhp_sp_sp (sp, key);
_11 = sp-&gt;root;
_12 = _11-&gt;key;
if (key == _12)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 556 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
_13 = sp-&gt;delval;
if (_13 != 0)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 557 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
_14 = sp-&gt;root;
_15 = _14-&gt;value;
if (_15 != 0)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 558 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
_16 = sp-&gt;root;
_17 = _16-&gt;value;
_18 = (void *) _17;
rhp_free (_18, &amp;__FUNCTION__, 1758);
_19 = sp-&gt;root;
_19-&gt;value = 0;
" ]

	node [ id 559 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
_20 = sp-&gt;root;
_20-&gt;value = value;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 19&gt;; [INV]
" ]

	node [ id 560 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
newspn = rhp_malloc (32, &amp;__FUNCTION__, 1766);
newspn-&gt;key = key;
newspn-&gt;value = value;
_21 = sp-&gt;root;
_22 = _21-&gt;key;
if (key &gt; _22)
  goto &lt;bb 14&gt;; [INV]
else
  goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 561 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
_23 = sp-&gt;root;
newspn-&gt;l = _23;
_24 = newspn-&gt;l;
_25 = _24-&gt;r;
newspn-&gt;r = _25;
_26 = newspn-&gt;l;
_26-&gt;r = 0B;
goto &lt;bb 16&gt;; [INV]
" ]

	node [ id 562 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
_27 = sp-&gt;root;
newspn-&gt;r = _27;
_28 = newspn-&gt;r;
_29 = _28-&gt;l;
newspn-&gt;l = _29;
_30 = newspn-&gt;r;
_30-&gt;l = 0B;
" ]

	node [ id 563 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
sp-&gt;root = newspn;
rhp_verbose.111_31 = rhp_verbose;
if (rhp_verbose.111_31 != 0)
  goto &lt;bb 17&gt;; [INV]
else
  goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 564 graphics [ fill "#d3d3d3" ] label "&lt;bb 17&gt;:
_32 = sp-&gt;root;
_33 = _32-&gt;key;
_34 = (long unsigned int) _33;
_35 = sp-&gt;root;
rhp_log (&quot;%s(): sp (%p) sp-&gt;root (%p) is %li at next entry\n&quot;, &amp;__FUNCTION__, sp, _35, _34);
" ]

	node [ id 565 graphics [ fill "#d3d3d3" ] label "&lt;bb 18&gt;:
" ]

	node [ id 566 graphics [ fill "#d3d3d3" ] label "&lt;bb 19&gt;:
&lt;L17&gt;:
return;
" ]

	edge [ source 547 target 549 graphics [ fill "#0000ff" ] ] 
	edge [ source 549 target 550 graphics [ fill "#000000" ] ] 
	edge [ source 549 target 551 graphics [ fill "#000000" ] ] 
	edge [ source 550 target 566 graphics [ fill "#0000ff" ] ] 
	edge [ source 551 target 552 graphics [ fill "#000000" ] ] 
	edge [ source 551 target 555 graphics [ fill "#000000" ] ] 
	edge [ source 552 target 553 graphics [ fill "#000000" ] ] 
	edge [ source 552 target 554 graphics [ fill "#000000" ] ] 
	edge [ source 553 target 554 graphics [ fill "#0000ff" ] ] 
	edge [ source 554 target 566 graphics [ fill "#0000ff" ] ] 
	edge [ source 555 target 556 graphics [ fill "#000000" ] ] 
	edge [ source 555 target 560 graphics [ fill "#000000" ] ] 
	edge [ source 556 target 557 graphics [ fill "#000000" ] ] 
	edge [ source 556 target 559 graphics [ fill "#000000" ] ] 
	edge [ source 557 target 558 graphics [ fill "#000000" ] ] 
	edge [ source 557 target 559 graphics [ fill "#000000" ] ] 
	edge [ source 558 target 559 graphics [ fill "#0000ff" ] ] 
	edge [ source 559 target 566 graphics [ fill "#0000ff" ] ] 
	edge [ source 560 target 561 graphics [ fill "#000000" ] ] 
	edge [ source 560 target 562 graphics [ fill "#000000" ] ] 
	edge [ source 561 target 563 graphics [ fill "#0000ff" ] ] 
	edge [ source 562 target 563 graphics [ fill "#0000ff" ] ] 
	edge [ source 563 target 564 graphics [ fill "#000000" ] ] 
	edge [ source 563 target 565 graphics [ fill "#000000" ] ] 
	edge [ source 564 target 565 graphics [ fill "#0000ff" ] ] 
	edge [ source 565 target 566 graphics [ fill "#0000ff" ] ] 
	edge [ source 566 target 548 graphics [ fill "#000000" ] ] 
	node [ id 587 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
_5 = left-&gt;r;
if (_5 != 0B)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 588 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
left = left-&gt;r;
" ]



# function number 26
	node [ id 589 graphics [ fill "#ffffff" ] label "rhp_sp_remove ()
ENTRY" ]

	node [ id 590 graphics [ fill "#ffffff" ] label "rhp_sp_remove ()
EXIT" ]

	node [ id 591 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
node = 0B;
left = 0B;
right = 0B;
if (sp == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 592 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 19&gt;; [INV]
" ]

	node [ id 593 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_1 = sp-&gt;root;
if (_1 == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 594 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 19&gt;; [INV]
" ]

	node [ id 595 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
spn = rhp_sp_lookup (sp, key);
if (spn == 0B)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 596 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
key.112_2 = (void *) key;
printf (&quot;%s(): key %p not found\n&quot;, &amp;__FUNCTION__, key.112_2);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 19&gt;; [INV]
" ]

	node [ id 597 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
node = sp-&gt;root;
_3 = sp-&gt;root;
left = _3-&gt;l;
_4 = sp-&gt;root;
right = _4-&gt;r;
if (left != 0B)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 598 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
sp-&gt;root = left;
if (right != 0B)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 599 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 600 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
left-&gt;r = right;
goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 601 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
sp-&gt;root = right;
" ]

	node [ id 602 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
_6 = sp-&gt;delval;
if (_6 != 0)
  goto &lt;bb 16&gt;; [INV]
else
  goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 603 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
_7 = node-&gt;value;
if (_7 != 0)
  goto &lt;bb 17&gt;; [INV]
else
  goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 604 graphics [ fill "#d3d3d3" ] label "&lt;bb 17&gt;:
_8 = node-&gt;value;
_9 = (void *) _8;
rhp_free (_9, &amp;__FUNCTION__, 1857);
node-&gt;value = 0;
" ]

	node [ id 605 graphics [ fill "#d3d3d3" ] label "&lt;bb 18&gt;:
node-&gt;l = 0B;
node-&gt;r = 0B;
rhp_free (node, &amp;__FUNCTION__, 1866);
" ]

	node [ id 606 graphics [ fill "#d3d3d3" ] label "&lt;bb 19&gt;:
&lt;L18&gt;:
return;
" ]

	edge [ source 589 target 591 graphics [ fill "#0000ff" ] ] 
	edge [ source 591 target 592 graphics [ fill "#000000" ] ] 
	edge [ source 591 target 593 graphics [ fill "#000000" ] ] 
	edge [ source 592 target 606 graphics [ fill "#0000ff" ] ] 
	edge [ source 593 target 594 graphics [ fill "#000000" ] ] 
	edge [ source 593 target 595 graphics [ fill "#000000" ] ] 
	edge [ source 594 target 606 graphics [ fill "#0000ff" ] ] 
	edge [ source 595 target 596 graphics [ fill "#000000" ] ] 
	edge [ source 595 target 597 graphics [ fill "#000000" ] ] 
	edge [ source 596 target 606 graphics [ fill "#0000ff" ] ] 
	edge [ source 597 target 598 graphics [ fill "#000000" ] ] 
	edge [ source 597 target 601 graphics [ fill "#000000" ] ] 
	edge [ source 598 target 599 graphics [ fill "#000000" ] ] 
	edge [ source 598 target 602 graphics [ fill "#000000" ] ] 
	edge [ source 599 target 587 graphics [ fill "#0000ff" ] ] 
	edge [ source 588 target 587 graphics [ fill "#0000ff" ] ] 
	edge [ source 587 target 588 graphics [ fill "#000000" ] ] 
	edge [ source 587 target 600 graphics [ fill "#000000" ] ] 
	edge [ source 600 target 602 graphics [ fill "#0000ff" ] ] 
	edge [ source 601 target 602 graphics [ fill "#0000ff" ] ] 
	edge [ source 602 target 603 graphics [ fill "#000000" ] ] 
	edge [ source 602 target 605 graphics [ fill "#000000" ] ] 
	edge [ source 603 target 604 graphics [ fill "#000000" ] ] 
	edge [ source 603 target 605 graphics [ fill "#000000" ] ] 
	edge [ source 604 target 605 graphics [ fill "#0000ff" ] ] 
	edge [ source 605 target 606 graphics [ fill "#0000ff" ] ] 
	edge [ source 606 target 590 graphics [ fill "#000000" ] ] 
	node [ id 627 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
if (spn != 0B)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 628 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
_2 = spn-&gt;key;
spn2 = rhp_sp_next (sp, _2);
_3 = spn-&gt;key;
rhp_sp_remove (sp, _3);
spn = spn2;
" ]



# function number 27
	node [ id 629 graphics [ fill "#ffffff" ] label "rhp_sp_delete ()
ENTRY" ]

	node [ id 630 graphics [ fill "#ffffff" ] label "rhp_sp_delete ()
EXIT" ]

	node [ id 631 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spp = 0B;
spn = 0B;
spn2 = 0B;
if (sp == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 632 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
D.4593 = 0B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 633 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
spp = sp;
_1 = spp-&gt;root;
if (_1 == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 634 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
spp = rhp_free (spp, &amp;__FUNCTION__, 1891);
D.4593 = 0B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 635 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
spn = rhp_sp_min (sp);
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 636 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
spp = sp;
spp = rhp_free (spp, &amp;__FUNCTION__, 1909);
D.4593 = 0B;
" ]

	node [ id 637 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
&lt;L7&gt;:
return D.4593;
" ]

	edge [ source 629 target 631 graphics [ fill "#0000ff" ] ] 
	edge [ source 631 target 632 graphics [ fill "#000000" ] ] 
	edge [ source 631 target 633 graphics [ fill "#000000" ] ] 
	edge [ source 632 target 637 graphics [ fill "#0000ff" ] ] 
	edge [ source 633 target 634 graphics [ fill "#000000" ] ] 
	edge [ source 633 target 635 graphics [ fill "#000000" ] ] 
	edge [ source 634 target 637 graphics [ fill "#0000ff" ] ] 
	edge [ source 635 target 627 graphics [ fill "#0000ff" ] ] 
	edge [ source 628 target 627 graphics [ fill "#0000ff" ] ] 
	edge [ source 627 target 628 graphics [ fill "#000000" ] ] 
	edge [ source 627 target 636 graphics [ fill "#000000" ] ] 
	edge [ source 636 target 637 graphics [ fill "#0000ff" ] ] 
	edge [ source 637 target 630 graphics [ fill "#000000" ] ] 
	node [ id 649 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
_5 = n-&gt;l;
if (_5 != 0B)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 650 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
n = n-&gt;l;
" ]



# function number 28
	node [ id 651 graphics [ fill "#ffffff" ] label "rhp_sp_next ()
ENTRY" ]

	node [ id 652 graphics [ fill "#ffffff" ] label "rhp_sp_next ()
EXIT" ]

	node [ id 653 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
n = 0B;
if (sp == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 654 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
D.4599 = 0B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 655 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_1 = sp-&gt;root;
if (_1 == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 656 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4599 = 0B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 657 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_sp_sp (sp, key);
_2 = sp-&gt;root;
_3 = _2-&gt;key;
if (key &lt; _3)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 658 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
D.4599 = sp-&gt;root;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 659 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
_4 = sp-&gt;root;
n = _4-&gt;r;
if (n != 0B)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 660 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 661 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
D.4599 = n;
" ]

	node [ id 662 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
&lt;L11&gt;:
return D.4599;
" ]

	edge [ source 651 target 653 graphics [ fill "#0000ff" ] ] 
	edge [ source 653 target 654 graphics [ fill "#000000" ] ] 
	edge [ source 653 target 655 graphics [ fill "#000000" ] ] 
	edge [ source 654 target 662 graphics [ fill "#0000ff" ] ] 
	edge [ source 655 target 656 graphics [ fill "#000000" ] ] 
	edge [ source 655 target 657 graphics [ fill "#000000" ] ] 
	edge [ source 656 target 662 graphics [ fill "#0000ff" ] ] 
	edge [ source 657 target 658 graphics [ fill "#000000" ] ] 
	edge [ source 657 target 659 graphics [ fill "#000000" ] ] 
	edge [ source 658 target 662 graphics [ fill "#0000ff" ] ] 
	edge [ source 659 target 660 graphics [ fill "#000000" ] ] 
	edge [ source 659 target 661 graphics [ fill "#000000" ] ] 
	edge [ source 660 target 649 graphics [ fill "#0000ff" ] ] 
	edge [ source 650 target 649 graphics [ fill "#0000ff" ] ] 
	edge [ source 649 target 650 graphics [ fill "#000000" ] ] 
	edge [ source 649 target 661 graphics [ fill "#000000" ] ] 
	edge [ source 661 target 662 graphics [ fill "#0000ff" ] ] 
	edge [ source 662 target 652 graphics [ fill "#000000" ] ] 


# function number 29
	node [ id 677 graphics [ fill "#ffffff" ] label "rhp_sp_lookup ()
ENTRY" ]

	node [ id 678 graphics [ fill "#ffffff" ] label "rhp_sp_lookup ()
EXIT" ]

	node [ id 679 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
s = &quot;not-found&quot;;
if (sp == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 680 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
D.4609 = 0B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 681 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_1 = sp-&gt;root;
if (_1 == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 682 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4609 = 0B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 683 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_2 = sp-&gt;root;
_3 = _2-&gt;key;
if (key == _3)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 684 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
D.4609 = sp-&gt;root;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 685 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
rhp_sp_sp (sp, key);
_4 = sp-&gt;root;
if (_4 == 0B)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 686 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
D.4609 = 0B;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 687 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
_5 = sp-&gt;root;
_6 = _5-&gt;key;
if (key == _6)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 688 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
s = &quot;found&quot;;
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 689 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
s = &quot;not-found&quot;;
" ]

	node [ id 690 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
rhp_verbose.113_7 = rhp_verbose;
if (rhp_verbose.113_7 != 0)
  goto &lt;bb 14&gt;; [INV]
else
  goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 691 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
key.114_8 = (long unsigned int) key;
_9 = sp-&gt;root;
_10 = _9-&gt;key;
_11 = (long unsigned int) _10;
rhp_log (&quot;%s(): %s in sp (%p) at %li when search for %li\n&quot;, &amp;__FUNCTION__, s, sp, _11, key.114_8);
" ]

	node [ id 692 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
_12 = sp-&gt;root;
_13 = _12-&gt;key;
if (key == _13)
  goto &lt;bb 16&gt;; [INV]
else
  goto &lt;bb 17&gt;; [INV]
" ]

	node [ id 693 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
D.4609 = sp-&gt;root;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 694 graphics [ fill "#d3d3d3" ] label "&lt;bb 17&gt;:
D.4609 = 0B;
" ]

	node [ id 695 graphics [ fill "#d3d3d3" ] label "&lt;bb 18&gt;:
&lt;L15&gt;:
return D.4609;
" ]

	edge [ source 677 target 679 graphics [ fill "#0000ff" ] ] 
	edge [ source 679 target 680 graphics [ fill "#000000" ] ] 
	edge [ source 679 target 681 graphics [ fill "#000000" ] ] 
	edge [ source 680 target 695 graphics [ fill "#0000ff" ] ] 
	edge [ source 681 target 682 graphics [ fill "#000000" ] ] 
	edge [ source 681 target 683 graphics [ fill "#000000" ] ] 
	edge [ source 682 target 695 graphics [ fill "#0000ff" ] ] 
	edge [ source 683 target 684 graphics [ fill "#000000" ] ] 
	edge [ source 683 target 685 graphics [ fill "#000000" ] ] 
	edge [ source 684 target 695 graphics [ fill "#0000ff" ] ] 
	edge [ source 685 target 686 graphics [ fill "#000000" ] ] 
	edge [ source 685 target 687 graphics [ fill "#000000" ] ] 
	edge [ source 686 target 695 graphics [ fill "#0000ff" ] ] 
	edge [ source 687 target 688 graphics [ fill "#000000" ] ] 
	edge [ source 687 target 689 graphics [ fill "#000000" ] ] 
	edge [ source 688 target 690 graphics [ fill "#0000ff" ] ] 
	edge [ source 689 target 690 graphics [ fill "#0000ff" ] ] 
	edge [ source 690 target 691 graphics [ fill "#000000" ] ] 
	edge [ source 690 target 692 graphics [ fill "#000000" ] ] 
	edge [ source 691 target 692 graphics [ fill "#0000ff" ] ] 
	edge [ source 692 target 693 graphics [ fill "#000000" ] ] 
	edge [ source 692 target 694 graphics [ fill "#000000" ] ] 
	edge [ source 693 target 695 graphics [ fill "#0000ff" ] ] 
	edge [ source 694 target 695 graphics [ fill "#0000ff" ] ] 
	edge [ source 695 target 678 graphics [ fill "#000000" ] ] 
	node [ id 715 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
label:
n = sp-&gt;root;
if (n == 0B)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 716 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
rhp_verbose.115_2 = rhp_verbose;
if (rhp_verbose.115_2 != 0)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 717 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
key.116_3 = (long unsigned int) key;
_4 = n-&gt;key;
_5 = (long unsigned int) _4;
rhp_log (&quot;%s(): at %li when search for %li\n&quot;, &amp;__FUNCTION__, _5, key.116_3);
" ]

	node [ id 718 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
_6 = n-&gt;key;
if (key == _6)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 719 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
_7 = n-&gt;key;
if (key &lt; _7)
  goto &lt;bb 13&gt;; [INV]
else
  goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 720 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
c = n-&gt;l;
goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 721 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
c = n-&gt;r;
" ]

	node [ id 722 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
if (c == 0B)
  goto &lt;bb 16&gt;; [INV]
else
  goto &lt;bb 19&gt;; [INV]
" ]

	node [ id 723 graphics [ fill "#d3d3d3" ] label "&lt;bb 19&gt;:
_13 = c-&gt;key;
if (key == _13)
  goto &lt;bb 24&gt;; [INV]
else
  goto &lt;bb 20&gt;; [INV]
" ]

	node [ id 724 graphics [ fill "#d3d3d3" ] label "&lt;bb 20&gt;:
_14 = c-&gt;key;
if (key &lt; _14)
  goto &lt;bb 21&gt;; [INV]
else
  goto &lt;bb 22&gt;; [INV]
" ]

	node [ id 725 graphics [ fill "#d3d3d3" ] label "&lt;bb 21&gt;:
_15 = c-&gt;l;
if (_15 == 0B)
  goto &lt;bb 24&gt;; [INV]
else
  goto &lt;bb 22&gt;; [INV]
" ]

	node [ id 726 graphics [ fill "#d3d3d3" ] label "&lt;bb 22&gt;:
_16 = c-&gt;key;
if (key &gt; _16)
  goto &lt;bb 23&gt;; [INV]
else
  goto &lt;bb 28&gt;; [INV]
" ]

	node [ id 727 graphics [ fill "#d3d3d3" ] label "&lt;bb 23&gt;:
_17 = c-&gt;r;
if (_17 == 0B)
  goto &lt;bb 24&gt;; [INV]
else
  goto &lt;bb 28&gt;; [INV]
" ]

	node [ id 728 graphics [ fill "#d3d3d3" ] label "&lt;bb 28&gt;:
_21 = n-&gt;key;
if (key &lt; _21)
  goto &lt;bb 29&gt;; [INV]
else
  goto &lt;bb 31&gt;; [INV]
" ]

	node [ id 729 graphics [ fill "#d3d3d3" ] label "&lt;bb 29&gt;:
_22 = c-&gt;key;
if (key &lt; _22)
  goto &lt;bb 30&gt;; [INV]
else
  goto &lt;bb 31&gt;; [INV]
" ]

	node [ id 730 graphics [ fill "#d3d3d3" ] label "&lt;bb 31&gt;:
_27 = n-&gt;key;
if (key &gt; _27)
  goto &lt;bb 32&gt;; [INV]
else
  goto &lt;bb 34&gt;; [INV]
" ]

	node [ id 731 graphics [ fill "#d3d3d3" ] label "&lt;bb 30&gt;:
_23 = c-&gt;l;
_24 = &amp;n-&gt;l;
rhp_sp_sp_rl (_24, c, _23);
_25 = n-&gt;l;
_26 = &amp;sp-&gt;root;
rhp_sp_sp_rl (_26, n, _25);
goto &lt;bb 40&gt;; [INV]
" ]

	node [ id 732 graphics [ fill "#d3d3d3" ] label "&lt;bb 32&gt;:
_28 = c-&gt;key;
if (key &gt; _28)
  goto &lt;bb 33&gt;; [INV]
else
  goto &lt;bb 34&gt;; [INV]
" ]

	node [ id 733 graphics [ fill "#d3d3d3" ] label "&lt;bb 34&gt;:
_33 = n-&gt;key;
if (key &lt; _33)
  goto &lt;bb 35&gt;; [INV]
else
  goto &lt;bb 37&gt;; [INV]
" ]

	node [ id 734 graphics [ fill "#d3d3d3" ] label "&lt;bb 40&gt;:
// predicted unlikely by goto predictor.
goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 735 graphics [ fill "#d3d3d3" ] label "&lt;bb 33&gt;:
_29 = c-&gt;r;
_30 = &amp;n-&gt;r;
rhp_sp_sp_rr (_30, c, _29);
_31 = n-&gt;r;
_32 = &amp;sp-&gt;root;
rhp_sp_sp_rr (_32, n, _31);
goto &lt;bb 40&gt;; [INV]
" ]

	node [ id 736 graphics [ fill "#d3d3d3" ] label "&lt;bb 35&gt;:
_34 = c-&gt;key;
if (key &gt; _34)
  goto &lt;bb 36&gt;; [INV]
else
  goto &lt;bb 37&gt;; [INV]
" ]

	node [ id 737 graphics [ fill "#d3d3d3" ] label "&lt;bb 37&gt;:
_39 = n-&gt;key;
if (key &gt; _39)
  goto &lt;bb 38&gt;; [INV]
else
  goto &lt;bb 40&gt;; [INV]
" ]

	node [ id 738 graphics [ fill "#d3d3d3" ] label "&lt;bb 36&gt;:
_35 = c-&gt;r;
_36 = &amp;n-&gt;l;
rhp_sp_sp_rr (_36, c, _35);
_37 = n-&gt;l;
_38 = &amp;sp-&gt;root;
rhp_sp_sp_rl (_38, n, _37);
goto &lt;bb 40&gt;; [INV]
" ]

	node [ id 739 graphics [ fill "#d3d3d3" ] label "&lt;bb 38&gt;:
_40 = c-&gt;key;
if (key &lt; _40)
  goto &lt;bb 39&gt;; [INV]
else
  goto &lt;bb 40&gt;; [INV]
" ]

	node [ id 740 graphics [ fill "#d3d3d3" ] label "&lt;bb 39&gt;:
_41 = c-&gt;l;
_42 = &amp;n-&gt;r;
rhp_sp_sp_rl (_42, c, _41);
_43 = n-&gt;r;
_44 = &amp;sp-&gt;root;
rhp_sp_sp_rr (_44, n, _43);
" ]



# function number 32
	node [ id 741 graphics [ fill "#ffffff" ] label "rhp_sp_sp ()
ENTRY" ]

	node [ id 742 graphics [ fill "#ffffff" ] label "rhp_sp_sp ()
EXIT" ]

	node [ id 743 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
n = 0B;
c = 0B;
if (sp == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 744 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 41&gt;; [INV]
" ]

	node [ id 745 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_1 = sp-&gt;root;
if (_1 == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 746 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 41&gt;; [INV]
" ]

	node [ id 747 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 41&gt;; [INV]
" ]

	node [ id 748 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 41&gt;; [INV]
" ]

	node [ id 749 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
rhp_verbose.117_8 = rhp_verbose;
if (rhp_verbose.117_8 != 0)
  goto &lt;bb 17&gt;; [INV]
else
  goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 750 graphics [ fill "#d3d3d3" ] label "&lt;bb 17&gt;:
key.118_9 = (long unsigned int) key;
_10 = sp-&gt;root;
_11 = _10-&gt;key;
_12 = (long unsigned int) _11;
rhp_log (&quot;%s(): c=&lt;nil&gt; at %li when search for %li\n&quot;, &amp;__FUNCTION__, _12, key.118_9);
" ]

	node [ id 751 graphics [ fill "#d3d3d3" ] label "&lt;bb 18&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 41&gt;; [INV]
" ]

	node [ id 752 graphics [ fill "#d3d3d3" ] label "&lt;bb 24&gt;:
_18 = n-&gt;key;
if (key &lt; _18)
  goto &lt;bb 25&gt;; [INV]
else
  goto &lt;bb 26&gt;; [INV]
" ]

	node [ id 753 graphics [ fill "#d3d3d3" ] label "&lt;bb 25&gt;:
_19 = &amp;sp-&gt;root;
rhp_sp_sp_rl (_19, n, c);
goto &lt;bb 27&gt;; [INV]
" ]

	node [ id 754 graphics [ fill "#d3d3d3" ] label "&lt;bb 26&gt;:
_20 = &amp;sp-&gt;root;
rhp_sp_sp_rr (_20, n, c);
" ]

	node [ id 755 graphics [ fill "#d3d3d3" ] label "&lt;bb 27&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 41&gt;; [INV]
" ]

	node [ id 756 graphics [ fill "#d3d3d3" ] label "&lt;bb 41&gt;:
&lt;L44&gt;:
return;
" ]

	edge [ source 741 target 743 graphics [ fill "#0000ff" ] ] 
	edge [ source 743 target 744 graphics [ fill "#000000" ] ] 
	edge [ source 743 target 745 graphics [ fill "#000000" ] ] 
	edge [ source 744 target 756 graphics [ fill "#0000ff" ] ] 
	edge [ source 745 target 746 graphics [ fill "#000000" ] ] 
	edge [ source 745 target 715 graphics [ fill "#000000" ] ] 
	edge [ source 746 target 756 graphics [ fill "#0000ff" ] ] 
	edge [ source 715 target 747 graphics [ fill "#000000" ] ] 
	edge [ source 715 target 716 graphics [ fill "#000000" ] ] 
	edge [ source 747 target 756 graphics [ fill "#0000ff" ] ] 
	edge [ source 716 target 717 graphics [ fill "#000000" ] ] 
	edge [ source 716 target 718 graphics [ fill "#000000" ] ] 
	edge [ source 717 target 718 graphics [ fill "#0000ff" ] ] 
	edge [ source 718 target 748 graphics [ fill "#000000" ] ] 
	edge [ source 718 target 719 graphics [ fill "#000000" ] ] 
	edge [ source 748 target 756 graphics [ fill "#0000ff" ] ] 
	edge [ source 719 target 720 graphics [ fill "#000000" ] ] 
	edge [ source 719 target 721 graphics [ fill "#000000" ] ] 
	edge [ source 720 target 722 graphics [ fill "#0000ff" ] ] 
	edge [ source 721 target 722 graphics [ fill "#0000ff" ] ] 
	edge [ source 722 target 749 graphics [ fill "#000000" ] ] 
	edge [ source 722 target 723 graphics [ fill "#000000" ] ] 
	edge [ source 749 target 750 graphics [ fill "#000000" ] ] 
	edge [ source 749 target 751 graphics [ fill "#000000" ] ] 
	edge [ source 750 target 751 graphics [ fill "#0000ff" ] ] 
	edge [ source 751 target 756 graphics [ fill "#0000ff" ] ] 
	edge [ source 723 target 752 graphics [ fill "#000000" ] ] 
	edge [ source 723 target 724 graphics [ fill "#000000" ] ] 
	edge [ source 724 target 725 graphics [ fill "#000000" ] ] 
	edge [ source 724 target 726 graphics [ fill "#000000" ] ] 
	edge [ source 725 target 752 graphics [ fill "#000000" ] ] 
	edge [ source 725 target 726 graphics [ fill "#000000" ] ] 
	edge [ source 726 target 727 graphics [ fill "#000000" ] ] 
	edge [ source 726 target 728 graphics [ fill "#000000" ] ] 
	edge [ source 727 target 752 graphics [ fill "#000000" ] ] 
	edge [ source 727 target 728 graphics [ fill "#000000" ] ] 
	edge [ source 752 target 753 graphics [ fill "#000000" ] ] 
	edge [ source 752 target 754 graphics [ fill "#000000" ] ] 
	edge [ source 753 target 755 graphics [ fill "#0000ff" ] ] 
	edge [ source 754 target 755 graphics [ fill "#0000ff" ] ] 
	edge [ source 755 target 756 graphics [ fill "#0000ff" ] ] 
	edge [ source 728 target 729 graphics [ fill "#000000" ] ] 
	edge [ source 728 target 730 graphics [ fill "#000000" ] ] 
	edge [ source 729 target 731 graphics [ fill "#000000" ] ] 
	edge [ source 729 target 730 graphics [ fill "#000000" ] ] 
	edge [ source 731 target 734 graphics [ fill "#0000ff" ] ] 
	edge [ source 730 target 732 graphics [ fill "#000000" ] ] 
	edge [ source 730 target 733 graphics [ fill "#000000" ] ] 
	edge [ source 732 target 735 graphics [ fill "#000000" ] ] 
	edge [ source 732 target 733 graphics [ fill "#000000" ] ] 
	edge [ source 735 target 734 graphics [ fill "#0000ff" ] ] 
	edge [ source 733 target 736 graphics [ fill "#000000" ] ] 
	edge [ source 733 target 737 graphics [ fill "#000000" ] ] 
	edge [ source 736 target 738 graphics [ fill "#000000" ] ] 
	edge [ source 736 target 737 graphics [ fill "#000000" ] ] 
	edge [ source 738 target 734 graphics [ fill "#0000ff" ] ] 
	edge [ source 737 target 739 graphics [ fill "#000000" ] ] 
	edge [ source 737 target 734 graphics [ fill "#000000" ] ] 
	edge [ source 739 target 740 graphics [ fill "#000000" ] ] 
	edge [ source 739 target 734 graphics [ fill "#000000" ] ] 
	edge [ source 740 target 734 graphics [ fill "#0000ff" ] ] 
	edge [ source 734 target 715 graphics [ fill "#0000ff" ] ] 
	edge [ source 756 target 742 graphics [ fill "#000000" ] ] 


# function number 30
	node [ id 799 graphics [ fill "#ffffff" ] label "rhp_sp_sp_rl ()
ENTRY" ]

	node [ id 800 graphics [ fill "#ffffff" ] label "rhp_sp_sp_rl ()
EXIT" ]

	node [ id 801 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
tmp = 0B;
tmp = n-&gt;r;
n-&gt;r = p;
p-&gt;l = tmp;
*pp = n;
" ]

	node [ id 802 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
&lt;L0&gt;:
return;
" ]

	edge [ source 799 target 801 graphics [ fill "#0000ff" ] ] 
	edge [ source 801 target 802 graphics [ fill "#0000ff" ] ] 
	edge [ source 802 target 800 graphics [ fill "#000000" ] ] 


# function number 31
	node [ id 807 graphics [ fill "#ffffff" ] label "rhp_sp_sp_rr ()
ENTRY" ]

	node [ id 808 graphics [ fill "#ffffff" ] label "rhp_sp_sp_rr ()
EXIT" ]

	node [ id 809 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
tmp = 0B;
tmp = n-&gt;l;
n-&gt;l = p;
p-&gt;r = tmp;
*pp = n;
" ]

	node [ id 810 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
&lt;L0&gt;:
return;
" ]

	edge [ source 807 target 809 graphics [ fill "#0000ff" ] ] 
	edge [ source 809 target 810 graphics [ fill "#0000ff" ] ] 
	edge [ source 810 target 808 graphics [ fill "#000000" ] ] 
	node [ id 815 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_2 = *p;
if (_2 != 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 816 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
_1 = *p;
if (_1 == 33)
  goto &lt;bb 4&gt;; [INV]
else
  goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 817 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
q = p;
" ]

	node [ id 818 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
p = p + 1;
" ]



# function number 33
	node [ id 819 graphics [ fill "#ffffff" ] label "rhp_log ()
ENTRY" ]

	node [ id 820 graphics [ fill "#ffffff" ] label "rhp_log ()
EXIT" ]

	node [ id 821 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
p = 0B;
q = 0B;
p = format;
q = 0B;
goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 822 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
if (q != 0B)
  goto &lt;bb 8&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 823 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
__builtin_va_start (&amp;ap, 0);
stderr.119_3 = stderr;
vfprintf (stderr.119_3, format, &amp;ap);
__builtin_va_end (&amp;ap);
stderr.120_4 = stderr;
fflush (stderr.120_4);
" ]

	node [ id 824 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_dolog.121_5 = rhp_dolog;
if (rhp_dolog.121_5 == 0)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 825 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 826 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
rhp_logstream.122_6 = rhp_logstream;
if (rhp_logstream.122_6 == 0B)
  goto &lt;bb 12&gt;; [INV]
else
  goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 827 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 828 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
__builtin_va_start (&amp;ap, 0);
rhp_logstream.123_7 = rhp_logstream;
vfprintf (rhp_logstream.123_7, format, &amp;ap);
__builtin_va_end (&amp;ap);
rhp_logstream.124_8 = rhp_logstream;
fflush (rhp_logstream.124_8);
" ]

	node [ id 829 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
ap = {CLOBBER};
" ]

	node [ id 830 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
&lt;L12&gt;:
return;
" ]

	edge [ source 819 target 821 graphics [ fill "#0000ff" ] ] 
	edge [ source 821 target 815 graphics [ fill "#0000ff" ] ] 
	edge [ source 816 target 817 graphics [ fill "#000000" ] ] 
	edge [ source 816 target 818 graphics [ fill "#000000" ] ] 
	edge [ source 817 target 818 graphics [ fill "#0000ff" ] ] 
	edge [ source 818 target 815 graphics [ fill "#0000ff" ] ] 
	edge [ source 815 target 816 graphics [ fill "#000000" ] ] 
	edge [ source 815 target 822 graphics [ fill "#000000" ] ] 
	edge [ source 822 target 823 graphics [ fill "#000000" ] ] 
	edge [ source 822 target 824 graphics [ fill "#000000" ] ] 
	edge [ source 823 target 824 graphics [ fill "#0000ff" ] ] 
	edge [ source 824 target 825 graphics [ fill "#000000" ] ] 
	edge [ source 824 target 826 graphics [ fill "#000000" ] ] 
	edge [ source 825 target 829 graphics [ fill "#0000ff" ] ] 
	edge [ source 826 target 827 graphics [ fill "#000000" ] ] 
	edge [ source 826 target 828 graphics [ fill "#000000" ] ] 
	edge [ source 827 target 829 graphics [ fill "#0000ff" ] ] 
	edge [ source 828 target 829 graphics [ fill "#0000ff" ] ] 
	edge [ source 829 target 830 graphics [ fill "#0000ff" ] ] 
	edge [ source 830 target 820 graphics [ fill "#000000" ] ] 
	node [ id 847 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
rhp_nlevels.131_24 = rhp_nlevels;
if (level &lt; rhp_nlevels.131_24)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 848 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_best_crossings_order.128_6 = rhp_best_crossings_order;
_7 = rhp_best_crossings_order.128_6-&gt;node_ptr_on_layer;
_8 = (long unsigned int) level;
_9 = _8 * 8;
_10 = _7 + _9;
_11 = *_10;
if (_11 != 0B)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 849 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_best_crossings_order.129_12 = rhp_best_crossings_order;
_13 = rhp_best_crossings_order.129_12-&gt;node_ptr_on_layer;
_14 = (long unsigned int) level;
_15 = _14 * 8;
_16 = _13 + _15;
_17 = *_16;
rhp_best_crossings_order.130_18 = rhp_best_crossings_order;
_19 = rhp_best_crossings_order.130_18-&gt;node_ptr_on_layer;
_20 = (long unsigned int) level;
_21 = _20 * 8;
_22 = _19 + _21;
_23 = rhp_free (_17, &amp;__FUNCTION__, 2195);
*_22 = _23;
" ]

	node [ id 850 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
level = level + 1;
" ]



# function number 34
	node [ id 851 graphics [ fill "#ffffff" ] label "rhp_empty_best_crossings_order ()
ENTRY" ]

	node [ id 852 graphics [ fill "#ffffff" ] label "rhp_empty_best_crossings_order ()
EXIT" ]

	node [ id 853 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
level = 0;
rhp_log (&quot;%s():\n&quot;, &amp;__FUNCTION__);
rhp_best_crossings_order.125_1 = rhp_best_crossings_order;
if (rhp_best_crossings_order.125_1 == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 854 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): no data\n&quot;, &amp;__FUNCTION__);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 855 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_best_crossings_order.126_2 = rhp_best_crossings_order;
_3 = rhp_best_crossings_order.126_2-&gt;num_nodes_on_layer;
rhp_best_crossings_order.127_4 = rhp_best_crossings_order;
_5 = rhp_free (_3, &amp;__FUNCTION__, 2187);
rhp_best_crossings_order.127_4-&gt;num_nodes_on_layer = _5;
level = 0;
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 856 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_best_crossings_order.132_25 = rhp_best_crossings_order;
_26 = rhp_best_crossings_order.132_25-&gt;node_ptr_on_layer;
if (_26 != 0B)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 857 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
rhp_best_crossings_order.133_27 = rhp_best_crossings_order;
_28 = rhp_best_crossings_order.133_27-&gt;node_ptr_on_layer;
rhp_best_crossings_order.134_29 = rhp_best_crossings_order;
_30 = rhp_free (_28, &amp;__FUNCTION__, 2203);
rhp_best_crossings_order.134_29-&gt;node_ptr_on_layer = _30;
" ]

	node [ id 858 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
" ]

	node [ id 859 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
&lt;L9&gt;:
return;
" ]

	edge [ source 851 target 853 graphics [ fill "#0000ff" ] ] 
	edge [ source 853 target 854 graphics [ fill "#000000" ] ] 
	edge [ source 853 target 855 graphics [ fill "#000000" ] ] 
	edge [ source 854 target 859 graphics [ fill "#0000ff" ] ] 
	edge [ source 855 target 847 graphics [ fill "#0000ff" ] ] 
	edge [ source 848 target 849 graphics [ fill "#000000" ] ] 
	edge [ source 848 target 850 graphics [ fill "#000000" ] ] 
	edge [ source 849 target 850 graphics [ fill "#0000ff" ] ] 
	edge [ source 850 target 847 graphics [ fill "#0000ff" ] ] 
	edge [ source 847 target 848 graphics [ fill "#000000" ] ] 
	edge [ source 847 target 856 graphics [ fill "#000000" ] ] 
	edge [ source 856 target 857 graphics [ fill "#000000" ] ] 
	edge [ source 856 target 858 graphics [ fill "#000000" ] ] 
	edge [ source 857 target 858 graphics [ fill "#0000ff" ] ] 
	edge [ source 858 target 859 graphics [ fill "#0000ff" ] ] 
	edge [ source 859 target 852 graphics [ fill "#000000" ] ] 
	node [ id 873 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
if (spn != 0B)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 874 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
_12 = spn-&gt;value;
_13 = (void *) _12;
rhp_free (_13, &amp;__FUNCTION__, 2245);
spn-&gt;value = 0;
_14 = spn-&gt;key;
rhp_sp_master_node_list_sorted.138_15 = rhp_sp_master_node_list_sorted;
spn = rhp_sp_next (rhp_sp_master_node_list_sorted.138_15, _14);
" ]

	node [ id 875 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
if (spn != 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 876 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
_2 = spn-&gt;value;
nd = (struct rhpnode *) _2;
_3 = nd-&gt;up_edges;
if (_3 != 0B)
  goto &lt;bb 4&gt;; [INV]
else
  goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 877 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_4 = nd-&gt;up_edges;
_5 = rhp_free (_4, &amp;__FUNCTION__, 2227);
nd-&gt;up_edges = _5;
nd-&gt;up_degree = 0;
" ]

	node [ id 878 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
_6 = nd-&gt;down_edges;
if (_6 != 0B)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 879 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_7 = nd-&gt;down_edges;
_8 = rhp_free (_7, &amp;__FUNCTION__, 2233);
nd-&gt;down_edges = _8;
nd-&gt;down_degree = 0;
" ]

	node [ id 880 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
_9 = spn-&gt;key;
rhp_sp_master_node_list.136_10 = rhp_sp_master_node_list;
spn = rhp_sp_next (rhp_sp_master_node_list.136_10, _9);
" ]



# function number 35
	node [ id 881 graphics [ fill "#ffffff" ] label "rhp_empty_sp_master_node_list ()
ENTRY" ]

	node [ id 882 graphics [ fill "#ffffff" ] label "rhp_empty_sp_master_node_list ()
EXIT" ]

	node [ id 883 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
nd = 0B;
rhp_log (&quot;%s():\n&quot;, &amp;__FUNCTION__);
rhp_sp_master_node_list.135_1 = rhp_sp_master_node_list;
spn = rhp_sp_min (rhp_sp_master_node_list.135_1);
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 884 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_sp_master_node_list_sorted.137_11 = rhp_sp_master_node_list_sorted;
spn = rhp_sp_min (rhp_sp_master_node_list_sorted.137_11);
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 885 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
" ]

	node [ id 886 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
&lt;L10&gt;:
return;
" ]

	edge [ source 881 target 883 graphics [ fill "#0000ff" ] ] 
	edge [ source 883 target 875 graphics [ fill "#0000ff" ] ] 
	edge [ source 876 target 877 graphics [ fill "#000000" ] ] 
	edge [ source 876 target 878 graphics [ fill "#000000" ] ] 
	edge [ source 877 target 878 graphics [ fill "#0000ff" ] ] 
	edge [ source 878 target 879 graphics [ fill "#000000" ] ] 
	edge [ source 878 target 880 graphics [ fill "#000000" ] ] 
	edge [ source 879 target 880 graphics [ fill "#0000ff" ] ] 
	edge [ source 880 target 875 graphics [ fill "#0000ff" ] ] 
	edge [ source 875 target 876 graphics [ fill "#000000" ] ] 
	edge [ source 875 target 884 graphics [ fill "#000000" ] ] 
	edge [ source 884 target 873 graphics [ fill "#0000ff" ] ] 
	edge [ source 874 target 873 graphics [ fill "#0000ff" ] ] 
	edge [ source 873 target 874 graphics [ fill "#000000" ] ] 
	edge [ source 873 target 885 graphics [ fill "#000000" ] ] 
	edge [ source 885 target 886 graphics [ fill "#0000ff" ] ] 
	edge [ source 886 target 882 graphics [ fill "#000000" ] ] 


# function number 36
	node [ id 901 graphics [ fill "#ffffff" ] label "rhp_empty_sp_master_edge_list ()
ENTRY" ]

	node [ id 902 graphics [ fill "#ffffff" ] label "rhp_empty_sp_master_edge_list ()
EXIT" ]

	node [ id 903 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
rhp_log (&quot;%s():\n&quot;, &amp;__FUNCTION__);
" ]

	node [ id 904 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
&lt;L0&gt;:
return;
" ]

	edge [ source 901 target 903 graphics [ fill "#0000ff" ] ] 
	edge [ source 903 target 904 graphics [ fill "#0000ff" ] ] 
	edge [ source 904 target 902 graphics [ fill "#000000" ] ] 
	node [ id 909 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
if (spn != 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 910 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
_4 = spn-&gt;value;
is = (struct rhp_inter_layer_struct *) _4;
_5 = is-&gt;eedges;
rhp_log (&quot;%s(): free eedges %p\n&quot;, &amp;__FUNCTION__, _5);
_6 = is-&gt;eedges;
if (_6 != 0B)
  goto &lt;bb 4&gt;; [INV]
else
  goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 911 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_7 = is-&gt;eedges;
_8 = rhp_free (_7, &amp;__FUNCTION__, 2281);
is-&gt;eedges = _8;
" ]

	node [ id 912 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
_9 = spn-&gt;key;
rhp_sp_between_layers.141_10 = rhp_sp_between_layers;
spn = rhp_sp_next (rhp_sp_between_layers.141_10, _9);
" ]



# function number 37
	node [ id 913 graphics [ fill "#ffffff" ] label "rhp_empty_sp_between_layers ()
ENTRY" ]

	node [ id 914 graphics [ fill "#ffffff" ] label "rhp_empty_sp_between_layers ()
EXIT" ]

	node [ id 915 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
is = 0B;
rhp_sp_between_layers.139_1 = rhp_sp_between_layers;
_2 = rhp_sp_has_data (rhp_sp_between_layers.139_1);
rhp_log (&quot;%s(): data is %d\n&quot;, &amp;__FUNCTION__, _2);
rhp_sp_between_layers.140_3 = rhp_sp_between_layers;
spn = rhp_sp_min (rhp_sp_between_layers.140_3);
goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 916 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
" ]

	node [ id 917 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
&lt;L5&gt;:
return;
" ]

	edge [ source 913 target 915 graphics [ fill "#0000ff" ] ] 
	edge [ source 915 target 909 graphics [ fill "#0000ff" ] ] 
	edge [ source 910 target 911 graphics [ fill "#000000" ] ] 
	edge [ source 910 target 912 graphics [ fill "#000000" ] ] 
	edge [ source 911 target 912 graphics [ fill "#0000ff" ] ] 
	edge [ source 912 target 909 graphics [ fill "#0000ff" ] ] 
	edge [ source 909 target 910 graphics [ fill "#000000" ] ] 
	edge [ source 909 target 916 graphics [ fill "#000000" ] ] 
	edge [ source 916 target 917 graphics [ fill "#0000ff" ] ] 
	edge [ source 917 target 914 graphics [ fill "#000000" ] ] 
	node [ id 927 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
_21 = rl-&gt;number_of_nodes;
if (i &lt; _21)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 17&gt;; [INV]
" ]

	node [ id 928 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
_11 = rl-&gt;nodes;
_12 = (long unsigned int) i;
_13 = _12 * 8;
_14 = _11 + _13;
nd = *_14;
_15 = nd-&gt;up_degree;
if (_15 != 0)
  goto &lt;bb 12&gt;; [INV]
else
  goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 929 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
_16 = nd-&gt;up_edges;
_17 = rhp_free (_16, &amp;__FUNCTION__, 2339);
nd-&gt;up_edges = _17;
nd-&gt;up_degree = 0;
" ]

	node [ id 930 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
_18 = nd-&gt;down_degree;
if (_18 != 0)
  goto &lt;bb 14&gt;; [INV]
else
  goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 931 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
_19 = nd-&gt;down_edges;
_20 = rhp_free (_19, &amp;__FUNCTION__, 2345);
nd-&gt;down_edges = _20;
nd-&gt;down_degree = 0;
" ]

	node [ id 932 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
i = i + 1;
" ]

	node [ id 933 graphics [ fill "#d3d3d3" ] label "&lt;bb 19&gt;:
rhp_nlevels.147_24 = rhp_nlevels;
if (level &lt; rhp_nlevels.147_24)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 20&gt;; [INV]
" ]

	node [ id 934 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
_4 = (long long int) level;
rhp_sp_layers.145_5 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.145_5, _4);
if (spn == 0B)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 935 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_nlevels.146_6 = rhp_nlevels;
if (rhp_nlevels.146_6 &gt; 1)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 936 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
_7 = spn-&gt;value;
rl = (struct rhplevel *) _7;
_8 = rl-&gt;nodes;
_9 = rl-&gt;number_of_nodes;
rhp_log (&quot;%s(): clear level %d with %d nodes %p\n&quot;, &amp;__FUNCTION__, level, _9, _8);
_10 = rl-&gt;nodes;
if (_10 != 0B)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 937 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_log (&quot;%s(): could not get data for level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
" ]

	node [ id 938 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
// predicted unlikely by continue predictor.
goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 939 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
i = 0;
goto &lt;bb 16&gt;; [INV]
" ]

	node [ id 940 graphics [ fill "#d3d3d3" ] label "&lt;bb 18&gt;:
level = level + 1;
" ]

	node [ id 941 graphics [ fill "#d3d3d3" ] label "&lt;bb 17&gt;:
_22 = rl-&gt;nodes;
_23 = rhp_free (_22, &amp;__FUNCTION__, 2350);
rl-&gt;nodes = _23;
rl-&gt;number_of_nodes = 0;
" ]



# function number 38
	node [ id 942 graphics [ fill "#ffffff" ] label "rhp_empty_sp_layers ()
ENTRY" ]

	node [ id 943 graphics [ fill "#ffffff" ] label "rhp_empty_sp_layers ()
EXIT" ]

	node [ id 944 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
rl = 0B;
nd = 0B;
level = 0;
i = 0;
rhp_sp_layers.142_1 = rhp_sp_layers;
rhp_nlevels.143_2 = rhp_nlevels;
rhp_log (&quot;%s(): %d levels to clear in sp %p\n&quot;, &amp;__FUNCTION__, rhp_nlevels.143_2, rhp_sp_layers.142_1);
rhp_sp_layers.144_3 = rhp_sp_layers;
if (rhp_sp_layers.144_3 == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 945 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 21&gt;; [INV]
" ]

	node [ id 946 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
level = 0;
goto &lt;bb 19&gt;; [INV]
" ]

	node [ id 947 graphics [ fill "#d3d3d3" ] label "&lt;bb 20&gt;:
" ]

	node [ id 948 graphics [ fill "#d3d3d3" ] label "&lt;bb 21&gt;:
&lt;L19&gt;:
return;
" ]

	edge [ source 942 target 944 graphics [ fill "#0000ff" ] ] 
	edge [ source 944 target 945 graphics [ fill "#000000" ] ] 
	edge [ source 944 target 946 graphics [ fill "#000000" ] ] 
	edge [ source 945 target 948 graphics [ fill "#0000ff" ] ] 
	edge [ source 946 target 933 graphics [ fill "#0000ff" ] ] 
	edge [ source 934 target 935 graphics [ fill "#000000" ] ] 
	edge [ source 934 target 936 graphics [ fill "#000000" ] ] 
	edge [ source 935 target 937 graphics [ fill "#000000" ] ] 
	edge [ source 935 target 938 graphics [ fill "#000000" ] ] 
	edge [ source 937 target 938 graphics [ fill "#0000ff" ] ] 
	edge [ source 938 target 940 graphics [ fill "#0000ff" ] ] 
	edge [ source 936 target 939 graphics [ fill "#000000" ] ] 
	edge [ source 936 target 940 graphics [ fill "#000000" ] ] 
	edge [ source 939 target 927 graphics [ fill "#0000ff" ] ] 
	edge [ source 928 target 929 graphics [ fill "#000000" ] ] 
	edge [ source 928 target 930 graphics [ fill "#000000" ] ] 
	edge [ source 929 target 930 graphics [ fill "#0000ff" ] ] 
	edge [ source 930 target 931 graphics [ fill "#000000" ] ] 
	edge [ source 930 target 932 graphics [ fill "#000000" ] ] 
	edge [ source 931 target 932 graphics [ fill "#0000ff" ] ] 
	edge [ source 932 target 927 graphics [ fill "#0000ff" ] ] 
	edge [ source 927 target 928 graphics [ fill "#000000" ] ] 
	edge [ source 927 target 941 graphics [ fill "#000000" ] ] 
	edge [ source 941 target 940 graphics [ fill "#0000ff" ] ] 
	edge [ source 940 target 933 graphics [ fill "#0000ff" ] ] 
	edge [ source 933 target 934 graphics [ fill "#000000" ] ] 
	edge [ source 933 target 947 graphics [ fill "#000000" ] ] 
	edge [ source 947 target 948 graphics [ fill "#0000ff" ] ] 
	edge [ source 948 target 943 graphics [ fill "#000000" ] ] 
	node [ id 971 graphics [ fill "#d3d3d3" ] label "&lt;bb 34&gt;:
_66 = rl-&gt;number_of_nodes;
if (ii &lt; _66)
  goto &lt;bb 33&gt;; [INV]
else
  goto &lt;bb 35&gt;; [INV]
" ]

	node [ id 972 graphics [ fill "#d3d3d3" ] label "&lt;bb 33&gt;:
_60 = rl-&gt;nodes;
_61 = (long unsigned int) ii;
_62 = _61 * 8;
_63 = _60 + _62;
_64 = *_63;
_65 = _64-&gt;innum;
rhp_log (&quot; %d&quot;, _65);
ii = ii + 1;
" ]

	node [ id 973 graphics [ fill "#d3d3d3" ] label "&lt;bb 37&gt;:
rhp_nlevels.166_68 = rhp_nlevels;
if (level &lt; rhp_nlevels.166_68)
  goto &lt;bb 29&gt;; [INV]
else
  goto &lt;bb 38&gt;; [INV]
" ]

	node [ id 974 graphics [ fill "#d3d3d3" ] label "&lt;bb 29&gt;:
_54 = (long long int) level;
rhp_sp_layers.165_55 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.165_55, _54);
_56 = spn-&gt;value;
rl = (struct rhplevel *) _56;
_57 = rl-&gt;number_of_nodes;
if (_57 == 0)
  goto &lt;bb 30&gt;; [INV]
else
  goto &lt;bb 31&gt;; [INV]
" ]

	node [ id 975 graphics [ fill "#d3d3d3" ] label "&lt;bb 30&gt;:
rhp_log (&quot;%s(): level %d has no nodes shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
goto &lt;bb 36&gt;; [INV]
" ]

	node [ id 976 graphics [ fill "#d3d3d3" ] label "&lt;bb 31&gt;:
_58 = rl-&gt;number_of_nodes;
rhp_log (&quot;%s(): level %d has %d nodes&quot;, &amp;__FUNCTION__, level, _58);
_59 = rl-&gt;nodes;
if (_59 != 0B)
  goto &lt;bb 32&gt;; [INV]
else
  goto &lt;bb 35&gt;; [INV]
" ]

	node [ id 977 graphics [ fill "#d3d3d3" ] label "&lt;bb 36&gt;:
_67 = rl-&gt;number_of_nodes;
i = i + _67;
level = level + 1;
" ]

	node [ id 978 graphics [ fill "#d3d3d3" ] label "&lt;bb 32&gt;:
rhp_log (&quot;%s&quot;, &quot; with numbers&quot;);
ii = 0;
goto &lt;bb 34&gt;; [INV]
" ]

	node [ id 979 graphics [ fill "#d3d3d3" ] label "&lt;bb 35&gt;:
rhp_log (&quot;%s&quot;, &quot;\n&quot;);
" ]

	node [ id 980 graphics [ fill "#d3d3d3" ] label "&lt;bb 27&gt;:
if (spnn != 0B)
  goto &lt;bb 21&gt;; [INV]
else
  goto &lt;bb 28&gt;; [INV]
" ]

	node [ id 981 graphics [ fill "#d3d3d3" ] label "&lt;bb 21&gt;:
_38 = spnn-&gt;value;
nd = (struct rhpnode *) _38;
level = nd-&gt;level;
_39 = (long long int) level;
rhp_sp_layers.163_40 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.163_40, _39);
if (spn == 0B)
  goto &lt;bb 22&gt;; [INV]
else
  goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 982 graphics [ fill "#d3d3d3" ] label "&lt;bb 23&gt;:
_41 = spn-&gt;value;
rl = (struct rhplevel *) _41;
_42 = rl-&gt;nodes;
if (_42 != 0B)
  goto &lt;bb 24&gt;; [INV]
else
  goto &lt;bb 25&gt;; [INV]
" ]

	node [ id 983 graphics [ fill "#d3d3d3" ] label "&lt;bb 24&gt;:
_43 = rl-&gt;nodes;
_44 = rl-&gt;number_of_nodes;
_45 = (long unsigned int) _44;
_46 = _45 * 8;
_47 = _43 + _46;
*_47 = nd;
_48 = rl-&gt;number_of_nodes;
_49 = _48 + 1;
rl-&gt;number_of_nodes = _49;
goto &lt;bb 26&gt;; [INV]
" ]

	node [ id 984 graphics [ fill "#d3d3d3" ] label "&lt;bb 25&gt;:
_50 = nd-&gt;level;
_51 = nd-&gt;innum;
rhp_log (&quot;%s(): should have been nodes[] for node %d level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, _51, _50);
" ]

	node [ id 985 graphics [ fill "#d3d3d3" ] label "&lt;bb 26&gt;:
_52 = spnn-&gt;key;
rhp_sp_master_node_list.164_53 = rhp_sp_master_node_list;
spnn = rhp_sp_next (rhp_sp_master_node_list.164_53, _52);
" ]

	node [ id 986 graphics [ fill "#d3d3d3" ] label "&lt;bb 19&gt;:
rhp_nlevels.161_36 = rhp_nlevels;
if (i &lt; rhp_nlevels.161_36)
  goto &lt;bb 15&gt;; [INV]
else
  goto &lt;bb 20&gt;; [INV]
" ]

	node [ id 987 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
_24 = (long long int) i;
rhp_sp_layers.160_25 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.160_25, _24);
_26 = spn-&gt;value;
rl = (struct rhplevel *) _26;
_27 = rl-&gt;number_of_nodes;
if (_27 != 0)
  goto &lt;bb 16&gt;; [INV]
else
  goto &lt;bb 17&gt;; [INV]
" ]

	node [ id 988 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
_28 = rl-&gt;number_of_nodes;
rhp_log (&quot;%s(): there are %d nodes in level %d\n&quot;, &amp;__FUNCTION__, _28, i);
_29 = rl-&gt;number_of_nodes;
_30 = (long unsigned int) _29;
_31 = _30 * 8;
_32 = rhp_malloc (_31, &amp;__FUNCTION__, 2442);
rl-&gt;nodes = _32;
_33 = rl-&gt;number_of_nodes;
_34 = (long unsigned int) _33;
_35 = _34 * 8;
bt = bt + _35;
goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 989 graphics [ fill "#d3d3d3" ] label "&lt;bb 17&gt;:
rhp_log (&quot;%s(): there are no nodes in level %d\n&quot;, &amp;__FUNCTION__, i);
" ]

	node [ id 990 graphics [ fill "#d3d3d3" ] label "&lt;bb 18&gt;:
rl-&gt;number_of_nodes = 0;
i = i + 1;
" ]

	node [ id 991 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
if (spnn != 0B)
  goto &lt;bb 12&gt;; [INV]
else
  goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 992 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
_12 = spnn-&gt;value;
nd = (struct rhpnode *) _12;
level = nd-&gt;level;
_13 = (long long int) level;
rhp_sp_layers.156_14 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.156_14, _13);
_15 = spn-&gt;value;
rl = (struct rhplevel *) _15;
_16 = rl-&gt;number_of_nodes;
_17 = _16 + 1;
rl-&gt;number_of_nodes = _17;
rhp_number_of_nodes.157_18 = rhp_number_of_nodes;
_19 = rhp_number_of_nodes.157_18 + 1;
rhp_number_of_nodes = _19;
rhp_number_of_nodes.158_20 = rhp_number_of_nodes;
_21 = rl-&gt;number_of_nodes;
rhp_log (&quot;%s(): now counted %d nodes in level %d total %d\n&quot;, &amp;__FUNCTION__, _21, i, rhp_number_of_nodes.158_20);
_22 = spnn-&gt;key;
rhp_sp_master_node_list.159_23 = rhp_sp_master_node_list;
spnn = rhp_sp_next (rhp_sp_master_node_list.159_23, _22);
" ]

	node [ id 993 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
rhp_nlevels.154_10 = rhp_nlevels;
if (i &lt; rhp_nlevels.154_10)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 994 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rl = rhp_malloc (16, &amp;__FUNCTION__, 2398);
bt = bt + 16;
rl-&gt;number_of_nodes = 0;
rl-&gt;nodes = 0B;
rhp_log (&quot;%s(): creating entry for level %d\n&quot;, &amp;__FUNCTION__, i);
rl.152_7 = (long long int) rl;
_8 = (long long int) i;
rhp_sp_layers.153_9 = rhp_sp_layers;
rhp_sp_insert (rhp_sp_layers.153_9, _8, rl.152_7);
i = i + 1;
" ]



# function number 39
	node [ id 995 graphics [ fill "#ffffff" ] label "rhp_allocatelayers ()
ENTRY" ]

	node [ id 996 graphics [ fill "#ffffff" ] label "rhp_allocatelayers ()
EXIT" ]

	node [ id 997 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
i = 0;
ii = 0;
rl = 0B;
spn = 0B;
spnn = 0B;
nd = 0B;
level = 0;
bt = 0;
rhp_number_of_nodes = 0;
rhp_sp_master_node_list.148_1 = rhp_sp_master_node_list;
_2 = rhp_sp_has_data (rhp_sp_master_node_list.148_1);
if (_2 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 998 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): no nodes shouldnothappen!\n&quot;, &amp;__FUNCTION__);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 39&gt;; [INV]
" ]

	node [ id 999 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_nlevels.149_3 = rhp_nlevels;
if (rhp_nlevels.149_3 == 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 1000 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_log (&quot;%s(): no levels shouldnothappen!\n&quot;, &amp;__FUNCTION__);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 39&gt;; [INV]
" ]

	node [ id 1001 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_sp_layers.150_4 = rhp_sp_layers;
if (rhp_sp_layers.150_4 != 0B)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1002 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_sp_layers.151_5 = rhp_sp_layers;
rhp_log (&quot;%s(): rhp_sp_layers %p shouldnothappen!\n&quot;, &amp;__FUNCTION__, rhp_sp_layers.151_5);
" ]

	node [ id 1003 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
_6 = rhp_sp_new (1);
rhp_sp_layers = _6;
i = 0;
goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1004 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
rhp_sp_master_node_list.155_11 = rhp_sp_master_node_list;
spnn = rhp_sp_min (rhp_sp_master_node_list.155_11);
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 1005 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
i = 0;
goto &lt;bb 19&gt;; [INV]
" ]

	node [ id 1006 graphics [ fill "#d3d3d3" ] label "&lt;bb 20&gt;:
rhp_sp_master_node_list.162_37 = rhp_sp_master_node_list;
spnn = rhp_sp_min (rhp_sp_master_node_list.162_37);
goto &lt;bb 27&gt;; [INV]
" ]

	node [ id 1007 graphics [ fill "#d3d3d3" ] label "&lt;bb 22&gt;:
rhp_log (&quot;%s(): no spn level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 39&gt;; [INV]
" ]

	node [ id 1008 graphics [ fill "#d3d3d3" ] label "&lt;bb 28&gt;:
i = 0;
level = 0;
goto &lt;bb 37&gt;; [INV]
" ]

	node [ id 1009 graphics [ fill "#d3d3d3" ] label "&lt;bb 38&gt;:
rhp_number_of_nodes.167_69 = rhp_number_of_nodes;
rhp_maxlevel.168_70 = rhp_maxlevel;
rhp_nlevels.169_71 = rhp_nlevels;
rhp_log (&quot;%s(): in %d levels (0...%d) are %d nodes and %d number_of_nodes\n&quot;, &amp;__FUNCTION__, rhp_nlevels.169_71, rhp_maxlevel.168_70, i, rhp_number_of_nodes.167_69);
rhp_log (&quot;%s(): using %lu bytes for the level data\n&quot;, &amp;__FUNCTION__, bt);
" ]

	node [ id 1010 graphics [ fill "#d3d3d3" ] label "&lt;bb 39&gt;:
&lt;L37&gt;:
return;
" ]

	edge [ source 995 target 997 graphics [ fill "#0000ff" ] ] 
	edge [ source 997 target 998 graphics [ fill "#000000" ] ] 
	edge [ source 997 target 999 graphics [ fill "#000000" ] ] 
	edge [ source 998 target 1010 graphics [ fill "#0000ff" ] ] 
	edge [ source 999 target 1000 graphics [ fill "#000000" ] ] 
	edge [ source 999 target 1001 graphics [ fill "#000000" ] ] 
	edge [ source 1000 target 1010 graphics [ fill "#0000ff" ] ] 
	edge [ source 1001 target 1002 graphics [ fill "#000000" ] ] 
	edge [ source 1001 target 1003 graphics [ fill "#000000" ] ] 
	edge [ source 1002 target 1003 graphics [ fill "#0000ff" ] ] 
	edge [ source 1003 target 993 graphics [ fill "#0000ff" ] ] 
	edge [ source 994 target 993 graphics [ fill "#0000ff" ] ] 
	edge [ source 993 target 994 graphics [ fill "#000000" ] ] 
	edge [ source 993 target 1004 graphics [ fill "#000000" ] ] 
	edge [ source 1004 target 991 graphics [ fill "#0000ff" ] ] 
	edge [ source 992 target 991 graphics [ fill "#0000ff" ] ] 
	edge [ source 991 target 992 graphics [ fill "#000000" ] ] 
	edge [ source 991 target 1005 graphics [ fill "#000000" ] ] 
	edge [ source 1005 target 986 graphics [ fill "#0000ff" ] ] 
	edge [ source 987 target 988 graphics [ fill "#000000" ] ] 
	edge [ source 987 target 989 graphics [ fill "#000000" ] ] 
	edge [ source 988 target 990 graphics [ fill "#0000ff" ] ] 
	edge [ source 989 target 990 graphics [ fill "#0000ff" ] ] 
	edge [ source 990 target 986 graphics [ fill "#0000ff" ] ] 
	edge [ source 986 target 987 graphics [ fill "#000000" ] ] 
	edge [ source 986 target 1006 graphics [ fill "#000000" ] ] 
	edge [ source 1006 target 980 graphics [ fill "#0000ff" ] ] 
	edge [ source 981 target 1007 graphics [ fill "#000000" ] ] 
	edge [ source 981 target 982 graphics [ fill "#000000" ] ] 
	edge [ source 1007 target 1010 graphics [ fill "#0000ff" ] ] 
	edge [ source 982 target 983 graphics [ fill "#000000" ] ] 
	edge [ source 982 target 984 graphics [ fill "#000000" ] ] 
	edge [ source 983 target 985 graphics [ fill "#0000ff" ] ] 
	edge [ source 984 target 985 graphics [ fill "#0000ff" ] ] 
	edge [ source 985 target 980 graphics [ fill "#0000ff" ] ] 
	edge [ source 980 target 981 graphics [ fill "#000000" ] ] 
	edge [ source 980 target 1008 graphics [ fill "#000000" ] ] 
	edge [ source 1008 target 973 graphics [ fill "#0000ff" ] ] 
	edge [ source 974 target 975 graphics [ fill "#000000" ] ] 
	edge [ source 974 target 976 graphics [ fill "#000000" ] ] 
	edge [ source 975 target 977 graphics [ fill "#0000ff" ] ] 
	edge [ source 976 target 978 graphics [ fill "#000000" ] ] 
	edge [ source 976 target 979 graphics [ fill "#000000" ] ] 
	edge [ source 978 target 971 graphics [ fill "#0000ff" ] ] 
	edge [ source 972 target 971 graphics [ fill "#0000ff" ] ] 
	edge [ source 971 target 972 graphics [ fill "#000000" ] ] 
	edge [ source 971 target 979 graphics [ fill "#000000" ] ] 
	edge [ source 979 target 977 graphics [ fill "#0000ff" ] ] 
	edge [ source 977 target 973 graphics [ fill "#0000ff" ] ] 
	edge [ source 973 target 974 graphics [ fill "#000000" ] ] 
	edge [ source 973 target 1009 graphics [ fill "#000000" ] ] 
	edge [ source 1009 target 1010 graphics [ fill "#0000ff" ] ] 
	edge [ source 1010 target 996 graphics [ fill "#000000" ] ] 
	node [ id 1051 graphics [ fill "#d3d3d3" ] label "&lt;bb 37&gt;:
_93 = nd-&gt;down_degree;
if (i &lt; _93)
  goto &lt;bb 36&gt;; [INV]
else
  goto &lt;bb 38&gt;; [INV]
" ]

	node [ id 1052 graphics [ fill "#d3d3d3" ] label "&lt;bb 36&gt;:
_88 = nd-&gt;down_edges;
_89 = (long unsigned int) i;
_90 = _89 * 8;
_91 = _88 + _90;
re = *_91;
_92 = re-&gt;innum;
rhp_log (&quot; %d&quot;, _92);
i = i + 1;
" ]

	node [ id 1053 graphics [ fill "#d3d3d3" ] label "&lt;bb 33&gt;:
_86 = nd-&gt;up_degree;
if (i &lt; _86)
  goto &lt;bb 32&gt;; [INV]
else
  goto &lt;bb 34&gt;; [INV]
" ]

	node [ id 1054 graphics [ fill "#d3d3d3" ] label "&lt;bb 32&gt;:
_81 = nd-&gt;up_edges;
_82 = (long unsigned int) i;
_83 = _82 * 8;
_84 = _81 + _83;
re = *_84;
_85 = re-&gt;innum;
rhp_log (&quot; %d&quot;, _85);
i = i + 1;
" ]

	node [ id 1055 graphics [ fill "#d3d3d3" ] label "&lt;bb 39&gt;:
if (spn != 0B)
  goto &lt;bb 30&gt;; [INV]
else
  goto &lt;bb 40&gt;; [INV]
" ]

	node [ id 1056 graphics [ fill "#d3d3d3" ] label "&lt;bb 30&gt;:
_76 = spn-&gt;value;
nd = (struct rhpnode *) _76;
_77 = nd-&gt;down_degree;
_78 = nd-&gt;up_degree;
_79 = nd-&gt;innum;
rhp_log (&quot;%s(): node %d has up/down degree %d/%d&quot;, &amp;__FUNCTION__, _79, _78, _77);
_80 = nd-&gt;up_edges;
if (_80 != 0B)
  goto &lt;bb 31&gt;; [INV]
else
  goto &lt;bb 34&gt;; [INV]
" ]

	node [ id 1057 graphics [ fill "#d3d3d3" ] label "&lt;bb 31&gt;:
rhp_log (&quot; up connected with edge number&quot;);
i = 0;
goto &lt;bb 33&gt;; [INV]
" ]

	node [ id 1058 graphics [ fill "#d3d3d3" ] label "&lt;bb 34&gt;:
_87 = nd-&gt;down_edges;
if (_87 != 0B)
  goto &lt;bb 35&gt;; [INV]
else
  goto &lt;bb 38&gt;; [INV]
" ]

	node [ id 1059 graphics [ fill "#d3d3d3" ] label "&lt;bb 35&gt;:
rhp_log (&quot; down connected with edge number&quot;);
i = 0;
goto &lt;bb 37&gt;; [INV]
" ]

	node [ id 1060 graphics [ fill "#d3d3d3" ] label "&lt;bb 38&gt;:
rhp_log (&quot;%s&quot;, &quot;\n&quot;);
_94 = spn-&gt;key;
rhp_sp_master_node_list.182_95 = rhp_sp_master_node_list;
spn = rhp_sp_next (rhp_sp_master_node_list.182_95, _94);
" ]

	node [ id 1061 graphics [ fill "#d3d3d3" ] label "&lt;bb 28&gt;:
if (spn != 0B)
  goto &lt;bb 24&gt;; [INV]
else
  goto &lt;bb 29&gt;; [INV]
" ]

	node [ id 1062 graphics [ fill "#d3d3d3" ] label "&lt;bb 24&gt;:
_53 = spn-&gt;value;
re = (struct rhpedge *) _53;
_54 = re-&gt;fn;
_55 = _54-&gt;level;
_56 = re-&gt;tn;
_57 = _56-&gt;level;
if (_55 &gt; _57)
  goto &lt;bb 25&gt;; [INV]
else
  goto &lt;bb 26&gt;; [INV]
" ]

	node [ id 1063 graphics [ fill "#d3d3d3" ] label "&lt;bb 25&gt;:
rhp_log (&quot;%s(): uppernode is above lowernode shouldnothappen!\n&quot;, &amp;__FUNCTION__);
upper_node = re-&gt;fn;
lower_node = re-&gt;tn;
goto &lt;bb 27&gt;; [INV]
" ]

	node [ id 1064 graphics [ fill "#d3d3d3" ] label "&lt;bb 26&gt;:
upper_node = re-&gt;tn;
lower_node = re-&gt;fn;
" ]

	node [ id 1065 graphics [ fill "#d3d3d3" ] label "&lt;bb 27&gt;:
_58 = upper_node-&gt;down_edges;
_59 = upper_node-&gt;down_degree;
_60 = (long unsigned int) _59;
_61 = _60 * 8;
_62 = _58 + _61;
*_62 = re;
_63 = upper_node-&gt;down_degree;
_64 = _63 + 1;
upper_node-&gt;down_degree = _64;
_65 = lower_node-&gt;up_edges;
_66 = lower_node-&gt;up_degree;
_67 = (long unsigned int) _66;
_68 = _67 * 8;
_69 = _65 + _68;
*_69 = re;
_70 = lower_node-&gt;up_degree;
_71 = _70 + 1;
lower_node-&gt;up_degree = _71;
_72 = spn-&gt;key;
rhp_sp_master_edge_list.179_73 = rhp_sp_master_edge_list;
spn = rhp_sp_next (rhp_sp_master_edge_list.179_73, _72);
" ]

	node [ id 1066 graphics [ fill "#d3d3d3" ] label "&lt;bb 20&gt;:
_44 = rl-&gt;number_of_nodes;
if (i &lt; _44)
  goto &lt;bb 15&gt;; [INV]
else
  goto &lt;bb 21&gt;; [INV]
" ]

	node [ id 1067 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
_21 = rl-&gt;nodes;
_22 = (long unsigned int) i;
_23 = _22 * 8;
_24 = _21 + _23;
nd = *_24;
nd-&gt;position = pos;
_25 = nd-&gt;down_degree;
_26 = nd-&gt;up_degree;
_27 = nd-&gt;innum;
rhp_log (&quot;%s(): node %d pos %d in level %d has up/down degree %d/%d\n&quot;, &amp;__FUNCTION__, _27, pos, level, _26, _25);
_28 = nd-&gt;up_degree;
if (_28 != 0)
  goto &lt;bb 16&gt;; [INV]
else
  goto &lt;bb 17&gt;; [INV]
" ]

	node [ id 1068 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
_29 = nd-&gt;up_degree;
_30 = (long unsigned int) _29;
_31 = _30 * 8;
_32 = rhp_malloc (_31, &amp;__FUNCTION__, 2617);
nd-&gt;up_edges = _32;
_33 = nd-&gt;up_degree;
_34 = (long unsigned int) _33;
_35 = _34 * 8;
bt = bt + _35;
" ]

	node [ id 1069 graphics [ fill "#d3d3d3" ] label "&lt;bb 17&gt;:
_36 = nd-&gt;down_degree;
if (_36 != 0)
  goto &lt;bb 18&gt;; [INV]
else
  goto &lt;bb 19&gt;; [INV]
" ]

	node [ id 1070 graphics [ fill "#d3d3d3" ] label "&lt;bb 18&gt;:
_37 = nd-&gt;down_degree;
_38 = (long unsigned int) _37;
_39 = _38 * 8;
_40 = rhp_malloc (_39, &amp;__FUNCTION__, 2623);
nd-&gt;down_edges = _40;
_41 = nd-&gt;down_degree;
_42 = (long unsigned int) _41;
_43 = _42 * 8;
bt = bt + _43;
" ]

	node [ id 1071 graphics [ fill "#d3d3d3" ] label "&lt;bb 19&gt;:
pos = pos + 1;
nd-&gt;up_degree = 0;
nd-&gt;down_degree = 0;
i = i + 1;
" ]

	node [ id 1072 graphics [ fill "#d3d3d3" ] label "&lt;bb 22&gt;:
rhp_nlevels.175_45 = rhp_nlevels;
if (level &lt; rhp_nlevels.175_45)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 1073 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
_17 = (long long int) level;
rhp_sp_layers.174_18 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.174_18, _17);
if (spn == 0B)
  goto &lt;bb 12&gt;; [INV]
else
  goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 1074 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
pos = 0;
_19 = spn-&gt;value;
rl = (struct rhplevel *) _19;
_20 = rl-&gt;nodes;
if (_20 != 0B)
  goto &lt;bb 14&gt;; [INV]
else
  goto &lt;bb 21&gt;; [INV]
" ]

	node [ id 1075 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
i = 0;
goto &lt;bb 20&gt;; [INV]
" ]

	node [ id 1076 graphics [ fill "#d3d3d3" ] label "&lt;bb 21&gt;:
level = level + 1;
" ]

	node [ id 1077 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
if (spn != 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1078 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
_4 = spn-&gt;value;
re = (struct rhpedge *) _4;
rhp_number_of_edges.172_5 = rhp_number_of_edges;
_6 = rhp_number_of_edges.172_5 + 1;
rhp_number_of_edges = _6;
_7 = re-&gt;fn;
_8 = _7-&gt;level;
_9 = re-&gt;tn;
_10 = _9-&gt;level;
if (_8 &gt; _10)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 1079 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_log (&quot;%s(): uppernode is above lowernode shouldnothappen!\n&quot;, &amp;__FUNCTION__);
upper_node = re-&gt;fn;
lower_node = re-&gt;tn;
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1080 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
upper_node = re-&gt;tn;
lower_node = re-&gt;fn;
" ]

	node [ id 1081 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
_11 = upper_node-&gt;down_degree;
_12 = _11 + 1;
upper_node-&gt;down_degree = _12;
_13 = lower_node-&gt;up_degree;
_14 = _13 + 1;
lower_node-&gt;up_degree = _14;
_15 = spn-&gt;key;
rhp_sp_master_edge_list.173_16 = rhp_sp_master_edge_list;
spn = rhp_sp_next (rhp_sp_master_edge_list.173_16, _15);
" ]



# function number 40
	node [ id 1082 graphics [ fill "#ffffff" ] label "rhp_allocateadjacencylists ()
ENTRY" ]

	node [ id 1083 graphics [ fill "#ffffff" ] label "rhp_allocateadjacencylists ()
EXIT" ]

	node [ id 1084 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
re = 0B;
upper_node = 0B;
lower_node = 0B;
nd = 0B;
rl = 0B;
level = 0;
pos = 0;
i = 0;
bt = 0;
rhp_number_of_edges = 0;
rhp_sp_master_edge_list.170_1 = rhp_sp_master_edge_list;
_2 = rhp_sp_has_data (rhp_sp_master_edge_list.170_1);
if (_2 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1085 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 41&gt;; [INV]
" ]

	node [ id 1086 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_sp_master_edge_list.171_3 = rhp_sp_master_edge_list;
spn = rhp_sp_min (rhp_sp_master_edge_list.171_3);
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 1087 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
bt = 0;
level = 0;
goto &lt;bb 22&gt;; [INV]
" ]

	node [ id 1088 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
rhp_log (&quot;%s(): no spn level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 41&gt;; [INV]
" ]

	node [ id 1089 graphics [ fill "#d3d3d3" ] label "&lt;bb 23&gt;:
rhp_number_of_nodes.176_46 = rhp_number_of_nodes;
_47 = (long unsigned int) rhp_number_of_nodes.176_46;
_48 = _47 * 80;
_49 = bt + _48;
_50 = (long long int) _49;
bt.177_51 = (long long int) bt;
rhp_log (&quot;%s(): using %lu additional more bytes for the node data and total now %lu bytes\n&quot;, &amp;__FUNCTION__, bt.177_51, _50);
rhp_sp_master_edge_list.178_52 = rhp_sp_master_edge_list;
spn = rhp_sp_min (rhp_sp_master_edge_list.178_52);
goto &lt;bb 28&gt;; [INV]
" ]

	node [ id 1090 graphics [ fill "#d3d3d3" ] label "&lt;bb 29&gt;:
rhp_number_of_edges.180_74 = rhp_number_of_edges;
rhp_log (&quot;%s(): number_of_edges is %d\n&quot;, &amp;__FUNCTION__, rhp_number_of_edges.180_74);
rhp_sp_master_node_list.181_75 = rhp_sp_master_node_list;
spn = rhp_sp_min (rhp_sp_master_node_list.181_75);
goto &lt;bb 39&gt;; [INV]
" ]

	node [ id 1091 graphics [ fill "#d3d3d3" ] label "&lt;bb 40&gt;:
" ]

	node [ id 1092 graphics [ fill "#d3d3d3" ] label "&lt;bb 41&gt;:
&lt;L41&gt;:
return;
" ]

	edge [ source 1082 target 1084 graphics [ fill "#0000ff" ] ] 
	edge [ source 1084 target 1085 graphics [ fill "#000000" ] ] 
	edge [ source 1084 target 1086 graphics [ fill "#000000" ] ] 
	edge [ source 1085 target 1092 graphics [ fill "#0000ff" ] ] 
	edge [ source 1086 target 1077 graphics [ fill "#0000ff" ] ] 
	edge [ source 1078 target 1079 graphics [ fill "#000000" ] ] 
	edge [ source 1078 target 1080 graphics [ fill "#000000" ] ] 
	edge [ source 1079 target 1081 graphics [ fill "#0000ff" ] ] 
	edge [ source 1080 target 1081 graphics [ fill "#0000ff" ] ] 
	edge [ source 1081 target 1077 graphics [ fill "#0000ff" ] ] 
	edge [ source 1077 target 1078 graphics [ fill "#000000" ] ] 
	edge [ source 1077 target 1087 graphics [ fill "#000000" ] ] 
	edge [ source 1087 target 1072 graphics [ fill "#0000ff" ] ] 
	edge [ source 1073 target 1088 graphics [ fill "#000000" ] ] 
	edge [ source 1073 target 1074 graphics [ fill "#000000" ] ] 
	edge [ source 1088 target 1092 graphics [ fill "#0000ff" ] ] 
	edge [ source 1074 target 1075 graphics [ fill "#000000" ] ] 
	edge [ source 1074 target 1076 graphics [ fill "#000000" ] ] 
	edge [ source 1075 target 1066 graphics [ fill "#0000ff" ] ] 
	edge [ source 1067 target 1068 graphics [ fill "#000000" ] ] 
	edge [ source 1067 target 1069 graphics [ fill "#000000" ] ] 
	edge [ source 1068 target 1069 graphics [ fill "#0000ff" ] ] 
	edge [ source 1069 target 1070 graphics [ fill "#000000" ] ] 
	edge [ source 1069 target 1071 graphics [ fill "#000000" ] ] 
	edge [ source 1070 target 1071 graphics [ fill "#0000ff" ] ] 
	edge [ source 1071 target 1066 graphics [ fill "#0000ff" ] ] 
	edge [ source 1066 target 1067 graphics [ fill "#000000" ] ] 
	edge [ source 1066 target 1076 graphics [ fill "#000000" ] ] 
	edge [ source 1076 target 1072 graphics [ fill "#0000ff" ] ] 
	edge [ source 1072 target 1073 graphics [ fill "#000000" ] ] 
	edge [ source 1072 target 1089 graphics [ fill "#000000" ] ] 
	edge [ source 1089 target 1061 graphics [ fill "#0000ff" ] ] 
	edge [ source 1062 target 1063 graphics [ fill "#000000" ] ] 
	edge [ source 1062 target 1064 graphics [ fill "#000000" ] ] 
	edge [ source 1063 target 1065 graphics [ fill "#0000ff" ] ] 
	edge [ source 1064 target 1065 graphics [ fill "#0000ff" ] ] 
	edge [ source 1065 target 1061 graphics [ fill "#0000ff" ] ] 
	edge [ source 1061 target 1062 graphics [ fill "#000000" ] ] 
	edge [ source 1061 target 1090 graphics [ fill "#000000" ] ] 
	edge [ source 1090 target 1055 graphics [ fill "#0000ff" ] ] 
	edge [ source 1056 target 1057 graphics [ fill "#000000" ] ] 
	edge [ source 1056 target 1058 graphics [ fill "#000000" ] ] 
	edge [ source 1057 target 1053 graphics [ fill "#0000ff" ] ] 
	edge [ source 1054 target 1053 graphics [ fill "#0000ff" ] ] 
	edge [ source 1053 target 1054 graphics [ fill "#000000" ] ] 
	edge [ source 1053 target 1058 graphics [ fill "#000000" ] ] 
	edge [ source 1058 target 1059 graphics [ fill "#000000" ] ] 
	edge [ source 1058 target 1060 graphics [ fill "#000000" ] ] 
	edge [ source 1059 target 1051 graphics [ fill "#0000ff" ] ] 
	edge [ source 1052 target 1051 graphics [ fill "#0000ff" ] ] 
	edge [ source 1051 target 1052 graphics [ fill "#000000" ] ] 
	edge [ source 1051 target 1060 graphics [ fill "#000000" ] ] 
	edge [ source 1060 target 1055 graphics [ fill "#0000ff" ] ] 
	edge [ source 1055 target 1056 graphics [ fill "#000000" ] ] 
	edge [ source 1055 target 1091 graphics [ fill "#000000" ] ] 
	edge [ source 1091 target 1092 graphics [ fill "#0000ff" ] ] 
	edge [ source 1092 target 1083 graphics [ fill "#000000" ] ] 
	node [ id 1135 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
if (spn != 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1136 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
_4 = spn-&gt;value;
nd = (struct rhpnode *) _4;
_5 = nd-&gt;up_degree;
if (_5 == 0)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1137 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_6 = nd-&gt;down_degree;
if (_6 == 0)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1138 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
_7 = spn-&gt;key;
rhp_sp_master_node_list.185_8 = rhp_sp_master_node_list;
spn = rhp_sp_next (rhp_sp_master_node_list.185_8, _7);
" ]

	node [ id 1139 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
c = c + 1;
" ]



# function number 41
	node [ id 1140 graphics [ fill "#ffffff" ] label "rhp_countisolatednodes ()
ENTRY" ]

	node [ id 1141 graphics [ fill "#ffffff" ] label "rhp_countisolatednodes ()
EXIT" ]

	node [ id 1142 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
nd = 0B;
spn = 0B;
c = 0;
rhp_number_of_isolated_nodes = 0;
rhp_sp_master_node_list.183_1 = rhp_sp_master_node_list;
_2 = rhp_sp_has_data (rhp_sp_master_node_list.183_1);
if (_2 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1143 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): no nodes shouldnothappen!\n&quot;, &amp;__FUNCTION__);
D.4752 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1144 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_sp_master_node_list.184_3 = rhp_sp_master_node_list;
spn = rhp_sp_min (rhp_sp_master_node_list.184_3);
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 1145 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
rhp_log (&quot;%s(): %d nodes without edge connections found\n&quot;, &amp;__FUNCTION__, c);
D.4752 = c;
" ]

	node [ id 1146 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
&lt;L9&gt;:
return D.4752;
" ]

	edge [ source 1140 target 1142 graphics [ fill "#0000ff" ] ] 
	edge [ source 1142 target 1143 graphics [ fill "#000000" ] ] 
	edge [ source 1142 target 1144 graphics [ fill "#000000" ] ] 
	edge [ source 1143 target 1146 graphics [ fill "#0000ff" ] ] 
	edge [ source 1144 target 1135 graphics [ fill "#0000ff" ] ] 
	edge [ source 1136 target 1137 graphics [ fill "#000000" ] ] 
	edge [ source 1136 target 1138 graphics [ fill "#000000" ] ] 
	edge [ source 1137 target 1139 graphics [ fill "#000000" ] ] 
	edge [ source 1137 target 1138 graphics [ fill "#000000" ] ] 
	edge [ source 1139 target 1138 graphics [ fill "#0000ff" ] ] 
	edge [ source 1138 target 1135 graphics [ fill "#0000ff" ] ] 
	edge [ source 1135 target 1136 graphics [ fill "#000000" ] ] 
	edge [ source 1135 target 1145 graphics [ fill "#000000" ] ] 
	edge [ source 1145 target 1146 graphics [ fill "#0000ff" ] ] 
	edge [ source 1146 target 1141 graphics [ fill "#000000" ] ] 
	node [ id 1159 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_nlevels.190_6 = rhp_nlevels;
if (i &lt; rhp_nlevels.190_6)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 1160 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
is = rhp_makeinterlayer (i);
is.188_3 = (long long int) is;
_4 = (long long int) i;
rhp_sp_between_layers.189_5 = rhp_sp_between_layers;
rhp_sp_insert (rhp_sp_between_layers.189_5, _4, is.188_3);
i = i + 1;
" ]



# function number 42
	node [ id 1161 graphics [ fill "#ffffff" ] label "rhp_initcrossings ()
ENTRY" ]

	node [ id 1162 graphics [ fill "#ffffff" ] label "rhp_initcrossings ()
EXIT" ]

	node [ id 1163 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
i = 0;
is = 0B;
rhp_nlevels.186_1 = rhp_nlevels;
rhp_log (&quot;%s(): rhp_nlevels is %d\n&quot;, &amp;__FUNCTION__, rhp_nlevels.186_1);
rhp_nlevels.187_2 = rhp_nlevels;
if (rhp_nlevels.187_2 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1164 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): no levels shouldnothappen!\n&quot;, &amp;__FUNCTION__);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1165 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
i = 0;
goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 1166 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
" ]

	node [ id 1167 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
&lt;L5&gt;:
return;
" ]

	edge [ source 1161 target 1163 graphics [ fill "#0000ff" ] ] 
	edge [ source 1163 target 1164 graphics [ fill "#000000" ] ] 
	edge [ source 1163 target 1165 graphics [ fill "#000000" ] ] 
	edge [ source 1164 target 1167 graphics [ fill "#0000ff" ] ] 
	edge [ source 1165 target 1159 graphics [ fill "#0000ff" ] ] 
	edge [ source 1160 target 1159 graphics [ fill "#0000ff" ] ] 
	edge [ source 1159 target 1160 graphics [ fill "#000000" ] ] 
	edge [ source 1159 target 1166 graphics [ fill "#000000" ] ] 
	edge [ source 1166 target 1167 graphics [ fill "#0000ff" ] ] 
	edge [ source 1167 target 1162 graphics [ fill "#000000" ] ] 


# function number 43
	node [ id 1177 graphics [ fill "#ffffff" ] label "rhp_makeinterlayer ()
ENTRY" ]

	node [ id 1178 graphics [ fill "#ffffff" ] label "rhp_makeinterlayer ()
EXIT" ]

	node [ id 1179 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
is = 0B;
bt = 0;
is = rhp_malloc (24, &amp;__FUNCTION__, 2788);
bt = bt + 24;
_1 = rhp_count_down_edges (upper_layer);
is-&gt;number_of_edges = _1;
is-&gt;number_of_crossings = -1;
_2 = is-&gt;number_of_edges;
if (_2 != 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1180 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
_3 = is-&gt;number_of_edges;
_4 = (long unsigned int) _3;
_5 = _4 * 8;
_6 = rhp_malloc (_5, &amp;__FUNCTION__, 2800);
is-&gt;eedges = _6;
_7 = is-&gt;number_of_edges;
_8 = (long unsigned int) _7;
_9 = _8 * 8;
bt = bt + _9;
" ]

	node [ id 1181 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
bt.191_10 = (long long int) bt;
rhp_log (&quot;%s(): using %lu bytes for the interlevels\n&quot;, &amp;__FUNCTION__, bt.191_10);
D.4763 = is;
" ]

	node [ id 1182 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
&lt;L2&gt;:
return D.4763;
" ]

	edge [ source 1177 target 1179 graphics [ fill "#0000ff" ] ] 
	edge [ source 1179 target 1180 graphics [ fill "#000000" ] ] 
	edge [ source 1179 target 1181 graphics [ fill "#000000" ] ] 
	edge [ source 1180 target 1181 graphics [ fill "#0000ff" ] ] 
	edge [ source 1181 target 1182 graphics [ fill "#0000ff" ] ] 
	edge [ source 1182 target 1178 graphics [ fill "#000000" ] ] 
	node [ id 1189 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
_11 = lv-&gt;number_of_nodes;
if (i &lt; _11)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 1190 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
_6 = lv-&gt;nodes;
_7 = (long unsigned int) i;
_8 = _7 * 8;
_9 = _6 + _8;
nd = *_9;
_10 = nd-&gt;down_degree;
count = count + _10;
i = i + 1;
" ]



# function number 44
	node [ id 1191 graphics [ fill "#ffffff" ] label "rhp_count_down_edges ()
ENTRY" ]

	node [ id 1192 graphics [ fill "#ffffff" ] label "rhp_count_down_edges ()
EXIT" ]

	node [ id 1193 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
lv = 0B;
nd = 0B;
count = 0;
i = 0;
_1 = (long long int) layer_number;
rhp_sp_layers.192_2 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.192_2, _1);
if (spn == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1194 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): no data for level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, layer_number);
D.4767 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 1195 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_3 = spn-&gt;value;
lv = (struct rhplevel *) _3;
if (lv == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 1196 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_log (&quot;%s(): no nodes in level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, layer_number);
D.4767 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 1197 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_4 = lv-&gt;nodes;
if (_4 == 0B)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1198 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_log (&quot;%s(): no data for nodes in level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, layer_number);
D.4767 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 1199 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
count = 0;
_5 = lv-&gt;nodes;
if (_5 != 0B)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 1200 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
i = 0;
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1201 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
rhp_log (&quot;%s(): down_degree count is %d at level %d\n&quot;, &amp;__FUNCTION__, count, layer_number);
D.4767 = count;
" ]

	node [ id 1202 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
&lt;L11&gt;:
return D.4767;
" ]

	edge [ source 1191 target 1193 graphics [ fill "#0000ff" ] ] 
	edge [ source 1193 target 1194 graphics [ fill "#000000" ] ] 
	edge [ source 1193 target 1195 graphics [ fill "#000000" ] ] 
	edge [ source 1194 target 1202 graphics [ fill "#0000ff" ] ] 
	edge [ source 1195 target 1196 graphics [ fill "#000000" ] ] 
	edge [ source 1195 target 1197 graphics [ fill "#000000" ] ] 
	edge [ source 1196 target 1202 graphics [ fill "#0000ff" ] ] 
	edge [ source 1197 target 1198 graphics [ fill "#000000" ] ] 
	edge [ source 1197 target 1199 graphics [ fill "#000000" ] ] 
	edge [ source 1198 target 1202 graphics [ fill "#0000ff" ] ] 
	edge [ source 1199 target 1200 graphics [ fill "#000000" ] ] 
	edge [ source 1199 target 1201 graphics [ fill "#000000" ] ] 
	edge [ source 1200 target 1189 graphics [ fill "#0000ff" ] ] 
	edge [ source 1190 target 1189 graphics [ fill "#0000ff" ] ] 
	edge [ source 1189 target 1190 graphics [ fill "#000000" ] ] 
	edge [ source 1189 target 1201 graphics [ fill "#000000" ] ] 
	edge [ source 1201 target 1202 graphics [ fill "#0000ff" ] ] 
	edge [ source 1202 target 1192 graphics [ fill "#000000" ] ] 
	node [ id 1217 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_nlevels.193_1 = rhp_nlevels;
if (i &lt; rhp_nlevels.193_1)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 1218 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_updatecrossingsbetweenlayers (i);
i = i + 1;
" ]



# function number 45
	node [ id 1219 graphics [ fill "#ffffff" ] label "rhp_updateallcrossings ()
ENTRY" ]

	node [ id 1220 graphics [ fill "#ffffff" ] label "rhp_updateallcrossings ()
EXIT" ]

	node [ id 1221 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
i = 0;
rhp_updateallpositions ();
i = 1;
goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1222 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
" ]

	node [ id 1223 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
&lt;L3&gt;:
return;
" ]

	edge [ source 1219 target 1221 graphics [ fill "#0000ff" ] ] 
	edge [ source 1221 target 1217 graphics [ fill "#0000ff" ] ] 
	edge [ source 1218 target 1217 graphics [ fill "#0000ff" ] ] 
	edge [ source 1217 target 1218 graphics [ fill "#000000" ] ] 
	edge [ source 1217 target 1222 graphics [ fill "#000000" ] ] 
	edge [ source 1222 target 1223 graphics [ fill "#0000ff" ] ] 
	edge [ source 1223 target 1220 graphics [ fill "#000000" ] ] 
	node [ id 1231 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_nlevels.195_2 = rhp_nlevels;
if (i &lt; rhp_nlevels.195_2)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 1232 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_updatenodepositions (i);
i = i + 1;
" ]



# function number 46
	node [ id 1233 graphics [ fill "#ffffff" ] label "rhp_updateallpositions ()
ENTRY" ]

	node [ id 1234 graphics [ fill "#ffffff" ] label "rhp_updateallpositions ()
EXIT" ]

	node [ id 1235 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
i = 0;
rhp_nlevels.194_1 = rhp_nlevels;
rhp_log (&quot;%s(): updating all node positions in %d levels\n&quot;, &amp;__FUNCTION__, rhp_nlevels.194_1);
i = 0;
goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1236 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
" ]

	node [ id 1237 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
&lt;L3&gt;:
return;
" ]

	edge [ source 1233 target 1235 graphics [ fill "#0000ff" ] ] 
	edge [ source 1235 target 1231 graphics [ fill "#0000ff" ] ] 
	edge [ source 1232 target 1231 graphics [ fill "#0000ff" ] ] 
	edge [ source 1231 target 1232 graphics [ fill "#000000" ] ] 
	edge [ source 1231 target 1236 graphics [ fill "#000000" ] ] 
	edge [ source 1236 target 1237 graphics [ fill "#0000ff" ] ] 
	edge [ source 1237 target 1234 graphics [ fill "#000000" ] ] 
	node [ id 1245 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
_13 = lv-&gt;number_of_nodes;
if (i &lt; _13)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1246 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
_5 = lv-&gt;nodes;
_6 = (long unsigned int) i;
_7 = _6 * 8;
_8 = _5 + _7;
nd = *_8;
nd-&gt;position = pos;
_9 = nd-&gt;weight;
_10 = nd-&gt;position;
_11 = nd-&gt;level;
_12 = nd-&gt;innum;
rhp_log (&quot;%s(): node %d level %d pos %d weight %d\n&quot;, &amp;__FUNCTION__, _12, _11, _10, _9);
pos = pos + 1;
i = i + 1;
" ]



# function number 47
	node [ id 1247 graphics [ fill "#ffffff" ] label "rhp_updatenodepositions ()
ENTRY" ]

	node [ id 1248 graphics [ fill "#ffffff" ] label "rhp_updatenodepositions ()
EXIT" ]

	node [ id 1249 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
lv = 0B;
nd = 0B;
pos = 0;
i = 0;
rhp_log (&quot;%s(): updating node positions for level %d\n&quot;, &amp;__FUNCTION__, layer_number);
_1 = (long long int) layer_number;
rhp_sp_layers.196_2 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.196_2, _1);
if (spn == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1250 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): no data for level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, layer_number);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 1251 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_3 = spn-&gt;value;
lv = (struct rhplevel *) _3;
if (lv == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 1252 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_log (&quot;%s(): no nodes in level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, layer_number);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 1253 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_4 = lv-&gt;nodes;
if (_4 == 0B)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1254 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_log (&quot;%s(): no data for nodes in level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, layer_number);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 1255 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
pos = 0;
i = 0;
goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1256 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
" ]

	node [ id 1257 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
&lt;L9&gt;:
return;
" ]

	edge [ source 1247 target 1249 graphics [ fill "#0000ff" ] ] 
	edge [ source 1249 target 1250 graphics [ fill "#000000" ] ] 
	edge [ source 1249 target 1251 graphics [ fill "#000000" ] ] 
	edge [ source 1250 target 1257 graphics [ fill "#0000ff" ] ] 
	edge [ source 1251 target 1252 graphics [ fill "#000000" ] ] 
	edge [ source 1251 target 1253 graphics [ fill "#000000" ] ] 
	edge [ source 1252 target 1257 graphics [ fill "#0000ff" ] ] 
	edge [ source 1253 target 1254 graphics [ fill "#000000" ] ] 
	edge [ source 1253 target 1255 graphics [ fill "#000000" ] ] 
	edge [ source 1254 target 1257 graphics [ fill "#0000ff" ] ] 
	edge [ source 1255 target 1245 graphics [ fill "#0000ff" ] ] 
	edge [ source 1246 target 1245 graphics [ fill "#0000ff" ] ] 
	edge [ source 1245 target 1246 graphics [ fill "#000000" ] ] 
	edge [ source 1245 target 1256 graphics [ fill "#000000" ] ] 
	edge [ source 1256 target 1257 graphics [ fill "#0000ff" ] ] 
	edge [ source 1257 target 1248 graphics [ fill "#000000" ] ] 


# function number 48
	node [ id 1271 graphics [ fill "#ffffff" ] label "rhp_updatecrossingsforlayer ()
ENTRY" ]

	node [ id 1272 graphics [ fill "#ffffff" ] label "rhp_updatecrossingsforlayer ()
EXIT" ]

	node [ id 1273 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
rhp_updatenodepositions (layer);
if (layer &gt; 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1274 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_updatecrossingsbetweenlayers (layer);
" ]

	node [ id 1275 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_nlevels.197_1 = rhp_nlevels;
_2 = rhp_nlevels.197_1 + -1;
if (layer &lt; _2)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 1276 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
_3 = layer + 1;
rhp_updatecrossingsbetweenlayers (_3);
" ]

	node [ id 1277 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
" ]

	node [ id 1278 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
&lt;L4&gt;:
return;
" ]

	edge [ source 1271 target 1273 graphics [ fill "#0000ff" ] ] 
	edge [ source 1273 target 1274 graphics [ fill "#000000" ] ] 
	edge [ source 1273 target 1275 graphics [ fill "#000000" ] ] 
	edge [ source 1274 target 1275 graphics [ fill "#0000ff" ] ] 
	edge [ source 1275 target 1276 graphics [ fill "#000000" ] ] 
	edge [ source 1275 target 1277 graphics [ fill "#000000" ] ] 
	edge [ source 1276 target 1277 graphics [ fill "#0000ff" ] ] 
	edge [ source 1277 target 1278 graphics [ fill "#0000ff" ] ] 
	edge [ source 1278 target 1272 graphics [ fill "#000000" ] ] 
	node [ id 1287 graphics [ fill "#d3d3d3" ] label "&lt;bb 49&gt;:
_80 = lv-&gt;number_of_nodes;
if (i &lt; _80)
  goto &lt;bb 48&gt;; [INV]
else
  goto &lt;bb 50&gt;; [INV]
" ]

	node [ id 1288 graphics [ fill "#d3d3d3" ] label "&lt;bb 48&gt;:
_75 = lv-&gt;nodes;
_76 = (long unsigned int) i;
_77 = _76 * 8;
_78 = _75 + _77;
nd = *_78;
_79 = nd-&gt;innum;
rhp_log (&quot; %d&quot;, _79);
i = i + 1;
" ]

	node [ id 1289 graphics [ fill "#d3d3d3" ] label "&lt;bb 38&gt;:
_63 = nd-&gt;down_degree;
if (ii &lt; _63)
  goto &lt;bb 37&gt;; [INV]
else
  goto &lt;bb 39&gt;; [INV]
" ]

	node [ id 1290 graphics [ fill "#d3d3d3" ] label "&lt;bb 37&gt;:
_57 = nd-&gt;down_edges;
_58 = (long unsigned int) ii;
_59 = _58 * 8;
_60 = _57 + _59;
_61 = *_60;
_62 = _61-&gt;innum;
rhp_log (&quot; %d&quot;, _62);
ii = ii + 1;
" ]

	node [ id 1291 graphics [ fill "#d3d3d3" ] label "&lt;bb 40&gt;:
_64 = lv-&gt;number_of_nodes;
if (i &lt; _64)
  goto &lt;bb 35&gt;; [INV]
else
  goto &lt;bb 41&gt;; [INV]
" ]

	node [ id 1292 graphics [ fill "#d3d3d3" ] label "&lt;bb 35&gt;:
_50 = lv-&gt;nodes;
_51 = (long unsigned int) i;
_52 = _51 * 8;
_53 = _50 + _52;
nd = *_53;
_54 = nd-&gt;down_degree;
_55 = nd-&gt;innum;
rhp_log (&quot;%s():   node %d down-degree %d connected to edges:&quot;, &amp;__FUNCTION__, _55, _54);
_56 = nd-&gt;down_degree;
if (_56 &gt; 0)
  goto &lt;bb 36&gt;; [INV]
else
  goto &lt;bb 39&gt;; [INV]
" ]

	node [ id 1293 graphics [ fill "#d3d3d3" ] label "&lt;bb 36&gt;:
ii = 0;
goto &lt;bb 38&gt;; [INV]
" ]

	node [ id 1294 graphics [ fill "#d3d3d3" ] label "&lt;bb 39&gt;:
rhp_log (&quot;%s&quot;, &quot;\n&quot;);
i = i + 1;
" ]

	node [ id 1295 graphics [ fill "#d3d3d3" ] label "&lt;bb 31&gt;:
_45 = lv-&gt;number_of_nodes;
if (i &lt; _45)
  goto &lt;bb 30&gt;; [INV]
else
  goto &lt;bb 32&gt;; [INV]
" ]

	node [ id 1296 graphics [ fill "#d3d3d3" ] label "&lt;bb 30&gt;:
_41 = lv-&gt;nodes;
_42 = (long unsigned int) i;
_43 = _42 * 8;
_44 = _41 + _43;
nd = *_44;
nd-&gt;up_crossings = 0;
i = i + 1;
" ]

	node [ id 1297 graphics [ fill "#d3d3d3" ] label "&lt;bb 20&gt;:
_31 = nd-&gt;down_degree;
if (ii &lt; _31)
  goto &lt;bb 19&gt;; [INV]
else
  goto &lt;bb 21&gt;; [INV]
" ]

	node [ id 1298 graphics [ fill "#d3d3d3" ] label "&lt;bb 19&gt;:
_26 = nd-&gt;down_edges;
_27 = (long unsigned int) ii;
_28 = _27 * 8;
_29 = _26 + _28;
_30 = *_29;
_30-&gt;crossings = 0;
ii = ii + 1;
" ]

	node [ id 1299 graphics [ fill "#d3d3d3" ] label "&lt;bb 22&gt;:
_32 = lv-&gt;number_of_nodes;
if (i &lt; _32)
  goto &lt;bb 17&gt;; [INV]
else
  goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 1300 graphics [ fill "#d3d3d3" ] label "&lt;bb 17&gt;:
_21 = lv-&gt;nodes;
_22 = (long unsigned int) i;
_23 = _22 * 8;
_24 = _21 + _23;
nd = *_24;
nd-&gt;down_crossings = 0;
_25 = nd-&gt;down_degree;
if (_25 &gt; 0)
  goto &lt;bb 18&gt;; [INV]
else
  goto &lt;bb 21&gt;; [INV]
" ]

	node [ id 1301 graphics [ fill "#d3d3d3" ] label "&lt;bb 18&gt;:
ii = 0;
goto &lt;bb 20&gt;; [INV]
" ]

	node [ id 1302 graphics [ fill "#d3d3d3" ] label "&lt;bb 21&gt;:
i = i + 1;
" ]

	node [ id 1303 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
_20 = lv-&gt;number_of_nodes;
if (i &lt; _20)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 16&gt;; [INV]
" ]

	node [ id 1304 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
_5 = lv-&gt;nodes;
_6 = (long unsigned int) i;
_7 = _6 * 8;
_8 = _5 + _7;
nd = *_8;
_9 = nd-&gt;down_degree;
if (_9 &gt; 1)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1305 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
_10 = nd-&gt;down_degree;
_11 = nd-&gt;down_edges;
rhp_sortbydownnodeposition (_11, _10);
" ]

	node [ id 1306 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
_12 = nd-&gt;down_degree;
if (_12 &gt; 0)
  goto &lt;bb 12&gt;; [INV]
else
  goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 1307 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
_13 = (long long int) upper_layer;
rhp_sp_between_layers.199_14 = rhp_sp_between_layers;
spnb = rhp_sp_lookup (rhp_sp_between_layers.199_14, _13);
if (spnb != 0B)
  goto &lt;bb 13&gt;; [INV]
else
  goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 1308 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
_19 = nd-&gt;down_degree;
ix = ix + _19;
i = i + 1;
" ]

	node [ id 1309 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
_15 = spnb-&gt;value;
is = (struct rhp_inter_layer_struct *) _15;
_16 = nd-&gt;down_degree;
_17 = nd-&gt;down_edges;
_18 = is-&gt;eedges;
rhp_add_edges_to_array (_18, _17, _16, ix);
" ]



# function number 49
	node [ id 1310 graphics [ fill "#ffffff" ] label "rhp_updatecrossingsbetweenlayers ()
ENTRY" ]

	node [ id 1311 graphics [ fill "#ffffff" ] label "rhp_updatecrossingsbetweenlayers ()
EXIT" ]

	node [ id 1312 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
spnb = 0B;
lv = 0B;
nd = 0B;
is = 0B;
ix = 0;
i = 0;
ii = 0;
ncross = 0;
_1 = (long long int) upper_layer;
rhp_sp_layers.198_2 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.198_2, _1);
if (spn == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1313 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): no data for level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, upper_layer);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 54&gt;; [INV]
" ]

	node [ id 1314 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_3 = spn-&gt;value;
lv = (struct rhplevel *) _3;
if (lv == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 1315 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_log (&quot;%s(): no nodes in level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, upper_layer);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 54&gt;; [INV]
" ]

	node [ id 1316 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_4 = lv-&gt;nodes;
if (_4 == 0B)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1317 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
rhp_log (&quot;%s(): no data for nodes in level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, upper_layer);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 54&gt;; [INV]
" ]

	node [ id 1318 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
i = 0;
goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 1319 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
i = 0;
goto &lt;bb 22&gt;; [INV]
" ]

	node [ id 1320 graphics [ fill "#d3d3d3" ] label "&lt;bb 23&gt;:
_33 = upper_layer + -1;
_34 = (long long int) _33;
rhp_sp_layers.200_35 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.200_35, _34);
if (spn == 0B)
  goto &lt;bb 24&gt;; [INV]
else
  goto &lt;bb 25&gt;; [INV]
" ]

	node [ id 1321 graphics [ fill "#d3d3d3" ] label "&lt;bb 24&gt;:
_36 = upper_layer + -1;
rhp_log (&quot;%s(): no data for level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, _36);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 54&gt;; [INV]
" ]

	node [ id 1322 graphics [ fill "#d3d3d3" ] label "&lt;bb 25&gt;:
_37 = spn-&gt;value;
lv = (struct rhplevel *) _37;
if (lv == 0B)
  goto &lt;bb 26&gt;; [INV]
else
  goto &lt;bb 27&gt;; [INV]
" ]

	node [ id 1323 graphics [ fill "#d3d3d3" ] label "&lt;bb 26&gt;:
_38 = upper_layer + -1;
rhp_log (&quot;%s(): no nodes in level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, _38);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 54&gt;; [INV]
" ]

	node [ id 1324 graphics [ fill "#d3d3d3" ] label "&lt;bb 27&gt;:
_39 = lv-&gt;nodes;
if (_39 == 0B)
  goto &lt;bb 28&gt;; [INV]
else
  goto &lt;bb 29&gt;; [INV]
" ]

	node [ id 1325 graphics [ fill "#d3d3d3" ] label "&lt;bb 28&gt;:
_40 = upper_layer + -1;
rhp_log (&quot;%s(): no data for nodes in level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, _40);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 54&gt;; [INV]
" ]

	node [ id 1326 graphics [ fill "#d3d3d3" ] label "&lt;bb 29&gt;:
i = 0;
goto &lt;bb 31&gt;; [INV]
" ]

	node [ id 1327 graphics [ fill "#d3d3d3" ] label "&lt;bb 32&gt;:
_46 = (long long int) upper_layer;
rhp_sp_layers.201_47 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.201_47, _46);
if (spn == 0B)
  goto &lt;bb 33&gt;; [INV]
else
  goto &lt;bb 34&gt;; [INV]
" ]

	node [ id 1328 graphics [ fill "#d3d3d3" ] label "&lt;bb 33&gt;:
rhp_log (&quot;%s(): no data for level %d shouldnothappen!\n&quot;, upper_layer);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 54&gt;; [INV]
" ]

	node [ id 1329 graphics [ fill "#d3d3d3" ] label "&lt;bb 34&gt;:
_48 = spn-&gt;value;
lv = (struct rhplevel *) _48;
_49 = lv-&gt;number_of_nodes;
rhp_log (&quot;%s(): level %d has %d nodes:\n&quot;, &amp;__FUNCTION__, upper_layer, _49);
i = 0;
goto &lt;bb 40&gt;; [INV]
" ]

	node [ id 1330 graphics [ fill "#d3d3d3" ] label "&lt;bb 41&gt;:
_65 = upper_layer + -1;
_66 = (long long int) _65;
rhp_sp_layers.202_67 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.202_67, _66);
if (spn == 0B)
  goto &lt;bb 42&gt;; [INV]
else
  goto &lt;bb 43&gt;; [INV]
" ]

	node [ id 1331 graphics [ fill "#d3d3d3" ] label "&lt;bb 42&gt;:
_68 = upper_layer + -1;
rhp_log (&quot;%s(): no data for level %d shouldnothappen!\n&quot;, _68);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 54&gt;; [INV]
" ]

	node [ id 1332 graphics [ fill "#d3d3d3" ] label "&lt;bb 43&gt;:
_69 = spn-&gt;value;
lv = (struct rhplevel *) _69;
if (lv == 0B)
  goto &lt;bb 44&gt;; [INV]
else
  goto &lt;bb 45&gt;; [INV]
" ]

	node [ id 1333 graphics [ fill "#d3d3d3" ] label "&lt;bb 44&gt;:
_70 = upper_layer + -1;
rhp_log (&quot;%s(): no nodes in level %d shouldnothappen!\n&quot;, _70);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 54&gt;; [INV]
" ]

	node [ id 1334 graphics [ fill "#d3d3d3" ] label "&lt;bb 45&gt;:
_71 = lv-&gt;nodes;
if (_71 == 0B)
  goto &lt;bb 46&gt;; [INV]
else
  goto &lt;bb 47&gt;; [INV]
" ]

	node [ id 1335 graphics [ fill "#d3d3d3" ] label "&lt;bb 46&gt;:
_72 = upper_layer + -1;
rhp_log (&quot;%s(): no data for nodes in level %d shouldnothappen!\n&quot;, _72);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 54&gt;; [INV]
" ]

	node [ id 1336 graphics [ fill "#d3d3d3" ] label "&lt;bb 47&gt;:
_73 = lv-&gt;number_of_nodes;
_74 = upper_layer + -1;
rhp_log (&quot;%s(): level %d has %d nodes:&quot;, &amp;__FUNCTION__, _74, _73);
i = 0;
goto &lt;bb 49&gt;; [INV]
" ]

	node [ id 1337 graphics [ fill "#d3d3d3" ] label "&lt;bb 50&gt;:
rhp_log (&quot;%s&quot;, &quot;\n&quot;);
_81 = (long long int) upper_layer;
rhp_sp_between_layers.203_82 = rhp_sp_between_layers;
spnb = rhp_sp_lookup (rhp_sp_between_layers.203_82, _81);
if (spnb != 0B)
  goto &lt;bb 51&gt;; [INV]
else
  goto &lt;bb 52&gt;; [INV]
" ]

	node [ id 1338 graphics [ fill "#d3d3d3" ] label "&lt;bb 51&gt;:
_83 = spnb-&gt;value;
is = (struct rhp_inter_layer_struct *) _83;
_84 = is-&gt;number_of_edges;
_85 = is-&gt;eedges;
ncross = rhp_count_inversions_down (_85, _84, 1);
is-&gt;number_of_crossings = ncross;
goto &lt;bb 53&gt;; [INV]
" ]

	node [ id 1339 graphics [ fill "#d3d3d3" ] label "&lt;bb 52&gt;:
rhp_log (&quot;%s(): could not find level %d in between_layers shouldnothappen!\n&quot;, &amp;__FUNCTION__, upper_layer);
" ]

	node [ id 1340 graphics [ fill "#d3d3d3" ] label "&lt;bb 53&gt;:
rhp_log (&quot;%s(): %li crossings at level %d\n&quot;, &amp;__FUNCTION__, ncross, upper_layer);
" ]

	node [ id 1341 graphics [ fill "#d3d3d3" ] label "&lt;bb 54&gt;:
&lt;L54&gt;:
return;
" ]

	edge [ source 1310 target 1312 graphics [ fill "#0000ff" ] ] 
	edge [ source 1312 target 1313 graphics [ fill "#000000" ] ] 
	edge [ source 1312 target 1314 graphics [ fill "#000000" ] ] 
	edge [ source 1313 target 1341 graphics [ fill "#0000ff" ] ] 
	edge [ source 1314 target 1315 graphics [ fill "#000000" ] ] 
	edge [ source 1314 target 1316 graphics [ fill "#000000" ] ] 
	edge [ source 1315 target 1341 graphics [ fill "#0000ff" ] ] 
	edge [ source 1316 target 1317 graphics [ fill "#000000" ] ] 
	edge [ source 1316 target 1318 graphics [ fill "#000000" ] ] 
	edge [ source 1317 target 1341 graphics [ fill "#0000ff" ] ] 
	edge [ source 1318 target 1303 graphics [ fill "#0000ff" ] ] 
	edge [ source 1304 target 1305 graphics [ fill "#000000" ] ] 
	edge [ source 1304 target 1306 graphics [ fill "#000000" ] ] 
	edge [ source 1305 target 1306 graphics [ fill "#0000ff" ] ] 
	edge [ source 1306 target 1307 graphics [ fill "#000000" ] ] 
	edge [ source 1306 target 1308 graphics [ fill "#000000" ] ] 
	edge [ source 1307 target 1309 graphics [ fill "#000000" ] ] 
	edge [ source 1307 target 1308 graphics [ fill "#000000" ] ] 
	edge [ source 1309 target 1308 graphics [ fill "#0000ff" ] ] 
	edge [ source 1308 target 1303 graphics [ fill "#0000ff" ] ] 
	edge [ source 1303 target 1304 graphics [ fill "#000000" ] ] 
	edge [ source 1303 target 1319 graphics [ fill "#000000" ] ] 
	edge [ source 1319 target 1299 graphics [ fill "#0000ff" ] ] 
	edge [ source 1300 target 1301 graphics [ fill "#000000" ] ] 
	edge [ source 1300 target 1302 graphics [ fill "#000000" ] ] 
	edge [ source 1301 target 1297 graphics [ fill "#0000ff" ] ] 
	edge [ source 1298 target 1297 graphics [ fill "#0000ff" ] ] 
	edge [ source 1297 target 1298 graphics [ fill "#000000" ] ] 
	edge [ source 1297 target 1302 graphics [ fill "#000000" ] ] 
	edge [ source 1302 target 1299 graphics [ fill "#0000ff" ] ] 
	edge [ source 1299 target 1300 graphics [ fill "#000000" ] ] 
	edge [ source 1299 target 1320 graphics [ fill "#000000" ] ] 
	edge [ source 1320 target 1321 graphics [ fill "#000000" ] ] 
	edge [ source 1320 target 1322 graphics [ fill "#000000" ] ] 
	edge [ source 1321 target 1341 graphics [ fill "#0000ff" ] ] 
	edge [ source 1322 target 1323 graphics [ fill "#000000" ] ] 
	edge [ source 1322 target 1324 graphics [ fill "#000000" ] ] 
	edge [ source 1323 target 1341 graphics [ fill "#0000ff" ] ] 
	edge [ source 1324 target 1325 graphics [ fill "#000000" ] ] 
	edge [ source 1324 target 1326 graphics [ fill "#000000" ] ] 
	edge [ source 1325 target 1341 graphics [ fill "#0000ff" ] ] 
	edge [ source 1326 target 1295 graphics [ fill "#0000ff" ] ] 
	edge [ source 1296 target 1295 graphics [ fill "#0000ff" ] ] 
	edge [ source 1295 target 1296 graphics [ fill "#000000" ] ] 
	edge [ source 1295 target 1327 graphics [ fill "#000000" ] ] 
	edge [ source 1327 target 1328 graphics [ fill "#000000" ] ] 
	edge [ source 1327 target 1329 graphics [ fill "#000000" ] ] 
	edge [ source 1328 target 1341 graphics [ fill "#0000ff" ] ] 
	edge [ source 1329 target 1291 graphics [ fill "#0000ff" ] ] 
	edge [ source 1292 target 1293 graphics [ fill "#000000" ] ] 
	edge [ source 1292 target 1294 graphics [ fill "#000000" ] ] 
	edge [ source 1293 target 1289 graphics [ fill "#0000ff" ] ] 
	edge [ source 1290 target 1289 graphics [ fill "#0000ff" ] ] 
	edge [ source 1289 target 1290 graphics [ fill "#000000" ] ] 
	edge [ source 1289 target 1294 graphics [ fill "#000000" ] ] 
	edge [ source 1294 target 1291 graphics [ fill "#0000ff" ] ] 
	edge [ source 1291 target 1292 graphics [ fill "#000000" ] ] 
	edge [ source 1291 target 1330 graphics [ fill "#000000" ] ] 
	edge [ source 1330 target 1331 graphics [ fill "#000000" ] ] 
	edge [ source 1330 target 1332 graphics [ fill "#000000" ] ] 
	edge [ source 1331 target 1341 graphics [ fill "#0000ff" ] ] 
	edge [ source 1332 target 1333 graphics [ fill "#000000" ] ] 
	edge [ source 1332 target 1334 graphics [ fill "#000000" ] ] 
	edge [ source 1333 target 1341 graphics [ fill "#0000ff" ] ] 
	edge [ source 1334 target 1335 graphics [ fill "#000000" ] ] 
	edge [ source 1334 target 1336 graphics [ fill "#000000" ] ] 
	edge [ source 1335 target 1341 graphics [ fill "#0000ff" ] ] 
	edge [ source 1336 target 1287 graphics [ fill "#0000ff" ] ] 
	edge [ source 1288 target 1287 graphics [ fill "#0000ff" ] ] 
	edge [ source 1287 target 1288 graphics [ fill "#000000" ] ] 
	edge [ source 1287 target 1337 graphics [ fill "#000000" ] ] 
	edge [ source 1337 target 1338 graphics [ fill "#000000" ] ] 
	edge [ source 1337 target 1339 graphics [ fill "#000000" ] ] 
	edge [ source 1338 target 1340 graphics [ fill "#0000ff" ] ] 
	edge [ source 1339 target 1340 graphics [ fill "#0000ff" ] ] 
	edge [ source 1340 target 1341 graphics [ fill "#0000ff" ] ] 
	edge [ source 1341 target 1311 graphics [ fill "#000000" ] ] 


# function number 50
	node [ id 1397 graphics [ fill "#ffffff" ] label "rhp_compare_down_edges ()
ENTRY" ]

	node [ id 1398 graphics [ fill "#ffffff" ] label "rhp_compare_down_edges ()
EXIT" ]

	node [ id 1399 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
entry_ptr_i = 0B;
entry_ptr_j = 0B;
edge_i = 0B;
edge_j = 0B;
entry_ptr_i = ptr_i;
entry_ptr_j = ptr_j;
edge_i = *entry_ptr_i;
edge_j = *entry_ptr_j;
_1 = edge_i-&gt;down_node;
_2 = _1-&gt;position;
_3 = edge_j-&gt;down_node;
_4 = _3-&gt;position;
if (_2 &gt; _4)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1400 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
D.4825 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 1401 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_5 = edge_i-&gt;down_node;
_6 = _5-&gt;position;
_7 = edge_j-&gt;down_node;
_8 = _7-&gt;position;
if (_6 &lt; _8)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 1402 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4825 = -1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 1403 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
D.4825 = 0;
// predicted unlikely by early return (on trees) predictor.
" ]

	node [ id 1404 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
&lt;L4&gt;:
return D.4825;
" ]

	edge [ source 1397 target 1399 graphics [ fill "#0000ff" ] ] 
	edge [ source 1399 target 1400 graphics [ fill "#000000" ] ] 
	edge [ source 1399 target 1401 graphics [ fill "#000000" ] ] 
	edge [ source 1400 target 1404 graphics [ fill "#0000ff" ] ] 
	edge [ source 1401 target 1402 graphics [ fill "#000000" ] ] 
	edge [ source 1401 target 1403 graphics [ fill "#000000" ] ] 
	edge [ source 1402 target 1404 graphics [ fill "#0000ff" ] ] 
	edge [ source 1403 target 1404 graphics [ fill "#0000ff" ] ] 
	edge [ source 1404 target 1398 graphics [ fill "#000000" ] ] 


# function number 51
	node [ id 1413 graphics [ fill "#ffffff" ] label "rhp_sortbydownnodeposition ()
ENTRY" ]

	node [ id 1414 graphics [ fill "#ffffff" ] label "rhp_sortbydownnodeposition ()
EXIT" ]

	node [ id 1415 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
_1 = (long unsigned int) num_edges;
qsort (edge_array, _1, 8, rhp_compare_down_edges);
" ]

	node [ id 1416 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
&lt;L0&gt;:
return;
" ]

	edge [ source 1413 target 1415 graphics [ fill "#0000ff" ] ] 
	edge [ source 1415 target 1416 graphics [ fill "#0000ff" ] ] 
	edge [ source 1416 target 1414 graphics [ fill "#000000" ] ] 
	node [ id 1421 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
if (edges_added &lt; num_edges)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 1422 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
_1 = (long unsigned int) edges_added;
_2 = _1 * 8;
_3 = edges_to_add + _2;
_4 = start_pos + edges_added;
_5 = (long unsigned int) _4;
_6 = _5 * 8;
_7 = edge_array + _6;
_8 = *_3;
*_7 = _8;
edges_added = edges_added + 1;
" ]



# function number 52
	node [ id 1423 graphics [ fill "#ffffff" ] label "rhp_add_edges_to_array ()
ENTRY" ]

	node [ id 1424 graphics [ fill "#ffffff" ] label "rhp_add_edges_to_array ()
EXIT" ]

	node [ id 1425 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
edges_added = 0;
if (num_edges &lt;= 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1426 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): %d num_edges is too low shouldnothappen!\n&quot;, &amp;__FUNCTION__, num_edges);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1427 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
edges_added = 0;
goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 1428 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
" ]

	node [ id 1429 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
&lt;L5&gt;:
return;
" ]

	edge [ source 1423 target 1425 graphics [ fill "#0000ff" ] ] 
	edge [ source 1425 target 1426 graphics [ fill "#000000" ] ] 
	edge [ source 1425 target 1427 graphics [ fill "#000000" ] ] 
	edge [ source 1426 target 1429 graphics [ fill "#0000ff" ] ] 
	edge [ source 1427 target 1421 graphics [ fill "#0000ff" ] ] 
	edge [ source 1422 target 1421 graphics [ fill "#0000ff" ] ] 
	edge [ source 1421 target 1422 graphics [ fill "#000000" ] ] 
	edge [ source 1421 target 1428 graphics [ fill "#000000" ] ] 
	edge [ source 1428 target 1429 graphics [ fill "#0000ff" ] ] 
	edge [ source 1429 target 1424 graphics [ fill "#000000" ] ] 
	node [ id 1439 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
if (i &lt; num_of_edges)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 1440 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
_1 = rhp_insert_and_count_inversions_down (edge_array, i, diff);
number_of_inversions = number_of_inversions + _1;
i = i + 1;
" ]



# function number 53
	node [ id 1441 graphics [ fill "#ffffff" ] label "rhp_count_inversions_down ()
ENTRY" ]

	node [ id 1442 graphics [ fill "#ffffff" ] label "rhp_count_inversions_down ()
EXIT" ]

	node [ id 1443 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
number_of_inversions = 0;
i = 0;
i = 1;
goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1444 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4833 = number_of_inversions;
" ]

	node [ id 1445 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
&lt;L3&gt;:
return D.4833;
" ]

	edge [ source 1441 target 1443 graphics [ fill "#0000ff" ] ] 
	edge [ source 1443 target 1439 graphics [ fill "#0000ff" ] ] 
	edge [ source 1440 target 1439 graphics [ fill "#0000ff" ] ] 
	edge [ source 1439 target 1440 graphics [ fill "#000000" ] ] 
	edge [ source 1439 target 1444 graphics [ fill "#000000" ] ] 
	edge [ source 1444 target 1445 graphics [ fill "#0000ff" ] ] 
	edge [ source 1445 target 1442 graphics [ fill "#000000" ] ] 
	node [ id 1453 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
if (ix &gt;= 0)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1454 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
_37 = (long unsigned int) ix;
_38 = _37 * 8;
_39 = edge_array + _38;
_40 = *_39;
_41 = _40-&gt;down_node;
_42 = _41-&gt;position;
_43 = edge_to_insert-&gt;down_node;
_44 = _43-&gt;position;
if (_42 &gt; _44)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1455 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
number_of_crossings = number_of_crossings + 1;
_8 = (long unsigned int) ix;
_9 = _8 * 8;
_10 = edge_array + _9;
edge_one = *_10;
edge_two = edge_to_insert;
_11 = edge_one-&gt;crossings;
_12 = (long int) diff;
_13 = _11 + _12;
edge_one-&gt;crossings = _13;
_14 = edge_two-&gt;crossings;
_15 = (long int) diff;
_16 = _14 + _15;
edge_two-&gt;crossings = _16;
up_node_one = edge_one-&gt;up_node;
up_node_two = edge_two-&gt;up_node;
down_node_one = edge_one-&gt;down_node;
down_node_two = edge_two-&gt;down_node;
_17 = up_node_one-&gt;down_crossings;
_18 = (long int) diff;
_19 = _17 + _18;
up_node_one-&gt;down_crossings = _19;
_20 = up_node_two-&gt;down_crossings;
_21 = (long int) diff;
_22 = _20 + _21;
up_node_two-&gt;down_crossings = _22;
_23 = down_node_one-&gt;up_crossings;
_24 = (long int) diff;
_25 = _23 + _24;
down_node_one-&gt;up_crossings = _25;
_26 = down_node_two-&gt;up_crossings;
_27 = (long int) diff;
_28 = _26 + _27;
down_node_two-&gt;up_crossings = _28;
_29 = (long unsigned int) ix;
_30 = _29 * 8;
_31 = edge_array + _30;
_32 = (sizetype) ix;
_33 = _32 + 1;
_34 = _33 * 8;
_35 = edge_array + _34;
_36 = *_31;
*_35 = _36;
ix = ix + -1;
" ]



# function number 54
	node [ id 1456 graphics [ fill "#ffffff" ] label "rhp_insert_and_count_inversions_down ()
ENTRY" ]

	node [ id 1457 graphics [ fill "#ffffff" ] label "rhp_insert_and_count_inversions_down ()
EXIT" ]

	node [ id 1458 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
number_of_crossings = 0;
ix = 0;
edge_to_insert = 0B;
edge_one = 0B;
edge_two = 0B;
up_node_one = 0B;
up_node_two = 0B;
down_node_one = 0B;
down_node_two = 0B;
number_of_crossings = 0;
if (starting_index &lt;= 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1459 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): starting_index is %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, starting_index);
D.4837 = number_of_crossings;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1460 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
ix = starting_index + -1;
_1 = (long unsigned int) starting_index;
_2 = _1 * 8;
_3 = edge_array + _2;
edge_to_insert = *_3;
_4 = (long unsigned int) ix;
_5 = _4 * 8;
_6 = edge_array + _5;
_7 = *_6;
if (_7 == 0B)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 1461 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_log (&quot;%s(): edge_array[%d] is nil and starting_index is %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, ix, starting_index);
D.4837 = number_of_crossings;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1462 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1463 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
_45 = (sizetype) ix;
_46 = _45 + 1;
_47 = _46 * 8;
_48 = edge_array + _47;
*_48 = edge_to_insert;
_49 = edge_to_insert-&gt;innum;
rhp_log (&quot;%s() at edge %d are %li crossings\n&quot;, &amp;__FUNCTION__, _49, number_of_crossings);
D.4837 = number_of_crossings;
" ]

	node [ id 1464 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
&lt;L8&gt;:
return D.4837;
" ]

	edge [ source 1456 target 1458 graphics [ fill "#0000ff" ] ] 
	edge [ source 1458 target 1459 graphics [ fill "#000000" ] ] 
	edge [ source 1458 target 1460 graphics [ fill "#000000" ] ] 
	edge [ source 1459 target 1464 graphics [ fill "#0000ff" ] ] 
	edge [ source 1460 target 1461 graphics [ fill "#000000" ] ] 
	edge [ source 1460 target 1462 graphics [ fill "#000000" ] ] 
	edge [ source 1461 target 1464 graphics [ fill "#0000ff" ] ] 
	edge [ source 1462 target 1453 graphics [ fill "#0000ff" ] ] 
	edge [ source 1455 target 1453 graphics [ fill "#0000ff" ] ] 
	edge [ source 1453 target 1454 graphics [ fill "#000000" ] ] 
	edge [ source 1453 target 1463 graphics [ fill "#000000" ] ] 
	edge [ source 1454 target 1455 graphics [ fill "#000000" ] ] 
	edge [ source 1454 target 1463 graphics [ fill "#000000" ] ] 
	edge [ source 1463 target 1464 graphics [ fill "#0000ff" ] ] 
	edge [ source 1464 target 1457 graphics [ fill "#000000" ] ] 
	node [ id 1477 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
rhp_nlevels.209_9 = rhp_nlevels;
if (i &lt; rhp_nlevels.209_9)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 1478 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
_5 = (long long int) i;
rhp_sp_between_layers.208_6 = rhp_sp_between_layers;
spnb = rhp_sp_lookup (rhp_sp_between_layers.208_6, _5);
if (spnb != 0B)
  goto &lt;bb 8&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 1479 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
_7 = spnb-&gt;value;
is = (struct rhp_inter_layer_struct *) _7;
_8 = is-&gt;number_of_crossings;
crossings = crossings + _8;
goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1480 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_log (&quot;%s(): could not find level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, i);
" ]

	node [ id 1481 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
i = i + 1;
" ]



# function number 55
	node [ id 1482 graphics [ fill "#ffffff" ] label "rhp_numberofcrossings ()
ENTRY" ]

	node [ id 1483 graphics [ fill "#ffffff" ] label "rhp_numberofcrossings ()
EXIT" ]

	node [ id 1484 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spnb = 0B;
is = 0B;
i = 1;
crossings = 0;
rhp_nlevels.204_1 = rhp_nlevels;
if (rhp_nlevels.204_1 &lt;= 1)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1485 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_nlevels.205_2 = rhp_nlevels;
rhp_log (&quot;%s(): graph has no edge crossings because low number of levels which is %d\n&quot;, &amp;__FUNCTION__, rhp_nlevels.205_2);
D.4844 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 1486 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_number_of_edges.206_3 = rhp_number_of_edges;
if (rhp_number_of_edges.206_3 &lt;= 1)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 1487 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_number_of_edges.207_4 = rhp_number_of_edges;
rhp_log (&quot;%s(): graph has no edge crossings because low number of edge which is %d\n&quot;, &amp;__FUNCTION__, rhp_number_of_edges.207_4);
D.4844 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 1488 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
i = 1;
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1489 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
rhp_number_of_edges.210_10 = rhp_number_of_edges;
rhp_nlevels.211_11 = rhp_nlevels;
rhp_log (&quot;%s(): graph has %li edge crossings in %d levels and %d edges\n&quot;, &amp;__FUNCTION__, crossings, rhp_nlevels.211_11, rhp_number_of_edges.210_10);
D.4844 = crossings;
" ]

	node [ id 1490 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
&lt;L10&gt;:
return D.4844;
" ]

	edge [ source 1482 target 1484 graphics [ fill "#0000ff" ] ] 
	edge [ source 1484 target 1485 graphics [ fill "#000000" ] ] 
	edge [ source 1484 target 1486 graphics [ fill "#000000" ] ] 
	edge [ source 1485 target 1490 graphics [ fill "#0000ff" ] ] 
	edge [ source 1486 target 1487 graphics [ fill "#000000" ] ] 
	edge [ source 1486 target 1488 graphics [ fill "#000000" ] ] 
	edge [ source 1487 target 1490 graphics [ fill "#0000ff" ] ] 
	edge [ source 1488 target 1477 graphics [ fill "#0000ff" ] ] 
	edge [ source 1478 target 1479 graphics [ fill "#000000" ] ] 
	edge [ source 1478 target 1480 graphics [ fill "#000000" ] ] 
	edge [ source 1479 target 1481 graphics [ fill "#0000ff" ] ] 
	edge [ source 1480 target 1481 graphics [ fill "#0000ff" ] ] 
	edge [ source 1481 target 1477 graphics [ fill "#0000ff" ] ] 
	edge [ source 1477 target 1478 graphics [ fill "#000000" ] ] 
	edge [ source 1477 target 1489 graphics [ fill "#000000" ] ] 
	edge [ source 1489 target 1490 graphics [ fill "#0000ff" ] ] 
	edge [ source 1490 target 1483 graphics [ fill "#000000" ] ] 
	node [ id 1505 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
rhp_nlevels.228_48 = rhp_nlevels;
if (level &lt; rhp_nlevels.228_48)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 1506 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
_25 = (long long int) level;
rhp_sp_layers.224_26 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.224_26, _25);
if (spn == 0B)
  goto &lt;bb 8&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 1507 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
rhp_sp_layers.225_27 = rhp_sp_layers;
rhp_log (&quot;%s(): could not get data for level %d in sp_layers=%p shouldnothappen!\n&quot;, &amp;__FUNCTION__, level, rhp_sp_layers.225_27);
// predicted unlikely by continue predictor.
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1508 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
_28 = spn-&gt;value;
rl = (struct rhplevel *) _28;
rhp_best_crossings_order.226_29 = rhp_best_crossings_order;
_30 = rhp_best_crossings_order.226_29-&gt;num_nodes_on_layer;
_31 = (long unsigned int) level;
_32 = _31 * 4;
_33 = _30 + _32;
_34 = rl-&gt;number_of_nodes;
*_33 = _34;
_35 = rl-&gt;number_of_nodes;
if (_35 != 0)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1509 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
level = level + 1;
" ]

	node [ id 1510 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
_36 = rl-&gt;number_of_nodes;
_37 = (long unsigned int) _36;
_38 = _37 * 8;
rhp_best_crossings_order.227_39 = rhp_best_crossings_order;
_40 = rhp_best_crossings_order.227_39-&gt;node_ptr_on_layer;
_41 = (long unsigned int) level;
_42 = _41 * 8;
_43 = _40 + _42;
_44 = rhp_malloc (_38, &amp;__FUNCTION__, 3434);
*_43 = _44;
_45 = rl-&gt;number_of_nodes;
_46 = (long unsigned int) _45;
_47 = _46 * 8;
tb = tb + _47;
" ]



# function number 56
	node [ id 1511 graphics [ fill "#ffffff" ] label "rhp_order_init ()
ENTRY" ]

	node [ id 1512 graphics [ fill "#ffffff" ] label "rhp_order_init ()
EXIT" ]

	node [ id 1513 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
rl = 0B;
level = 0;
tb = 0;
rhp_nlevels.212_1 = rhp_nlevels;
rhp_log (&quot;%s(): rhp_nlevels is %d\n&quot;, &amp;__FUNCTION__, rhp_nlevels.212_1);
_2 = rhp_malloc (24, &amp;__FUNCTION__, 3388);
rhp_best_crossings_order = _2;
tb = tb + 24;
rhp_best_crossings_order.213_3 = rhp_best_crossings_order;
rhp_nlevels.214_4 = rhp_nlevels;
rhp_best_crossings_order.213_3-&gt;num_layers = rhp_nlevels.214_4;
rhp_nlevels.215_5 = rhp_nlevels;
_6 = (long unsigned int) rhp_nlevels.215_5;
_7 = _6 * 4;
rhp_best_crossings_order.216_8 = rhp_best_crossings_order;
_9 = rhp_malloc (_7, &amp;__FUNCTION__, 3395);
rhp_best_crossings_order.216_8-&gt;num_nodes_on_layer = _9;
rhp_nlevels.217_10 = rhp_nlevels;
_11 = (long unsigned int) rhp_nlevels.217_10;
_12 = _11 * 4;
tb = tb + _12;
rhp_nlevels.218_13 = rhp_nlevels;
_14 = (long unsigned int) rhp_nlevels.218_13;
_15 = _14 * 8;
rhp_best_crossings_order.219_16 = rhp_best_crossings_order;
_17 = rhp_malloc (_15, &amp;__FUNCTION__, 3399);
rhp_best_crossings_order.219_16-&gt;node_ptr_on_layer = _17;
rhp_nlevels.220_18 = rhp_nlevels;
_19 = (long unsigned int) rhp_nlevels.220_18;
_20 = _19 * 8;
tb = tb + _20;
rhp_sp_layers.221_21 = rhp_sp_layers;
_22 = rhp_sp_has_data (rhp_sp_layers.221_21);
if (_22 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 1514 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_nlevels.222_23 = rhp_nlevels;
if (rhp_nlevels.222_23 &gt; 1)
  goto &lt;bb 4&gt;; [INV]
else
  goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 1515 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_nlevels.223_24 = rhp_nlevels;
rhp_log (&quot;%s(): there is no level data for %d levels shouldnothappen!\n&quot;, &amp;__FUNCTION__, rhp_nlevels.223_24);
" ]

	node [ id 1516 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 1517 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
level = 0;
goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 1518 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
rhp_save_order ();
tb.229_49 = (long long int) tb;
rhp_log (&quot;%s(): using %lu bytes for the order data\n&quot;, &amp;__FUNCTION__, tb.229_49);
" ]

	node [ id 1519 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
&lt;L12&gt;:
return;
" ]

	edge [ source 1511 target 1513 graphics [ fill "#0000ff" ] ] 
	edge [ source 1513 target 1514 graphics [ fill "#000000" ] ] 
	edge [ source 1513 target 1517 graphics [ fill "#000000" ] ] 
	edge [ source 1514 target 1515 graphics [ fill "#000000" ] ] 
	edge [ source 1514 target 1516 graphics [ fill "#000000" ] ] 
	edge [ source 1515 target 1516 graphics [ fill "#0000ff" ] ] 
	edge [ source 1516 target 1519 graphics [ fill "#0000ff" ] ] 
	edge [ source 1517 target 1505 graphics [ fill "#0000ff" ] ] 
	edge [ source 1506 target 1507 graphics [ fill "#000000" ] ] 
	edge [ source 1506 target 1508 graphics [ fill "#000000" ] ] 
	edge [ source 1507 target 1509 graphics [ fill "#0000ff" ] ] 
	edge [ source 1508 target 1510 graphics [ fill "#000000" ] ] 
	edge [ source 1508 target 1509 graphics [ fill "#000000" ] ] 
	edge [ source 1510 target 1509 graphics [ fill "#0000ff" ] ] 
	edge [ source 1509 target 1505 graphics [ fill "#0000ff" ] ] 
	edge [ source 1505 target 1506 graphics [ fill "#000000" ] ] 
	edge [ source 1505 target 1518 graphics [ fill "#000000" ] ] 
	edge [ source 1518 target 1519 graphics [ fill "#0000ff" ] ] 
	edge [ source 1519 target 1512 graphics [ fill "#000000" ] ] 
	node [ id 1535 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
_20 = rl-&gt;number_of_nodes;
if (i &lt; _20)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1536 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_6 = rl-&gt;nodes;
_7 = (long unsigned int) i;
_8 = _7 * 8;
_9 = _6 + _8;
nd = *_9;
rhp_best_crossings_order.233_10 = rhp_best_crossings_order;
_11 = rhp_best_crossings_order.233_10-&gt;node_ptr_on_layer;
_12 = (long unsigned int) level;
_13 = _12 * 8;
_14 = _11 + _13;
_15 = *_14;
_16 = (long unsigned int) i;
_17 = _16 * 8;
_18 = _15 + _17;
*_18 = nd;
_19 = nd-&gt;innum;
rhp_log (&quot; %d&quot;, _19);
i = i + 1;
" ]

	node [ id 1537 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
rhp_nlevels.234_21 = rhp_nlevels;
if (level &lt; rhp_nlevels.234_21)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1538 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
_3 = (long long int) level;
rhp_sp_layers.232_4 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.232_4, _3);
if (spn == 0B)
  goto &lt;bb 4&gt;; [INV]
else
  goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 1539 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_log (&quot;%s(): could not get data for level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
// predicted unlikely by continue predictor.
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 1540 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
_5 = spn-&gt;value;
rl = (struct rhplevel *) _5;
rhp_log (&quot;%s(): level %d has nodes:&quot;, &amp;__FUNCTION__, level);
i = 0;
goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 1541 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
level = level + 1;
" ]

	node [ id 1542 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
rhp_log (&quot;\n&quot;);
" ]



# function number 57
	node [ id 1543 graphics [ fill "#ffffff" ] label "rhp_save_order ()
ENTRY" ]

	node [ id 1544 graphics [ fill "#ffffff" ] label "rhp_save_order ()
EXIT" ]

	node [ id 1545 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
rl = 0B;
nd = 0B;
level = 0;
i = 0;
rhp_best_crossings_order.230_1 = rhp_best_crossings_order;
rhp_nlevels.231_2 = rhp_nlevels;
rhp_best_crossings_order.230_1-&gt;num_layers = rhp_nlevels.231_2;
level = 0;
goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1546 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
" ]

	node [ id 1547 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
&lt;L9&gt;:
return;
" ]

	edge [ source 1543 target 1545 graphics [ fill "#0000ff" ] ] 
	edge [ source 1545 target 1537 graphics [ fill "#0000ff" ] ] 
	edge [ source 1538 target 1539 graphics [ fill "#000000" ] ] 
	edge [ source 1538 target 1540 graphics [ fill "#000000" ] ] 
	edge [ source 1539 target 1541 graphics [ fill "#0000ff" ] ] 
	edge [ source 1540 target 1535 graphics [ fill "#0000ff" ] ] 
	edge [ source 1536 target 1535 graphics [ fill "#0000ff" ] ] 
	edge [ source 1535 target 1536 graphics [ fill "#000000" ] ] 
	edge [ source 1535 target 1542 graphics [ fill "#000000" ] ] 
	edge [ source 1542 target 1541 graphics [ fill "#0000ff" ] ] 
	edge [ source 1541 target 1537 graphics [ fill "#0000ff" ] ] 
	edge [ source 1537 target 1538 graphics [ fill "#000000" ] ] 
	edge [ source 1537 target 1546 graphics [ fill "#000000" ] ] 
	edge [ source 1546 target 1547 graphics [ fill "#0000ff" ] ] 
	edge [ source 1547 target 1544 graphics [ fill "#000000" ] ] 
	node [ id 1561 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
_19 = rl-&gt;number_of_nodes;
if (i &lt; _19)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1562 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_best_crossings_order.238_6 = rhp_best_crossings_order;
_7 = rhp_best_crossings_order.238_6-&gt;node_ptr_on_layer;
_8 = (long unsigned int) level;
_9 = _8 * 8;
_10 = _7 + _9;
_11 = *_10;
_12 = (long unsigned int) i;
_13 = _12 * 8;
_14 = _11 + _13;
nd = *_14;
_15 = rl-&gt;nodes;
_16 = (long unsigned int) i;
_17 = _16 * 8;
_18 = _15 + _17;
*_18 = nd;
nd-&gt;position = i;
i = i + 1;
" ]

	node [ id 1563 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_nlevels.239_20 = rhp_nlevels;
if (level &lt; rhp_nlevels.239_20)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1564 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
_3 = (long long int) level;
rhp_sp_layers.237_4 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.237_4, _3);
if (spn == 0B)
  goto &lt;bb 4&gt;; [INV]
else
  goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 1565 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_log (&quot;%s(): could not get data for level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
// predicted unlikely by continue predictor.
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1566 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
_5 = spn-&gt;value;
rl = (struct rhplevel *) _5;
i = 0;
goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 1567 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
level = level + 1;
" ]



# function number 58
	node [ id 1568 graphics [ fill "#ffffff" ] label "rhp_restore_order ()
ENTRY" ]

	node [ id 1569 graphics [ fill "#ffffff" ] label "rhp_restore_order ()
EXIT" ]

	node [ id 1570 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
rl = 0B;
nd = 0B;
level = 0;
i = 0;
rhp_log (&quot;%s(): \n&quot;, &amp;__FUNCTION__);
rhp_best_crossings_order.235_1 = rhp_best_crossings_order;
rhp_nlevels.236_2 = rhp_nlevels;
rhp_best_crossings_order.235_1-&gt;num_layers = rhp_nlevels.236_2;
level = 0;
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 1571 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
" ]

	node [ id 1572 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
&lt;L9&gt;:
return;
" ]

	edge [ source 1568 target 1570 graphics [ fill "#0000ff" ] ] 
	edge [ source 1570 target 1563 graphics [ fill "#0000ff" ] ] 
	edge [ source 1564 target 1565 graphics [ fill "#000000" ] ] 
	edge [ source 1564 target 1566 graphics [ fill "#000000" ] ] 
	edge [ source 1565 target 1567 graphics [ fill "#0000ff" ] ] 
	edge [ source 1566 target 1561 graphics [ fill "#0000ff" ] ] 
	edge [ source 1562 target 1561 graphics [ fill "#0000ff" ] ] 
	edge [ source 1561 target 1562 graphics [ fill "#000000" ] ] 
	edge [ source 1561 target 1567 graphics [ fill "#000000" ] ] 
	edge [ source 1567 target 1563 graphics [ fill "#0000ff" ] ] 
	edge [ source 1563 target 1564 graphics [ fill "#000000" ] ] 
	edge [ source 1563 target 1571 graphics [ fill "#000000" ] ] 
	edge [ source 1571 target 1572 graphics [ fill "#0000ff" ] ] 
	edge [ source 1572 target 1569 graphics [ fill "#000000" ] ] 
	node [ id 1585 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_nlevels.241_2 = rhp_nlevels;
_3 = rhp_nlevels.241_2 + -2;
_4 = rhp_barycenterupsweep (1, _3);
if (_4 != 0)
  goto &lt;bb 4&gt;; [INV]
else
  goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 1586 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_nlevels.242_5 = rhp_nlevels;
_6 = rhp_nlevels.242_5 + -2;
_7 = rhp_barycenterdownsweep (1, _6);
if (_7 != 0)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 1587 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
_8 = rhp_terminate ();
if (_8 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]



# function number 59
	node [ id 1588 graphics [ fill "#ffffff" ] label "rhp_barycenter ()
ENTRY" ]

	node [ id 1589 graphics [ fill "#ffffff" ] label "rhp_barycenter ()
EXIT" ]

	node [ id 1590 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
redu = 0;
rhp_iter = 0;
rhp_maxiter = 255;
rhp_start_crossings.240_1 = rhp_start_crossings;
rhp_log (&quot;%s(): starting barycenter with %li edge crossings at start\n&quot;, &amp;__FUNCTION__, rhp_start_crossings.240_1);
" ]

	node [ id 1591 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 1592 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 1593 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
rhp_start_crossings.243_9 = rhp_start_crossings;
rhp_crossings.244_10 = rhp_crossings;
rhp_log (&quot;%s(): ending barycenter with %li edge crossings and started with %li edge crossings at start\n&quot;, &amp;__FUNCTION__, rhp_crossings.244_10, rhp_start_crossings.243_9);
rhp_start_crossings.245_11 = rhp_start_crossings;
if (rhp_start_crossings.245_11 != 0)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1594 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_crossings.246_12 = rhp_crossings;
_13 = rhp_crossings.246_12 * 100;
rhp_start_crossings.247_14 = rhp_start_crossings;
redu = _13 / rhp_start_crossings.247_14;
redu = 100 - redu;
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1595 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
redu = 0;
" ]

	node [ id 1596 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
rhp_crossings.248_15 = rhp_crossings;
rhp_start_crossings.249_16 = rhp_start_crossings;
rhp_log (&quot;%s(): reduced edge crossings with %li percent from %li-&gt;%li\n&quot;, &amp;__FUNCTION__, redu, rhp_start_crossings.249_16, rhp_crossings.248_15);
" ]

	node [ id 1597 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
&lt;L9&gt;:
return;
" ]

	edge [ source 1588 target 1590 graphics [ fill "#0000ff" ] ] 
	edge [ source 1590 target 1585 graphics [ fill "#0000ff" ] ] 
	edge [ source 1585 target 1591 graphics [ fill "#000000" ] ] 
	edge [ source 1585 target 1586 graphics [ fill "#000000" ] ] 
	edge [ source 1591 target 1597 graphics [ fill "#0000ff" ] ] 
	edge [ source 1586 target 1592 graphics [ fill "#000000" ] ] 
	edge [ source 1586 target 1587 graphics [ fill "#000000" ] ] 
	edge [ source 1592 target 1597 graphics [ fill "#0000ff" ] ] 
	edge [ source 1587 target 1585 graphics [ fill "#0000ff" ] ] 
	edge [ source 1587 target 1593 graphics [ fill "#000000" ] ] 
	edge [ source 1593 target 1594 graphics [ fill "#000000" ] ] 
	edge [ source 1593 target 1595 graphics [ fill "#000000" ] ] 
	edge [ source 1594 target 1596 graphics [ fill "#0000ff" ] ] 
	edge [ source 1595 target 1596 graphics [ fill "#0000ff" ] ] 
	edge [ source 1596 target 1597 graphics [ fill "#0000ff" ] ] 
	edge [ source 1597 target 1589 graphics [ fill "#000000" ] ] 


# function number 60
	node [ id 1611 graphics [ fill "#ffffff" ] label "rhp_terminate ()
ENTRY" ]

	node [ id 1612 graphics [ fill "#ffffff" ] label "rhp_terminate ()
EXIT" ]

	node [ id 1613 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
redu = 0;
rhp_cur_crossings = 0;
status = 0;
better = 0;
rhp_cur_crossings = rhp_numberofcrossings ();
rhp_iter.250_1 = rhp_iter;
_2 = rhp_iter.250_1 + 1;
rhp_iter = _2;
rhp_crossings.251_3 = rhp_crossings;
rhp_log (&quot;%s(): changed from %li to %li crossings\n&quot;, &amp;__FUNCTION__, rhp_crossings.251_3, rhp_cur_crossings);
rhp_crossings.252_4 = rhp_crossings;
if (rhp_cur_crossings &lt; rhp_crossings.252_4)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1614 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
better = 1;
rhp_improvements.253_5 = rhp_improvements;
_6 = rhp_improvements.253_5 + 1;
rhp_improvements = _6;
goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 1615 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
better = 0;
rhp_notimprovements.254_7 = rhp_notimprovements;
_8 = rhp_notimprovements.254_7 + 1;
rhp_notimprovements = _8;
" ]

	node [ id 1616 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_getlayoutdata.255_9 = rhp_getlayoutdata;
if (rhp_getlayoutdata.255_9 != 0B)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1617 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_crossings.256_10 = rhp_crossings;
if (rhp_crossings.256_10 != 0)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1618 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
_11 = rhp_cur_crossings * 100;
rhp_crossings.257_12 = rhp_crossings;
_13 = _11 / rhp_crossings.257_12;
redu = (uint64_t) _13;
redu = 100 - redu;
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 1619 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
redu = 0;
" ]

	node [ id 1620 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
rhp_getlayoutdata.258_14 = rhp_getlayoutdata;
rhp_notimprovements.259_15 = rhp_notimprovements;
rhp_improvements.260_16 = rhp_improvements;
rhp_crossings.261_17 = rhp_crossings;
rhp_crossings.262_18 = (long unsigned int) rhp_crossings.261_17;
rhp_cur_crossings.263_19 = (long unsigned int) rhp_cur_crossings;
rhp_maxiter.264_20 = rhp_maxiter;
rhp_iter.265_21 = rhp_iter;
status = rhp_getlayoutdata.258_14 (rhp_iter.265_21, rhp_maxiter.264_20, rhp_cur_crossings.263_19, rhp_crossings.262_18, redu, better, rhp_improvements.260_16, rhp_notimprovements.259_15);
if (status != 0)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1621 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
rhp_log (&quot;%s(): stop barycenter because status %d from callback routine at %lu crossings\n&quot;, &amp;__FUNCTION__, status, rhp_cur_crossings);
rhp_save_order ();
rhp_crossings = rhp_cur_crossings;
D.4884 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 26&gt;; [INV]
" ]

	node [ id 1622 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
if (rhp_cur_crossings == 0)
  goto &lt;bb 13&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 1623 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
rhp_crossings.266_22 = rhp_crossings;
if (rhp_crossings.266_22 == 0)
  goto &lt;bb 13&gt;; [INV]
else
  goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 1624 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
rhp_crossings.267_23 = rhp_crossings;
rhp_log (&quot;%s(): stop barycenter because of no edge crossings cur=%lu old=%lu\n&quot;, &amp;__FUNCTION__, rhp_cur_crossings, rhp_crossings.267_23);
rhp_save_order ();
rhp_crossings = rhp_cur_crossings;
D.4884 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 26&gt;; [INV]
" ]

	node [ id 1625 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
rhp_crossings.268_24 = rhp_crossings;
if (rhp_cur_crossings &lt; rhp_crossings.268_24)
  goto &lt;bb 15&gt;; [INV]
else
  goto &lt;bb 20&gt;; [INV]
" ]

	node [ id 1626 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
rhp_save_order ();
rhp_crossings = rhp_cur_crossings;
rhp_crossings.269_25 = rhp_crossings;
if (rhp_crossings.269_25 == 0)
  goto &lt;bb 16&gt;; [INV]
else
  goto &lt;bb 17&gt;; [INV]
" ]

	node [ id 1627 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
D.4884 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 26&gt;; [INV]
" ]

	node [ id 1628 graphics [ fill "#d3d3d3" ] label "&lt;bb 17&gt;:
rhp_iter.270_26 = rhp_iter;
rhp_maxiter.271_27 = rhp_maxiter;
if (rhp_iter.270_26 &gt; rhp_maxiter.271_27)
  goto &lt;bb 18&gt;; [INV]
else
  goto &lt;bb 19&gt;; [INV]
" ]

	node [ id 1629 graphics [ fill "#d3d3d3" ] label "&lt;bb 18&gt;:
D.4884 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 26&gt;; [INV]
" ]

	node [ id 1630 graphics [ fill "#d3d3d3" ] label "&lt;bb 19&gt;:
D.4884 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 26&gt;; [INV]
" ]

	node [ id 1631 graphics [ fill "#d3d3d3" ] label "&lt;bb 20&gt;:
rhp_crossings.272_28 = rhp_crossings;
if (rhp_cur_crossings != rhp_crossings.272_28)
  goto &lt;bb 21&gt;; [INV]
else
  goto &lt;bb 22&gt;; [INV]
" ]

	node [ id 1632 graphics [ fill "#d3d3d3" ] label "&lt;bb 21&gt;:
rhp_restore_order ();
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 1633 graphics [ fill "#d3d3d3" ] label "&lt;bb 22&gt;:
rhp_save_order ();
" ]

	node [ id 1634 graphics [ fill "#d3d3d3" ] label "&lt;bb 23&gt;:
rhp_iter.273_29 = rhp_iter;
rhp_maxiter.274_30 = rhp_maxiter;
if (rhp_iter.273_29 &gt; rhp_maxiter.274_30)
  goto &lt;bb 24&gt;; [INV]
else
  goto &lt;bb 25&gt;; [INV]
" ]

	node [ id 1635 graphics [ fill "#d3d3d3" ] label "&lt;bb 24&gt;:
D.4884 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 26&gt;; [INV]
" ]

	node [ id 1636 graphics [ fill "#d3d3d3" ] label "&lt;bb 25&gt;:
D.4884 = 0;
// predicted unlikely by early return (on trees) predictor.
" ]

	node [ id 1637 graphics [ fill "#d3d3d3" ] label "&lt;bb 26&gt;:
&lt;L24&gt;:
return D.4884;
" ]

	edge [ source 1611 target 1613 graphics [ fill "#0000ff" ] ] 
	edge [ source 1613 target 1614 graphics [ fill "#000000" ] ] 
	edge [ source 1613 target 1615 graphics [ fill "#000000" ] ] 
	edge [ source 1614 target 1616 graphics [ fill "#0000ff" ] ] 
	edge [ source 1615 target 1616 graphics [ fill "#0000ff" ] ] 
	edge [ source 1616 target 1617 graphics [ fill "#000000" ] ] 
	edge [ source 1616 target 1622 graphics [ fill "#000000" ] ] 
	edge [ source 1617 target 1618 graphics [ fill "#000000" ] ] 
	edge [ source 1617 target 1619 graphics [ fill "#000000" ] ] 
	edge [ source 1618 target 1620 graphics [ fill "#0000ff" ] ] 
	edge [ source 1619 target 1620 graphics [ fill "#0000ff" ] ] 
	edge [ source 1620 target 1621 graphics [ fill "#000000" ] ] 
	edge [ source 1620 target 1622 graphics [ fill "#000000" ] ] 
	edge [ source 1621 target 1637 graphics [ fill "#0000ff" ] ] 
	edge [ source 1622 target 1624 graphics [ fill "#000000" ] ] 
	edge [ source 1622 target 1623 graphics [ fill "#000000" ] ] 
	edge [ source 1623 target 1624 graphics [ fill "#000000" ] ] 
	edge [ source 1623 target 1625 graphics [ fill "#000000" ] ] 
	edge [ source 1624 target 1637 graphics [ fill "#0000ff" ] ] 
	edge [ source 1625 target 1626 graphics [ fill "#000000" ] ] 
	edge [ source 1625 target 1631 graphics [ fill "#000000" ] ] 
	edge [ source 1626 target 1627 graphics [ fill "#000000" ] ] 
	edge [ source 1626 target 1628 graphics [ fill "#000000" ] ] 
	edge [ source 1627 target 1637 graphics [ fill "#0000ff" ] ] 
	edge [ source 1628 target 1629 graphics [ fill "#000000" ] ] 
	edge [ source 1628 target 1630 graphics [ fill "#000000" ] ] 
	edge [ source 1629 target 1637 graphics [ fill "#0000ff" ] ] 
	edge [ source 1630 target 1637 graphics [ fill "#0000ff" ] ] 
	edge [ source 1631 target 1632 graphics [ fill "#000000" ] ] 
	edge [ source 1631 target 1633 graphics [ fill "#000000" ] ] 
	edge [ source 1632 target 1634 graphics [ fill "#0000ff" ] ] 
	edge [ source 1633 target 1634 graphics [ fill "#0000ff" ] ] 
	edge [ source 1634 target 1635 graphics [ fill "#000000" ] ] 
	edge [ source 1634 target 1636 graphics [ fill "#000000" ] ] 
	edge [ source 1635 target 1637 graphics [ fill "#0000ff" ] ] 
	edge [ source 1636 target 1637 graphics [ fill "#0000ff" ] ] 
	edge [ source 1637 target 1612 graphics [ fill "#000000" ] ] 


# function number 61
	node [ id 1665 graphics [ fill "#ffffff" ] label "rhp_end_of_iteration ()
ENTRY" ]

	node [ id 1666 graphics [ fill "#ffffff" ] label "rhp_end_of_iteration ()
EXIT" ]

	node [ id 1667 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
D.4900 = 0;
" ]

	node [ id 1668 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
&lt;L0&gt;:
return D.4900;
" ]

	edge [ source 1665 target 1667 graphics [ fill "#0000ff" ] ] 
	edge [ source 1667 target 1668 graphics [ fill "#0000ff" ] ] 
	edge [ source 1668 target 1666 graphics [ fill "#000000" ] ] 
	node [ id 1673 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
if (layer &lt; hilevel)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 1674 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
nadj = 0;
nadj = rhp_barycenterweights (layer, 0);
if (nadj != 0)
  goto &lt;bb 4&gt;; [INV]
else
  goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 1675 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_barycenterweights_adjust (layer, 0);
" ]

	node [ id 1676 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_layersort (layer);
rhp_updatecrossingsforlayer (layer);
_1 = rhp_end_of_iteration ();
if (_1 != 0)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 1677 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
layer = layer + 1;
" ]



# function number 62
	node [ id 1678 graphics [ fill "#ffffff" ] label "rhp_barycenterupsweep ()
ENTRY" ]

	node [ id 1679 graphics [ fill "#ffffff" ] label "rhp_barycenterupsweep ()
EXIT" ]

	node [ id 1680 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
layer = 0;
nadj = 0;
layer = lowlevel;
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1681 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
D.4906 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1682 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
D.4906 = 0;
" ]

	node [ id 1683 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
&lt;L7&gt;:
return D.4906;
" ]

	edge [ source 1678 target 1680 graphics [ fill "#0000ff" ] ] 
	edge [ source 1680 target 1673 graphics [ fill "#0000ff" ] ] 
	edge [ source 1674 target 1675 graphics [ fill "#000000" ] ] 
	edge [ source 1674 target 1676 graphics [ fill "#000000" ] ] 
	edge [ source 1675 target 1676 graphics [ fill "#0000ff" ] ] 
	edge [ source 1676 target 1681 graphics [ fill "#000000" ] ] 
	edge [ source 1676 target 1677 graphics [ fill "#000000" ] ] 
	edge [ source 1681 target 1683 graphics [ fill "#0000ff" ] ] 
	edge [ source 1677 target 1673 graphics [ fill "#0000ff" ] ] 
	edge [ source 1673 target 1674 graphics [ fill "#000000" ] ] 
	edge [ source 1673 target 1682 graphics [ fill "#000000" ] ] 
	edge [ source 1682 target 1683 graphics [ fill "#0000ff" ] ] 
	edge [ source 1683 target 1679 graphics [ fill "#000000" ] ] 
	node [ id 1695 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
_2 = lowlevel + -1;
if (layer &gt;= _2)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 1696 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
nadj = 0;
nadj = rhp_barycenterweights (layer, 1);
if (nadj != 0)
  goto &lt;bb 4&gt;; [INV]
else
  goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 1697 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_barycenterweights_adjust (layer, 1);
" ]

	node [ id 1698 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_layersort (layer);
rhp_updatecrossingsforlayer (layer);
_1 = rhp_end_of_iteration ();
if (_1 != 0)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 1699 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
layer = layer + -1;
" ]



# function number 63
	node [ id 1700 graphics [ fill "#ffffff" ] label "rhp_barycenterdownsweep ()
ENTRY" ]

	node [ id 1701 graphics [ fill "#ffffff" ] label "rhp_barycenterdownsweep ()
EXIT" ]

	node [ id 1702 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
layer = 0;
nadj = 0;
layer = hilevel;
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1703 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
D.4912 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1704 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
D.4912 = 0;
" ]

	node [ id 1705 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
&lt;L7&gt;:
return D.4912;
" ]

	edge [ source 1700 target 1702 graphics [ fill "#0000ff" ] ] 
	edge [ source 1702 target 1695 graphics [ fill "#0000ff" ] ] 
	edge [ source 1696 target 1697 graphics [ fill "#000000" ] ] 
	edge [ source 1696 target 1698 graphics [ fill "#000000" ] ] 
	edge [ source 1697 target 1698 graphics [ fill "#0000ff" ] ] 
	edge [ source 1698 target 1703 graphics [ fill "#000000" ] ] 
	edge [ source 1698 target 1699 graphics [ fill "#000000" ] ] 
	edge [ source 1703 target 1705 graphics [ fill "#0000ff" ] ] 
	edge [ source 1699 target 1695 graphics [ fill "#0000ff" ] ] 
	edge [ source 1695 target 1696 graphics [ fill "#000000" ] ] 
	edge [ source 1695 target 1704 graphics [ fill "#000000" ] ] 
	edge [ source 1704 target 1705 graphics [ fill "#0000ff" ] ] 
	edge [ source 1705 target 1701 graphics [ fill "#000000" ] ] 
	node [ id 1717 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
_16 = rl-&gt;number_of_nodes;
if (i &lt; _16)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 1718 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
_5 = rl-&gt;nodes;
_6 = (long unsigned int) i;
_7 = _6 * 8;
_8 = _5 + _7;
_9 = *_8;
rhp_node_weight (_9, orientation);
_10 = rl-&gt;nodes;
_11 = (long unsigned int) i;
_12 = _11 * 8;
_13 = _10 + _12;
_14 = *_13;
_15 = _14-&gt;weight;
if (_15 == -1)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 1719 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
n_node_adjust = n_node_adjust + 1;
" ]

	node [ id 1720 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
i = i + 1;
" ]



# function number 64
	node [ id 1721 graphics [ fill "#ffffff" ] label "rhp_barycenterweights ()
ENTRY" ]

	node [ id 1722 graphics [ fill "#ffffff" ] label "rhp_barycenterweights ()
EXIT" ]

	node [ id 1723 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
rl = 0B;
i = 0;
n_node_adjust = 0;
_1 = (long long int) level;
rhp_sp_layers.275_2 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.275_2, _1);
if (spn == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1724 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): could not find data for level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
D.4916 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 1725 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_3 = spn-&gt;value;
rl = (struct rhplevel *) _3;
_4 = rl-&gt;number_of_nodes;
rhp_log (&quot;%s(): weights for %d nodes in level %d mode %d\n&quot;, &amp;__FUNCTION__, _4, level, orientation);
n_node_adjust = 0;
i = 0;
goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1726 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
if (n_node_adjust != 0)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1727 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
_17 = rl-&gt;number_of_nodes;
rhp_iter.276_18 = rhp_iter;
rhp_log (&quot;%s(): iteration %d %d nodes need adjust from %d nodes in level %d mode %d\n&quot;, &amp;__FUNCTION__, rhp_iter.276_18, n_node_adjust, _17, level, orientation);
" ]

	node [ id 1728 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
rl-&gt;number_adjustments = n_node_adjust;
D.4916 = n_node_adjust;
" ]

	node [ id 1729 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
&lt;L9&gt;:
return D.4916;
" ]

	edge [ source 1721 target 1723 graphics [ fill "#0000ff" ] ] 
	edge [ source 1723 target 1724 graphics [ fill "#000000" ] ] 
	edge [ source 1723 target 1725 graphics [ fill "#000000" ] ] 
	edge [ source 1724 target 1729 graphics [ fill "#0000ff" ] ] 
	edge [ source 1725 target 1717 graphics [ fill "#0000ff" ] ] 
	edge [ source 1718 target 1719 graphics [ fill "#000000" ] ] 
	edge [ source 1718 target 1720 graphics [ fill "#000000" ] ] 
	edge [ source 1719 target 1720 graphics [ fill "#0000ff" ] ] 
	edge [ source 1720 target 1717 graphics [ fill "#0000ff" ] ] 
	edge [ source 1717 target 1718 graphics [ fill "#000000" ] ] 
	edge [ source 1717 target 1726 graphics [ fill "#000000" ] ] 
	edge [ source 1726 target 1727 graphics [ fill "#000000" ] ] 
	edge [ source 1726 target 1728 graphics [ fill "#000000" ] ] 
	edge [ source 1727 target 1728 graphics [ fill "#0000ff" ] ] 
	edge [ source 1728 target 1729 graphics [ fill "#0000ff" ] ] 
	edge [ source 1729 target 1722 graphics [ fill "#000000" ] ] 
	node [ id 1743 graphics [ fill "#d3d3d3" ] label "&lt;bb 22&gt;:
_51 = rl-&gt;number_of_nodes;
if (i &lt; _51)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 1744 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
_5 = rl-&gt;nodes;
_6 = (long unsigned int) i;
_7 = _6 * 8;
_8 = _5 + _7;
_9 = *_8;
_10 = _9-&gt;weight;
if (_10 == -1)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 21&gt;; [INV]
" ]

	node [ id 1745 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_11 = rl-&gt;nodes;
_12 = (long unsigned int) i;
_13 = _12 * 8;
_14 = _11 + _13;
node = *_14;
rhp_adjustweight.278_15 = rhp_adjustweight;
if (rhp_adjustweight.278_15 != 0)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 17&gt;; [INV]
" ]

	node [ id 1746 graphics [ fill "#d3d3d3" ] label "&lt;bb 21&gt;:
i = i + 1;
" ]

	node [ id 1747 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
number_of_weights = 0;
total_weight = 0;
" ]

	node [ id 1748 graphics [ fill "#d3d3d3" ] label "&lt;bb 17&gt;:
if (i &lt;= 0)
  goto &lt;bb 18&gt;; [INV]
else
  goto &lt;bb 19&gt;; [INV]
" ]

	node [ id 1749 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
if (i &gt; 0)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1750 graphics [ fill "#d3d3d3" ] label "&lt;bb 18&gt;:
node-&gt;weight = 0;
goto &lt;bb 20&gt;; [INV]
" ]

	node [ id 1751 graphics [ fill "#d3d3d3" ] label "&lt;bb 19&gt;:
_43 = rl-&gt;nodes;
_44 = (long unsigned int) i;
_45 = _44 * 8;
_46 = _45 + 18446744073709551608;
_47 = _43 + _46;
_48 = *_47;
_49 = _48-&gt;weight;
node-&gt;weight = _49;
" ]

	node [ id 1752 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
number_of_weights = number_of_weights + 1;
_16 = rl-&gt;nodes;
_17 = (long unsigned int) i;
_18 = _17 * 8;
_19 = _18 + 18446744073709551608;
_20 = _16 + _19;
_21 = *_20;
_22 = _21-&gt;weight;
total_weight = total_weight + _22;
" ]

	node [ id 1753 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
_23 = rl-&gt;number_of_nodes;
_24 = _23 + -1;
if (i &lt; _24)
  goto &lt;bb 11&gt;; [INV]
else
  goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 1754 graphics [ fill "#d3d3d3" ] label "&lt;bb 20&gt;:
_50 = node-&gt;weight;
rhp_log (&quot;%s(): adjusted node[%d] weight from -1 to %d (leftish mode)\n&quot;, &amp;__FUNCTION__, i, _50);
" ]

	node [ id 1755 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
_25 = rl-&gt;nodes;
_26 = (sizetype) i;
_27 = _26 + 1;
_28 = _27 * 8;
_29 = _25 + _28;
_30 = *_29;
_31 = _30-&gt;weight;
if (_31 &gt;= 0)
  goto &lt;bb 12&gt;; [INV]
else
  goto &lt;bb 13&gt;; [INV]
" ]

	node [ id 1756 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
if (number_of_weights &gt; 0)
  goto &lt;bb 14&gt;; [INV]
else
  goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 1757 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
number_of_weights = number_of_weights + 1;
_32 = rl-&gt;nodes;
_33 = (sizetype) i;
_34 = _33 + 1;
_35 = _34 * 8;
_36 = _32 + _35;
_37 = *_36;
_38 = _37-&gt;weight;
total_weight = total_weight + _38;
" ]

	node [ id 1758 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
_39 = total_weight * 100;
node-&gt;weight = _39;
_40 = node-&gt;weight;
_41 = _40 / number_of_weights;
node-&gt;weight = _41;
goto &lt;bb 16&gt;; [INV]
" ]

	node [ id 1759 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
node-&gt;weight = 0;
" ]

	node [ id 1760 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
_42 = node-&gt;weight;
rhp_log (&quot;%s(): adjusted node[%d] weight from -1 to %d (avg mode)\n&quot;, &amp;__FUNCTION__, i, _42);
goto &lt;bb 21&gt;; [INV]
" ]



# function number 65
	node [ id 1761 graphics [ fill "#ffffff" ] label "rhp_barycenterweights_adjust ()
ENTRY" ]

	node [ id 1762 graphics [ fill "#ffffff" ] label "rhp_barycenterweights_adjust ()
EXIT" ]

	node [ id 1763 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
rl = 0B;
node = 0B;
number_of_weights = 0;
total_weight = 0;
i = 0;
_1 = (long long int) level;
rhp_sp_layers.277_2 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.277_2, _1);
if (spn == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1764 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): could not find data for level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 24&gt;; [INV]
" ]

	node [ id 1765 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_3 = spn-&gt;value;
rl = (struct rhplevel *) _3;
_4 = rl-&gt;number_of_nodes;
rhp_log (&quot;%s(): to adjust %d weights for %d nodes in level %d orientation %d\n&quot;, &amp;__FUNCTION__, number_of_weights, _4, level, orientation);
i = 0;
goto &lt;bb 22&gt;; [INV]
" ]

	node [ id 1766 graphics [ fill "#d3d3d3" ] label "&lt;bb 23&gt;:
" ]

	node [ id 1767 graphics [ fill "#d3d3d3" ] label "&lt;bb 24&gt;:
&lt;L24&gt;:
return;
" ]

	edge [ source 1761 target 1763 graphics [ fill "#0000ff" ] ] 
	edge [ source 1763 target 1764 graphics [ fill "#000000" ] ] 
	edge [ source 1763 target 1765 graphics [ fill "#000000" ] ] 
	edge [ source 1764 target 1767 graphics [ fill "#0000ff" ] ] 
	edge [ source 1765 target 1743 graphics [ fill "#0000ff" ] ] 
	edge [ source 1744 target 1745 graphics [ fill "#000000" ] ] 
	edge [ source 1744 target 1746 graphics [ fill "#000000" ] ] 
	edge [ source 1745 target 1747 graphics [ fill "#000000" ] ] 
	edge [ source 1745 target 1748 graphics [ fill "#000000" ] ] 
	edge [ source 1747 target 1749 graphics [ fill "#0000ff" ] ] 
	edge [ source 1749 target 1752 graphics [ fill "#000000" ] ] 
	edge [ source 1749 target 1753 graphics [ fill "#000000" ] ] 
	edge [ source 1752 target 1753 graphics [ fill "#0000ff" ] ] 
	edge [ source 1753 target 1755 graphics [ fill "#000000" ] ] 
	edge [ source 1753 target 1756 graphics [ fill "#000000" ] ] 
	edge [ source 1755 target 1757 graphics [ fill "#000000" ] ] 
	edge [ source 1755 target 1756 graphics [ fill "#000000" ] ] 
	edge [ source 1757 target 1756 graphics [ fill "#0000ff" ] ] 
	edge [ source 1756 target 1758 graphics [ fill "#000000" ] ] 
	edge [ source 1756 target 1759 graphics [ fill "#000000" ] ] 
	edge [ source 1758 target 1760 graphics [ fill "#0000ff" ] ] 
	edge [ source 1759 target 1760 graphics [ fill "#0000ff" ] ] 
	edge [ source 1760 target 1746 graphics [ fill "#0000ff" ] ] 
	edge [ source 1748 target 1750 graphics [ fill "#000000" ] ] 
	edge [ source 1748 target 1751 graphics [ fill "#000000" ] ] 
	edge [ source 1750 target 1754 graphics [ fill "#0000ff" ] ] 
	edge [ source 1751 target 1754 graphics [ fill "#0000ff" ] ] 
	edge [ source 1754 target 1746 graphics [ fill "#0000ff" ] ] 
	edge [ source 1746 target 1743 graphics [ fill "#0000ff" ] ] 
	edge [ source 1743 target 1744 graphics [ fill "#000000" ] ] 
	edge [ source 1743 target 1766 graphics [ fill "#000000" ] ] 
	edge [ source 1766 target 1767 graphics [ fill "#0000ff" ] ] 
	edge [ source 1767 target 1762 graphics [ fill "#000000" ] ] 
	node [ id 1793 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
_23 = node-&gt;up_degree;
if (adj_index &lt; _23)
  goto &lt;bb 10&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 1794 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
_16 = node-&gt;up_edges;
_17 = (long unsigned int) adj_index;
_18 = _17 * 8;
_19 = _16 + _18;
_20 = *_19;
_21 = _20-&gt;up_node;
_22 = _21-&gt;position;
total_of_positions = total_of_positions + _22;
adj_index = adj_index + 1;
" ]

	node [ id 1795 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
_15 = node-&gt;down_degree;
if (adj_index &lt; _15)
  goto &lt;bb 6&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1796 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_8 = node-&gt;down_edges;
_9 = (long unsigned int) adj_index;
_10 = _9 * 8;
_11 = _8 + _10;
_12 = *_11;
_13 = _12-&gt;down_node;
_14 = _13-&gt;position;
total_of_positions = total_of_positions + _14;
adj_index = adj_index + 1;
" ]



# function number 66
	node [ id 1797 graphics [ fill "#ffffff" ] label "rhp_node_weight ()
ENTRY" ]

	node [ id 1798 graphics [ fill "#ffffff" ] label "rhp_node_weight ()
EXIT" ]

	node [ id 1799 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
total_degree1 = 0;
total_degree2 = 0;
total_degree = 0;
total_of_positions = 0;
adj_index = 0;
_1 = node-&gt;down_degree;
_2 = node-&gt;up_degree;
_3 = node-&gt;innum;
rhp_log (&quot;%s(): at node %d up degree %d down degree %d mode %d\n&quot;, &amp;__FUNCTION__, _3, _2, _1, orientation);
_4 = node-&gt;up_degree;
_5 = node-&gt;down_degree;
_6 = _4 + _5;
if (_6 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1800 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
node-&gt;weight = 0;
_7 = node-&gt;innum;
rhp_log (&quot;%s(): node %d has weight set (0) isolated node special mode %d\n&quot;, &amp;__FUNCTION__, _7, orientation);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 16&gt;; [INV]
" ]

	node [ id 1801 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
if (orientation != 1)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1802 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
total_degree1 = node-&gt;down_degree;
adj_index = 0;
goto &lt;bb 7&gt;; [INV]
" ]

	node [ id 1803 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
if (orientation != 0)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 12&gt;; [INV]
" ]

	node [ id 1804 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
total_degree2 = node-&gt;up_degree;
adj_index = 0;
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1805 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
total_degree = total_degree1 + total_degree2;
if (total_degree &gt; 0)
  goto &lt;bb 13&gt;; [INV]
else
  goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 1806 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
_24 = total_of_positions * 100;
node-&gt;weight = _24;
_25 = node-&gt;weight;
_26 = _25 / total_degree;
node-&gt;weight = _26;
goto &lt;bb 15&gt;; [INV]
" ]

	node [ id 1807 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
node-&gt;weight = -1;
_27 = node-&gt;innum;
rhp_log (&quot;%s(): node %d has weight set (-1) special degree=(%d+%d) mode %d\n&quot;, &amp;__FUNCTION__, _27, total_degree1, total_degree2, orientation);
" ]

	node [ id 1808 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
_28 = node-&gt;weight;
_29 = node-&gt;innum;
rhp_log (&quot;%s(): node %d has now weight %d mode %d\n&quot;, &amp;__FUNCTION__, _29, _28, orientation);
" ]

	node [ id 1809 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
&lt;L15&gt;:
return;
" ]

	edge [ source 1797 target 1799 graphics [ fill "#0000ff" ] ] 
	edge [ source 1799 target 1800 graphics [ fill "#000000" ] ] 
	edge [ source 1799 target 1801 graphics [ fill "#000000" ] ] 
	edge [ source 1800 target 1809 graphics [ fill "#0000ff" ] ] 
	edge [ source 1801 target 1802 graphics [ fill "#000000" ] ] 
	edge [ source 1801 target 1803 graphics [ fill "#000000" ] ] 
	edge [ source 1802 target 1795 graphics [ fill "#0000ff" ] ] 
	edge [ source 1796 target 1795 graphics [ fill "#0000ff" ] ] 
	edge [ source 1795 target 1796 graphics [ fill "#000000" ] ] 
	edge [ source 1795 target 1803 graphics [ fill "#000000" ] ] 
	edge [ source 1803 target 1804 graphics [ fill "#000000" ] ] 
	edge [ source 1803 target 1805 graphics [ fill "#000000" ] ] 
	edge [ source 1804 target 1793 graphics [ fill "#0000ff" ] ] 
	edge [ source 1794 target 1793 graphics [ fill "#0000ff" ] ] 
	edge [ source 1793 target 1794 graphics [ fill "#000000" ] ] 
	edge [ source 1793 target 1805 graphics [ fill "#000000" ] ] 
	edge [ source 1805 target 1806 graphics [ fill "#000000" ] ] 
	edge [ source 1805 target 1807 graphics [ fill "#000000" ] ] 
	edge [ source 1806 target 1808 graphics [ fill "#0000ff" ] ] 
	edge [ source 1807 target 1808 graphics [ fill "#0000ff" ] ] 
	edge [ source 1808 target 1809 graphics [ fill "#0000ff" ] ] 
	edge [ source 1809 target 1798 graphics [ fill "#000000" ] ] 


# function number 67
	node [ id 1827 graphics [ fill "#ffffff" ] label "rhp_compare_weights ()
ENTRY" ]

	node [ id 1828 graphics [ fill "#ffffff" ] label "rhp_compare_weights ()
EXIT" ]

	node [ id 1829 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
entry_ptr_i = 0B;
entry_ptr_j = 0B;
node_i = 0B;
node_j = 0B;
diff = 0;
entry_ptr_i = ptr_i;
entry_ptr_j = ptr_j;
node_i = *entry_ptr_i;
node_j = *entry_ptr_j;
_1 = node_i-&gt;weight;
_2 = node_j-&gt;weight;
_3 = _1 &gt; _2;
diff = (int) _3;
if (diff &lt; 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1830 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
diff = -diff;
" ]

	node [ id 1831 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
if (diff &lt;= 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 1832 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
D.4958 = 0;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1833 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
_4 = node_i-&gt;weight;
_5 = node_j-&gt;weight;
if (_4 &gt; _5)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 8&gt;; [INV]
" ]

	node [ id 1834 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
D.4958 = 1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1835 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
_6 = node_i-&gt;weight;
_7 = node_j-&gt;weight;
if (_6 &lt; _7)
  goto &lt;bb 9&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1836 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
D.4958 = -1;
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1837 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
D.4958 = 0;
// predicted unlikely by early return (on trees) predictor.
" ]

	node [ id 1838 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
&lt;L8&gt;:
return D.4958;
" ]

	edge [ source 1827 target 1829 graphics [ fill "#0000ff" ] ] 
	edge [ source 1829 target 1830 graphics [ fill "#000000" ] ] 
	edge [ source 1829 target 1831 graphics [ fill "#000000" ] ] 
	edge [ source 1830 target 1831 graphics [ fill "#0000ff" ] ] 
	edge [ source 1831 target 1832 graphics [ fill "#000000" ] ] 
	edge [ source 1831 target 1833 graphics [ fill "#000000" ] ] 
	edge [ source 1832 target 1838 graphics [ fill "#0000ff" ] ] 
	edge [ source 1833 target 1834 graphics [ fill "#000000" ] ] 
	edge [ source 1833 target 1835 graphics [ fill "#000000" ] ] 
	edge [ source 1834 target 1838 graphics [ fill "#0000ff" ] ] 
	edge [ source 1835 target 1836 graphics [ fill "#000000" ] ] 
	edge [ source 1835 target 1837 graphics [ fill "#000000" ] ] 
	edge [ source 1836 target 1838 graphics [ fill "#0000ff" ] ] 
	edge [ source 1837 target 1838 graphics [ fill "#0000ff" ] ] 
	edge [ source 1838 target 1828 graphics [ fill "#000000" ] ] 


# function number 68
	node [ id 1851 graphics [ fill "#ffffff" ] label "rhp_layersort ()
ENTRY" ]

	node [ id 1852 graphics [ fill "#ffffff" ] label "rhp_layersort ()
EXIT" ]

	node [ id 1853 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
rl = 0B;
_1 = (long long int) level;
rhp_sp_layers.279_2 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.279_2, _1);
if (spn == 0B)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1854 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): could not find data for level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, level);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 5&gt;; [INV]
" ]

	node [ id 1855 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
_3 = spn-&gt;value;
rl = (struct rhplevel *) _3;
_4 = rl-&gt;number_of_nodes;
_5 = (long unsigned int) _4;
_6 = rl-&gt;nodes;
qsort (_6, _5, 8, rhp_compare_weights);
rhp_updatenodepositions (level);
rhp_log (&quot;%s(): sorted level %d and updated node positions\n&quot;, &amp;__FUNCTION__, level);
" ]

	node [ id 1856 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
&lt;L2&gt;:
return;
" ]

	edge [ source 1851 target 1853 graphics [ fill "#0000ff" ] ] 
	edge [ source 1853 target 1854 graphics [ fill "#000000" ] ] 
	edge [ source 1853 target 1855 graphics [ fill "#000000" ] ] 
	edge [ source 1854 target 1856 graphics [ fill "#0000ff" ] ] 
	edge [ source 1855 target 1856 graphics [ fill "#0000ff" ] ] 
	edge [ source 1856 target 1852 graphics [ fill "#000000" ] ] 
	node [ id 1863 graphics [ fill "#d3d3d3" ] label "&lt;bb 9&gt;:
if (spn != 0B)
  goto &lt;bb 8&gt;; [INV]
else
  goto &lt;bb 10&gt;; [INV]
" ]

	node [ id 1864 graphics [ fill "#d3d3d3" ] label "&lt;bb 8&gt;:
_8 = spn-&gt;value;
nd = (struct rhpnode *) _8;
_9 = nd-&gt;position;
_10 = nd-&gt;level;
_11 = nd-&gt;innum;
rhp_log (&quot;%s(): node %d level %d pos %d\n&quot;, &amp;__FUNCTION__, _11, _10, _9);
nn = rhp_malloc (80, &amp;__FUNCTION__, 4129);
nn-&gt;num = num;
_12 = nd-&gt;innum;
nn-&gt;innum = _12;
_13 = nd-&gt;level;
nn-&gt;level = _13;
_14 = nd-&gt;data;
nn-&gt;data = _14;
_15 = nd-&gt;position;
nn-&gt;position = _15;
_16 = nd-&gt;up_degree;
nn-&gt;up_degree = _16;
_17 = nd-&gt;down_degree;
nn-&gt;down_degree = _17;
_18 = nd-&gt;up_edges;
nn-&gt;up_edges = _18;
_19 = nd-&gt;down_edges;
nn-&gt;down_edges = _19;
_20 = nd-&gt;weight;
nn-&gt;weight = _20;
_21 = nd-&gt;up_crossings;
nn-&gt;up_crossings = _21;
_22 = nd-&gt;down_crossings;
nn-&gt;down_crossings = _22;
_23 = nd-&gt;weight;
_24 = nd-&gt;position;
_25 = nd-&gt;level;
_26 = nd-&gt;innum;
rhp_log (&quot;%s(): node %d level %d pos %d weight %d at %d\n&quot;, &amp;__FUNCTION__, _26, _25, _24, _23, num);
nn.285_27 = (long long int) nn;
_28 = (long long int) num;
rhp_sp_master_node_list_sorted.286_29 = rhp_sp_master_node_list_sorted;
rhp_sp_insert (rhp_sp_master_node_list_sorted.286_29, _28, nn.285_27);
num = num + 1;
_30 = spn-&gt;key;
rhp_sp_master_node_list.287_31 = rhp_sp_master_node_list;
spn = rhp_sp_next (rhp_sp_master_node_list.287_31, _30);
" ]

	node [ id 1865 graphics [ fill "#d3d3d3" ] label "&lt;bb 22&gt;:
_60 = lv-&gt;number_of_nodes;
if (ii &lt; _60)
  goto &lt;bb 21&gt;; [INV]
else
  goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 1866 graphics [ fill "#d3d3d3" ] label "&lt;bb 21&gt;:
_38 = lv-&gt;nodes;
_39 = (long unsigned int) ii;
_40 = _39 * 8;
_41 = _38 + _40;
nd = *_41;
nn = rhp_malloc (80, &amp;__FUNCTION__, 4202);
nn-&gt;num = num;
_42 = nd-&gt;innum;
nn-&gt;innum = _42;
_43 = nd-&gt;level;
nn-&gt;level = _43;
_44 = nd-&gt;data;
nn-&gt;data = _44;
_45 = nd-&gt;position;
nn-&gt;position = _45;
_46 = nd-&gt;up_degree;
nn-&gt;up_degree = _46;
_47 = nd-&gt;down_degree;
nn-&gt;down_degree = _47;
_48 = nd-&gt;up_edges;
nn-&gt;up_edges = _48;
_49 = nd-&gt;down_edges;
nn-&gt;down_edges = _49;
_50 = nd-&gt;weight;
nn-&gt;weight = _50;
_51 = nd-&gt;up_crossings;
nn-&gt;up_crossings = _51;
_52 = nd-&gt;down_crossings;
nn-&gt;down_crossings = _52;
_53 = nd-&gt;weight;
_54 = nd-&gt;position;
_55 = nd-&gt;level;
_56 = nd-&gt;innum;
rhp_log (&quot;%s(): node %d level %d pos %d weight %d at %d\n&quot;, &amp;__FUNCTION__, _56, _55, _54, _53, num);
nn.289_57 = (long long int) nn;
_58 = (long long int) num;
rhp_sp_master_node_list_sorted.290_59 = rhp_sp_master_node_list_sorted;
rhp_sp_insert (rhp_sp_master_node_list_sorted.290_59, _58, nn.289_57);
num = num + 1;
ii = ii + 1;
" ]

	node [ id 1867 graphics [ fill "#d3d3d3" ] label "&lt;bb 24&gt;:
rhp_nlevels.291_61 = rhp_nlevels;
if (i &lt; rhp_nlevels.291_61)
  goto &lt;bb 12&gt;; [INV]
else
  goto &lt;bb 25&gt;; [INV]
" ]

	node [ id 1868 graphics [ fill "#d3d3d3" ] label "&lt;bb 12&gt;:
_33 = (long long int) i;
rhp_sp_layers.288_34 = rhp_sp_layers;
spn = rhp_sp_lookup (rhp_sp_layers.288_34, _33);
if (spn == 0B)
  goto &lt;bb 13&gt;; [INV]
else
  goto &lt;bb 14&gt;; [INV]
" ]

	node [ id 1869 graphics [ fill "#d3d3d3" ] label "&lt;bb 13&gt;:
rhp_log (&quot;%s(): no data for level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, i);
// predicted unlikely by continue predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 1870 graphics [ fill "#d3d3d3" ] label "&lt;bb 14&gt;:
_35 = spn-&gt;value;
lv = (struct rhplevel *) _35;
if (lv == 0B)
  goto &lt;bb 15&gt;; [INV]
else
  goto &lt;bb 16&gt;; [INV]
" ]

	node [ id 1871 graphics [ fill "#d3d3d3" ] label "&lt;bb 23&gt;:
i = i + 1;
" ]

	node [ id 1872 graphics [ fill "#d3d3d3" ] label "&lt;bb 15&gt;:
rhp_log (&quot;%s(): no nodes in level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, i);
// predicted unlikely by continue predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 1873 graphics [ fill "#d3d3d3" ] label "&lt;bb 16&gt;:
_36 = lv-&gt;nodes;
if (_36 == 0B)
  goto &lt;bb 17&gt;; [INV]
else
  goto &lt;bb 18&gt;; [INV]
" ]

	node [ id 1874 graphics [ fill "#d3d3d3" ] label "&lt;bb 17&gt;:
rhp_log (&quot;%s(): no data for nodes in level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, i);
// predicted unlikely by continue predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 1875 graphics [ fill "#d3d3d3" ] label "&lt;bb 18&gt;:
_37 = lv-&gt;number_of_nodes;
if (_37 == 0)
  goto &lt;bb 19&gt;; [INV]
else
  goto &lt;bb 20&gt;; [INV]
" ]

	node [ id 1876 graphics [ fill "#d3d3d3" ] label "&lt;bb 19&gt;:
rhp_log (&quot;%s(): no nodes in level %d shouldnothappen!\n&quot;, &amp;__FUNCTION__, i);
// predicted unlikely by continue predictor.
goto &lt;bb 23&gt;; [INV]
" ]

	node [ id 1877 graphics [ fill "#d3d3d3" ] label "&lt;bb 20&gt;:
ii = 0;
goto &lt;bb 22&gt;; [INV]
" ]



# function number 69
	node [ id 1878 graphics [ fill "#ffffff" ] label "rhp_sorted_nodelist ()
ENTRY" ]

	node [ id 1879 graphics [ fill "#ffffff" ] label "rhp_sorted_nodelist ()
EXIT" ]

	node [ id 1880 graphics [ fill "#d3d3d3" ] label "&lt;bb 2&gt;:
spn = 0B;
lv = 0B;
nd = 0B;
nn = 0B;
i = 0;
ii = 0;
num = 0;
rhp_nlevels.280_1 = rhp_nlevels;
rhp_log (&quot;%s(): %d levels\n&quot;, &amp;__FUNCTION__, rhp_nlevels.280_1);
rhp_nlevels.281_2 = rhp_nlevels;
if (rhp_nlevels.281_2 == 0)
  goto &lt;bb 3&gt;; [INV]
else
  goto &lt;bb 4&gt;; [INV]
" ]

	node [ id 1881 graphics [ fill "#d3d3d3" ] label "&lt;bb 3&gt;:
rhp_log (&quot;%s(): no levels shouldnothappen!\n&quot;, &amp;__FUNCTION__);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 26&gt;; [INV]
" ]

	node [ id 1882 graphics [ fill "#d3d3d3" ] label "&lt;bb 4&gt;:
rhp_sp_master_node_list.282_3 = rhp_sp_master_node_list;
_4 = rhp_sp_has_data (rhp_sp_master_node_list.282_3);
if (_4 == 0)
  goto &lt;bb 5&gt;; [INV]
else
  goto &lt;bb 6&gt;; [INV]
" ]

	node [ id 1883 graphics [ fill "#d3d3d3" ] label "&lt;bb 5&gt;:
rhp_log (&quot;%s(): no node data shouldnothappen!\n&quot;, &amp;__FUNCTION__);
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 26&gt;; [INV]
" ]

	node [ id 1884 graphics [ fill "#d3d3d3" ] label "&lt;bb 6&gt;:
rhp_nlevels.283_5 = rhp_nlevels;
if (rhp_nlevels.283_5 == 1)
  goto &lt;bb 7&gt;; [INV]
else
  goto &lt;bb 11&gt;; [INV]
" ]

	node [ id 1885 graphics [ fill "#d3d3d3" ] label "&lt;bb 7&gt;:
num = 0;
_6 = rhp_sp_new (1);
rhp_sp_master_node_list_sorted = _6;
rhp_sp_master_node_list.284_7 = rhp_sp_master_node_list;
spn = rhp_sp_min (rhp_sp_master_node_list.284_7);
goto &lt;bb 9&gt;; [INV]
" ]

	node [ id 1886 graphics [ fill "#d3d3d3" ] label "&lt;bb 10&gt;:
// predicted unlikely by early return (on trees) predictor.
goto &lt;bb 26&gt;; [INV]
" ]

	node [ id 1887 graphics [ fill "#d3d3d3" ] label "&lt;bb 11&gt;:
num = 0;
_32 = rhp_sp_new (1);
rhp_sp_master_node_list_sorted = _32;
i = 0;
goto &lt;bb 24&gt;; [INV]
" ]

	node [ id 1888 graphics [ fill "#d3d3d3" ] label "&lt;bb 25&gt;:
" ]

	node [ id 1889 graphics [ fill "#d3d3d3" ] label "&lt;bb 26&gt;:
&lt;L24&gt;:
return;
" ]

	edge [ source 1878 target 1880 graphics [ fill "#0000ff" ] ] 
	edge [ source 1880 target 1881 graphics [ fill "#000000" ] ] 
	edge [ source 1880 target 1882 graphics [ fill "#000000" ] ] 
	edge [ source 1881 target 1889 graphics [ fill "#0000ff" ] ] 
	edge [ source 1882 target 1883 graphics [ fill "#000000" ] ] 
	edge [ source 1882 target 1884 graphics [ fill "#000000" ] ] 
	edge [ source 1883 target 1889 graphics [ fill "#0000ff" ] ] 
	edge [ source 1884 target 1885 graphics [ fill "#000000" ] ] 
	edge [ source 1884 target 1887 graphics [ fill "#000000" ] ] 
	edge [ source 1885 target 1863 graphics [ fill "#0000ff" ] ] 
	edge [ source 1864 target 1863 graphics [ fill "#0000ff" ] ] 
	edge [ source 1863 target 1864 graphics [ fill "#000000" ] ] 
	edge [ source 1863 target 1886 graphics [ fill "#000000" ] ] 
	edge [ source 1886 target 1889 graphics [ fill "#0000ff" ] ] 
	edge [ source 1887 target 1867 graphics [ fill "#0000ff" ] ] 
	edge [ source 1868 target 1869 graphics [ fill "#000000" ] ] 
	edge [ source 1868 target 1870 graphics [ fill "#000000" ] ] 
	edge [ source 1869 target 1871 graphics [ fill "#0000ff" ] ] 
	edge [ source 1870 target 1872 graphics [ fill "#000000" ] ] 
	edge [ source 1870 target 1873 graphics [ fill "#000000" ] ] 
	edge [ source 1872 target 1871 graphics [ fill "#0000ff" ] ] 
	edge [ source 1873 target 1874 graphics [ fill "#000000" ] ] 
	edge [ source 1873 target 1875 graphics [ fill "#000000" ] ] 
	edge [ source 1874 target 1871 graphics [ fill "#0000ff" ] ] 
	edge [ source 1875 target 1876 graphics [ fill "#000000" ] ] 
	edge [ source 1875 target 1877 graphics [ fill "#000000" ] ] 
	edge [ source 1876 target 1871 graphics [ fill "#0000ff" ] ] 
	edge [ source 1877 target 1865 graphics [ fill "#0000ff" ] ] 
	edge [ source 1866 target 1865 graphics [ fill "#0000ff" ] ] 
	edge [ source 1865 target 1866 graphics [ fill "#000000" ] ] 
	edge [ source 1865 target 1871 graphics [ fill "#000000" ] ] 
	edge [ source 1871 target 1867 graphics [ fill "#0000ff" ] ] 
	edge [ source 1867 target 1868 graphics [ fill "#000000" ] ] 
	edge [ source 1867 target 1888 graphics [ fill "#000000" ] ] 
	edge [ source 1888 target 1889 graphics [ fill "#0000ff" ] ] 
	edge [ source 1889 target 1879 graphics [ fill "#000000" ] ] 
]
