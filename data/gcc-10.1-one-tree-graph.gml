graph [

  directed 1




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


]

