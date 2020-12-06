# generated with gcctree2gml
graph [
  directed 1
  node [ id 72 label "search()
ENTRY" ]
  node [ id 73 label "search()
EXIT" ]
  node [ id 3 label "<bb 2>: search()
  bbD.4175_2(D)->visitedD.4144 = 1;  
  veD.4179_3 = bbD.4175_2(D)->succD.4149;  
  if (veD.4179_3 != 0B)  
    goto <bb 3>;  
  else  
    goto <bb 7>;  
" ]
  node [ id 4 label "<bb 3>: search()
   
" ]
  node [ id 5 label "<bb 7>: search()
  count.10D.5607_8 = countD.4173;  
  bbD.4175_2(D)->dfs_orderD.4145 = count.10D.5607_8;  
  count.11D.5608_10 = count.10D.5607_8 + -1;  
  countD.4173 = count.11D.5608_10;  
  return;  
" ]
  node [ id 6 label "<bb 4>: search()
  eD.4180_4 = veD.4179_9->edgeD.4138;  
  succ_bbD.4178_5 = eD.4180_4->targetD.4135;  
  D.5604_6 = succ_bbD.4178_5->visitedD.4144;  
  if (D.5604_6 == 0)  
    goto <bb 5>;  
  else  
    goto <bb 6>;  
" ]
  node [ id 7 label "<bb 6>: search()
  veD.4179_7 = veD.4179_9->nextD.4139;  
  if (veD.4179_7 != 0B)  
    goto <bb 4>;  
  else  
    goto <bb 7>;  
" ]
  node [ id 8 label "<bb 5>: search()
  eD.4180_4->typeD.4133 = 1;  
  searchD.4176 (succ_bbD.4178_5);  
" ]
  edge [ source 72 target 3 ]
  edge [ source 3 target 4 ]
  edge [ source 3 target 5 ]
  edge [ source 4 target 6 ]
  edge [ source 7 target 6 fill "#0000ff" ]
  edge [ source 6 target 8 ]
  edge [ source 6 target 7 ]
  edge [ source 8 target 7 ]
  edge [ source 7 target 5 ]
  edge [ source 5 target 73 ]
  node [ id 74 label "depth_first_search()
ENTRY" ]
  node [ id 75 label "depth_first_search()
EXIT" ]
  node [ id 11 label "<bb 2>: depth_first_search()
  cfg.8D.5601_2 = cfgD.4174;  
  bbD.4187_3 = cfg.8D.5601_2->bbD.4157;  
  if (bbD.4187_3 != 0B)  
    goto <bb 3>;  
  else  
    goto <bb 5>;  
" ]
  node [ id 12 label "<bb 3>: depth_first_search()
   
" ]
  node [ id 13 label "<bb 5>: depth_first_search()
  count.9D.5602_6 = cfg.8D.5601_2->bb_numD.4153;  
  countD.4173 = count.9D.5602_6;  
  D.5603_8 = cfg.8D.5601_2->entryD.4155;  
  searchD.4176 (D.5603_8); [tail call]  
  return;  
" ]
  node [ id 14 label "<bb 4>: depth_first_search()
  bbD.4187_14->visitedD.4144 = 0;  
  bbD.4187_4 = bbD.4187_14->nextD.4151;  
  if (bbD.4187_4 != 0B)  
    goto <bb 4>;  
  else  
    goto <bb 5>;  
" ]
  edge [ source 74 target 11 ]
  edge [ source 11 target 12 ]
  edge [ source 11 target 13 ]
  edge [ source 12 target 14 ]
  edge [ source 14 target 14 fill "#0000ff" ]
  edge [ source 14 target 13 ]
  edge [ source 13 target 75 ]
  node [ id 76 label "is_ancestor()
ENTRY" ]
  node [ id 77 label "is_ancestor()
EXIT" ]
  node [ id 17 label "<bb 2>: is_ancestor()
  if (targetD.4192_5(D) == sourceD.4191_7(D))  
    goto <bb 11>;  
  else  
    goto <bb 3>;  
" ]
  node [ id 18 label "<bb 11>: is_ancestor()
  return D.5594_4;  
" ]
  node [ id 19 label "<bb 3>: is_ancestor()
  pretmp.24D.5629_1 = cfgD.4174;  
  pretmp.26D.5631_19 = pretmp.24D.5629_1->entryD.4155;  
  goto <bb 5>;  
" ]
  node [ id 20 label "<bb 5>: is_ancestor()
  veD.4196_9 = bbD.4195_21->predD.4147;  
  if (veD.4196_9 != 0B)  
    goto <bb 6>;  
  else  
    goto <bb 10>;  
" ]
  node [ id 21 label "<bb 4>: is_ancestor()
  if (bbD.4195_2 == sourceD.4191_7(D))  
    goto <bb 11>;  
  else  
    goto <bb 13>;  
" ]
  node [ id 22 label "<bb 10>: is_ancestor()
  if (bbD.4195_2 != pretmp.26D.5631_19)  
    goto <bb 4>;  
  else  
    goto <bb 11>;  
" ]
  node [ id 23 label "<bb 13>: is_ancestor()
   
" ]
  node [ id 24 label "<bb 6>: is_ancestor()
  eD.4197_20 = veD.4196_9->edgeD.4138;  
  D.5595_23 = eD.4197_20->typeD.4133;  
  if (D.5595_23 == 1)  
    goto <bb 8>;  
  else  
    goto <bb 9>;  
" ]
  node [ id 25 label "<bb 8>: is_ancestor()
  bbD.4195_12 = eD.4197_18->sourceD.4134;  
  goto <bb 10>;  
" ]
  node [ id 26 label "<bb 9>: is_ancestor()
   
" ]
  node [ id 27 label "<bb 7>: is_ancestor()
  eD.4197_10 = veD.4196_13->edgeD.4138;  
  D.5595_11 = eD.4197_10->typeD.4133;  
  if (D.5595_11 == 1)  
    goto <bb 8>;  
  else  
    goto <bb 14>;  
" ]
  node [ id 28 label "<bb 12>: is_ancestor()
  veD.4196_13 = veD.4196_24->nextD.4139;  
  if (veD.4196_13 != 0B)  
    goto <bb 7>;  
  else  
    goto <bb 10>;  
" ]
  node [ id 29 label "<bb 14>: is_ancestor()
  goto <bb 12>;  
" ]
  edge [ source 76 target 17 ]
  edge [ source 17 target 18 ]
  edge [ source 17 target 19 ]
  edge [ source 19 target 20 ]
  edge [ source 22 target 21 ]
  edge [ source 21 target 18 ]
  edge [ source 21 target 23 ]
  edge [ source 23 target 20 fill "#0000ff" ]
  edge [ source 20 target 24 ]
  edge [ source 20 target 22 ]
  edge [ source 24 target 25 ]
  edge [ source 24 target 26 ]
  edge [ source 28 target 27 ]
  edge [ source 27 target 25 ]
  edge [ source 27 target 29 ]
  edge [ source 29 target 28 fill "#0000ff" ]
  edge [ source 25 target 22 ]
  edge [ source 26 target 28 ]
  edge [ source 28 target 22 ]
  edge [ source 22 target 18 ]
  edge [ source 18 target 77 ]
  node [ id 78 label "mark_edge()
ENTRY" ]
  node [ id 79 label "mark_edge()
EXIT" ]
  node [ id 32 label "<bb 2>: mark_edge()
  sourceD.4206_2 = eD.4203_1(D)->sourceD.4134;  
  targetD.4207_3 = eD.4203_1(D)->targetD.4135;  
  D.5584_4 = is_ancestorD.4193 (targetD.4207_3, sourceD.4206_2);  
  if (D.5584_4 != 0)  
    goto <bb 3>;  
  else  
    goto <bb 4>;  
" ]
  node [ id 33 label "<bb 3>: mark_edge()
  eD.4203_1(D)->typeD.4133 = 3;  
  goto <bb 7>;  
" ]
  node [ id 34 label "<bb 4>: mark_edge()
  D.5588_5 = is_ancestorD.4193 (sourceD.4206_2, targetD.4207_3);  
  if (D.5588_5 != 0)  
    goto <bb 5>;  
  else  
    goto <bb 6>;  
" ]
  node [ id 35 label "<bb 7>: mark_edge()
  return;  
" ]
  node [ id 36 label "<bb 5>: mark_edge()
  eD.4203_1(D)->typeD.4133 = 2;  
  goto <bb 7>;  
" ]
  node [ id 37 label "<bb 6>: mark_edge()
  eD.4203_1(D)->typeD.4133 = 4;  
" ]
  edge [ source 78 target 32 ]
  edge [ source 32 target 33 ]
  edge [ source 32 target 34 ]
  edge [ source 33 target 35 ]
  edge [ source 34 target 36 ]
  edge [ source 34 target 37 ]
  edge [ source 36 target 35 ]
  edge [ source 37 target 35 ]
  edge [ source 35 target 79 ]
  node [ id 80 label "mark_edges()
ENTRY" ]
  node [ id 81 label "mark_edges()
EXIT" ]
  node [ id 40 label "<bb 2>: mark_edges()
  current_function.6D.5580_2 = current_functionD.4113;  
  cfgD.4211_3 = current_function.6D.5580_2->cfgD.4162;  
  eD.4212_4 = cfgD.4211_3->edgeD.4159;  
  if (eD.4212_4 != 0B)  
    goto <bb 3>;  
  else  
    goto <bb 7>;  
" ]
  node [ id 41 label "<bb 3>: mark_edges()
   
" ]
  node [ id 42 label "<bb 7>: mark_edges()
  return;  
" ]
  node [ id 43 label "<bb 4>: mark_edges()
  D.5581_5 = eD.4212_13->typeD.4133;  
  if (D.5581_5 == 0)  
    goto <bb 5>;  
  else  
    goto <bb 6>;  
" ]
  node [ id 44 label "<bb 6>: mark_edges()
  eD.4212_6 = eD.4212_13->nextD.4136;  
  if (eD.4212_6 != 0B)  
    goto <bb 4>;  
  else  
    goto <bb 7>;  
" ]
  node [ id 45 label "<bb 5>: mark_edges()
  mark_edgeD.4204 (eD.4212_13);  
" ]
  edge [ source 80 target 40 ]
  edge [ source 40 target 41 ]
  edge [ source 40 target 42 ]
  edge [ source 41 target 43 ]
  edge [ source 44 target 43 fill "#0000ff" ]
  edge [ source 43 target 45 ]
  edge [ source 43 target 44 ]
  edge [ source 45 target 44 ]
  edge [ source 44 target 42 ]
  edge [ source 42 target 81 ]
  node [ id 82 label "calc_max_distance_recursive()
ENTRY" ]
  node [ id 83 label "calc_max_distance_recursive()
EXIT" ]
  node [ id 48 label "<bb 2>: calc_max_distance_recursive()
  prephitmp.35D.5640_6 = bbD.4216_5(D)->max_distanceD.4146;  
  if (prephitmp.35D.5640_6 == 0)  
    goto <bb 3>;  
  else  
    goto <bb 10>;  
" ]
  node [ id 49 label "<bb 3>: calc_max_distance_recursive()
  veD.4221_7 = bbD.4216_5(D)->predD.4147;  
  if (veD.4221_7 != 0B)  
    goto <bb 4>;  
  else  
    goto <bb 9>;  
" ]
  node [ id 50 label "<bb 10>: calc_max_distance_recursive()
  return prephitmp.35D.5640_2;  
" ]
  node [ id 51 label "<bb 4>: calc_max_distance_recursive()
   
" ]
  node [ id 52 label "<bb 9>: calc_max_distance_recursive()
  bbD.4216_5(D)->max_distanceD.4146 = prephitmp.35D.5640_23;  
" ]
  node [ id 53 label "<bb 5>: calc_max_distance_recursive()
  eD.4222_8 = veD.4221_27->edgeD.4138;  
  D.5573_9 = eD.4222_8->typeD.4133;  
  if (D.5573_9 == 3)  
    goto <bb 7>;  
  else  
    goto <bb 6>;  
" ]
  node [ id 54 label "<bb 7>: calc_max_distance_recursive()
  veD.4221_13 = veD.4221_27->nextD.4139;  
  if (veD.4221_13 != 0B)  
    goto <bb 5>;  
  else  
    goto <bb 8>;  
" ]
  node [ id 55 label "<bb 6>: calc_max_distance_recursive()
  D.5576_10 = eD.4222_8->sourceD.4134;  
  valD.4219_11 = calc_max_distance_recursiveD.4217 (D.5576_10);  
  maxD.4220_12 = MAX_EXPR <valD.4219_11, maxD.4220_24>;  
" ]
  node [ id 56 label "<bb 8>: calc_max_distance_recursive()
  prephitmp.35D.5640_25 = maxD.4220_26 + 1;  
" ]
  edge [ source 82 target 48 ]
  edge [ source 48 target 49 ]
  edge [ source 48 target 50 ]
  edge [ source 49 target 51 ]
  edge [ source 49 target 52 ]
  edge [ source 51 target 53 ]
  edge [ source 54 target 53 fill "#0000ff" ]
  edge [ source 53 target 54 ]
  edge [ source 53 target 55 ]
  edge [ source 55 target 54 ]
  edge [ source 54 target 56 ]
  edge [ source 56 target 52 ]
  edge [ source 52 target 50 ]
  edge [ source 50 target 83 ]
  node [ id 84 label "calc_max_distance()
ENTRY" ]
  node [ id 85 label "calc_max_distance()
EXIT" ]
  node [ id 59 label "<bb 2>: calc_max_distance()
  depth_first_searchD.4185 ();  
  mark_edgesD.4209 ();  
  cfg.4D.5561_6 = cfgD.4174;  
  D.5562_7 = cfg.4D.5561_6->exitD.4156;  
  maxD.4231_8 = calc_max_distance_recursiveD.4217 (D.5562_7);  
  bbD.4232_10 = cfg.4D.5561_6->bbD.4157;  
  if (bbD.4232_10 != 0B)  
    goto <bb 3>;  
  else  
    goto <bb 8>;  
" ]
  node [ id 60 label "<bb 3>: calc_max_distance()
   
" ]
  node [ id 61 label "<bb 8>: calc_max_distance()
  D.5562_18 = cfg.4D.5561_6->exitD.4156;  
  D.5562_18->max_distanceD.4146 = maxD.4231_4;  
  return;  
" ]
  node [ id 62 label "<bb 4>: calc_max_distance()
  D.5563_11 = bbD.4232_28->max_distanceD.4146;  
  if (D.5563_11 == 0)  
    goto <bb 5>;  
  else  
    goto <bb 7>;  
" ]
  node [ id 63 label "<bb 7>: calc_max_distance()
  bbD.4232_16 = bbD.4232_28->nextD.4151;  
  if (bbD.4232_16 != 0B)  
    goto <bb 4>;  
  else  
    goto <bb 8>;  
" ]
  node [ id 64 label "<bb 5>: calc_max_distance()
  valD.4230_12 = calc_max_distance_recursiveD.4217 (bbD.4232_28);  
  if (valD.4230_12 >= maxD.4231_27)  
    goto <bb 6>;  
  else  
    goto <bb 7>;  
" ]
  node [ id 65 label "<bb 6>: calc_max_distance()
  maxD.4231_13 = valD.4230_12 + 1;  
" ]
  edge [ source 84 target 59 ]
  edge [ source 59 target 60 ]
  edge [ source 59 target 61 ]
  edge [ source 60 target 62 ]
  edge [ source 63 target 62 fill "#0000ff" ]
  edge [ source 62 target 64 ]
  edge [ source 62 target 63 ]
  edge [ source 64 target 65 ]
  edge [ source 64 target 63 ]
  edge [ source 65 target 63 ]
  edge [ source 63 target 61 ]
  edge [ source 61 target 85 ]
  node [ id 86 label "fine_tune_cfg()
ENTRY" ]
  node [ id 87 label "fine_tune_cfg()
EXIT" ]
  node [ id 68 label "<bb 2>: fine_tune_cfg()
  current_function.1D.5558_1 = first_functionD.4111;  
  current_functionD.4113 = current_function.1D.5558_1;  
  if (current_function.1D.5558_1 != 0B)  
    goto <bb 3>;  
  else  
    goto <bb 5>;  
" ]
  node [ id 69 label "<bb 3>: fine_tune_cfg()
   
" ]
  node [ id 70 label "<bb 5>: fine_tune_cfg()
  return;  
" ]
  node [ id 71 label "<bb 4>: fine_tune_cfg()
  cfg.2D.5559_4 = current_function.1D.5558_14->cfgD.4162;  
  cfgD.4174 = cfg.2D.5559_4;  
  calc_max_distanceD.4228 ();  
  current_function.1D.5558_5 = current_functionD.4113;  
  current_function.1D.5558_6 = current_function.1D.5558_5->nextD.4163;  
  current_functionD.4113 = current_function.1D.5558_6;  
  if (current_function.1D.5558_6 != 0B)  
    goto <bb 4>;  
  else  
    goto <bb 5>;  
" ]
  edge [ source 86 target 68 ]
  edge [ source 68 target 69 ]
  edge [ source 68 target 70 ]
  edge [ source 69 target 71 ]
  edge [ source 71 target 71 fill "#0000ff" ]
  edge [ source 71 target 70 ]
  edge [ source 70 target 87 ]
]
