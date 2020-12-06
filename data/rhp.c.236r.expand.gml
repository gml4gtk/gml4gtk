# RTL graph generated with GCC 10.1
graph
[
  directed 1


# function number 2
	node [ id 1 graphics [ fill "#ffffff" ] label "rhp_version ()
ENTRY" ]

	node [ id 2 graphics [ fill "#ffffff" ] label "rhp_version ()
EXIT" ]

	node [ id 3 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: r82:DI=`*.LC0'
    8: r83:DI=r82:DI
   12: ax:DI=r83:DI
   13: use ax:DI
" ]

	edge [ source 1 target 3 graphics [ fill "#0000ff" ] ] 
	edge [ source 3 target 2 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 3
	node [ id 4 graphics [ fill "#ffffff" ] label "rhp_init ()
ENTRY" ]

	node [ id 5 graphics [ fill "#ffffff" ] label "rhp_init ()
EXIT" ]

	node [ id 6 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x8]=di:DI
    3: [r77:DI-0xc]=si:SI
    4: NOTE_INSN_FUNCTION_BEG
    7: r82:SI=[`rhp_inited']
    8: flags:CCZ=cmp(r82:SI,0)
    9: pc={(flags:CCZ==0)?L16:pc}
" ]

	node [ id 7 graphics [ fill "#d3d3d3" ] label "   10: NOTE_INSN_BASIC_BLOCK 4
   11: si:DI=`__FUNCTION__.51'
   12: di:DI=`*.LC1'
   13: ax:QI=0
   14: call [`rhp_log'] argc:0
   15: call [`rhp_deinit'] argc:0
" ]

	node [ id 8 graphics [ fill "#d3d3d3" ] label "   16: L16:
   17: NOTE_INSN_BASIC_BLOCK 5
   18: [`rhp_logstream']=0
   19: [`rhp_dolog']=0
   20: [`rhp_logname']=0
   21: flags:CCZ=cmp([r77:DI-0x8],0)
   22: pc={(flags:CCZ==0)?L55:pc}
" ]

	node [ id 9 graphics [ fill "#d3d3d3" ] label "   23: NOTE_INSN_BASIC_BLOCK 6
   24: r91:DI=[r77:DI-0x8]
   25: r83:QI=[r91:DI]
   26: flags:CCZ=cmp(r83:QI,0)
   27: pc={(flags:CCZ!=0)?L33:pc}
" ]

	node [ id 10 graphics [ fill "#d3d3d3" ] label "   28: NOTE_INSN_BASIC_BLOCK 7
   29: r84:DI=[`stdout']
   30: [`rhp_logstream']=r84:DI
   31: pc=L47
" ]

	node [ id 11 graphics [ fill "#d3d3d3" ] label "   33: L33:
   34: NOTE_INSN_BASIC_BLOCK 8
   35: r92:DI=[r77:DI-0x8]
   36: si:DI=`*.LC2'
   37: di:DI=r92:DI
   38: ax:DI=call [`fopen'] argc:0
   39: r85:DI=ax:DI
   40: [`rhp_logstream']=r85:DI
   41: r86:DI=[`rhp_logstream']
   42: flags:CCZ=cmp(r86:DI,0)
   43: pc={(flags:CCZ!=0)?L47:pc}
" ]

	node [ id 12 graphics [ fill "#d3d3d3" ] label "   44: NOTE_INSN_BASIC_BLOCK 9
   45: r87:DI=[`stdout']
   46: [`rhp_logstream']=r87:DI
" ]

	node [ id 13 graphics [ fill "#d3d3d3" ] label "   47: L47:
   48: NOTE_INSN_BASIC_BLOCK 10
   49: r93:SI=[r77:DI-0xc]
   50: [`rhp_dolog']=r93:SI
   51: si:DI=`__FUNCTION__.51'
   52: di:DI=`*.LC3'
   53: ax:QI=0
   54: call [`rhp_log'] argc:0
" ]

	node [ id 14 graphics [ fill "#d3d3d3" ] label "   55: L55:
   56: NOTE_INSN_BASIC_BLOCK 11
   57: di:SI=0x1
   58: ax:DI=call [`rhp_sp_new'] argc:0
   59: r88:DI=ax:DI
   60: [`rhp_sp_master_node_list']=r88:DI
   61: di:SI=0x1
   62: ax:DI=call [`rhp_sp_new'] argc:0
   63: r89:DI=ax:DI
   64: [`rhp_sp_master_edge_list']=r89:DI
   65: [`rhp_uniq_nodenum']=0
   66: [`rhp_uniq_edgenum']=0
   67: [`rhp_number_of_nodes']=0
   68: [`rhp_number_of_edges']=0
   69: [`rhp_number_of_isolated_nodes']=0
   70: di:SI=0x1
   71: ax:DI=call [`rhp_sp_new'] argc:0
   72: r90:DI=ax:DI
   73: [`rhp_sp_between_layers']=r90:DI
   74: [`rhp_maxlevel']=0
   75: [`rhp_nlevels']=0
   76: [`rhp_crossings']=0xffffffffffffffff
   77: [`rhp_start_crossings']=0xffffffffffffffff
   78: [`rhp_best_crossings_order']=0
   79: [`rhp_getlayoutdata']=0
   80: [`rhp_improvements']=0
   81: [`rhp_notimprovements']=0
   82: dx:SI=0x4
   83: si:DI=`__FUNCTION__.51'
   84: di:DI=`*.LC4'
   85: ax:QI=0
   86: call [`rhp_log'] argc:0
   87: dx:SI=0x8
   88: si:DI=`__FUNCTION__.51'
   89: di:DI=`*.LC5'
   90: ax:QI=0
   91: call [`rhp_log'] argc:0
   92: dx:SI=0x8
   93: si:DI=`__FUNCTION__.51'
   94: di:DI=`*.LC6'
   95: ax:QI=0
   96: call [`rhp_log'] argc:0
   97: dx:SI=0x8
   98: si:DI=`__FUNCTION__.51'
   99: di:DI=`*.LC7'
  100: ax:QI=0
  101: call [`rhp_log'] argc:0
  102: dx:SI=0x20
  103: si:DI=`__FUNCTION__.51'
  104: di:DI=`*.LC8'
  105: ax:QI=0
  106: call [`rhp_log'] argc:0
  107: dx:SI=0x10
  108: si:DI=`__FUNCTION__.51'
  109: di:DI=`*.LC9'
  110: ax:QI=0
  111: call [`rhp_log'] argc:0
  112: dx:SI=0x50
  113: si:DI=`__FUNCTION__.51'
  114: di:DI=`*.LC10'
  115: ax:QI=0
  116: call [`rhp_log'] argc:0
  117: dx:SI=0x38
  118: si:DI=`__FUNCTION__.51'
  119: di:DI=`*.LC11'
  120: ax:QI=0
  121: call [`rhp_log'] argc:0
  122: dx:SI=0x10
  123: si:DI=`__FUNCTION__.51'
  124: di:DI=`*.LC12'
  125: ax:QI=0
  126: call [`rhp_log'] argc:0
  127: dx:SI=0x18
  128: si:DI=`__FUNCTION__.51'
  129: di:DI=`*.LC13'
  130: ax:QI=0
  131: call [`rhp_log'] argc:0
  132: dx:SI=0x18
  133: si:DI=`__FUNCTION__.51'
  134: di:DI=`*.LC14'
  135: ax:QI=0
  136: call [`rhp_log'] argc:0
  137: [`rhp_inited']=0x1
  142: 0
" ]

	edge [ source 4 target 6 graphics [ fill "#0000ff" ] ] 
	edge [ source 6 target 7 graphics [ fill "#0000ff" ] ] 
	edge [ source 6 target 8 graphics [ fill "#000000" ] ] 
	edge [ source 7 target 8 graphics [ fill "#0000ff" ] ] 
	edge [ source 8 target 9 graphics [ fill "#0000ff" ] ] 
	edge [ source 8 target 14 graphics [ fill "#000000" ] ] 
	edge [ source 9 target 10 graphics [ fill "#0000ff" ] ] 
	edge [ source 9 target 11 graphics [ fill "#000000" ] ] 
	edge [ source 10 target 13 graphics [ fill "#000000" ] ] 
	edge [ source 11 target 12 graphics [ fill "#0000ff" ] ] 
	edge [ source 11 target 13 graphics [ fill "#000000" ] ] 
	edge [ source 12 target 13 graphics [ fill "#0000ff" ] ] 
	edge [ source 13 target 14 graphics [ fill "#0000ff" ] ] 
	edge [ source 14 target 5 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 4
	node [ id 191 graphics [ fill "#ffffff" ] label "rhp_deinit ()
ENTRY" ]

	node [ id 192 graphics [ fill "#ffffff" ] label "rhp_deinit ()
EXIT" ]

	node [ id 193 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: r82:SI=[`rhp_inited']
    6: flags:CCZ=cmp(r82:SI,0)
    7: pc={(flags:CCZ!=0)?L15:pc}
" ]

	node [ id 194 graphics [ fill "#d3d3d3" ] label "    8: NOTE_INSN_BASIC_BLOCK 4
    9: si:DI=`__FUNCTION__.50'
   10: di:DI=`*.LC15'
   11: ax:QI=0
   12: call [`rhp_log'] argc:0
   13: pc=L125
" ]

	node [ id 195 graphics [ fill "#d3d3d3" ] label "   15: L15:
   16: NOTE_INSN_BASIC_BLOCK 5
   17: si:DI=`__FUNCTION__.50'
   18: di:DI=`*.LC16'
   19: ax:QI=0
   20: call [`rhp_log'] argc:0
   21: call [`rhp_empty_best_crossings_order'] argc:0
   22: call [`rhp_empty_sp_layers'] argc:0
   23: call [`rhp_empty_sp_between_layers'] argc:0
   24: call [`rhp_empty_sp_master_node_list'] argc:0
   25: call [`rhp_empty_sp_master_edge_list'] argc:0
   26: r83:DI=[`rhp_sp_layers']
   27: di:DI=r83:DI
   28: ax:DI=call [`rhp_sp_delete'] argc:0
   29: r84:DI=ax:DI
   30: [`rhp_sp_layers']=r84:DI
   31: r85:DI=[`rhp_best_crossings_order']
   32: flags:CCZ=cmp(r85:DI,0)
   33: pc={(flags:CCZ==0)?L42:pc}
" ]

	node [ id 196 graphics [ fill "#d3d3d3" ] label "   34: NOTE_INSN_BASIC_BLOCK 6
   35: r86:DI=[`rhp_best_crossings_order']
   36: dx:SI=0x2df
   37: si:DI=`__FUNCTION__.50'
   38: di:DI=r86:DI
   39: ax:DI=call [`rhp_free'] argc:0
   40: r87:DI=ax:DI
   41: [`rhp_best_crossings_order']=r87:DI
" ]

	node [ id 197 graphics [ fill "#d3d3d3" ] label "   42: L42:
   43: NOTE_INSN_BASIC_BLOCK 7
   44: r88:DI=[`rhp_sp_master_node_list']
   45: di:DI=r88:DI
   46: ax:DI=call [`rhp_sp_delete'] argc:0
   47: r89:DI=ax:DI
   48: [`rhp_sp_master_node_list']=r89:DI
   49: r90:DI=[`rhp_sp_master_edge_list']
   50: di:DI=r90:DI
   51: ax:DI=call [`rhp_sp_delete'] argc:0
   52: r91:DI=ax:DI
   53: [`rhp_sp_master_edge_list']=r91:DI
   54: r92:DI=[`rhp_sp_master_node_list_sorted']
   55: di:DI=r92:DI
   56: ax:DI=call [`rhp_sp_delete'] argc:0
   57: r93:DI=ax:DI
   58: [`rhp_sp_master_node_list_sorted']=r93:DI
   59: r94:DI=[`rhp_sp_between_layers']
   60: di:DI=r94:DI
   61: ax:DI=call [`rhp_sp_delete'] argc:0
   62: r95:DI=ax:DI
   63: [`rhp_sp_between_layers']=r95:DI
   64: [`rhp_uniq_nodenum']=0
   65: [`rhp_uniq_edgenum']=0
   66: [`rhp_number_of_nodes']=0
   67: [`rhp_number_of_edges']=0
   68: [`rhp_number_of_isolated_nodes']=0
   69: [`rhp_maxlevel']=0
   70: [`rhp_nlevels']=0
   71: [`rhp_crossings']=0xffffffffffffffff
   72: [`rhp_start_crossings']=0xffffffffffffffff
   73: [`rhp_getlayoutdata']=0
   74: [`rhp_improvements']=0
   75: [`rhp_notimprovements']=0
   76: r96:DI=[`rhp_n_malloc']
   77: r97:DI=[`rhp_n_free']
   78: flags:CCZ=cmp(r96:DI,r97:DI)
   79: pc={(flags:CCZ==0)?L99:pc}
" ]

	node [ id 198 graphics [ fill "#d3d3d3" ] label "   80: NOTE_INSN_BASIC_BLOCK 8
   81: r98:SI=[`rhp_dolog']
   84: flags:CCGC=cmp(r98:SI,0x1)
   85: pc={(flags:CCGC&lt;=0)?L99:pc}
" ]

	node [ id 199 graphics [ fill "#d3d3d3" ] label "   86: NOTE_INSN_BASIC_BLOCK 9
   87: r99:DI=[`rhp_n_malloc']
   88: r100:DI=[`rhp_n_free']
   89: {r101:DI=r99:DI-r100:DI;clobber flags:CC;}
   90: r102:DI=[`rhp_n_free']
   91: r103:DI=[`rhp_n_malloc']
   92: r8:DI=r101:DI
   93: cx:DI=r102:DI
   94: dx:DI=r103:DI
   95: si:DI=`__FUNCTION__.50'
   96: di:DI=`*.LC17'
   97: ax:QI=0
   98: call [`rhp_log'] argc:0
" ]

	node [ id 200 graphics [ fill "#d3d3d3" ] label "   99: L99:
  100: NOTE_INSN_BASIC_BLOCK 10
  101: [`rhp_n_malloc']=0
  102: [`rhp_n_free']=0
  103: r104:SI=[`rhp_dolog']
  104: flags:CCZ=cmp(r104:SI,0)
  105: pc={(flags:CCZ==0)?L119:pc}
" ]

	node [ id 201 graphics [ fill "#d3d3d3" ] label "  106: NOTE_INSN_BASIC_BLOCK 11
  107: si:DI=`__FUNCTION__.50'
  108: di:DI=`*.LC18'
  109: ax:QI=0
  110: call [`rhp_log'] argc:0
  111: r105:DI=[`rhp_logname']
  112: flags:CCZ=cmp(r105:DI,0)
  113: pc={(flags:CCZ==0)?L119:pc}
" ]

	node [ id 202 graphics [ fill "#d3d3d3" ] label "  114: NOTE_INSN_BASIC_BLOCK 12
  115: r106:DI=[`rhp_logstream']
  116: di:DI=r106:DI
  117: ax:SI=call [`fclose'] argc:0
  118: [`rhp_logname']=0
" ]

	node [ id 203 graphics [ fill "#d3d3d3" ] label "  119: L119:
  120: NOTE_INSN_BASIC_BLOCK 13
  121: [`rhp_dolog']=0
  122: [`rhp_inited']=0
" ]

	node [ id 204 graphics [ fill "#d3d3d3" ] label "  125: L125:
  126: NOTE_INSN_BASIC_BLOCK 15
" ]

	edge [ source 191 target 193 graphics [ fill "#0000ff" ] ] 
	edge [ source 193 target 194 graphics [ fill "#0000ff" ] ] 
	edge [ source 193 target 195 graphics [ fill "#000000" ] ] 
	edge [ source 194 target 204 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 195 target 196 graphics [ fill "#0000ff" ] ] 
	edge [ source 195 target 197 graphics [ fill "#000000" ] ] 
	edge [ source 196 target 197 graphics [ fill "#0000ff" ] ] 
	edge [ source 197 target 198 graphics [ fill "#0000ff" ] ] 
	edge [ source 197 target 200 graphics [ fill "#000000" ] ] 
	edge [ source 198 target 199 graphics [ fill "#0000ff" ] ] 
	edge [ source 198 target 200 graphics [ fill "#000000" ] ] 
	edge [ source 199 target 200 graphics [ fill "#0000ff" ] ] 
	edge [ source 200 target 201 graphics [ fill "#0000ff" ] ] 
	edge [ source 200 target 203 graphics [ fill "#000000" ] ] 
	edge [ source 201 target 202 graphics [ fill "#0000ff" ] ] 
	edge [ source 201 target 203 graphics [ fill "#000000" ] ] 
	edge [ source 202 target 203 graphics [ fill "#0000ff" ] ] 
	edge [ source 203 target 204 graphics [ fill "#0000ff" ] ] 
	edge [ source 204 target 192 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 5
	node [ id 436 graphics [ fill "#ffffff" ] label "rhp_addnode ()
ENTRY" ]

	node [ id 437 graphics [ fill "#ffffff" ] label "rhp_addnode ()
EXIT" ]

	node [ id 438 graphics [ fill "#d3d3d3" ] label "    6: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x14]=di:SI
    3: [r77:DI-0x18]=si:SI
    4: [r77:DI-0x20]=dx:DI
    5: NOTE_INSN_FUNCTION_BEG
    8: [r77:DI-0x8]=0
    9: [r77:DI-0x10]=0
   10: r82:SI=[`rhp_inited']
   11: flags:CCZ=cmp(r82:SI,0)
   12: pc={(flags:CCZ!=0)?L21:pc}
" ]

	node [ id 439 graphics [ fill "#d3d3d3" ] label "   13: NOTE_INSN_BASIC_BLOCK 4
   14: si:DI=`__FUNCTION__.49'
   15: di:DI=`*.LC19'
   16: ax:QI=0
   17: call [`rhp_log'] argc:0
   18: r95:SI=0x1
   19: pc=L130
" ]

	node [ id 440 graphics [ fill "#d3d3d3" ] label "   21: L21:
   22: NOTE_INSN_BASIC_BLOCK 5
   25: flags:CCGOC=cmp([r77:DI-0x14],0)
   26: pc={(flags:CCGOC&gt;=0)?L37:pc}
" ]

	node [ id 441 graphics [ fill "#d3d3d3" ] label "   27: NOTE_INSN_BASIC_BLOCK 6
   28: r97:SI=[r77:DI-0x14]
   29: dx:SI=r97:SI
   30: si:DI=`__FUNCTION__.49'
   31: di:DI=`*.LC20'
   32: ax:QI=0
   33: call [`rhp_log'] argc:0
   34: r95:SI=0x1
   35: pc=L130
" ]

	node [ id 442 graphics [ fill "#d3d3d3" ] label "   37: L37:
   38: NOTE_INSN_BASIC_BLOCK 7
   41: flags:CCGOC=cmp([r77:DI-0x18],0)
   42: pc={(flags:CCGOC&gt;=0)?L53:pc}
" ]

	node [ id 443 graphics [ fill "#d3d3d3" ] label "   43: NOTE_INSN_BASIC_BLOCK 8
   44: r98:SI=[r77:DI-0x18]
   45: dx:SI=r98:SI
   46: si:DI=`__FUNCTION__.49'
   47: di:DI=`*.LC21'
   48: ax:QI=0
   49: call [`rhp_log'] argc:0
   50: r95:SI=0x1
   51: pc=L130
" ]

	node [ id 444 graphics [ fill "#d3d3d3" ] label "   53: L53:
   54: NOTE_INSN_BASIC_BLOCK 9
   55: r99:SI=[r77:DI-0x14]
   56: r83:DI=sign_extend(r99:SI)
   57: r84:DI=[`rhp_sp_master_node_list']
   58: si:DI=r83:DI
   59: di:DI=r84:DI
   60: ax:DI=call [`rhp_sp_lookup'] argc:0
   61: r100:DI=ax:DI
   62: [r77:DI-0x8]=r100:DI
   63: flags:CCZ=cmp([r77:DI-0x8],0)
   64: pc={(flags:CCZ==0)?L75:pc}
" ]

	node [ id 445 graphics [ fill "#d3d3d3" ] label "   65: NOTE_INSN_BASIC_BLOCK 10
   66: r101:SI=[r77:DI-0x14]
   67: dx:SI=r101:SI
   68: si:DI=`__FUNCTION__.49'
   69: di:DI=`*.LC22'
   70: ax:QI=0
   71: call [`rhp_log'] argc:0
   72: r95:SI=0x1
   73: pc=L130
" ]

	node [ id 446 graphics [ fill "#d3d3d3" ] label "   75: L75:
   76: NOTE_INSN_BASIC_BLOCK 11
   77: dx:SI=0x34a
   78: si:DI=`__FUNCTION__.49'
   79: di:DI=0x50
   80: ax:DI=call [`rhp_malloc'] argc:0
   81: r102:DI=ax:DI
   82: [r77:DI-0x10]=r102:DI
   83: r85:SI=[`rhp_uniq_nodenum']
   84: r103:DI=[r77:DI-0x10]
   85: [r103:DI]=r85:SI
   86: r86:SI=[`rhp_uniq_nodenum']
   87: {r87:SI=r86:SI+0x1;clobber flags:CC;}
   88: [`rhp_uniq_nodenum']=r87:SI
   89: r104:DI=[r77:DI-0x10]
   90: r105:SI=[r77:DI-0x14]
   91: [r104:DI+0x4]=r105:SI
   92: r106:DI=[r77:DI-0x10]
   93: r107:SI=[r77:DI-0x18]
   94: [r106:DI+0x8]=r107:SI
   95: r108:DI=[r77:DI-0x10]
   96: r109:DI=[r77:DI-0x20]
   97: [r108:DI+0x10]=r109:DI
   98: r88:DI=[r77:DI-0x10]
   99: r110:SI=[r77:DI-0x14]
  100: r89:DI=sign_extend(r110:SI)
  101: r90:DI=[`rhp_sp_master_node_list']
  102: dx:DI=r88:DI
  103: si:DI=r89:DI
  104: di:DI=r90:DI
  105: call [`rhp_sp_insert'] argc:0
  106: r91:SI=[`rhp_maxlevel']
  107: flags:CCGC=cmp([r77:DI-0x18],r91:SI)
  108: pc={(flags:CCGC&lt;0)?L115:pc}
" ]

	node [ id 447 graphics [ fill "#d3d3d3" ] label "  109: NOTE_INSN_BASIC_BLOCK 12
  110: r111:SI=[r77:DI-0x18]
  111: [`rhp_maxlevel']=r111:SI
  112: r92:SI=[`rhp_maxlevel']
  113: {r93:SI=r92:SI+0x1;clobber flags:CC;}
  114: [`rhp_nlevels']=r93:SI
" ]

	node [ id 448 graphics [ fill "#d3d3d3" ] label "  115: L115:
  116: NOTE_INSN_BASIC_BLOCK 13
  117: r94:SI=[`rhp_maxlevel']
  118: r112:DI=[r77:DI-0x20]
  119: r113:SI=[r77:DI-0x18]
  120: r114:SI=[r77:DI-0x14]
  121: r9:SI=r94:SI
  122: r8:DI=r112:DI
  123: cx:SI=r113:SI
  124: dx:SI=r114:SI
  125: si:DI=`__FUNCTION__.49'
  126: di:DI=`*.LC23'
  127: ax:QI=0
  128: call [`rhp_log'] argc:0
  129: r95:SI=0
" ]

	node [ id 449 graphics [ fill "#d3d3d3" ] label "  130: L130:
  131: NOTE_INSN_BASIC_BLOCK 14
  132: r96:SI=r95:SI
  136: ax:SI=r96:SI
  137: use ax:SI
" ]

	edge [ source 436 target 438 graphics [ fill "#0000ff" ] ] 
	edge [ source 438 target 439 graphics [ fill "#0000ff" ] ] 
	edge [ source 438 target 440 graphics [ fill "#000000" ] ] 
	edge [ source 439 target 449 graphics [ fill "#000000" ] ] 
	edge [ source 440 target 441 graphics [ fill "#0000ff" ] ] 
	edge [ source 440 target 442 graphics [ fill "#000000" ] ] 
	edge [ source 441 target 449 graphics [ fill "#000000" ] ] 
	edge [ source 442 target 443 graphics [ fill "#0000ff" ] ] 
	edge [ source 442 target 444 graphics [ fill "#000000" ] ] 
	edge [ source 443 target 449 graphics [ fill "#000000" ] ] 
	edge [ source 444 target 445 graphics [ fill "#0000ff" ] ] 
	edge [ source 444 target 446 graphics [ fill "#000000" ] ] 
	edge [ source 445 target 449 graphics [ fill "#000000" ] ] 
	edge [ source 446 target 447 graphics [ fill "#0000ff" ] ] 
	edge [ source 446 target 448 graphics [ fill "#000000" ] ] 
	edge [ source 447 target 448 graphics [ fill "#0000ff" ] ] 
	edge [ source 448 target 449 graphics [ fill "#0000ff" ] ] 
	edge [ source 449 target 437 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 6
	node [ id 674 graphics [ fill "#ffffff" ] label "rhp_addedge ()
ENTRY" ]

	node [ id 675 graphics [ fill "#ffffff" ] label "rhp_addedge ()
EXIT" ]

	node [ id 676 graphics [ fill "#d3d3d3" ] label "    7: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x44]=di:SI
    3: [r77:DI-0x48]=si:SI
    4: [r77:DI-0x4c]=dx:SI
    5: [r77:DI-0x58]=cx:DI
    6: NOTE_INSN_FUNCTION_BEG
    9: [r77:DI-0x8]=0
   10: [r77:DI-0x10]=0
   11: [r77:DI-0x18]=0
   12: [r77:DI-0x20]=0
   13: [r77:DI-0x28]=0
   14: [r77:DI-0x30]=0
   15: [r77:DI-0x34]=0
   16: r82:SI=[`rhp_inited']
   17: flags:CCZ=cmp(r82:SI,0)
   18: pc={(flags:CCZ!=0)?L27:pc}
" ]

	node [ id 677 graphics [ fill "#d3d3d3" ] label "   19: NOTE_INSN_BASIC_BLOCK 4
   20: si:DI=`__FUNCTION__.48'
   21: di:DI=`*.LC19'
   22: ax:QI=0
   23: call [`rhp_log'] argc:0
   24: r107:SI=0x1
   25: pc=L296
" ]

	node [ id 678 graphics [ fill "#d3d3d3" ] label "   27: L27:
   28: NOTE_INSN_BASIC_BLOCK 5
   29: r83:DI=[`rhp_sp_master_node_list']
   30: di:DI=r83:DI
   31: ax:SI=call [`rhp_sp_has_data'] argc:0
   32: r84:SI=ax:SI
   33: flags:CCZ=cmp(r84:SI,0)
   34: pc={(flags:CCZ!=0)?L47:pc}
" ]

	node [ id 679 graphics [ fill "#d3d3d3" ] label "   35: NOTE_INSN_BASIC_BLOCK 6
   36: r109:SI=[r77:DI-0x4c]
   37: r110:SI=[r77:DI-0x48]
   38: cx:SI=r109:SI
   39: dx:SI=r110:SI
   40: si:DI=`__FUNCTION__.48'
   41: di:DI=`*.LC24'
   42: ax:QI=0
   43: call [`rhp_log'] argc:0
   44: r107:SI=0x1
   45: pc=L296
" ]

	node [ id 680 graphics [ fill "#d3d3d3" ] label "   47: L47:
   48: NOTE_INSN_BASIC_BLOCK 7
   51: flags:CCGOC=cmp([r77:DI-0x44],0)
   52: pc={(flags:CCGOC&gt;=0)?L63:pc}
" ]

	node [ id 681 graphics [ fill "#d3d3d3" ] label "   53: NOTE_INSN_BASIC_BLOCK 8
   54: r111:SI=[r77:DI-0x44]
   55: dx:SI=r111:SI
   56: si:DI=`__FUNCTION__.48'
   57: di:DI=`*.LC25'
   58: ax:QI=0
   59: call [`rhp_log'] argc:0
   60: r107:SI=0x1
   61: pc=L296
" ]

	node [ id 682 graphics [ fill "#d3d3d3" ] label "   63: L63:
   64: NOTE_INSN_BASIC_BLOCK 9
   67: flags:CCGOC=cmp([r77:DI-0x48],0)
   68: pc={(flags:CCGOC&gt;=0)?L79:pc}
" ]

	node [ id 683 graphics [ fill "#d3d3d3" ] label "   69: NOTE_INSN_BASIC_BLOCK 10
   70: r112:SI=[r77:DI-0x48]
   71: dx:SI=r112:SI
   72: si:DI=`__FUNCTION__.48'
   73: di:DI=`*.LC26'
   74: ax:QI=0
   75: call [`rhp_log'] argc:0
   76: r107:SI=0x1
   77: pc=L296
" ]

	node [ id 684 graphics [ fill "#d3d3d3" ] label "   79: L79:
   80: NOTE_INSN_BASIC_BLOCK 11
   83: flags:CCGOC=cmp([r77:DI-0x4c],0)
   84: pc={(flags:CCGOC&gt;=0)?L95:pc}
" ]

	node [ id 685 graphics [ fill "#d3d3d3" ] label "   85: NOTE_INSN_BASIC_BLOCK 12
   86: r113:SI=[r77:DI-0x4c]
   87: dx:SI=r113:SI
   88: si:DI=`__FUNCTION__.48'
   89: di:DI=`*.LC27'
   90: ax:QI=0
   91: call [`rhp_log'] argc:0
   92: r107:SI=0x1
   93: pc=L296
" ]

	node [ id 686 graphics [ fill "#d3d3d3" ] label "   95: L95:
   96: NOTE_INSN_BASIC_BLOCK 13
   97: r114:SI=[r77:DI-0x44]
   98: r85:DI=sign_extend(r114:SI)
   99: r86:DI=[`rhp_sp_master_edge_list']
  100: si:DI=r85:DI
  101: di:DI=r86:DI
  102: ax:DI=call [`rhp_sp_lookup'] argc:0
  103: r115:DI=ax:DI
  104: [r77:DI-0x8]=r115:DI
  105: flags:CCZ=cmp([r77:DI-0x8],0)
  106: pc={(flags:CCZ==0)?L121:pc}
" ]

	node [ id 687 graphics [ fill "#d3d3d3" ] label "  107: NOTE_INSN_BASIC_BLOCK 14
  108: r116:SI=[r77:DI-0x4c]
  109: r117:SI=[r77:DI-0x48]
  110: r118:SI=[r77:DI-0x44]
  111: r8:SI=r116:SI
  112: cx:SI=r117:SI
  113: dx:SI=r118:SI
  114: si:DI=`__FUNCTION__.48'
  115: di:DI=`*.LC28'
  116: ax:QI=0
  117: call [`rhp_log'] argc:0
  118: r107:SI=0x1
  119: pc=L296
" ]

	node [ id 688 graphics [ fill "#d3d3d3" ] label "  121: L121:
  122: NOTE_INSN_BASIC_BLOCK 15
  123: r119:SI=[r77:DI-0x48]
  124: r87:DI=sign_extend(r119:SI)
  125: r88:DI=[`rhp_sp_master_node_list']
  126: si:DI=r87:DI
  127: di:DI=r88:DI
  128: ax:DI=call [`rhp_sp_lookup'] argc:0
  129: r120:DI=ax:DI
  130: [r77:DI-0x10]=r120:DI
  131: flags:CCZ=cmp([r77:DI-0x10],0)
  132: pc={(flags:CCZ!=0)?L147:pc}
" ]

	node [ id 689 graphics [ fill "#d3d3d3" ] label "  133: NOTE_INSN_BASIC_BLOCK 16
  134: r121:SI=[r77:DI-0x4c]
  135: r122:SI=[r77:DI-0x48]
  136: r123:SI=[r77:DI-0x48]
  137: r8:SI=r121:SI
  138: cx:SI=r122:SI
  139: dx:SI=r123:SI
  140: si:DI=`__FUNCTION__.48'
  141: di:DI=`*.LC29'
  142: ax:QI=0
  143: call [`rhp_log'] argc:0
  144: r107:SI=0x1
  145: pc=L296
" ]

	node [ id 690 graphics [ fill "#d3d3d3" ] label "  147: L147:
  148: NOTE_INSN_BASIC_BLOCK 17
  149: r124:DI=[r77:DI-0x10]
  150: r89:DI=[r124:DI+0x8]
  151: [r77:DI-0x20]=r89:DI
  152: r125:SI=[r77:DI-0x4c]
  153: r90:DI=sign_extend(r125:SI)
  154: r91:DI=[`rhp_sp_master_node_list']
  155: si:DI=r90:DI
  156: di:DI=r91:DI
  157: ax:DI=call [`rhp_sp_lookup'] argc:0
  158: r126:DI=ax:DI
  159: [r77:DI-0x18]=r126:DI
  160: flags:CCZ=cmp([r77:DI-0x18],0)
  161: pc={(flags:CCZ!=0)?L176:pc}
" ]

	node [ id 691 graphics [ fill "#d3d3d3" ] label "  162: NOTE_INSN_BASIC_BLOCK 18
  163: r127:SI=[r77:DI-0x4c]
  164: r128:SI=[r77:DI-0x48]
  165: r129:SI=[r77:DI-0x4c]
  166: r8:SI=r127:SI
  167: cx:SI=r128:SI
  168: dx:SI=r129:SI
  169: si:DI=`__FUNCTION__.48'
  170: di:DI=`*.LC30'
  171: ax:QI=0
  172: call [`rhp_log'] argc:0
  173: r107:SI=0x1
  174: pc=L296
" ]

	node [ id 692 graphics [ fill "#d3d3d3" ] label "  176: L176:
  177: NOTE_INSN_BASIC_BLOCK 19
  178: r130:DI=[r77:DI-0x18]
  179: r92:DI=[r130:DI+0x8]
  180: [r77:DI-0x28]=r92:DI
  181: r131:DI=[r77:DI-0x28]
  182: r93:SI=[r131:DI+0x8]
  183: r132:DI=[r77:DI-0x20]
  184: r94:SI=[r132:DI+0x8]
  185: {r133:SI=r93:SI-r94:SI;clobber flags:CC;}
  186: [r77:DI-0x34]=r133:SI
  187: flags:CCZ=cmp([r77:DI-0x34],0x1)
  188: pc={(flags:CCZ==0)?L211:pc}
" ]

	node [ id 693 graphics [ fill "#d3d3d3" ] label "  189: NOTE_INSN_BASIC_BLOCK 20
  190: r134:DI=[r77:DI-0x28]
  191: r95:SI=[r134:DI+0x8]
  192: r135:DI=[r77:DI-0x20]
  193: r96:SI=[r135:DI+0x8]
  194: r136:SI=[r77:DI-0x4c]
  195: r137:SI=[r77:DI-0x48]
  196: r138:SI=[r77:DI-0x34]
  197: {sp:DI=sp:DI-0x8;clobber flags:CC;}
      REG_ARGS_SIZE 0x8
  198: [pre sp:DI+=0xfffffffffffffff8]=r95:SI
      REG_ARGS_SIZE 0x10
  199: r9:SI=r96:SI
  200: r8:SI=r136:SI
  201: cx:SI=r137:SI
  202: dx:SI=r138:SI
  203: si:DI=`__FUNCTION__.48'
  204: di:DI=`*.LC31'
  205: ax:QI=0
  206: call [`rhp_log'] argc:0x10
  207: {sp:DI=sp:DI+0x10;clobber flags:CC;}
      REG_ARGS_SIZE 0
  208: r107:SI=0x1
  209: pc=L296
" ]

	node [ id 694 graphics [ fill "#d3d3d3" ] label "  211: L211:
  212: NOTE_INSN_BASIC_BLOCK 21
  213: r139:DI=[r77:DI-0x28]
  214: r97:SI=[r139:DI+0x8]
  215: r140:DI=[r77:DI-0x20]
  216: r98:SI=[r140:DI+0x8]
  217: flags:CCGC=cmp(r97:SI,r98:SI)
  218: pc={(flags:CCGC&gt;=0)?L241:pc}
" ]

	node [ id 695 graphics [ fill "#d3d3d3" ] label "  219: NOTE_INSN_BASIC_BLOCK 22
  220: r141:DI=[r77:DI-0x28]
  221: r99:SI=[r141:DI+0x8]
  222: r142:DI=[r77:DI-0x20]
  223: r100:SI=[r142:DI+0x8]
  224: r143:SI=[r77:DI-0x4c]
  225: r144:SI=[r77:DI-0x48]
  226: r145:SI=[r77:DI-0x34]
  227: {sp:DI=sp:DI-0x8;clobber flags:CC;}
      REG_ARGS_SIZE 0x8
  228: [pre sp:DI+=0xfffffffffffffff8]=r99:SI
      REG_ARGS_SIZE 0x10
  229: r9:SI=r100:SI
  230: r8:SI=r143:SI
  231: cx:SI=r144:SI
  232: dx:SI=r145:SI
  233: si:DI=`__FUNCTION__.48'
  234: di:DI=`*.LC32'
  235: ax:QI=0
  236: call [`rhp_log'] argc:0x10
  237: {sp:DI=sp:DI+0x10;clobber flags:CC;}
      REG_ARGS_SIZE 0
  238: r107:SI=0x1
  239: pc=L296
" ]

	node [ id 696 graphics [ fill "#d3d3d3" ] label "  241: L241:
  242: NOTE_INSN_BASIC_BLOCK 23
  243: dx:SI=0x3c2
  244: si:DI=`__FUNCTION__.48'
  245: di:DI=0x38
  246: ax:DI=call [`rhp_malloc'] argc:0
  247: r146:DI=ax:DI
  248: [r77:DI-0x30]=r146:DI
  249: r101:SI=[`rhp_uniq_edgenum']
  250: r147:DI=[r77:DI-0x30]
  251: [r147:DI]=r101:SI
  252: r102:SI=[`rhp_uniq_edgenum']
  253: {r103:SI=r102:SI+0x1;clobber flags:CC;}
  254: [`rhp_uniq_edgenum']=r103:SI
  255: r148:DI=[r77:DI-0x30]
  256: r149:SI=[r77:DI-0x44]
  257: [r148:DI+0x4]=r149:SI
  258: r150:DI=[r77:DI-0x30]
  259: r151:DI=[r77:DI-0x20]
  260: [r150:DI+0x8]=r151:DI
  261: r152:DI=[r77:DI-0x30]
  262: r153:DI=[r77:DI-0x28]
  263: [r152:DI+0x10]=r153:DI
  264: r154:DI=[r77:DI-0x30]
  265: r155:DI=[r77:DI-0x58]
  266: [r154:DI+0x18]=r155:DI
  267: r156:DI=[r77:DI-0x30]
  268: r157:DI=[r77:DI-0x28]
  269: [r156:DI+0x20]=r157:DI
  270: r158:DI=[r77:DI-0x30]
  271: r159:DI=[r77:DI-0x20]
  272: [r158:DI+0x28]=r159:DI
  273: r160:DI=[r77:DI-0x30]
  274: [r160:DI+0x30]=0
  275: r104:DI=[r77:DI-0x30]
  276: r161:SI=[r77:DI-0x44]
  277: r105:DI=sign_extend(r161:SI)
  278: r106:DI=[`rhp_sp_master_edge_list']
  279: dx:DI=r104:DI
  280: si:DI=r105:DI
  281: di:DI=r106:DI
  282: call [`rhp_sp_insert'] argc:0
  283: r162:DI=[r77:DI-0x58]
  284: r163:SI=[r77:DI-0x4c]
  285: r164:SI=[r77:DI-0x48]
  286: r165:SI=[r77:DI-0x44]
  287: r9:DI=r162:DI
  288: r8:SI=r163:SI
  289: cx:SI=r164:SI
  290: dx:SI=r165:SI
  291: si:DI=`__FUNCTION__.48'
  292: di:DI=`*.LC33'
  293: ax:QI=0
  294: call [`rhp_log'] argc:0
  295: r107:SI=0
" ]

	node [ id 697 graphics [ fill "#d3d3d3" ] label "  296: L296:
  297: NOTE_INSN_BASIC_BLOCK 24
  298: r108:SI=r107:SI
  302: ax:SI=r108:SI
  303: use ax:SI
" ]

	edge [ source 674 target 676 graphics [ fill "#0000ff" ] ] 
	edge [ source 676 target 677 graphics [ fill "#0000ff" ] ] 
	edge [ source 676 target 678 graphics [ fill "#000000" ] ] 
	edge [ source 677 target 697 graphics [ fill "#000000" ] ] 
	edge [ source 678 target 679 graphics [ fill "#0000ff" ] ] 
	edge [ source 678 target 680 graphics [ fill "#000000" ] ] 
	edge [ source 679 target 697 graphics [ fill "#000000" ] ] 
	edge [ source 680 target 681 graphics [ fill "#0000ff" ] ] 
	edge [ source 680 target 682 graphics [ fill "#000000" ] ] 
	edge [ source 681 target 697 graphics [ fill "#000000" ] ] 
	edge [ source 682 target 683 graphics [ fill "#0000ff" ] ] 
	edge [ source 682 target 684 graphics [ fill "#000000" ] ] 
	edge [ source 683 target 697 graphics [ fill "#000000" ] ] 
	edge [ source 684 target 685 graphics [ fill "#0000ff" ] ] 
	edge [ source 684 target 686 graphics [ fill "#000000" ] ] 
	edge [ source 685 target 697 graphics [ fill "#000000" ] ] 
	edge [ source 686 target 687 graphics [ fill "#0000ff" ] ] 
	edge [ source 686 target 688 graphics [ fill "#000000" ] ] 
	edge [ source 687 target 697 graphics [ fill "#000000" ] ] 
	edge [ source 688 target 689 graphics [ fill "#0000ff" ] ] 
	edge [ source 688 target 690 graphics [ fill "#000000" ] ] 
	edge [ source 689 target 697 graphics [ fill "#000000" ] ] 
	edge [ source 690 target 691 graphics [ fill "#0000ff" ] ] 
	edge [ source 690 target 692 graphics [ fill "#000000" ] ] 
	edge [ source 691 target 697 graphics [ fill "#000000" ] ] 
	edge [ source 692 target 693 graphics [ fill "#0000ff" ] ] 
	edge [ source 692 target 694 graphics [ fill "#000000" ] ] 
	edge [ source 693 target 697 graphics [ fill "#000000" ] ] 
	edge [ source 694 target 695 graphics [ fill "#0000ff" ] ] 
	edge [ source 694 target 696 graphics [ fill "#000000" ] ] 
	edge [ source 695 target 697 graphics [ fill "#000000" ] ] 
	edge [ source 696 target 697 graphics [ fill "#0000ff" ] ] 
	edge [ source 697 target 675 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 7
	node [ id 1082 graphics [ fill "#ffffff" ] label "rhp_layout ()
ENTRY" ]

	node [ id 1083 graphics [ fill "#ffffff" ] label "rhp_layout ()
EXIT" ]

	node [ id 1084 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x14]=di:SI
    3: [r77:DI-0x18]=si:SI
    4: NOTE_INSN_FUNCTION_BEG
    7: [r77:DI-0x8]=0
    9: flags:CCZ=cmp([r77:DI-0x18],0)
   10: pc={(flags:CCZ==0)?L15:pc}
" ]

	node [ id 1085 graphics [ fill "#d3d3d3" ] label "   11: NOTE_INSN_BASIC_BLOCK 5
   12: [`rhp_adjustweight']=0x1
   13: pc=L18
" ]

	node [ id 1086 graphics [ fill "#d3d3d3" ] label "   15: L15:
   16: NOTE_INSN_BASIC_BLOCK 6
   17: [`rhp_adjustweight']=0
" ]

	node [ id 1087 graphics [ fill "#d3d3d3" ] label "   18: L18:
   19: NOTE_INSN_BASIC_BLOCK 7
   20: r82:SI=[`rhp_adjustweight']
   21: dx:SI=r82:SI
   22: si:DI=`__FUNCTION__.47'
   23: di:DI=`*.LC34'
   24: ax:QI=0
   25: call [`rhp_log'] argc:0
   26: r83:SI=[`rhp_inited']
   27: flags:CCZ=cmp(r83:SI,0)
   28: pc={(flags:CCZ!=0)?L36:pc}
" ]

	node [ id 1088 graphics [ fill "#d3d3d3" ] label "   29: NOTE_INSN_BASIC_BLOCK 8
   30: si:DI=`__FUNCTION__.47'
   31: di:DI=`*.LC15'
   32: ax:QI=0
   33: call [`rhp_log'] argc:0
   34: pc=L126
" ]

	node [ id 1089 graphics [ fill "#d3d3d3" ] label "   36: L36:
   37: NOTE_INSN_BASIC_BLOCK 9
   38: r84:DI=[`rhp_sp_master_node_list']
   39: di:DI=r84:DI
   40: ax:SI=call [`rhp_sp_has_data'] argc:0
   41: r85:SI=ax:SI
   42: flags:CCZ=cmp(r85:SI,0)
   43: pc={(flags:CCZ!=0)?L51:pc}
" ]

	node [ id 1090 graphics [ fill "#d3d3d3" ] label "   44: NOTE_INSN_BASIC_BLOCK 10
   45: si:DI=`__FUNCTION__.47'
   46: di:DI=`*.LC35'
   47: ax:QI=0
   48: call [`rhp_log'] argc:0
   49: pc=L126
" ]

	node [ id 1091 graphics [ fill "#d3d3d3" ] label "   51: L51:
   52: NOTE_INSN_BASIC_BLOCK 11
   53: [`rhp_improvements']=0
   54: [`rhp_notimprovements']=0
   55: r86:DI=[`rhp_crossings']
   56: r87:DI=[`rhp_start_crossings']
   57: cx:DI=r86:DI
   58: dx:DI=r87:DI
   59: si:DI=`__FUNCTION__.47'
   60: di:DI=`*.LC36'
   61: ax:QI=0
   62: call [`rhp_log'] argc:0
   63: ax:DI=call [`rhp_initial_crossings'] argc:0
   64: r88:DI=ax:DI
   65: [`rhp_crossings']=r88:DI
   66: r89:DI=[`rhp_crossings']
   67: r90:DI=[`rhp_start_crossings']
   68: cx:DI=r89:DI
   69: dx:DI=r90:DI
   70: si:DI=`__FUNCTION__.47'
   71: di:DI=`*.LC37'
   72: ax:QI=0
   73: call [`rhp_log'] argc:0
   74: call [`rhp_order_init'] argc:0
   75: r91:DI=[`rhp_start_crossings']
   76: flags:CCZ=cmp(r91:DI,0)
   77: pc={(flags:CCZ==0)?L80:pc}
" ]

	node [ id 1092 graphics [ fill "#d3d3d3" ] label "   78: NOTE_INSN_BASIC_BLOCK 12
   79: call [`rhp_barycenter'] argc:0
" ]

	node [ id 1093 graphics [ fill "#d3d3d3" ] label "   80: L80:
   81: NOTE_INSN_BASIC_BLOCK 13
   82: r92:DI=[`rhp_start_crossings']
   83: flags:CCZ=cmp(r92:DI,0)
   84: pc={(flags:CCZ==0)?L106:pc}
" ]

	node [ id 1094 graphics [ fill "#d3d3d3" ] label "   85: NOTE_INSN_BASIC_BLOCK 14
   86: r93:DI=[`rhp_crossings']
   87: r99:DI=r93:DI
   88: {r99:DI=r99:DI&lt;&lt;0x2;clobber flags:CC;}
   89: {r99:DI=r99:DI+r93:DI;clobber flags:CC;}
      REG_EQUAL r93:DI*0x5
   90: {r100:DI=r99:DI&lt;&lt;0x2;clobber flags:CC;}
   91: {r99:DI=r99:DI+r100:DI;clobber flags:CC;}
      REG_EQUAL r93:DI*0x19
   92: {r101:DI=r99:DI&lt;&lt;0x2;clobber flags:CC;}
   93: r99:DI=r101:DI
      REG_EQUAL r93:DI*0x64
   94: r94:DI=r99:DI
   95: r95:DI=[`rhp_start_crossings']
   96: {r102:DI=r94:DI/r95:DI;r103:DI=r94:DI%r95:DI;clobber flags:CC;}
   97: [r77:DI-0x8]=r102:DI
  101: r107:DI=0x64
  102: {r106:DI=r107:DI-[r77:DI-0x8];clobber flags:CC;}
  103: [r77:DI-0x8]=r106:DI
  104: pc=L109
" ]

	node [ id 1095 graphics [ fill "#d3d3d3" ] label "  106: L106:
  107: NOTE_INSN_BASIC_BLOCK 15
  108: [r77:DI-0x8]=0
" ]

	node [ id 1096 graphics [ fill "#d3d3d3" ] label "  109: L109:
  110: NOTE_INSN_BASIC_BLOCK 16
  111: call [`rhp_sorted_nodelist'] argc:0
  112: r96:DI=[`rhp_start_crossings']
  113: r97:SI=[`rhp_iter']
  114: r98:DI=[`rhp_crossings']
  115: r108:DI=[r77:DI-0x8]
  116: r9:DI=r108:DI
  117: r8:DI=r96:DI
  118: cx:SI=r97:SI
  119: dx:DI=r98:DI
  120: si:DI=`__FUNCTION__.47'
  121: di:DI=`*.LC38'
  122: ax:QI=0
  123: call [`rhp_log'] argc:0
" ]

	node [ id 1097 graphics [ fill "#d3d3d3" ] label "  126: L126:
  127: NOTE_INSN_BASIC_BLOCK 18
" ]

	edge [ source 1082 target 1084 graphics [ fill "#0000ff" ] ] 
	edge [ source 1084 target 1085 graphics [ fill "#0000ff" ] ] 
	edge [ source 1084 target 1086 graphics [ fill "#000000" ] ] 
	edge [ source 1085 target 1087 graphics [ fill "#000000" ] ] 
	edge [ source 1086 target 1087 graphics [ fill "#0000ff" ] ] 
	edge [ source 1087 target 1088 graphics [ fill "#0000ff" ] ] 
	edge [ source 1087 target 1089 graphics [ fill "#000000" ] ] 
	edge [ source 1088 target 1097 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 1089 target 1090 graphics [ fill "#0000ff" ] ] 
	edge [ source 1089 target 1091 graphics [ fill "#000000" ] ] 
	edge [ source 1090 target 1097 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 1091 target 1092 graphics [ fill "#0000ff" ] ] 
	edge [ source 1091 target 1093 graphics [ fill "#000000" ] ] 
	edge [ source 1092 target 1093 graphics [ fill "#0000ff" ] ] 
	edge [ source 1093 target 1094 graphics [ fill "#0000ff" ] ] 
	edge [ source 1093 target 1095 graphics [ fill "#000000" ] ] 
	edge [ source 1094 target 1096 graphics [ fill "#000000" ] ] 
	edge [ source 1095 target 1096 graphics [ fill "#0000ff" ] ] 
	edge [ source 1096 target 1097 graphics [ fill "#0000ff" ] ] 
	edge [ source 1097 target 1083 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 8
	node [ id 1361 graphics [ fill "#ffffff" ] label "rhp_layout_callback ()
ENTRY" ]

	node [ id 1362 graphics [ fill "#ffffff" ] label "rhp_layout_callback ()
EXIT" ]

	node [ id 1363 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x8]=di:DI
    3: NOTE_INSN_FUNCTION_BEG
    6: flags:CCZ=cmp([r77:DI-0x8],0)
    7: pc={(flags:CCZ!=0)?L15:pc}
" ]

	node [ id 1364 graphics [ fill "#d3d3d3" ] label "    8: NOTE_INSN_BASIC_BLOCK 4
    9: si:DI=`__FUNCTION__.46'
   10: di:DI=`*.LC39'
   11: ax:QI=0
   12: call [`rhp_log'] argc:0
   13: pc=L21
" ]

	node [ id 1365 graphics [ fill "#d3d3d3" ] label "   15: L15:
   16: NOTE_INSN_BASIC_BLOCK 5
   17: r82:DI=[r77:DI-0x8]
   18: [`rhp_getlayoutdata']=r82:DI
" ]

	node [ id 1366 graphics [ fill "#d3d3d3" ] label "   21: L21:
   22: NOTE_INSN_BASIC_BLOCK 7
" ]

	edge [ source 1361 target 1363 graphics [ fill "#0000ff" ] ] 
	edge [ source 1363 target 1364 graphics [ fill "#0000ff" ] ] 
	edge [ source 1363 target 1365 graphics [ fill "#000000" ] ] 
	edge [ source 1364 target 1366 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 1365 target 1366 graphics [ fill "#0000ff" ] ] 
	edge [ source 1366 target 1362 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 1470 graphics [ fill "#d3d3d3" ] label "   98: L98:
   99: NOTE_INSN_BASIC_BLOCK 13
  101: flags:CCZ=cmp([r77:DI-0x8],0)
  102: pc={(flags:CCZ!=0)?L100:pc}
" ]

	node [ id 1471 graphics [ fill "#d3d3d3" ] label "  100: L100:
   50: NOTE_INSN_BASIC_BLOCK 10
   51: r99:DI=[r77:DI-0x8]
   52: r86:DI=[r99:DI+0x8]
   53: [r77:DI-0x18]=r86:DI
   54: r100:DI=[r77:DI-0x18]
   55: r87:SI=[r100:DI+0x18]
   56: r101:DI=[r77:DI-0x18]
   57: r88:SI=[r101:DI+0x8]
   58: r102:DI=[r77:DI-0x18]
   59: r89:SI=[r102:DI+0x4]
   60: r8:SI=r87:SI
   61: cx:SI=r88:SI
   62: dx:SI=r89:SI
   63: si:DI=`__FUNCTION__.45'
   64: di:DI=`*.LC40'
   65: ax:QI=0
   66: call [`rhp_log'] argc:0
   67: r103:DI=[r77:DI-0x18]
   68: r90:DI=[r103:DI+0x10]
   69: r104:DI=[r77:DI-0x18]
   70: r91:SI=[r104:DI+0x18]
   71: r105:DI=[r77:DI-0x18]
   72: r92:SI=[r105:DI+0x8]
   73: r106:DI=[r77:DI-0x18]
   74: r93:SI=[r106:DI+0x4]
   75: r107:DI=[r77:DI-0x28]
   76: cx:DI=r90:DI
   77: dx:SI=r91:SI
   78: si:SI=r92:SI
   79: di:SI=r93:SI
   80: ax:SI=call [r107:DI] argc:0
   81: r108:SI=ax:SI
   82: [r77:DI-0xc]=r108:SI
   83: flags:CCZ=cmp([r77:DI-0xc],0)
   84: pc={(flags:CCZ==0)?L88:pc}
" ]

	node [ id 1472 graphics [ fill "#d3d3d3" ] label "   88: L88:
   89: NOTE_INSN_BASIC_BLOCK 12
   90: r109:DI=[r77:DI-0x8]
   91: r94:DI=[r109:DI]
   92: r95:DI=[`rhp_sp_master_node_list_sorted']
   93: si:DI=r94:DI
   94: di:DI=r95:DI
   95: ax:DI=call [`rhp_sp_next'] argc:0
   96: r110:DI=ax:DI
   97: [r77:DI-0x8]=r110:DI
" ]



# function number 9
	node [ id 1473 graphics [ fill "#ffffff" ] label "rhp_node_foreach ()
ENTRY" ]

	node [ id 1474 graphics [ fill "#ffffff" ] label "rhp_node_foreach ()
EXIT" ]

	node [ id 1475 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x28]=di:DI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x8]=0
    7: [r77:DI-0x18]=0
    8: [r77:DI-0xc]=0
    9: r82:SI=[`rhp_inited']
   10: flags:CCZ=cmp(r82:SI,0)
   11: pc={(flags:CCZ!=0)?L20:pc}
" ]

	node [ id 1476 graphics [ fill "#d3d3d3" ] label "   12: NOTE_INSN_BASIC_BLOCK 4
   13: si:DI=`__FUNCTION__.45'
   14: di:DI=`*.LC15'
   15: ax:QI=0
   16: call [`rhp_log'] argc:0
   17: r96:SI=0
   18: pc=L106
" ]

	node [ id 1477 graphics [ fill "#d3d3d3" ] label "   20: L20:
   21: NOTE_INSN_BASIC_BLOCK 5
   22: flags:CCZ=cmp([r77:DI-0x28],0)
   23: pc={(flags:CCZ!=0)?L28:pc}
" ]

	node [ id 1478 graphics [ fill "#d3d3d3" ] label "   24: NOTE_INSN_BASIC_BLOCK 6
   25: r96:SI=0
   26: pc=L106
" ]

	node [ id 1479 graphics [ fill "#d3d3d3" ] label "   28: L28:
   29: NOTE_INSN_BASIC_BLOCK 7
   30: r83:DI=[`rhp_sp_master_node_list_sorted']
   31: di:DI=r83:DI
   32: ax:SI=call [`rhp_sp_has_data'] argc:0
   33: r84:SI=ax:SI
   34: flags:CCZ=cmp(r84:SI,0)
   35: pc={(flags:CCZ!=0)?L40:pc}
" ]

	node [ id 1480 graphics [ fill "#d3d3d3" ] label "   36: NOTE_INSN_BASIC_BLOCK 8
   37: r96:SI=0
   38: pc=L106
" ]

	node [ id 1481 graphics [ fill "#d3d3d3" ] label "   40: L40:
   41: NOTE_INSN_BASIC_BLOCK 9
   42: [r77:DI-0xc]=0
   43: r85:DI=[`rhp_sp_master_node_list_sorted']
   44: di:DI=r85:DI
   45: ax:DI=call [`rhp_sp_min'] argc:0
   46: r98:DI=ax:DI
   47: [r77:DI-0x8]=r98:DI
   48: pc=L98
" ]

	node [ id 1482 graphics [ fill "#d3d3d3" ] label "   85: NOTE_INSN_BASIC_BLOCK 11
   86: pc=L103
" ]

	node [ id 1483 graphics [ fill "#d3d3d3" ] label "  103: L103:
  104: NOTE_INSN_BASIC_BLOCK 14
  105: r96:SI=[r77:DI-0xc]
" ]

	node [ id 1484 graphics [ fill "#d3d3d3" ] label "  106: L106:
  107: NOTE_INSN_BASIC_BLOCK 15
  108: r97:SI=r96:SI
  112: ax:SI=r97:SI
  113: use ax:SI
" ]

	edge [ source 1473 target 1475 graphics [ fill "#0000ff" ] ] 
	edge [ source 1475 target 1476 graphics [ fill "#0000ff" ] ] 
	edge [ source 1475 target 1477 graphics [ fill "#000000" ] ] 
	edge [ source 1476 target 1484 graphics [ fill "#000000" ] ] 
	edge [ source 1477 target 1478 graphics [ fill "#0000ff" ] ] 
	edge [ source 1477 target 1479 graphics [ fill "#000000" ] ] 
	edge [ source 1478 target 1484 graphics [ fill "#000000" ] ] 
	edge [ source 1479 target 1480 graphics [ fill "#0000ff" ] ] 
	edge [ source 1479 target 1481 graphics [ fill "#000000" ] ] 
	edge [ source 1480 target 1484 graphics [ fill "#000000" ] ] 
	edge [ source 1481 target 1470 graphics [ fill "#000000" ] ] 
	edge [ source 1471 target 1482 graphics [ fill "#0000ff" ] ] 
	edge [ source 1471 target 1472 graphics [ fill "#000000" ] ] 
	edge [ source 1482 target 1483 graphics [ fill "#000000" ] ] 
	edge [ source 1472 target 1470 graphics [ fill "#0000ff" ] ] 
	edge [ source 1470 target 1471 graphics [ fill "#000000" ] ] 
	edge [ source 1470 target 1483 graphics [ fill "#0000ff" ] ] 
	edge [ source 1483 target 1484 graphics [ fill "#0000ff" ] ] 
	edge [ source 1484 target 1474 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 10
	node [ id 1734 graphics [ fill "#ffffff" ] label "rhp_node_get_level ()
ENTRY" ]

	node [ id 1735 graphics [ fill "#ffffff" ] label "rhp_node_get_level ()
EXIT" ]

	node [ id 1736 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x14]=di:SI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x8]=0
    7: [r77:DI-0x10]=0
    8: r82:SI=[`rhp_inited']
    9: flags:CCZ=cmp(r82:SI,0)
   10: pc={(flags:CCZ!=0)?L19:pc}
" ]

	node [ id 1737 graphics [ fill "#d3d3d3" ] label "   11: NOTE_INSN_BASIC_BLOCK 4
   12: si:DI=`__FUNCTION__.44'
   13: di:DI=`*.LC15'
   14: ax:QI=0
   15: call [`rhp_log'] argc:0
   16: r91:SI=0xffffffffffffffff
   17: pc=L73
" ]

	node [ id 1738 graphics [ fill "#d3d3d3" ] label "   19: L19:
   20: NOTE_INSN_BASIC_BLOCK 5
   21: r83:DI=[`rhp_sp_master_node_list']
   22: di:DI=r83:DI
   23: ax:SI=call [`rhp_sp_has_data'] argc:0
   24: r84:SI=ax:SI
   25: flags:CCZ=cmp(r84:SI,0)
   26: pc={(flags:CCZ!=0)?L31:pc}
" ]

	node [ id 1739 graphics [ fill "#d3d3d3" ] label "   27: NOTE_INSN_BASIC_BLOCK 6
   28: r91:SI=0xffffffffffffffff
   29: pc=L73
" ]

	node [ id 1740 graphics [ fill "#d3d3d3" ] label "   31: L31:
   32: NOTE_INSN_BASIC_BLOCK 7
   33: r93:SI=[r77:DI-0x14]
   34: r85:DI=sign_extend(r93:SI)
   35: r86:DI=[`rhp_sp_master_node_list']
   36: si:DI=r85:DI
   37: di:DI=r86:DI
   38: ax:DI=call [`rhp_sp_lookup'] argc:0
   39: r94:DI=ax:DI
   40: [r77:DI-0x8]=r94:DI
   41: flags:CCZ=cmp([r77:DI-0x8],0)
   42: pc={(flags:CCZ!=0)?L53:pc}
" ]

	node [ id 1741 graphics [ fill "#d3d3d3" ] label "   43: NOTE_INSN_BASIC_BLOCK 8
   44: r95:SI=[r77:DI-0x14]
   45: dx:SI=r95:SI
   46: si:DI=`__FUNCTION__.44'
   47: di:DI=`*.LC41'
   48: ax:QI=0
   49: call [`rhp_log'] argc:0
   50: r91:SI=0xffffffffffffffff
   51: pc=L73
" ]

	node [ id 1742 graphics [ fill "#d3d3d3" ] label "   53: L53:
   54: NOTE_INSN_BASIC_BLOCK 9
   55: r96:DI=[r77:DI-0x8]
   56: r87:DI=[r96:DI+0x8]
   57: [r77:DI-0x10]=r87:DI
   58: r97:DI=[r77:DI-0x10]
   59: r88:SI=[r97:DI+0x18]
   60: r98:DI=[r77:DI-0x10]
   61: r89:SI=[r98:DI+0x8]
   62: r99:DI=[r77:DI-0x10]
   63: r90:SI=[r99:DI+0x4]
   64: r8:SI=r88:SI
   65: cx:SI=r89:SI
   66: dx:SI=r90:SI
   67: si:DI=`__FUNCTION__.44'
   68: di:DI=`*.LC40'
   69: ax:QI=0
   70: call [`rhp_log'] argc:0
   71: r100:DI=[r77:DI-0x10]
   72: r91:SI=[r100:DI+0x8]
" ]

	node [ id 1743 graphics [ fill "#d3d3d3" ] label "   73: L73:
   74: NOTE_INSN_BASIC_BLOCK 10
   75: r92:SI=r91:SI
   79: ax:SI=r92:SI
   80: use ax:SI
" ]

	edge [ source 1734 target 1736 graphics [ fill "#0000ff" ] ] 
	edge [ source 1736 target 1737 graphics [ fill "#0000ff" ] ] 
	edge [ source 1736 target 1738 graphics [ fill "#000000" ] ] 
	edge [ source 1737 target 1743 graphics [ fill "#000000" ] ] 
	edge [ source 1738 target 1739 graphics [ fill "#0000ff" ] ] 
	edge [ source 1738 target 1740 graphics [ fill "#000000" ] ] 
	edge [ source 1739 target 1743 graphics [ fill "#000000" ] ] 
	edge [ source 1740 target 1741 graphics [ fill "#0000ff" ] ] 
	edge [ source 1740 target 1742 graphics [ fill "#000000" ] ] 
	edge [ source 1741 target 1743 graphics [ fill "#000000" ] ] 
	edge [ source 1742 target 1743 graphics [ fill "#0000ff" ] ] 
	edge [ source 1743 target 1735 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 11
	node [ id 1904 graphics [ fill "#ffffff" ] label "rhp_node_get_position ()
ENTRY" ]

	node [ id 1905 graphics [ fill "#ffffff" ] label "rhp_node_get_position ()
EXIT" ]

	node [ id 1906 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x14]=di:SI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x8]=0
    7: [r77:DI-0x10]=0
    8: r82:SI=[`rhp_inited']
    9: flags:CCZ=cmp(r82:SI,0)
   10: pc={(flags:CCZ!=0)?L19:pc}
" ]

	node [ id 1907 graphics [ fill "#d3d3d3" ] label "   11: NOTE_INSN_BASIC_BLOCK 4
   12: si:DI=`__FUNCTION__.43'
   13: di:DI=`*.LC15'
   14: ax:QI=0
   15: call [`rhp_log'] argc:0
   16: r91:SI=0xffffffffffffffff
   17: pc=L73
" ]

	node [ id 1908 graphics [ fill "#d3d3d3" ] label "   19: L19:
   20: NOTE_INSN_BASIC_BLOCK 5
   21: r83:DI=[`rhp_sp_master_node_list']
   22: di:DI=r83:DI
   23: ax:SI=call [`rhp_sp_has_data'] argc:0
   24: r84:SI=ax:SI
   25: flags:CCZ=cmp(r84:SI,0)
   26: pc={(flags:CCZ!=0)?L31:pc}
" ]

	node [ id 1909 graphics [ fill "#d3d3d3" ] label "   27: NOTE_INSN_BASIC_BLOCK 6
   28: r91:SI=0xffffffffffffffff
   29: pc=L73
" ]

	node [ id 1910 graphics [ fill "#d3d3d3" ] label "   31: L31:
   32: NOTE_INSN_BASIC_BLOCK 7
   33: r93:SI=[r77:DI-0x14]
   34: r85:DI=sign_extend(r93:SI)
   35: r86:DI=[`rhp_sp_master_node_list']
   36: si:DI=r85:DI
   37: di:DI=r86:DI
   38: ax:DI=call [`rhp_sp_lookup'] argc:0
   39: r94:DI=ax:DI
   40: [r77:DI-0x8]=r94:DI
   41: flags:CCZ=cmp([r77:DI-0x8],0)
   42: pc={(flags:CCZ!=0)?L53:pc}
" ]

	node [ id 1911 graphics [ fill "#d3d3d3" ] label "   43: NOTE_INSN_BASIC_BLOCK 8
   44: r95:SI=[r77:DI-0x14]
   45: dx:SI=r95:SI
   46: si:DI=`__FUNCTION__.43'
   47: di:DI=`*.LC41'
   48: ax:QI=0
   49: call [`rhp_log'] argc:0
   50: r91:SI=0xffffffffffffffff
   51: pc=L73
" ]

	node [ id 1912 graphics [ fill "#d3d3d3" ] label "   53: L53:
   54: NOTE_INSN_BASIC_BLOCK 9
   55: r96:DI=[r77:DI-0x8]
   56: r87:DI=[r96:DI+0x8]
   57: [r77:DI-0x10]=r87:DI
   58: r97:DI=[r77:DI-0x10]
   59: r88:SI=[r97:DI+0x18]
   60: r98:DI=[r77:DI-0x10]
   61: r89:SI=[r98:DI+0x8]
   62: r99:DI=[r77:DI-0x10]
   63: r90:SI=[r99:DI+0x4]
   64: r8:SI=r88:SI
   65: cx:SI=r89:SI
   66: dx:SI=r90:SI
   67: si:DI=`__FUNCTION__.43'
   68: di:DI=`*.LC40'
   69: ax:QI=0
   70: call [`rhp_log'] argc:0
   71: r100:DI=[r77:DI-0x10]
   72: r91:SI=[r100:DI+0x18]
" ]

	node [ id 1913 graphics [ fill "#d3d3d3" ] label "   73: L73:
   74: NOTE_INSN_BASIC_BLOCK 10
   75: r92:SI=r91:SI
   79: ax:SI=r92:SI
   80: use ax:SI
" ]

	edge [ source 1904 target 1906 graphics [ fill "#0000ff" ] ] 
	edge [ source 1906 target 1907 graphics [ fill "#0000ff" ] ] 
	edge [ source 1906 target 1908 graphics [ fill "#000000" ] ] 
	edge [ source 1907 target 1913 graphics [ fill "#000000" ] ] 
	edge [ source 1908 target 1909 graphics [ fill "#0000ff" ] ] 
	edge [ source 1908 target 1910 graphics [ fill "#000000" ] ] 
	edge [ source 1909 target 1913 graphics [ fill "#000000" ] ] 
	edge [ source 1910 target 1911 graphics [ fill "#0000ff" ] ] 
	edge [ source 1910 target 1912 graphics [ fill "#000000" ] ] 
	edge [ source 1911 target 1913 graphics [ fill "#000000" ] ] 
	edge [ source 1912 target 1913 graphics [ fill "#0000ff" ] ] 
	edge [ source 1913 target 1905 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 12
	node [ id 2074 graphics [ fill "#ffffff" ] label "rhp_node_get_data ()
ENTRY" ]

	node [ id 2075 graphics [ fill "#ffffff" ] label "rhp_node_get_data ()
EXIT" ]

	node [ id 2076 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x14]=di:SI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x8]=0
    7: [r77:DI-0x10]=0
    8: r82:SI=[`rhp_inited']
    9: flags:CCZ=cmp(r82:SI,0)
   10: pc={(flags:CCZ!=0)?L19:pc}
" ]

	node [ id 2077 graphics [ fill "#d3d3d3" ] label "   11: NOTE_INSN_BASIC_BLOCK 4
   12: si:DI=`__FUNCTION__.42'
   13: di:DI=`*.LC15'
   14: ax:QI=0
   15: call [`rhp_log'] argc:0
   16: r91:DI=0xffffffffffffffff
   17: pc=L73
" ]

	node [ id 2078 graphics [ fill "#d3d3d3" ] label "   19: L19:
   20: NOTE_INSN_BASIC_BLOCK 5
   21: r83:DI=[`rhp_sp_master_node_list']
   22: di:DI=r83:DI
   23: ax:SI=call [`rhp_sp_has_data'] argc:0
   24: r84:SI=ax:SI
   25: flags:CCZ=cmp(r84:SI,0)
   26: pc={(flags:CCZ!=0)?L31:pc}
" ]

	node [ id 2079 graphics [ fill "#d3d3d3" ] label "   27: NOTE_INSN_BASIC_BLOCK 6
   28: r91:DI=0xffffffffffffffff
   29: pc=L73
" ]

	node [ id 2080 graphics [ fill "#d3d3d3" ] label "   31: L31:
   32: NOTE_INSN_BASIC_BLOCK 7
   33: r93:SI=[r77:DI-0x14]
   34: r85:DI=sign_extend(r93:SI)
   35: r86:DI=[`rhp_sp_master_node_list']
   36: si:DI=r85:DI
   37: di:DI=r86:DI
   38: ax:DI=call [`rhp_sp_lookup'] argc:0
   39: r94:DI=ax:DI
   40: [r77:DI-0x8]=r94:DI
   41: flags:CCZ=cmp([r77:DI-0x8],0)
   42: pc={(flags:CCZ!=0)?L53:pc}
" ]

	node [ id 2081 graphics [ fill "#d3d3d3" ] label "   43: NOTE_INSN_BASIC_BLOCK 8
   44: r95:SI=[r77:DI-0x14]
   45: dx:SI=r95:SI
   46: si:DI=`__FUNCTION__.42'
   47: di:DI=`*.LC41'
   48: ax:QI=0
   49: call [`rhp_log'] argc:0
   50: r91:DI=0xffffffffffffffff
   51: pc=L73
" ]

	node [ id 2082 graphics [ fill "#d3d3d3" ] label "   53: L53:
   54: NOTE_INSN_BASIC_BLOCK 9
   55: r96:DI=[r77:DI-0x8]
   56: r87:DI=[r96:DI+0x8]
   57: [r77:DI-0x10]=r87:DI
   58: r97:DI=[r77:DI-0x10]
   59: r88:SI=[r97:DI+0x18]
   60: r98:DI=[r77:DI-0x10]
   61: r89:SI=[r98:DI+0x8]
   62: r99:DI=[r77:DI-0x10]
   63: r90:SI=[r99:DI+0x4]
   64: r8:SI=r88:SI
   65: cx:SI=r89:SI
   66: dx:SI=r90:SI
   67: si:DI=`__FUNCTION__.42'
   68: di:DI=`*.LC40'
   69: ax:QI=0
   70: call [`rhp_log'] argc:0
   71: r100:DI=[r77:DI-0x10]
   72: r91:DI=[r100:DI+0x10]
" ]

	node [ id 2083 graphics [ fill "#d3d3d3" ] label "   73: L73:
   74: NOTE_INSN_BASIC_BLOCK 10
   75: r92:DI=r91:DI
   79: ax:DI=r92:DI
   80: use ax:DI
" ]

	edge [ source 2074 target 2076 graphics [ fill "#0000ff" ] ] 
	edge [ source 2076 target 2077 graphics [ fill "#0000ff" ] ] 
	edge [ source 2076 target 2078 graphics [ fill "#000000" ] ] 
	edge [ source 2077 target 2083 graphics [ fill "#000000" ] ] 
	edge [ source 2078 target 2079 graphics [ fill "#0000ff" ] ] 
	edge [ source 2078 target 2080 graphics [ fill "#000000" ] ] 
	edge [ source 2079 target 2083 graphics [ fill "#000000" ] ] 
	edge [ source 2080 target 2081 graphics [ fill "#0000ff" ] ] 
	edge [ source 2080 target 2082 graphics [ fill "#000000" ] ] 
	edge [ source 2081 target 2083 graphics [ fill "#000000" ] ] 
	edge [ source 2082 target 2083 graphics [ fill "#0000ff" ] ] 
	edge [ source 2083 target 2075 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 2244 graphics [ fill "#d3d3d3" ] label "  108: L108:
  109: NOTE_INSN_BASIC_BLOCK 13
  111: flags:CCZ=cmp([r77:DI-0x8],0)
  112: pc={(flags:CCZ!=0)?L110:pc}
" ]

	node [ id 2245 graphics [ fill "#d3d3d3" ] label "  110: L110:
   50: NOTE_INSN_BASIC_BLOCK 10
   51: r107:DI=[r77:DI-0x8]
   52: r86:DI=[r107:DI+0x8]
   53: [r77:DI-0x18]=r86:DI
   54: r108:DI=[r77:DI-0x18]
   55: r87:DI=[r108:DI+0x18]
   56: r109:DI=[r77:DI-0x18]
   57: r88:DI=[r109:DI+0x30]
   58: r110:DI=[r77:DI-0x18]
   59: r89:DI=[r110:DI+0x10]
   60: r90:SI=[r89:DI+0x18]
   61: r111:DI=[r77:DI-0x18]
   62: r91:DI=[r111:DI+0x10]
   63: r92:SI=[r91:DI+0x8]
   64: r112:DI=[r77:DI-0x18]
   65: r93:DI=[r112:DI+0x10]
   66: r94:SI=[r93:DI+0x4]
   67: r113:DI=[r77:DI-0x18]
   68: r95:DI=[r113:DI+0x8]
   69: r96:SI=[r95:DI+0x18]
   70: r114:DI=[r77:DI-0x18]
   71: r97:DI=[r114:DI+0x8]
   72: r98:SI=[r97:DI+0x8]
   73: r115:DI=[r77:DI-0x18]
   74: r99:DI=[r115:DI+0x8]
   75: r100:SI=[r99:DI+0x4]
   76: r116:DI=[r77:DI-0x18]
   77: r101:SI=[r116:DI+0x4]
   78: {sp:DI=sp:DI-0x8;clobber flags:CC;}
      REG_ARGS_SIZE 0x8
   79: [--sp:DI]=r87:DI
      REG_ARGS_SIZE 0x10
   80: [--sp:DI]=r88:DI
      REG_ARGS_SIZE 0x18
   81: [pre sp:DI+=0xfffffffffffffff8]=r90:SI
      REG_ARGS_SIZE 0x20
   82: r117:DI=[r77:DI-0x28]
   83: r9:SI=r92:SI
   84: r8:SI=r94:SI
   85: cx:SI=r96:SI
   86: dx:SI=r98:SI
   87: si:SI=r100:SI
   88: di:SI=r101:SI
   89: ax:SI=call [r117:DI] argc:0x20
   90: {sp:DI=sp:DI+0x20;clobber flags:CC;}
      REG_ARGS_SIZE 0
   91: r118:SI=ax:SI
   92: [r77:DI-0xc]=r118:SI
   93: flags:CCZ=cmp([r77:DI-0xc],0)
   94: pc={(flags:CCZ==0)?L98:pc}
" ]

	node [ id 2246 graphics [ fill "#d3d3d3" ] label "   98: L98:
   99: NOTE_INSN_BASIC_BLOCK 12
  100: r119:DI=[r77:DI-0x8]
  101: r102:DI=[r119:DI]
  102: r103:DI=[`rhp_sp_master_edge_list']
  103: si:DI=r102:DI
  104: di:DI=r103:DI
  105: ax:DI=call [`rhp_sp_next'] argc:0
  106: r120:DI=ax:DI
  107: [r77:DI-0x8]=r120:DI
" ]



# function number 13
	node [ id 2247 graphics [ fill "#ffffff" ] label "rhp_edge_foreach ()
ENTRY" ]

	node [ id 2248 graphics [ fill "#ffffff" ] label "rhp_edge_foreach ()
EXIT" ]

	node [ id 2249 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x28]=di:DI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x8]=0
    7: [r77:DI-0x18]=0
    8: [r77:DI-0xc]=0
    9: r82:SI=[`rhp_inited']
   10: flags:CCZ=cmp(r82:SI,0)
   11: pc={(flags:CCZ!=0)?L20:pc}
" ]

	node [ id 2250 graphics [ fill "#d3d3d3" ] label "   12: NOTE_INSN_BASIC_BLOCK 4
   13: si:DI=`__FUNCTION__.41'
   14: di:DI=`*.LC15'
   15: ax:QI=0
   16: call [`rhp_log'] argc:0
   17: r104:SI=0
   18: pc=L116
" ]

	node [ id 2251 graphics [ fill "#d3d3d3" ] label "   20: L20:
   21: NOTE_INSN_BASIC_BLOCK 5
   22: flags:CCZ=cmp([r77:DI-0x28],0)
   23: pc={(flags:CCZ!=0)?L28:pc}
" ]

	node [ id 2252 graphics [ fill "#d3d3d3" ] label "   24: NOTE_INSN_BASIC_BLOCK 6
   25: r104:SI=0
   26: pc=L116
" ]

	node [ id 2253 graphics [ fill "#d3d3d3" ] label "   28: L28:
   29: NOTE_INSN_BASIC_BLOCK 7
   30: r83:DI=[`rhp_sp_master_edge_list']
   31: di:DI=r83:DI
   32: ax:SI=call [`rhp_sp_has_data'] argc:0
   33: r84:SI=ax:SI
   34: flags:CCZ=cmp(r84:SI,0)
   35: pc={(flags:CCZ!=0)?L40:pc}
" ]

	node [ id 2254 graphics [ fill "#d3d3d3" ] label "   36: NOTE_INSN_BASIC_BLOCK 8
   37: r104:SI=0
   38: pc=L116
" ]

	node [ id 2255 graphics [ fill "#d3d3d3" ] label "   40: L40:
   41: NOTE_INSN_BASIC_BLOCK 9
   42: [r77:DI-0xc]=0
   43: r85:DI=[`rhp_sp_master_edge_list']
   44: di:DI=r85:DI
   45: ax:DI=call [`rhp_sp_min'] argc:0
   46: r106:DI=ax:DI
   47: [r77:DI-0x8]=r106:DI
   48: pc=L108
" ]

	node [ id 2256 graphics [ fill "#d3d3d3" ] label "   95: NOTE_INSN_BASIC_BLOCK 11
   96: pc=L113
" ]

	node [ id 2257 graphics [ fill "#d3d3d3" ] label "  113: L113:
  114: NOTE_INSN_BASIC_BLOCK 14
  115: r104:SI=[r77:DI-0xc]
" ]

	node [ id 2258 graphics [ fill "#d3d3d3" ] label "  116: L116:
  117: NOTE_INSN_BASIC_BLOCK 15
  118: r105:SI=r104:SI
  122: ax:SI=r105:SI
  123: use ax:SI
" ]

	edge [ source 2247 target 2249 graphics [ fill "#0000ff" ] ] 
	edge [ source 2249 target 2250 graphics [ fill "#0000ff" ] ] 
	edge [ source 2249 target 2251 graphics [ fill "#000000" ] ] 
	edge [ source 2250 target 2258 graphics [ fill "#000000" ] ] 
	edge [ source 2251 target 2252 graphics [ fill "#0000ff" ] ] 
	edge [ source 2251 target 2253 graphics [ fill "#000000" ] ] 
	edge [ source 2252 target 2258 graphics [ fill "#000000" ] ] 
	edge [ source 2253 target 2254 graphics [ fill "#0000ff" ] ] 
	edge [ source 2253 target 2255 graphics [ fill "#000000" ] ] 
	edge [ source 2254 target 2258 graphics [ fill "#000000" ] ] 
	edge [ source 2255 target 2244 graphics [ fill "#000000" ] ] 
	edge [ source 2245 target 2256 graphics [ fill "#0000ff" ] ] 
	edge [ source 2245 target 2246 graphics [ fill "#000000" ] ] 
	edge [ source 2256 target 2257 graphics [ fill "#000000" ] ] 
	edge [ source 2246 target 2244 graphics [ fill "#0000ff" ] ] 
	edge [ source 2244 target 2245 graphics [ fill "#000000" ] ] 
	edge [ source 2244 target 2257 graphics [ fill "#0000ff" ] ] 
	edge [ source 2257 target 2258 graphics [ fill "#0000ff" ] ] 
	edge [ source 2258 target 2248 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 14
	node [ id 2508 graphics [ fill "#ffffff" ] label "rhp_initial_crossings ()
ENTRY" ]

	node [ id 2509 graphics [ fill "#ffffff" ] label "rhp_initial_crossings ()
EXIT" ]

	node [ id 2510 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: r82:DI=[`rhp_start_crossings']
    6: dx:DI=r82:DI
    7: si:DI=`__FUNCTION__.40'
    8: di:DI=`*.LC42'
    9: ax:QI=0
   10: call [`rhp_log'] argc:0
   11: r83:SI=[`rhp_inited']
   12: flags:CCZ=cmp(r83:SI,0)
   13: pc={(flags:CCZ!=0)?L22:pc}
" ]

	node [ id 2511 graphics [ fill "#d3d3d3" ] label "   14: NOTE_INSN_BASIC_BLOCK 4
   15: si:DI=`__FUNCTION__.40'
   16: di:DI=`*.LC15'
   17: ax:QI=0
   18: call [`rhp_log'] argc:0
   19: r100:DI=0
   20: pc=L117
" ]

	node [ id 2512 graphics [ fill "#d3d3d3" ] label "   22: L22:
   23: NOTE_INSN_BASIC_BLOCK 5
   24: r84:DI=[`rhp_sp_master_node_list']
   25: di:DI=r84:DI
   26: ax:SI=call [`rhp_sp_has_data'] argc:0
   27: r85:SI=ax:SI
   28: flags:CCZ=cmp(r85:SI,0)
   29: pc={(flags:CCZ!=0)?L39:pc}
" ]

	node [ id 2513 graphics [ fill "#d3d3d3" ] label "   30: NOTE_INSN_BASIC_BLOCK 6
   31: si:DI=`__FUNCTION__.40'
   32: di:DI=`*.LC43'
   33: ax:QI=0
   34: call [`rhp_log'] argc:0
   35: [`rhp_start_crossings']=0
   36: r100:DI=[`rhp_start_crossings']
   37: pc=L117
" ]

	node [ id 2514 graphics [ fill "#d3d3d3" ] label "   39: L39:
   40: NOTE_INSN_BASIC_BLOCK 7
   41: r86:DI=[`rhp_sp_master_edge_list']
   42: di:DI=r86:DI
   43: ax:SI=call [`rhp_sp_has_data'] argc:0
   44: r87:SI=ax:SI
   45: flags:CCZ=cmp(r87:SI,0)
   46: pc={(flags:CCZ!=0)?L49:pc}
" ]

	node [ id 2515 graphics [ fill "#d3d3d3" ] label "   47: NOTE_INSN_BASIC_BLOCK 8
   48: [`rhp_start_crossings']=0
" ]

	node [ id 2516 graphics [ fill "#d3d3d3" ] label "   49: L49:
   50: NOTE_INSN_BASIC_BLOCK 9
   51: r88:DI=[`rhp_start_crossings']
   54: flags:CCGOC=cmp(r88:DI,0)
   55: pc={(flags:CCGOC&lt;0)?L66:pc}
" ]

	node [ id 2517 graphics [ fill "#d3d3d3" ] label "   56: NOTE_INSN_BASIC_BLOCK 10
   57: r89:DI=[`rhp_start_crossings']
   58: dx:DI=r89:DI
   59: si:DI=`__FUNCTION__.40'
   60: di:DI=`*.LC44'
   61: ax:QI=0
   62: call [`rhp_log'] argc:0
   63: r100:DI=[`rhp_start_crossings']
   64: pc=L117
" ]

	node [ id 2518 graphics [ fill "#d3d3d3" ] label "   66: L66:
   67: NOTE_INSN_BASIC_BLOCK 11
   68: si:DI=`__FUNCTION__.40'
   69: di:DI=`*.LC45'
   70: ax:QI=0
   71: call [`rhp_log'] argc:0
   72: call [`rhp_allocatelayers'] argc:0
   73: call [`rhp_allocateadjacencylists'] argc:0
   74: ax:SI=call [`rhp_countisolatednodes'] argc:0
   75: r90:SI=ax:SI
   76: [`rhp_number_of_isolated_nodes']=r90:SI
   77: r91:SI=[`rhp_number_of_isolated_nodes']
   78: r92:DI=sign_extend(r91:SI)
   79: dx:DI=r92:DI
   80: si:DI=`__FUNCTION__.40'
   81: di:DI=`*.LC46'
   82: ax:QI=0
   83: call [`rhp_log'] argc:0
   84: call [`rhp_initcrossings'] argc:0
   85: call [`rhp_updateallcrossings'] argc:0
   86: ax:DI=call [`rhp_numberofcrossings'] argc:0
   87: r93:DI=ax:DI
   88: [`rhp_start_crossings']=r93:DI
   89: r94:SI=[`rhp_number_of_nodes']
   90: r95:DI=sign_extend(r94:SI)
   91: r102:DI=r95:DI
   92: {r102:DI=r102:DI&lt;&lt;0x2;clobber flags:CC;}
   93: {r102:DI=r102:DI+r95:DI;clobber flags:CC;}
      REG_EQUAL r95:DI*0x5
   94: {r103:DI=r102:DI&lt;&lt;0x4;clobber flags:CC;}
   95: r102:DI=r103:DI
      REG_EQUAL r95:DI*0x50
   96: r96:DI=r102:DI
   97: dx:DI=r96:DI
   98: si:DI=`__FUNCTION__.40'
   99: di:DI=`*.LC47'
  100: ax:QI=0
  101: call [`rhp_log'] argc:0
  102: r97:SI=[`rhp_number_of_edges']
  103: r98:DI=sign_extend(r97:SI)
  104: r104:DI=r98:DI
  105: {r105:DI=r104:DI&lt;&lt;0x3;clobber flags:CC;}
  106: r104:DI=r105:DI
      REG_EQUAL r98:DI*0x8
  107: {r104:DI=r104:DI-r98:DI;clobber flags:CC;}
      REG_EQUAL r98:DI*0x7
  108: {r106:DI=r104:DI&lt;&lt;0x3;clobber flags:CC;}
  109: r104:DI=r106:DI
      REG_EQUAL r98:DI*0x38
  110: r99:DI=r104:DI
  111: dx:DI=r99:DI
  112: si:DI=`__FUNCTION__.40'
  113: di:DI=`*.LC48'
  114: ax:QI=0
  115: call [`rhp_log'] argc:0
  116: r100:DI=[`rhp_start_crossings']
" ]

	node [ id 2519 graphics [ fill "#d3d3d3" ] label "  117: L117:
  118: NOTE_INSN_BASIC_BLOCK 12
  119: r101:DI=r100:DI
  123: ax:DI=r101:DI
  124: use ax:DI
" ]

	edge [ source 2508 target 2510 graphics [ fill "#0000ff" ] ] 
	edge [ source 2510 target 2511 graphics [ fill "#0000ff" ] ] 
	edge [ source 2510 target 2512 graphics [ fill "#000000" ] ] 
	edge [ source 2511 target 2519 graphics [ fill "#000000" ] ] 
	edge [ source 2512 target 2513 graphics [ fill "#0000ff" ] ] 
	edge [ source 2512 target 2514 graphics [ fill "#000000" ] ] 
	edge [ source 2513 target 2519 graphics [ fill "#000000" ] ] 
	edge [ source 2514 target 2515 graphics [ fill "#0000ff" ] ] 
	edge [ source 2514 target 2516 graphics [ fill "#000000" ] ] 
	edge [ source 2515 target 2516 graphics [ fill "#0000ff" ] ] 
	edge [ source 2516 target 2517 graphics [ fill "#0000ff" ] ] 
	edge [ source 2516 target 2518 graphics [ fill "#000000" ] ] 
	edge [ source 2517 target 2519 graphics [ fill "#000000" ] ] 
	edge [ source 2518 target 2519 graphics [ fill "#0000ff" ] ] 
	edge [ source 2519 target 2509 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 15
	node [ id 2712 graphics [ fill "#ffffff" ] label "rhp_current_crossings ()
ENTRY" ]

	node [ id 2713 graphics [ fill "#ffffff" ] label "rhp_current_crossings ()
EXIT" ]

	node [ id 2714 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: r82:SI=[`rhp_inited']
    6: flags:CCZ=cmp(r82:SI,0)
    7: pc={(flags:CCZ!=0)?L16:pc}
" ]

	node [ id 2715 graphics [ fill "#d3d3d3" ] label "    8: NOTE_INSN_BASIC_BLOCK 4
    9: si:DI=`__FUNCTION__.39'
   10: di:DI=`*.LC15'
   11: ax:QI=0
   12: call [`rhp_log'] argc:0
   13: r91:DI=0
   14: pc=L78
" ]

	node [ id 2716 graphics [ fill "#d3d3d3" ] label "   16: L16:
   17: NOTE_INSN_BASIC_BLOCK 5
   18: r83:DI=[`rhp_sp_master_node_list']
   19: di:DI=r83:DI
   20: ax:SI=call [`rhp_sp_has_data'] argc:0
   21: r84:SI=ax:SI
   22: flags:CCZ=cmp(r84:SI,0)
   23: pc={(flags:CCZ!=0)?L33:pc}
" ]

	node [ id 2717 graphics [ fill "#d3d3d3" ] label "   24: NOTE_INSN_BASIC_BLOCK 6
   25: si:DI=`__FUNCTION__.39'
   26: di:DI=`*.LC43'
   27: ax:QI=0
   28: call [`rhp_log'] argc:0
   29: [`rhp_crossings']=0
   30: r91:DI=[`rhp_crossings']
   31: pc=L78
" ]

	node [ id 2718 graphics [ fill "#d3d3d3" ] label "   33: L33:
   34: NOTE_INSN_BASIC_BLOCK 7
   35: r85:DI=[`rhp_sp_master_edge_list']
   36: di:DI=r85:DI
   37: ax:SI=call [`rhp_sp_has_data'] argc:0
   38: r86:SI=ax:SI
   39: flags:CCZ=cmp(r86:SI,0)
   40: pc={(flags:CCZ!=0)?L46:pc}
" ]

	node [ id 2719 graphics [ fill "#d3d3d3" ] label "   41: NOTE_INSN_BASIC_BLOCK 8
   42: [`rhp_crossings']=0
   43: r91:DI=[`rhp_crossings']
   44: pc=L78
" ]

	node [ id 2720 graphics [ fill "#d3d3d3" ] label "   46: L46:
   47: NOTE_INSN_BASIC_BLOCK 9
   48: r87:DI=[`rhp_start_crossings']
   51: flags:CCGOC=cmp(r87:DI,0)
   52: pc={(flags:CCGOC&gt;=0)?L59:pc}
" ]

	node [ id 2721 graphics [ fill "#d3d3d3" ] label "   53: NOTE_INSN_BASIC_BLOCK 10
   54: ax:DI=call [`rhp_initial_crossings'] argc:0
   55: r88:DI=ax:DI
   56: [`rhp_crossings']=r88:DI
   57: pc=L75
" ]

	node [ id 2722 graphics [ fill "#d3d3d3" ] label "   59: L59:
   60: NOTE_INSN_BASIC_BLOCK 11
   61: r89:SI=[`rhp_number_of_edges']
   62: flags:CCZ=cmp(r89:SI,0x1)
   63: pc={(flags:CCZ!=0)?L68:pc}
" ]

	node [ id 2723 graphics [ fill "#d3d3d3" ] label "   64: NOTE_INSN_BASIC_BLOCK 12
   65: [`rhp_crossings']=0
   66: pc=L75
" ]

	node [ id 2724 graphics [ fill "#d3d3d3" ] label "   68: L68:
   69: NOTE_INSN_BASIC_BLOCK 13
   70: [`rhp_crossings']=0
   71: call [`rhp_updateallcrossings'] argc:0
   72: ax:DI=call [`rhp_numberofcrossings'] argc:0
   73: r90:DI=ax:DI
   74: [`rhp_crossings']=r90:DI
" ]

	node [ id 2725 graphics [ fill "#d3d3d3" ] label "   75: L75:
   76: NOTE_INSN_BASIC_BLOCK 14
   77: r91:DI=[`rhp_crossings']
" ]

	node [ id 2726 graphics [ fill "#d3d3d3" ] label "   78: L78:
   79: NOTE_INSN_BASIC_BLOCK 15
   80: r92:DI=r91:DI
   84: ax:DI=r92:DI
   85: use ax:DI
" ]

	edge [ source 2712 target 2714 graphics [ fill "#0000ff" ] ] 
	edge [ source 2714 target 2715 graphics [ fill "#0000ff" ] ] 
	edge [ source 2714 target 2716 graphics [ fill "#000000" ] ] 
	edge [ source 2715 target 2726 graphics [ fill "#000000" ] ] 
	edge [ source 2716 target 2717 graphics [ fill "#0000ff" ] ] 
	edge [ source 2716 target 2718 graphics [ fill "#000000" ] ] 
	edge [ source 2717 target 2726 graphics [ fill "#000000" ] ] 
	edge [ source 2718 target 2719 graphics [ fill "#0000ff" ] ] 
	edge [ source 2718 target 2720 graphics [ fill "#000000" ] ] 
	edge [ source 2719 target 2726 graphics [ fill "#000000" ] ] 
	edge [ source 2720 target 2721 graphics [ fill "#0000ff" ] ] 
	edge [ source 2720 target 2722 graphics [ fill "#000000" ] ] 
	edge [ source 2721 target 2725 graphics [ fill "#000000" ] ] 
	edge [ source 2722 target 2723 graphics [ fill "#0000ff" ] ] 
	edge [ source 2722 target 2724 graphics [ fill "#000000" ] ] 
	edge [ source 2723 target 2725 graphics [ fill "#000000" ] ] 
	edge [ source 2724 target 2725 graphics [ fill "#0000ff" ] ] 
	edge [ source 2725 target 2726 graphics [ fill "#0000ff" ] ] 
	edge [ source 2726 target 2713 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 16
	node [ id 2967 graphics [ fill "#ffffff" ] label "rhp_current_crossings_at_level ()
ENTRY" ]

	node [ id 2968 graphics [ fill "#ffffff" ] label "rhp_current_crossings_at_level ()
EXIT" ]

	node [ id 2969 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x14]=di:SI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x8]=0
    7: [r77:DI-0x10]=0
    8: r82:SI=[`rhp_inited']
    9: flags:CCZ=cmp(r82:SI,0)
   10: pc={(flags:CCZ!=0)?L19:pc}
" ]

	node [ id 2970 graphics [ fill "#d3d3d3" ] label "   11: NOTE_INSN_BASIC_BLOCK 4
   12: si:DI=`__FUNCTION__.38'
   13: di:DI=`*.LC15'
   14: ax:QI=0
   15: call [`rhp_log'] argc:0
   16: r93:DI=0
   17: pc=L122
" ]

	node [ id 2971 graphics [ fill "#d3d3d3" ] label "   19: L19:
   20: NOTE_INSN_BASIC_BLOCK 5
   21: r83:DI=[`rhp_sp_master_node_list']
   22: di:DI=r83:DI
   23: ax:SI=call [`rhp_sp_has_data'] argc:0
   24: r84:SI=ax:SI
   25: flags:CCZ=cmp(r84:SI,0)
   26: pc={(flags:CCZ!=0)?L35:pc}
" ]

	node [ id 2972 graphics [ fill "#d3d3d3" ] label "   27: NOTE_INSN_BASIC_BLOCK 6
   28: si:DI=`__FUNCTION__.38'
   29: di:DI=`*.LC43'
   30: ax:QI=0
   31: call [`rhp_log'] argc:0
   32: r93:DI=0
   33: pc=L122
" ]

	node [ id 2973 graphics [ fill "#d3d3d3" ] label "   35: L35:
   36: NOTE_INSN_BASIC_BLOCK 7
   39: flags:CCGOC=cmp([r77:DI-0x14],0)
   40: pc={(flags:CCGOC&gt;=0)?L51:pc}
" ]

	node [ id 2974 graphics [ fill "#d3d3d3" ] label "   41: NOTE_INSN_BASIC_BLOCK 8
   42: r95:SI=[r77:DI-0x14]
   43: dx:SI=r95:SI
   44: si:DI=`__FUNCTION__.38'
   45: di:DI=`*.LC49'
   46: ax:QI=0
   47: call [`rhp_log'] argc:0
   48: r93:DI=0
   49: pc=L122
" ]

	node [ id 2975 graphics [ fill "#d3d3d3" ] label "   51: L51:
   52: NOTE_INSN_BASIC_BLOCK 9
   53: r85:SI=[`rhp_maxlevel']
   54: flags:CCGC=cmp([r77:DI-0x14],r85:SI)
   55: pc={(flags:CCGC&lt;=0)?L68:pc}
" ]

	node [ id 2976 graphics [ fill "#d3d3d3" ] label "   56: NOTE_INSN_BASIC_BLOCK 10
   57: r86:SI=[`rhp_maxlevel']
   58: r96:SI=[r77:DI-0x14]
   59: cx:SI=r86:SI
   60: dx:SI=r96:SI
   61: si:DI=`__FUNCTION__.38'
   62: di:DI=`*.LC50'
   63: ax:QI=0
   64: call [`rhp_log'] argc:0
   65: r93:DI=0
   66: pc=L122
" ]

	node [ id 2977 graphics [ fill "#d3d3d3" ] label "   68: L68:
   69: NOTE_INSN_BASIC_BLOCK 11
   70: r87:DI=[`rhp_sp_between_layers']
   71: di:DI=r87:DI
   72: ax:SI=call [`rhp_sp_has_data'] argc:0
   73: r88:SI=ax:SI
   74: flags:CCZ=cmp(r88:SI,0)
   75: pc={(flags:CCZ!=0)?L80:pc}
" ]

	node [ id 2978 graphics [ fill "#d3d3d3" ] label "   76: NOTE_INSN_BASIC_BLOCK 12
   77: r93:DI=0
   78: pc=L122
" ]

	node [ id 2979 graphics [ fill "#d3d3d3" ] label "   80: L80:
   81: NOTE_INSN_BASIC_BLOCK 13
   82: r89:SI=[`rhp_nlevels']
   83: flags:CCZ=cmp(r89:SI,0)
   84: pc={(flags:CCZ!=0)?L93:pc}
" ]

	node [ id 2980 graphics [ fill "#d3d3d3" ] label "   85: NOTE_INSN_BASIC_BLOCK 14
   86: si:DI=`__FUNCTION__.38'
   87: di:DI=`*.LC51'
   88: ax:QI=0
   89: call [`rhp_log'] argc:0
   90: r93:DI=0
   91: pc=L122
" ]

	node [ id 2981 graphics [ fill "#d3d3d3" ] label "   93: L93:
   94: NOTE_INSN_BASIC_BLOCK 15
   95: r97:SI=[r77:DI-0x14]
   96: r90:DI=sign_extend(r97:SI)
   97: r91:DI=[`rhp_sp_between_layers']
   98: si:DI=r90:DI
   99: di:DI=r91:DI
  100: ax:DI=call [`rhp_sp_lookup'] argc:0
  101: r98:DI=ax:DI
  102: [r77:DI-0x8]=r98:DI
  103: flags:CCZ=cmp([r77:DI-0x8],0)
  104: pc={(flags:CCZ==0)?L113:pc}
" ]

	node [ id 2982 graphics [ fill "#d3d3d3" ] label "  105: NOTE_INSN_BASIC_BLOCK 16
  106: r99:DI=[r77:DI-0x8]
  107: r92:DI=[r99:DI+0x8]
  108: [r77:DI-0x10]=r92:DI
  109: r100:DI=[r77:DI-0x10]
  110: r93:DI=[r100:DI+0x10]
  111: pc=L122
" ]

	node [ id 2983 graphics [ fill "#d3d3d3" ] label "  113: L113:
  114: NOTE_INSN_BASIC_BLOCK 17
  115: r101:SI=[r77:DI-0x14]
  116: dx:SI=r101:SI
  117: si:DI=`__FUNCTION__.38'
  118: di:DI=`*.LC52'
  119: ax:QI=0
  120: call [`rhp_log'] argc:0
  121: r93:DI=0
" ]

	node [ id 2984 graphics [ fill "#d3d3d3" ] label "  122: L122:
  123: NOTE_INSN_BASIC_BLOCK 18
  124: r94:DI=r93:DI
  128: ax:DI=r94:DI
  129: use ax:DI
" ]

	edge [ source 2967 target 2969 graphics [ fill "#0000ff" ] ] 
	edge [ source 2969 target 2970 graphics [ fill "#0000ff" ] ] 
	edge [ source 2969 target 2971 graphics [ fill "#000000" ] ] 
	edge [ source 2970 target 2984 graphics [ fill "#000000" ] ] 
	edge [ source 2971 target 2972 graphics [ fill "#0000ff" ] ] 
	edge [ source 2971 target 2973 graphics [ fill "#000000" ] ] 
	edge [ source 2972 target 2984 graphics [ fill "#000000" ] ] 
	edge [ source 2973 target 2974 graphics [ fill "#0000ff" ] ] 
	edge [ source 2973 target 2975 graphics [ fill "#000000" ] ] 
	edge [ source 2974 target 2984 graphics [ fill "#000000" ] ] 
	edge [ source 2975 target 2976 graphics [ fill "#0000ff" ] ] 
	edge [ source 2975 target 2977 graphics [ fill "#000000" ] ] 
	edge [ source 2976 target 2984 graphics [ fill "#000000" ] ] 
	edge [ source 2977 target 2978 graphics [ fill "#0000ff" ] ] 
	edge [ source 2977 target 2979 graphics [ fill "#000000" ] ] 
	edge [ source 2978 target 2984 graphics [ fill "#000000" ] ] 
	edge [ source 2979 target 2980 graphics [ fill "#0000ff" ] ] 
	edge [ source 2979 target 2981 graphics [ fill "#000000" ] ] 
	edge [ source 2980 target 2984 graphics [ fill "#000000" ] ] 
	edge [ source 2981 target 2982 graphics [ fill "#0000ff" ] ] 
	edge [ source 2981 target 2983 graphics [ fill "#000000" ] ] 
	edge [ source 2982 target 2984 graphics [ fill "#000000" ] ] 
	edge [ source 2983 target 2984 graphics [ fill "#0000ff" ] ] 
	edge [ source 2984 target 2968 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 17
	node [ id 3273 graphics [ fill "#ffffff" ] label "rhp_nodes_in_level ()
ENTRY" ]

	node [ id 3274 graphics [ fill "#ffffff" ] label "rhp_nodes_in_level ()
EXIT" ]

	node [ id 3275 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x14]=di:SI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x8]=0
    7: [r77:DI-0x10]=0
    8: r82:SI=[`rhp_inited']
    9: flags:CCZ=cmp(r82:SI,0)
   10: pc={(flags:CCZ!=0)?L19:pc}
" ]

	node [ id 3276 graphics [ fill "#d3d3d3" ] label "   11: NOTE_INSN_BASIC_BLOCK 4
   12: si:DI=`__FUNCTION__.37'
   13: di:DI=`*.LC15'
   14: ax:QI=0
   15: call [`rhp_log'] argc:0
   16: r92:SI=0
   17: pc=L109
" ]

	node [ id 3277 graphics [ fill "#d3d3d3" ] label "   19: L19:
   20: NOTE_INSN_BASIC_BLOCK 5
   21: r83:DI=[`rhp_sp_master_node_list']
   22: di:DI=r83:DI
   23: ax:SI=call [`rhp_sp_has_data'] argc:0
   24: r84:SI=ax:SI
   25: flags:CCZ=cmp(r84:SI,0)
   26: pc={(flags:CCZ!=0)?L35:pc}
" ]

	node [ id 3278 graphics [ fill "#d3d3d3" ] label "   27: NOTE_INSN_BASIC_BLOCK 6
   28: si:DI=`__FUNCTION__.37'
   29: di:DI=`*.LC43'
   30: ax:QI=0
   31: call [`rhp_log'] argc:0
   32: r92:SI=0
   33: pc=L109
" ]

	node [ id 3279 graphics [ fill "#d3d3d3" ] label "   35: L35:
   36: NOTE_INSN_BASIC_BLOCK 7
   39: flags:CCGOC=cmp([r77:DI-0x14],0)
   40: pc={(flags:CCGOC&gt;=0)?L51:pc}
" ]

	node [ id 3280 graphics [ fill "#d3d3d3" ] label "   41: NOTE_INSN_BASIC_BLOCK 8
   42: r94:SI=[r77:DI-0x14]
   43: dx:SI=r94:SI
   44: si:DI=`__FUNCTION__.37'
   45: di:DI=`*.LC49'
   46: ax:QI=0
   47: call [`rhp_log'] argc:0
   48: r92:SI=0
   49: pc=L109
" ]

	node [ id 3281 graphics [ fill "#d3d3d3" ] label "   51: L51:
   52: NOTE_INSN_BASIC_BLOCK 9
   53: r85:SI=[`rhp_maxlevel']
   54: flags:CCGC=cmp([r77:DI-0x14],r85:SI)
   55: pc={(flags:CCGC&lt;=0)?L68:pc}
" ]

	node [ id 3282 graphics [ fill "#d3d3d3" ] label "   56: NOTE_INSN_BASIC_BLOCK 10
   57: r86:SI=[`rhp_maxlevel']
   58: r95:SI=[r77:DI-0x14]
   59: cx:SI=r86:SI
   60: dx:SI=r95:SI
   61: si:DI=`__FUNCTION__.37'
   62: di:DI=`*.LC50'
   63: ax:QI=0
   64: call [`rhp_log'] argc:0
   65: r92:SI=0
   66: pc=L109
" ]

	node [ id 3283 graphics [ fill "#d3d3d3" ] label "   68: L68:
   69: NOTE_INSN_BASIC_BLOCK 11
   70: r87:DI=[`rhp_sp_layers']
   71: di:DI=r87:DI
   72: ax:SI=call [`rhp_sp_has_data'] argc:0
   73: r88:SI=ax:SI
   74: flags:CCZ=cmp(r88:SI,0)
   75: pc={(flags:CCZ!=0)?L80:pc}
" ]

	node [ id 3284 graphics [ fill "#d3d3d3" ] label "   76: NOTE_INSN_BASIC_BLOCK 12
   77: r92:SI=0
   78: pc=L109
" ]

	node [ id 3285 graphics [ fill "#d3d3d3" ] label "   80: L80:
   81: NOTE_INSN_BASIC_BLOCK 13
   82: r96:SI=[r77:DI-0x14]
   83: r89:DI=sign_extend(r96:SI)
   84: r90:DI=[`rhp_sp_layers']
   85: si:DI=r89:DI
   86: di:DI=r90:DI
   87: ax:DI=call [`rhp_sp_lookup'] argc:0
   88: r97:DI=ax:DI
   89: [r77:DI-0x8]=r97:DI
   90: flags:CCZ=cmp([r77:DI-0x8],0)
   91: pc={(flags:CCZ==0)?L100:pc}
" ]

	node [ id 3286 graphics [ fill "#d3d3d3" ] label "   92: NOTE_INSN_BASIC_BLOCK 14
   93: r98:DI=[r77:DI-0x8]
   94: r91:DI=[r98:DI+0x8]
   95: [r77:DI-0x10]=r91:DI
   96: r99:DI=[r77:DI-0x10]
   97: r92:SI=[r99:DI]
   98: pc=L109
" ]

	node [ id 3287 graphics [ fill "#d3d3d3" ] label "  100: L100:
  101: NOTE_INSN_BASIC_BLOCK 15
  102: r100:SI=[r77:DI-0x14]
  103: dx:SI=r100:SI
  104: si:DI=`__FUNCTION__.37'
  105: di:DI=`*.LC53'
  106: ax:QI=0
  107: call [`rhp_log'] argc:0
  108: r92:SI=0
" ]

	node [ id 3288 graphics [ fill "#d3d3d3" ] label "  109: L109:
  110: NOTE_INSN_BASIC_BLOCK 16
  111: r93:SI=r92:SI
  115: ax:SI=r93:SI
  116: use ax:SI
" ]

	edge [ source 3273 target 3275 graphics [ fill "#0000ff" ] ] 
	edge [ source 3275 target 3276 graphics [ fill "#0000ff" ] ] 
	edge [ source 3275 target 3277 graphics [ fill "#000000" ] ] 
	edge [ source 3276 target 3288 graphics [ fill "#000000" ] ] 
	edge [ source 3277 target 3278 graphics [ fill "#0000ff" ] ] 
	edge [ source 3277 target 3279 graphics [ fill "#000000" ] ] 
	edge [ source 3278 target 3288 graphics [ fill "#000000" ] ] 
	edge [ source 3279 target 3280 graphics [ fill "#0000ff" ] ] 
	edge [ source 3279 target 3281 graphics [ fill "#000000" ] ] 
	edge [ source 3280 target 3288 graphics [ fill "#000000" ] ] 
	edge [ source 3281 target 3282 graphics [ fill "#0000ff" ] ] 
	edge [ source 3281 target 3283 graphics [ fill "#000000" ] ] 
	edge [ source 3282 target 3288 graphics [ fill "#000000" ] ] 
	edge [ source 3283 target 3284 graphics [ fill "#0000ff" ] ] 
	edge [ source 3283 target 3285 graphics [ fill "#000000" ] ] 
	edge [ source 3284 target 3288 graphics [ fill "#000000" ] ] 
	edge [ source 3285 target 3286 graphics [ fill "#0000ff" ] ] 
	edge [ source 3285 target 3287 graphics [ fill "#000000" ] ] 
	edge [ source 3286 target 3288 graphics [ fill "#000000" ] ] 
	edge [ source 3287 target 3288 graphics [ fill "#0000ff" ] ] 
	edge [ source 3288 target 3274 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 3545 graphics [ fill "#d3d3d3" ] label "   50: L50:
   51: NOTE_INSN_BASIC_BLOCK 9
   53: flags:CCZ=cmp([r77:DI-0x10],0)
   54: pc={(flags:CCZ!=0)?L52:pc}
" ]

	node [ id 3546 graphics [ fill "#d3d3d3" ] label "   52: L52:
   40: NOTE_INSN_BASIC_BLOCK 8
   41: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
   42: r91:DI=[r77:DI-0x10]
   43: r86:DI=[r91:DI]
   44: r87:DI=[`rhp_sp_master_node_list']
   45: si:DI=r86:DI
   46: di:DI=r87:DI
   47: ax:DI=call [`rhp_sp_next'] argc:0
   48: r92:DI=ax:DI
   49: [r77:DI-0x10]=r92:DI
" ]



# function number 18
	node [ id 3547 graphics [ fill "#ffffff" ] label "rhp_nodes_in_layout ()
ENTRY" ]

	node [ id 3548 graphics [ fill "#ffffff" ] label "rhp_nodes_in_layout ()
EXIT" ]

	node [ id 3549 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x4]=0
    6: [r77:DI-0x10]=0
    7: r82:SI=[`rhp_inited']
    8: flags:CCZ=cmp(r82:SI,0)
    9: pc={(flags:CCZ!=0)?L18:pc}
" ]

	node [ id 3550 graphics [ fill "#d3d3d3" ] label "   10: NOTE_INSN_BASIC_BLOCK 4
   11: si:DI=`__FUNCTION__.36'
   12: di:DI=`*.LC15'
   13: ax:QI=0
   14: call [`rhp_log'] argc:0
   15: r88:SI=0
   16: pc=L57
" ]

	node [ id 3551 graphics [ fill "#d3d3d3" ] label "   18: L18:
   19: NOTE_INSN_BASIC_BLOCK 5
   20: r83:DI=[`rhp_sp_master_node_list']
   21: di:DI=r83:DI
   22: ax:SI=call [`rhp_sp_has_data'] argc:0
   23: r84:SI=ax:SI
   24: flags:CCZ=cmp(r84:SI,0)
   25: pc={(flags:CCZ!=0)?L30:pc}
" ]

	node [ id 3552 graphics [ fill "#d3d3d3" ] label "   26: NOTE_INSN_BASIC_BLOCK 6
   27: r88:SI=0
   28: pc=L57
" ]

	node [ id 3553 graphics [ fill "#d3d3d3" ] label "   30: L30:
   31: NOTE_INSN_BASIC_BLOCK 7
   32: [r77:DI-0x4]=0
   33: r85:DI=[`rhp_sp_master_node_list']
   34: di:DI=r85:DI
   35: ax:DI=call [`rhp_sp_min'] argc:0
   36: r90:DI=ax:DI
   37: [r77:DI-0x10]=r90:DI
   38: pc=L50
" ]

	node [ id 3554 graphics [ fill "#d3d3d3" ] label "   55: NOTE_INSN_BASIC_BLOCK 10
   56: r88:SI=[r77:DI-0x4]
" ]

	node [ id 3555 graphics [ fill "#d3d3d3" ] label "   57: L57:
   58: NOTE_INSN_BASIC_BLOCK 11
   59: r89:SI=r88:SI
   63: ax:SI=r89:SI
   64: use ax:SI
" ]

	edge [ source 3547 target 3549 graphics [ fill "#0000ff" ] ] 
	edge [ source 3549 target 3550 graphics [ fill "#0000ff" ] ] 
	edge [ source 3549 target 3551 graphics [ fill "#000000" ] ] 
	edge [ source 3550 target 3555 graphics [ fill "#000000" ] ] 
	edge [ source 3551 target 3552 graphics [ fill "#0000ff" ] ] 
	edge [ source 3551 target 3553 graphics [ fill "#000000" ] ] 
	edge [ source 3552 target 3555 graphics [ fill "#000000" ] ] 
	edge [ source 3553 target 3545 graphics [ fill "#000000" ] ] 
	edge [ source 3546 target 3545 graphics [ fill "#0000ff" ] ] 
	edge [ source 3545 target 3546 graphics [ fill "#000000" ] ] 
	edge [ source 3545 target 3554 graphics [ fill "#0000ff" ] ] 
	edge [ source 3554 target 3555 graphics [ fill "#0000ff" ] ] 
	edge [ source 3555 target 3548 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 3732 graphics [ fill "#d3d3d3" ] label "   50: L50:
   51: NOTE_INSN_BASIC_BLOCK 9
   53: flags:CCZ=cmp([r77:DI-0x10],0)
   54: pc={(flags:CCZ!=0)?L52:pc}
" ]

	node [ id 3733 graphics [ fill "#d3d3d3" ] label "   52: L52:
   40: NOTE_INSN_BASIC_BLOCK 8
   41: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
   42: r91:DI=[r77:DI-0x10]
   43: r86:DI=[r91:DI]
   44: r87:DI=[`rhp_sp_master_edge_list']
   45: si:DI=r86:DI
   46: di:DI=r87:DI
   47: ax:DI=call [`rhp_sp_next'] argc:0
   48: r92:DI=ax:DI
   49: [r77:DI-0x10]=r92:DI
" ]



# function number 19
	node [ id 3734 graphics [ fill "#ffffff" ] label "rhp_edges_in_layout ()
ENTRY" ]

	node [ id 3735 graphics [ fill "#ffffff" ] label "rhp_edges_in_layout ()
EXIT" ]

	node [ id 3736 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x4]=0
    6: [r77:DI-0x10]=0
    7: r82:SI=[`rhp_inited']
    8: flags:CCZ=cmp(r82:SI,0)
    9: pc={(flags:CCZ!=0)?L18:pc}
" ]

	node [ id 3737 graphics [ fill "#d3d3d3" ] label "   10: NOTE_INSN_BASIC_BLOCK 4
   11: si:DI=`__FUNCTION__.35'
   12: di:DI=`*.LC15'
   13: ax:QI=0
   14: call [`rhp_log'] argc:0
   15: r88:SI=0
   16: pc=L57
" ]

	node [ id 3738 graphics [ fill "#d3d3d3" ] label "   18: L18:
   19: NOTE_INSN_BASIC_BLOCK 5
   20: r83:DI=[`rhp_sp_master_edge_list']
   21: di:DI=r83:DI
   22: ax:SI=call [`rhp_sp_has_data'] argc:0
   23: r84:SI=ax:SI
   24: flags:CCZ=cmp(r84:SI,0)
   25: pc={(flags:CCZ!=0)?L30:pc}
" ]

	node [ id 3739 graphics [ fill "#d3d3d3" ] label "   26: NOTE_INSN_BASIC_BLOCK 6
   27: r88:SI=0
   28: pc=L57
" ]

	node [ id 3740 graphics [ fill "#d3d3d3" ] label "   30: L30:
   31: NOTE_INSN_BASIC_BLOCK 7
   32: [r77:DI-0x4]=0
   33: r85:DI=[`rhp_sp_master_edge_list']
   34: di:DI=r85:DI
   35: ax:DI=call [`rhp_sp_min'] argc:0
   36: r90:DI=ax:DI
   37: [r77:DI-0x10]=r90:DI
   38: pc=L50
" ]

	node [ id 3741 graphics [ fill "#d3d3d3" ] label "   55: NOTE_INSN_BASIC_BLOCK 10
   56: r88:SI=[r77:DI-0x4]
" ]

	node [ id 3742 graphics [ fill "#d3d3d3" ] label "   57: L57:
   58: NOTE_INSN_BASIC_BLOCK 11
   59: r89:SI=r88:SI
   63: ax:SI=r89:SI
   64: use ax:SI
" ]

	edge [ source 3734 target 3736 graphics [ fill "#0000ff" ] ] 
	edge [ source 3736 target 3737 graphics [ fill "#0000ff" ] ] 
	edge [ source 3736 target 3738 graphics [ fill "#000000" ] ] 
	edge [ source 3737 target 3742 graphics [ fill "#000000" ] ] 
	edge [ source 3738 target 3739 graphics [ fill "#0000ff" ] ] 
	edge [ source 3738 target 3740 graphics [ fill "#000000" ] ] 
	edge [ source 3739 target 3742 graphics [ fill "#000000" ] ] 
	edge [ source 3740 target 3732 graphics [ fill "#000000" ] ] 
	edge [ source 3733 target 3732 graphics [ fill "#0000ff" ] ] 
	edge [ source 3732 target 3733 graphics [ fill "#000000" ] ] 
	edge [ source 3732 target 3741 graphics [ fill "#0000ff" ] ] 
	edge [ source 3741 target 3742 graphics [ fill "#0000ff" ] ] 
	edge [ source 3742 target 3735 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 20
	node [ id 3919 graphics [ fill "#ffffff" ] label "rhp_free ()
ENTRY" ]

	node [ id 3920 graphics [ fill "#ffffff" ] label "rhp_free ()
EXIT" ]

	node [ id 3921 graphics [ fill "#d3d3d3" ] label "    6: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x8]=di:DI
    3: [r77:DI-0x10]=si:DI
    4: [r77:DI-0x14]=dx:SI
    5: NOTE_INSN_FUNCTION_BEG
    8: flags:CCZ=cmp([r77:DI-0x8],0)
    9: pc={(flags:CCZ!=0)?L22:pc}
" ]

	node [ id 3922 graphics [ fill "#d3d3d3" ] label "   10: NOTE_INSN_BASIC_BLOCK 4
   11: r87:SI=[r77:DI-0x14]
   12: r88:DI=[r77:DI-0x10]
   13: cx:SI=r87:SI
   14: dx:DI=r88:DI
   15: si:DI=`__FUNCTION__.34'
   16: di:DI=`*.LC54'
   17: ax:QI=0
   18: call [`rhp_log'] argc:0
   19: r85:DI=0
   20: pc=L55
" ]

	node [ id 3923 graphics [ fill "#d3d3d3" ] label "   22: L22:
   23: NOTE_INSN_BASIC_BLOCK 5
   24: flags:CCZ=cmp([r77:DI-0x8],0)
   25: pc={(flags:CCZ==0)?L52:pc}
" ]

	node [ id 3924 graphics [ fill "#d3d3d3" ] label "   26: NOTE_INSN_BASIC_BLOCK 6
   27: r89:SI=[r77:DI-0x14]
   28: r90:DI=[r77:DI-0x10]
   29: r91:DI=[r77:DI-0x8]
   30: dx:SI=r89:SI
   31: si:DI=r90:DI
   32: di:DI=r91:DI
   33: call [`myfree'] argc:0
   34: r82:DI=[`rhp_n_free']
   35: {r83:DI=r82:DI+0x1;clobber flags:CC;}
   36: [`rhp_n_free']=r83:DI
   37: r84:SI=[`rhp_dolog']
   40: flags:CCGC=cmp(r84:SI,0x1)
   41: pc={(flags:CCGC&lt;=0)?L52:pc}
" ]

	node [ id 3925 graphics [ fill "#d3d3d3" ] label "   42: NOTE_INSN_BASIC_BLOCK 7
   43: r92:SI=[r77:DI-0x14]
   44: r93:DI=[r77:DI-0x10]
   45: r94:DI=[r77:DI-0x8]
   46: cx:SI=r92:SI
   47: dx:DI=r93:DI
   48: si:DI=r94:DI
   49: di:DI=`*.LC55'
   50: ax:QI=0
   51: call [`rhp_log'] argc:0
" ]

	node [ id 3926 graphics [ fill "#d3d3d3" ] label "   52: L52:
   53: NOTE_INSN_BASIC_BLOCK 8
   54: r85:DI=0
" ]

	node [ id 3927 graphics [ fill "#d3d3d3" ] label "   55: L55:
   56: NOTE_INSN_BASIC_BLOCK 9
   57: r86:DI=r85:DI
   61: ax:DI=r86:DI
   62: use ax:DI
" ]

	edge [ source 3919 target 3921 graphics [ fill "#0000ff" ] ] 
	edge [ source 3921 target 3922 graphics [ fill "#0000ff" ] ] 
	edge [ source 3921 target 3923 graphics [ fill "#000000" ] ] 
	edge [ source 3922 target 3927 graphics [ fill "#000000" ] ] 
	edge [ source 3923 target 3924 graphics [ fill "#0000ff" ] ] 
	edge [ source 3923 target 3926 graphics [ fill "#000000" ] ] 
	edge [ source 3924 target 3925 graphics [ fill "#0000ff" ] ] 
	edge [ source 3924 target 3926 graphics [ fill "#000000" ] ] 
	edge [ source 3925 target 3926 graphics [ fill "#0000ff" ] ] 
	edge [ source 3926 target 3927 graphics [ fill "#0000ff" ] ] 
	edge [ source 3927 target 3920 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 21
	node [ id 4072 graphics [ fill "#ffffff" ] label "rhp_malloc ()
ENTRY" ]

	node [ id 4073 graphics [ fill "#ffffff" ] label "rhp_malloc ()
EXIT" ]

	node [ id 4074 graphics [ fill "#d3d3d3" ] label "    6: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x18]=di:DI
    3: [r77:DI-0x20]=si:DI
    4: [r77:DI-0x24]=dx:SI
    5: NOTE_INSN_FUNCTION_BEG
    8: [r77:DI-0x8]=0
    9: flags:CCZ=cmp([r77:DI-0x18],0)
   10: pc={(flags:CCZ!=0)?L23:pc}
" ]

	node [ id 4075 graphics [ fill "#d3d3d3" ] label "   11: NOTE_INSN_BASIC_BLOCK 4
   12: r87:SI=[r77:DI-0x24]
   13: r88:DI=[r77:DI-0x20]
   14: cx:SI=r87:SI
   15: dx:DI=r88:DI
   16: si:DI=`__FUNCTION__.33'
   17: di:DI=`*.LC56'
   18: ax:QI=0
   19: call [`rhp_log'] argc:0
   20: r85:DI=0
   21: pc=L57
" ]

	node [ id 4076 graphics [ fill "#d3d3d3" ] label "   23: L23:
   24: NOTE_INSN_BASIC_BLOCK 5
   25: r82:DI=[`rhp_n_malloc']
   26: {r83:DI=r82:DI+0x1;clobber flags:CC;}
   27: [`rhp_n_malloc']=r83:DI
   28: r89:SI=[r77:DI-0x24]
   29: r90:DI=[r77:DI-0x20]
   30: r91:DI=[r77:DI-0x18]
   31: dx:SI=r89:SI
   32: si:DI=r90:DI
   33: di:DI=r91:DI
   34: ax:DI=call [`mymalloc'] argc:0
   35: r92:DI=ax:DI
   36: [r77:DI-0x8]=r92:DI
   37: r84:SI=[`rhp_dolog']
   40: flags:CCGC=cmp(r84:SI,0x1)
   41: pc={(flags:CCGC&lt;=0)?L54:pc}
" ]

	node [ id 4077 graphics [ fill "#d3d3d3" ] label "   42: NOTE_INSN_BASIC_BLOCK 6
   43: r93:DI=[r77:DI-0x18]
   44: r94:SI=[r77:DI-0x24]
   45: r95:DI=[r77:DI-0x20]
   46: r96:DI=[r77:DI-0x8]
   47: r8:DI=r93:DI
   48: cx:SI=r94:SI
   49: dx:DI=r95:DI
   50: si:DI=r96:DI
   51: di:DI=`*.LC57'
   52: ax:QI=0
   53: call [`rhp_log'] argc:0
" ]

	node [ id 4078 graphics [ fill "#d3d3d3" ] label "   54: L54:
   55: NOTE_INSN_BASIC_BLOCK 7
   56: r85:DI=[r77:DI-0x8]
" ]

	node [ id 4079 graphics [ fill "#d3d3d3" ] label "   57: L57:
   58: NOTE_INSN_BASIC_BLOCK 8
   59: r86:DI=r85:DI
   63: ax:DI=r86:DI
   64: use ax:DI
" ]

	edge [ source 4072 target 4074 graphics [ fill "#0000ff" ] ] 
	edge [ source 4074 target 4075 graphics [ fill "#0000ff" ] ] 
	edge [ source 4074 target 4076 graphics [ fill "#000000" ] ] 
	edge [ source 4075 target 4079 graphics [ fill "#000000" ] ] 
	edge [ source 4076 target 4077 graphics [ fill "#0000ff" ] ] 
	edge [ source 4076 target 4078 graphics [ fill "#000000" ] ] 
	edge [ source 4077 target 4078 graphics [ fill "#0000ff" ] ] 
	edge [ source 4078 target 4079 graphics [ fill "#0000ff" ] ] 
	edge [ source 4079 target 4073 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 22
	node [ id 4208 graphics [ fill "#ffffff" ] label "rhp_sp_new ()
ENTRY" ]

	node [ id 4209 graphics [ fill "#ffffff" ] label "rhp_sp_new ()
EXIT" ]

	node [ id 4210 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x14]=di:SI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x8]=0
    7: dx:SI=0x673
    8: si:DI=`__FUNCTION__.32'
    9: di:DI=0x10
   10: ax:DI=call [`rhp_malloc'] argc:0
   11: r84:DI=ax:DI
   12: [r77:DI-0x8]=r84:DI
   13: r85:DI=[r77:DI-0x8]
   14: [r85:DI]=0
   15: r86:DI=[r77:DI-0x8]
   16: r87:SI=[r77:DI-0x14]
   17: [r86:DI+0x8]=r87:SI
   18: r82:DI=[r77:DI-0x8]
   21: r83:DI=r82:DI
   25: ax:DI=r83:DI
   26: use ax:DI
" ]

	edge [ source 4208 target 4210 graphics [ fill "#0000ff" ] ] 
	edge [ source 4210 target 4209 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 23
	node [ id 4259 graphics [ fill "#ffffff" ] label "rhp_sp_has_data ()
ENTRY" ]

	node [ id 4260 graphics [ fill "#ffffff" ] label "rhp_sp_has_data ()
EXIT" ]

	node [ id 4261 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x8]=di:DI
    3: NOTE_INSN_FUNCTION_BEG
    6: flags:CCZ=cmp([r77:DI-0x8],0)
    7: pc={(flags:CCZ!=0)?L12:pc}
" ]

	node [ id 4262 graphics [ fill "#d3d3d3" ] label "    8: NOTE_INSN_BASIC_BLOCK 4
    9: r83:SI=0
   10: pc=L25
" ]

	node [ id 4263 graphics [ fill "#d3d3d3" ] label "   12: L12:
   13: NOTE_INSN_BASIC_BLOCK 5
   14: r85:DI=[r77:DI-0x8]
   15: r82:DI=[r85:DI]
   16: flags:CCZ=cmp(r82:DI,0)
   17: pc={(flags:CCZ!=0)?L22:pc}
" ]

	node [ id 4264 graphics [ fill "#d3d3d3" ] label "   18: NOTE_INSN_BASIC_BLOCK 6
   19: r83:SI=0
   20: pc=L25
" ]

	node [ id 4265 graphics [ fill "#d3d3d3" ] label "   22: L22:
   23: NOTE_INSN_BASIC_BLOCK 7
   24: r83:SI=0x1
" ]

	node [ id 4266 graphics [ fill "#d3d3d3" ] label "   25: L25:
   26: NOTE_INSN_BASIC_BLOCK 8
   27: r84:SI=r83:SI
   31: ax:SI=r84:SI
   32: use ax:SI
" ]

	edge [ source 4259 target 4261 graphics [ fill "#0000ff" ] ] 
	edge [ source 4261 target 4262 graphics [ fill "#0000ff" ] ] 
	edge [ source 4261 target 4263 graphics [ fill "#000000" ] ] 
	edge [ source 4262 target 4266 graphics [ fill "#000000" ] ] 
	edge [ source 4263 target 4264 graphics [ fill "#0000ff" ] ] 
	edge [ source 4263 target 4265 graphics [ fill "#000000" ] ] 
	edge [ source 4264 target 4266 graphics [ fill "#000000" ] ] 
	edge [ source 4265 target 4266 graphics [ fill "#0000ff" ] ] 
	edge [ source 4266 target 4260 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 4395 graphics [ fill "#d3d3d3" ] label "   37: L37:
   38: NOTE_INSN_BASIC_BLOCK 10
   39: r91:DI=[r77:DI-0x8]
   40: r83:DI=[r91:DI+0x10]
   42: flags:CCZ=cmp(r83:DI,0)
   43: pc={(flags:CCZ!=0)?L41:pc}
" ]

	node [ id 4396 graphics [ fill "#d3d3d3" ] label "   41: L41:
   33: NOTE_INSN_BASIC_BLOCK 9
   34: r89:DI=[r77:DI-0x8]
   35: r90:DI=[r89:DI+0x10]
   36: [r77:DI-0x8]=r90:DI
" ]



# function number 24
	node [ id 4397 graphics [ fill "#ffffff" ] label "rhp_sp_min ()
ENTRY" ]

	node [ id 4398 graphics [ fill "#ffffff" ] label "rhp_sp_min ()
EXIT" ]

	node [ id 4399 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x18]=di:DI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x8]=0
    7: flags:CCZ=cmp([r77:DI-0x18],0)
    8: pc={(flags:CCZ!=0)?L13:pc}
" ]

	node [ id 4400 graphics [ fill "#d3d3d3" ] label "    9: NOTE_INSN_BASIC_BLOCK 4
   10: r84:DI=0
   11: pc=L47
" ]

	node [ id 4401 graphics [ fill "#d3d3d3" ] label "   13: L13:
   14: NOTE_INSN_BASIC_BLOCK 5
   15: r86:DI=[r77:DI-0x18]
   16: r82:DI=[r86:DI]
   17: flags:CCZ=cmp(r82:DI,0)
   18: pc={(flags:CCZ!=0)?L23:pc}
" ]

	node [ id 4402 graphics [ fill "#d3d3d3" ] label "   19: NOTE_INSN_BASIC_BLOCK 6
   20: r84:DI=0
   21: pc=L47
" ]

	node [ id 4403 graphics [ fill "#d3d3d3" ] label "   23: L23:
   24: NOTE_INSN_BASIC_BLOCK 7
   25: r87:DI=[r77:DI-0x18]
   26: r88:DI=[r87:DI]
   27: [r77:DI-0x8]=r88:DI
   28: flags:CCZ=cmp([r77:DI-0x8],0)
   29: pc={(flags:CCZ==0)?L44:pc}
" ]

	node [ id 4404 graphics [ fill "#d3d3d3" ] label "   30: NOTE_INSN_BASIC_BLOCK 8
   31: pc=L37
" ]

	node [ id 4405 graphics [ fill "#d3d3d3" ] label "   44: L44:
   45: NOTE_INSN_BASIC_BLOCK 11
   46: r84:DI=[r77:DI-0x8]
" ]

	node [ id 4406 graphics [ fill "#d3d3d3" ] label "   47: L47:
   48: NOTE_INSN_BASIC_BLOCK 12
   49: r85:DI=r84:DI
   53: ax:DI=r85:DI
   54: use ax:DI
" ]

	edge [ source 4397 target 4399 graphics [ fill "#0000ff" ] ] 
	edge [ source 4399 target 4400 graphics [ fill "#0000ff" ] ] 
	edge [ source 4399 target 4401 graphics [ fill "#000000" ] ] 
	edge [ source 4400 target 4406 graphics [ fill "#000000" ] ] 
	edge [ source 4401 target 4402 graphics [ fill "#0000ff" ] ] 
	edge [ source 4401 target 4403 graphics [ fill "#000000" ] ] 
	edge [ source 4402 target 4406 graphics [ fill "#000000" ] ] 
	edge [ source 4403 target 4404 graphics [ fill "#0000ff" ] ] 
	edge [ source 4403 target 4405 graphics [ fill "#000000" ] ] 
	edge [ source 4404 target 4395 graphics [ fill "#000000" ] ] 
	edge [ source 4396 target 4395 graphics [ fill "#0000ff" ] ] 
	edge [ source 4395 target 4396 graphics [ fill "#000000" ] ] 
	edge [ source 4395 target 4405 graphics [ fill "#0000ff" ] ] 
	edge [ source 4405 target 4406 graphics [ fill "#0000ff" ] ] 
	edge [ source 4406 target 4398 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 25
	node [ id 4599 graphics [ fill "#ffffff" ] label "rhp_sp_insert ()
ENTRY" ]

	node [ id 4600 graphics [ fill "#ffffff" ] label "rhp_sp_insert ()
EXIT" ]

	node [ id 4601 graphics [ fill "#d3d3d3" ] label "    6: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x18]=di:DI
    3: [r77:DI-0x20]=si:DI
    4: [r77:DI-0x28]=dx:DI
    5: NOTE_INSN_FUNCTION_BEG
    8: [r77:DI-0x8]=0
    9: flags:CCZ=cmp([r77:DI-0x18],0)
   10: pc={(flags:CCZ!=0)?L14:pc}
" ]

	node [ id 4602 graphics [ fill "#d3d3d3" ] label "   11: NOTE_INSN_BASIC_BLOCK 4
   12: pc=L184
" ]

	node [ id 4603 graphics [ fill "#d3d3d3" ] label "   14: L14:
   15: NOTE_INSN_BASIC_BLOCK 5
   16: r117:DI=[r77:DI-0x18]
   17: r82:DI=[r117:DI]
   18: flags:CCZ=cmp(r82:DI,0)
   19: pc={(flags:CCZ!=0)?L66:pc}
" ]

	node [ id 4604 graphics [ fill "#d3d3d3" ] label "   20: NOTE_INSN_BASIC_BLOCK 6
   21: dx:SI=0x6c3
   22: si:DI=`__FUNCTION__.31'
   23: di:DI=0x20
   24: ax:DI=call [`rhp_malloc'] argc:0
   25: r118:DI=ax:DI
   26: [r77:DI-0x8]=r118:DI
   27: r119:DI=[r77:DI-0x18]
   28: r120:DI=[r77:DI-0x8]
   29: [r119:DI]=r120:DI
   30: r121:DI=[r77:DI-0x18]
   31: r83:DI=[r121:DI]
   32: [r83:DI+0x10]=0
   33: r122:DI=[r77:DI-0x18]
   34: r84:DI=[r122:DI]
   35: [r84:DI+0x18]=0
   36: r123:DI=[r77:DI-0x18]
   37: r85:DI=[r123:DI]
   38: r124:DI=[r77:DI-0x20]
   39: [r85:DI]=r124:DI
   40: r125:DI=[r77:DI-0x18]
   41: r86:DI=[r125:DI]
   42: r126:DI=[r77:DI-0x28]
   43: [r86:DI+0x8]=r126:DI
   44: r87:SI=[`rhp_verbose']
   45: flags:CCZ=cmp(r87:SI,0)
   46: pc={(flags:CCZ==0)?L184:pc}
" ]

	node [ id 4605 graphics [ fill "#d3d3d3" ] label "   47: NOTE_INSN_BASIC_BLOCK 7
   48: r127:DI=[r77:DI-0x18]
   49: r88:DI=[r127:DI]
   50: r89:DI=[r88:DI]
   51: r90:DI=r89:DI
   52: r128:DI=[r77:DI-0x18]
   53: r91:DI=[r128:DI]
   54: r129:DI=[r77:DI-0x18]
   55: r8:DI=r90:DI
   56: cx:DI=r91:DI
   57: dx:DI=r129:DI
   58: si:DI=`__FUNCTION__.31'
   59: di:DI=`*.LC58'
   60: ax:QI=0
   61: call [`rhp_log'] argc:0
   64: pc=L184
" ]

	node [ id 4606 graphics [ fill "#d3d3d3" ] label "   66: L66:
   67: NOTE_INSN_BASIC_BLOCK 9
   68: r130:DI=[r77:DI-0x20]
   69: r131:DI=[r77:DI-0x18]
   70: si:DI=r130:DI
   71: di:DI=r131:DI
   72: call [`rhp_sp_sp'] argc:0
   73: r132:DI=[r77:DI-0x18]
   74: r92:DI=[r132:DI]
   75: r93:DI=[r92:DI]
   76: flags:CCZ=cmp([r77:DI-0x20],r93:DI)
   77: pc={(flags:CCZ!=0)?L109:pc}
" ]

	node [ id 4607 graphics [ fill "#d3d3d3" ] label "   78: NOTE_INSN_BASIC_BLOCK 10
   79: r133:DI=[r77:DI-0x18]
   80: r94:SI=[r133:DI+0x8]
   81: flags:CCZ=cmp(r94:SI,0)
   82: pc={(flags:CCZ==0)?L101:pc}
" ]

	node [ id 4608 graphics [ fill "#d3d3d3" ] label "   83: NOTE_INSN_BASIC_BLOCK 11
   84: r134:DI=[r77:DI-0x18]
   85: r95:DI=[r134:DI]
   86: r96:DI=[r95:DI+0x8]
   87: flags:CCZ=cmp(r96:DI,0)
   88: pc={(flags:CCZ==0)?L101:pc}
" ]

	node [ id 4609 graphics [ fill "#d3d3d3" ] label "   89: NOTE_INSN_BASIC_BLOCK 12
   90: r135:DI=[r77:DI-0x18]
   91: r97:DI=[r135:DI]
   92: r98:DI=[r97:DI+0x8]
   93: r99:DI=r98:DI
   94: dx:SI=0x6de
   95: si:DI=`__FUNCTION__.31'
   96: di:DI=r99:DI
   97: ax:DI=call [`rhp_free'] argc:0
   98: r136:DI=[r77:DI-0x18]
   99: r100:DI=[r136:DI]
  100: [r100:DI+0x8]=0
" ]

	node [ id 4610 graphics [ fill "#d3d3d3" ] label "  101: L101:
  102: NOTE_INSN_BASIC_BLOCK 13
  103: r137:DI=[r77:DI-0x18]
  104: r101:DI=[r137:DI]
  105: r138:DI=[r77:DI-0x28]
  106: [r101:DI+0x8]=r138:DI
  107: pc=L184
" ]

	node [ id 4611 graphics [ fill "#d3d3d3" ] label "  109: L109:
  110: NOTE_INSN_BASIC_BLOCK 14
  111: dx:SI=0x6e6
  112: si:DI=`__FUNCTION__.31'
  113: di:DI=0x20
  114: ax:DI=call [`rhp_malloc'] argc:0
  115: r139:DI=ax:DI
  116: [r77:DI-0x8]=r139:DI
  117: r140:DI=[r77:DI-0x8]
  118: r141:DI=[r77:DI-0x20]
  119: [r140:DI]=r141:DI
  120: r142:DI=[r77:DI-0x8]
  121: r143:DI=[r77:DI-0x28]
  122: [r142:DI+0x8]=r143:DI
  123: r144:DI=[r77:DI-0x18]
  124: r102:DI=[r144:DI]
  125: r103:DI=[r102:DI]
  126: flags:CCGC=cmp([r77:DI-0x20],r103:DI)
  127: pc={(flags:CCGC&lt;=0)?L143:pc}
" ]

	node [ id 4612 graphics [ fill "#d3d3d3" ] label "  128: NOTE_INSN_BASIC_BLOCK 15
  129: r145:DI=[r77:DI-0x18]
  130: r104:DI=[r145:DI]
  131: r146:DI=[r77:DI-0x8]
  132: [r146:DI+0x10]=r104:DI
  133: r147:DI=[r77:DI-0x8]
  134: r105:DI=[r147:DI+0x10]
  135: r106:DI=[r105:DI+0x18]
  136: r148:DI=[r77:DI-0x8]
  137: [r148:DI+0x18]=r106:DI
  138: r149:DI=[r77:DI-0x8]
  139: r107:DI=[r149:DI+0x10]
  140: [r107:DI+0x18]=0
  141: pc=L157
" ]

	node [ id 4613 graphics [ fill "#d3d3d3" ] label "  143: L143:
  144: NOTE_INSN_BASIC_BLOCK 16
  145: r150:DI=[r77:DI-0x18]
  146: r108:DI=[r150:DI]
  147: r151:DI=[r77:DI-0x8]
  148: [r151:DI+0x18]=r108:DI
  149: r152:DI=[r77:DI-0x8]
  150: r109:DI=[r152:DI+0x18]
  151: r110:DI=[r109:DI+0x10]
  152: r153:DI=[r77:DI-0x8]
  153: [r153:DI+0x10]=r110:DI
  154: r154:DI=[r77:DI-0x8]
  155: r111:DI=[r154:DI+0x18]
  156: [r111:DI+0x10]=0
" ]

	node [ id 4614 graphics [ fill "#d3d3d3" ] label "  157: L157:
  158: NOTE_INSN_BASIC_BLOCK 17
  159: r155:DI=[r77:DI-0x18]
  160: r156:DI=[r77:DI-0x8]
  161: [r155:DI]=r156:DI
  162: r112:SI=[`rhp_verbose']
  163: flags:CCZ=cmp(r112:SI,0)
  164: pc={(flags:CCZ==0)?L184:pc}
" ]

	node [ id 4615 graphics [ fill "#d3d3d3" ] label "  165: NOTE_INSN_BASIC_BLOCK 18
  166: r157:DI=[r77:DI-0x18]
  167: r113:DI=[r157:DI]
  168: r114:DI=[r113:DI]
  169: r115:DI=r114:DI
  170: r158:DI=[r77:DI-0x18]
  171: r116:DI=[r158:DI]
  172: r159:DI=[r77:DI-0x18]
  173: r8:DI=r115:DI
  174: cx:DI=r116:DI
  175: dx:DI=r159:DI
  176: si:DI=`__FUNCTION__.31'
  177: di:DI=`*.LC59'
  178: ax:QI=0
  179: call [`rhp_log'] argc:0
" ]

	node [ id 4616 graphics [ fill "#d3d3d3" ] label "  184: L184:
  185: NOTE_INSN_BASIC_BLOCK 21
" ]

	edge [ source 4599 target 4601 graphics [ fill "#0000ff" ] ] 
	edge [ source 4601 target 4602 graphics [ fill "#0000ff" ] ] 
	edge [ source 4601 target 4603 graphics [ fill "#000000" ] ] 
	edge [ source 4602 target 4616 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 4603 target 4604 graphics [ fill "#0000ff" ] ] 
	edge [ source 4603 target 4606 graphics [ fill "#000000" ] ] 
	edge [ source 4604 target 4605 graphics [ fill "#0000ff" ] ] 
	edge [ source 4604 target 4616 graphics [ fill "#000000" ] ] 
	edge [ source 4605 target 4616 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 4606 target 4607 graphics [ fill "#0000ff" ] ] 
	edge [ source 4606 target 4611 graphics [ fill "#000000" ] ] 
	edge [ source 4607 target 4608 graphics [ fill "#0000ff" ] ] 
	edge [ source 4607 target 4610 graphics [ fill "#000000" ] ] 
	edge [ source 4608 target 4609 graphics [ fill "#0000ff" ] ] 
	edge [ source 4608 target 4610 graphics [ fill "#000000" ] ] 
	edge [ source 4609 target 4610 graphics [ fill "#0000ff" ] ] 
	edge [ source 4610 target 4616 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 4611 target 4612 graphics [ fill "#0000ff" ] ] 
	edge [ source 4611 target 4613 graphics [ fill "#000000" ] ] 
	edge [ source 4612 target 4614 graphics [ fill "#000000" ] ] 
	edge [ source 4613 target 4614 graphics [ fill "#0000ff" ] ] 
	edge [ source 4614 target 4615 graphics [ fill "#0000ff" ] ] 
	edge [ source 4614 target 4616 graphics [ fill "#000000" ] ] 
	edge [ source 4615 target 4616 graphics [ fill "#0000ff" ] ] 
	edge [ source 4616 target 4600 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 4926 graphics [ fill "#d3d3d3" ] label "   73: L73:
   74: NOTE_INSN_BASIC_BLOCK 13
   75: r105:DI=[r77:DI-0x8]
   76: r86:DI=[r105:DI+0x18]
   78: flags:CCZ=cmp(r86:DI,0)
   79: pc={(flags:CCZ!=0)?L77:pc}
" ]

	node [ id 4927 graphics [ fill "#d3d3d3" ] label "   77: L77:
   69: NOTE_INSN_BASIC_BLOCK 12
   70: r103:DI=[r77:DI-0x8]
   71: r104:DI=[r103:DI+0x18]
   72: [r77:DI-0x8]=r104:DI
" ]



# function number 26
	node [ id 4928 graphics [ fill "#ffffff" ] label "rhp_sp_remove ()
ENTRY" ]

	node [ id 4929 graphics [ fill "#ffffff" ] label "rhp_sp_remove ()
EXIT" ]

	node [ id 4930 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x28]=di:DI
    3: [r77:DI-0x30]=si:DI
    4: NOTE_INSN_FUNCTION_BEG
    7: [r77:DI-0x10]=0
    8: [r77:DI-0x18]=0
    9: [r77:DI-0x8]=0
   10: [r77:DI-0x20]=0
   11: flags:CCZ=cmp([r77:DI-0x28],0)
   12: pc={(flags:CCZ!=0)?L16:pc}
" ]

	node [ id 4931 graphics [ fill "#d3d3d3" ] label "   13: NOTE_INSN_BASIC_BLOCK 4
   14: pc=L125
" ]

	node [ id 4932 graphics [ fill "#d3d3d3" ] label "   16: L16:
   17: NOTE_INSN_BASIC_BLOCK 5
   18: r91:DI=[r77:DI-0x28]
   19: r82:DI=[r91:DI]
   20: flags:CCZ=cmp(r82:DI,0)
   21: pc={(flags:CCZ!=0)?L25:pc}
" ]

	node [ id 4933 graphics [ fill "#d3d3d3" ] label "   22: NOTE_INSN_BASIC_BLOCK 6
   23: pc=L125
" ]

	node [ id 4934 graphics [ fill "#d3d3d3" ] label "   25: L25:
   26: NOTE_INSN_BASIC_BLOCK 7
   27: r92:DI=[r77:DI-0x30]
   28: r93:DI=[r77:DI-0x28]
   29: si:DI=r92:DI
   30: di:DI=r93:DI
   31: ax:DI=call [`rhp_sp_lookup'] argc:0
   32: r94:DI=ax:DI
   33: [r77:DI-0x10]=r94:DI
   34: flags:CCZ=cmp([r77:DI-0x10],0)
   35: pc={(flags:CCZ!=0)?L45:pc}
" ]

	node [ id 4935 graphics [ fill "#d3d3d3" ] label "   36: NOTE_INSN_BASIC_BLOCK 8
   37: r83:DI=[r77:DI-0x30]
   38: dx:DI=r83:DI
   39: si:DI=`__FUNCTION__.30'
   40: di:DI=`*.LC60'
   41: ax:QI=0
   42: ax:SI=call [`printf'] argc:0
   43: pc=L125
" ]

	node [ id 4936 graphics [ fill "#d3d3d3" ] label "   45: L45:
   46: NOTE_INSN_BASIC_BLOCK 9
   47: r95:DI=[r77:DI-0x28]
   48: r96:DI=[r95:DI]
   49: [r77:DI-0x18]=r96:DI
   50: r97:DI=[r77:DI-0x28]
   51: r84:DI=[r97:DI]
   52: r98:DI=[r84:DI+0x10]
   53: [r77:DI-0x8]=r98:DI
   54: r99:DI=[r77:DI-0x28]
   55: r85:DI=[r99:DI]
   56: r100:DI=[r85:DI+0x18]
   57: [r77:DI-0x20]=r100:DI
   58: flags:CCZ=cmp([r77:DI-0x8],0)
   59: pc={(flags:CCZ==0)?L86:pc}
" ]

	node [ id 4937 graphics [ fill "#d3d3d3" ] label "   60: NOTE_INSN_BASIC_BLOCK 10
   61: r101:DI=[r77:DI-0x28]
   62: r102:DI=[r77:DI-0x8]
   63: [r101:DI]=r102:DI
   64: flags:CCZ=cmp([r77:DI-0x20],0)
   65: pc={(flags:CCZ==0)?L91:pc}
" ]

	node [ id 4938 graphics [ fill "#d3d3d3" ] label "   66: NOTE_INSN_BASIC_BLOCK 11
   67: pc=L73
" ]

	node [ id 4939 graphics [ fill "#d3d3d3" ] label "   80: NOTE_INSN_BASIC_BLOCK 14
   81: r106:DI=[r77:DI-0x8]
   82: r107:DI=[r77:DI-0x20]
   83: [r106:DI+0x18]=r107:DI
   84: pc=L91
" ]

	node [ id 4940 graphics [ fill "#d3d3d3" ] label "   86: L86:
   87: NOTE_INSN_BASIC_BLOCK 15
   88: r108:DI=[r77:DI-0x28]
   89: r109:DI=[r77:DI-0x20]
   90: [r108:DI]=r109:DI
" ]

	node [ id 4941 graphics [ fill "#d3d3d3" ] label "   91: L91:
   92: NOTE_INSN_BASIC_BLOCK 16
   93: r110:DI=[r77:DI-0x28]
   94: r87:SI=[r110:DI+0x8]
   95: flags:CCZ=cmp(r87:SI,0)
   96: pc={(flags:CCZ==0)?L112:pc}
" ]

	node [ id 4942 graphics [ fill "#d3d3d3" ] label "   97: NOTE_INSN_BASIC_BLOCK 17
   98: r111:DI=[r77:DI-0x18]
   99: r88:DI=[r111:DI+0x8]
  100: flags:CCZ=cmp(r88:DI,0)
  101: pc={(flags:CCZ==0)?L112:pc}
" ]

	node [ id 4943 graphics [ fill "#d3d3d3" ] label "  102: NOTE_INSN_BASIC_BLOCK 18
  103: r112:DI=[r77:DI-0x18]
  104: r89:DI=[r112:DI+0x8]
  105: r90:DI=r89:DI
  106: dx:SI=0x741
  107: si:DI=`__FUNCTION__.30'
  108: di:DI=r90:DI
  109: ax:DI=call [`rhp_free'] argc:0
  110: r113:DI=[r77:DI-0x18]
  111: [r113:DI+0x8]=0
" ]

	node [ id 4944 graphics [ fill "#d3d3d3" ] label "  112: L112:
  113: NOTE_INSN_BASIC_BLOCK 19
  114: r114:DI=[r77:DI-0x18]
  115: [r114:DI+0x10]=0
  116: r115:DI=[r77:DI-0x18]
  117: [r115:DI+0x18]=0
  118: r116:DI=[r77:DI-0x18]
  119: dx:SI=0x74a
  120: si:DI=`__FUNCTION__.30'
  121: di:DI=r116:DI
  122: ax:DI=call [`rhp_free'] argc:0
" ]

	node [ id 4945 graphics [ fill "#d3d3d3" ] label "  125: L125:
  126: NOTE_INSN_BASIC_BLOCK 21
" ]

	edge [ source 4928 target 4930 graphics [ fill "#0000ff" ] ] 
	edge [ source 4930 target 4931 graphics [ fill "#0000ff" ] ] 
	edge [ source 4930 target 4932 graphics [ fill "#000000" ] ] 
	edge [ source 4931 target 4945 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 4932 target 4933 graphics [ fill "#0000ff" ] ] 
	edge [ source 4932 target 4934 graphics [ fill "#000000" ] ] 
	edge [ source 4933 target 4945 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 4934 target 4935 graphics [ fill "#0000ff" ] ] 
	edge [ source 4934 target 4936 graphics [ fill "#000000" ] ] 
	edge [ source 4935 target 4945 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 4936 target 4937 graphics [ fill "#0000ff" ] ] 
	edge [ source 4936 target 4940 graphics [ fill "#000000" ] ] 
	edge [ source 4937 target 4938 graphics [ fill "#0000ff" ] ] 
	edge [ source 4937 target 4941 graphics [ fill "#000000" ] ] 
	edge [ source 4938 target 4926 graphics [ fill "#000000" ] ] 
	edge [ source 4927 target 4926 graphics [ fill "#0000ff" ] ] 
	edge [ source 4926 target 4927 graphics [ fill "#000000" ] ] 
	edge [ source 4926 target 4939 graphics [ fill "#0000ff" ] ] 
	edge [ source 4939 target 4941 graphics [ fill "#000000" ] ] 
	edge [ source 4940 target 4941 graphics [ fill "#0000ff" ] ] 
	edge [ source 4941 target 4942 graphics [ fill "#0000ff" ] ] 
	edge [ source 4941 target 4944 graphics [ fill "#000000" ] ] 
	edge [ source 4942 target 4943 graphics [ fill "#0000ff" ] ] 
	edge [ source 4942 target 4944 graphics [ fill "#000000" ] ] 
	edge [ source 4943 target 4944 graphics [ fill "#0000ff" ] ] 
	edge [ source 4944 target 4945 graphics [ fill "#0000ff" ] ] 
	edge [ source 4945 target 4929 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 5260 graphics [ fill "#d3d3d3" ] label "   60: L60:
   61: NOTE_INSN_BASIC_BLOCK 9
   63: flags:CCZ=cmp([r77:DI-0x8],0)
   64: pc={(flags:CCZ!=0)?L62:pc}
" ]

	node [ id 5261 graphics [ fill "#d3d3d3" ] label "   62: L62:
   43: NOTE_INSN_BASIC_BLOCK 8
   44: r93:DI=[r77:DI-0x8]
   45: r83:DI=[r93:DI]
   46: r94:DI=[r77:DI-0x28]
   47: si:DI=r83:DI
   48: di:DI=r94:DI
   49: ax:DI=call [`rhp_sp_next'] argc:0
   50: r95:DI=ax:DI
   51: [r77:DI-0x18]=r95:DI
   52: r96:DI=[r77:DI-0x8]
   53: r84:DI=[r96:DI]
   54: r97:DI=[r77:DI-0x28]
   55: si:DI=r84:DI
   56: di:DI=r97:DI
   57: call [`rhp_sp_remove'] argc:0
   58: r98:DI=[r77:DI-0x18]
   59: [r77:DI-0x8]=r98:DI
" ]



# function number 27
	node [ id 5262 graphics [ fill "#ffffff" ] label "rhp_sp_delete ()
ENTRY" ]

	node [ id 5263 graphics [ fill "#ffffff" ] label "rhp_sp_delete ()
EXIT" ]

	node [ id 5264 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x28]=di:DI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x10]=0
    7: [r77:DI-0x8]=0
    8: [r77:DI-0x18]=0
    9: flags:CCZ=cmp([r77:DI-0x28],0)
   10: pc={(flags:CCZ!=0)?L15:pc}
" ]

	node [ id 5265 graphics [ fill "#d3d3d3" ] label "   11: NOTE_INSN_BASIC_BLOCK 4
   12: r85:DI=0
   13: pc=L76
" ]

	node [ id 5266 graphics [ fill "#d3d3d3" ] label "   15: L15:
   16: NOTE_INSN_BASIC_BLOCK 5
   17: r87:DI=[r77:DI-0x28]
   18: [r77:DI-0x10]=r87:DI
   19: r88:DI=[r77:DI-0x10]
   20: r82:DI=[r88:DI]
   21: flags:CCZ=cmp(r82:DI,0)
   22: pc={(flags:CCZ!=0)?L34:pc}
" ]

	node [ id 5267 graphics [ fill "#d3d3d3" ] label "   23: NOTE_INSN_BASIC_BLOCK 6
   24: r89:DI=[r77:DI-0x10]
   25: dx:SI=0x763
   26: si:DI=`__FUNCTION__.29'
   27: di:DI=r89:DI
   28: ax:DI=call [`rhp_free'] argc:0
   29: r90:DI=ax:DI
   30: [r77:DI-0x10]=r90:DI
   31: r85:DI=0
   32: pc=L76
" ]

	node [ id 5268 graphics [ fill "#d3d3d3" ] label "   34: L34:
   35: NOTE_INSN_BASIC_BLOCK 7
   36: r91:DI=[r77:DI-0x28]
   37: di:DI=r91:DI
   38: ax:DI=call [`rhp_sp_min'] argc:0
   39: r92:DI=ax:DI
   40: [r77:DI-0x8]=r92:DI
   41: pc=L60
" ]

	node [ id 5269 graphics [ fill "#d3d3d3" ] label "   65: NOTE_INSN_BASIC_BLOCK 10
   66: r99:DI=[r77:DI-0x28]
   67: [r77:DI-0x10]=r99:DI
   68: r100:DI=[r77:DI-0x10]
   69: dx:SI=0x775
   70: si:DI=`__FUNCTION__.29'
   71: di:DI=r100:DI
   72: ax:DI=call [`rhp_free'] argc:0
   73: r101:DI=ax:DI
   74: [r77:DI-0x10]=r101:DI
   75: r85:DI=0
" ]

	node [ id 5270 graphics [ fill "#d3d3d3" ] label "   76: L76:
   77: NOTE_INSN_BASIC_BLOCK 11
   78: r86:DI=r85:DI
   82: ax:DI=r86:DI
   83: use ax:DI
" ]

	edge [ source 5262 target 5264 graphics [ fill "#0000ff" ] ] 
	edge [ source 5264 target 5265 graphics [ fill "#0000ff" ] ] 
	edge [ source 5264 target 5266 graphics [ fill "#000000" ] ] 
	edge [ source 5265 target 5270 graphics [ fill "#000000" ] ] 
	edge [ source 5266 target 5267 graphics [ fill "#0000ff" ] ] 
	edge [ source 5266 target 5268 graphics [ fill "#000000" ] ] 
	edge [ source 5267 target 5270 graphics [ fill "#000000" ] ] 
	edge [ source 5268 target 5260 graphics [ fill "#000000" ] ] 
	edge [ source 5261 target 5260 graphics [ fill "#0000ff" ] ] 
	edge [ source 5260 target 5261 graphics [ fill "#000000" ] ] 
	edge [ source 5260 target 5269 graphics [ fill "#0000ff" ] ] 
	edge [ source 5269 target 5270 graphics [ fill "#0000ff" ] ] 
	edge [ source 5270 target 5263 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 5447 graphics [ fill "#d3d3d3" ] label "   56: L56:
   57: NOTE_INSN_BASIC_BLOCK 12
   58: r98:DI=[r77:DI-0x8]
   59: r86:DI=[r98:DI+0x10]
   61: flags:CCZ=cmp(r86:DI,0)
   62: pc={(flags:CCZ!=0)?L60:pc}
" ]

	node [ id 5448 graphics [ fill "#d3d3d3" ] label "   60: L60:
   52: NOTE_INSN_BASIC_BLOCK 11
   53: r96:DI=[r77:DI-0x8]
   54: r97:DI=[r96:DI+0x10]
   55: [r77:DI-0x8]=r97:DI
" ]



# function number 28
	node [ id 5449 graphics [ fill "#ffffff" ] label "rhp_sp_next ()
ENTRY" ]

	node [ id 5450 graphics [ fill "#ffffff" ] label "rhp_sp_next ()
EXIT" ]

	node [ id 5451 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x18]=di:DI
    3: [r77:DI-0x20]=si:DI
    4: NOTE_INSN_FUNCTION_BEG
    7: [r77:DI-0x8]=0
    8: flags:CCZ=cmp([r77:DI-0x18],0)
    9: pc={(flags:CCZ!=0)?L14:pc}
" ]

	node [ id 5452 graphics [ fill "#d3d3d3" ] label "   10: NOTE_INSN_BASIC_BLOCK 4
   11: r87:DI=0
   12: pc=L66
" ]

	node [ id 5453 graphics [ fill "#d3d3d3" ] label "   14: L14:
   15: NOTE_INSN_BASIC_BLOCK 5
   16: r89:DI=[r77:DI-0x18]
   17: r82:DI=[r89:DI]
   18: flags:CCZ=cmp(r82:DI,0)
   19: pc={(flags:CCZ!=0)?L24:pc}
" ]

	node [ id 5454 graphics [ fill "#d3d3d3" ] label "   20: NOTE_INSN_BASIC_BLOCK 6
   21: r87:DI=0
   22: pc=L66
" ]

	node [ id 5455 graphics [ fill "#d3d3d3" ] label "   24: L24:
   25: NOTE_INSN_BASIC_BLOCK 7
   26: r90:DI=[r77:DI-0x20]
   27: r91:DI=[r77:DI-0x18]
   28: si:DI=r90:DI
   29: di:DI=r91:DI
   30: call [`rhp_sp_sp'] argc:0
   31: r92:DI=[r77:DI-0x18]
   32: r83:DI=[r92:DI]
   33: r84:DI=[r83:DI]
   34: flags:CCGC=cmp([r77:DI-0x20],r84:DI)
   35: pc={(flags:CCGC&gt;=0)?L41:pc}
" ]

	node [ id 5456 graphics [ fill "#d3d3d3" ] label "   36: NOTE_INSN_BASIC_BLOCK 8
   37: r93:DI=[r77:DI-0x18]
   38: r87:DI=[r93:DI]
   39: pc=L66
" ]

	node [ id 5457 graphics [ fill "#d3d3d3" ] label "   41: L41:
   42: NOTE_INSN_BASIC_BLOCK 9
   43: r94:DI=[r77:DI-0x18]
   44: r85:DI=[r94:DI]
   45: r95:DI=[r85:DI+0x18]
   46: [r77:DI-0x8]=r95:DI
   47: flags:CCZ=cmp([r77:DI-0x8],0)
   48: pc={(flags:CCZ==0)?L63:pc}
" ]

	node [ id 5458 graphics [ fill "#d3d3d3" ] label "   49: NOTE_INSN_BASIC_BLOCK 10
   50: pc=L56
" ]

	node [ id 5459 graphics [ fill "#d3d3d3" ] label "   63: L63:
   64: NOTE_INSN_BASIC_BLOCK 13
   65: r87:DI=[r77:DI-0x8]
" ]

	node [ id 5460 graphics [ fill "#d3d3d3" ] label "   66: L66:
   67: NOTE_INSN_BASIC_BLOCK 14
   68: r88:DI=r87:DI
   72: ax:DI=r88:DI
   73: use ax:DI
" ]

	edge [ source 5449 target 5451 graphics [ fill "#0000ff" ] ] 
	edge [ source 5451 target 5452 graphics [ fill "#0000ff" ] ] 
	edge [ source 5451 target 5453 graphics [ fill "#000000" ] ] 
	edge [ source 5452 target 5460 graphics [ fill "#000000" ] ] 
	edge [ source 5453 target 5454 graphics [ fill "#0000ff" ] ] 
	edge [ source 5453 target 5455 graphics [ fill "#000000" ] ] 
	edge [ source 5454 target 5460 graphics [ fill "#000000" ] ] 
	edge [ source 5455 target 5456 graphics [ fill "#0000ff" ] ] 
	edge [ source 5455 target 5457 graphics [ fill "#000000" ] ] 
	edge [ source 5456 target 5460 graphics [ fill "#000000" ] ] 
	edge [ source 5457 target 5458 graphics [ fill "#0000ff" ] ] 
	edge [ source 5457 target 5459 graphics [ fill "#000000" ] ] 
	edge [ source 5458 target 5447 graphics [ fill "#000000" ] ] 
	edge [ source 5448 target 5447 graphics [ fill "#0000ff" ] ] 
	edge [ source 5447 target 5448 graphics [ fill "#000000" ] ] 
	edge [ source 5447 target 5459 graphics [ fill "#0000ff" ] ] 
	edge [ source 5459 target 5460 graphics [ fill "#0000ff" ] ] 
	edge [ source 5460 target 5450 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 29
	node [ id 5685 graphics [ fill "#ffffff" ] label "rhp_sp_lookup ()
ENTRY" ]

	node [ id 5686 graphics [ fill "#ffffff" ] label "rhp_sp_lookup ()
EXIT" ]

	node [ id 5687 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x18]=di:DI
    3: [r77:DI-0x20]=si:DI
    4: NOTE_INSN_FUNCTION_BEG
    7: [r77:DI-0x8]=`*.LC61'
    8: flags:CCZ=cmp([r77:DI-0x18],0)
    9: pc={(flags:CCZ!=0)?L14:pc}
" ]

	node [ id 5688 graphics [ fill "#d3d3d3" ] label "   10: NOTE_INSN_BASIC_BLOCK 4
   11: r95:DI=0
   12: pc=L101
" ]

	node [ id 5689 graphics [ fill "#d3d3d3" ] label "   14: L14:
   15: NOTE_INSN_BASIC_BLOCK 5
   16: r97:DI=[r77:DI-0x18]
   17: r82:DI=[r97:DI]
   18: flags:CCZ=cmp(r82:DI,0)
   19: pc={(flags:CCZ!=0)?L24:pc}
" ]

	node [ id 5690 graphics [ fill "#d3d3d3" ] label "   20: NOTE_INSN_BASIC_BLOCK 6
   21: r95:DI=0
   22: pc=L101
" ]

	node [ id 5691 graphics [ fill "#d3d3d3" ] label "   24: L24:
   25: NOTE_INSN_BASIC_BLOCK 7
   26: r98:DI=[r77:DI-0x18]
   27: r83:DI=[r98:DI]
   28: r84:DI=[r83:DI]
   29: flags:CCZ=cmp([r77:DI-0x20],r84:DI)
   30: pc={(flags:CCZ!=0)?L36:pc}
" ]

	node [ id 5692 graphics [ fill "#d3d3d3" ] label "   31: NOTE_INSN_BASIC_BLOCK 8
   32: r99:DI=[r77:DI-0x18]
   33: r95:DI=[r99:DI]
   34: pc=L101
" ]

	node [ id 5693 graphics [ fill "#d3d3d3" ] label "   36: L36:
   37: NOTE_INSN_BASIC_BLOCK 9
   38: r100:DI=[r77:DI-0x20]
   39: r101:DI=[r77:DI-0x18]
   40: si:DI=r100:DI
   41: di:DI=r101:DI
   42: call [`rhp_sp_sp'] argc:0
   43: r102:DI=[r77:DI-0x18]
   44: r85:DI=[r102:DI]
   45: flags:CCZ=cmp(r85:DI,0)
   46: pc={(flags:CCZ!=0)?L51:pc}
" ]

	node [ id 5694 graphics [ fill "#d3d3d3" ] label "   47: NOTE_INSN_BASIC_BLOCK 10
   48: r95:DI=0
   49: pc=L101
" ]

	node [ id 5695 graphics [ fill "#d3d3d3" ] label "   51: L51:
   52: NOTE_INSN_BASIC_BLOCK 11
   53: r103:DI=[r77:DI-0x18]
   54: r86:DI=[r103:DI]
   55: r87:DI=[r86:DI]
   56: flags:CCZ=cmp([r77:DI-0x20],r87:DI)
   57: pc={(flags:CCZ!=0)?L62:pc}
" ]

	node [ id 5696 graphics [ fill "#d3d3d3" ] label "   58: NOTE_INSN_BASIC_BLOCK 12
   59: [r77:DI-0x8]=`*.LC62'
   60: pc=L65
" ]

	node [ id 5697 graphics [ fill "#d3d3d3" ] label "   62: L62:
   63: NOTE_INSN_BASIC_BLOCK 13
   64: [r77:DI-0x8]=`*.LC61'
" ]

	node [ id 5698 graphics [ fill "#d3d3d3" ] label "   65: L65:
   66: NOTE_INSN_BASIC_BLOCK 14
   67: r88:SI=[`rhp_verbose']
   68: flags:CCZ=cmp(r88:SI,0)
   69: pc={(flags:CCZ==0)?L86:pc}
" ]

	node [ id 5699 graphics [ fill "#d3d3d3" ] label "   70: NOTE_INSN_BASIC_BLOCK 15
   71: r89:DI=[r77:DI-0x20]
   72: r104:DI=[r77:DI-0x18]
   73: r90:DI=[r104:DI]
   74: r91:DI=[r90:DI]
   75: r92:DI=r91:DI
   76: r105:DI=[r77:DI-0x18]
   77: r106:DI=[r77:DI-0x8]
   78: r9:DI=r89:DI
   79: r8:DI=r92:DI
   80: cx:DI=r105:DI
   81: dx:DI=r106:DI
   82: si:DI=`__FUNCTION__.28'
   83: di:DI=`*.LC63'
   84: ax:QI=0
   85: call [`rhp_log'] argc:0
" ]

	node [ id 5700 graphics [ fill "#d3d3d3" ] label "   86: L86:
   87: NOTE_INSN_BASIC_BLOCK 16
   88: r107:DI=[r77:DI-0x18]
   89: r93:DI=[r107:DI]
   90: r94:DI=[r93:DI]
   91: flags:CCZ=cmp([r77:DI-0x20],r94:DI)
   92: pc={(flags:CCZ!=0)?L98:pc}
" ]

	node [ id 5701 graphics [ fill "#d3d3d3" ] label "   93: NOTE_INSN_BASIC_BLOCK 17
   94: r108:DI=[r77:DI-0x18]
   95: r95:DI=[r108:DI]
   96: pc=L101
" ]

	node [ id 5702 graphics [ fill "#d3d3d3" ] label "   98: L98:
   99: NOTE_INSN_BASIC_BLOCK 18
  100: r95:DI=0
" ]

	node [ id 5703 graphics [ fill "#d3d3d3" ] label "  101: L101:
  102: NOTE_INSN_BASIC_BLOCK 19
  103: r96:DI=r95:DI
  107: ax:DI=r96:DI
  108: use ax:DI
" ]

	edge [ source 5685 target 5687 graphics [ fill "#0000ff" ] ] 
	edge [ source 5687 target 5688 graphics [ fill "#0000ff" ] ] 
	edge [ source 5687 target 5689 graphics [ fill "#000000" ] ] 
	edge [ source 5688 target 5703 graphics [ fill "#000000" ] ] 
	edge [ source 5689 target 5690 graphics [ fill "#0000ff" ] ] 
	edge [ source 5689 target 5691 graphics [ fill "#000000" ] ] 
	edge [ source 5690 target 5703 graphics [ fill "#000000" ] ] 
	edge [ source 5691 target 5692 graphics [ fill "#0000ff" ] ] 
	edge [ source 5691 target 5693 graphics [ fill "#000000" ] ] 
	edge [ source 5692 target 5703 graphics [ fill "#000000" ] ] 
	edge [ source 5693 target 5694 graphics [ fill "#0000ff" ] ] 
	edge [ source 5693 target 5695 graphics [ fill "#000000" ] ] 
	edge [ source 5694 target 5703 graphics [ fill "#000000" ] ] 
	edge [ source 5695 target 5696 graphics [ fill "#0000ff" ] ] 
	edge [ source 5695 target 5697 graphics [ fill "#000000" ] ] 
	edge [ source 5696 target 5698 graphics [ fill "#000000" ] ] 
	edge [ source 5697 target 5698 graphics [ fill "#0000ff" ] ] 
	edge [ source 5698 target 5699 graphics [ fill "#0000ff" ] ] 
	edge [ source 5698 target 5700 graphics [ fill "#000000" ] ] 
	edge [ source 5699 target 5700 graphics [ fill "#0000ff" ] ] 
	edge [ source 5700 target 5701 graphics [ fill "#0000ff" ] ] 
	edge [ source 5700 target 5702 graphics [ fill "#000000" ] ] 
	edge [ source 5701 target 5703 graphics [ fill "#000000" ] ] 
	edge [ source 5702 target 5703 graphics [ fill "#0000ff" ] ] 
	edge [ source 5703 target 5686 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 30
	node [ id 6008 graphics [ fill "#ffffff" ] label "rhp_sp_sp_rl ()
ENTRY" ]

	node [ id 6009 graphics [ fill "#ffffff" ] label "rhp_sp_sp_rl ()
EXIT" ]

	node [ id 6010 graphics [ fill "#d3d3d3" ] label "    6: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x18]=di:DI
    3: [r77:DI-0x20]=si:DI
    4: [r77:DI-0x28]=dx:DI
    5: NOTE_INSN_FUNCTION_BEG
    8: [r77:DI-0x8]=0
    9: r82:DI=[r77:DI-0x28]
   10: r83:DI=[r82:DI+0x18]
   11: [r77:DI-0x8]=r83:DI
   12: r84:DI=[r77:DI-0x28]
   13: r85:DI=[r77:DI-0x20]
   14: [r84:DI+0x18]=r85:DI
   15: r86:DI=[r77:DI-0x20]
   16: r87:DI=[r77:DI-0x8]
   17: [r86:DI+0x10]=r87:DI
   18: r88:DI=[r77:DI-0x18]
   19: r89:DI=[r77:DI-0x28]
   20: [r88:DI]=r89:DI
   25: 0
" ]

	edge [ source 6008 target 6010 graphics [ fill "#0000ff" ] ] 
	edge [ source 6010 target 6009 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 31
	node [ id 6059 graphics [ fill "#ffffff" ] label "rhp_sp_sp_rr ()
ENTRY" ]

	node [ id 6060 graphics [ fill "#ffffff" ] label "rhp_sp_sp_rr ()
EXIT" ]

	node [ id 6061 graphics [ fill "#d3d3d3" ] label "    6: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x18]=di:DI
    3: [r77:DI-0x20]=si:DI
    4: [r77:DI-0x28]=dx:DI
    5: NOTE_INSN_FUNCTION_BEG
    8: [r77:DI-0x8]=0
    9: r82:DI=[r77:DI-0x28]
   10: r83:DI=[r82:DI+0x10]
   11: [r77:DI-0x8]=r83:DI
   12: r84:DI=[r77:DI-0x28]
   13: r85:DI=[r77:DI-0x20]
   14: [r84:DI+0x10]=r85:DI
   15: r86:DI=[r77:DI-0x20]
   16: r87:DI=[r77:DI-0x8]
   17: [r86:DI+0x18]=r87:DI
   18: r88:DI=[r77:DI-0x18]
   19: r89:DI=[r77:DI-0x28]
   20: [r88:DI]=r89:DI
   25: 0
" ]

	edge [ source 6059 target 6061 graphics [ fill "#0000ff" ] ] 
	edge [ source 6061 target 6060 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 6110 graphics [ fill "#d3d3d3" ] label "   23: L23:
   24: NOTE_INSN_BASIC_BLOCK 7
   25: r127:DI=[r77:DI-0x18]
   26: r128:DI=[r127:DI]
   27: [r77:DI-0x10]=r128:DI
   28: flags:CCZ=cmp([r77:DI-0x10],0)
   29: pc={(flags:CCZ!=0)?L33:pc}
" ]

	node [ id 6111 graphics [ fill "#d3d3d3" ] label "   33: L33:
   34: NOTE_INSN_BASIC_BLOCK 9
   35: r83:SI=[`rhp_verbose']
   36: flags:CCZ=cmp(r83:SI,0)
   37: pc={(flags:CCZ==0)?L49:pc}
" ]

	node [ id 6112 graphics [ fill "#d3d3d3" ] label "   38: NOTE_INSN_BASIC_BLOCK 10
   39: r84:DI=[r77:DI-0x20]
   40: r129:DI=[r77:DI-0x10]
   41: r85:DI=[r129:DI]
   42: r86:DI=r85:DI
   43: cx:DI=r84:DI
   44: dx:DI=r86:DI
   45: si:DI=`__FUNCTION__.27'
   46: di:DI=`*.LC64'
   47: ax:QI=0
   48: call [`rhp_log'] argc:0
" ]

	node [ id 6113 graphics [ fill "#d3d3d3" ] label "   49: L49:
   50: NOTE_INSN_BASIC_BLOCK 11
   51: r130:DI=[r77:DI-0x10]
   52: r87:DI=[r130:DI]
   53: flags:CCZ=cmp([r77:DI-0x20],r87:DI)
   54: pc={(flags:CCZ!=0)?L58:pc}
" ]

	node [ id 6114 graphics [ fill "#d3d3d3" ] label "   58: L58:
   59: NOTE_INSN_BASIC_BLOCK 13
   60: r131:DI=[r77:DI-0x10]
   61: r88:DI=[r131:DI]
   62: flags:CCGC=cmp([r77:DI-0x20],r88:DI)
   63: pc={(flags:CCGC&gt;=0)?L70:pc}
" ]

	node [ id 6115 graphics [ fill "#d3d3d3" ] label "   64: NOTE_INSN_BASIC_BLOCK 14
   65: r132:DI=[r77:DI-0x10]
   66: r133:DI=[r132:DI+0x10]
   67: [r77:DI-0x8]=r133:DI
   68: pc=L75
" ]

	node [ id 6116 graphics [ fill "#d3d3d3" ] label "   70: L70:
   71: NOTE_INSN_BASIC_BLOCK 15
   72: r134:DI=[r77:DI-0x10]
   73: r135:DI=[r134:DI+0x18]
   74: [r77:DI-0x8]=r135:DI
" ]

	node [ id 6117 graphics [ fill "#d3d3d3" ] label "   75: L75:
   76: NOTE_INSN_BASIC_BLOCK 16
   77: flags:CCZ=cmp([r77:DI-0x8],0)
   78: pc={(flags:CCZ!=0)?L99:pc}
" ]

	node [ id 6118 graphics [ fill "#d3d3d3" ] label "   99: L99:
  100: NOTE_INSN_BASIC_BLOCK 20
  101: r137:DI=[r77:DI-0x8]
  102: r94:DI=[r137:DI]
  103: flags:CCZ=cmp([r77:DI-0x20],r94:DI)
  104: pc={(flags:CCZ==0)?L126:pc}
" ]

	node [ id 6119 graphics [ fill "#d3d3d3" ] label "  105: NOTE_INSN_BASIC_BLOCK 21
  106: r138:DI=[r77:DI-0x8]
  107: r95:DI=[r138:DI]
  108: flags:CCGC=cmp([r77:DI-0x20],r95:DI)
  109: pc={(flags:CCGC&gt;=0)?L115:pc}
" ]

	node [ id 6120 graphics [ fill "#d3d3d3" ] label "  110: NOTE_INSN_BASIC_BLOCK 22
  111: r139:DI=[r77:DI-0x8]
  112: r96:DI=[r139:DI+0x10]
  113: flags:CCZ=cmp(r96:DI,0)
  114: pc={(flags:CCZ==0)?L126:pc}
" ]

	node [ id 6121 graphics [ fill "#d3d3d3" ] label "  115: L115:
  116: NOTE_INSN_BASIC_BLOCK 23
  117: r140:DI=[r77:DI-0x8]
  118: r97:DI=[r140:DI]
  119: flags:CCGC=cmp([r77:DI-0x20],r97:DI)
  120: pc={(flags:CCGC&lt;=0)?L155:pc}
" ]

	node [ id 6122 graphics [ fill "#d3d3d3" ] label "  121: NOTE_INSN_BASIC_BLOCK 24
  122: r141:DI=[r77:DI-0x8]
  123: r98:DI=[r141:DI+0x18]
  124: flags:CCZ=cmp(r98:DI,0)
  125: pc={(flags:CCZ!=0)?L155:pc}
" ]

	node [ id 6123 graphics [ fill "#d3d3d3" ] label "  155: L155:
  156: NOTE_INSN_BASIC_BLOCK 29
  157: r147:DI=[r77:DI-0x10]
  158: r102:DI=[r147:DI]
  159: flags:CCGC=cmp([r77:DI-0x20],r102:DI)
  160: pc={(flags:CCGC&gt;=0)?L186:pc}
" ]

	node [ id 6124 graphics [ fill "#d3d3d3" ] label "  161: NOTE_INSN_BASIC_BLOCK 30
  162: r148:DI=[r77:DI-0x8]
  163: r103:DI=[r148:DI]
  164: flags:CCGC=cmp([r77:DI-0x20],r103:DI)
  165: pc={(flags:CCGC&gt;=0)?L186:pc}
" ]

	node [ id 6125 graphics [ fill "#d3d3d3" ] label "  186: L186:
  187: NOTE_INSN_BASIC_BLOCK 32
  188: r154:DI=[r77:DI-0x10]
  189: r108:DI=[r154:DI]
  190: flags:CCGC=cmp([r77:DI-0x20],r108:DI)
  191: pc={(flags:CCGC&lt;=0)?L217:pc}
" ]

	node [ id 6126 graphics [ fill "#d3d3d3" ] label "  166: NOTE_INSN_BASIC_BLOCK 31
  167: r149:DI=[r77:DI-0x8]
  168: r104:DI=[r149:DI+0x10]
  169: r150:DI=[r77:DI-0x10]
  170: {r105:DI=r150:DI+0x10;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x10]+0x10
  171: r151:DI=[r77:DI-0x8]
  172: dx:DI=r104:DI
  173: si:DI=r151:DI
  174: di:DI=r105:DI
  175: call [`rhp_sp_sp_rl'] argc:0
  176: r152:DI=[r77:DI-0x10]
  177: r106:DI=[r152:DI+0x10]
  178: r107:DI=[r77:DI-0x18]
  179: r153:DI=[r77:DI-0x10]
  180: dx:DI=r106:DI
  181: si:DI=r153:DI
  182: di:DI=r107:DI
  183: call [`rhp_sp_sp_rl'] argc:0
  184: pc=L277
" ]

	node [ id 6127 graphics [ fill "#d3d3d3" ] label "  192: NOTE_INSN_BASIC_BLOCK 33
  193: r155:DI=[r77:DI-0x8]
  194: r109:DI=[r155:DI]
  195: flags:CCGC=cmp([r77:DI-0x20],r109:DI)
  196: pc={(flags:CCGC&lt;=0)?L217:pc}
" ]

	node [ id 6128 graphics [ fill "#d3d3d3" ] label "  217: L217:
  218: NOTE_INSN_BASIC_BLOCK 35
  219: r161:DI=[r77:DI-0x10]
  220: r114:DI=[r161:DI]
  221: flags:CCGC=cmp([r77:DI-0x20],r114:DI)
  222: pc={(flags:CCGC&gt;=0)?L248:pc}
" ]

	node [ id 6129 graphics [ fill "#d3d3d3" ] label "  277: L277:
  278: NOTE_INSN_BASIC_BLOCK 41
  279: pc=L23
" ]

	node [ id 6130 graphics [ fill "#d3d3d3" ] label "  197: NOTE_INSN_BASIC_BLOCK 34
  198: r156:DI=[r77:DI-0x8]
  199: r110:DI=[r156:DI+0x18]
  200: r157:DI=[r77:DI-0x10]
  201: {r111:DI=r157:DI+0x18;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x10]+0x18
  202: r158:DI=[r77:DI-0x8]
  203: dx:DI=r110:DI
  204: si:DI=r158:DI
  205: di:DI=r111:DI
  206: call [`rhp_sp_sp_rr'] argc:0
  207: r159:DI=[r77:DI-0x10]
  208: r112:DI=[r159:DI+0x18]
  209: r113:DI=[r77:DI-0x18]
  210: r160:DI=[r77:DI-0x10]
  211: dx:DI=r112:DI
  212: si:DI=r160:DI
  213: di:DI=r113:DI
  214: call [`rhp_sp_sp_rr'] argc:0
  215: pc=L277
" ]

	node [ id 6131 graphics [ fill "#d3d3d3" ] label "  223: NOTE_INSN_BASIC_BLOCK 36
  224: r162:DI=[r77:DI-0x8]
  225: r115:DI=[r162:DI]
  226: flags:CCGC=cmp([r77:DI-0x20],r115:DI)
  227: pc={(flags:CCGC&lt;=0)?L248:pc}
" ]

	node [ id 6132 graphics [ fill "#d3d3d3" ] label "  248: L248:
  249: NOTE_INSN_BASIC_BLOCK 38
  250: r168:DI=[r77:DI-0x10]
  251: r120:DI=[r168:DI]
  252: flags:CCGC=cmp([r77:DI-0x20],r120:DI)
  253: pc={(flags:CCGC&lt;=0)?L277:pc}
" ]

	node [ id 6133 graphics [ fill "#d3d3d3" ] label "  228: NOTE_INSN_BASIC_BLOCK 37
  229: r163:DI=[r77:DI-0x8]
  230: r116:DI=[r163:DI+0x18]
  231: r164:DI=[r77:DI-0x10]
  232: {r117:DI=r164:DI+0x10;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x10]+0x10
  233: r165:DI=[r77:DI-0x8]
  234: dx:DI=r116:DI
  235: si:DI=r165:DI
  236: di:DI=r117:DI
  237: call [`rhp_sp_sp_rr'] argc:0
  238: r166:DI=[r77:DI-0x10]
  239: r118:DI=[r166:DI+0x10]
  240: r119:DI=[r77:DI-0x18]
  241: r167:DI=[r77:DI-0x10]
  242: dx:DI=r118:DI
  243: si:DI=r167:DI
  244: di:DI=r119:DI
  245: call [`rhp_sp_sp_rl'] argc:0
  246: pc=L277
" ]

	node [ id 6134 graphics [ fill "#d3d3d3" ] label "  254: NOTE_INSN_BASIC_BLOCK 39
  255: r169:DI=[r77:DI-0x8]
  256: r121:DI=[r169:DI]
  257: flags:CCGC=cmp([r77:DI-0x20],r121:DI)
  258: pc={(flags:CCGC&gt;=0)?L277:pc}
" ]

	node [ id 6135 graphics [ fill "#d3d3d3" ] label "  259: NOTE_INSN_BASIC_BLOCK 40
  260: r170:DI=[r77:DI-0x8]
  261: r122:DI=[r170:DI+0x10]
  262: r171:DI=[r77:DI-0x10]
  263: {r123:DI=r171:DI+0x18;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x10]+0x18
  264: r172:DI=[r77:DI-0x8]
  265: dx:DI=r122:DI
  266: si:DI=r172:DI
  267: di:DI=r123:DI
  268: call [`rhp_sp_sp_rl'] argc:0
  269: r173:DI=[r77:DI-0x10]
  270: r124:DI=[r173:DI+0x18]
  271: r125:DI=[r77:DI-0x18]
  272: r174:DI=[r77:DI-0x10]
  273: dx:DI=r124:DI
  274: si:DI=r174:DI
  275: di:DI=r125:DI
  276: call [`rhp_sp_sp_rr'] argc:0
" ]



# function number 32
	node [ id 6136 graphics [ fill "#ffffff" ] label "rhp_sp_sp ()
ENTRY" ]

	node [ id 6137 graphics [ fill "#ffffff" ] label "rhp_sp_sp ()
EXIT" ]

	node [ id 6138 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x18]=di:DI
    3: [r77:DI-0x20]=si:DI
    4: NOTE_INSN_FUNCTION_BEG
    7: [r77:DI-0x10]=0
    8: [r77:DI-0x8]=0
    9: flags:CCZ=cmp([r77:DI-0x18],0)
   10: pc={(flags:CCZ!=0)?L14:pc}
" ]

	node [ id 6139 graphics [ fill "#d3d3d3" ] label "   11: NOTE_INSN_BASIC_BLOCK 4
   12: pc=L283
" ]

	node [ id 6140 graphics [ fill "#d3d3d3" ] label "   14: L14:
   15: NOTE_INSN_BASIC_BLOCK 5
   16: r126:DI=[r77:DI-0x18]
   17: r82:DI=[r126:DI]
   18: flags:CCZ=cmp(r82:DI,0)
   19: pc={(flags:CCZ!=0)?L23:pc}
" ]

	node [ id 6141 graphics [ fill "#d3d3d3" ] label "   20: NOTE_INSN_BASIC_BLOCK 6
   21: pc=L283
" ]

	node [ id 6142 graphics [ fill "#d3d3d3" ] label "   30: NOTE_INSN_BASIC_BLOCK 8
   31: pc=L283
" ]

	node [ id 6143 graphics [ fill "#d3d3d3" ] label "   55: NOTE_INSN_BASIC_BLOCK 12
   56: pc=L283
" ]

	node [ id 6144 graphics [ fill "#d3d3d3" ] label "   79: NOTE_INSN_BASIC_BLOCK 17
   80: r89:SI=[`rhp_verbose']
   81: flags:CCZ=cmp(r89:SI,0)
   82: pc={(flags:CCZ==0)?L283:pc}
" ]

	node [ id 6145 graphics [ fill "#d3d3d3" ] label "   83: NOTE_INSN_BASIC_BLOCK 18
   84: r90:DI=[r77:DI-0x20]
   85: r136:DI=[r77:DI-0x18]
   86: r91:DI=[r136:DI]
   87: r92:DI=[r91:DI]
   88: r93:DI=r92:DI
   89: cx:DI=r90:DI
   90: dx:DI=r93:DI
   91: si:DI=`__FUNCTION__.27'
   92: di:DI=`*.LC65'
   93: ax:QI=0
   94: call [`rhp_log'] argc:0
   97: pc=L283
" ]

	node [ id 6146 graphics [ fill "#d3d3d3" ] label "  126: L126:
  127: NOTE_INSN_BASIC_BLOCK 25
  128: r142:DI=[r77:DI-0x10]
  129: r99:DI=[r142:DI]
  130: flags:CCGC=cmp([r77:DI-0x20],r99:DI)
  131: pc={(flags:CCGC&gt;=0)?L142:pc}
" ]

	node [ id 6147 graphics [ fill "#d3d3d3" ] label "  132: NOTE_INSN_BASIC_BLOCK 26
  133: r100:DI=[r77:DI-0x18]
  134: r143:DI=[r77:DI-0x8]
  135: r144:DI=[r77:DI-0x10]
  136: dx:DI=r143:DI
  137: si:DI=r144:DI
  138: di:DI=r100:DI
  139: call [`rhp_sp_sp_rl'] argc:0
  140: pc=L283
" ]

	node [ id 6148 graphics [ fill "#d3d3d3" ] label "  142: L142:
  143: NOTE_INSN_BASIC_BLOCK 27
  144: r101:DI=[r77:DI-0x18]
  145: r145:DI=[r77:DI-0x8]
  146: r146:DI=[r77:DI-0x10]
  147: dx:DI=r145:DI
  148: si:DI=r146:DI
  149: di:DI=r101:DI
  150: call [`rhp_sp_sp_rr'] argc:0
  153: pc=L283
" ]

	node [ id 6149 graphics [ fill "#d3d3d3" ] label "  283: L283:
  284: NOTE_INSN_BASIC_BLOCK 43
" ]

	edge [ source 6136 target 6138 graphics [ fill "#0000ff" ] ] 
	edge [ source 6138 target 6139 graphics [ fill "#0000ff" ] ] 
	edge [ source 6138 target 6140 graphics [ fill "#000000" ] ] 
	edge [ source 6139 target 6149 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 6140 target 6141 graphics [ fill "#0000ff" ] ] 
	edge [ source 6140 target 6110 graphics [ fill "#000000" ] ] 
	edge [ source 6141 target 6149 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 6110 target 6142 graphics [ fill "#0000ff" ] ] 
	edge [ source 6110 target 6111 graphics [ fill "#000000" ] ] 
	edge [ source 6142 target 6149 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 6111 target 6112 graphics [ fill "#0000ff" ] ] 
	edge [ source 6111 target 6113 graphics [ fill "#000000" ] ] 
	edge [ source 6112 target 6113 graphics [ fill "#0000ff" ] ] 
	edge [ source 6113 target 6143 graphics [ fill "#0000ff" ] ] 
	edge [ source 6113 target 6114 graphics [ fill "#000000" ] ] 
	edge [ source 6143 target 6149 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 6114 target 6115 graphics [ fill "#0000ff" ] ] 
	edge [ source 6114 target 6116 graphics [ fill "#000000" ] ] 
	edge [ source 6115 target 6117 graphics [ fill "#000000" ] ] 
	edge [ source 6116 target 6117 graphics [ fill "#0000ff" ] ] 
	edge [ source 6117 target 6144 graphics [ fill "#0000ff" ] ] 
	edge [ source 6117 target 6118 graphics [ fill "#000000" ] ] 
	edge [ source 6144 target 6145 graphics [ fill "#0000ff" ] ] 
	edge [ source 6144 target 6149 graphics [ fill "#000000" ] ] 
	edge [ source 6145 target 6149 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 6118 target 6146 graphics [ fill "#000000" ] ] 
	edge [ source 6118 target 6119 graphics [ fill "#0000ff" ] ] 
	edge [ source 6119 target 6120 graphics [ fill "#0000ff" ] ] 
	edge [ source 6119 target 6121 graphics [ fill "#000000" ] ] 
	edge [ source 6120 target 6146 graphics [ fill "#000000" ] ] 
	edge [ source 6120 target 6121 graphics [ fill "#0000ff" ] ] 
	edge [ source 6121 target 6122 graphics [ fill "#0000ff" ] ] 
	edge [ source 6121 target 6123 graphics [ fill "#000000" ] ] 
	edge [ source 6122 target 6146 graphics [ fill "#0000ff" ] ] 
	edge [ source 6122 target 6123 graphics [ fill "#000000" ] ] 
	edge [ source 6146 target 6147 graphics [ fill "#0000ff" ] ] 
	edge [ source 6146 target 6148 graphics [ fill "#000000" ] ] 
	edge [ source 6147 target 6149 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 6148 target 6149 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 6123 target 6124 graphics [ fill "#0000ff" ] ] 
	edge [ source 6123 target 6125 graphics [ fill "#000000" ] ] 
	edge [ source 6124 target 6126 graphics [ fill "#0000ff" ] ] 
	edge [ source 6124 target 6125 graphics [ fill "#000000" ] ] 
	edge [ source 6126 target 6129 graphics [ fill "#000000" ] ] 
	edge [ source 6125 target 6127 graphics [ fill "#0000ff" ] ] 
	edge [ source 6125 target 6128 graphics [ fill "#000000" ] ] 
	edge [ source 6127 target 6130 graphics [ fill "#0000ff" ] ] 
	edge [ source 6127 target 6128 graphics [ fill "#000000" ] ] 
	edge [ source 6130 target 6129 graphics [ fill "#000000" ] ] 
	edge [ source 6128 target 6131 graphics [ fill "#0000ff" ] ] 
	edge [ source 6128 target 6132 graphics [ fill "#000000" ] ] 
	edge [ source 6131 target 6133 graphics [ fill "#0000ff" ] ] 
	edge [ source 6131 target 6132 graphics [ fill "#000000" ] ] 
	edge [ source 6133 target 6129 graphics [ fill "#000000" ] ] 
	edge [ source 6132 target 6134 graphics [ fill "#0000ff" ] ] 
	edge [ source 6132 target 6129 graphics [ fill "#000000" ] ] 
	edge [ source 6134 target 6135 graphics [ fill "#0000ff" ] ] 
	edge [ source 6134 target 6129 graphics [ fill "#000000" ] ] 
	edge [ source 6135 target 6129 graphics [ fill "#0000ff" ] ] 
	edge [ source 6129 target 6110 graphics [ fill "#0000ff" ] ] 
	edge [ source 6149 target 6137 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 6802 graphics [ fill "#d3d3d3" ] label "   40: L40:
   41: NOTE_INSN_BASIC_BLOCK 9
   42: r93:DI=[r77:DI-0x8]
   43: r83:QI=[r93:DI]
   45: flags:CCZ=cmp(r83:QI,0)
   46: pc={(flags:CCZ!=0)?L44:pc}
" ]

	node [ id 6803 graphics [ fill "#d3d3d3" ] label "   44: L44:
   29: NOTE_INSN_BASIC_BLOCK 6
   30: r91:DI=[r77:DI-0x8]
   31: r82:QI=[r91:DI]
   32: flags:CCZ=cmp(r82:QI,0x21)
   33: pc={(flags:CCZ!=0)?L37:pc}
" ]

	node [ id 6804 graphics [ fill "#d3d3d3" ] label "   34: NOTE_INSN_BASIC_BLOCK 7
   35: r92:DI=[r77:DI-0x8]
   36: [r77:DI-0x10]=r92:DI
" ]

	node [ id 6805 graphics [ fill "#d3d3d3" ] label "   37: L37:
   38: NOTE_INSN_BASIC_BLOCK 8
   39: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
" ]



# function number 33
	node [ id 6806 graphics [ fill "#ffffff" ] label "rhp_log ()
ENTRY" ]

	node [ id 6807 graphics [ fill "#ffffff" ] label "rhp_log ()
EXIT" ]

	node [ id 6808 graphics [ fill "#d3d3d3" ] label "   20: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x38]=di:DI
    3: [frame:DI+0x8]=si:DI
    4: [frame:DI+0x10]=dx:DI
    5: [frame:DI+0x18]=cx:DI
    6: [frame:DI+0x20]=r8:DI
    7: [frame:DI+0x28]=r9:DI
    8: flags:CCZ=cmp(ax:QI,0)
    9: pc={(flags:CCZ==0)?L107:pc}
" ]

	node [ id 6809 graphics [ fill "#d3d3d3" ] label "  105: NOTE_INSN_BASIC_BLOCK 3
   10: [frame:DI+0x30]=xmm0:V4SF
   11: [frame:DI+0x40]=xmm1:V4SF
   12: [frame:DI+0x50]=xmm2:V4SF
   13: [frame:DI+0x60]=xmm3:V4SF
   14: [frame:DI+0x70]=xmm4:V4SF
   15: [frame:DI+0x80]=xmm5:V4SF
   16: [frame:DI+0x90]=xmm6:V4SF
   17: [frame:DI+0xa0]=xmm7:V4SF
   19: NOTE_INSN_FUNCTION_BEG
" ]

	node [ id 6810 graphics [ fill "#d3d3d3" ] label "  107: L107:
   21: NOTE_INSN_BASIC_BLOCK 5
   22: [r77:DI-0x8]=0
   23: [r77:DI-0x10]=0
   24: r90:DI=[r77:DI-0x38]
   25: [r77:DI-0x8]=r90:DI
   26: [r77:DI-0x10]=0
   27: pc=L40
" ]

	node [ id 6811 graphics [ fill "#d3d3d3" ] label "   47: NOTE_INSN_BASIC_BLOCK 10
   48: flags:CCZ=cmp([r77:DI-0x10],0)
   49: pc={(flags:CCZ==0)?L66:pc}
" ]

	node [ id 6812 graphics [ fill "#d3d3d3" ] label "   50: NOTE_INSN_BASIC_BLOCK 11
   51: {r94:DI=r76:DI+0;clobber flags:CC;}
   52: [r77:DI-0x28]=0x8
   53: [r77:DI-0x24]=0x30
   54: [r77:DI-0x20]=r76:DI
   55: [r77:DI-0x18]=frame:DI
   56: r84:DI=[`stderr']
   57: {r95:DI=r77:DI-0x28;clobber flags:CC;}
   58: r96:DI=[r77:DI-0x38]
   59: dx:DI=r95:DI
   60: si:DI=r96:DI
   61: di:DI=r84:DI
   62: ax:SI=call [`vfprintf'] argc:0
   63: r85:DI=[`stderr']
   64: di:DI=r85:DI
   65: ax:SI=call [`fflush'] argc:0
" ]

	node [ id 6813 graphics [ fill "#d3d3d3" ] label "   66: L66:
   67: NOTE_INSN_BASIC_BLOCK 12
   68: r86:SI=[`rhp_dolog']
   69: flags:CCZ=cmp(r86:SI,0)
   70: pc={(flags:CCZ!=0)?L74:pc}
" ]

	node [ id 6814 graphics [ fill "#d3d3d3" ] label "   71: NOTE_INSN_BASIC_BLOCK 13
   72: pc=L103
" ]

	node [ id 6815 graphics [ fill "#d3d3d3" ] label "   74: L74:
   75: NOTE_INSN_BASIC_BLOCK 14
   76: r87:DI=[`rhp_logstream']
   77: flags:CCZ=cmp(r87:DI,0)
   78: pc={(flags:CCZ!=0)?L82:pc}
" ]

	node [ id 6816 graphics [ fill "#d3d3d3" ] label "   79: NOTE_INSN_BASIC_BLOCK 15
   80: pc=L103
" ]

	node [ id 6817 graphics [ fill "#d3d3d3" ] label "   82: L82:
   83: NOTE_INSN_BASIC_BLOCK 16
   84: {r97:DI=r76:DI+0;clobber flags:CC;}
   85: [r77:DI-0x28]=0x8
   86: [r77:DI-0x24]=0x30
   87: [r77:DI-0x20]=r76:DI
   88: [r77:DI-0x18]=frame:DI
   89: r88:DI=[`rhp_logstream']
   90: {r98:DI=r77:DI-0x28;clobber flags:CC;}
   91: r99:DI=[r77:DI-0x38]
   92: dx:DI=r98:DI
   93: si:DI=r99:DI
   94: di:DI=r88:DI
   95: ax:SI=call [`vfprintf'] argc:0
   96: r89:DI=[`rhp_logstream']
   97: di:DI=r89:DI
   98: ax:SI=call [`fflush'] argc:0
" ]

	node [ id 6818 graphics [ fill "#d3d3d3" ] label "  103: L103:
  104: NOTE_INSN_BASIC_BLOCK 19
" ]

	edge [ source 6806 target 6808 graphics [ fill "#0000ff" ] ] 
	edge [ source 6808 target 6810 graphics [ fill "#000000" ] ] 
	edge [ source 6808 target 6809 graphics [ fill "#0000ff" ] ] 
	edge [ source 6809 target 6810 graphics [ fill "#0000ff" ] label "[100%]"] 
	edge [ source 6810 target 6802 graphics [ fill "#000000" ] ] 
	edge [ source 6803 target 6804 graphics [ fill "#0000ff" ] ] 
	edge [ source 6803 target 6805 graphics [ fill "#000000" ] ] 
	edge [ source 6804 target 6805 graphics [ fill "#0000ff" ] ] 
	edge [ source 6805 target 6802 graphics [ fill "#0000ff" ] ] 
	edge [ source 6802 target 6803 graphics [ fill "#000000" ] ] 
	edge [ source 6802 target 6811 graphics [ fill "#0000ff" ] ] 
	edge [ source 6811 target 6812 graphics [ fill "#0000ff" ] ] 
	edge [ source 6811 target 6813 graphics [ fill "#000000" ] ] 
	edge [ source 6812 target 6813 graphics [ fill "#0000ff" ] ] 
	edge [ source 6813 target 6814 graphics [ fill "#0000ff" ] ] 
	edge [ source 6813 target 6815 graphics [ fill "#000000" ] ] 
	edge [ source 6814 target 6818 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 6815 target 6816 graphics [ fill "#0000ff" ] ] 
	edge [ source 6815 target 6817 graphics [ fill "#000000" ] ] 
	edge [ source 6816 target 6818 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 6817 target 6818 graphics [ fill "#0000ff" ] ] 
	edge [ source 6818 target 6807 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 7085 graphics [ fill "#d3d3d3" ] label "   67: L67:
   68: NOTE_INSN_BASIC_BLOCK 9
   69: r105:SI=[`rhp_nlevels']
   71: flags:CCGC=cmp([r77:DI-0x4],r105:SI)
   72: pc={(flags:CCGC&lt;0)?L70:pc}
" ]

	node [ id 7086 graphics [ fill "#d3d3d3" ] label "   70: L70:
   34: NOTE_INSN_BASIC_BLOCK 6
   35: r87:DI=[`rhp_best_crossings_order']
   36: r88:DI=[r87:DI+0x10]
   37: r112:SI=[r77:DI-0x4]
   38: r89:DI=sign_extend(r112:SI)
   39: {r90:DI=r89:DI&lt;&lt;0x3;clobber flags:CC;}
   40: {r91:DI=r88:DI+r90:DI;clobber flags:CC;}
   41: r92:DI=[r91:DI]
   42: flags:CCZ=cmp(r92:DI,0)
   43: pc={(flags:CCZ==0)?L64:pc}
" ]

	node [ id 7087 graphics [ fill "#d3d3d3" ] label "   44: NOTE_INSN_BASIC_BLOCK 7
   45: r93:DI=[`rhp_best_crossings_order']
   46: r94:DI=[r93:DI+0x10]
   47: r113:SI=[r77:DI-0x4]
   48: r95:DI=sign_extend(r113:SI)
   49: {r96:DI=r95:DI&lt;&lt;0x3;clobber flags:CC;}
   50: {r97:DI=r94:DI+r96:DI;clobber flags:CC;}
   51: r98:DI=[r97:DI]
   52: r99:DI=[`rhp_best_crossings_order']
   53: r100:DI=[r99:DI+0x10]
   54: r114:SI=[r77:DI-0x4]
   55: r101:DI=sign_extend(r114:SI)
   56: {r102:DI=r101:DI&lt;&lt;0x3;clobber flags:CC;}
   57: {r103:DI=r100:DI+r102:DI;clobber flags:CC;}
   58: dx:SI=0x893
   59: si:DI=`__FUNCTION__.26'
   60: di:DI=r98:DI
   61: ax:DI=call [`rhp_free'] argc:0
   62: r104:DI=ax:DI
   63: [r103:DI]=r104:DI
" ]

	node [ id 7088 graphics [ fill "#d3d3d3" ] label "   64: L64:
   65: NOTE_INSN_BASIC_BLOCK 8
   66: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]



# function number 34
	node [ id 7089 graphics [ fill "#ffffff" ] label "rhp_empty_best_crossings_order ()
ENTRY" ]

	node [ id 7090 graphics [ fill "#ffffff" ] label "rhp_empty_best_crossings_order ()
EXIT" ]

	node [ id 7091 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x4]=0
    6: si:DI=`__FUNCTION__.26'
    7: di:DI=`*.LC16'
    8: ax:QI=0
    9: call [`rhp_log'] argc:0
   10: r82:DI=[`rhp_best_crossings_order']
   11: flags:CCZ=cmp(r82:DI,0)
   12: pc={(flags:CCZ!=0)?L20:pc}
" ]

	node [ id 7092 graphics [ fill "#d3d3d3" ] label "   13: NOTE_INSN_BASIC_BLOCK 4
   14: si:DI=`__FUNCTION__.26'
   15: di:DI=`*.LC66'
   16: ax:QI=0
   17: call [`rhp_log'] argc:0
   18: pc=L92
" ]

	node [ id 7093 graphics [ fill "#d3d3d3" ] label "   20: L20:
   21: NOTE_INSN_BASIC_BLOCK 5
   22: r83:DI=[`rhp_best_crossings_order']
   23: r84:DI=[r83:DI+0x8]
   24: r85:DI=[`rhp_best_crossings_order']
   25: dx:SI=0x88b
   26: si:DI=`__FUNCTION__.26'
   27: di:DI=r84:DI
   28: ax:DI=call [`rhp_free'] argc:0
   29: r86:DI=ax:DI
   30: [r85:DI+0x8]=r86:DI
   31: [r77:DI-0x4]=0
   32: pc=L67
" ]

	node [ id 7094 graphics [ fill "#d3d3d3" ] label "   73: NOTE_INSN_BASIC_BLOCK 10
   74: r106:DI=[`rhp_best_crossings_order']
   75: r107:DI=[r106:DI+0x10]
   76: flags:CCZ=cmp(r107:DI,0)
   77: pc={(flags:CCZ==0)?L92:pc}
" ]

	node [ id 7095 graphics [ fill "#d3d3d3" ] label "   78: NOTE_INSN_BASIC_BLOCK 11
   79: r108:DI=[`rhp_best_crossings_order']
   80: r109:DI=[r108:DI+0x10]
   81: r110:DI=[`rhp_best_crossings_order']
   82: dx:SI=0x89b
   83: si:DI=`__FUNCTION__.26'
   84: di:DI=r109:DI
   85: ax:DI=call [`rhp_free'] argc:0
   86: r111:DI=ax:DI
   87: [r110:DI+0x10]=r111:DI
" ]

	node [ id 7096 graphics [ fill "#d3d3d3" ] label "   92: L92:
   93: NOTE_INSN_BASIC_BLOCK 14
" ]

	edge [ source 7089 target 7091 graphics [ fill "#0000ff" ] ] 
	edge [ source 7091 target 7092 graphics [ fill "#0000ff" ] ] 
	edge [ source 7091 target 7093 graphics [ fill "#000000" ] ] 
	edge [ source 7092 target 7096 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 7093 target 7085 graphics [ fill "#000000" ] ] 
	edge [ source 7086 target 7087 graphics [ fill "#0000ff" ] ] 
	edge [ source 7086 target 7088 graphics [ fill "#000000" ] ] 
	edge [ source 7087 target 7088 graphics [ fill "#0000ff" ] ] 
	edge [ source 7088 target 7085 graphics [ fill "#0000ff" ] ] 
	edge [ source 7085 target 7086 graphics [ fill "#000000" ] ] 
	edge [ source 7085 target 7094 graphics [ fill "#0000ff" ] ] 
	edge [ source 7094 target 7095 graphics [ fill "#0000ff" ] ] 
	edge [ source 7094 target 7096 graphics [ fill "#000000" ] ] 
	edge [ source 7095 target 7096 graphics [ fill "#0000ff" ] ] 
	edge [ source 7096 target 7090 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 7301 graphics [ fill "#d3d3d3" ] label "   97: L97:
   98: NOTE_INSN_BASIC_BLOCK 12
  100: flags:CCZ=cmp([r77:DI-0x8],0)
  101: pc={(flags:CCZ!=0)?L99:pc}
" ]

	node [ id 7302 graphics [ fill "#d3d3d3" ] label "   99: L99:
   79: NOTE_INSN_BASIC_BLOCK 11
   80: r110:DI=[r77:DI-0x8]
   81: r93:DI=[r110:DI+0x8]
   82: r94:DI=r93:DI
   83: dx:SI=0x8c5
   84: si:DI=`__FUNCTION__.25'
   85: di:DI=r94:DI
   86: ax:DI=call [`rhp_free'] argc:0
   87: r111:DI=[r77:DI-0x8]
   88: [r111:DI+0x8]=0
   89: r112:DI=[r77:DI-0x8]
   90: r95:DI=[r112:DI]
   91: r96:DI=[`rhp_sp_master_node_list_sorted']
   92: si:DI=r95:DI
   93: di:DI=r96:DI
   94: ax:DI=call [`rhp_sp_next'] argc:0
   95: r113:DI=ax:DI
   96: [r77:DI-0x8]=r113:DI
" ]

	node [ id 7303 graphics [ fill "#d3d3d3" ] label "   66: L66:
   67: NOTE_INSN_BASIC_BLOCK 9
   69: flags:CCZ=cmp([r77:DI-0x8],0)
   70: pc={(flags:CCZ!=0)?L68:pc}
" ]

	node [ id 7304 graphics [ fill "#d3d3d3" ] label "   68: L68:
   18: NOTE_INSN_BASIC_BLOCK 4
   19: r98:DI=[r77:DI-0x8]
   20: r83:DI=[r98:DI+0x8]
   21: [r77:DI-0x10]=r83:DI
   22: r99:DI=[r77:DI-0x10]
   23: r84:DI=[r99:DI+0x28]
   24: flags:CCZ=cmp(r84:DI,0)
   25: pc={(flags:CCZ==0)?L38:pc}
" ]

	node [ id 7305 graphics [ fill "#d3d3d3" ] label "   26: NOTE_INSN_BASIC_BLOCK 5
   27: r100:DI=[r77:DI-0x10]
   28: r85:DI=[r100:DI+0x28]
   29: dx:SI=0x8b3
   30: si:DI=`__FUNCTION__.25'
   31: di:DI=r85:DI
   32: ax:DI=call [`rhp_free'] argc:0
   33: r86:DI=ax:DI
   34: r101:DI=[r77:DI-0x10]
   35: [r101:DI+0x28]=r86:DI
   36: r102:DI=[r77:DI-0x10]
   37: [r102:DI+0x1c]=0
" ]

	node [ id 7306 graphics [ fill "#d3d3d3" ] label "   38: L38:
   39: NOTE_INSN_BASIC_BLOCK 6
   40: r103:DI=[r77:DI-0x10]
   41: r87:DI=[r103:DI+0x30]
   42: flags:CCZ=cmp(r87:DI,0)
   43: pc={(flags:CCZ==0)?L56:pc}
" ]

	node [ id 7307 graphics [ fill "#d3d3d3" ] label "   44: NOTE_INSN_BASIC_BLOCK 7
   45: r104:DI=[r77:DI-0x10]
   46: r88:DI=[r104:DI+0x30]
   47: dx:SI=0x8b9
   48: si:DI=`__FUNCTION__.25'
   49: di:DI=r88:DI
   50: ax:DI=call [`rhp_free'] argc:0
   51: r89:DI=ax:DI
   52: r105:DI=[r77:DI-0x10]
   53: [r105:DI+0x30]=r89:DI
   54: r106:DI=[r77:DI-0x10]
   55: [r106:DI+0x20]=0
" ]

	node [ id 7308 graphics [ fill "#d3d3d3" ] label "   56: L56:
   57: NOTE_INSN_BASIC_BLOCK 8
   58: r107:DI=[r77:DI-0x8]
   59: r90:DI=[r107:DI]
   60: r91:DI=[`rhp_sp_master_node_list']
   61: si:DI=r90:DI
   62: di:DI=r91:DI
   63: ax:DI=call [`rhp_sp_next'] argc:0
   64: r108:DI=ax:DI
   65: [r77:DI-0x8]=r108:DI
" ]



# function number 35
	node [ id 7309 graphics [ fill "#ffffff" ] label "rhp_empty_sp_master_node_list ()
ENTRY" ]

	node [ id 7310 graphics [ fill "#ffffff" ] label "rhp_empty_sp_master_node_list ()
EXIT" ]

	node [ id 7311 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x8]=0
    6: [r77:DI-0x10]=0
    7: si:DI=`__FUNCTION__.25'
    8: di:DI=`*.LC16'
    9: ax:QI=0
   10: call [`rhp_log'] argc:0
   11: r82:DI=[`rhp_sp_master_node_list']
   12: di:DI=r82:DI
   13: ax:DI=call [`rhp_sp_min'] argc:0
   14: r97:DI=ax:DI
   15: [r77:DI-0x8]=r97:DI
   16: pc=L66
" ]

	node [ id 7312 graphics [ fill "#d3d3d3" ] label "   71: NOTE_INSN_BASIC_BLOCK 10
   72: r92:DI=[`rhp_sp_master_node_list_sorted']
   73: di:DI=r92:DI
   74: ax:DI=call [`rhp_sp_min'] argc:0
   75: r109:DI=ax:DI
   76: [r77:DI-0x8]=r109:DI
   77: pc=L97
" ]

	node [ id 7313 graphics [ fill "#d3d3d3" ] label "  102: NOTE_INSN_BASIC_BLOCK 13
  107: 0
" ]

	edge [ source 7309 target 7311 graphics [ fill "#0000ff" ] ] 
	edge [ source 7311 target 7303 graphics [ fill "#000000" ] ] 
	edge [ source 7304 target 7305 graphics [ fill "#0000ff" ] ] 
	edge [ source 7304 target 7306 graphics [ fill "#000000" ] ] 
	edge [ source 7305 target 7306 graphics [ fill "#0000ff" ] ] 
	edge [ source 7306 target 7307 graphics [ fill "#0000ff" ] ] 
	edge [ source 7306 target 7308 graphics [ fill "#000000" ] ] 
	edge [ source 7307 target 7308 graphics [ fill "#0000ff" ] ] 
	edge [ source 7308 target 7303 graphics [ fill "#0000ff" ] ] 
	edge [ source 7303 target 7304 graphics [ fill "#000000" ] ] 
	edge [ source 7303 target 7312 graphics [ fill "#0000ff" ] ] 
	edge [ source 7312 target 7301 graphics [ fill "#000000" ] ] 
	edge [ source 7302 target 7301 graphics [ fill "#0000ff" ] ] 
	edge [ source 7301 target 7302 graphics [ fill "#000000" ] ] 
	edge [ source 7301 target 7313 graphics [ fill "#0000ff" ] ] 
	edge [ source 7313 target 7310 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 36
	node [ id 7522 graphics [ fill "#ffffff" ] label "rhp_empty_sp_master_edge_list ()
ENTRY" ]

	node [ id 7523 graphics [ fill "#ffffff" ] label "rhp_empty_sp_master_edge_list ()
EXIT" ]

	node [ id 7524 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: si:DI=`__FUNCTION__.24'
    6: di:DI=`*.LC16'
    7: ax:QI=0
    8: call [`rhp_log'] argc:0
   13: 0
" ]

	edge [ source 7522 target 7524 graphics [ fill "#0000ff" ] ] 
	edge [ source 7524 target 7523 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 7573 graphics [ fill "#d3d3d3" ] label "   58: L58:
   59: NOTE_INSN_BASIC_BLOCK 7
   61: flags:CCZ=cmp([r77:DI-0x8],0)
   62: pc={(flags:CCZ!=0)?L60:pc}
" ]

	node [ id 7574 graphics [ fill "#d3d3d3" ] label "   60: L60:
   23: NOTE_INSN_BASIC_BLOCK 4
   24: r93:DI=[r77:DI-0x8]
   25: r85:DI=[r93:DI+0x8]
   26: [r77:DI-0x10]=r85:DI
   27: r94:DI=[r77:DI-0x10]
   28: r86:DI=[r94:DI+0x8]
   29: dx:DI=r86:DI
   30: si:DI=`__FUNCTION__.23'
   31: di:DI=`*.LC68'
   32: ax:QI=0
   33: call [`rhp_log'] argc:0
   34: r95:DI=[r77:DI-0x10]
   35: r87:DI=[r95:DI+0x8]
   36: flags:CCZ=cmp(r87:DI,0)
   37: pc={(flags:CCZ==0)?L48:pc}
" ]

	node [ id 7575 graphics [ fill "#d3d3d3" ] label "   38: NOTE_INSN_BASIC_BLOCK 5
   39: r96:DI=[r77:DI-0x10]
   40: r88:DI=[r96:DI+0x8]
   41: dx:SI=0x8e9
   42: si:DI=`__FUNCTION__.23'
   43: di:DI=r88:DI
   44: ax:DI=call [`rhp_free'] argc:0
   45: r89:DI=ax:DI
   46: r97:DI=[r77:DI-0x10]
   47: [r97:DI+0x8]=r89:DI
" ]

	node [ id 7576 graphics [ fill "#d3d3d3" ] label "   48: L48:
   49: NOTE_INSN_BASIC_BLOCK 6
   50: r98:DI=[r77:DI-0x8]
   51: r90:DI=[r98:DI]
   52: r91:DI=[`rhp_sp_between_layers']
   53: si:DI=r90:DI
   54: di:DI=r91:DI
   55: ax:DI=call [`rhp_sp_next'] argc:0
   56: r99:DI=ax:DI
   57: [r77:DI-0x8]=r99:DI
" ]



# function number 37
	node [ id 7577 graphics [ fill "#ffffff" ] label "rhp_empty_sp_between_layers ()
ENTRY" ]

	node [ id 7578 graphics [ fill "#ffffff" ] label "rhp_empty_sp_between_layers ()
EXIT" ]

	node [ id 7579 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x8]=0
    6: [r77:DI-0x10]=0
    7: r82:DI=[`rhp_sp_between_layers']
    8: di:DI=r82:DI
    9: ax:SI=call [`rhp_sp_has_data'] argc:0
   10: r83:SI=ax:SI
   11: dx:SI=r83:SI
   12: si:DI=`__FUNCTION__.23'
   13: di:DI=`*.LC67'
   14: ax:QI=0
   15: call [`rhp_log'] argc:0
   16: r84:DI=[`rhp_sp_between_layers']
   17: di:DI=r84:DI
   18: ax:DI=call [`rhp_sp_min'] argc:0
   19: r92:DI=ax:DI
   20: [r77:DI-0x8]=r92:DI
   21: pc=L58
" ]

	node [ id 7580 graphics [ fill "#d3d3d3" ] label "   63: NOTE_INSN_BASIC_BLOCK 8
   68: 0
" ]

	edge [ source 7577 target 7579 graphics [ fill "#0000ff" ] ] 
	edge [ source 7579 target 7573 graphics [ fill "#000000" ] ] 
	edge [ source 7574 target 7575 graphics [ fill "#0000ff" ] ] 
	edge [ source 7574 target 7576 graphics [ fill "#000000" ] ] 
	edge [ source 7575 target 7576 graphics [ fill "#0000ff" ] ] 
	edge [ source 7576 target 7573 graphics [ fill "#0000ff" ] ] 
	edge [ source 7573 target 7574 graphics [ fill "#000000" ] ] 
	edge [ source 7573 target 7580 graphics [ fill "#0000ff" ] ] 
	edge [ source 7580 target 7578 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 7709 graphics [ fill "#d3d3d3" ] label "  128: L128:
  129: NOTE_INSN_BASIC_BLOCK 17
  130: r125:DI=[r77:DI-0x18]
  131: r102:SI=[r125:DI]
  133: flags:CCGC=cmp([r77:DI-0x8],r102:SI)
  134: pc={(flags:CCGC&lt;0)?L132:pc}
" ]

	node [ id 7710 graphics [ fill "#d3d3d3" ] label "  132: L132:
   82: NOTE_INSN_BASIC_BLOCK 12
   83: r114:DI=[r77:DI-0x18]
   84: r92:DI=[r114:DI+0x8]
   85: r115:SI=[r77:DI-0x8]
   86: r93:DI=sign_extend(r115:SI)
   87: {r94:DI=r93:DI&lt;&lt;0x3;clobber flags:CC;}
   88: {r95:DI=r92:DI+r94:DI;clobber flags:CC;}
   89: r116:DI=[r95:DI]
   90: [r77:DI-0x20]=r116:DI
   91: r117:DI=[r77:DI-0x20]
   92: r96:SI=[r117:DI+0x1c]
   93: flags:CCZ=cmp(r96:SI,0)
   94: pc={(flags:CCZ==0)?L107:pc}
" ]

	node [ id 7711 graphics [ fill "#d3d3d3" ] label "   95: NOTE_INSN_BASIC_BLOCK 13
   96: r118:DI=[r77:DI-0x20]
   97: r97:DI=[r118:DI+0x28]
   98: dx:SI=0x923
   99: si:DI=`__FUNCTION__.22'
  100: di:DI=r97:DI
  101: ax:DI=call [`rhp_free'] argc:0
  102: r98:DI=ax:DI
  103: r119:DI=[r77:DI-0x20]
  104: [r119:DI+0x28]=r98:DI
  105: r120:DI=[r77:DI-0x20]
  106: [r120:DI+0x1c]=0
" ]

	node [ id 7712 graphics [ fill "#d3d3d3" ] label "  107: L107:
  108: NOTE_INSN_BASIC_BLOCK 14
  109: r121:DI=[r77:DI-0x20]
  110: r99:SI=[r121:DI+0x20]
  111: flags:CCZ=cmp(r99:SI,0)
  112: pc={(flags:CCZ==0)?L125:pc}
" ]

	node [ id 7713 graphics [ fill "#d3d3d3" ] label "  113: NOTE_INSN_BASIC_BLOCK 15
  114: r122:DI=[r77:DI-0x20]
  115: r100:DI=[r122:DI+0x30]
  116: dx:SI=0x929
  117: si:DI=`__FUNCTION__.22'
  118: di:DI=r100:DI
  119: ax:DI=call [`rhp_free'] argc:0
  120: r101:DI=ax:DI
  121: r123:DI=[r77:DI-0x20]
  122: [r123:DI+0x30]=r101:DI
  123: r124:DI=[r77:DI-0x20]
  124: [r124:DI+0x20]=0
" ]

	node [ id 7714 graphics [ fill "#d3d3d3" ] label "  125: L125:
  126: NOTE_INSN_BASIC_BLOCK 16
  127: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
" ]

	node [ id 7715 graphics [ fill "#d3d3d3" ] label "  150: L150:
  151: NOTE_INSN_BASIC_BLOCK 20
  152: r105:SI=[`rhp_nlevels']
  154: flags:CCGC=cmp([r77:DI-0x4],r105:SI)
  155: pc={(flags:CCGC&lt;0)?L153:pc}
" ]

	node [ id 7716 graphics [ fill "#d3d3d3" ] label "  153: L153:
   29: NOTE_INSN_BASIC_BLOCK 6
   30: r106:SI=[r77:DI-0x4]
   31: r85:DI=sign_extend(r106:SI)
   32: r86:DI=[`rhp_sp_layers']
   33: si:DI=r85:DI
   34: di:DI=r86:DI
   35: ax:DI=call [`rhp_sp_lookup'] argc:0
   36: r107:DI=ax:DI
   37: [r77:DI-0x10]=r107:DI
   38: flags:CCZ=cmp([r77:DI-0x10],0)
   39: pc={(flags:CCZ!=0)?L57:pc}
" ]

	node [ id 7717 graphics [ fill "#d3d3d3" ] label "   40: NOTE_INSN_BASIC_BLOCK 7
   41: r87:SI=[`rhp_nlevels']
   44: flags:CCGC=cmp(r87:SI,0x1)
   45: pc={(flags:CCGC&lt;=0)?L147:pc}
" ]

	node [ id 7718 graphics [ fill "#d3d3d3" ] label "   57: L57:
   58: NOTE_INSN_BASIC_BLOCK 10
   59: r109:DI=[r77:DI-0x10]
   60: r88:DI=[r109:DI+0x8]
   61: [r77:DI-0x18]=r88:DI
   62: r110:DI=[r77:DI-0x18]
   63: r89:DI=[r110:DI+0x8]
   64: r111:DI=[r77:DI-0x18]
   65: r90:SI=[r111:DI]
   66: r112:SI=[r77:DI-0x4]
   67: r8:DI=r89:DI
   68: cx:SI=r90:SI
   69: dx:SI=r112:SI
   70: si:DI=`__FUNCTION__.22'
   71: di:DI=`*.LC70'
   72: ax:QI=0
   73: call [`rhp_log'] argc:0
   74: r113:DI=[r77:DI-0x18]
   75: r91:DI=[r113:DI+0x8]
   76: flags:CCZ=cmp(r91:DI,0)
   77: pc={(flags:CCZ==0)?L147:pc}
" ]

	node [ id 7719 graphics [ fill "#d3d3d3" ] label "   46: NOTE_INSN_BASIC_BLOCK 8
   47: r108:SI=[r77:DI-0x4]
   48: dx:SI=r108:SI
   49: si:DI=`__FUNCTION__.22'
   50: di:DI=`*.LC52'
   51: ax:QI=0
   52: call [`rhp_log'] argc:0
   55: pc=L147
" ]

	node [ id 7720 graphics [ fill "#d3d3d3" ] label "  147: L147:
  148: NOTE_INSN_BASIC_BLOCK 19
  149: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]

	node [ id 7721 graphics [ fill "#d3d3d3" ] label "   78: NOTE_INSN_BASIC_BLOCK 11
   79: [r77:DI-0x8]=0
   80: pc=L128
" ]

	node [ id 7722 graphics [ fill "#d3d3d3" ] label "  135: NOTE_INSN_BASIC_BLOCK 18
  136: r126:DI=[r77:DI-0x18]
  137: r103:DI=[r126:DI+0x8]
  138: dx:SI=0x92e
  139: si:DI=`__FUNCTION__.22'
  140: di:DI=r103:DI
  141: ax:DI=call [`rhp_free'] argc:0
  142: r104:DI=ax:DI
  143: r127:DI=[r77:DI-0x18]
  144: [r127:DI+0x8]=r104:DI
  145: r128:DI=[r77:DI-0x18]
  146: [r128:DI]=0
" ]



# function number 38
	node [ id 7723 graphics [ fill "#ffffff" ] label "rhp_empty_sp_layers ()
ENTRY" ]

	node [ id 7724 graphics [ fill "#ffffff" ] label "rhp_empty_sp_layers ()
EXIT" ]

	node [ id 7725 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x10]=0
    6: [r77:DI-0x18]=0
    7: [r77:DI-0x20]=0
    8: [r77:DI-0x4]=0
    9: [r77:DI-0x8]=0
   10: r82:DI=[`rhp_sp_layers']
   11: r83:SI=[`rhp_nlevels']
   12: cx:DI=r82:DI
   13: dx:SI=r83:SI
   14: si:DI=`__FUNCTION__.22'
   15: di:DI=`*.LC69'
   16: ax:QI=0
   17: call [`rhp_log'] argc:0
   18: r84:DI=[`rhp_sp_layers']
   19: flags:CCZ=cmp(r84:DI,0)
   20: pc={(flags:CCZ!=0)?L24:pc}
" ]

	node [ id 7726 graphics [ fill "#d3d3d3" ] label "   21: NOTE_INSN_BASIC_BLOCK 4
   22: pc=L159
" ]

	node [ id 7727 graphics [ fill "#d3d3d3" ] label "   24: L24:
   25: NOTE_INSN_BASIC_BLOCK 5
   26: [r77:DI-0x4]=0
   27: pc=L150
" ]

	node [ id 7728 graphics [ fill "#d3d3d3" ] label "  156: NOTE_INSN_BASIC_BLOCK 21
" ]

	node [ id 7729 graphics [ fill "#d3d3d3" ] label "  159: L159:
  160: NOTE_INSN_BASIC_BLOCK 23
" ]

	edge [ source 7723 target 7725 graphics [ fill "#0000ff" ] ] 
	edge [ source 7725 target 7726 graphics [ fill "#0000ff" ] ] 
	edge [ source 7725 target 7727 graphics [ fill "#000000" ] ] 
	edge [ source 7726 target 7729 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 7727 target 7715 graphics [ fill "#000000" ] ] 
	edge [ source 7716 target 7717 graphics [ fill "#0000ff" ] ] 
	edge [ source 7716 target 7718 graphics [ fill "#000000" ] ] 
	edge [ source 7717 target 7719 graphics [ fill "#0000ff" ] ] 
	edge [ source 7717 target 7720 graphics [ fill "#000000" ] ] 
	edge [ source 7719 target 7720 graphics [ fill "#000000" ] ] 
	edge [ source 7718 target 7721 graphics [ fill "#0000ff" ] ] 
	edge [ source 7718 target 7720 graphics [ fill "#000000" ] ] 
	edge [ source 7721 target 7709 graphics [ fill "#000000" ] ] 
	edge [ source 7710 target 7711 graphics [ fill "#0000ff" ] ] 
	edge [ source 7710 target 7712 graphics [ fill "#000000" ] ] 
	edge [ source 7711 target 7712 graphics [ fill "#0000ff" ] ] 
	edge [ source 7712 target 7713 graphics [ fill "#0000ff" ] ] 
	edge [ source 7712 target 7714 graphics [ fill "#000000" ] ] 
	edge [ source 7713 target 7714 graphics [ fill "#0000ff" ] ] 
	edge [ source 7714 target 7709 graphics [ fill "#0000ff" ] ] 
	edge [ source 7709 target 7710 graphics [ fill "#000000" ] ] 
	edge [ source 7709 target 7722 graphics [ fill "#0000ff" ] ] 
	edge [ source 7722 target 7720 graphics [ fill "#0000ff" ] ] 
	edge [ source 7720 target 7715 graphics [ fill "#0000ff" ] ] 
	edge [ source 7715 target 7716 graphics [ fill "#000000" ] ] 
	edge [ source 7715 target 7728 graphics [ fill "#0000ff" ] ] 
	edge [ source 7728 target 7729 graphics [ fill "#0000ff" ] ] 
	edge [ source 7729 target 7724 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 8072 graphics [ fill "#d3d3d3" ] label "  372: L372:
  373: NOTE_INSN_BASIC_BLOCK 35
  374: r210:DI=[r77:DI-0x28]
  375: r147:SI=[r210:DI]
  377: flags:CCGC=cmp([r77:DI-0x8],r147:SI)
  378: pc={(flags:CCGC&lt;0)?L376:pc}
" ]

	node [ id 8073 graphics [ fill "#d3d3d3" ] label "  376: L376:
  358: NOTE_INSN_BASIC_BLOCK 34
  359: r208:DI=[r77:DI-0x28]
  360: r141:DI=[r208:DI+0x8]
  361: r209:SI=[r77:DI-0x8]
  362: r142:DI=sign_extend(r209:SI)
  363: {r143:DI=r142:DI&lt;&lt;0x3;clobber flags:CC;}
  364: {r144:DI=r141:DI+r143:DI;clobber flags:CC;}
  365: r145:DI=[r144:DI]
  366: r146:SI=[r145:DI+0x4]
  367: si:SI=r146:SI
  368: di:DI=`*.LC82'
  369: ax:QI=0
  370: call [`rhp_log'] argc:0
  371: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
" ]

	node [ id 8074 graphics [ fill "#d3d3d3" ] label "  391: L391:
  392: NOTE_INSN_BASIC_BLOCK 38
  393: r149:SI=[`rhp_nlevels']
  395: flags:CCGC=cmp([r77:DI-0x14],r149:SI)
  396: pc={(flags:CCGC&lt;0)?L394:pc}
" ]

	node [ id 8075 graphics [ fill "#d3d3d3" ] label "  394: L394:
  310: NOTE_INSN_BASIC_BLOCK 30
  311: r200:SI=[r77:DI-0x14]
  312: r135:DI=sign_extend(r200:SI)
  313: r136:DI=[`rhp_sp_layers']
  314: si:DI=r135:DI
  315: di:DI=r136:DI
  316: ax:DI=call [`rhp_sp_lookup'] argc:0
  317: r201:DI=ax:DI
  318: [r77:DI-0x30]=r201:DI
  319: r202:DI=[r77:DI-0x30]
  320: r137:DI=[r202:DI+0x8]
  321: [r77:DI-0x28]=r137:DI
  322: r203:DI=[r77:DI-0x28]
  323: r138:SI=[r203:DI]
  324: flags:CCZ=cmp(r138:SI,0)
  325: pc={(flags:CCZ!=0)?L335:pc}
" ]

	node [ id 8076 graphics [ fill "#d3d3d3" ] label "  326: NOTE_INSN_BASIC_BLOCK 31
  327: r204:SI=[r77:DI-0x14]
  328: dx:SI=r204:SI
  329: si:DI=`__FUNCTION__.21'
  330: di:DI=`*.LC78'
  331: ax:QI=0
  332: call [`rhp_log'] argc:0
  333: pc=L385
" ]

	node [ id 8077 graphics [ fill "#d3d3d3" ] label "  335: L335:
  336: NOTE_INSN_BASIC_BLOCK 32
  337: r205:DI=[r77:DI-0x28]
  338: r139:SI=[r205:DI]
  339: r206:SI=[r77:DI-0x14]
  340: cx:SI=r139:SI
  341: dx:SI=r206:SI
  342: si:DI=`__FUNCTION__.21'
  343: di:DI=`*.LC79'
  344: ax:QI=0
  345: call [`rhp_log'] argc:0
  346: r207:DI=[r77:DI-0x28]
  347: r140:DI=[r207:DI+0x8]
  348: flags:CCZ=cmp(r140:DI,0)
  349: pc={(flags:CCZ==0)?L379:pc}
" ]

	node [ id 8078 graphics [ fill "#d3d3d3" ] label "  385: L385:
  386: NOTE_INSN_BASIC_BLOCK 37
  387: r211:DI=[r77:DI-0x28]
  388: r148:SI=[r211:DI]
  389: {[r77:DI-0x4]=[r77:DI-0x4]+r148:SI;clobber flags:CC;}
  390: {[r77:DI-0x14]=[r77:DI-0x14]+0x1;clobber flags:CC;}
" ]

	node [ id 8079 graphics [ fill "#d3d3d3" ] label "  350: NOTE_INSN_BASIC_BLOCK 33
  351: si:DI=`*.LC80'
  352: di:DI=`*.LC81'
  353: ax:QI=0
  354: call [`rhp_log'] argc:0
  355: [r77:DI-0x8]=0
  356: pc=L372
" ]

	node [ id 8080 graphics [ fill "#d3d3d3" ] label "  379: L379:
  380: NOTE_INSN_BASIC_BLOCK 36
  381: si:DI=`*.LC83'
  382: di:DI=`*.LC81'
  383: ax:QI=0
  384: call [`rhp_log'] argc:0
" ]

	node [ id 8081 graphics [ fill "#d3d3d3" ] label "  300: L300:
  301: NOTE_INSN_BASIC_BLOCK 28
  303: flags:CCZ=cmp([r77:DI-0x10],0)
  304: pc={(flags:CCZ!=0)?L302:pc}
" ]

	node [ id 8082 graphics [ fill "#d3d3d3" ] label "  302: L302:
  226: NOTE_INSN_BASIC_BLOCK 22
  227: r183:DI=[r77:DI-0x10]
  228: r119:DI=[r183:DI+0x8]
  229: [r77:DI-0x38]=r119:DI
  230: r184:DI=[r77:DI-0x38]
  231: r185:SI=[r184:DI+0x8]
  232: [r77:DI-0x14]=r185:SI
  233: r186:SI=[r77:DI-0x14]
  234: r120:DI=sign_extend(r186:SI)
  235: r121:DI=[`rhp_sp_layers']
  236: si:DI=r120:DI
  237: di:DI=r121:DI
  238: ax:DI=call [`rhp_sp_lookup'] argc:0
  239: r187:DI=ax:DI
  240: [r77:DI-0x30]=r187:DI
  241: flags:CCZ=cmp([r77:DI-0x30],0)
  242: pc={(flags:CCZ!=0)?L252:pc}
" ]

	node [ id 8083 graphics [ fill "#d3d3d3" ] label "  252: L252:
  253: NOTE_INSN_BASIC_BLOCK 24
  254: r189:DI=[r77:DI-0x30]
  255: r122:DI=[r189:DI+0x8]
  256: [r77:DI-0x28]=r122:DI
  257: r190:DI=[r77:DI-0x28]
  258: r123:DI=[r190:DI+0x8]
  259: flags:CCZ=cmp(r123:DI,0)
  260: pc={(flags:CCZ==0)?L278:pc}
" ]

	node [ id 8084 graphics [ fill "#d3d3d3" ] label "  261: NOTE_INSN_BASIC_BLOCK 25
  262: r191:DI=[r77:DI-0x28]
  263: r124:DI=[r191:DI+0x8]
  264: r192:DI=[r77:DI-0x28]
  265: r125:SI=[r192:DI]
  266: r126:DI=sign_extend(r125:SI)
  267: {r127:DI=r126:DI&lt;&lt;0x3;clobber flags:CC;}
  268: {r128:DI=r124:DI+r127:DI;clobber flags:CC;}
  269: r193:DI=[r77:DI-0x38]
  270: [r128:DI]=r193:DI
  271: r194:DI=[r77:DI-0x28]
  272: r129:SI=[r194:DI]
  273: {r130:SI=r129:SI+0x1;clobber flags:CC;}
  274: r195:DI=[r77:DI-0x28]
  275: [r195:DI]=r130:SI
  276: pc=L290
" ]

	node [ id 8085 graphics [ fill "#d3d3d3" ] label "  278: L278:
  279: NOTE_INSN_BASIC_BLOCK 26
  280: r196:DI=[r77:DI-0x38]
  281: r131:SI=[r196:DI+0x8]
  282: r197:DI=[r77:DI-0x38]
  283: r132:SI=[r197:DI+0x4]
  284: cx:SI=r131:SI
  285: dx:SI=r132:SI
  286: si:DI=`__FUNCTION__.21'
  287: di:DI=`*.LC77'
  288: ax:QI=0
  289: call [`rhp_log'] argc:0
" ]

	node [ id 8086 graphics [ fill "#d3d3d3" ] label "  290: L290:
  291: NOTE_INSN_BASIC_BLOCK 27
  292: r198:DI=[r77:DI-0x10]
  293: r133:DI=[r198:DI]
  294: r134:DI=[`rhp_sp_master_node_list']
  295: si:DI=r133:DI
  296: di:DI=r134:DI
  297: ax:DI=call [`rhp_sp_next'] argc:0
  298: r199:DI=ax:DI
  299: [r77:DI-0x10]=r199:DI
" ]

	node [ id 8087 graphics [ fill "#d3d3d3" ] label "  212: L212:
  213: NOTE_INSN_BASIC_BLOCK 20
  214: r117:SI=[`rhp_nlevels']
  216: flags:CCGC=cmp([r77:DI-0x4],r117:SI)
  217: pc={(flags:CCGC&lt;0)?L215:pc}
" ]

	node [ id 8088 graphics [ fill "#d3d3d3" ] label "  215: L215:
  155: NOTE_INSN_BASIC_BLOCK 16
  156: r171:SI=[r77:DI-0x4]
  157: r105:DI=sign_extend(r171:SI)
  158: r106:DI=[`rhp_sp_layers']
  159: si:DI=r105:DI
  160: di:DI=r106:DI
  161: ax:DI=call [`rhp_sp_lookup'] argc:0
  162: r172:DI=ax:DI
  163: [r77:DI-0x30]=r172:DI
  164: r173:DI=[r77:DI-0x30]
  165: r107:DI=[r173:DI+0x8]
  166: [r77:DI-0x28]=r107:DI
  167: r174:DI=[r77:DI-0x28]
  168: r108:SI=[r174:DI]
  169: flags:CCZ=cmp(r108:SI,0)
  170: pc={(flags:CCZ==0)?L199:pc}
" ]

	node [ id 8089 graphics [ fill "#d3d3d3" ] label "  171: NOTE_INSN_BASIC_BLOCK 17
  172: r175:DI=[r77:DI-0x28]
  173: r109:SI=[r175:DI]
  174: r176:SI=[r77:DI-0x4]
  175: cx:SI=r176:SI
  176: dx:SI=r109:SI
  177: si:DI=`__FUNCTION__.21'
  178: di:DI=`*.LC74'
  179: ax:QI=0
  180: call [`rhp_log'] argc:0
  181: r177:DI=[r77:DI-0x28]
  182: r110:SI=[r177:DI]
  183: r111:DI=sign_extend(r110:SI)
  184: {r112:DI=r111:DI&lt;&lt;0x3;clobber flags:CC;}
  185: dx:SI=0x98a
  186: si:DI=`__FUNCTION__.21'
  187: di:DI=r112:DI
  188: ax:DI=call [`rhp_malloc'] argc:0
  189: r113:DI=ax:DI
  190: r178:DI=[r77:DI-0x28]
  191: [r178:DI+0x8]=r113:DI
  192: r179:DI=[r77:DI-0x28]
  193: r114:SI=[r179:DI]
  194: r115:DI=sign_extend(r114:SI)
  195: {r116:DI=r115:DI&lt;&lt;0x3;clobber flags:CC;}
  196: {[r77:DI-0x20]=[r77:DI-0x20]+r116:DI;clobber flags:CC;}
  197: pc=L207
" ]

	node [ id 8090 graphics [ fill "#d3d3d3" ] label "  199: L199:
  200: NOTE_INSN_BASIC_BLOCK 18
  201: r180:SI=[r77:DI-0x4]
  202: dx:SI=r180:SI
  203: si:DI=`__FUNCTION__.21'
  204: di:DI=`*.LC75'
  205: ax:QI=0
  206: call [`rhp_log'] argc:0
" ]

	node [ id 8091 graphics [ fill "#d3d3d3" ] label "  207: L207:
  208: NOTE_INSN_BASIC_BLOCK 19
  209: r181:DI=[r77:DI-0x28]
  210: [r181:DI]=0
  211: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]

	node [ id 8092 graphics [ fill "#d3d3d3" ] label "  146: L146:
  147: NOTE_INSN_BASIC_BLOCK 14
  149: flags:CCZ=cmp([r77:DI-0x10],0)
  150: pc={(flags:CCZ!=0)?L148:pc}
" ]

	node [ id 8093 graphics [ fill "#d3d3d3" ] label "  148: L148:
  101: NOTE_INSN_BASIC_BLOCK 13
  102: r159:DI=[r77:DI-0x10]
  103: r93:DI=[r159:DI+0x8]
  104: [r77:DI-0x38]=r93:DI
  105: r160:DI=[r77:DI-0x38]
  106: r161:SI=[r160:DI+0x8]
  107: [r77:DI-0x14]=r161:SI
  108: r162:SI=[r77:DI-0x14]
  109: r94:DI=sign_extend(r162:SI)
  110: r95:DI=[`rhp_sp_layers']
  111: si:DI=r94:DI
  112: di:DI=r95:DI
  113: ax:DI=call [`rhp_sp_lookup'] argc:0
  114: r163:DI=ax:DI
  115: [r77:DI-0x30]=r163:DI
  116: r164:DI=[r77:DI-0x30]
  117: r96:DI=[r164:DI+0x8]
  118: [r77:DI-0x28]=r96:DI
  119: r165:DI=[r77:DI-0x28]
  120: r97:SI=[r165:DI]
  121: {r98:SI=r97:SI+0x1;clobber flags:CC;}
  122: r166:DI=[r77:DI-0x28]
  123: [r166:DI]=r98:SI
  124: r99:SI=[`rhp_number_of_nodes']
  125: {r100:SI=r99:SI+0x1;clobber flags:CC;}
  126: [`rhp_number_of_nodes']=r100:SI
  127: r101:SI=[`rhp_number_of_nodes']
  128: r167:DI=[r77:DI-0x28]
  129: r102:SI=[r167:DI]
  130: r168:SI=[r77:DI-0x4]
  131: r8:SI=r101:SI
  132: cx:SI=r168:SI
  133: dx:SI=r102:SI
  134: si:DI=`__FUNCTION__.21'
  135: di:DI=`*.LC73'
  136: ax:QI=0
  137: call [`rhp_log'] argc:0
  138: r169:DI=[r77:DI-0x10]
  139: r103:DI=[r169:DI]
  140: r104:DI=[`rhp_sp_master_node_list']
  141: si:DI=r103:DI
  142: di:DI=r104:DI
  143: ax:DI=call [`rhp_sp_next'] argc:0
  144: r170:DI=ax:DI
  145: [r77:DI-0x10]=r170:DI
" ]

	node [ id 8094 graphics [ fill "#d3d3d3" ] label "   87: L87:
   88: NOTE_INSN_BASIC_BLOCK 11
   89: r91:SI=[`rhp_nlevels']
   91: flags:CCGC=cmp([r77:DI-0x4],r91:SI)
   92: pc={(flags:CCGC&lt;0)?L90:pc}
" ]

	node [ id 8095 graphics [ fill "#d3d3d3" ] label "   90: L90:
   60: NOTE_INSN_BASIC_BLOCK 10
   61: dx:SI=0x95e
   62: si:DI=`__FUNCTION__.21'
   63: di:DI=0x10
   64: ax:DI=call [`rhp_malloc'] argc:0
   65: r153:DI=ax:DI
   66: [r77:DI-0x28]=r153:DI
   67: {[r77:DI-0x20]=[r77:DI-0x20]+0x10;clobber flags:CC;}
   68: r154:DI=[r77:DI-0x28]
   69: [r154:DI]=0
   70: r155:DI=[r77:DI-0x28]
   71: [r155:DI+0x8]=0
   72: r156:SI=[r77:DI-0x4]
   73: dx:SI=r156:SI
   74: si:DI=`__FUNCTION__.21'
   75: di:DI=`*.LC72'
   76: ax:QI=0
   77: call [`rhp_log'] argc:0
   78: r88:DI=[r77:DI-0x28]
   79: r157:SI=[r77:DI-0x4]
   80: r89:DI=sign_extend(r157:SI)
   81: r90:DI=[`rhp_sp_layers']
   82: dx:DI=r88:DI
   83: si:DI=r89:DI
   84: di:DI=r90:DI
   85: call [`rhp_sp_insert'] argc:0
   86: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]



# function number 39
	node [ id 8096 graphics [ fill "#ffffff" ] label "rhp_allocatelayers ()
ENTRY" ]

	node [ id 8097 graphics [ fill "#ffffff" ] label "rhp_allocatelayers ()
EXIT" ]

	node [ id 8098 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x4]=0
    6: [r77:DI-0x8]=0
    7: [r77:DI-0x28]=0
    8: [r77:DI-0x30]=0
    9: [r77:DI-0x10]=0
   10: [r77:DI-0x38]=0
   11: [r77:DI-0x14]=0
   12: [r77:DI-0x20]=0
   13: [`rhp_number_of_nodes']=0
   14: r82:DI=[`rhp_sp_master_node_list']
   15: di:DI=r82:DI
   16: ax:SI=call [`rhp_sp_has_data'] argc:0
   17: r83:SI=ax:SI
   18: flags:CCZ=cmp(r83:SI,0)
   19: pc={(flags:CCZ!=0)?L27:pc}
" ]

	node [ id 8099 graphics [ fill "#d3d3d3" ] label "   20: NOTE_INSN_BASIC_BLOCK 4
   21: si:DI=`__FUNCTION__.21'
   22: di:DI=`*.LC43'
   23: ax:QI=0
   24: call [`rhp_log'] argc:0
   25: pc=L418
" ]

	node [ id 8100 graphics [ fill "#d3d3d3" ] label "   27: L27:
   28: NOTE_INSN_BASIC_BLOCK 5
   29: r84:SI=[`rhp_nlevels']
   30: flags:CCZ=cmp(r84:SI,0)
   31: pc={(flags:CCZ!=0)?L39:pc}
" ]

	node [ id 8101 graphics [ fill "#d3d3d3" ] label "   32: NOTE_INSN_BASIC_BLOCK 6
   33: si:DI=`__FUNCTION__.21'
   34: di:DI=`*.LC51'
   35: ax:QI=0
   36: call [`rhp_log'] argc:0
   37: pc=L418
" ]

	node [ id 8102 graphics [ fill "#d3d3d3" ] label "   39: L39:
   40: NOTE_INSN_BASIC_BLOCK 7
   41: r85:DI=[`rhp_sp_layers']
   42: flags:CCZ=cmp(r85:DI,0)
   43: pc={(flags:CCZ==0)?L51:pc}
" ]

	node [ id 8103 graphics [ fill "#d3d3d3" ] label "   44: NOTE_INSN_BASIC_BLOCK 8
   45: r86:DI=[`rhp_sp_layers']
   46: dx:DI=r86:DI
   47: si:DI=`__FUNCTION__.21'
   48: di:DI=`*.LC71'
   49: ax:QI=0
   50: call [`rhp_log'] argc:0
" ]

	node [ id 8104 graphics [ fill "#d3d3d3" ] label "   51: L51:
   52: NOTE_INSN_BASIC_BLOCK 9
   53: di:SI=0x1
   54: ax:DI=call [`rhp_sp_new'] argc:0
   55: r87:DI=ax:DI
   56: [`rhp_sp_layers']=r87:DI
   57: [r77:DI-0x4]=0
   58: pc=L87
" ]

	node [ id 8105 graphics [ fill "#d3d3d3" ] label "   93: NOTE_INSN_BASIC_BLOCK 12
   94: r92:DI=[`rhp_sp_master_node_list']
   95: di:DI=r92:DI
   96: ax:DI=call [`rhp_sp_min'] argc:0
   97: r158:DI=ax:DI
   98: [r77:DI-0x10]=r158:DI
   99: pc=L146
" ]

	node [ id 8106 graphics [ fill "#d3d3d3" ] label "  151: NOTE_INSN_BASIC_BLOCK 15
  152: [r77:DI-0x4]=0
  153: pc=L212
" ]

	node [ id 8107 graphics [ fill "#d3d3d3" ] label "  218: NOTE_INSN_BASIC_BLOCK 21
  219: r118:DI=[`rhp_sp_master_node_list']
  220: di:DI=r118:DI
  221: ax:DI=call [`rhp_sp_min'] argc:0
  222: r182:DI=ax:DI
  223: [r77:DI-0x10]=r182:DI
  224: pc=L300
" ]

	node [ id 8108 graphics [ fill "#d3d3d3" ] label "  243: NOTE_INSN_BASIC_BLOCK 23
  244: r188:SI=[r77:DI-0x14]
  245: dx:SI=r188:SI
  246: si:DI=`__FUNCTION__.21'
  247: di:DI=`*.LC76'
  248: ax:QI=0
  249: call [`rhp_log'] argc:0
  250: pc=L418
" ]

	node [ id 8109 graphics [ fill "#d3d3d3" ] label "  305: NOTE_INSN_BASIC_BLOCK 29
  306: [r77:DI-0x4]=0
  307: [r77:DI-0x14]=0
  308: pc=L391
" ]

	node [ id 8110 graphics [ fill "#d3d3d3" ] label "  397: NOTE_INSN_BASIC_BLOCK 39
  398: r150:SI=[`rhp_number_of_nodes']
  399: r151:SI=[`rhp_maxlevel']
  400: r152:SI=[`rhp_nlevels']
  401: r212:SI=[r77:DI-0x4]
  402: r9:SI=r150:SI
  403: r8:SI=r212:SI
  404: cx:SI=r151:SI
  405: dx:SI=r152:SI
  406: si:DI=`__FUNCTION__.21'
  407: di:DI=`*.LC84'
  408: ax:QI=0
  409: call [`rhp_log'] argc:0
  410: r213:DI=[r77:DI-0x20]
  411: dx:DI=r213:DI
  412: si:DI=`__FUNCTION__.21'
  413: di:DI=`*.LC85'
  414: ax:QI=0
  415: call [`rhp_log'] argc:0
" ]

	node [ id 8111 graphics [ fill "#d3d3d3" ] label "  418: L418:
  419: NOTE_INSN_BASIC_BLOCK 41
" ]

	edge [ source 8096 target 8098 graphics [ fill "#0000ff" ] ] 
	edge [ source 8098 target 8099 graphics [ fill "#0000ff" ] ] 
	edge [ source 8098 target 8100 graphics [ fill "#000000" ] ] 
	edge [ source 8099 target 8111 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 8100 target 8101 graphics [ fill "#0000ff" ] ] 
	edge [ source 8100 target 8102 graphics [ fill "#000000" ] ] 
	edge [ source 8101 target 8111 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 8102 target 8103 graphics [ fill "#0000ff" ] ] 
	edge [ source 8102 target 8104 graphics [ fill "#000000" ] ] 
	edge [ source 8103 target 8104 graphics [ fill "#0000ff" ] ] 
	edge [ source 8104 target 8094 graphics [ fill "#000000" ] ] 
	edge [ source 8095 target 8094 graphics [ fill "#0000ff" ] ] 
	edge [ source 8094 target 8095 graphics [ fill "#000000" ] ] 
	edge [ source 8094 target 8105 graphics [ fill "#0000ff" ] ] 
	edge [ source 8105 target 8092 graphics [ fill "#000000" ] ] 
	edge [ source 8093 target 8092 graphics [ fill "#0000ff" ] ] 
	edge [ source 8092 target 8093 graphics [ fill "#000000" ] ] 
	edge [ source 8092 target 8106 graphics [ fill "#0000ff" ] ] 
	edge [ source 8106 target 8087 graphics [ fill "#000000" ] ] 
	edge [ source 8088 target 8089 graphics [ fill "#0000ff" ] ] 
	edge [ source 8088 target 8090 graphics [ fill "#000000" ] ] 
	edge [ source 8089 target 8091 graphics [ fill "#000000" ] ] 
	edge [ source 8090 target 8091 graphics [ fill "#0000ff" ] ] 
	edge [ source 8091 target 8087 graphics [ fill "#0000ff" ] ] 
	edge [ source 8087 target 8088 graphics [ fill "#000000" ] ] 
	edge [ source 8087 target 8107 graphics [ fill "#0000ff" ] ] 
	edge [ source 8107 target 8081 graphics [ fill "#000000" ] ] 
	edge [ source 8082 target 8108 graphics [ fill "#0000ff" ] ] 
	edge [ source 8082 target 8083 graphics [ fill "#000000" ] ] 
	edge [ source 8108 target 8111 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 8083 target 8084 graphics [ fill "#0000ff" ] ] 
	edge [ source 8083 target 8085 graphics [ fill "#000000" ] ] 
	edge [ source 8084 target 8086 graphics [ fill "#000000" ] ] 
	edge [ source 8085 target 8086 graphics [ fill "#0000ff" ] ] 
	edge [ source 8086 target 8081 graphics [ fill "#0000ff" ] ] 
	edge [ source 8081 target 8082 graphics [ fill "#000000" ] ] 
	edge [ source 8081 target 8109 graphics [ fill "#0000ff" ] ] 
	edge [ source 8109 target 8074 graphics [ fill "#000000" ] ] 
	edge [ source 8075 target 8076 graphics [ fill "#0000ff" ] ] 
	edge [ source 8075 target 8077 graphics [ fill "#000000" ] ] 
	edge [ source 8076 target 8078 graphics [ fill "#000000" ] ] 
	edge [ source 8077 target 8079 graphics [ fill "#0000ff" ] ] 
	edge [ source 8077 target 8080 graphics [ fill "#000000" ] ] 
	edge [ source 8079 target 8072 graphics [ fill "#000000" ] ] 
	edge [ source 8073 target 8072 graphics [ fill "#0000ff" ] ] 
	edge [ source 8072 target 8073 graphics [ fill "#000000" ] ] 
	edge [ source 8072 target 8080 graphics [ fill "#0000ff" ] ] 
	edge [ source 8080 target 8078 graphics [ fill "#0000ff" ] ] 
	edge [ source 8078 target 8074 graphics [ fill "#0000ff" ] ] 
	edge [ source 8074 target 8075 graphics [ fill "#000000" ] ] 
	edge [ source 8074 target 8110 graphics [ fill "#0000ff" ] ] 
	edge [ source 8110 target 8111 graphics [ fill "#0000ff" ] ] 
	edge [ source 8111 target 8097 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 8759 graphics [ fill "#d3d3d3" ] label "  429: L429:
  430: NOTE_INSN_BASIC_BLOCK 38
  431: r264:DI=[r77:DI-0x40]
  432: r174:SI=[r264:DI+0x20]
  434: flags:CCGC=cmp([r77:DI-0x24],r174:SI)
  435: pc={(flags:CCGC&lt;0)?L433:pc}
" ]

	node [ id 8760 graphics [ fill "#d3d3d3" ] label "  433: L433:
  413: NOTE_INSN_BASIC_BLOCK 37
  414: r260:DI=[r77:DI-0x40]
  415: r169:DI=[r260:DI+0x30]
  416: r261:SI=[r77:DI-0x24]
  417: r170:DI=sign_extend(r261:SI)
  418: {r171:DI=r170:DI&lt;&lt;0x3;clobber flags:CC;}
  419: {r172:DI=r169:DI+r171:DI;clobber flags:CC;}
  420: r262:DI=[r172:DI]
  421: [r77:DI-0x38]=r262:DI
  422: r263:DI=[r77:DI-0x38]
  423: r173:SI=[r263:DI+0x4]
  424: si:SI=r173:SI
  425: di:DI=`*.LC82'
  426: ax:QI=0
  427: call [`rhp_log'] argc:0
  428: {[r77:DI-0x24]=[r77:DI-0x24]+0x1;clobber flags:CC;}
" ]

	node [ id 8761 graphics [ fill "#d3d3d3" ] label "  393: L393:
  394: NOTE_INSN_BASIC_BLOCK 34
  395: r258:DI=[r77:DI-0x40]
  396: r167:SI=[r258:DI+0x1c]
  398: flags:CCGC=cmp([r77:DI-0x24],r167:SI)
  399: pc={(flags:CCGC&lt;0)?L397:pc}
" ]

	node [ id 8762 graphics [ fill "#d3d3d3" ] label "  397: L397:
  377: NOTE_INSN_BASIC_BLOCK 33
  378: r254:DI=[r77:DI-0x40]
  379: r162:DI=[r254:DI+0x28]
  380: r255:SI=[r77:DI-0x24]
  381: r163:DI=sign_extend(r255:SI)
  382: {r164:DI=r163:DI&lt;&lt;0x3;clobber flags:CC;}
  383: {r165:DI=r162:DI+r164:DI;clobber flags:CC;}
  384: r256:DI=[r165:DI]
  385: [r77:DI-0x38]=r256:DI
  386: r257:DI=[r77:DI-0x38]
  387: r166:SI=[r257:DI+0x4]
  388: si:SI=r166:SI
  389: di:DI=`*.LC82'
  390: ax:QI=0
  391: call [`rhp_log'] argc:0
  392: {[r77:DI-0x24]=[r77:DI-0x24]+0x1;clobber flags:CC;}
" ]

	node [ id 8763 graphics [ fill "#d3d3d3" ] label "  450: L450:
  451: NOTE_INSN_BASIC_BLOCK 40
  453: flags:CCZ=cmp([r77:DI-0x8],0)
  454: pc={(flags:CCZ!=0)?L452:pc}
" ]

	node [ id 8764 graphics [ fill "#d3d3d3" ] label "  452: L452:
  349: NOTE_INSN_BASIC_BLOCK 31
  350: r249:DI=[r77:DI-0x8]
  351: r157:DI=[r249:DI+0x8]
  352: [r77:DI-0x40]=r157:DI
  353: r250:DI=[r77:DI-0x40]
  354: r158:SI=[r250:DI+0x20]
  355: r251:DI=[r77:DI-0x40]
  356: r159:SI=[r251:DI+0x1c]
  357: r252:DI=[r77:DI-0x40]
  358: r160:SI=[r252:DI+0x4]
  359: r8:SI=r158:SI
  360: cx:SI=r159:SI
  361: dx:SI=r160:SI
  362: si:DI=`__FUNCTION__.20'
  363: di:DI=`*.LC90'
  364: ax:QI=0
  365: call [`rhp_log'] argc:0
  366: r253:DI=[r77:DI-0x40]
  367: r161:DI=[r253:DI+0x28]
  368: flags:CCZ=cmp(r161:DI,0)
  369: pc={(flags:CCZ==0)?L400:pc}
" ]

	node [ id 8765 graphics [ fill "#d3d3d3" ] label "  370: NOTE_INSN_BASIC_BLOCK 32
  371: di:DI=`*.LC91'
  372: ax:QI=0
  373: call [`rhp_log'] argc:0
  374: [r77:DI-0x24]=0
  375: pc=L393
" ]

	node [ id 8766 graphics [ fill "#d3d3d3" ] label "  400: L400:
  401: NOTE_INSN_BASIC_BLOCK 35
  402: r259:DI=[r77:DI-0x40]
  403: r168:DI=[r259:DI+0x30]
  404: flags:CCZ=cmp(r168:DI,0)
  405: pc={(flags:CCZ==0)?L436:pc}
" ]

	node [ id 8767 graphics [ fill "#d3d3d3" ] label "  406: NOTE_INSN_BASIC_BLOCK 36
  407: di:DI=`*.LC92'
  408: ax:QI=0
  409: call [`rhp_log'] argc:0
  410: [r77:DI-0x24]=0
  411: pc=L429
" ]

	node [ id 8768 graphics [ fill "#d3d3d3" ] label "  436: L436:
  437: NOTE_INSN_BASIC_BLOCK 39
  438: si:DI=`*.LC83'
  439: di:DI=`*.LC81'
  440: ax:QI=0
  441: call [`rhp_log'] argc:0
  442: r265:DI=[r77:DI-0x8]
  443: r175:DI=[r265:DI]
  444: r176:DI=[`rhp_sp_master_node_list']
  445: si:DI=r175:DI
  446: di:DI=r176:DI
  447: ax:DI=call [`rhp_sp_next'] argc:0
  448: r266:DI=ax:DI
  449: [r77:DI-0x8]=r266:DI
" ]

	node [ id 8769 graphics [ fill "#d3d3d3" ] label "  330: L330:
  331: NOTE_INSN_BASIC_BLOCK 29
  333: flags:CCZ=cmp([r77:DI-0x8],0)
  334: pc={(flags:CCZ!=0)?L332:pc}
" ]

	node [ id 8770 graphics [ fill "#d3d3d3" ] label "  332: L332:
  259: NOTE_INSN_BASIC_BLOCK 25
  260: r225:DI=[r77:DI-0x8]
  261: r134:DI=[r225:DI+0x8]
  262: [r77:DI-0x38]=r134:DI
  263: r226:DI=[r77:DI-0x38]
  264: r135:DI=[r226:DI+0x8]
  265: r136:SI=[r135:DI+0x8]
  266: r227:DI=[r77:DI-0x38]
  267: r137:DI=[r227:DI+0x10]
  268: r138:SI=[r137:DI+0x8]
  269: flags:CCGC=cmp(r136:SI,r138:SI)
  270: pc={(flags:CCGC&lt;=0)?L284:pc}
" ]

	node [ id 8771 graphics [ fill "#d3d3d3" ] label "  271: NOTE_INSN_BASIC_BLOCK 26
  272: si:DI=`__FUNCTION__.20'
  273: di:DI=`*.LC86'
  274: ax:QI=0
  275: call [`rhp_log'] argc:0
  276: r228:DI=[r77:DI-0x38]
  277: r229:DI=[r228:DI+0x8]
  278: [r77:DI-0x10]=r229:DI
  279: r230:DI=[r77:DI-0x38]
  280: r231:DI=[r230:DI+0x10]
  281: [r77:DI-0x18]=r231:DI
  282: pc=L292
" ]

	node [ id 8772 graphics [ fill "#d3d3d3" ] label "  284: L284:
  285: NOTE_INSN_BASIC_BLOCK 27
  286: r232:DI=[r77:DI-0x38]
  287: r233:DI=[r232:DI+0x10]
  288: [r77:DI-0x10]=r233:DI
  289: r234:DI=[r77:DI-0x38]
  290: r235:DI=[r234:DI+0x8]
  291: [r77:DI-0x18]=r235:DI
" ]

	node [ id 8773 graphics [ fill "#d3d3d3" ] label "  292: L292:
  293: NOTE_INSN_BASIC_BLOCK 28
  294: r236:DI=[r77:DI-0x10]
  295: r139:DI=[r236:DI+0x30]
  296: r237:DI=[r77:DI-0x10]
  297: r140:SI=[r237:DI+0x20]
  298: r141:DI=sign_extend(r140:SI)
  299: {r142:DI=r141:DI&lt;&lt;0x3;clobber flags:CC;}
  300: {r143:DI=r139:DI+r142:DI;clobber flags:CC;}
  301: r238:DI=[r77:DI-0x38]
  302: [r143:DI]=r238:DI
  303: r239:DI=[r77:DI-0x10]
  304: r144:SI=[r239:DI+0x20]
  305: {r145:SI=r144:SI+0x1;clobber flags:CC;}
  306: r240:DI=[r77:DI-0x10]
  307: [r240:DI+0x20]=r145:SI
  308: r241:DI=[r77:DI-0x18]
  309: r146:DI=[r241:DI+0x28]
  310: r242:DI=[r77:DI-0x18]
  311: r147:SI=[r242:DI+0x1c]
  312: r148:DI=sign_extend(r147:SI)
  313: {r149:DI=r148:DI&lt;&lt;0x3;clobber flags:CC;}
  314: {r150:DI=r146:DI+r149:DI;clobber flags:CC;}
  315: r243:DI=[r77:DI-0x38]
  316: [r150:DI]=r243:DI
  317: r244:DI=[r77:DI-0x18]
  318: r151:SI=[r244:DI+0x1c]
  319: {r152:SI=r151:SI+0x1;clobber flags:CC;}
  320: r245:DI=[r77:DI-0x18]
  321: [r245:DI+0x1c]=r152:SI
  322: r246:DI=[r77:DI-0x8]
  323: r153:DI=[r246:DI]
  324: r154:DI=[`rhp_sp_master_edge_list']
  325: si:DI=r153:DI
  326: di:DI=r154:DI
  327: ax:DI=call [`rhp_sp_next'] argc:0
  328: r247:DI=ax:DI
  329: [r77:DI-0x8]=r247:DI
" ]

	node [ id 8774 graphics [ fill "#d3d3d3" ] label "  217: L217:
  218: NOTE_INSN_BASIC_BLOCK 21
  219: r220:DI=[r77:DI-0x48]
  220: r125:SI=[r220:DI]
  222: flags:CCGC=cmp([r77:DI-0x24],r125:SI)
  223: pc={(flags:CCGC&lt;0)?L221:pc}
" ]

	node [ id 8775 graphics [ fill "#d3d3d3" ] label "  221: L221:
  134: NOTE_INSN_BASIC_BLOCK 16
  135: r200:DI=[r77:DI-0x48]
  136: r102:DI=[r200:DI+0x8]
  137: r201:SI=[r77:DI-0x24]
  138: r103:DI=sign_extend(r201:SI)
  139: {r104:DI=r103:DI&lt;&lt;0x3;clobber flags:CC;}
  140: {r105:DI=r102:DI+r104:DI;clobber flags:CC;}
  141: r202:DI=[r105:DI]
  142: [r77:DI-0x40]=r202:DI
  143: r203:DI=[r77:DI-0x40]
  144: r204:SI=[r77:DI-0x20]
  145: [r203:DI+0x18]=r204:SI
  146: r205:DI=[r77:DI-0x40]
  147: r106:SI=[r205:DI+0x20]
  148: r206:DI=[r77:DI-0x40]
  149: r107:SI=[r206:DI+0x1c]
  150: r207:DI=[r77:DI-0x40]
  151: r108:SI=[r207:DI+0x4]
  152: r208:SI=[r77:DI-0x1c]
  153: r209:SI=[r77:DI-0x20]
  154: {sp:DI=sp:DI-0x8;clobber flags:CC;}
      REG_ARGS_SIZE 0x8
  155: [pre sp:DI+=0xfffffffffffffff8]=r106:SI
      REG_ARGS_SIZE 0x10
  156: r9:SI=r107:SI
  157: r8:SI=r208:SI
  158: cx:SI=r209:SI
  159: dx:SI=r108:SI
  160: si:DI=`__FUNCTION__.20'
  161: di:DI=`*.LC87'
  162: ax:QI=0
  163: call [`rhp_log'] argc:0x10
  164: {sp:DI=sp:DI+0x10;clobber flags:CC;}
      REG_ARGS_SIZE 0
  165: r210:DI=[r77:DI-0x40]
  166: r109:SI=[r210:DI+0x1c]
  167: flags:CCZ=cmp(r109:SI,0)
  168: pc={(flags:CCZ==0)?L186:pc}
" ]

	node [ id 8776 graphics [ fill "#d3d3d3" ] label "  169: NOTE_INSN_BASIC_BLOCK 17
  170: r211:DI=[r77:DI-0x40]
  171: r110:SI=[r211:DI+0x1c]
  172: r111:DI=sign_extend(r110:SI)
  173: {r112:DI=r111:DI&lt;&lt;0x3;clobber flags:CC;}
  174: dx:SI=0xa39
  175: si:DI=`__FUNCTION__.20'
  176: di:DI=r112:DI
  177: ax:DI=call [`rhp_malloc'] argc:0
  178: r113:DI=ax:DI
  179: r212:DI=[r77:DI-0x40]
  180: [r212:DI+0x28]=r113:DI
  181: r213:DI=[r77:DI-0x40]
  182: r114:SI=[r213:DI+0x1c]
  183: r115:DI=sign_extend(r114:SI)
  184: {r116:DI=r115:DI&lt;&lt;0x3;clobber flags:CC;}
  185: {[r77:DI-0x30]=[r77:DI-0x30]+r116:DI;clobber flags:CC;}
" ]

	node [ id 8777 graphics [ fill "#d3d3d3" ] label "  186: L186:
  187: NOTE_INSN_BASIC_BLOCK 18
  188: r214:DI=[r77:DI-0x40]
  189: r117:SI=[r214:DI+0x20]
  190: flags:CCZ=cmp(r117:SI,0)
  191: pc={(flags:CCZ==0)?L209:pc}
" ]

	node [ id 8778 graphics [ fill "#d3d3d3" ] label "  192: NOTE_INSN_BASIC_BLOCK 19
  193: r215:DI=[r77:DI-0x40]
  194: r118:SI=[r215:DI+0x20]
  195: r119:DI=sign_extend(r118:SI)
  196: {r120:DI=r119:DI&lt;&lt;0x3;clobber flags:CC;}
  197: dx:SI=0xa3f
  198: si:DI=`__FUNCTION__.20'
  199: di:DI=r120:DI
  200: ax:DI=call [`rhp_malloc'] argc:0
  201: r121:DI=ax:DI
  202: r216:DI=[r77:DI-0x40]
  203: [r216:DI+0x30]=r121:DI
  204: r217:DI=[r77:DI-0x40]
  205: r122:SI=[r217:DI+0x20]
  206: r123:DI=sign_extend(r122:SI)
  207: {r124:DI=r123:DI&lt;&lt;0x3;clobber flags:CC;}
  208: {[r77:DI-0x30]=[r77:DI-0x30]+r124:DI;clobber flags:CC;}
" ]

	node [ id 8779 graphics [ fill "#d3d3d3" ] label "  209: L209:
  210: NOTE_INSN_BASIC_BLOCK 20
  211: {[r77:DI-0x20]=[r77:DI-0x20]+0x1;clobber flags:CC;}
  212: r218:DI=[r77:DI-0x40]
  213: [r218:DI+0x1c]=0
  214: r219:DI=[r77:DI-0x40]
  215: [r219:DI+0x20]=0
  216: {[r77:DI-0x24]=[r77:DI-0x24]+0x1;clobber flags:CC;}
" ]

	node [ id 8780 graphics [ fill "#d3d3d3" ] label "  227: L227:
  228: NOTE_INSN_BASIC_BLOCK 23
  229: r126:SI=[`rhp_nlevels']
  231: flags:CCGC=cmp([r77:DI-0x1c],r126:SI)
  232: pc={(flags:CCGC&lt;0)?L230:pc}
" ]

	node [ id 8781 graphics [ fill "#d3d3d3" ] label "  230: L230:
  100: NOTE_INSN_BASIC_BLOCK 12
  101: r195:SI=[r77:DI-0x1c]
  102: r98:DI=sign_extend(r195:SI)
  103: r99:DI=[`rhp_sp_layers']
  104: si:DI=r98:DI
  105: di:DI=r99:DI
  106: ax:DI=call [`rhp_sp_lookup'] argc:0
  107: r196:DI=ax:DI
  108: [r77:DI-0x8]=r196:DI
  109: flags:CCZ=cmp([r77:DI-0x8],0)
  110: pc={(flags:CCZ!=0)?L120:pc}
" ]

	node [ id 8782 graphics [ fill "#d3d3d3" ] label "  120: L120:
  121: NOTE_INSN_BASIC_BLOCK 14
  122: [r77:DI-0x20]=0
  123: r198:DI=[r77:DI-0x8]
  124: r100:DI=[r198:DI+0x8]
  125: [r77:DI-0x48]=r100:DI
  126: r199:DI=[r77:DI-0x48]
  127: r101:DI=[r199:DI+0x8]
  128: flags:CCZ=cmp(r101:DI,0)
  129: pc={(flags:CCZ==0)?L224:pc}
" ]

	node [ id 8783 graphics [ fill "#d3d3d3" ] label "  130: NOTE_INSN_BASIC_BLOCK 15
  131: [r77:DI-0x24]=0
  132: pc=L217
" ]

	node [ id 8784 graphics [ fill "#d3d3d3" ] label "  224: L224:
  225: NOTE_INSN_BASIC_BLOCK 22
  226: {[r77:DI-0x1c]=[r77:DI-0x1c]+0x1;clobber flags:CC;}
" ]

	node [ id 8785 graphics [ fill "#d3d3d3" ] label "   90: L90:
   91: NOTE_INSN_BASIC_BLOCK 10
   93: flags:CCZ=cmp([r77:DI-0x8],0)
   94: pc={(flags:CCZ!=0)?L92:pc}
" ]

	node [ id 8786 graphics [ fill "#d3d3d3" ] label "   92: L92:
   34: NOTE_INSN_BASIC_BLOCK 6
   35: r178:DI=[r77:DI-0x8]
   36: r85:DI=[r178:DI+0x8]
   37: [r77:DI-0x38]=r85:DI
   38: r86:SI=[`rhp_number_of_edges']
   39: {r87:SI=r86:SI+0x1;clobber flags:CC;}
   40: [`rhp_number_of_edges']=r87:SI
   41: r179:DI=[r77:DI-0x38]
   42: r88:DI=[r179:DI+0x8]
   43: r89:SI=[r88:DI+0x8]
   44: r180:DI=[r77:DI-0x38]
   45: r90:DI=[r180:DI+0x10]
   46: r91:SI=[r90:DI+0x8]
   47: flags:CCGC=cmp(r89:SI,r91:SI)
   48: pc={(flags:CCGC&lt;=0)?L62:pc}
" ]

	node [ id 8787 graphics [ fill "#d3d3d3" ] label "   49: NOTE_INSN_BASIC_BLOCK 7
   50: si:DI=`__FUNCTION__.20'
   51: di:DI=`*.LC86'
   52: ax:QI=0
   53: call [`rhp_log'] argc:0
   54: r181:DI=[r77:DI-0x38]
   55: r182:DI=[r181:DI+0x8]
   56: [r77:DI-0x10]=r182:DI
   57: r183:DI=[r77:DI-0x38]
   58: r184:DI=[r183:DI+0x10]
   59: [r77:DI-0x18]=r184:DI
   60: pc=L70
" ]

	node [ id 8788 graphics [ fill "#d3d3d3" ] label "   62: L62:
   63: NOTE_INSN_BASIC_BLOCK 8
   64: r185:DI=[r77:DI-0x38]
   65: r186:DI=[r185:DI+0x10]
   66: [r77:DI-0x10]=r186:DI
   67: r187:DI=[r77:DI-0x38]
   68: r188:DI=[r187:DI+0x8]
   69: [r77:DI-0x18]=r188:DI
" ]

	node [ id 8789 graphics [ fill "#d3d3d3" ] label "   70: L70:
   71: NOTE_INSN_BASIC_BLOCK 9
   72: r189:DI=[r77:DI-0x10]
   73: r92:SI=[r189:DI+0x20]
   74: {r93:SI=r92:SI+0x1;clobber flags:CC;}
   75: r190:DI=[r77:DI-0x10]
   76: [r190:DI+0x20]=r93:SI
   77: r191:DI=[r77:DI-0x18]
   78: r94:SI=[r191:DI+0x1c]
   79: {r95:SI=r94:SI+0x1;clobber flags:CC;}
   80: r192:DI=[r77:DI-0x18]
   81: [r192:DI+0x1c]=r95:SI
   82: r193:DI=[r77:DI-0x8]
   83: r96:DI=[r193:DI]
   84: r97:DI=[`rhp_sp_master_edge_list']
   85: si:DI=r96:DI
   86: di:DI=r97:DI
   87: ax:DI=call [`rhp_sp_next'] argc:0
   88: r194:DI=ax:DI
   89: [r77:DI-0x8]=r194:DI
" ]



# function number 40
	node [ id 8790 graphics [ fill "#ffffff" ] label "rhp_allocateadjacencylists ()
ENTRY" ]

	node [ id 8791 graphics [ fill "#ffffff" ] label "rhp_allocateadjacencylists ()
EXIT" ]

	node [ id 8792 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x8]=0
    6: [r77:DI-0x38]=0
    7: [r77:DI-0x10]=0
    8: [r77:DI-0x18]=0
    9: [r77:DI-0x40]=0
   10: [r77:DI-0x48]=0
   11: [r77:DI-0x1c]=0
   12: [r77:DI-0x20]=0
   13: [r77:DI-0x24]=0
   14: [r77:DI-0x30]=0
   15: [`rhp_number_of_edges']=0
   16: r82:DI=[`rhp_sp_master_edge_list']
   17: di:DI=r82:DI
   18: ax:SI=call [`rhp_sp_has_data'] argc:0
   19: r83:SI=ax:SI
   20: flags:CCZ=cmp(r83:SI,0)
   21: pc={(flags:CCZ!=0)?L25:pc}
" ]

	node [ id 8793 graphics [ fill "#d3d3d3" ] label "   22: NOTE_INSN_BASIC_BLOCK 4
   23: pc=L458
" ]

	node [ id 8794 graphics [ fill "#d3d3d3" ] label "   25: L25:
   26: NOTE_INSN_BASIC_BLOCK 5
   27: r84:DI=[`rhp_sp_master_edge_list']
   28: di:DI=r84:DI
   29: ax:DI=call [`rhp_sp_min'] argc:0
   30: r177:DI=ax:DI
   31: [r77:DI-0x8]=r177:DI
   32: pc=L90
" ]

	node [ id 8795 graphics [ fill "#d3d3d3" ] label "   95: NOTE_INSN_BASIC_BLOCK 11
   96: [r77:DI-0x30]=0
   97: [r77:DI-0x1c]=0
   98: pc=L227
" ]

	node [ id 8796 graphics [ fill "#d3d3d3" ] label "  111: NOTE_INSN_BASIC_BLOCK 13
  112: r197:SI=[r77:DI-0x1c]
  113: dx:SI=r197:SI
  114: si:DI=`__FUNCTION__.20'
  115: di:DI=`*.LC76'
  116: ax:QI=0
  117: call [`rhp_log'] argc:0
  118: pc=L458
" ]

	node [ id 8797 graphics [ fill "#d3d3d3" ] label "  233: NOTE_INSN_BASIC_BLOCK 24
  234: r127:SI=[`rhp_number_of_nodes']
  235: r128:DI=sign_extend(r127:SI)
  236: r221:DI=r128:DI
  237: {r221:DI=r221:DI&lt;&lt;0x2;clobber flags:CC;}
  238: {r221:DI=r221:DI+r128:DI;clobber flags:CC;}
      REG_EQUAL r128:DI*0x5
  239: {r222:DI=r221:DI&lt;&lt;0x4;clobber flags:CC;}
  240: r221:DI=r222:DI
      REG_EQUAL r128:DI*0x50
  241: r129:DI=r221:DI
  242: r223:DI=[r77:DI-0x30]
  243: {r130:DI=r129:DI+r223:DI;clobber flags:CC;}
      REG_EQUAL r129:DI+[r77:DI-0x30]
  244: r131:DI=r130:DI
  245: r132:DI=[r77:DI-0x30]
  246: cx:DI=r131:DI
  247: dx:DI=r132:DI
  248: si:DI=`__FUNCTION__.20'
  249: di:DI=`*.LC88'
  250: ax:QI=0
  251: call [`rhp_log'] argc:0
  252: r133:DI=[`rhp_sp_master_edge_list']
  253: di:DI=r133:DI
  254: ax:DI=call [`rhp_sp_min'] argc:0
  255: r224:DI=ax:DI
  256: [r77:DI-0x8]=r224:DI
  257: pc=L330
" ]

	node [ id 8798 graphics [ fill "#d3d3d3" ] label "  335: NOTE_INSN_BASIC_BLOCK 30
  336: r155:SI=[`rhp_number_of_edges']
  337: dx:SI=r155:SI
  338: si:DI=`__FUNCTION__.20'
  339: di:DI=`*.LC89'
  340: ax:QI=0
  341: call [`rhp_log'] argc:0
  342: r156:DI=[`rhp_sp_master_node_list']
  343: di:DI=r156:DI
  344: ax:DI=call [`rhp_sp_min'] argc:0
  345: r248:DI=ax:DI
  346: [r77:DI-0x8]=r248:DI
  347: pc=L450
" ]

	node [ id 8799 graphics [ fill "#d3d3d3" ] label "  455: NOTE_INSN_BASIC_BLOCK 41
" ]

	node [ id 8800 graphics [ fill "#d3d3d3" ] label "  458: L458:
  459: NOTE_INSN_BASIC_BLOCK 43
" ]

	edge [ source 8790 target 8792 graphics [ fill "#0000ff" ] ] 
	edge [ source 8792 target 8793 graphics [ fill "#0000ff" ] ] 
	edge [ source 8792 target 8794 graphics [ fill "#000000" ] ] 
	edge [ source 8793 target 8800 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 8794 target 8785 graphics [ fill "#000000" ] ] 
	edge [ source 8786 target 8787 graphics [ fill "#0000ff" ] ] 
	edge [ source 8786 target 8788 graphics [ fill "#000000" ] ] 
	edge [ source 8787 target 8789 graphics [ fill "#000000" ] ] 
	edge [ source 8788 target 8789 graphics [ fill "#0000ff" ] ] 
	edge [ source 8789 target 8785 graphics [ fill "#0000ff" ] ] 
	edge [ source 8785 target 8786 graphics [ fill "#000000" ] ] 
	edge [ source 8785 target 8795 graphics [ fill "#0000ff" ] ] 
	edge [ source 8795 target 8780 graphics [ fill "#000000" ] ] 
	edge [ source 8781 target 8796 graphics [ fill "#0000ff" ] ] 
	edge [ source 8781 target 8782 graphics [ fill "#000000" ] ] 
	edge [ source 8796 target 8800 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 8782 target 8783 graphics [ fill "#0000ff" ] ] 
	edge [ source 8782 target 8784 graphics [ fill "#000000" ] ] 
	edge [ source 8783 target 8774 graphics [ fill "#000000" ] ] 
	edge [ source 8775 target 8776 graphics [ fill "#0000ff" ] ] 
	edge [ source 8775 target 8777 graphics [ fill "#000000" ] ] 
	edge [ source 8776 target 8777 graphics [ fill "#0000ff" ] ] 
	edge [ source 8777 target 8778 graphics [ fill "#0000ff" ] ] 
	edge [ source 8777 target 8779 graphics [ fill "#000000" ] ] 
	edge [ source 8778 target 8779 graphics [ fill "#0000ff" ] ] 
	edge [ source 8779 target 8774 graphics [ fill "#0000ff" ] ] 
	edge [ source 8774 target 8775 graphics [ fill "#000000" ] ] 
	edge [ source 8774 target 8784 graphics [ fill "#0000ff" ] ] 
	edge [ source 8784 target 8780 graphics [ fill "#0000ff" ] ] 
	edge [ source 8780 target 8781 graphics [ fill "#000000" ] ] 
	edge [ source 8780 target 8797 graphics [ fill "#0000ff" ] ] 
	edge [ source 8797 target 8769 graphics [ fill "#000000" ] ] 
	edge [ source 8770 target 8771 graphics [ fill "#0000ff" ] ] 
	edge [ source 8770 target 8772 graphics [ fill "#000000" ] ] 
	edge [ source 8771 target 8773 graphics [ fill "#000000" ] ] 
	edge [ source 8772 target 8773 graphics [ fill "#0000ff" ] ] 
	edge [ source 8773 target 8769 graphics [ fill "#0000ff" ] ] 
	edge [ source 8769 target 8770 graphics [ fill "#000000" ] ] 
	edge [ source 8769 target 8798 graphics [ fill "#0000ff" ] ] 
	edge [ source 8798 target 8763 graphics [ fill "#000000" ] ] 
	edge [ source 8764 target 8765 graphics [ fill "#0000ff" ] ] 
	edge [ source 8764 target 8766 graphics [ fill "#000000" ] ] 
	edge [ source 8765 target 8761 graphics [ fill "#000000" ] ] 
	edge [ source 8762 target 8761 graphics [ fill "#0000ff" ] ] 
	edge [ source 8761 target 8762 graphics [ fill "#000000" ] ] 
	edge [ source 8761 target 8766 graphics [ fill "#0000ff" ] ] 
	edge [ source 8766 target 8767 graphics [ fill "#0000ff" ] ] 
	edge [ source 8766 target 8768 graphics [ fill "#000000" ] ] 
	edge [ source 8767 target 8759 graphics [ fill "#000000" ] ] 
	edge [ source 8760 target 8759 graphics [ fill "#0000ff" ] ] 
	edge [ source 8759 target 8760 graphics [ fill "#000000" ] ] 
	edge [ source 8759 target 8768 graphics [ fill "#0000ff" ] ] 
	edge [ source 8768 target 8763 graphics [ fill "#0000ff" ] ] 
	edge [ source 8763 target 8764 graphics [ fill "#000000" ] ] 
	edge [ source 8763 target 8799 graphics [ fill "#0000ff" ] ] 
	edge [ source 8799 target 8800 graphics [ fill "#0000ff" ] ] 
	edge [ source 8800 target 8791 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 9467 graphics [ fill "#d3d3d3" ] label "   57: L57:
   58: NOTE_INSN_BASIC_BLOCK 10
   60: flags:CCZ=cmp([r77:DI-0x8],0)
   61: pc={(flags:CCZ!=0)?L59:pc}
" ]

	node [ id 9468 graphics [ fill "#d3d3d3" ] label "   59: L59:
   32: NOTE_INSN_BASIC_BLOCK 6
   33: r93:DI=[r77:DI-0x8]
   34: r85:DI=[r93:DI+0x8]
   35: [r77:DI-0x18]=r85:DI
   36: r94:DI=[r77:DI-0x18]
   37: r86:SI=[r94:DI+0x1c]
   38: flags:CCZ=cmp(r86:SI,0)
   39: pc={(flags:CCZ!=0)?L47:pc}
" ]

	node [ id 9469 graphics [ fill "#d3d3d3" ] label "   40: NOTE_INSN_BASIC_BLOCK 7
   41: r95:DI=[r77:DI-0x18]
   42: r87:SI=[r95:DI+0x20]
   43: flags:CCZ=cmp(r87:SI,0)
   44: pc={(flags:CCZ!=0)?L47:pc}
" ]

	node [ id 9470 graphics [ fill "#d3d3d3" ] label "   47: L47:
   48: NOTE_INSN_BASIC_BLOCK 9
   49: r96:DI=[r77:DI-0x8]
   50: r88:DI=[r96:DI]
   51: r89:DI=[`rhp_sp_master_node_list']
   52: si:DI=r88:DI
   53: di:DI=r89:DI
   54: ax:DI=call [`rhp_sp_next'] argc:0
   55: r97:DI=ax:DI
   56: [r77:DI-0x8]=r97:DI
" ]

	node [ id 9471 graphics [ fill "#d3d3d3" ] label "   45: NOTE_INSN_BASIC_BLOCK 8
   46: {[r77:DI-0xc]=[r77:DI-0xc]+0x1;clobber flags:CC;}
" ]



# function number 41
	node [ id 9472 graphics [ fill "#ffffff" ] label "rhp_countisolatednodes ()
ENTRY" ]

	node [ id 9473 graphics [ fill "#ffffff" ] label "rhp_countisolatednodes ()
EXIT" ]

	node [ id 9474 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x18]=0
    6: [r77:DI-0x8]=0
    7: [r77:DI-0xc]=0
    8: [`rhp_number_of_isolated_nodes']=0
    9: r82:DI=[`rhp_sp_master_node_list']
   10: di:DI=r82:DI
   11: ax:SI=call [`rhp_sp_has_data'] argc:0
   12: r83:SI=ax:SI
   13: flags:CCZ=cmp(r83:SI,0)
   14: pc={(flags:CCZ!=0)?L23:pc}
" ]

	node [ id 9475 graphics [ fill "#d3d3d3" ] label "   15: NOTE_INSN_BASIC_BLOCK 4
   16: si:DI=`__FUNCTION__.19'
   17: di:DI=`*.LC43'
   18: ax:QI=0
   19: call [`rhp_log'] argc:0
   20: r90:SI=0
   21: pc=L70
" ]

	node [ id 9476 graphics [ fill "#d3d3d3" ] label "   23: L23:
   24: NOTE_INSN_BASIC_BLOCK 5
   25: r84:DI=[`rhp_sp_master_node_list']
   26: di:DI=r84:DI
   27: ax:DI=call [`rhp_sp_min'] argc:0
   28: r92:DI=ax:DI
   29: [r77:DI-0x8]=r92:DI
   30: pc=L57
" ]

	node [ id 9477 graphics [ fill "#d3d3d3" ] label "   62: NOTE_INSN_BASIC_BLOCK 11
   63: r98:SI=[r77:DI-0xc]
   64: dx:SI=r98:SI
   65: si:DI=`__FUNCTION__.19'
   66: di:DI=`*.LC93'
   67: ax:QI=0
   68: call [`rhp_log'] argc:0
   69: r90:SI=[r77:DI-0xc]
" ]

	node [ id 9478 graphics [ fill "#d3d3d3" ] label "   70: L70:
   71: NOTE_INSN_BASIC_BLOCK 12
   72: r91:SI=r90:SI
   76: ax:SI=r91:SI
   77: use ax:SI
" ]

	edge [ source 9472 target 9474 graphics [ fill "#0000ff" ] ] 
	edge [ source 9474 target 9475 graphics [ fill "#0000ff" ] ] 
	edge [ source 9474 target 9476 graphics [ fill "#000000" ] ] 
	edge [ source 9475 target 9478 graphics [ fill "#000000" ] ] 
	edge [ source 9476 target 9467 graphics [ fill "#000000" ] ] 
	edge [ source 9468 target 9469 graphics [ fill "#0000ff" ] ] 
	edge [ source 9468 target 9470 graphics [ fill "#000000" ] ] 
	edge [ source 9469 target 9471 graphics [ fill "#0000ff" ] ] 
	edge [ source 9469 target 9470 graphics [ fill "#000000" ] ] 
	edge [ source 9471 target 9470 graphics [ fill "#0000ff" ] ] 
	edge [ source 9470 target 9467 graphics [ fill "#0000ff" ] ] 
	edge [ source 9467 target 9468 graphics [ fill "#000000" ] ] 
	edge [ source 9467 target 9477 graphics [ fill "#0000ff" ] ] 
	edge [ source 9477 target 9478 graphics [ fill "#0000ff" ] ] 
	edge [ source 9478 target 9473 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 9671 graphics [ fill "#d3d3d3" ] label "   43: L43:
   44: NOTE_INSN_BASIC_BLOCK 7
   45: r87:SI=[`rhp_nlevels']
   47: flags:CCGC=cmp([r77:DI-0x4],r87:SI)
   48: pc={(flags:CCGC&lt;0)?L46:pc}
" ]

	node [ id 9672 graphics [ fill "#d3d3d3" ] label "   46: L46:
   28: NOTE_INSN_BASIC_BLOCK 6
   29: r88:SI=[r77:DI-0x4]
   30: di:SI=r88:SI
   31: ax:DI=call [`rhp_makeinterlayer'] argc:0
   32: r89:DI=ax:DI
   33: [r77:DI-0x10]=r89:DI
   34: r84:DI=[r77:DI-0x10]
   35: r90:SI=[r77:DI-0x4]
   36: r85:DI=sign_extend(r90:SI)
   37: r86:DI=[`rhp_sp_between_layers']
   38: dx:DI=r84:DI
   39: si:DI=r85:DI
   40: di:DI=r86:DI
   41: call [`rhp_sp_insert'] argc:0
   42: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]



# function number 42
	node [ id 9673 graphics [ fill "#ffffff" ] label "rhp_initcrossings ()
ENTRY" ]

	node [ id 9674 graphics [ fill "#ffffff" ] label "rhp_initcrossings ()
EXIT" ]

	node [ id 9675 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x4]=0
    6: [r77:DI-0x10]=0
    7: r82:SI=[`rhp_nlevels']
    8: dx:SI=r82:SI
    9: si:DI=`__FUNCTION__.18'
   10: di:DI=`*.LC94'
   11: ax:QI=0
   12: call [`rhp_log'] argc:0
   13: r83:SI=[`rhp_nlevels']
   14: flags:CCZ=cmp(r83:SI,0)
   15: pc={(flags:CCZ!=0)?L23:pc}
" ]

	node [ id 9676 graphics [ fill "#d3d3d3" ] label "   16: NOTE_INSN_BASIC_BLOCK 4
   17: si:DI=`__FUNCTION__.18'
   18: di:DI=`*.LC51'
   19: ax:QI=0
   20: call [`rhp_log'] argc:0
   21: pc=L52
" ]

	node [ id 9677 graphics [ fill "#d3d3d3" ] label "   23: L23:
   24: NOTE_INSN_BASIC_BLOCK 5
   25: [r77:DI-0x4]=0
   26: pc=L43
" ]

	node [ id 9678 graphics [ fill "#d3d3d3" ] label "   49: NOTE_INSN_BASIC_BLOCK 8
" ]

	node [ id 9679 graphics [ fill "#d3d3d3" ] label "   52: L52:
   53: NOTE_INSN_BASIC_BLOCK 10
" ]

	edge [ source 9673 target 9675 graphics [ fill "#0000ff" ] ] 
	edge [ source 9675 target 9676 graphics [ fill "#0000ff" ] ] 
	edge [ source 9675 target 9677 graphics [ fill "#000000" ] ] 
	edge [ source 9676 target 9679 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 9677 target 9671 graphics [ fill "#000000" ] ] 
	edge [ source 9672 target 9671 graphics [ fill "#0000ff" ] ] 
	edge [ source 9671 target 9672 graphics [ fill "#000000" ] ] 
	edge [ source 9671 target 9678 graphics [ fill "#0000ff" ] ] 
	edge [ source 9678 target 9679 graphics [ fill "#0000ff" ] ] 
	edge [ source 9679 target 9674 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 43
	node [ id 9821 graphics [ fill "#ffffff" ] label "rhp_makeinterlayer ()
ENTRY" ]

	node [ id 9822 graphics [ fill "#ffffff" ] label "rhp_makeinterlayer ()
EXIT" ]

	node [ id 9823 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x14]=di:SI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x10]=0
    7: [r77:DI-0x8]=0
    8: dx:SI=0xae4
    9: si:DI=`__FUNCTION__.17'
   10: di:DI=0x18
   11: ax:DI=call [`rhp_malloc'] argc:0
   12: r94:DI=ax:DI
   13: [r77:DI-0x10]=r94:DI
   14: {[r77:DI-0x8]=[r77:DI-0x8]+0x18;clobber flags:CC;}
   15: r95:SI=[r77:DI-0x14]
   16: di:SI=r95:SI
   17: ax:SI=call [`rhp_count_down_edges'] argc:0
   18: r82:SI=ax:SI
   19: r96:DI=[r77:DI-0x10]
   20: [r96:DI]=r82:SI
   21: r97:DI=[r77:DI-0x10]
   22: [r97:DI+0x10]=0xffffffffffffffff
   23: r98:DI=[r77:DI-0x10]
   24: r83:SI=[r98:DI]
   25: flags:CCZ=cmp(r83:SI,0)
   26: pc={(flags:CCZ==0)?L44:pc}
" ]

	node [ id 9824 graphics [ fill "#d3d3d3" ] label "   27: NOTE_INSN_BASIC_BLOCK 4
   28: r99:DI=[r77:DI-0x10]
   29: r84:SI=[r99:DI]
   30: r85:DI=sign_extend(r84:SI)
   31: {r86:DI=r85:DI&lt;&lt;0x3;clobber flags:CC;}
   32: dx:SI=0xaf0
   33: si:DI=`__FUNCTION__.17'
   34: di:DI=r86:DI
   35: ax:DI=call [`rhp_malloc'] argc:0
   36: r87:DI=ax:DI
   37: r100:DI=[r77:DI-0x10]
   38: [r100:DI+0x8]=r87:DI
   39: r101:DI=[r77:DI-0x10]
   40: r88:SI=[r101:DI]
   41: r89:DI=sign_extend(r88:SI)
   42: {r90:DI=r89:DI&lt;&lt;0x3;clobber flags:CC;}
   43: {[r77:DI-0x8]=[r77:DI-0x8]+r90:DI;clobber flags:CC;}
" ]

	node [ id 9825 graphics [ fill "#d3d3d3" ] label "   44: L44:
   45: NOTE_INSN_BASIC_BLOCK 5
   46: r91:DI=[r77:DI-0x8]
   47: dx:DI=r91:DI
   48: si:DI=`__FUNCTION__.17'
   49: di:DI=`*.LC95'
   50: ax:QI=0
   51: call [`rhp_log'] argc:0
   52: r92:DI=[r77:DI-0x10]
   55: r93:DI=r92:DI
   59: ax:DI=r93:DI
   60: use ax:DI
" ]

	edge [ source 9821 target 9823 graphics [ fill "#0000ff" ] ] 
	edge [ source 9823 target 9824 graphics [ fill "#0000ff" ] ] 
	edge [ source 9823 target 9825 graphics [ fill "#000000" ] ] 
	edge [ source 9824 target 9825 graphics [ fill "#0000ff" ] ] 
	edge [ source 9825 target 9822 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 9906 graphics [ fill "#d3d3d3" ] label "   88: L88:
   89: NOTE_INSN_BASIC_BLOCK 12
   90: r107:DI=[r77:DI-0x18]
   91: r92:SI=[r107:DI]
   93: flags:CCGC=cmp([r77:DI-0x8],r92:SI)
   94: pc={(flags:CCGC&lt;0)?L92:pc}
" ]

	node [ id 9907 graphics [ fill "#d3d3d3" ] label "   92: L92:
   75: NOTE_INSN_BASIC_BLOCK 11
   76: r103:DI=[r77:DI-0x18]
   77: r87:DI=[r103:DI+0x8]
   78: r104:SI=[r77:DI-0x8]
   79: r88:DI=sign_extend(r104:SI)
   80: {r89:DI=r88:DI&lt;&lt;0x3;clobber flags:CC;}
   81: {r90:DI=r87:DI+r89:DI;clobber flags:CC;}
   82: r105:DI=[r90:DI]
   83: [r77:DI-0x20]=r105:DI
   84: r106:DI=[r77:DI-0x20]
   85: r91:SI=[r106:DI+0x20]
   86: {[r77:DI-0x4]=[r77:DI-0x4]+r91:SI;clobber flags:CC;}
   87: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
" ]



# function number 44
	node [ id 9908 graphics [ fill "#ffffff" ] label "rhp_count_down_edges ()
ENTRY" ]

	node [ id 9909 graphics [ fill "#ffffff" ] label "rhp_count_down_edges ()
EXIT" ]

	node [ id 9910 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x24]=di:SI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x10]=0
    7: [r77:DI-0x18]=0
    8: [r77:DI-0x20]=0
    9: [r77:DI-0x4]=0
   10: [r77:DI-0x8]=0
   11: r95:SI=[r77:DI-0x24]
   12: r82:DI=sign_extend(r95:SI)
   13: r83:DI=[`rhp_sp_layers']
   14: si:DI=r82:DI
   15: di:DI=r83:DI
   16: ax:DI=call [`rhp_sp_lookup'] argc:0
   17: r96:DI=ax:DI
   18: [r77:DI-0x10]=r96:DI
   19: flags:CCZ=cmp([r77:DI-0x10],0)
   20: pc={(flags:CCZ!=0)?L31:pc}
" ]

	node [ id 9911 graphics [ fill "#d3d3d3" ] label "   21: NOTE_INSN_BASIC_BLOCK 4
   22: r97:SI=[r77:DI-0x24]
   23: dx:SI=r97:SI
   24: si:DI=`__FUNCTION__.16'
   25: di:DI=`*.LC96'
   26: ax:QI=0
   27: call [`rhp_log'] argc:0
   28: r93:SI=0
   29: pc=L106
" ]

	node [ id 9912 graphics [ fill "#d3d3d3" ] label "   31: L31:
   32: NOTE_INSN_BASIC_BLOCK 5
   33: r98:DI=[r77:DI-0x10]
   34: r84:DI=[r98:DI+0x8]
   35: [r77:DI-0x18]=r84:DI
   36: flags:CCZ=cmp([r77:DI-0x18],0)
   37: pc={(flags:CCZ!=0)?L48:pc}
" ]

	node [ id 9913 graphics [ fill "#d3d3d3" ] label "   38: NOTE_INSN_BASIC_BLOCK 6
   39: r99:SI=[r77:DI-0x24]
   40: dx:SI=r99:SI
   41: si:DI=`__FUNCTION__.16'
   42: di:DI=`*.LC97'
   43: ax:QI=0
   44: call [`rhp_log'] argc:0
   45: r93:SI=0
   46: pc=L106
" ]

	node [ id 9914 graphics [ fill "#d3d3d3" ] label "   48: L48:
   49: NOTE_INSN_BASIC_BLOCK 7
   50: r100:DI=[r77:DI-0x18]
   51: r85:DI=[r100:DI+0x8]
   52: flags:CCZ=cmp(r85:DI,0)
   53: pc={(flags:CCZ!=0)?L64:pc}
" ]

	node [ id 9915 graphics [ fill "#d3d3d3" ] label "   54: NOTE_INSN_BASIC_BLOCK 8
   55: r101:SI=[r77:DI-0x24]
   56: dx:SI=r101:SI
   57: si:DI=`__FUNCTION__.16'
   58: di:DI=`*.LC98'
   59: ax:QI=0
   60: call [`rhp_log'] argc:0
   61: r93:SI=0
   62: pc=L106
" ]

	node [ id 9916 graphics [ fill "#d3d3d3" ] label "   64: L64:
   65: NOTE_INSN_BASIC_BLOCK 9
   66: [r77:DI-0x4]=0
   67: r102:DI=[r77:DI-0x18]
   68: r86:DI=[r102:DI+0x8]
   69: flags:CCZ=cmp(r86:DI,0)
   70: pc={(flags:CCZ==0)?L95:pc}
" ]

	node [ id 9917 graphics [ fill "#d3d3d3" ] label "   71: NOTE_INSN_BASIC_BLOCK 10
   72: [r77:DI-0x8]=0
   73: pc=L88
" ]

	node [ id 9918 graphics [ fill "#d3d3d3" ] label "   95: L95:
   96: NOTE_INSN_BASIC_BLOCK 13
   97: r108:SI=[r77:DI-0x24]
   98: r109:SI=[r77:DI-0x4]
   99: cx:SI=r108:SI
  100: dx:SI=r109:SI
  101: si:DI=`__FUNCTION__.16'
  102: di:DI=`*.LC99'
  103: ax:QI=0
  104: call [`rhp_log'] argc:0
  105: r93:SI=[r77:DI-0x4]
" ]

	node [ id 9919 graphics [ fill "#d3d3d3" ] label "  106: L106:
  107: NOTE_INSN_BASIC_BLOCK 14
  108: r94:SI=r93:SI
  112: ax:SI=r94:SI
  113: use ax:SI
" ]

	edge [ source 9908 target 9910 graphics [ fill "#0000ff" ] ] 
	edge [ source 9910 target 9911 graphics [ fill "#0000ff" ] ] 
	edge [ source 9910 target 9912 graphics [ fill "#000000" ] ] 
	edge [ source 9911 target 9919 graphics [ fill "#000000" ] ] 
	edge [ source 9912 target 9913 graphics [ fill "#0000ff" ] ] 
	edge [ source 9912 target 9914 graphics [ fill "#000000" ] ] 
	edge [ source 9913 target 9919 graphics [ fill "#000000" ] ] 
	edge [ source 9914 target 9915 graphics [ fill "#0000ff" ] ] 
	edge [ source 9914 target 9916 graphics [ fill "#000000" ] ] 
	edge [ source 9915 target 9919 graphics [ fill "#000000" ] ] 
	edge [ source 9916 target 9917 graphics [ fill "#0000ff" ] ] 
	edge [ source 9916 target 9918 graphics [ fill "#000000" ] ] 
	edge [ source 9917 target 9906 graphics [ fill "#000000" ] ] 
	edge [ source 9907 target 9906 graphics [ fill "#0000ff" ] ] 
	edge [ source 9906 target 9907 graphics [ fill "#000000" ] ] 
	edge [ source 9906 target 9918 graphics [ fill "#0000ff" ] ] 
	edge [ source 9918 target 9919 graphics [ fill "#0000ff" ] ] 
	edge [ source 9919 target 9909 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 10144 graphics [ fill "#d3d3d3" ] label "   15: L15:
   16: NOTE_INSN_BASIC_BLOCK 5
   17: r82:SI=[`rhp_nlevels']
   19: flags:CCGC=cmp([r77:DI-0x4],r82:SI)
   20: pc={(flags:CCGC&lt;0)?L18:pc}
" ]

	node [ id 10145 graphics [ fill "#d3d3d3" ] label "   18: L18:
   10: NOTE_INSN_BASIC_BLOCK 4
   11: r83:SI=[r77:DI-0x4]
   12: di:SI=r83:SI
   13: call [`rhp_updatecrossingsbetweenlayers'] argc:0
   14: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]



# function number 45
	node [ id 10146 graphics [ fill "#ffffff" ] label "rhp_updateallcrossings ()
ENTRY" ]

	node [ id 10147 graphics [ fill "#ffffff" ] label "rhp_updateallcrossings ()
EXIT" ]

	node [ id 10148 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x4]=0
    6: call [`rhp_updateallpositions'] argc:0
    7: [r77:DI-0x4]=0x1
    8: pc=L15
" ]

	node [ id 10149 graphics [ fill "#d3d3d3" ] label "   21: NOTE_INSN_BASIC_BLOCK 6
   26: 0
" ]

	edge [ source 10146 target 10148 graphics [ fill "#0000ff" ] ] 
	edge [ source 10148 target 10144 graphics [ fill "#000000" ] ] 
	edge [ source 10145 target 10144 graphics [ fill "#0000ff" ] ] 
	edge [ source 10144 target 10145 graphics [ fill "#000000" ] ] 
	edge [ source 10144 target 10149 graphics [ fill "#0000ff" ] ] 
	edge [ source 10149 target 10147 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 10246 graphics [ fill "#d3d3d3" ] label "   20: L20:
   21: NOTE_INSN_BASIC_BLOCK 5
   22: r83:SI=[`rhp_nlevels']
   24: flags:CCGC=cmp([r77:DI-0x4],r83:SI)
   25: pc={(flags:CCGC&lt;0)?L23:pc}
" ]

	node [ id 10247 graphics [ fill "#d3d3d3" ] label "   23: L23:
   15: NOTE_INSN_BASIC_BLOCK 4
   16: r84:SI=[r77:DI-0x4]
   17: di:SI=r84:SI
   18: call [`rhp_updatenodepositions'] argc:0
   19: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]



# function number 46
	node [ id 10248 graphics [ fill "#ffffff" ] label "rhp_updateallpositions ()
ENTRY" ]

	node [ id 10249 graphics [ fill "#ffffff" ] label "rhp_updateallpositions ()
EXIT" ]

	node [ id 10250 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x4]=0
    6: r82:SI=[`rhp_nlevels']
    7: dx:SI=r82:SI
    8: si:DI=`__FUNCTION__.15'
    9: di:DI=`*.LC100'
   10: ax:QI=0
   11: call [`rhp_log'] argc:0
   12: [r77:DI-0x4]=0
   13: pc=L20
" ]

	node [ id 10251 graphics [ fill "#d3d3d3" ] label "   26: NOTE_INSN_BASIC_BLOCK 6
   31: 0
" ]

	edge [ source 10248 target 10250 graphics [ fill "#0000ff" ] ] 
	edge [ source 10250 target 10246 graphics [ fill "#000000" ] ] 
	edge [ source 10247 target 10246 graphics [ fill "#0000ff" ] ] 
	edge [ source 10246 target 10247 graphics [ fill "#000000" ] ] 
	edge [ source 10246 target 10251 graphics [ fill "#0000ff" ] ] 
	edge [ source 10251 target 10249 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 10348 graphics [ fill "#d3d3d3" ] label "  103: L103:
  104: NOTE_INSN_BASIC_BLOCK 11
  105: r112:DI=[r77:DI-0x18]
  106: r94:SI=[r112:DI]
  108: flags:CCGC=cmp([r77:DI-0x8],r94:SI)
  109: pc={(flags:CCGC&lt;0)?L107:pc}
" ]

	node [ id 10349 graphics [ fill "#d3d3d3" ] label "  107: L107:
   73: NOTE_INSN_BASIC_BLOCK 10
   74: r103:DI=[r77:DI-0x18]
   75: r86:DI=[r103:DI+0x8]
   76: r104:SI=[r77:DI-0x8]
   77: r87:DI=sign_extend(r104:SI)
   78: {r88:DI=r87:DI&lt;&lt;0x3;clobber flags:CC;}
   79: {r89:DI=r86:DI+r88:DI;clobber flags:CC;}
   80: r105:DI=[r89:DI]
   81: [r77:DI-0x20]=r105:DI
   82: r106:DI=[r77:DI-0x20]
   83: r107:SI=[r77:DI-0x4]
   84: [r106:DI+0x18]=r107:SI
   85: r108:DI=[r77:DI-0x20]
   86: r90:SI=[r108:DI+0x38]
   87: r109:DI=[r77:DI-0x20]
   88: r91:SI=[r109:DI+0x18]
   89: r110:DI=[r77:DI-0x20]
   90: r92:SI=[r110:DI+0x8]
   91: r111:DI=[r77:DI-0x20]
   92: r93:SI=[r111:DI+0x4]
   93: r9:SI=r90:SI
   94: r8:SI=r91:SI
   95: cx:SI=r92:SI
   96: dx:SI=r93:SI
   97: si:DI=`__FUNCTION__.14'
   98: di:DI=`*.LC102'
   99: ax:QI=0
  100: call [`rhp_log'] argc:0
  101: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
  102: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
" ]



# function number 47
	node [ id 10350 graphics [ fill "#ffffff" ] label "rhp_updatenodepositions ()
ENTRY" ]

	node [ id 10351 graphics [ fill "#ffffff" ] label "rhp_updatenodepositions ()
EXIT" ]

	node [ id 10352 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x24]=di:SI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x10]=0
    7: [r77:DI-0x18]=0
    8: [r77:DI-0x20]=0
    9: [r77:DI-0x4]=0
   10: [r77:DI-0x8]=0
   11: r95:SI=[r77:DI-0x24]
   12: dx:SI=r95:SI
   13: si:DI=`__FUNCTION__.14'
   14: di:DI=`*.LC101'
   15: ax:QI=0
   16: call [`rhp_log'] argc:0
   17: r96:SI=[r77:DI-0x24]
   18: r82:DI=sign_extend(r96:SI)
   19: r83:DI=[`rhp_sp_layers']
   20: si:DI=r82:DI
   21: di:DI=r83:DI
   22: ax:DI=call [`rhp_sp_lookup'] argc:0
   23: r97:DI=ax:DI
   24: [r77:DI-0x10]=r97:DI
   25: flags:CCZ=cmp([r77:DI-0x10],0)
   26: pc={(flags:CCZ!=0)?L36:pc}
" ]

	node [ id 10353 graphics [ fill "#d3d3d3" ] label "   27: NOTE_INSN_BASIC_BLOCK 4
   28: r98:SI=[r77:DI-0x24]
   29: dx:SI=r98:SI
   30: si:DI=`__FUNCTION__.14'
   31: di:DI=`*.LC96'
   32: ax:QI=0
   33: call [`rhp_log'] argc:0
   34: pc=L113
" ]

	node [ id 10354 graphics [ fill "#d3d3d3" ] label "   36: L36:
   37: NOTE_INSN_BASIC_BLOCK 5
   38: r99:DI=[r77:DI-0x10]
   39: r84:DI=[r99:DI+0x8]
   40: [r77:DI-0x18]=r84:DI
   41: flags:CCZ=cmp([r77:DI-0x18],0)
   42: pc={(flags:CCZ!=0)?L52:pc}
" ]

	node [ id 10355 graphics [ fill "#d3d3d3" ] label "   43: NOTE_INSN_BASIC_BLOCK 6
   44: r100:SI=[r77:DI-0x24]
   45: dx:SI=r100:SI
   46: si:DI=`__FUNCTION__.14'
   47: di:DI=`*.LC97'
   48: ax:QI=0
   49: call [`rhp_log'] argc:0
   50: pc=L113
" ]

	node [ id 10356 graphics [ fill "#d3d3d3" ] label "   52: L52:
   53: NOTE_INSN_BASIC_BLOCK 7
   54: r101:DI=[r77:DI-0x18]
   55: r85:DI=[r101:DI+0x8]
   56: flags:CCZ=cmp(r85:DI,0)
   57: pc={(flags:CCZ!=0)?L67:pc}
" ]

	node [ id 10357 graphics [ fill "#d3d3d3" ] label "   58: NOTE_INSN_BASIC_BLOCK 8
   59: r102:SI=[r77:DI-0x24]
   60: dx:SI=r102:SI
   61: si:DI=`__FUNCTION__.14'
   62: di:DI=`*.LC98'
   63: ax:QI=0
   64: call [`rhp_log'] argc:0
   65: pc=L113
" ]

	node [ id 10358 graphics [ fill "#d3d3d3" ] label "   67: L67:
   68: NOTE_INSN_BASIC_BLOCK 9
   69: [r77:DI-0x4]=0
   70: [r77:DI-0x8]=0
   71: pc=L103
" ]

	node [ id 10359 graphics [ fill "#d3d3d3" ] label "  110: NOTE_INSN_BASIC_BLOCK 12
" ]

	node [ id 10360 graphics [ fill "#d3d3d3" ] label "  113: L113:
  114: NOTE_INSN_BASIC_BLOCK 14
" ]

	edge [ source 10350 target 10352 graphics [ fill "#0000ff" ] ] 
	edge [ source 10352 target 10353 graphics [ fill "#0000ff" ] ] 
	edge [ source 10352 target 10354 graphics [ fill "#000000" ] ] 
	edge [ source 10353 target 10360 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 10354 target 10355 graphics [ fill "#0000ff" ] ] 
	edge [ source 10354 target 10356 graphics [ fill "#000000" ] ] 
	edge [ source 10355 target 10360 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 10356 target 10357 graphics [ fill "#0000ff" ] ] 
	edge [ source 10356 target 10358 graphics [ fill "#000000" ] ] 
	edge [ source 10357 target 10360 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 10358 target 10348 graphics [ fill "#000000" ] ] 
	edge [ source 10349 target 10348 graphics [ fill "#0000ff" ] ] 
	edge [ source 10348 target 10349 graphics [ fill "#000000" ] ] 
	edge [ source 10348 target 10359 graphics [ fill "#0000ff" ] ] 
	edge [ source 10359 target 10360 graphics [ fill "#0000ff" ] ] 
	edge [ source 10360 target 10351 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 48
	node [ id 10566 graphics [ fill "#ffffff" ] label "rhp_updatecrossingsforlayer ()
ENTRY" ]

	node [ id 10567 graphics [ fill "#ffffff" ] label "rhp_updatecrossingsforlayer ()
EXIT" ]

	node [ id 10568 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x4]=di:SI
    3: NOTE_INSN_FUNCTION_BEG
    6: r85:SI=[r77:DI-0x4]
    7: di:SI=r85:SI
    8: call [`rhp_updatenodepositions'] argc:0
   11: flags:CCNO=cmp([r77:DI-0x4],0)
   12: pc={(flags:CCNO&lt;=0)?L17:pc}
" ]

	node [ id 10569 graphics [ fill "#d3d3d3" ] label "   13: NOTE_INSN_BASIC_BLOCK 4
   14: r86:SI=[r77:DI-0x4]
   15: di:SI=r86:SI
   16: call [`rhp_updatecrossingsbetweenlayers'] argc:0
" ]

	node [ id 10570 graphics [ fill "#d3d3d3" ] label "   17: L17:
   18: NOTE_INSN_BASIC_BLOCK 5
   19: r82:SI=[`rhp_nlevels']
   20: {r83:SI=r82:SI-0x1;clobber flags:CC;}
   21: flags:CCGC=cmp([r77:DI-0x4],r83:SI)
   22: pc={(flags:CCGC&gt;=0)?L32:pc}
" ]

	node [ id 10571 graphics [ fill "#d3d3d3" ] label "   23: NOTE_INSN_BASIC_BLOCK 6
   24: r87:SI=[r77:DI-0x4]
   25: {r84:SI=r87:SI+0x1;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x4]+0x1
   26: di:SI=r84:SI
   27: call [`rhp_updatecrossingsbetweenlayers'] argc:0
   34: 0
" ]

	node [ id 10572 graphics [ fill "#d3d3d3" ] label "   32: L32:
   33: NOTE_INSN_BASIC_BLOCK 9
" ]

	edge [ source 10566 target 10568 graphics [ fill "#0000ff" ] ] 
	edge [ source 10568 target 10569 graphics [ fill "#0000ff" ] ] 
	edge [ source 10568 target 10570 graphics [ fill "#000000" ] ] 
	edge [ source 10569 target 10570 graphics [ fill "#0000ff" ] ] 
	edge [ source 10570 target 10571 graphics [ fill "#0000ff" ] ] 
	edge [ source 10570 target 10572 graphics [ fill "#000000" ] ] 
	edge [ source 10571 target 10572 graphics [ fill "#0000ff" ] ] 
	edge [ source 10572 target 10567 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 10692 graphics [ fill "#d3d3d3" ] label "  455: L455:
  456: NOTE_INSN_BASIC_BLOCK 50
  457: r240:DI=[r77:DI-0x30]
  458: r161:SI=[r240:DI]
  460: flags:CCGC=cmp([r77:DI-0x8],r161:SI)
  461: pc={(flags:CCGC&lt;0)?L459:pc}
" ]

	node [ id 10693 graphics [ fill "#d3d3d3" ] label "  459: L459:
  439: NOTE_INSN_BASIC_BLOCK 49
  440: r236:DI=[r77:DI-0x30]
  441: r156:DI=[r236:DI+0x8]
  442: r237:SI=[r77:DI-0x8]
  443: r157:DI=sign_extend(r237:SI)
  444: {r158:DI=r157:DI&lt;&lt;0x3;clobber flags:CC;}
  445: {r159:DI=r156:DI+r158:DI;clobber flags:CC;}
  446: r238:DI=[r159:DI]
  447: [r77:DI-0x38]=r238:DI
  448: r239:DI=[r77:DI-0x38]
  449: r160:SI=[r239:DI+0x4]
  450: si:SI=r160:SI
  451: di:DI=`*.LC82'
  452: ax:QI=0
  453: call [`rhp_log'] argc:0
  454: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
" ]

	node [ id 10694 graphics [ fill "#d3d3d3" ] label "  351: L351:
  352: NOTE_INSN_BASIC_BLOCK 39
  353: r225:DI=[r77:DI-0x38]
  354: r144:SI=[r225:DI+0x20]
  356: flags:CCGC=cmp([r77:DI-0xc],r144:SI)
  357: pc={(flags:CCGC&lt;0)?L355:pc}
" ]

	node [ id 10695 graphics [ fill "#d3d3d3" ] label "  355: L355:
  337: NOTE_INSN_BASIC_BLOCK 38
  338: r223:DI=[r77:DI-0x38]
  339: r138:DI=[r223:DI+0x30]
  340: r224:SI=[r77:DI-0xc]
  341: r139:DI=sign_extend(r224:SI)
  342: {r140:DI=r139:DI&lt;&lt;0x3;clobber flags:CC;}
  343: {r141:DI=r138:DI+r140:DI;clobber flags:CC;}
  344: r142:DI=[r141:DI]
  345: r143:SI=[r142:DI+0x4]
  346: si:SI=r143:SI
  347: di:DI=`*.LC82'
  348: ax:QI=0
  349: call [`rhp_log'] argc:0
  350: {[r77:DI-0xc]=[r77:DI-0xc]+0x1;clobber flags:CC;}
" ]

	node [ id 10696 graphics [ fill "#d3d3d3" ] label "  365: L365:
  366: NOTE_INSN_BASIC_BLOCK 41
  367: r226:DI=[r77:DI-0x30]
  368: r145:SI=[r226:DI]
  370: flags:CCGC=cmp([r77:DI-0x8],r145:SI)
  371: pc={(flags:CCGC&lt;0)?L369:pc}
" ]

	node [ id 10697 graphics [ fill "#d3d3d3" ] label "  369: L369:
  308: NOTE_INSN_BASIC_BLOCK 36
  309: r217:DI=[r77:DI-0x30]
  310: r131:DI=[r217:DI+0x8]
  311: r218:SI=[r77:DI-0x8]
  312: r132:DI=sign_extend(r218:SI)
  313: {r133:DI=r132:DI&lt;&lt;0x3;clobber flags:CC;}
  314: {r134:DI=r131:DI+r133:DI;clobber flags:CC;}
  315: r219:DI=[r134:DI]
  316: [r77:DI-0x38]=r219:DI
  317: r220:DI=[r77:DI-0x38]
  318: r135:SI=[r220:DI+0x20]
  319: r221:DI=[r77:DI-0x38]
  320: r136:SI=[r221:DI+0x4]
  321: cx:SI=r135:SI
  322: dx:SI=r136:SI
  323: si:DI=`__FUNCTION__.13'
  324: di:DI=`*.LC104'
  325: ax:QI=0
  326: call [`rhp_log'] argc:0
  327: r222:DI=[r77:DI-0x38]
  328: r137:SI=[r222:DI+0x20]
  331: flags:CCNO=cmp(r137:SI,0)
  332: pc={(flags:CCNO&lt;=0)?L358:pc}
" ]

	node [ id 10698 graphics [ fill "#d3d3d3" ] label "  333: NOTE_INSN_BASIC_BLOCK 37
  334: [r77:DI-0xc]=0
  335: pc=L351
" ]

	node [ id 10699 graphics [ fill "#d3d3d3" ] label "  358: L358:
  359: NOTE_INSN_BASIC_BLOCK 40
  360: si:DI=`*.LC83'
  361: di:DI=`*.LC81'
  362: ax:QI=0
  363: call [`rhp_log'] argc:0
  364: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
" ]

	node [ id 10700 graphics [ fill "#d3d3d3" ] label "  265: L265:
  266: NOTE_INSN_BASIC_BLOCK 32
  267: r210:DI=[r77:DI-0x30]
  268: r126:SI=[r210:DI]
  270: flags:CCGC=cmp([r77:DI-0x8],r126:SI)
  271: pc={(flags:CCGC&lt;0)?L269:pc}
" ]

	node [ id 10701 graphics [ fill "#d3d3d3" ] label "  269: L269:
  253: NOTE_INSN_BASIC_BLOCK 31
  254: r206:DI=[r77:DI-0x30]
  255: r122:DI=[r206:DI+0x8]
  256: r207:SI=[r77:DI-0x8]
  257: r123:DI=sign_extend(r207:SI)
  258: {r124:DI=r123:DI&lt;&lt;0x3;clobber flags:CC;}
  259: {r125:DI=r122:DI+r124:DI;clobber flags:CC;}
  260: r208:DI=[r125:DI]
  261: [r77:DI-0x38]=r208:DI
  262: r209:DI=[r77:DI-0x38]
  263: [r209:DI+0x40]=0
  264: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
" ]

	node [ id 10702 graphics [ fill "#d3d3d3" ] label "  176: L176:
  177: NOTE_INSN_BASIC_BLOCK 21
  178: r197:DI=[r77:DI-0x38]
  179: r112:SI=[r197:DI+0x20]
  181: flags:CCGC=cmp([r77:DI-0xc],r112:SI)
  182: pc={(flags:CCGC&lt;0)?L180:pc}
" ]

	node [ id 10703 graphics [ fill "#d3d3d3" ] label "  180: L180:
  166: NOTE_INSN_BASIC_BLOCK 20
  167: r195:DI=[r77:DI-0x38]
  168: r107:DI=[r195:DI+0x30]
  169: r196:SI=[r77:DI-0xc]
  170: r108:DI=sign_extend(r196:SI)
  171: {r109:DI=r108:DI&lt;&lt;0x3;clobber flags:CC;}
  172: {r110:DI=r107:DI+r109:DI;clobber flags:CC;}
  173: r111:DI=[r110:DI]
  174: [r111:DI+0x30]=0
  175: {[r77:DI-0xc]=[r77:DI-0xc]+0x1;clobber flags:CC;}
" ]

	node [ id 10704 graphics [ fill "#d3d3d3" ] label "  186: L186:
  187: NOTE_INSN_BASIC_BLOCK 23
  188: r198:DI=[r77:DI-0x30]
  189: r113:SI=[r198:DI]
  191: flags:CCGC=cmp([r77:DI-0x8],r113:SI)
  192: pc={(flags:CCGC&lt;0)?L190:pc}
" ]

	node [ id 10705 graphics [ fill "#d3d3d3" ] label "  190: L190:
  145: NOTE_INSN_BASIC_BLOCK 18
  146: r190:DI=[r77:DI-0x30]
  147: r102:DI=[r190:DI+0x8]
  148: r191:SI=[r77:DI-0x8]
  149: r103:DI=sign_extend(r191:SI)
  150: {r104:DI=r103:DI&lt;&lt;0x3;clobber flags:CC;}
  151: {r105:DI=r102:DI+r104:DI;clobber flags:CC;}
  152: r192:DI=[r105:DI]
  153: [r77:DI-0x38]=r192:DI
  154: r193:DI=[r77:DI-0x38]
  155: [r193:DI+0x48]=0
  156: r194:DI=[r77:DI-0x38]
  157: r106:SI=[r194:DI+0x20]
  160: flags:CCNO=cmp(r106:SI,0)
  161: pc={(flags:CCNO&lt;=0)?L183:pc}
" ]

	node [ id 10706 graphics [ fill "#d3d3d3" ] label "  162: NOTE_INSN_BASIC_BLOCK 19
  163: [r77:DI-0xc]=0
  164: pc=L176
" ]

	node [ id 10707 graphics [ fill "#d3d3d3" ] label "  183: L183:
  184: NOTE_INSN_BASIC_BLOCK 22
  185: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
" ]

	node [ id 10708 graphics [ fill "#d3d3d3" ] label "  134: L134:
  135: NOTE_INSN_BASIC_BLOCK 16
  136: r189:DI=[r77:DI-0x30]
  137: r101:SI=[r189:DI]
  139: flags:CCGC=cmp([r77:DI-0x8],r101:SI)
  140: pc={(flags:CCGC&lt;0)?L138:pc}
" ]

	node [ id 10709 graphics [ fill "#d3d3d3" ] label "  138: L138:
   70: NOTE_INSN_BASIC_BLOCK 10
   71: r174:DI=[r77:DI-0x30]
   72: r86:DI=[r174:DI+0x8]
   73: r175:SI=[r77:DI-0x8]
   74: r87:DI=sign_extend(r175:SI)
   75: {r88:DI=r87:DI&lt;&lt;0x3;clobber flags:CC;}
   76: {r89:DI=r86:DI+r88:DI;clobber flags:CC;}
   77: r176:DI=[r89:DI]
   78: [r77:DI-0x38]=r176:DI
   79: r177:DI=[r77:DI-0x38]
   80: r90:SI=[r177:DI+0x20]
   83: flags:CCGC=cmp(r90:SI,0x1)
   84: pc={(flags:CCGC&lt;=0)?L93:pc}
" ]

	node [ id 10710 graphics [ fill "#d3d3d3" ] label "   85: NOTE_INSN_BASIC_BLOCK 11
   86: r178:DI=[r77:DI-0x38]
   87: r91:SI=[r178:DI+0x20]
   88: r179:DI=[r77:DI-0x38]
   89: r92:DI=[r179:DI+0x30]
   90: si:SI=r91:SI
   91: di:DI=r92:DI
   92: call [`rhp_sortbydownnodeposition'] argc:0
" ]

	node [ id 10711 graphics [ fill "#d3d3d3" ] label "   93: L93:
   94: NOTE_INSN_BASIC_BLOCK 12
   95: r180:DI=[r77:DI-0x38]
   96: r93:SI=[r180:DI+0x20]
   99: flags:CCNO=cmp(r93:SI,0)
  100: pc={(flags:CCNO&lt;=0)?L128:pc}
" ]

	node [ id 10712 graphics [ fill "#d3d3d3" ] label "  101: NOTE_INSN_BASIC_BLOCK 13
  102: r181:SI=[r77:DI-0x44]
  103: r94:DI=sign_extend(r181:SI)
  104: r95:DI=[`rhp_sp_between_layers']
  105: si:DI=r94:DI
  106: di:DI=r95:DI
  107: ax:DI=call [`rhp_sp_lookup'] argc:0
  108: r182:DI=ax:DI
  109: [r77:DI-0x28]=r182:DI
  110: flags:CCZ=cmp([r77:DI-0x28],0)
  111: pc={(flags:CCZ==0)?L128:pc}
" ]

	node [ id 10713 graphics [ fill "#d3d3d3" ] label "  128: L128:
  129: NOTE_INSN_BASIC_BLOCK 15
  130: r188:DI=[r77:DI-0x38]
  131: r100:SI=[r188:DI+0x20]
  132: {[r77:DI-0x4]=[r77:DI-0x4]+r100:SI;clobber flags:CC;}
  133: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
" ]

	node [ id 10714 graphics [ fill "#d3d3d3" ] label "  112: NOTE_INSN_BASIC_BLOCK 14
  113: r183:DI=[r77:DI-0x28]
  114: r96:DI=[r183:DI+0x8]
  115: [r77:DI-0x40]=r96:DI
  116: r184:DI=[r77:DI-0x38]
  117: r97:SI=[r184:DI+0x20]
  118: r185:DI=[r77:DI-0x38]
  119: r98:DI=[r185:DI+0x30]
  120: r186:DI=[r77:DI-0x40]
  121: r99:DI=[r186:DI+0x8]
  122: r187:SI=[r77:DI-0x4]
  123: cx:SI=r187:SI
  124: dx:SI=r97:SI
  125: si:DI=r98:DI
  126: di:DI=r99:DI
  127: call [`rhp_add_edges_to_array'] argc:0
" ]



# function number 49
	node [ id 10715 graphics [ fill "#ffffff" ] label "rhp_updatecrossingsbetweenlayers ()
ENTRY" ]

	node [ id 10716 graphics [ fill "#ffffff" ] label "rhp_updatecrossingsbetweenlayers ()
EXIT" ]

	node [ id 10717 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x44]=di:SI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x20]=0
    7: [r77:DI-0x28]=0
    8: [r77:DI-0x30]=0
    9: [r77:DI-0x38]=0
   10: [r77:DI-0x40]=0
   11: [r77:DI-0x4]=0
   12: [r77:DI-0x8]=0
   13: [r77:DI-0xc]=0
   14: [r77:DI-0x18]=0
   15: r167:SI=[r77:DI-0x44]
   16: r82:DI=sign_extend(r167:SI)
   17: r83:DI=[`rhp_sp_layers']
   18: si:DI=r82:DI
   19: di:DI=r83:DI
   20: ax:DI=call [`rhp_sp_lookup'] argc:0
   21: r168:DI=ax:DI
   22: [r77:DI-0x20]=r168:DI
   23: flags:CCZ=cmp([r77:DI-0x20],0)
   24: pc={(flags:CCZ!=0)?L34:pc}
" ]

	node [ id 10718 graphics [ fill "#d3d3d3" ] label "   25: NOTE_INSN_BASIC_BLOCK 4
   26: r169:SI=[r77:DI-0x44]
   27: dx:SI=r169:SI
   28: si:DI=`__FUNCTION__.13'
   29: di:DI=`*.LC96'
   30: ax:QI=0
   31: call [`rhp_log'] argc:0
   32: pc=L516
" ]

	node [ id 10719 graphics [ fill "#d3d3d3" ] label "   34: L34:
   35: NOTE_INSN_BASIC_BLOCK 5
   36: r170:DI=[r77:DI-0x20]
   37: r84:DI=[r170:DI+0x8]
   38: [r77:DI-0x30]=r84:DI
   39: flags:CCZ=cmp([r77:DI-0x30],0)
   40: pc={(flags:CCZ!=0)?L50:pc}
" ]

	node [ id 10720 graphics [ fill "#d3d3d3" ] label "   41: NOTE_INSN_BASIC_BLOCK 6
   42: r171:SI=[r77:DI-0x44]
   43: dx:SI=r171:SI
   44: si:DI=`__FUNCTION__.13'
   45: di:DI=`*.LC97'
   46: ax:QI=0
   47: call [`rhp_log'] argc:0
   48: pc=L516
" ]

	node [ id 10721 graphics [ fill "#d3d3d3" ] label "   50: L50:
   51: NOTE_INSN_BASIC_BLOCK 7
   52: r172:DI=[r77:DI-0x30]
   53: r85:DI=[r172:DI+0x8]
   54: flags:CCZ=cmp(r85:DI,0)
   55: pc={(flags:CCZ!=0)?L65:pc}
" ]

	node [ id 10722 graphics [ fill "#d3d3d3" ] label "   56: NOTE_INSN_BASIC_BLOCK 8
   57: r173:SI=[r77:DI-0x44]
   58: dx:SI=r173:SI
   59: si:DI=`__FUNCTION__.13'
   60: di:DI=`*.LC98'
   61: ax:QI=0
   62: call [`rhp_log'] argc:0
   63: pc=L516
" ]

	node [ id 10723 graphics [ fill "#d3d3d3" ] label "   65: L65:
   66: NOTE_INSN_BASIC_BLOCK 9
   67: [r77:DI-0x8]=0
   68: pc=L134
" ]

	node [ id 10724 graphics [ fill "#d3d3d3" ] label "  141: NOTE_INSN_BASIC_BLOCK 17
  142: [r77:DI-0x8]=0
  143: pc=L186
" ]

	node [ id 10725 graphics [ fill "#d3d3d3" ] label "  193: NOTE_INSN_BASIC_BLOCK 24
  194: r199:SI=[r77:DI-0x44]
  195: {r114:SI=r199:SI-0x1;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x44]-0x1
  196: r115:DI=sign_extend(r114:SI)
  197: r116:DI=[`rhp_sp_layers']
  198: si:DI=r115:DI
  199: di:DI=r116:DI
  200: ax:DI=call [`rhp_sp_lookup'] argc:0
  201: r200:DI=ax:DI
  202: [r77:DI-0x20]=r200:DI
  203: flags:CCZ=cmp([r77:DI-0x20],0)
  204: pc={(flags:CCZ!=0)?L215:pc}
" ]

	node [ id 10726 graphics [ fill "#d3d3d3" ] label "  205: NOTE_INSN_BASIC_BLOCK 25
  206: r201:SI=[r77:DI-0x44]
  207: {r117:SI=r201:SI-0x1;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x44]-0x1
  208: dx:SI=r117:SI
  209: si:DI=`__FUNCTION__.13'
  210: di:DI=`*.LC96'
  211: ax:QI=0
  212: call [`rhp_log'] argc:0
  213: pc=L516
" ]

	node [ id 10727 graphics [ fill "#d3d3d3" ] label "  215: L215:
  216: NOTE_INSN_BASIC_BLOCK 26
  217: r202:DI=[r77:DI-0x20]
  218: r118:DI=[r202:DI+0x8]
  219: [r77:DI-0x30]=r118:DI
  220: flags:CCZ=cmp([r77:DI-0x30],0)
  221: pc={(flags:CCZ!=0)?L232:pc}
" ]

	node [ id 10728 graphics [ fill "#d3d3d3" ] label "  222: NOTE_INSN_BASIC_BLOCK 27
  223: r203:SI=[r77:DI-0x44]
  224: {r119:SI=r203:SI-0x1;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x44]-0x1
  225: dx:SI=r119:SI
  226: si:DI=`__FUNCTION__.13'
  227: di:DI=`*.LC97'
  228: ax:QI=0
  229: call [`rhp_log'] argc:0
  230: pc=L516
" ]

	node [ id 10729 graphics [ fill "#d3d3d3" ] label "  232: L232:
  233: NOTE_INSN_BASIC_BLOCK 28
  234: r204:DI=[r77:DI-0x30]
  235: r120:DI=[r204:DI+0x8]
  236: flags:CCZ=cmp(r120:DI,0)
  237: pc={(flags:CCZ!=0)?L248:pc}
" ]

	node [ id 10730 graphics [ fill "#d3d3d3" ] label "  238: NOTE_INSN_BASIC_BLOCK 29
  239: r205:SI=[r77:DI-0x44]
  240: {r121:SI=r205:SI-0x1;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x44]-0x1
  241: dx:SI=r121:SI
  242: si:DI=`__FUNCTION__.13'
  243: di:DI=`*.LC98'
  244: ax:QI=0
  245: call [`rhp_log'] argc:0
  246: pc=L516
" ]

	node [ id 10731 graphics [ fill "#d3d3d3" ] label "  248: L248:
  249: NOTE_INSN_BASIC_BLOCK 30
  250: [r77:DI-0x8]=0
  251: pc=L265
" ]

	node [ id 10732 graphics [ fill "#d3d3d3" ] label "  272: NOTE_INSN_BASIC_BLOCK 33
  273: r211:SI=[r77:DI-0x44]
  274: r127:DI=sign_extend(r211:SI)
  275: r128:DI=[`rhp_sp_layers']
  276: si:DI=r127:DI
  277: di:DI=r128:DI
  278: ax:DI=call [`rhp_sp_lookup'] argc:0
  279: r212:DI=ax:DI
  280: [r77:DI-0x20]=r212:DI
  281: flags:CCZ=cmp([r77:DI-0x20],0)
  282: pc={(flags:CCZ!=0)?L291:pc}
" ]

	node [ id 10733 graphics [ fill "#d3d3d3" ] label "  283: NOTE_INSN_BASIC_BLOCK 34
  284: r213:SI=[r77:DI-0x44]
  285: si:SI=r213:SI
  286: di:DI=`*.LC96'
  287: ax:QI=0
  288: call [`rhp_log'] argc:0
  289: pc=L516
" ]

	node [ id 10734 graphics [ fill "#d3d3d3" ] label "  291: L291:
  292: NOTE_INSN_BASIC_BLOCK 35
  293: r214:DI=[r77:DI-0x20]
  294: r129:DI=[r214:DI+0x8]
  295: [r77:DI-0x30]=r129:DI
  296: r215:DI=[r77:DI-0x30]
  297: r130:SI=[r215:DI]
  298: r216:SI=[r77:DI-0x44]
  299: cx:SI=r130:SI
  300: dx:SI=r216:SI
  301: si:DI=`__FUNCTION__.13'
  302: di:DI=`*.LC103'
  303: ax:QI=0
  304: call [`rhp_log'] argc:0
  305: [r77:DI-0x8]=0
  306: pc=L365
" ]

	node [ id 10735 graphics [ fill "#d3d3d3" ] label "  372: NOTE_INSN_BASIC_BLOCK 42
  373: r227:SI=[r77:DI-0x44]
  374: {r146:SI=r227:SI-0x1;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x44]-0x1
  375: r147:DI=sign_extend(r146:SI)
  376: r148:DI=[`rhp_sp_layers']
  377: si:DI=r147:DI
  378: di:DI=r148:DI
  379: ax:DI=call [`rhp_sp_lookup'] argc:0
  380: r228:DI=ax:DI
  381: [r77:DI-0x20]=r228:DI
  382: flags:CCZ=cmp([r77:DI-0x20],0)
  383: pc={(flags:CCZ!=0)?L393:pc}
" ]

	node [ id 10736 graphics [ fill "#d3d3d3" ] label "  384: NOTE_INSN_BASIC_BLOCK 43
  385: r229:SI=[r77:DI-0x44]
  386: {r149:SI=r229:SI-0x1;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x44]-0x1
  387: si:SI=r149:SI
  388: di:DI=`*.LC96'
  389: ax:QI=0
  390: call [`rhp_log'] argc:0
  391: pc=L516
" ]

	node [ id 10737 graphics [ fill "#d3d3d3" ] label "  393: L393:
  394: NOTE_INSN_BASIC_BLOCK 44
  395: r230:DI=[r77:DI-0x20]
  396: r150:DI=[r230:DI+0x8]
  397: [r77:DI-0x30]=r150:DI
  398: flags:CCZ=cmp([r77:DI-0x30],0)
  399: pc={(flags:CCZ!=0)?L409:pc}
" ]

	node [ id 10738 graphics [ fill "#d3d3d3" ] label "  400: NOTE_INSN_BASIC_BLOCK 45
  401: r231:SI=[r77:DI-0x44]
  402: {r151:SI=r231:SI-0x1;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x44]-0x1
  403: si:SI=r151:SI
  404: di:DI=`*.LC97'
  405: ax:QI=0
  406: call [`rhp_log'] argc:0
  407: pc=L516
" ]

	node [ id 10739 graphics [ fill "#d3d3d3" ] label "  409: L409:
  410: NOTE_INSN_BASIC_BLOCK 46
  411: r232:DI=[r77:DI-0x30]
  412: r152:DI=[r232:DI+0x8]
  413: flags:CCZ=cmp(r152:DI,0)
  414: pc={(flags:CCZ!=0)?L424:pc}
" ]

	node [ id 10740 graphics [ fill "#d3d3d3" ] label "  415: NOTE_INSN_BASIC_BLOCK 47
  416: r233:SI=[r77:DI-0x44]
  417: {r153:SI=r233:SI-0x1;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x44]-0x1
  418: si:SI=r153:SI
  419: di:DI=`*.LC98'
  420: ax:QI=0
  421: call [`rhp_log'] argc:0
  422: pc=L516
" ]

	node [ id 10741 graphics [ fill "#d3d3d3" ] label "  424: L424:
  425: NOTE_INSN_BASIC_BLOCK 48
  426: r234:DI=[r77:DI-0x30]
  427: r154:SI=[r234:DI]
  428: r235:SI=[r77:DI-0x44]
  429: {r155:SI=r235:SI-0x1;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x44]-0x1
  430: cx:SI=r154:SI
  431: dx:SI=r155:SI
  432: si:DI=`__FUNCTION__.13'
  433: di:DI=`*.LC105'
  434: ax:QI=0
  435: call [`rhp_log'] argc:0
  436: [r77:DI-0x8]=0
  437: pc=L455
" ]

	node [ id 10742 graphics [ fill "#d3d3d3" ] label "  462: NOTE_INSN_BASIC_BLOCK 51
  463: si:DI=`*.LC83'
  464: di:DI=`*.LC81'
  465: ax:QI=0
  466: call [`rhp_log'] argc:0
  467: r241:SI=[r77:DI-0x44]
  468: r162:DI=sign_extend(r241:SI)
  469: r163:DI=[`rhp_sp_between_layers']
  470: si:DI=r162:DI
  471: di:DI=r163:DI
  472: ax:DI=call [`rhp_sp_lookup'] argc:0
  473: r242:DI=ax:DI
  474: [r77:DI-0x28]=r242:DI
  475: flags:CCZ=cmp([r77:DI-0x28],0)
  476: pc={(flags:CCZ==0)?L496:pc}
" ]

	node [ id 10743 graphics [ fill "#d3d3d3" ] label "  477: NOTE_INSN_BASIC_BLOCK 52
  478: r243:DI=[r77:DI-0x28]
  479: r164:DI=[r243:DI+0x8]
  480: [r77:DI-0x40]=r164:DI
  481: r244:DI=[r77:DI-0x40]
  482: r165:SI=[r244:DI]
  483: r245:DI=[r77:DI-0x40]
  484: r166:DI=[r245:DI+0x8]
  485: dx:SI=0x1
  486: si:SI=r165:SI
  487: di:DI=r166:DI
  488: ax:DI=call [`rhp_count_inversions_down'] argc:0
  489: r246:DI=ax:DI
  490: [r77:DI-0x18]=r246:DI
  491: r247:DI=[r77:DI-0x40]
  492: r248:DI=[r77:DI-0x18]
  493: [r247:DI+0x10]=r248:DI
  494: pc=L504
" ]

	node [ id 10744 graphics [ fill "#d3d3d3" ] label "  496: L496:
  497: NOTE_INSN_BASIC_BLOCK 53
  498: r249:SI=[r77:DI-0x44]
  499: dx:SI=r249:SI
  500: si:DI=`__FUNCTION__.13'
  501: di:DI=`*.LC106'
  502: ax:QI=0
  503: call [`rhp_log'] argc:0
" ]

	node [ id 10745 graphics [ fill "#d3d3d3" ] label "  504: L504:
  505: NOTE_INSN_BASIC_BLOCK 54
  506: r250:SI=[r77:DI-0x44]
  507: r251:DI=[r77:DI-0x18]
  508: cx:SI=r250:SI
  509: dx:DI=r251:DI
  510: si:DI=`__FUNCTION__.13'
  511: di:DI=`*.LC107'
  512: ax:QI=0
  513: call [`rhp_log'] argc:0
" ]

	node [ id 10746 graphics [ fill "#d3d3d3" ] label "  516: L516:
  517: NOTE_INSN_BASIC_BLOCK 56
" ]

	edge [ source 10715 target 10717 graphics [ fill "#0000ff" ] ] 
	edge [ source 10717 target 10718 graphics [ fill "#0000ff" ] ] 
	edge [ source 10717 target 10719 graphics [ fill "#000000" ] ] 
	edge [ source 10718 target 10746 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 10719 target 10720 graphics [ fill "#0000ff" ] ] 
	edge [ source 10719 target 10721 graphics [ fill "#000000" ] ] 
	edge [ source 10720 target 10746 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 10721 target 10722 graphics [ fill "#0000ff" ] ] 
	edge [ source 10721 target 10723 graphics [ fill "#000000" ] ] 
	edge [ source 10722 target 10746 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 10723 target 10708 graphics [ fill "#000000" ] ] 
	edge [ source 10709 target 10710 graphics [ fill "#0000ff" ] ] 
	edge [ source 10709 target 10711 graphics [ fill "#000000" ] ] 
	edge [ source 10710 target 10711 graphics [ fill "#0000ff" ] ] 
	edge [ source 10711 target 10712 graphics [ fill "#0000ff" ] ] 
	edge [ source 10711 target 10713 graphics [ fill "#000000" ] ] 
	edge [ source 10712 target 10714 graphics [ fill "#0000ff" ] ] 
	edge [ source 10712 target 10713 graphics [ fill "#000000" ] ] 
	edge [ source 10714 target 10713 graphics [ fill "#0000ff" ] ] 
	edge [ source 10713 target 10708 graphics [ fill "#0000ff" ] ] 
	edge [ source 10708 target 10709 graphics [ fill "#000000" ] ] 
	edge [ source 10708 target 10724 graphics [ fill "#0000ff" ] ] 
	edge [ source 10724 target 10704 graphics [ fill "#000000" ] ] 
	edge [ source 10705 target 10706 graphics [ fill "#0000ff" ] ] 
	edge [ source 10705 target 10707 graphics [ fill "#000000" ] ] 
	edge [ source 10706 target 10702 graphics [ fill "#000000" ] ] 
	edge [ source 10703 target 10702 graphics [ fill "#0000ff" ] ] 
	edge [ source 10702 target 10703 graphics [ fill "#000000" ] ] 
	edge [ source 10702 target 10707 graphics [ fill "#0000ff" ] ] 
	edge [ source 10707 target 10704 graphics [ fill "#0000ff" ] ] 
	edge [ source 10704 target 10705 graphics [ fill "#000000" ] ] 
	edge [ source 10704 target 10725 graphics [ fill "#0000ff" ] ] 
	edge [ source 10725 target 10726 graphics [ fill "#0000ff" ] ] 
	edge [ source 10725 target 10727 graphics [ fill "#000000" ] ] 
	edge [ source 10726 target 10746 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 10727 target 10728 graphics [ fill "#0000ff" ] ] 
	edge [ source 10727 target 10729 graphics [ fill "#000000" ] ] 
	edge [ source 10728 target 10746 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 10729 target 10730 graphics [ fill "#0000ff" ] ] 
	edge [ source 10729 target 10731 graphics [ fill "#000000" ] ] 
	edge [ source 10730 target 10746 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 10731 target 10700 graphics [ fill "#000000" ] ] 
	edge [ source 10701 target 10700 graphics [ fill "#0000ff" ] ] 
	edge [ source 10700 target 10701 graphics [ fill "#000000" ] ] 
	edge [ source 10700 target 10732 graphics [ fill "#0000ff" ] ] 
	edge [ source 10732 target 10733 graphics [ fill "#0000ff" ] ] 
	edge [ source 10732 target 10734 graphics [ fill "#000000" ] ] 
	edge [ source 10733 target 10746 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 10734 target 10696 graphics [ fill "#000000" ] ] 
	edge [ source 10697 target 10698 graphics [ fill "#0000ff" ] ] 
	edge [ source 10697 target 10699 graphics [ fill "#000000" ] ] 
	edge [ source 10698 target 10694 graphics [ fill "#000000" ] ] 
	edge [ source 10695 target 10694 graphics [ fill "#0000ff" ] ] 
	edge [ source 10694 target 10695 graphics [ fill "#000000" ] ] 
	edge [ source 10694 target 10699 graphics [ fill "#0000ff" ] ] 
	edge [ source 10699 target 10696 graphics [ fill "#0000ff" ] ] 
	edge [ source 10696 target 10697 graphics [ fill "#000000" ] ] 
	edge [ source 10696 target 10735 graphics [ fill "#0000ff" ] ] 
	edge [ source 10735 target 10736 graphics [ fill "#0000ff" ] ] 
	edge [ source 10735 target 10737 graphics [ fill "#000000" ] ] 
	edge [ source 10736 target 10746 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 10737 target 10738 graphics [ fill "#0000ff" ] ] 
	edge [ source 10737 target 10739 graphics [ fill "#000000" ] ] 
	edge [ source 10738 target 10746 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 10739 target 10740 graphics [ fill "#0000ff" ] ] 
	edge [ source 10739 target 10741 graphics [ fill "#000000" ] ] 
	edge [ source 10740 target 10746 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 10741 target 10692 graphics [ fill "#000000" ] ] 
	edge [ source 10693 target 10692 graphics [ fill "#0000ff" ] ] 
	edge [ source 10692 target 10693 graphics [ fill "#000000" ] ] 
	edge [ source 10692 target 10742 graphics [ fill "#0000ff" ] ] 
	edge [ source 10742 target 10743 graphics [ fill "#0000ff" ] ] 
	edge [ source 10742 target 10744 graphics [ fill "#000000" ] ] 
	edge [ source 10743 target 10745 graphics [ fill "#000000" ] ] 
	edge [ source 10744 target 10745 graphics [ fill "#0000ff" ] ] 
	edge [ source 10745 target 10746 graphics [ fill "#0000ff" ] ] 
	edge [ source 10746 target 10716 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 50
	node [ id 11634 graphics [ fill "#ffffff" ] label "rhp_compare_down_edges ()
ENTRY" ]

	node [ id 11635 graphics [ fill "#ffffff" ] label "rhp_compare_down_edges ()
EXIT" ]

	node [ id 11636 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x28]=di:DI
    3: [r77:DI-0x30]=si:DI
    4: NOTE_INSN_FUNCTION_BEG
    7: [r77:DI-0x8]=0
    8: [r77:DI-0x10]=0
    9: [r77:DI-0x18]=0
   10: [r77:DI-0x20]=0
   11: r92:DI=[r77:DI-0x28]
   12: [r77:DI-0x8]=r92:DI
   13: r93:DI=[r77:DI-0x30]
   14: [r77:DI-0x10]=r93:DI
   15: r94:DI=[r77:DI-0x8]
   16: r95:DI=[r94:DI]
   17: [r77:DI-0x18]=r95:DI
   18: r96:DI=[r77:DI-0x10]
   19: r97:DI=[r96:DI]
   20: [r77:DI-0x20]=r97:DI
   21: r98:DI=[r77:DI-0x18]
   22: r82:DI=[r98:DI+0x28]
   23: r83:SI=[r82:DI+0x18]
   24: r99:DI=[r77:DI-0x20]
   25: r84:DI=[r99:DI+0x28]
   26: r85:SI=[r84:DI+0x18]
   27: flags:CCGC=cmp(r83:SI,r85:SI)
   28: pc={(flags:CCGC&lt;=0)?L33:pc}
" ]

	node [ id 11637 graphics [ fill "#d3d3d3" ] label "   29: NOTE_INSN_BASIC_BLOCK 4
   30: r90:SI=0x1
   31: pc=L50
" ]

	node [ id 11638 graphics [ fill "#d3d3d3" ] label "   33: L33:
   34: NOTE_INSN_BASIC_BLOCK 5
   35: r100:DI=[r77:DI-0x18]
   36: r86:DI=[r100:DI+0x28]
   37: r87:SI=[r86:DI+0x18]
   38: r101:DI=[r77:DI-0x20]
   39: r88:DI=[r101:DI+0x28]
   40: r89:SI=[r88:DI+0x18]
   41: flags:CCGC=cmp(r87:SI,r89:SI)
   42: pc={(flags:CCGC&gt;=0)?L47:pc}
" ]

	node [ id 11639 graphics [ fill "#d3d3d3" ] label "   43: NOTE_INSN_BASIC_BLOCK 6
   44: r90:SI=0xffffffffffffffff
   45: pc=L50
" ]

	node [ id 11640 graphics [ fill "#d3d3d3" ] label "   47: L47:
   48: NOTE_INSN_BASIC_BLOCK 7
   49: r90:SI=0
" ]

	node [ id 11641 graphics [ fill "#d3d3d3" ] label "   50: L50:
   51: NOTE_INSN_BASIC_BLOCK 8
   52: r91:SI=r90:SI
   56: ax:SI=r91:SI
   57: use ax:SI
" ]

	edge [ source 11634 target 11636 graphics [ fill "#0000ff" ] ] 
	edge [ source 11636 target 11637 graphics [ fill "#0000ff" ] ] 
	edge [ source 11636 target 11638 graphics [ fill "#000000" ] ] 
	edge [ source 11637 target 11641 graphics [ fill "#000000" ] ] 
	edge [ source 11638 target 11639 graphics [ fill "#0000ff" ] ] 
	edge [ source 11638 target 11640 graphics [ fill "#000000" ] ] 
	edge [ source 11639 target 11641 graphics [ fill "#000000" ] ] 
	edge [ source 11640 target 11641 graphics [ fill "#0000ff" ] ] 
	edge [ source 11641 target 11635 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 51
	node [ id 11770 graphics [ fill "#ffffff" ] label "rhp_sortbydownnodeposition ()
ENTRY" ]

	node [ id 11771 graphics [ fill "#ffffff" ] label "rhp_sortbydownnodeposition ()
EXIT" ]

	node [ id 11772 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x8]=di:DI
    3: [r77:DI-0xc]=si:SI
    4: NOTE_INSN_FUNCTION_BEG
    7: r83:SI=[r77:DI-0xc]
    8: r82:DI=sign_extend(r83:SI)
    9: r84:DI=[r77:DI-0x8]
   10: cx:DI=`rhp_compare_down_edges'
   11: dx:DI=0x8
   12: si:DI=r82:DI
   13: di:DI=r84:DI
   14: call [`qsort'] argc:0
   19: 0
" ]

	edge [ source 11770 target 11772 graphics [ fill "#0000ff" ] ] 
	edge [ source 11772 target 11771 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 11821 graphics [ fill "#d3d3d3" ] label "   44: L44:
   45: NOTE_INSN_BASIC_BLOCK 7
   47: r96:SI=[r77:DI-0x4]
   48: flags:CCGC=cmp(r96:SI,[r77:DI-0x24])
   49: pc={(flags:CCGC&lt;0)?L46:pc}
" ]

	node [ id 11822 graphics [ fill "#d3d3d3" ] label "   46: L46:
   28: NOTE_INSN_BASIC_BLOCK 6
   29: r91:SI=[r77:DI-0x4]
   30: r82:DI=sign_extend(r91:SI)
   31: {r83:DI=r82:DI&lt;&lt;0x3;clobber flags:CC;}
   32: r92:DI=[r77:DI-0x20]
   33: {r84:DI=r83:DI+r92:DI;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x20]+r83:DI
   34: r93:SI=[r77:DI-0x28]
   35: r94:SI=[r77:DI-0x4]
   36: {r85:SI=r93:SI+r94:SI;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x28]+[r77:DI-0x4]
   37: r86:DI=sign_extend(r85:SI)
   38: {r87:DI=r86:DI&lt;&lt;0x3;clobber flags:CC;}
   39: r95:DI=[r77:DI-0x18]
   40: {r88:DI=r87:DI+r95:DI;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x18]+r87:DI
   41: r89:DI=[r84:DI]
   42: [r88:DI]=r89:DI
   43: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]



# function number 52
	node [ id 11823 graphics [ fill "#ffffff" ] label "rhp_add_edges_to_array ()
ENTRY" ]

	node [ id 11824 graphics [ fill "#ffffff" ] label "rhp_add_edges_to_array ()
EXIT" ]

	node [ id 11825 graphics [ fill "#d3d3d3" ] label "    7: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x18]=di:DI
    3: [r77:DI-0x20]=si:DI
    4: [r77:DI-0x24]=dx:SI
    5: [r77:DI-0x28]=cx:SI
    6: NOTE_INSN_FUNCTION_BEG
    9: [r77:DI-0x4]=0
   12: flags:CCNO=cmp([r77:DI-0x24],0)
   13: pc={(flags:CCNO&gt;0)?L23:pc}
" ]

	node [ id 11826 graphics [ fill "#d3d3d3" ] label "   14: NOTE_INSN_BASIC_BLOCK 4
   15: r90:SI=[r77:DI-0x24]
   16: dx:SI=r90:SI
   17: si:DI=`__FUNCTION__.12'
   18: di:DI=`*.LC108'
   19: ax:QI=0
   20: call [`rhp_log'] argc:0
   21: pc=L53
" ]

	node [ id 11827 graphics [ fill "#d3d3d3" ] label "   23: L23:
   24: NOTE_INSN_BASIC_BLOCK 5
   25: [r77:DI-0x4]=0
   26: pc=L44
" ]

	node [ id 11828 graphics [ fill "#d3d3d3" ] label "   50: NOTE_INSN_BASIC_BLOCK 8
" ]

	node [ id 11829 graphics [ fill "#d3d3d3" ] label "   53: L53:
   54: NOTE_INSN_BASIC_BLOCK 10
" ]

	edge [ source 11823 target 11825 graphics [ fill "#0000ff" ] ] 
	edge [ source 11825 target 11826 graphics [ fill "#0000ff" ] ] 
	edge [ source 11825 target 11827 graphics [ fill "#000000" ] ] 
	edge [ source 11826 target 11829 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 11827 target 11821 graphics [ fill "#000000" ] ] 
	edge [ source 11822 target 11821 graphics [ fill "#0000ff" ] ] 
	edge [ source 11821 target 11822 graphics [ fill "#000000" ] ] 
	edge [ source 11821 target 11828 graphics [ fill "#0000ff" ] ] 
	edge [ source 11828 target 11829 graphics [ fill "#0000ff" ] ] 
	edge [ source 11829 target 11824 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 11971 graphics [ fill "#d3d3d3" ] label "   24: L24:
   25: NOTE_INSN_BASIC_BLOCK 5
   27: r88:SI=[r77:DI-0xc]
   28: flags:CCGC=cmp(r88:SI,[r77:DI-0x1c])
   29: pc={(flags:CCGC&lt;0)?L26:pc}
" ]

	node [ id 11972 graphics [ fill "#d3d3d3" ] label "   26: L26:
   13: NOTE_INSN_BASIC_BLOCK 4
   14: r85:SI=[r77:DI-0x20]
   15: r86:SI=[r77:DI-0xc]
   16: r87:DI=[r77:DI-0x18]
   17: dx:SI=r85:SI
   18: si:SI=r86:SI
   19: di:DI=r87:DI
   20: ax:DI=call [`rhp_insert_and_count_inversions_down'] argc:0
   21: r82:DI=ax:DI
   22: {[r77:DI-0x8]=[r77:DI-0x8]+r82:DI;clobber flags:CC;}
   23: {[r77:DI-0xc]=[r77:DI-0xc]+0x1;clobber flags:CC;}
" ]



# function number 53
	node [ id 11973 graphics [ fill "#ffffff" ] label "rhp_count_inversions_down ()
ENTRY" ]

	node [ id 11974 graphics [ fill "#ffffff" ] label "rhp_count_inversions_down ()
EXIT" ]

	node [ id 11975 graphics [ fill "#d3d3d3" ] label "    6: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x18]=di:DI
    3: [r77:DI-0x1c]=si:SI
    4: [r77:DI-0x20]=dx:SI
    5: NOTE_INSN_FUNCTION_BEG
    8: [r77:DI-0x8]=0
    9: [r77:DI-0xc]=0
   10: [r77:DI-0xc]=0x1
   11: pc=L24
" ]

	node [ id 11976 graphics [ fill "#d3d3d3" ] label "   30: NOTE_INSN_BASIC_BLOCK 6
   31: r83:DI=[r77:DI-0x8]
   34: r84:DI=r83:DI
   38: ax:DI=r84:DI
   39: use ax:DI
" ]

	edge [ source 11973 target 11975 graphics [ fill "#0000ff" ] ] 
	edge [ source 11975 target 11971 graphics [ fill "#000000" ] ] 
	edge [ source 11972 target 11971 graphics [ fill "#0000ff" ] ] 
	edge [ source 11971 target 11972 graphics [ fill "#000000" ] ] 
	edge [ source 11971 target 11976 graphics [ fill "#0000ff" ] ] 
	edge [ source 11976 target 11974 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 12073 graphics [ fill "#d3d3d3" ] label "  150: L150:
  151: NOTE_INSN_BASIC_BLOCK 9
  154: flags:CCGOC=cmp([r77:DI-0xc],0)
  155: pc={(flags:CCGOC&lt;0)?L171:pc}
" ]

	node [ id 12074 graphics [ fill "#d3d3d3" ] label "  156: NOTE_INSN_BASIC_BLOCK 10
  157: r179:SI=[r77:DI-0xc]
  158: r118:DI=sign_extend(r179:SI)
  159: {r119:DI=r118:DI&lt;&lt;0x3;clobber flags:CC;}
  160: r180:DI=[r77:DI-0x58]
  161: {r120:DI=r119:DI+r180:DI;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x58]+r119:DI
  162: r121:DI=[r120:DI]
  163: r122:DI=[r121:DI+0x28]
  164: r123:SI=[r122:DI+0x18]
  165: r181:DI=[r77:DI-0x18]
  166: r124:DI=[r181:DI+0x28]
  167: r125:SI=[r124:DI+0x18]
  169: flags:CCGC=cmp(r123:SI,r125:SI)
  170: pc={(flags:CCGC&gt;0)?L168:pc}
" ]

	node [ id 12075 graphics [ fill "#d3d3d3" ] label "  168: L168:
   71: NOTE_INSN_BASIC_BLOCK 8
   72: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
   73: r145:SI=[r77:DI-0xc]
   74: r89:DI=sign_extend(r145:SI)
   75: {r90:DI=r89:DI&lt;&lt;0x3;clobber flags:CC;}
   76: r146:DI=[r77:DI-0x58]
   77: {r91:DI=r90:DI+r146:DI;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x58]+r90:DI
   78: r147:DI=[r91:DI]
   79: [r77:DI-0x20]=r147:DI
   80: r148:DI=[r77:DI-0x18]
   81: [r77:DI-0x28]=r148:DI
   82: r149:DI=[r77:DI-0x20]
   83: r92:DI=[r149:DI+0x30]
   84: r150:SI=[r77:DI-0x60]
   85: r93:DI=sign_extend(r150:SI)
   86: {r94:DI=r92:DI+r93:DI;clobber flags:CC;}
   87: r151:DI=[r77:DI-0x20]
   88: [r151:DI+0x30]=r94:DI
   89: r152:DI=[r77:DI-0x28]
   90: r95:DI=[r152:DI+0x30]
   91: r153:SI=[r77:DI-0x60]
   92: r96:DI=sign_extend(r153:SI)
   93: {r97:DI=r95:DI+r96:DI;clobber flags:CC;}
   94: r154:DI=[r77:DI-0x28]
   95: [r154:DI+0x30]=r97:DI
   96: r155:DI=[r77:DI-0x20]
   97: r156:DI=[r155:DI+0x20]
   98: [r77:DI-0x30]=r156:DI
   99: r157:DI=[r77:DI-0x28]
  100: r158:DI=[r157:DI+0x20]
  101: [r77:DI-0x38]=r158:DI
  102: r159:DI=[r77:DI-0x20]
  103: r160:DI=[r159:DI+0x28]
  104: [r77:DI-0x40]=r160:DI
  105: r161:DI=[r77:DI-0x28]
  106: r162:DI=[r161:DI+0x28]
  107: [r77:DI-0x48]=r162:DI
  108: r163:DI=[r77:DI-0x30]
  109: r98:DI=[r163:DI+0x48]
  110: r164:SI=[r77:DI-0x60]
  111: r99:DI=sign_extend(r164:SI)
  112: {r100:DI=r98:DI+r99:DI;clobber flags:CC;}
  113: r165:DI=[r77:DI-0x30]
  114: [r165:DI+0x48]=r100:DI
  115: r166:DI=[r77:DI-0x38]
  116: r101:DI=[r166:DI+0x48]
  117: r167:SI=[r77:DI-0x60]
  118: r102:DI=sign_extend(r167:SI)
  119: {r103:DI=r101:DI+r102:DI;clobber flags:CC;}
  120: r168:DI=[r77:DI-0x38]
  121: [r168:DI+0x48]=r103:DI
  122: r169:DI=[r77:DI-0x40]
  123: r104:DI=[r169:DI+0x40]
  124: r170:SI=[r77:DI-0x60]
  125: r105:DI=sign_extend(r170:SI)
  126: {r106:DI=r104:DI+r105:DI;clobber flags:CC;}
  127: r171:DI=[r77:DI-0x40]
  128: [r171:DI+0x40]=r106:DI
  129: r172:DI=[r77:DI-0x48]
  130: r107:DI=[r172:DI+0x40]
  131: r173:SI=[r77:DI-0x60]
  132: r108:DI=sign_extend(r173:SI)
  133: {r109:DI=r107:DI+r108:DI;clobber flags:CC;}
  134: r174:DI=[r77:DI-0x48]
  135: [r174:DI+0x40]=r109:DI
  136: r175:SI=[r77:DI-0xc]
  137: r110:DI=sign_extend(r175:SI)
  138: {r111:DI=r110:DI&lt;&lt;0x3;clobber flags:CC;}
  139: r176:DI=[r77:DI-0x58]
  140: {r112:DI=r111:DI+r176:DI;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x58]+r111:DI
  141: r177:SI=[r77:DI-0xc]
  142: r113:DI=sign_extend(r177:SI)
  143: {r114:DI=r113:DI+0x1;clobber flags:CC;}
  144: {r115:DI=r114:DI&lt;&lt;0x3;clobber flags:CC;}
  145: r178:DI=[r77:DI-0x58]
  146: {r116:DI=r115:DI+r178:DI;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x58]+r115:DI
  147: r117:DI=[r112:DI]
  148: [r116:DI]=r117:DI
  149: {[r77:DI-0xc]=[r77:DI-0xc]-0x1;clobber flags:CC;}
" ]



# function number 54
	node [ id 12076 graphics [ fill "#ffffff" ] label "rhp_insert_and_count_inversions_down ()
ENTRY" ]

	node [ id 12077 graphics [ fill "#ffffff" ] label "rhp_insert_and_count_inversions_down ()
EXIT" ]

	node [ id 12078 graphics [ fill "#d3d3d3" ] label "    6: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x58]=di:DI
    3: [r77:DI-0x5c]=si:SI
    4: [r77:DI-0x60]=dx:SI
    5: NOTE_INSN_FUNCTION_BEG
    8: [r77:DI-0x8]=0
    9: [r77:DI-0xc]=0
   10: [r77:DI-0x18]=0
   11: [r77:DI-0x20]=0
   12: [r77:DI-0x28]=0
   13: [r77:DI-0x30]=0
   14: [r77:DI-0x38]=0
   15: [r77:DI-0x40]=0
   16: [r77:DI-0x48]=0
   17: [r77:DI-0x8]=0
   20: flags:CCNO=cmp([r77:DI-0x5c],0)
   21: pc={(flags:CCNO&gt;0)?L32:pc}
" ]

	node [ id 12079 graphics [ fill "#d3d3d3" ] label "   22: NOTE_INSN_BASIC_BLOCK 4
   23: r133:SI=[r77:DI-0x5c]
   24: dx:SI=r133:SI
   25: si:DI=`__FUNCTION__.11'
   26: di:DI=`*.LC109'
   27: ax:QI=0
   28: call [`rhp_log'] argc:0
   29: r131:DI=[r77:DI-0x8]
   30: pc=L191
" ]

	node [ id 12080 graphics [ fill "#d3d3d3" ] label "   32: L32:
   33: NOTE_INSN_BASIC_BLOCK 5
   37: r137:SI=[r77:DI-0x5c]
   38: {r136:SI=r137:SI-0x1;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x5c]-0x1
   39: [r77:DI-0xc]=r136:SI
   40: r138:SI=[r77:DI-0x5c]
   41: r82:DI=sign_extend(r138:SI)
   42: {r83:DI=r82:DI&lt;&lt;0x3;clobber flags:CC;}
   43: r139:DI=[r77:DI-0x58]
   44: {r84:DI=r83:DI+r139:DI;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x58]+r83:DI
   45: r140:DI=[r84:DI]
   46: [r77:DI-0x18]=r140:DI
   47: r141:SI=[r77:DI-0xc]
   48: r85:DI=sign_extend(r141:SI)
   49: {r86:DI=r85:DI&lt;&lt;0x3;clobber flags:CC;}
   50: r142:DI=[r77:DI-0x58]
   51: {r87:DI=r86:DI+r142:DI;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x58]+r86:DI
   52: r88:DI=[r87:DI]
   53: flags:CCZ=cmp(r88:DI,0)
   54: pc={(flags:CCZ!=0)?L67:pc}
" ]

	node [ id 12081 graphics [ fill "#d3d3d3" ] label "   55: NOTE_INSN_BASIC_BLOCK 6
   56: r143:SI=[r77:DI-0x5c]
   57: r144:SI=[r77:DI-0xc]
   58: cx:SI=r143:SI
   59: dx:SI=r144:SI
   60: si:DI=`__FUNCTION__.11'
   61: di:DI=`*.LC110'
   62: ax:QI=0
   63: call [`rhp_log'] argc:0
   64: r131:DI=[r77:DI-0x8]
   65: pc=L191
" ]

	node [ id 12082 graphics [ fill "#d3d3d3" ] label "   67: L67:
   68: NOTE_INSN_BASIC_BLOCK 7
   69: pc=L150
" ]

	node [ id 12083 graphics [ fill "#d3d3d3" ] label "  171: L171:
  172: NOTE_INSN_BASIC_BLOCK 11
  173: r182:SI=[r77:DI-0xc]
  174: r126:DI=sign_extend(r182:SI)
  175: {r127:DI=r126:DI+0x1;clobber flags:CC;}
  176: {r128:DI=r127:DI&lt;&lt;0x3;clobber flags:CC;}
  177: r183:DI=[r77:DI-0x58]
  178: {r129:DI=r128:DI+r183:DI;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x58]+r128:DI
  179: r184:DI=[r77:DI-0x18]
  180: [r129:DI]=r184:DI
  181: r185:DI=[r77:DI-0x18]
  182: r130:SI=[r185:DI+0x4]
  183: r186:DI=[r77:DI-0x8]
  184: cx:DI=r186:DI
  185: dx:SI=r130:SI
  186: si:DI=`__FUNCTION__.11'
  187: di:DI=`*.LC111'
  188: ax:QI=0
  189: call [`rhp_log'] argc:0
  190: r131:DI=[r77:DI-0x8]
" ]

	node [ id 12084 graphics [ fill "#d3d3d3" ] label "  191: L191:
  192: NOTE_INSN_BASIC_BLOCK 12
  193: r132:DI=r131:DI
  197: ax:DI=r132:DI
  198: use ax:DI
" ]

	edge [ source 12076 target 12078 graphics [ fill "#0000ff" ] ] 
	edge [ source 12078 target 12079 graphics [ fill "#0000ff" ] ] 
	edge [ source 12078 target 12080 graphics [ fill "#000000" ] ] 
	edge [ source 12079 target 12084 graphics [ fill "#000000" ] ] 
	edge [ source 12080 target 12081 graphics [ fill "#0000ff" ] ] 
	edge [ source 12080 target 12082 graphics [ fill "#000000" ] ] 
	edge [ source 12081 target 12084 graphics [ fill "#000000" ] ] 
	edge [ source 12082 target 12073 graphics [ fill "#000000" ] ] 
	edge [ source 12075 target 12073 graphics [ fill "#0000ff" ] ] 
	edge [ source 12073 target 12074 graphics [ fill "#0000ff" ] ] 
	edge [ source 12073 target 12083 graphics [ fill "#000000" ] ] 
	edge [ source 12074 target 12075 graphics [ fill "#000000" ] ] 
	edge [ source 12074 target 12083 graphics [ fill "#0000ff" ] ] 
	edge [ source 12083 target 12084 graphics [ fill "#0000ff" ] ] 
	edge [ source 12084 target 12077 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 12272 graphics [ fill "#d3d3d3" ] label "   77: L77:
   78: NOTE_INSN_BASIC_BLOCK 12
   79: r90:SI=[`rhp_nlevels']
   81: flags:CCGC=cmp([r77:DI-0x4],r90:SI)
   82: pc={(flags:CCGC&lt;0)?L80:pc}
" ]

	node [ id 12273 graphics [ fill "#d3d3d3" ] label "   80: L80:
   46: NOTE_INSN_BASIC_BLOCK 8
   47: r95:SI=[r77:DI-0x4]
   48: r86:DI=sign_extend(r95:SI)
   49: r87:DI=[`rhp_sp_between_layers']
   50: si:DI=r86:DI
   51: di:DI=r87:DI
   52: ax:DI=call [`rhp_sp_lookup'] argc:0
   53: r96:DI=ax:DI
   54: [r77:DI-0x18]=r96:DI
   55: flags:CCZ=cmp([r77:DI-0x18],0)
   56: pc={(flags:CCZ==0)?L66:pc}
" ]

	node [ id 12274 graphics [ fill "#d3d3d3" ] label "   57: NOTE_INSN_BASIC_BLOCK 9
   58: r97:DI=[r77:DI-0x18]
   59: r88:DI=[r97:DI+0x8]
   60: [r77:DI-0x20]=r88:DI
   61: r98:DI=[r77:DI-0x20]
   62: r89:DI=[r98:DI+0x10]
   63: {[r77:DI-0x10]=[r77:DI-0x10]+r89:DI;clobber flags:CC;}
   64: pc=L74
" ]

	node [ id 12275 graphics [ fill "#d3d3d3" ] label "   66: L66:
   67: NOTE_INSN_BASIC_BLOCK 10
   68: r99:SI=[r77:DI-0x4]
   69: dx:SI=r99:SI
   70: si:DI=`__FUNCTION__.10'
   71: di:DI=`*.LC114'
   72: ax:QI=0
   73: call [`rhp_log'] argc:0
" ]

	node [ id 12276 graphics [ fill "#d3d3d3" ] label "   74: L74:
   75: NOTE_INSN_BASIC_BLOCK 11
   76: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]



# function number 55
	node [ id 12277 graphics [ fill "#ffffff" ] label "rhp_numberofcrossings ()
ENTRY" ]

	node [ id 12278 graphics [ fill "#ffffff" ] label "rhp_numberofcrossings ()
EXIT" ]

	node [ id 12279 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x18]=0
    6: [r77:DI-0x20]=0
    7: [r77:DI-0x4]=0x1
    8: [r77:DI-0x10]=0
    9: r82:SI=[`rhp_nlevels']
   12: flags:CCGC=cmp(r82:SI,0x1)
   13: pc={(flags:CCGC&gt;0)?L24:pc}
" ]

	node [ id 12280 graphics [ fill "#d3d3d3" ] label "   14: NOTE_INSN_BASIC_BLOCK 4
   15: r83:SI=[`rhp_nlevels']
   16: dx:SI=r83:SI
   17: si:DI=`__FUNCTION__.10'
   18: di:DI=`*.LC112'
   19: ax:QI=0
   20: call [`rhp_log'] argc:0
   21: r93:DI=0
   22: pc=L95
" ]

	node [ id 12281 graphics [ fill "#d3d3d3" ] label "   24: L24:
   25: NOTE_INSN_BASIC_BLOCK 5
   26: r84:SI=[`rhp_number_of_edges']
   29: flags:CCGC=cmp(r84:SI,0x1)
   30: pc={(flags:CCGC&gt;0)?L41:pc}
" ]

	node [ id 12282 graphics [ fill "#d3d3d3" ] label "   31: NOTE_INSN_BASIC_BLOCK 6
   32: r85:SI=[`rhp_number_of_edges']
   33: dx:SI=r85:SI
   34: si:DI=`__FUNCTION__.10'
   35: di:DI=`*.LC113'
   36: ax:QI=0
   37: call [`rhp_log'] argc:0
   38: r93:DI=0
   39: pc=L95
" ]

	node [ id 12283 graphics [ fill "#d3d3d3" ] label "   41: L41:
   42: NOTE_INSN_BASIC_BLOCK 7
   43: [r77:DI-0x4]=0x1
   44: pc=L77
" ]

	node [ id 12284 graphics [ fill "#d3d3d3" ] label "   83: NOTE_INSN_BASIC_BLOCK 13
   84: r91:SI=[`rhp_number_of_edges']
   85: r92:SI=[`rhp_nlevels']
   86: r100:DI=[r77:DI-0x10]
   87: r8:SI=r91:SI
   88: cx:SI=r92:SI
   89: dx:DI=r100:DI
   90: si:DI=`__FUNCTION__.10'
   91: di:DI=`*.LC115'
   92: ax:QI=0
   93: call [`rhp_log'] argc:0
   94: r93:DI=[r77:DI-0x10]
" ]

	node [ id 12285 graphics [ fill "#d3d3d3" ] label "   95: L95:
   96: NOTE_INSN_BASIC_BLOCK 14
   97: r94:DI=r93:DI
  101: ax:DI=r94:DI
  102: use ax:DI
" ]

	edge [ source 12277 target 12279 graphics [ fill "#0000ff" ] ] 
	edge [ source 12279 target 12280 graphics [ fill "#0000ff" ] ] 
	edge [ source 12279 target 12281 graphics [ fill "#000000" ] ] 
	edge [ source 12280 target 12285 graphics [ fill "#000000" ] ] 
	edge [ source 12281 target 12282 graphics [ fill "#0000ff" ] ] 
	edge [ source 12281 target 12283 graphics [ fill "#000000" ] ] 
	edge [ source 12282 target 12285 graphics [ fill "#000000" ] ] 
	edge [ source 12283 target 12272 graphics [ fill "#000000" ] ] 
	edge [ source 12273 target 12274 graphics [ fill "#0000ff" ] ] 
	edge [ source 12273 target 12275 graphics [ fill "#000000" ] ] 
	edge [ source 12274 target 12276 graphics [ fill "#000000" ] ] 
	edge [ source 12275 target 12276 graphics [ fill "#0000ff" ] ] 
	edge [ source 12276 target 12272 graphics [ fill "#0000ff" ] ] 
	edge [ source 12272 target 12273 graphics [ fill "#000000" ] ] 
	edge [ source 12272 target 12284 graphics [ fill "#0000ff" ] ] 
	edge [ source 12284 target 12285 graphics [ fill "#0000ff" ] ] 
	edge [ source 12285 target 12278 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 12510 graphics [ fill "#d3d3d3" ] label "  146: L146:
  147: NOTE_INSN_BASIC_BLOCK 13
  148: r129:SI=[`rhp_nlevels']
  150: flags:CCGC=cmp([r77:DI-0x4],r129:SI)
  151: pc={(flags:CCGC&lt;0)?L149:pc}
" ]

	node [ id 12511 graphics [ fill "#d3d3d3" ] label "  149: L149:
   81: NOTE_INSN_BASIC_BLOCK 8
   82: r131:SI=[r77:DI-0x4]
   83: r106:DI=sign_extend(r131:SI)
   84: r107:DI=[`rhp_sp_layers']
   85: si:DI=r106:DI
   86: di:DI=r107:DI
   87: ax:DI=call [`rhp_sp_lookup'] argc:0
   88: r132:DI=ax:DI
   89: [r77:DI-0x18]=r132:DI
   90: flags:CCZ=cmp([r77:DI-0x18],0)
   91: pc={(flags:CCZ!=0)?L103:pc}
" ]

	node [ id 12512 graphics [ fill "#d3d3d3" ] label "   92: NOTE_INSN_BASIC_BLOCK 9
   93: r108:DI=[`rhp_sp_layers']
   94: r133:SI=[r77:DI-0x4]
   95: cx:DI=r108:DI
   96: dx:SI=r133:SI
   97: si:DI=`__FUNCTION__.9'
   98: di:DI=`*.LC117'
   99: ax:QI=0
  100: call [`rhp_log'] argc:0
  101: pc=L143
" ]

	node [ id 12513 graphics [ fill "#d3d3d3" ] label "  103: L103:
  104: NOTE_INSN_BASIC_BLOCK 10
  105: r134:DI=[r77:DI-0x18]
  106: r109:DI=[r134:DI+0x8]
  107: [r77:DI-0x20]=r109:DI
  108: r110:DI=[`rhp_best_crossings_order']
  109: r111:DI=[r110:DI+0x8]
  110: r135:SI=[r77:DI-0x4]
  111: r112:DI=sign_extend(r135:SI)
  112: {r113:DI=r112:DI&lt;&lt;0x2;clobber flags:CC;}
  113: {r114:DI=r111:DI+r113:DI;clobber flags:CC;}
  114: r136:DI=[r77:DI-0x20]
  115: r115:SI=[r136:DI]
  116: [r114:DI]=r115:SI
  117: r137:DI=[r77:DI-0x20]
  118: r116:SI=[r137:DI]
  119: flags:CCZ=cmp(r116:SI,0)
  120: pc={(flags:CCZ==0)?L143:pc}
" ]

	node [ id 12514 graphics [ fill "#d3d3d3" ] label "  143: L143:
  144: NOTE_INSN_BASIC_BLOCK 12
  145: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]

	node [ id 12515 graphics [ fill "#d3d3d3" ] label "  121: NOTE_INSN_BASIC_BLOCK 11
  122: r138:DI=[r77:DI-0x20]
  123: r117:SI=[r138:DI]
  124: r118:DI=sign_extend(r117:SI)
  125: {r119:DI=r118:DI&lt;&lt;0x3;clobber flags:CC;}
  126: r120:DI=[`rhp_best_crossings_order']
  127: r121:DI=[r120:DI+0x10]
  128: r139:SI=[r77:DI-0x4]
  129: r122:DI=sign_extend(r139:SI)
  130: {r123:DI=r122:DI&lt;&lt;0x3;clobber flags:CC;}
  131: {r124:DI=r121:DI+r123:DI;clobber flags:CC;}
  132: dx:SI=0xd6a
  133: si:DI=`__FUNCTION__.9'
  134: di:DI=r119:DI
  135: ax:DI=call [`rhp_malloc'] argc:0
  136: r125:DI=ax:DI
  137: [r124:DI]=r125:DI
  138: r140:DI=[r77:DI-0x20]
  139: r126:SI=[r140:DI]
  140: r127:DI=sign_extend(r126:SI)
  141: {r128:DI=r127:DI&lt;&lt;0x3;clobber flags:CC;}
  142: {[r77:DI-0x10]=[r77:DI-0x10]+r128:DI;clobber flags:CC;}
" ]



# function number 56
	node [ id 12516 graphics [ fill "#ffffff" ] label "rhp_order_init ()
ENTRY" ]

	node [ id 12517 graphics [ fill "#ffffff" ] label "rhp_order_init ()
EXIT" ]

	node [ id 12518 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x18]=0
    6: [r77:DI-0x20]=0
    7: [r77:DI-0x4]=0
    8: [r77:DI-0x10]=0
    9: r82:SI=[`rhp_nlevels']
   10: dx:SI=r82:SI
   11: si:DI=`__FUNCTION__.9'
   12: di:DI=`*.LC94'
   13: ax:QI=0
   14: call [`rhp_log'] argc:0
   15: dx:SI=0xd3c
   16: si:DI=`__FUNCTION__.9'
   17: di:DI=0x18
   18: ax:DI=call [`rhp_malloc'] argc:0
   19: r83:DI=ax:DI
   20: [`rhp_best_crossings_order']=r83:DI
   21: {[r77:DI-0x10]=[r77:DI-0x10]+0x18;clobber flags:CC;}
   22: r84:DI=[`rhp_best_crossings_order']
   23: r85:SI=[`rhp_nlevels']
   24: [r84:DI]=r85:SI
   25: r86:SI=[`rhp_nlevels']
   26: r87:DI=sign_extend(r86:SI)
   27: {r88:DI=r87:DI&lt;&lt;0x2;clobber flags:CC;}
   28: r89:DI=[`rhp_best_crossings_order']
   29: dx:SI=0xd43
   30: si:DI=`__FUNCTION__.9'
   31: di:DI=r88:DI
   32: ax:DI=call [`rhp_malloc'] argc:0
   33: r90:DI=ax:DI
   34: [r89:DI+0x8]=r90:DI
   35: r91:SI=[`rhp_nlevels']
   36: r92:DI=sign_extend(r91:SI)
   37: {r93:DI=r92:DI&lt;&lt;0x2;clobber flags:CC;}
   38: {[r77:DI-0x10]=[r77:DI-0x10]+r93:DI;clobber flags:CC;}
   39: r94:SI=[`rhp_nlevels']
   40: r95:DI=sign_extend(r94:SI)
   41: {r96:DI=r95:DI&lt;&lt;0x3;clobber flags:CC;}
   42: r97:DI=[`rhp_best_crossings_order']
   43: dx:SI=0xd47
   44: si:DI=`__FUNCTION__.9'
   45: di:DI=r96:DI
   46: ax:DI=call [`rhp_malloc'] argc:0
   47: r98:DI=ax:DI
   48: [r97:DI+0x10]=r98:DI
   49: r99:SI=[`rhp_nlevels']
   50: r100:DI=sign_extend(r99:SI)
   51: {r101:DI=r100:DI&lt;&lt;0x3;clobber flags:CC;}
   52: {[r77:DI-0x10]=[r77:DI-0x10]+r101:DI;clobber flags:CC;}
   53: r102:DI=[`rhp_sp_layers']
   54: di:DI=r102:DI
   55: ax:SI=call [`rhp_sp_has_data'] argc:0
   56: r103:SI=ax:SI
   57: flags:CCZ=cmp(r103:SI,0)
   58: pc={(flags:CCZ!=0)?L76:pc}
" ]

	node [ id 12519 graphics [ fill "#d3d3d3" ] label "   59: NOTE_INSN_BASIC_BLOCK 4
   60: r104:SI=[`rhp_nlevels']
   63: flags:CCGC=cmp(r104:SI,0x1)
   64: pc={(flags:CCGC&lt;=0)?L162:pc}
" ]

	node [ id 12520 graphics [ fill "#d3d3d3" ] label "   65: NOTE_INSN_BASIC_BLOCK 5
   66: r105:SI=[`rhp_nlevels']
   67: dx:SI=r105:SI
   68: si:DI=`__FUNCTION__.9'
   69: di:DI=`*.LC116'
   70: ax:QI=0
   71: call [`rhp_log'] argc:0
   74: pc=L162
" ]

	node [ id 12521 graphics [ fill "#d3d3d3" ] label "   76: L76:
   77: NOTE_INSN_BASIC_BLOCK 7
   78: [r77:DI-0x4]=0
   79: pc=L146
" ]

	node [ id 12522 graphics [ fill "#d3d3d3" ] label "  152: NOTE_INSN_BASIC_BLOCK 14
  153: call [`rhp_save_order'] argc:0
  154: r130:DI=[r77:DI-0x10]
  155: dx:DI=r130:DI
  156: si:DI=`__FUNCTION__.9'
  157: di:DI=`*.LC118'
  158: ax:QI=0
  159: call [`rhp_log'] argc:0
" ]

	node [ id 12523 graphics [ fill "#d3d3d3" ] label "  162: L162:
  163: NOTE_INSN_BASIC_BLOCK 16
" ]

	edge [ source 12516 target 12518 graphics [ fill "#0000ff" ] ] 
	edge [ source 12518 target 12519 graphics [ fill "#0000ff" ] ] 
	edge [ source 12518 target 12521 graphics [ fill "#000000" ] ] 
	edge [ source 12519 target 12520 graphics [ fill "#0000ff" ] ] 
	edge [ source 12519 target 12523 graphics [ fill "#000000" ] ] 
	edge [ source 12520 target 12523 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 12521 target 12510 graphics [ fill "#000000" ] ] 
	edge [ source 12511 target 12512 graphics [ fill "#0000ff" ] ] 
	edge [ source 12511 target 12513 graphics [ fill "#000000" ] ] 
	edge [ source 12512 target 12514 graphics [ fill "#000000" ] ] 
	edge [ source 12513 target 12515 graphics [ fill "#0000ff" ] ] 
	edge [ source 12513 target 12514 graphics [ fill "#000000" ] ] 
	edge [ source 12515 target 12514 graphics [ fill "#0000ff" ] ] 
	edge [ source 12514 target 12510 graphics [ fill "#0000ff" ] ] 
	edge [ source 12510 target 12511 graphics [ fill "#000000" ] ] 
	edge [ source 12510 target 12522 graphics [ fill "#0000ff" ] ] 
	edge [ source 12522 target 12523 graphics [ fill "#0000ff" ] ] 
	edge [ source 12523 target 12517 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 12760 graphics [ fill "#d3d3d3" ] label "   79: L79:
   80: NOTE_INSN_BASIC_BLOCK 8
   81: r115:DI=[r77:DI-0x18]
   82: r101:SI=[r115:DI]
   84: flags:CCGC=cmp([r77:DI-0x8],r101:SI)
   85: pc={(flags:CCGC&lt;0)?L83:pc}
" ]

	node [ id 12761 graphics [ fill "#d3d3d3" ] label "   83: L83:
   50: NOTE_INSN_BASIC_BLOCK 7
   51: r108:DI=[r77:DI-0x18]
   52: r87:DI=[r108:DI+0x8]
   53: r109:SI=[r77:DI-0x8]
   54: r88:DI=sign_extend(r109:SI)
   55: {r89:DI=r88:DI&lt;&lt;0x3;clobber flags:CC;}
   56: {r90:DI=r87:DI+r89:DI;clobber flags:CC;}
   57: r110:DI=[r90:DI]
   58: [r77:DI-0x20]=r110:DI
   59: r91:DI=[`rhp_best_crossings_order']
   60: r92:DI=[r91:DI+0x10]
   61: r111:SI=[r77:DI-0x4]
   62: r93:DI=sign_extend(r111:SI)
   63: {r94:DI=r93:DI&lt;&lt;0x3;clobber flags:CC;}
   64: {r95:DI=r92:DI+r94:DI;clobber flags:CC;}
   65: r96:DI=[r95:DI]
   66: r112:SI=[r77:DI-0x8]
   67: r97:DI=sign_extend(r112:SI)
   68: {r98:DI=r97:DI&lt;&lt;0x3;clobber flags:CC;}
   69: {r99:DI=r96:DI+r98:DI;clobber flags:CC;}
   70: r113:DI=[r77:DI-0x20]
   71: [r99:DI]=r113:DI
   72: r114:DI=[r77:DI-0x20]
   73: r100:SI=[r114:DI+0x4]
   74: si:SI=r100:SI
   75: di:DI=`*.LC82'
   76: ax:QI=0
   77: call [`rhp_log'] argc:0
   78: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
" ]

	node [ id 12762 graphics [ fill "#d3d3d3" ] label "   93: L93:
   94: NOTE_INSN_BASIC_BLOCK 11
   95: r102:SI=[`rhp_nlevels']
   97: flags:CCGC=cmp([r77:DI-0x4],r102:SI)
   98: pc={(flags:CCGC&lt;0)?L96:pc}
" ]

	node [ id 12763 graphics [ fill "#d3d3d3" ] label "   96: L96:
   16: NOTE_INSN_BASIC_BLOCK 4
   17: r103:SI=[r77:DI-0x4]
   18: r84:DI=sign_extend(r103:SI)
   19: r85:DI=[`rhp_sp_layers']
   20: si:DI=r84:DI
   21: di:DI=r85:DI
   22: ax:DI=call [`rhp_sp_lookup'] argc:0
   23: r104:DI=ax:DI
   24: [r77:DI-0x10]=r104:DI
   25: flags:CCZ=cmp([r77:DI-0x10],0)
   26: pc={(flags:CCZ!=0)?L36:pc}
" ]

	node [ id 12764 graphics [ fill "#d3d3d3" ] label "   27: NOTE_INSN_BASIC_BLOCK 5
   28: r105:SI=[r77:DI-0x4]
   29: dx:SI=r105:SI
   30: si:DI=`__FUNCTION__.8'
   31: di:DI=`*.LC52'
   32: ax:QI=0
   33: call [`rhp_log'] argc:0
   34: pc=L90
" ]

	node [ id 12765 graphics [ fill "#d3d3d3" ] label "   36: L36:
   37: NOTE_INSN_BASIC_BLOCK 6
   38: r106:DI=[r77:DI-0x10]
   39: r86:DI=[r106:DI+0x8]
   40: [r77:DI-0x18]=r86:DI
   41: r107:SI=[r77:DI-0x4]
   42: dx:SI=r107:SI
   43: si:DI=`__FUNCTION__.8'
   44: di:DI=`*.LC119'
   45: ax:QI=0
   46: call [`rhp_log'] argc:0
   47: [r77:DI-0x8]=0
   48: pc=L79
" ]

	node [ id 12766 graphics [ fill "#d3d3d3" ] label "   90: L90:
   91: NOTE_INSN_BASIC_BLOCK 10
   92: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]

	node [ id 12767 graphics [ fill "#d3d3d3" ] label "   86: NOTE_INSN_BASIC_BLOCK 9
   87: di:DI=`*.LC83'
   88: ax:QI=0
   89: call [`rhp_log'] argc:0
" ]



# function number 57
	node [ id 12768 graphics [ fill "#ffffff" ] label "rhp_save_order ()
ENTRY" ]

	node [ id 12769 graphics [ fill "#ffffff" ] label "rhp_save_order ()
EXIT" ]

	node [ id 12770 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x10]=0
    6: [r77:DI-0x18]=0
    7: [r77:DI-0x20]=0
    8: [r77:DI-0x4]=0
    9: [r77:DI-0x8]=0
   10: r82:DI=[`rhp_best_crossings_order']
   11: r83:SI=[`rhp_nlevels']
   12: [r82:DI]=r83:SI
   13: [r77:DI-0x4]=0
   14: pc=L93
" ]

	node [ id 12771 graphics [ fill "#d3d3d3" ] label "   99: NOTE_INSN_BASIC_BLOCK 12
  104: 0
" ]

	edge [ source 12768 target 12770 graphics [ fill "#0000ff" ] ] 
	edge [ source 12770 target 12762 graphics [ fill "#000000" ] ] 
	edge [ source 12763 target 12764 graphics [ fill "#0000ff" ] ] 
	edge [ source 12763 target 12765 graphics [ fill "#000000" ] ] 
	edge [ source 12764 target 12766 graphics [ fill "#000000" ] ] 
	edge [ source 12765 target 12760 graphics [ fill "#000000" ] ] 
	edge [ source 12761 target 12760 graphics [ fill "#0000ff" ] ] 
	edge [ source 12760 target 12761 graphics [ fill "#000000" ] ] 
	edge [ source 12760 target 12767 graphics [ fill "#0000ff" ] ] 
	edge [ source 12767 target 12766 graphics [ fill "#0000ff" ] ] 
	edge [ source 12766 target 12762 graphics [ fill "#0000ff" ] ] 
	edge [ source 12762 target 12763 graphics [ fill "#000000" ] ] 
	edge [ source 12762 target 12771 graphics [ fill "#0000ff" ] ] 
	edge [ source 12771 target 12769 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 12964 graphics [ fill "#d3d3d3" ] label "   74: L74:
   75: NOTE_INSN_BASIC_BLOCK 8
   76: r114:DI=[r77:DI-0x18]
   77: r100:SI=[r114:DI]
   79: flags:CCGC=cmp([r77:DI-0x8],r100:SI)
   80: pc={(flags:CCGC&lt;0)?L78:pc}
" ]

	node [ id 12965 graphics [ fill "#d3d3d3" ] label "   78: L78:
   48: NOTE_INSN_BASIC_BLOCK 7
   49: r87:DI=[`rhp_best_crossings_order']
   50: r88:DI=[r87:DI+0x10]
   51: r106:SI=[r77:DI-0x4]
   52: r89:DI=sign_extend(r106:SI)
   53: {r90:DI=r89:DI&lt;&lt;0x3;clobber flags:CC;}
   54: {r91:DI=r88:DI+r90:DI;clobber flags:CC;}
   55: r92:DI=[r91:DI]
   56: r107:SI=[r77:DI-0x8]
   57: r93:DI=sign_extend(r107:SI)
   58: {r94:DI=r93:DI&lt;&lt;0x3;clobber flags:CC;}
   59: {r95:DI=r92:DI+r94:DI;clobber flags:CC;}
   60: r108:DI=[r95:DI]
   61: [r77:DI-0x20]=r108:DI
   62: r109:DI=[r77:DI-0x18]
   63: r96:DI=[r109:DI+0x8]
   64: r110:SI=[r77:DI-0x8]
   65: r97:DI=sign_extend(r110:SI)
   66: {r98:DI=r97:DI&lt;&lt;0x3;clobber flags:CC;}
   67: {r99:DI=r96:DI+r98:DI;clobber flags:CC;}
   68: r111:DI=[r77:DI-0x20]
   69: [r99:DI]=r111:DI
   70: r112:DI=[r77:DI-0x20]
   71: r113:SI=[r77:DI-0x8]
   72: [r112:DI+0x18]=r113:SI
   73: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
" ]

	node [ id 12966 graphics [ fill "#d3d3d3" ] label "   84: L84:
   85: NOTE_INSN_BASIC_BLOCK 10
   86: r101:SI=[`rhp_nlevels']
   88: flags:CCGC=cmp([r77:DI-0x4],r101:SI)
   89: pc={(flags:CCGC&lt;0)?L87:pc}
" ]

	node [ id 12967 graphics [ fill "#d3d3d3" ] label "   87: L87:
   20: NOTE_INSN_BASIC_BLOCK 4
   21: r102:SI=[r77:DI-0x4]
   22: r84:DI=sign_extend(r102:SI)
   23: r85:DI=[`rhp_sp_layers']
   24: si:DI=r84:DI
   25: di:DI=r85:DI
   26: ax:DI=call [`rhp_sp_lookup'] argc:0
   27: r103:DI=ax:DI
   28: [r77:DI-0x10]=r103:DI
   29: flags:CCZ=cmp([r77:DI-0x10],0)
   30: pc={(flags:CCZ!=0)?L40:pc}
" ]

	node [ id 12968 graphics [ fill "#d3d3d3" ] label "   31: NOTE_INSN_BASIC_BLOCK 5
   32: r104:SI=[r77:DI-0x4]
   33: dx:SI=r104:SI
   34: si:DI=`__FUNCTION__.7'
   35: di:DI=`*.LC52'
   36: ax:QI=0
   37: call [`rhp_log'] argc:0
   38: pc=L81
" ]

	node [ id 12969 graphics [ fill "#d3d3d3" ] label "   40: L40:
   41: NOTE_INSN_BASIC_BLOCK 6
   42: r105:DI=[r77:DI-0x10]
   43: r86:DI=[r105:DI+0x8]
   44: [r77:DI-0x18]=r86:DI
   45: [r77:DI-0x8]=0
   46: pc=L74
" ]

	node [ id 12970 graphics [ fill "#d3d3d3" ] label "   81: L81:
   82: NOTE_INSN_BASIC_BLOCK 9
   83: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]



# function number 58
	node [ id 12971 graphics [ fill "#ffffff" ] label "rhp_restore_order ()
ENTRY" ]

	node [ id 12972 graphics [ fill "#ffffff" ] label "rhp_restore_order ()
EXIT" ]

	node [ id 12973 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x10]=0
    6: [r77:DI-0x18]=0
    7: [r77:DI-0x20]=0
    8: [r77:DI-0x4]=0
    9: [r77:DI-0x8]=0
   10: si:DI=`__FUNCTION__.7'
   11: di:DI=`*.LC120'
   12: ax:QI=0
   13: call [`rhp_log'] argc:0
   14: r82:DI=[`rhp_best_crossings_order']
   15: r83:SI=[`rhp_nlevels']
   16: [r82:DI]=r83:SI
   17: [r77:DI-0x4]=0
   18: pc=L84
" ]

	node [ id 12974 graphics [ fill "#d3d3d3" ] label "   90: NOTE_INSN_BASIC_BLOCK 11
   95: 0
" ]

	edge [ source 12971 target 12973 graphics [ fill "#0000ff" ] ] 
	edge [ source 12973 target 12966 graphics [ fill "#000000" ] ] 
	edge [ source 12967 target 12968 graphics [ fill "#0000ff" ] ] 
	edge [ source 12967 target 12969 graphics [ fill "#000000" ] ] 
	edge [ source 12968 target 12970 graphics [ fill "#000000" ] ] 
	edge [ source 12969 target 12964 graphics [ fill "#000000" ] ] 
	edge [ source 12965 target 12964 graphics [ fill "#0000ff" ] ] 
	edge [ source 12964 target 12965 graphics [ fill "#000000" ] ] 
	edge [ source 12964 target 12970 graphics [ fill "#0000ff" ] ] 
	edge [ source 12970 target 12966 graphics [ fill "#0000ff" ] ] 
	edge [ source 12966 target 12967 graphics [ fill "#000000" ] ] 
	edge [ source 12966 target 12974 graphics [ fill "#0000ff" ] ] 
	edge [ source 12974 target 12972 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 13151 graphics [ fill "#d3d3d3" ] label "   43: L43:
   14: NOTE_INSN_BASIC_BLOCK 4
   15: r83:SI=[`rhp_nlevels']
   16: {r84:SI=r83:SI-0x2;clobber flags:CC;}
   17: si:SI=r84:SI
   18: di:SI=0x1
   19: ax:SI=call [`rhp_barycenterupsweep'] argc:0
   20: r85:SI=ax:SI
   21: flags:CCZ=cmp(r85:SI,0)
   22: pc={(flags:CCZ==0)?L26:pc}
" ]

	node [ id 13152 graphics [ fill "#d3d3d3" ] label "   26: L26:
   27: NOTE_INSN_BASIC_BLOCK 6
   28: r86:SI=[`rhp_nlevels']
   29: {r87:SI=r86:SI-0x2;clobber flags:CC;}
   30: si:SI=r87:SI
   31: di:SI=0x1
   32: ax:SI=call [`rhp_barycenterdownsweep'] argc:0
   33: r88:SI=ax:SI
   34: flags:CCZ=cmp(r88:SI,0)
   35: pc={(flags:CCZ==0)?L39:pc}
" ]

	node [ id 13153 graphics [ fill "#d3d3d3" ] label "   39: L39:
   40: NOTE_INSN_BASIC_BLOCK 8
   41: ax:SI=call [`rhp_terminate'] argc:0
   42: r89:SI=ax:SI
   44: flags:CCZ=cmp(r89:SI,0)
   45: pc={(flags:CCZ==0)?L43:pc}
" ]



# function number 59
	node [ id 13154 graphics [ fill "#ffffff" ] label "rhp_barycenter ()
ENTRY" ]

	node [ id 13155 graphics [ fill "#ffffff" ] label "rhp_barycenter ()
EXIT" ]

	node [ id 13156 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x8]=0
    6: [`rhp_iter']=0
    7: [`rhp_maxiter']=0xff
    8: r82:DI=[`rhp_start_crossings']
    9: dx:DI=r82:DI
   10: si:DI=`__FUNCTION__.6'
   11: di:DI=`*.LC121'
   12: ax:QI=0
   13: call [`rhp_log'] argc:0
" ]

	node [ id 13157 graphics [ fill "#d3d3d3" ] label "   23: NOTE_INSN_BASIC_BLOCK 5
   24: pc=L96
" ]

	node [ id 13158 graphics [ fill "#d3d3d3" ] label "   36: NOTE_INSN_BASIC_BLOCK 7
   37: pc=L96
" ]

	node [ id 13159 graphics [ fill "#d3d3d3" ] label "   46: NOTE_INSN_BASIC_BLOCK 9
   47: r90:DI=[`rhp_start_crossings']
   48: r91:DI=[`rhp_crossings']
   49: cx:DI=r90:DI
   50: dx:DI=r91:DI
   51: si:DI=`__FUNCTION__.6'
   52: di:DI=`*.LC122'
   53: ax:QI=0
   54: call [`rhp_log'] argc:0
   55: r92:DI=[`rhp_start_crossings']
   56: flags:CCZ=cmp(r92:DI,0)
   57: pc={(flags:CCZ==0)?L79:pc}
" ]

	node [ id 13160 graphics [ fill "#d3d3d3" ] label "   58: NOTE_INSN_BASIC_BLOCK 10
   59: r93:DI=[`rhp_crossings']
   60: r98:DI=r93:DI
   61: {r98:DI=r98:DI&lt;&lt;0x2;clobber flags:CC;}
   62: {r98:DI=r98:DI+r93:DI;clobber flags:CC;}
      REG_EQUAL r93:DI*0x5
   63: {r99:DI=r98:DI&lt;&lt;0x2;clobber flags:CC;}
   64: {r98:DI=r98:DI+r99:DI;clobber flags:CC;}
      REG_EQUAL r93:DI*0x19
   65: {r100:DI=r98:DI&lt;&lt;0x2;clobber flags:CC;}
   66: r98:DI=r100:DI
      REG_EQUAL r93:DI*0x64
   67: r94:DI=r98:DI
   68: r95:DI=[`rhp_start_crossings']
   69: {r101:DI=r94:DI/r95:DI;r102:DI=r94:DI%r95:DI;clobber flags:CC;}
   70: [r77:DI-0x8]=r101:DI
   74: r106:DI=0x64
   75: {r105:DI=r106:DI-[r77:DI-0x8];clobber flags:CC;}
   76: [r77:DI-0x8]=r105:DI
   77: pc=L82
" ]

	node [ id 13161 graphics [ fill "#d3d3d3" ] label "   79: L79:
   80: NOTE_INSN_BASIC_BLOCK 11
   81: [r77:DI-0x8]=0
" ]

	node [ id 13162 graphics [ fill "#d3d3d3" ] label "   82: L82:
   83: NOTE_INSN_BASIC_BLOCK 12
   84: r96:DI=[`rhp_crossings']
   85: r97:DI=[`rhp_start_crossings']
   86: r107:DI=[r77:DI-0x8]
   87: r8:DI=r96:DI
   88: cx:DI=r97:DI
   89: dx:DI=r107:DI
   90: si:DI=`__FUNCTION__.6'
   91: di:DI=`*.LC123'
   92: ax:QI=0
   93: call [`rhp_log'] argc:0
" ]

	node [ id 13163 graphics [ fill "#d3d3d3" ] label "   96: L96:
   97: NOTE_INSN_BASIC_BLOCK 14
" ]

	edge [ source 13154 target 13156 graphics [ fill "#0000ff" ] ] 
	edge [ source 13156 target 13151 graphics [ fill "#0000ff" ] ] 
	edge [ source 13151 target 13157 graphics [ fill "#0000ff" ] ] 
	edge [ source 13151 target 13152 graphics [ fill "#000000" ] ] 
	edge [ source 13157 target 13163 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 13152 target 13158 graphics [ fill "#0000ff" ] ] 
	edge [ source 13152 target 13153 graphics [ fill "#000000" ] ] 
	edge [ source 13158 target 13163 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 13153 target 13151 graphics [ fill "#0000ff" ] ] 
	edge [ source 13153 target 13159 graphics [ fill "#0000ff" ] ] 
	edge [ source 13159 target 13160 graphics [ fill "#0000ff" ] ] 
	edge [ source 13159 target 13161 graphics [ fill "#000000" ] ] 
	edge [ source 13160 target 13162 graphics [ fill "#000000" ] ] 
	edge [ source 13161 target 13162 graphics [ fill "#0000ff" ] ] 
	edge [ source 13162 target 13163 graphics [ fill "#0000ff" ] ] 
	edge [ source 13163 target 13155 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 60
	node [ id 13366 graphics [ fill "#ffffff" ] label "rhp_terminate ()
ENTRY" ]

	node [ id 13367 graphics [ fill "#ffffff" ] label "rhp_terminate ()
EXIT" ]

	node [ id 13368 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x8]=0
    6: [r77:DI-0x18]=0
    7: [r77:DI-0x1c]=0
    8: [r77:DI-0xc]=0
    9: ax:DI=call [`rhp_numberofcrossings'] argc:0
   10: r114:DI=ax:DI
   11: [r77:DI-0x18]=r114:DI
   12: r82:SI=[`rhp_iter']
   13: {r83:SI=r82:SI+0x1;clobber flags:CC;}
   14: [`rhp_iter']=r83:SI
   15: r84:DI=[`rhp_crossings']
   16: r115:DI=[r77:DI-0x18]
   17: cx:DI=r115:DI
   18: dx:DI=r84:DI
   19: si:DI=`__FUNCTION__.5'
   20: di:DI=`*.LC124'
   21: ax:QI=0
   22: call [`rhp_log'] argc:0
   23: r85:DI=[`rhp_crossings']
   24: flags:CCGC=cmp([r77:DI-0x18],r85:DI)
   25: pc={(flags:CCGC&gt;=0)?L33:pc}
" ]

	node [ id 13369 graphics [ fill "#d3d3d3" ] label "   26: NOTE_INSN_BASIC_BLOCK 4
   27: [r77:DI-0xc]=0x1
   28: r86:SI=[`rhp_improvements']
   29: {r87:SI=r86:SI+0x1;clobber flags:CC;}
   30: [`rhp_improvements']=r87:SI
   31: pc=L39
" ]

	node [ id 13370 graphics [ fill "#d3d3d3" ] label "   33: L33:
   34: NOTE_INSN_BASIC_BLOCK 5
   35: [r77:DI-0xc]=0
   36: r88:SI=[`rhp_notimprovements']
   37: {r89:SI=r88:SI+0x1;clobber flags:CC;}
   38: [`rhp_notimprovements']=r89:SI
" ]

	node [ id 13371 graphics [ fill "#d3d3d3" ] label "   39: L39:
   40: NOTE_INSN_BASIC_BLOCK 6
   41: r90:DI=[`rhp_getlayoutdata']
   42: flags:CCZ=cmp(r90:DI,0)
   43: pc={(flags:CCZ==0)?L114:pc}
" ]

	node [ id 13372 graphics [ fill "#d3d3d3" ] label "   44: NOTE_INSN_BASIC_BLOCK 7
   45: r91:DI=[`rhp_crossings']
   46: flags:CCZ=cmp(r91:DI,0)
   47: pc={(flags:CCZ==0)?L70:pc}
" ]

	node [ id 13373 graphics [ fill "#d3d3d3" ] label "   48: NOTE_INSN_BASIC_BLOCK 8
   49: r116:DI=[r77:DI-0x18]
   50: r117:DI=r116:DI
   51: {r117:DI=r117:DI&lt;&lt;0x2;clobber flags:CC;}
   52: {r117:DI=r117:DI+r116:DI;clobber flags:CC;}
      REG_EQUAL r116:DI*0x5
   53: {r118:DI=r117:DI&lt;&lt;0x2;clobber flags:CC;}
   54: {r117:DI=r117:DI+r118:DI;clobber flags:CC;}
      REG_EQUAL r116:DI*0x19
   55: {r119:DI=r117:DI&lt;&lt;0x2;clobber flags:CC;}
   56: r117:DI=r119:DI
      REG_EQUAL r116:DI*0x64
   57: r92:DI=r117:DI
   58: r93:DI=[`rhp_crossings']
   59: {r120:DI=r92:DI/r93:DI;r121:DI=r92:DI%r93:DI;clobber flags:CC;}
   60: r94:DI=r120:DI
   61: [r77:DI-0x8]=r94:DI
   65: r125:DI=0x64
   66: {r124:DI=r125:DI-[r77:DI-0x8];clobber flags:CC;}
   67: [r77:DI-0x8]=r124:DI
   68: pc=L73
" ]

	node [ id 13374 graphics [ fill "#d3d3d3" ] label "   70: L70:
   71: NOTE_INSN_BASIC_BLOCK 9
   72: [r77:DI-0x8]=0
" ]

	node [ id 13375 graphics [ fill "#d3d3d3" ] label "   73: L73:
   74: NOTE_INSN_BASIC_BLOCK 10
   75: r95:DI=[`rhp_getlayoutdata']
   76: r96:SI=[`rhp_notimprovements']
   77: r97:SI=[`rhp_improvements']
   78: r98:DI=[`rhp_crossings']
   79: r99:DI=r98:DI
   80: r100:DI=[r77:DI-0x18]
   81: r101:SI=[`rhp_maxiter']
   82: r102:SI=[`rhp_iter']
   83: r126:SI=[r77:DI-0xc]
   84: r127:DI=[r77:DI-0x8]
   85: [pre sp:DI+=0xfffffffffffffff8]=r96:SI
      REG_ARGS_SIZE 0x8
   86: [pre sp:DI+=0xfffffffffffffff8]=r97:SI
      REG_ARGS_SIZE 0x10
   87: r9:SI=r126:SI
   88: r8:DI=r127:DI
   89: cx:DI=r99:DI
   90: dx:DI=r100:DI
   91: si:SI=r101:SI
   92: di:SI=r102:SI
   93: ax:SI=call [r95:DI] argc:0x10
   94: {sp:DI=sp:DI+0x10;clobber flags:CC;}
      REG_ARGS_SIZE 0
   95: r128:SI=ax:SI
   96: [r77:DI-0x1c]=r128:SI
   97: flags:CCZ=cmp([r77:DI-0x1c],0)
   98: pc={(flags:CCZ==0)?L114:pc}
" ]

	node [ id 13376 graphics [ fill "#d3d3d3" ] label "   99: NOTE_INSN_BASIC_BLOCK 11
  100: r129:DI=[r77:DI-0x18]
  101: r130:SI=[r77:DI-0x1c]
  102: cx:DI=r129:DI
  103: dx:SI=r130:SI
  104: si:DI=`__FUNCTION__.5'
  105: di:DI=`*.LC125'
  106: ax:QI=0
  107: call [`rhp_log'] argc:0
  108: call [`rhp_save_order'] argc:0
  109: r131:DI=[r77:DI-0x18]
  110: [`rhp_crossings']=r131:DI
  111: r112:SI=0x1
  112: pc=L194
" ]

	node [ id 13377 graphics [ fill "#d3d3d3" ] label "  114: L114:
  115: NOTE_INSN_BASIC_BLOCK 12
  116: flags:CCZ=cmp([r77:DI-0x18],0)
  117: pc={(flags:CCZ==0)?L122:pc}
" ]

	node [ id 13378 graphics [ fill "#d3d3d3" ] label "  118: NOTE_INSN_BASIC_BLOCK 13
  119: r103:DI=[`rhp_crossings']
  120: flags:CCZ=cmp(r103:DI,0)
  121: pc={(flags:CCZ!=0)?L138:pc}
" ]

	node [ id 13379 graphics [ fill "#d3d3d3" ] label "  122: L122:
  123: NOTE_INSN_BASIC_BLOCK 14
  124: r104:DI=[`rhp_crossings']
  125: r132:DI=[r77:DI-0x18]
  126: cx:DI=r104:DI
  127: dx:DI=r132:DI
  128: si:DI=`__FUNCTION__.5'
  129: di:DI=`*.LC126'
  130: ax:QI=0
  131: call [`rhp_log'] argc:0
  132: call [`rhp_save_order'] argc:0
  133: r133:DI=[r77:DI-0x18]
  134: [`rhp_crossings']=r133:DI
  135: r112:SI=0x1
  136: pc=L194
" ]

	node [ id 13380 graphics [ fill "#d3d3d3" ] label "  138: L138:
  139: NOTE_INSN_BASIC_BLOCK 15
  140: r105:DI=[`rhp_crossings']
  141: flags:CCGC=cmp([r77:DI-0x18],r105:DI)
  142: pc={(flags:CCGC&gt;=0)?L169:pc}
" ]

	node [ id 13381 graphics [ fill "#d3d3d3" ] label "  143: NOTE_INSN_BASIC_BLOCK 16
  144: call [`rhp_save_order'] argc:0
  145: r134:DI=[r77:DI-0x18]
  146: [`rhp_crossings']=r134:DI
  147: r106:DI=[`rhp_crossings']
  148: flags:CCZ=cmp(r106:DI,0)
  149: pc={(flags:CCZ!=0)?L154:pc}
" ]

	node [ id 13382 graphics [ fill "#d3d3d3" ] label "  150: NOTE_INSN_BASIC_BLOCK 17
  151: r112:SI=0x1
  152: pc=L194
" ]

	node [ id 13383 graphics [ fill "#d3d3d3" ] label "  154: L154:
  155: NOTE_INSN_BASIC_BLOCK 18
  156: r107:SI=[`rhp_iter']
  157: r108:SI=[`rhp_maxiter']
  158: flags:CCGC=cmp(r107:SI,r108:SI)
  159: pc={(flags:CCGC&lt;=0)?L164:pc}
" ]

	node [ id 13384 graphics [ fill "#d3d3d3" ] label "  160: NOTE_INSN_BASIC_BLOCK 19
  161: r112:SI=0x1
  162: pc=L194
" ]

	node [ id 13385 graphics [ fill "#d3d3d3" ] label "  164: L164:
  165: NOTE_INSN_BASIC_BLOCK 20
  166: r112:SI=0
  167: pc=L194
" ]

	node [ id 13386 graphics [ fill "#d3d3d3" ] label "  169: L169:
  170: NOTE_INSN_BASIC_BLOCK 21
  171: r109:DI=[`rhp_crossings']
  172: flags:CCZ=cmp([r77:DI-0x18],r109:DI)
  173: pc={(flags:CCZ==0)?L178:pc}
" ]

	node [ id 13387 graphics [ fill "#d3d3d3" ] label "  174: NOTE_INSN_BASIC_BLOCK 22
  175: call [`rhp_restore_order'] argc:0
  176: pc=L181
" ]

	node [ id 13388 graphics [ fill "#d3d3d3" ] label "  178: L178:
  179: NOTE_INSN_BASIC_BLOCK 23
  180: call [`rhp_save_order'] argc:0
" ]

	node [ id 13389 graphics [ fill "#d3d3d3" ] label "  181: L181:
  182: NOTE_INSN_BASIC_BLOCK 24
  183: r110:SI=[`rhp_iter']
  184: r111:SI=[`rhp_maxiter']
  185: flags:CCGC=cmp(r110:SI,r111:SI)
  186: pc={(flags:CCGC&lt;=0)?L191:pc}
" ]

	node [ id 13390 graphics [ fill "#d3d3d3" ] label "  187: NOTE_INSN_BASIC_BLOCK 25
  188: r112:SI=0x1
  189: pc=L194
" ]

	node [ id 13391 graphics [ fill "#d3d3d3" ] label "  191: L191:
  192: NOTE_INSN_BASIC_BLOCK 26
  193: r112:SI=0
" ]

	node [ id 13392 graphics [ fill "#d3d3d3" ] label "  194: L194:
  195: NOTE_INSN_BASIC_BLOCK 27
  196: r113:SI=r112:SI
  200: ax:SI=r113:SI
  201: use ax:SI
" ]

	edge [ source 13366 target 13368 graphics [ fill "#0000ff" ] ] 
	edge [ source 13368 target 13369 graphics [ fill "#0000ff" ] ] 
	edge [ source 13368 target 13370 graphics [ fill "#000000" ] ] 
	edge [ source 13369 target 13371 graphics [ fill "#000000" ] ] 
	edge [ source 13370 target 13371 graphics [ fill "#0000ff" ] ] 
	edge [ source 13371 target 13372 graphics [ fill "#0000ff" ] ] 
	edge [ source 13371 target 13377 graphics [ fill "#000000" ] ] 
	edge [ source 13372 target 13373 graphics [ fill "#0000ff" ] ] 
	edge [ source 13372 target 13374 graphics [ fill "#000000" ] ] 
	edge [ source 13373 target 13375 graphics [ fill "#000000" ] ] 
	edge [ source 13374 target 13375 graphics [ fill "#0000ff" ] ] 
	edge [ source 13375 target 13376 graphics [ fill "#0000ff" ] ] 
	edge [ source 13375 target 13377 graphics [ fill "#000000" ] ] 
	edge [ source 13376 target 13392 graphics [ fill "#000000" ] ] 
	edge [ source 13377 target 13379 graphics [ fill "#000000" ] ] 
	edge [ source 13377 target 13378 graphics [ fill "#0000ff" ] ] 
	edge [ source 13378 target 13379 graphics [ fill "#0000ff" ] ] 
	edge [ source 13378 target 13380 graphics [ fill "#000000" ] ] 
	edge [ source 13379 target 13392 graphics [ fill "#000000" ] ] 
	edge [ source 13380 target 13381 graphics [ fill "#0000ff" ] ] 
	edge [ source 13380 target 13386 graphics [ fill "#000000" ] ] 
	edge [ source 13381 target 13382 graphics [ fill "#0000ff" ] ] 
	edge [ source 13381 target 13383 graphics [ fill "#000000" ] ] 
	edge [ source 13382 target 13392 graphics [ fill "#000000" ] ] 
	edge [ source 13383 target 13384 graphics [ fill "#0000ff" ] ] 
	edge [ source 13383 target 13385 graphics [ fill "#000000" ] ] 
	edge [ source 13384 target 13392 graphics [ fill "#000000" ] ] 
	edge [ source 13385 target 13392 graphics [ fill "#000000" ] ] 
	edge [ source 13386 target 13387 graphics [ fill "#0000ff" ] ] 
	edge [ source 13386 target 13388 graphics [ fill "#000000" ] ] 
	edge [ source 13387 target 13389 graphics [ fill "#000000" ] ] 
	edge [ source 13388 target 13389 graphics [ fill "#0000ff" ] ] 
	edge [ source 13389 target 13390 graphics [ fill "#0000ff" ] ] 
	edge [ source 13389 target 13391 graphics [ fill "#000000" ] ] 
	edge [ source 13390 target 13392 graphics [ fill "#000000" ] ] 
	edge [ source 13391 target 13392 graphics [ fill "#0000ff" ] ] 
	edge [ source 13392 target 13367 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 61
	node [ id 13825 graphics [ fill "#ffffff" ] label "rhp_end_of_iteration ()
ENTRY" ]

	node [ id 13826 graphics [ fill "#ffffff" ] label "rhp_end_of_iteration ()
EXIT" ]

	node [ id 13827 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: r82:SI=0
    8: r83:SI=r82:SI
   12: ax:SI=r83:SI
   13: use ax:SI
" ]

	edge [ source 13825 target 13827 graphics [ fill "#0000ff" ] ] 
	edge [ source 13827 target 13826 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 13876 graphics [ fill "#d3d3d3" ] label "   47: L47:
   48: NOTE_INSN_BASIC_BLOCK 9
   50: r91:SI=[r77:DI-0x4]
   51: flags:CCGC=cmp(r91:SI,[r77:DI-0x18])
   52: pc={(flags:CCGC&lt;0)?L49:pc}
" ]

	node [ id 13877 graphics [ fill "#d3d3d3" ] label "   49: L49:
   13: NOTE_INSN_BASIC_BLOCK 4
   14: [r77:DI-0x8]=0
   15: r86:SI=[r77:DI-0x4]
   16: si:SI=0
   17: di:SI=r86:SI
   18: ax:SI=call [`rhp_barycenterweights'] argc:0
   19: r87:SI=ax:SI
   20: [r77:DI-0x8]=r87:SI
   21: flags:CCZ=cmp([r77:DI-0x8],0)
   22: pc={(flags:CCZ==0)?L28:pc}
" ]

	node [ id 13878 graphics [ fill "#d3d3d3" ] label "   23: NOTE_INSN_BASIC_BLOCK 5
   24: r88:SI=[r77:DI-0x4]
   25: si:SI=0
   26: di:SI=r88:SI
   27: call [`rhp_barycenterweights_adjust'] argc:0
" ]

	node [ id 13879 graphics [ fill "#d3d3d3" ] label "   28: L28:
   29: NOTE_INSN_BASIC_BLOCK 6
   30: r89:SI=[r77:DI-0x4]
   31: di:SI=r89:SI
   32: call [`rhp_layersort'] argc:0
   33: r90:SI=[r77:DI-0x4]
   34: di:SI=r90:SI
   35: call [`rhp_updatecrossingsforlayer'] argc:0
   36: ax:SI=call [`rhp_end_of_iteration'] argc:0
   37: r82:SI=ax:SI
   38: flags:CCZ=cmp(r82:SI,0)
   39: pc={(flags:CCZ==0)?L44:pc}
" ]

	node [ id 13880 graphics [ fill "#d3d3d3" ] label "   44: L44:
   45: NOTE_INSN_BASIC_BLOCK 8
   46: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]



# function number 62
	node [ id 13881 graphics [ fill "#ffffff" ] label "rhp_barycenterupsweep ()
ENTRY" ]

	node [ id 13882 graphics [ fill "#ffffff" ] label "rhp_barycenterupsweep ()
EXIT" ]

	node [ id 13883 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x14]=di:SI
    3: [r77:DI-0x18]=si:SI
    4: NOTE_INSN_FUNCTION_BEG
    7: [r77:DI-0x4]=0
    8: [r77:DI-0x8]=0
    9: r85:SI=[r77:DI-0x14]
   10: [r77:DI-0x4]=r85:SI
   11: pc=L47
" ]

	node [ id 13884 graphics [ fill "#d3d3d3" ] label "   40: NOTE_INSN_BASIC_BLOCK 7
   41: r83:SI=0x1
   42: pc=L55
" ]

	node [ id 13885 graphics [ fill "#d3d3d3" ] label "   53: NOTE_INSN_BASIC_BLOCK 10
   54: r83:SI=0
" ]

	node [ id 13886 graphics [ fill "#d3d3d3" ] label "   55: L55:
   56: NOTE_INSN_BASIC_BLOCK 11
   57: r84:SI=r83:SI
   61: ax:SI=r84:SI
   62: use ax:SI
" ]

	edge [ source 13881 target 13883 graphics [ fill "#0000ff" ] ] 
	edge [ source 13883 target 13876 graphics [ fill "#000000" ] ] 
	edge [ source 13877 target 13878 graphics [ fill "#0000ff" ] ] 
	edge [ source 13877 target 13879 graphics [ fill "#000000" ] ] 
	edge [ source 13878 target 13879 graphics [ fill "#0000ff" ] ] 
	edge [ source 13879 target 13884 graphics [ fill "#0000ff" ] ] 
	edge [ source 13879 target 13880 graphics [ fill "#000000" ] ] 
	edge [ source 13884 target 13886 graphics [ fill "#000000" ] ] 
	edge [ source 13880 target 13876 graphics [ fill "#0000ff" ] ] 
	edge [ source 13876 target 13877 graphics [ fill "#000000" ] ] 
	edge [ source 13876 target 13885 graphics [ fill "#0000ff" ] ] 
	edge [ source 13885 target 13886 graphics [ fill "#0000ff" ] ] 
	edge [ source 13886 target 13882 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 14063 graphics [ fill "#d3d3d3" ] label "   47: L47:
   48: NOTE_INSN_BASIC_BLOCK 9
   49: r92:SI=[r77:DI-0x14]
   50: {r83:SI=r92:SI-0x1;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x14]-0x1
   52: flags:CCGC=cmp([r77:DI-0x4],r83:SI)
   53: pc={(flags:CCGC&gt;=0)?L51:pc}
" ]

	node [ id 14064 graphics [ fill "#d3d3d3" ] label "   51: L51:
   13: NOTE_INSN_BASIC_BLOCK 4
   14: [r77:DI-0x8]=0
   15: r87:SI=[r77:DI-0x4]
   16: si:SI=0x1
   17: di:SI=r87:SI
   18: ax:SI=call [`rhp_barycenterweights'] argc:0
   19: r88:SI=ax:SI
   20: [r77:DI-0x8]=r88:SI
   21: flags:CCZ=cmp([r77:DI-0x8],0)
   22: pc={(flags:CCZ==0)?L28:pc}
" ]

	node [ id 14065 graphics [ fill "#d3d3d3" ] label "   23: NOTE_INSN_BASIC_BLOCK 5
   24: r89:SI=[r77:DI-0x4]
   25: si:SI=0x1
   26: di:SI=r89:SI
   27: call [`rhp_barycenterweights_adjust'] argc:0
" ]

	node [ id 14066 graphics [ fill "#d3d3d3" ] label "   28: L28:
   29: NOTE_INSN_BASIC_BLOCK 6
   30: r90:SI=[r77:DI-0x4]
   31: di:SI=r90:SI
   32: call [`rhp_layersort'] argc:0
   33: r91:SI=[r77:DI-0x4]
   34: di:SI=r91:SI
   35: call [`rhp_updatecrossingsforlayer'] argc:0
   36: ax:SI=call [`rhp_end_of_iteration'] argc:0
   37: r82:SI=ax:SI
   38: flags:CCZ=cmp(r82:SI,0)
   39: pc={(flags:CCZ==0)?L44:pc}
" ]

	node [ id 14067 graphics [ fill "#d3d3d3" ] label "   44: L44:
   45: NOTE_INSN_BASIC_BLOCK 8
   46: {[r77:DI-0x4]=[r77:DI-0x4]-0x1;clobber flags:CC;}
" ]



# function number 63
	node [ id 14068 graphics [ fill "#ffffff" ] label "rhp_barycenterdownsweep ()
ENTRY" ]

	node [ id 14069 graphics [ fill "#ffffff" ] label "rhp_barycenterdownsweep ()
EXIT" ]

	node [ id 14070 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x14]=di:SI
    3: [r77:DI-0x18]=si:SI
    4: NOTE_INSN_FUNCTION_BEG
    7: [r77:DI-0x4]=0
    8: [r77:DI-0x8]=0
    9: r86:SI=[r77:DI-0x18]
   10: [r77:DI-0x4]=r86:SI
   11: pc=L47
" ]

	node [ id 14071 graphics [ fill "#d3d3d3" ] label "   40: NOTE_INSN_BASIC_BLOCK 7
   41: r84:SI=0x1
   42: pc=L56
" ]

	node [ id 14072 graphics [ fill "#d3d3d3" ] label "   54: NOTE_INSN_BASIC_BLOCK 10
   55: r84:SI=0
" ]

	node [ id 14073 graphics [ fill "#d3d3d3" ] label "   56: L56:
   57: NOTE_INSN_BASIC_BLOCK 11
   58: r85:SI=r84:SI
   62: ax:SI=r85:SI
   63: use ax:SI
" ]

	edge [ source 14068 target 14070 graphics [ fill "#0000ff" ] ] 
	edge [ source 14070 target 14063 graphics [ fill "#000000" ] ] 
	edge [ source 14064 target 14065 graphics [ fill "#0000ff" ] ] 
	edge [ source 14064 target 14066 graphics [ fill "#000000" ] ] 
	edge [ source 14065 target 14066 graphics [ fill "#0000ff" ] ] 
	edge [ source 14066 target 14071 graphics [ fill "#0000ff" ] ] 
	edge [ source 14066 target 14067 graphics [ fill "#000000" ] ] 
	edge [ source 14071 target 14073 graphics [ fill "#000000" ] ] 
	edge [ source 14067 target 14063 graphics [ fill "#0000ff" ] ] 
	edge [ source 14063 target 14064 graphics [ fill "#000000" ] ] 
	edge [ source 14063 target 14072 graphics [ fill "#0000ff" ] ] 
	edge [ source 14072 target 14073 graphics [ fill "#0000ff" ] ] 
	edge [ source 14073 target 14069 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 14250 graphics [ fill "#d3d3d3" ] label "   78: L78:
   79: NOTE_INSN_BASIC_BLOCK 9
   80: r114:DI=[r77:DI-0x18]
   81: r97:SI=[r114:DI]
   83: flags:CCGC=cmp([r77:DI-0x4],r97:SI)
   84: pc={(flags:CCGC&lt;0)?L82:pc}
" ]

	node [ id 14251 graphics [ fill "#d3d3d3" ] label "   82: L82:
   51: NOTE_INSN_BASIC_BLOCK 6
   52: r109:DI=[r77:DI-0x18]
   53: r86:DI=[r109:DI+0x8]
   54: r110:SI=[r77:DI-0x4]
   55: r87:DI=sign_extend(r110:SI)
   56: {r88:DI=r87:DI&lt;&lt;0x3;clobber flags:CC;}
   57: {r89:DI=r86:DI+r88:DI;clobber flags:CC;}
   58: r90:DI=[r89:DI]
   59: r111:SI=[r77:DI-0x28]
   60: si:SI=r111:SI
   61: di:DI=r90:DI
   62: call [`rhp_node_weight'] argc:0
   63: r112:DI=[r77:DI-0x18]
   64: r91:DI=[r112:DI+0x8]
   65: r113:SI=[r77:DI-0x4]
   66: r92:DI=sign_extend(r113:SI)
   67: {r93:DI=r92:DI&lt;&lt;0x3;clobber flags:CC;}
   68: {r94:DI=r91:DI+r93:DI;clobber flags:CC;}
   69: r95:DI=[r94:DI]
   70: r96:SI=[r95:DI+0x38]
   71: flags:CCZ=cmp(r96:SI,0xffffffffffffffff)
   72: pc={(flags:CCZ!=0)?L75:pc}
" ]

	node [ id 14252 graphics [ fill "#d3d3d3" ] label "   73: NOTE_INSN_BASIC_BLOCK 7
   74: {[r77:DI-0x8]=[r77:DI-0x8]+0x1;clobber flags:CC;}
" ]

	node [ id 14253 graphics [ fill "#d3d3d3" ] label "   75: L75:
   76: NOTE_INSN_BASIC_BLOCK 8
   77: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
" ]



# function number 64
	node [ id 14254 graphics [ fill "#ffffff" ] label "rhp_barycenterweights ()
ENTRY" ]

	node [ id 14255 graphics [ fill "#ffffff" ] label "rhp_barycenterweights ()
EXIT" ]

	node [ id 14256 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x24]=di:SI
    3: [r77:DI-0x28]=si:SI
    4: NOTE_INSN_FUNCTION_BEG
    7: [r77:DI-0x10]=0
    8: [r77:DI-0x18]=0
    9: [r77:DI-0x4]=0
   10: [r77:DI-0x8]=0
   11: r102:SI=[r77:DI-0x24]
   12: r82:DI=sign_extend(r102:SI)
   13: r83:DI=[`rhp_sp_layers']
   14: si:DI=r82:DI
   15: di:DI=r83:DI
   16: ax:DI=call [`rhp_sp_lookup'] argc:0
   17: r103:DI=ax:DI
   18: [r77:DI-0x10]=r103:DI
   19: flags:CCZ=cmp([r77:DI-0x10],0)
   20: pc={(flags:CCZ!=0)?L31:pc}
" ]

	node [ id 14257 graphics [ fill "#d3d3d3" ] label "   21: NOTE_INSN_BASIC_BLOCK 4
   22: r104:SI=[r77:DI-0x24]
   23: dx:SI=r104:SI
   24: si:DI=`__FUNCTION__.4'
   25: di:DI=`*.LC53'
   26: ax:QI=0
   27: call [`rhp_log'] argc:0
   28: r100:SI=0
   29: pc=L112
" ]

	node [ id 14258 graphics [ fill "#d3d3d3" ] label "   31: L31:
   32: NOTE_INSN_BASIC_BLOCK 5
   33: r105:DI=[r77:DI-0x10]
   34: r84:DI=[r105:DI+0x8]
   35: [r77:DI-0x18]=r84:DI
   36: r106:DI=[r77:DI-0x18]
   37: r85:SI=[r106:DI]
   38: r107:SI=[r77:DI-0x28]
   39: r108:SI=[r77:DI-0x24]
   40: r8:SI=r107:SI
   41: cx:SI=r108:SI
   42: dx:SI=r85:SI
   43: si:DI=`__FUNCTION__.4'
   44: di:DI=`*.LC127'
   45: ax:QI=0
   46: call [`rhp_log'] argc:0
   47: [r77:DI-0x8]=0
   48: [r77:DI-0x4]=0
   49: pc=L78
" ]

	node [ id 14259 graphics [ fill "#d3d3d3" ] label "   85: NOTE_INSN_BASIC_BLOCK 10
   86: flags:CCZ=cmp([r77:DI-0x8],0)
   87: pc={(flags:CCZ==0)?L106:pc}
" ]

	node [ id 14260 graphics [ fill "#d3d3d3" ] label "   88: NOTE_INSN_BASIC_BLOCK 11
   89: r115:DI=[r77:DI-0x18]
   90: r98:SI=[r115:DI]
   91: r99:SI=[`rhp_iter']
   92: r116:SI=[r77:DI-0x24]
   93: r117:SI=[r77:DI-0x8]
   94: {sp:DI=sp:DI-0x8;clobber flags:CC;}
      REG_ARGS_SIZE 0x8
   95: r118:SI=[r77:DI-0x28]
   96: [pre sp:DI+=0xfffffffffffffff8]=r118:SI
      REG_ARGS_SIZE 0x10
   97: r9:SI=r116:SI
   98: r8:SI=r98:SI
   99: cx:SI=r117:SI
  100: dx:SI=r99:SI
  101: si:DI=`__FUNCTION__.4'
  102: di:DI=`*.LC128'
  103: ax:QI=0
  104: call [`rhp_log'] argc:0x10
  105: {sp:DI=sp:DI+0x10;clobber flags:CC;}
      REG_ARGS_SIZE 0
" ]

	node [ id 14261 graphics [ fill "#d3d3d3" ] label "  106: L106:
  107: NOTE_INSN_BASIC_BLOCK 12
  108: r119:DI=[r77:DI-0x18]
  109: r120:SI=[r77:DI-0x8]
  110: [r119:DI+0x4]=r120:SI
  111: r100:SI=[r77:DI-0x8]
" ]

	node [ id 14262 graphics [ fill "#d3d3d3" ] label "  112: L112:
  113: NOTE_INSN_BASIC_BLOCK 13
  114: r101:SI=r100:SI
  118: ax:SI=r101:SI
  119: use ax:SI
" ]

	edge [ source 14254 target 14256 graphics [ fill "#0000ff" ] ] 
	edge [ source 14256 target 14257 graphics [ fill "#0000ff" ] ] 
	edge [ source 14256 target 14258 graphics [ fill "#000000" ] ] 
	edge [ source 14257 target 14262 graphics [ fill "#000000" ] ] 
	edge [ source 14258 target 14250 graphics [ fill "#000000" ] ] 
	edge [ source 14251 target 14252 graphics [ fill "#0000ff" ] ] 
	edge [ source 14251 target 14253 graphics [ fill "#000000" ] ] 
	edge [ source 14252 target 14253 graphics [ fill "#0000ff" ] ] 
	edge [ source 14253 target 14250 graphics [ fill "#0000ff" ] ] 
	edge [ source 14250 target 14251 graphics [ fill "#000000" ] ] 
	edge [ source 14250 target 14259 graphics [ fill "#0000ff" ] ] 
	edge [ source 14259 target 14260 graphics [ fill "#0000ff" ] ] 
	edge [ source 14259 target 14261 graphics [ fill "#000000" ] ] 
	edge [ source 14260 target 14261 graphics [ fill "#0000ff" ] ] 
	edge [ source 14261 target 14262 graphics [ fill "#0000ff" ] ] 
	edge [ source 14262 target 14255 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 14471 graphics [ fill "#d3d3d3" ] label "  203: L203:
  204: NOTE_INSN_BASIC_BLOCK 23
  205: r168:DI=[r77:DI-0x20]
  206: r132:SI=[r168:DI]
  208: flags:CCGC=cmp([r77:DI-0xc],r132:SI)
  209: pc={(flags:CCGC&lt;0)?L207:pc}
" ]

	node [ id 14472 graphics [ fill "#d3d3d3" ] label "  207: L207:
   53: NOTE_INSN_BASIC_BLOCK 6
   54: r141:DI=[r77:DI-0x20]
   55: r86:DI=[r141:DI+0x8]
   56: r142:SI=[r77:DI-0xc]
   57: r87:DI=sign_extend(r142:SI)
   58: {r88:DI=r87:DI&lt;&lt;0x3;clobber flags:CC;}
   59: {r89:DI=r86:DI+r88:DI;clobber flags:CC;}
   60: r90:DI=[r89:DI]
   61: r91:SI=[r90:DI+0x38]
   62: flags:CCZ=cmp(r91:SI,0xffffffffffffffff)
   63: pc={(flags:CCZ!=0)?L200:pc}
" ]

	node [ id 14473 graphics [ fill "#d3d3d3" ] label "   64: NOTE_INSN_BASIC_BLOCK 7
   65: r143:DI=[r77:DI-0x20]
   66: r92:DI=[r143:DI+0x8]
   67: r144:SI=[r77:DI-0xc]
   68: r93:DI=sign_extend(r144:SI)
   69: {r94:DI=r93:DI&lt;&lt;0x3;clobber flags:CC;}
   70: {r95:DI=r92:DI+r94:DI;clobber flags:CC;}
   71: r145:DI=[r95:DI]
   72: [r77:DI-0x28]=r145:DI
   73: r96:SI=[`rhp_adjustweight']
   74: flags:CCZ=cmp(r96:SI,0)
   75: pc={(flags:CCZ==0)?L165:pc}
" ]

	node [ id 14474 graphics [ fill "#d3d3d3" ] label "  200: L200:
  201: NOTE_INSN_BASIC_BLOCK 22
  202: {[r77:DI-0xc]=[r77:DI-0xc]+0x1;clobber flags:CC;}
" ]

	node [ id 14475 graphics [ fill "#d3d3d3" ] label "   76: NOTE_INSN_BASIC_BLOCK 8
   77: [r77:DI-0x4]=0
   78: [r77:DI-0x8]=0
   82: flags:CCNO=cmp([r77:DI-0xc],0)
   83: pc={(flags:CCNO&lt;=0)?L96:pc}
" ]

	node [ id 14476 graphics [ fill "#d3d3d3" ] label "  165: L165:
  166: NOTE_INSN_BASIC_BLOCK 18
  169: flags:CCNO=cmp([r77:DI-0xc],0)
  170: pc={(flags:CCNO&gt;0)?L176:pc}
" ]

	node [ id 14477 graphics [ fill "#d3d3d3" ] label "   84: NOTE_INSN_BASIC_BLOCK 10
   85: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
   86: r146:DI=[r77:DI-0x20]
   87: r97:DI=[r146:DI+0x8]
   88: r147:SI=[r77:DI-0xc]
   89: r98:DI=sign_extend(r147:SI)
   90: {r99:DI=r98:DI&lt;&lt;0x3;clobber flags:CC;}
   91: {r100:DI=r99:DI-0x8;clobber flags:CC;}
   92: {r101:DI=r97:DI+r100:DI;clobber flags:CC;}
   93: r102:DI=[r101:DI]
   94: r103:SI=[r102:DI+0x38]
   95: {[r77:DI-0x8]=[r77:DI-0x8]+r103:SI;clobber flags:CC;}
" ]

	node [ id 14478 graphics [ fill "#d3d3d3" ] label "   96: L96:
   97: NOTE_INSN_BASIC_BLOCK 11
   98: r148:DI=[r77:DI-0x20]
   99: r104:SI=[r148:DI]
  100: {r105:SI=r104:SI-0x1;clobber flags:CC;}
  101: flags:CCGC=cmp([r77:DI-0xc],r105:SI)
  102: pc={(flags:CCGC&gt;=0)?L129:pc}
" ]

	node [ id 14479 graphics [ fill "#d3d3d3" ] label "  171: NOTE_INSN_BASIC_BLOCK 19
  172: r162:DI=[r77:DI-0x28]
  173: [r162:DI+0x38]=0
  174: pc=L189
" ]

	node [ id 14480 graphics [ fill "#d3d3d3" ] label "  176: L176:
  177: NOTE_INSN_BASIC_BLOCK 20
  178: r163:DI=[r77:DI-0x20]
  179: r124:DI=[r163:DI+0x8]
  180: r164:SI=[r77:DI-0xc]
  181: r125:DI=sign_extend(r164:SI)
  182: {r126:DI=r125:DI&lt;&lt;0x3;clobber flags:CC;}
  183: {r127:DI=r126:DI-0x8;clobber flags:CC;}
  184: {r128:DI=r124:DI+r127:DI;clobber flags:CC;}
  185: r129:DI=[r128:DI]
  186: r130:SI=[r129:DI+0x38]
  187: r165:DI=[r77:DI-0x28]
  188: [r165:DI+0x38]=r130:SI
" ]

	node [ id 14481 graphics [ fill "#d3d3d3" ] label "  103: NOTE_INSN_BASIC_BLOCK 12
  104: r149:DI=[r77:DI-0x20]
  105: r106:DI=[r149:DI+0x8]
  106: r150:SI=[r77:DI-0xc]
  107: r107:DI=sign_extend(r150:SI)
  108: {r108:DI=r107:DI+0x1;clobber flags:CC;}
  109: {r109:DI=r108:DI&lt;&lt;0x3;clobber flags:CC;}
  110: {r110:DI=r106:DI+r109:DI;clobber flags:CC;}
  111: r111:DI=[r110:DI]
  112: r112:SI=[r111:DI+0x38]
  115: flags:CCGOC=cmp(r112:SI,0)
  116: pc={(flags:CCGOC&lt;0)?L129:pc}
" ]

	node [ id 14482 graphics [ fill "#d3d3d3" ] label "  129: L129:
  130: NOTE_INSN_BASIC_BLOCK 14
  133: flags:CCNO=cmp([r77:DI-0x4],0)
  134: pc={(flags:CCNO&lt;=0)?L148:pc}
" ]

	node [ id 14483 graphics [ fill "#d3d3d3" ] label "  189: L189:
  190: NOTE_INSN_BASIC_BLOCK 21
  191: r166:DI=[r77:DI-0x28]
  192: r131:SI=[r166:DI+0x38]
  193: r167:SI=[r77:DI-0xc]
  194: cx:SI=r131:SI
  195: dx:SI=r167:SI
  196: si:DI=`__FUNCTION__.3'
  197: di:DI=`*.LC131'
  198: ax:QI=0
  199: call [`rhp_log'] argc:0
" ]

	node [ id 14484 graphics [ fill "#d3d3d3" ] label "  117: NOTE_INSN_BASIC_BLOCK 13
  118: {[r77:DI-0x4]=[r77:DI-0x4]+0x1;clobber flags:CC;}
  119: r151:DI=[r77:DI-0x20]
  120: r113:DI=[r151:DI+0x8]
  121: r152:SI=[r77:DI-0xc]
  122: r114:DI=sign_extend(r152:SI)
  123: {r115:DI=r114:DI+0x1;clobber flags:CC;}
  124: {r116:DI=r115:DI&lt;&lt;0x3;clobber flags:CC;}
  125: {r117:DI=r113:DI+r116:DI;clobber flags:CC;}
  126: r118:DI=[r117:DI]
  127: r119:SI=[r118:DI+0x38]
  128: {[r77:DI-0x8]=[r77:DI-0x8]+r119:SI;clobber flags:CC;}
" ]

	node [ id 14485 graphics [ fill "#d3d3d3" ] label "  135: NOTE_INSN_BASIC_BLOCK 15
  136: r153:SI=[r77:DI-0x8]
  137: {r120:SI=r153:SI*0x64;clobber flags:CC;}
  138: r154:DI=[r77:DI-0x28]
  139: [r154:DI+0x38]=r120:SI
  140: r155:DI=[r77:DI-0x28]
  141: r121:SI=[r155:DI+0x38]
  142: {r156:SI=r121:SI/[r77:DI-0x4];r157:SI=r121:SI%[r77:DI-0x4];clobber flags:CC;}
  143: r122:SI=r156:SI
  144: r158:DI=[r77:DI-0x28]
  145: [r158:DI+0x38]=r122:SI
  146: pc=L152
" ]

	node [ id 14486 graphics [ fill "#d3d3d3" ] label "  148: L148:
  149: NOTE_INSN_BASIC_BLOCK 16
  150: r159:DI=[r77:DI-0x28]
  151: [r159:DI+0x38]=0
" ]

	node [ id 14487 graphics [ fill "#d3d3d3" ] label "  152: L152:
  153: NOTE_INSN_BASIC_BLOCK 17
  154: r160:DI=[r77:DI-0x28]
  155: r123:SI=[r160:DI+0x38]
  156: r161:SI=[r77:DI-0xc]
  157: cx:SI=r123:SI
  158: dx:SI=r161:SI
  159: si:DI=`__FUNCTION__.3'
  160: di:DI=`*.LC130'
  161: ax:QI=0
  162: call [`rhp_log'] argc:0
  163: pc=L200
" ]



# function number 65
	node [ id 14488 graphics [ fill "#ffffff" ] label "rhp_barycenterweights_adjust ()
ENTRY" ]

	node [ id 14489 graphics [ fill "#ffffff" ] label "rhp_barycenterweights_adjust ()
EXIT" ]

	node [ id 14490 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x34]=di:SI
    3: [r77:DI-0x38]=si:SI
    4: NOTE_INSN_FUNCTION_BEG
    7: [r77:DI-0x18]=0
    8: [r77:DI-0x20]=0
    9: [r77:DI-0x28]=0
   10: [r77:DI-0x4]=0
   11: [r77:DI-0x8]=0
   12: [r77:DI-0xc]=0
   13: r133:SI=[r77:DI-0x34]
   14: r82:DI=sign_extend(r133:SI)
   15: r83:DI=[`rhp_sp_layers']
   16: si:DI=r82:DI
   17: di:DI=r83:DI
   18: ax:DI=call [`rhp_sp_lookup'] argc:0
   19: r134:DI=ax:DI
   20: [r77:DI-0x18]=r134:DI
   21: flags:CCZ=cmp([r77:DI-0x18],0)
   22: pc={(flags:CCZ!=0)?L32:pc}
" ]

	node [ id 14491 graphics [ fill "#d3d3d3" ] label "   23: NOTE_INSN_BASIC_BLOCK 4
   24: r135:SI=[r77:DI-0x34]
   25: dx:SI=r135:SI
   26: si:DI=`__FUNCTION__.3'
   27: di:DI=`*.LC53'
   28: ax:QI=0
   29: call [`rhp_log'] argc:0
   30: pc=L213
" ]

	node [ id 14492 graphics [ fill "#d3d3d3" ] label "   32: L32:
   33: NOTE_INSN_BASIC_BLOCK 5
   34: r136:DI=[r77:DI-0x18]
   35: r84:DI=[r136:DI+0x8]
   36: [r77:DI-0x20]=r84:DI
   37: r137:DI=[r77:DI-0x20]
   38: r85:SI=[r137:DI]
   39: r138:SI=[r77:DI-0x38]
   40: r139:SI=[r77:DI-0x34]
   41: r140:SI=[r77:DI-0x4]
   42: r9:SI=r138:SI
   43: r8:SI=r139:SI
   44: cx:SI=r85:SI
   45: dx:SI=r140:SI
   46: si:DI=`__FUNCTION__.3'
   47: di:DI=`*.LC129'
   48: ax:QI=0
   49: call [`rhp_log'] argc:0
   50: [r77:DI-0xc]=0
   51: pc=L203
" ]

	node [ id 14493 graphics [ fill "#d3d3d3" ] label "  210: NOTE_INSN_BASIC_BLOCK 24
" ]

	node [ id 14494 graphics [ fill "#d3d3d3" ] label "  213: L213:
  214: NOTE_INSN_BASIC_BLOCK 26
" ]

	edge [ source 14488 target 14490 graphics [ fill "#0000ff" ] ] 
	edge [ source 14490 target 14491 graphics [ fill "#0000ff" ] ] 
	edge [ source 14490 target 14492 graphics [ fill "#000000" ] ] 
	edge [ source 14491 target 14494 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 14492 target 14471 graphics [ fill "#000000" ] ] 
	edge [ source 14472 target 14473 graphics [ fill "#0000ff" ] ] 
	edge [ source 14472 target 14474 graphics [ fill "#000000" ] ] 
	edge [ source 14473 target 14475 graphics [ fill "#0000ff" ] ] 
	edge [ source 14473 target 14476 graphics [ fill "#000000" ] ] 
	edge [ source 14475 target 14477 graphics [ fill "#0000ff" ] ] 
	edge [ source 14475 target 14478 graphics [ fill "#000000" ] ] 
	edge [ source 14477 target 14478 graphics [ fill "#0000ff" ] ] 
	edge [ source 14478 target 14481 graphics [ fill "#0000ff" ] ] 
	edge [ source 14478 target 14482 graphics [ fill "#000000" ] ] 
	edge [ source 14481 target 14484 graphics [ fill "#0000ff" ] ] 
	edge [ source 14481 target 14482 graphics [ fill "#000000" ] ] 
	edge [ source 14484 target 14482 graphics [ fill "#0000ff" ] ] 
	edge [ source 14482 target 14485 graphics [ fill "#0000ff" ] ] 
	edge [ source 14482 target 14486 graphics [ fill "#000000" ] ] 
	edge [ source 14485 target 14487 graphics [ fill "#000000" ] ] 
	edge [ source 14486 target 14487 graphics [ fill "#0000ff" ] ] 
	edge [ source 14487 target 14474 graphics [ fill "#000000" ] ] 
	edge [ source 14476 target 14479 graphics [ fill "#0000ff" ] ] 
	edge [ source 14476 target 14480 graphics [ fill "#000000" ] ] 
	edge [ source 14479 target 14483 graphics [ fill "#000000" ] ] 
	edge [ source 14480 target 14483 graphics [ fill "#0000ff" ] ] 
	edge [ source 14483 target 14474 graphics [ fill "#0000ff" ] ] 
	edge [ source 14474 target 14471 graphics [ fill "#0000ff" ] ] 
	edge [ source 14471 target 14472 graphics [ fill "#000000" ] ] 
	edge [ source 14471 target 14493 graphics [ fill "#0000ff" ] ] 
	edge [ source 14493 target 14494 graphics [ fill "#0000ff" ] ] 
	edge [ source 14494 target 14489 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 14876 graphics [ fill "#d3d3d3" ] label "  101: L101:
  102: NOTE_INSN_BASIC_BLOCK 12
  103: r129:DI=[r77:DI-0x28]
  104: r104:SI=[r129:DI+0x1c]
  106: flags:CCGC=cmp([r77:DI-0x10],r104:SI)
  107: pc={(flags:CCGC&lt;0)?L105:pc}
" ]

	node [ id 14877 graphics [ fill "#d3d3d3" ] label "  105: L105:
   89: NOTE_INSN_BASIC_BLOCK 11
   90: r127:DI=[r77:DI-0x28]
   91: r97:DI=[r127:DI+0x28]
   92: r128:SI=[r77:DI-0x10]
   93: r98:DI=sign_extend(r128:SI)
   94: {r99:DI=r98:DI&lt;&lt;0x3;clobber flags:CC;}
   95: {r100:DI=r97:DI+r99:DI;clobber flags:CC;}
   96: r101:DI=[r100:DI]
   97: r102:DI=[r101:DI+0x20]
   98: r103:SI=[r102:DI+0x18]
   99: {[r77:DI-0xc]=[r77:DI-0xc]+r103:SI;clobber flags:CC;}
  100: {[r77:DI-0x10]=[r77:DI-0x10]+0x1;clobber flags:CC;}
" ]

	node [ id 14878 graphics [ fill "#d3d3d3" ] label "   71: L71:
   72: NOTE_INSN_BASIC_BLOCK 8
   73: r124:DI=[r77:DI-0x28]
   74: r96:SI=[r124:DI+0x20]
   76: flags:CCGC=cmp([r77:DI-0x10],r96:SI)
   77: pc={(flags:CCGC&lt;0)?L75:pc}
" ]

	node [ id 14879 graphics [ fill "#d3d3d3" ] label "   75: L75:
   59: NOTE_INSN_BASIC_BLOCK 7
   60: r122:DI=[r77:DI-0x28]
   61: r89:DI=[r122:DI+0x30]
   62: r123:SI=[r77:DI-0x10]
   63: r90:DI=sign_extend(r123:SI)
   64: {r91:DI=r90:DI&lt;&lt;0x3;clobber flags:CC;}
   65: {r92:DI=r89:DI+r91:DI;clobber flags:CC;}
   66: r93:DI=[r92:DI]
   67: r94:DI=[r93:DI+0x28]
   68: r95:SI=[r94:DI+0x18]
   69: {[r77:DI-0xc]=[r77:DI-0xc]+r95:SI;clobber flags:CC;}
   70: {[r77:DI-0x10]=[r77:DI-0x10]+0x1;clobber flags:CC;}
" ]



# function number 66
	node [ id 14880 graphics [ fill "#ffffff" ] label "rhp_node_weight ()
ENTRY" ]

	node [ id 14881 graphics [ fill "#ffffff" ] label "rhp_node_weight ()
EXIT" ]

	node [ id 14882 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x28]=di:DI
    3: [r77:DI-0x2c]=si:SI
    4: NOTE_INSN_FUNCTION_BEG
    7: [r77:DI-0x4]=0
    8: [r77:DI-0x8]=0
    9: [r77:DI-0x14]=0
   10: [r77:DI-0xc]=0
   11: [r77:DI-0x10]=0
   12: r111:DI=[r77:DI-0x28]
   13: r82:SI=[r111:DI+0x20]
   14: r112:DI=[r77:DI-0x28]
   15: r83:SI=[r112:DI+0x1c]
   16: r113:DI=[r77:DI-0x28]
   17: r84:SI=[r113:DI+0x4]
   18: r114:SI=[r77:DI-0x2c]
   19: r9:SI=r114:SI
   20: r8:SI=r82:SI
   21: cx:SI=r83:SI
   22: dx:SI=r84:SI
   23: si:DI=`__FUNCTION__.2'
   24: di:DI=`*.LC132'
   25: ax:QI=0
   26: call [`rhp_log'] argc:0
   27: r115:DI=[r77:DI-0x28]
   28: r85:SI=[r115:DI+0x1c]
   29: r116:DI=[r77:DI-0x28]
   30: r86:SI=[r116:DI+0x20]
   31: {r87:SI=r85:SI+r86:SI;clobber flags:CC;}
   32: flags:CCZ=cmp(r87:SI,0)
   33: pc={(flags:CCZ!=0)?L48:pc}
" ]

	node [ id 14883 graphics [ fill "#d3d3d3" ] label "   34: NOTE_INSN_BASIC_BLOCK 4
   35: r117:DI=[r77:DI-0x28]
   36: [r117:DI+0x38]=0
   37: r118:DI=[r77:DI-0x28]
   38: r88:SI=[r118:DI+0x4]
   39: r119:SI=[r77:DI-0x2c]
   40: cx:SI=r119:SI
   41: dx:SI=r88:SI
   42: si:DI=`__FUNCTION__.2'
   43: di:DI=`*.LC133'
   44: ax:QI=0
   45: call [`rhp_log'] argc:0
   46: pc=L168
" ]

	node [ id 14884 graphics [ fill "#d3d3d3" ] label "   48: L48:
   49: NOTE_INSN_BASIC_BLOCK 5
   50: flags:CCZ=cmp([r77:DI-0x2c],0x1)
   51: pc={(flags:CCZ==0)?L78:pc}
" ]

	node [ id 14885 graphics [ fill "#d3d3d3" ] label "   52: NOTE_INSN_BASIC_BLOCK 6
   53: r120:DI=[r77:DI-0x28]
   54: r121:SI=[r120:DI+0x20]
   55: [r77:DI-0x4]=r121:SI
   56: [r77:DI-0x10]=0
   57: pc=L71
" ]

	node [ id 14886 graphics [ fill "#d3d3d3" ] label "   78: L78:
   79: NOTE_INSN_BASIC_BLOCK 9
   80: flags:CCZ=cmp([r77:DI-0x2c],0)
   81: pc={(flags:CCZ==0)?L108:pc}
" ]

	node [ id 14887 graphics [ fill "#d3d3d3" ] label "   82: NOTE_INSN_BASIC_BLOCK 10
   83: r125:DI=[r77:DI-0x28]
   84: r126:SI=[r125:DI+0x1c]
   85: [r77:DI-0x8]=r126:SI
   86: [r77:DI-0x10]=0
   87: pc=L101
" ]

	node [ id 14888 graphics [ fill "#d3d3d3" ] label "  108: L108:
  109: NOTE_INSN_BASIC_BLOCK 13
  114: r134:SI=[r77:DI-0x4]
  115: r135:SI=[r77:DI-0x8]
  116: {r133:SI=r134:SI+r135:SI;clobber flags:CC;}
      REG_EQUAL [r77:DI-0x4]+[r77:DI-0x8]
  117: [r77:DI-0x14]=r133:SI
  120: flags:CCNO=cmp([r77:DI-0x14],0)
  121: pc={(flags:CCNO&lt;=0)?L135:pc}
" ]

	node [ id 14889 graphics [ fill "#d3d3d3" ] label "  122: NOTE_INSN_BASIC_BLOCK 14
  123: r136:SI=[r77:DI-0xc]
  124: {r105:SI=r136:SI*0x64;clobber flags:CC;}
  125: r137:DI=[r77:DI-0x28]
  126: [r137:DI+0x38]=r105:SI
  127: r138:DI=[r77:DI-0x28]
  128: r106:SI=[r138:DI+0x38]
  129: {r139:SI=r106:SI/[r77:DI-0x14];r140:SI=r106:SI%[r77:DI-0x14];clobber flags:CC;}
  130: r107:SI=r139:SI
  131: r141:DI=[r77:DI-0x28]
  132: [r141:DI+0x38]=r107:SI
  133: pc=L152
" ]

	node [ id 14890 graphics [ fill "#d3d3d3" ] label "  135: L135:
  136: NOTE_INSN_BASIC_BLOCK 15
  137: r142:DI=[r77:DI-0x28]
  138: [r142:DI+0x38]=0xffffffffffffffff
  139: r143:DI=[r77:DI-0x28]
  140: r108:SI=[r143:DI+0x4]
  141: r144:SI=[r77:DI-0x2c]
  142: r145:SI=[r77:DI-0x8]
  143: r146:SI=[r77:DI-0x4]
  144: r9:SI=r144:SI
  145: r8:SI=r145:SI
  146: cx:SI=r146:SI
  147: dx:SI=r108:SI
  148: si:DI=`__FUNCTION__.2'
  149: di:DI=`*.LC134'
  150: ax:QI=0
  151: call [`rhp_log'] argc:0
" ]

	node [ id 14891 graphics [ fill "#d3d3d3" ] label "  152: L152:
  153: NOTE_INSN_BASIC_BLOCK 16
  154: r147:DI=[r77:DI-0x28]
  155: r109:SI=[r147:DI+0x38]
  156: r148:DI=[r77:DI-0x28]
  157: r110:SI=[r148:DI+0x4]
  158: r149:SI=[r77:DI-0x2c]
  159: r8:SI=r149:SI
  160: cx:SI=r109:SI
  161: dx:SI=r110:SI
  162: si:DI=`__FUNCTION__.2'
  163: di:DI=`*.LC135'
  164: ax:QI=0
  165: call [`rhp_log'] argc:0
" ]

	node [ id 14892 graphics [ fill "#d3d3d3" ] label "  168: L168:
  169: NOTE_INSN_BASIC_BLOCK 18
" ]

	edge [ source 14880 target 14882 graphics [ fill "#0000ff" ] ] 
	edge [ source 14882 target 14883 graphics [ fill "#0000ff" ] ] 
	edge [ source 14882 target 14884 graphics [ fill "#000000" ] ] 
	edge [ source 14883 target 14892 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 14884 target 14885 graphics [ fill "#0000ff" ] ] 
	edge [ source 14884 target 14886 graphics [ fill "#000000" ] ] 
	edge [ source 14885 target 14878 graphics [ fill "#000000" ] ] 
	edge [ source 14879 target 14878 graphics [ fill "#0000ff" ] ] 
	edge [ source 14878 target 14879 graphics [ fill "#000000" ] ] 
	edge [ source 14878 target 14886 graphics [ fill "#0000ff" ] ] 
	edge [ source 14886 target 14887 graphics [ fill "#0000ff" ] ] 
	edge [ source 14886 target 14888 graphics [ fill "#000000" ] ] 
	edge [ source 14887 target 14876 graphics [ fill "#000000" ] ] 
	edge [ source 14877 target 14876 graphics [ fill "#0000ff" ] ] 
	edge [ source 14876 target 14877 graphics [ fill "#000000" ] ] 
	edge [ source 14876 target 14888 graphics [ fill "#0000ff" ] ] 
	edge [ source 14888 target 14889 graphics [ fill "#0000ff" ] ] 
	edge [ source 14888 target 14890 graphics [ fill "#000000" ] ] 
	edge [ source 14889 target 14891 graphics [ fill "#000000" ] ] 
	edge [ source 14890 target 14891 graphics [ fill "#0000ff" ] ] 
	edge [ source 14891 target 14892 graphics [ fill "#0000ff" ] ] 
	edge [ source 14892 target 14881 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 67
	node [ id 15172 graphics [ fill "#ffffff" ] label "rhp_compare_weights ()
ENTRY" ]

	node [ id 15173 graphics [ fill "#ffffff" ] label "rhp_compare_weights ()
EXIT" ]

	node [ id 15174 graphics [ fill "#d3d3d3" ] label "    5: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x38]=di:DI
    3: [r77:DI-0x40]=si:DI
    4: NOTE_INSN_FUNCTION_BEG
    7: [r77:DI-0x10]=0
    8: [r77:DI-0x18]=0
    9: [r77:DI-0x20]=0
   10: [r77:DI-0x28]=0
   11: [r77:DI-0x4]=0
   12: r91:DI=[r77:DI-0x38]
   13: [r77:DI-0x10]=r91:DI
   14: r92:DI=[r77:DI-0x40]
   15: [r77:DI-0x18]=r92:DI
   16: r93:DI=[r77:DI-0x10]
   17: r94:DI=[r93:DI]
   18: [r77:DI-0x20]=r94:DI
   19: r95:DI=[r77:DI-0x18]
   20: r96:DI=[r95:DI]
   21: [r77:DI-0x28]=r96:DI
   22: r97:DI=[r77:DI-0x20]
   23: r82:SI=[r97:DI+0x38]
   24: r98:DI=[r77:DI-0x28]
   25: r83:SI=[r98:DI+0x38]
   26: flags:CCGC=cmp(r82:SI,r83:SI)
   27: r84:QI=flags:CCGC&gt;0
   28: r99:SI=zero_extend(r84:QI)
   29: [r77:DI-0x4]=r99:SI
   32: flags:CCGOC=cmp([r77:DI-0x4],0)
   33: pc={(flags:CCGOC&gt;=0)?L36:pc}
" ]

	node [ id 15175 graphics [ fill "#d3d3d3" ] label "   34: NOTE_INSN_BASIC_BLOCK 4
   35: {[r77:DI-0x4]=-[r77:DI-0x4];clobber flags:CC;}
" ]

	node [ id 15176 graphics [ fill "#d3d3d3" ] label "   36: L36:
   37: NOTE_INSN_BASIC_BLOCK 5
   40: flags:CCNO=cmp([r77:DI-0x4],0)
   41: pc={(flags:CCNO&gt;0)?L46:pc}
" ]

	node [ id 15177 graphics [ fill "#d3d3d3" ] label "   42: NOTE_INSN_BASIC_BLOCK 6
   43: r89:SI=0
   44: pc=L73
" ]

	node [ id 15178 graphics [ fill "#d3d3d3" ] label "   46: L46:
   47: NOTE_INSN_BASIC_BLOCK 7
   48: r100:DI=[r77:DI-0x20]
   49: r85:SI=[r100:DI+0x38]
   50: r101:DI=[r77:DI-0x28]
   51: r86:SI=[r101:DI+0x38]
   52: flags:CCGC=cmp(r85:SI,r86:SI)
   53: pc={(flags:CCGC&lt;=0)?L58:pc}
" ]

	node [ id 15179 graphics [ fill "#d3d3d3" ] label "   54: NOTE_INSN_BASIC_BLOCK 8
   55: r89:SI=0x1
   56: pc=L73
" ]

	node [ id 15180 graphics [ fill "#d3d3d3" ] label "   58: L58:
   59: NOTE_INSN_BASIC_BLOCK 9
   60: r102:DI=[r77:DI-0x20]
   61: r87:SI=[r102:DI+0x38]
   62: r103:DI=[r77:DI-0x28]
   63: r88:SI=[r103:DI+0x38]
   64: flags:CCGC=cmp(r87:SI,r88:SI)
   65: pc={(flags:CCGC&gt;=0)?L70:pc}
" ]

	node [ id 15181 graphics [ fill "#d3d3d3" ] label "   66: NOTE_INSN_BASIC_BLOCK 10
   67: r89:SI=0xffffffffffffffff
   68: pc=L73
" ]

	node [ id 15182 graphics [ fill "#d3d3d3" ] label "   70: L70:
   71: NOTE_INSN_BASIC_BLOCK 11
   72: r89:SI=0
" ]

	node [ id 15183 graphics [ fill "#d3d3d3" ] label "   73: L73:
   74: NOTE_INSN_BASIC_BLOCK 12
   75: r90:SI=r89:SI
   79: ax:SI=r90:SI
   80: use ax:SI
" ]

	edge [ source 15172 target 15174 graphics [ fill "#0000ff" ] ] 
	edge [ source 15174 target 15175 graphics [ fill "#0000ff" ] ] 
	edge [ source 15174 target 15176 graphics [ fill "#000000" ] ] 
	edge [ source 15175 target 15176 graphics [ fill "#0000ff" ] ] 
	edge [ source 15176 target 15177 graphics [ fill "#0000ff" ] ] 
	edge [ source 15176 target 15178 graphics [ fill "#000000" ] ] 
	edge [ source 15177 target 15183 graphics [ fill "#000000" ] ] 
	edge [ source 15178 target 15179 graphics [ fill "#0000ff" ] ] 
	edge [ source 15178 target 15180 graphics [ fill "#000000" ] ] 
	edge [ source 15179 target 15183 graphics [ fill "#000000" ] ] 
	edge [ source 15180 target 15181 graphics [ fill "#0000ff" ] ] 
	edge [ source 15180 target 15182 graphics [ fill "#000000" ] ] 
	edge [ source 15181 target 15183 graphics [ fill "#000000" ] ] 
	edge [ source 15182 target 15183 graphics [ fill "#0000ff" ] ] 
	edge [ source 15183 target 15173 graphics [ fill "#0000ff" ] label "[100%]"] 


# function number 68
	node [ id 15376 graphics [ fill "#ffffff" ] label "rhp_layersort ()
ENTRY" ]

	node [ id 15377 graphics [ fill "#ffffff" ] label "rhp_layersort ()
EXIT" ]

	node [ id 15378 graphics [ fill "#d3d3d3" ] label "    4: NOTE_INSN_BASIC_BLOCK 2
    2: [r77:DI-0x14]=di:SI
    3: NOTE_INSN_FUNCTION_BEG
    6: [r77:DI-0x8]=0
    7: [r77:DI-0x10]=0
    8: r88:SI=[r77:DI-0x14]
    9: r82:DI=sign_extend(r88:SI)
   10: r83:DI=[`rhp_sp_layers']
   11: si:DI=r82:DI
   12: di:DI=r83:DI
   13: ax:DI=call [`rhp_sp_lookup'] argc:0
   14: r89:DI=ax:DI
   15: [r77:DI-0x8]=r89:DI
   16: flags:CCZ=cmp([r77:DI-0x8],0)
   17: pc={(flags:CCZ!=0)?L27:pc}
" ]

	node [ id 15379 graphics [ fill "#d3d3d3" ] label "   18: NOTE_INSN_BASIC_BLOCK 4
   19: r90:SI=[r77:DI-0x14]
   20: dx:SI=r90:SI
   21: si:DI=`__FUNCTION__.1'
   22: di:DI=`*.LC53'
   23: ax:QI=0
   24: call [`rhp_log'] argc:0
   25: pc=L53
" ]

	node [ id 15380 graphics [ fill "#d3d3d3" ] label "   27: L27:
   28: NOTE_INSN_BASIC_BLOCK 5
   29: r91:DI=[r77:DI-0x8]
   30: r84:DI=[r91:DI+0x8]
   31: [r77:DI-0x10]=r84:DI
   32: r92:DI=[r77:DI-0x10]
   33: r85:SI=[r92:DI]
   34: r86:DI=sign_extend(r85:SI)
   35: r93:DI=[r77:DI-0x10]
   36: r87:DI=[r93:DI+0x8]
   37: cx:DI=`rhp_compare_weights'
   38: dx:DI=0x8
   39: si:DI=r86:DI
   40: di:DI=r87:DI
   41: call [`qsort'] argc:0
   42: r94:SI=[r77:DI-0x14]
   43: di:SI=r94:SI
   44: call [`rhp_updatenodepositions'] argc:0
   45: r95:SI=[r77:DI-0x14]
   46: dx:SI=r95:SI
   47: si:DI=`__FUNCTION__.1'
   48: di:DI=`*.LC136'
   49: ax:QI=0
   50: call [`rhp_log'] argc:0
" ]

	node [ id 15381 graphics [ fill "#d3d3d3" ] label "   53: L53:
   54: NOTE_INSN_BASIC_BLOCK 7
" ]

	edge [ source 15376 target 15378 graphics [ fill "#0000ff" ] ] 
	edge [ source 15378 target 15379 graphics [ fill "#0000ff" ] ] 
	edge [ source 15378 target 15380 graphics [ fill "#000000" ] ] 
	edge [ source 15379 target 15381 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 15380 target 15381 graphics [ fill "#0000ff" ] ] 
	edge [ source 15381 target 15377 graphics [ fill "#0000ff" ] label "[100%]"] 
	node [ id 15485 graphics [ fill "#d3d3d3" ] label "  168: L168:
  169: NOTE_INSN_BASIC_BLOCK 10
  171: flags:CCZ=cmp([r77:DI-0x8],0)
  172: pc={(flags:CCZ!=0)?L170:pc}
" ]

	node [ id 15486 graphics [ fill "#d3d3d3" ] label "  170: L170:
   61: NOTE_INSN_BASIC_BLOCK 9
   62: r144:DI=[r77:DI-0x8]
   63: r89:DI=[r144:DI+0x8]
   64: [r77:DI-0x28]=r89:DI
   65: r145:DI=[r77:DI-0x28]
   66: r90:SI=[r145:DI+0x18]
   67: r146:DI=[r77:DI-0x28]
   68: r91:SI=[r146:DI+0x8]
   69: r147:DI=[r77:DI-0x28]
   70: r92:SI=[r147:DI+0x4]
   71: r8:SI=r90:SI
   72: cx:SI=r91:SI
   73: dx:SI=r92:SI
   74: si:DI=`__FUNCTION__.0'
   75: di:DI=`*.LC40'
   76: ax:QI=0
   77: call [`rhp_log'] argc:0
   78: dx:SI=0x1021
   79: si:DI=`__FUNCTION__.0'
   80: di:DI=0x50
   81: ax:DI=call [`rhp_malloc'] argc:0
   82: r148:DI=ax:DI
   83: [r77:DI-0x30]=r148:DI
   84: r149:DI=[r77:DI-0x30]
   85: r150:SI=[r77:DI-0x14]
   86: [r149:DI]=r150:SI
   87: r151:DI=[r77:DI-0x28]
   88: r93:SI=[r151:DI+0x4]
   89: r152:DI=[r77:DI-0x30]
   90: [r152:DI+0x4]=r93:SI
   91: r153:DI=[r77:DI-0x28]
   92: r94:SI=[r153:DI+0x8]
   93: r154:DI=[r77:DI-0x30]
   94: [r154:DI+0x8]=r94:SI
   95: r155:DI=[r77:DI-0x28]
   96: r95:DI=[r155:DI+0x10]
   97: r156:DI=[r77:DI-0x30]
   98: [r156:DI+0x10]=r95:DI
   99: r157:DI=[r77:DI-0x28]
  100: r96:SI=[r157:DI+0x18]
  101: r158:DI=[r77:DI-0x30]
  102: [r158:DI+0x18]=r96:SI
  103: r159:DI=[r77:DI-0x28]
  104: r97:SI=[r159:DI+0x1c]
  105: r160:DI=[r77:DI-0x30]
  106: [r160:DI+0x1c]=r97:SI
  107: r161:DI=[r77:DI-0x28]
  108: r98:SI=[r161:DI+0x20]
  109: r162:DI=[r77:DI-0x30]
  110: [r162:DI+0x20]=r98:SI
  111: r163:DI=[r77:DI-0x28]
  112: r99:DI=[r163:DI+0x28]
  113: r164:DI=[r77:DI-0x30]
  114: [r164:DI+0x28]=r99:DI
  115: r165:DI=[r77:DI-0x28]
  116: r100:DI=[r165:DI+0x30]
  117: r166:DI=[r77:DI-0x30]
  118: [r166:DI+0x30]=r100:DI
  119: r167:DI=[r77:DI-0x28]
  120: r101:SI=[r167:DI+0x38]
  121: r168:DI=[r77:DI-0x30]
  122: [r168:DI+0x38]=r101:SI
  123: r169:DI=[r77:DI-0x28]
  124: r102:DI=[r169:DI+0x40]
  125: r170:DI=[r77:DI-0x30]
  126: [r170:DI+0x40]=r102:DI
  127: r171:DI=[r77:DI-0x28]
  128: r103:DI=[r171:DI+0x48]
  129: r172:DI=[r77:DI-0x30]
  130: [r172:DI+0x48]=r103:DI
  131: r173:DI=[r77:DI-0x28]
  132: r104:SI=[r173:DI+0x38]
  133: r174:DI=[r77:DI-0x28]
  134: r105:SI=[r174:DI+0x18]
  135: r175:DI=[r77:DI-0x28]
  136: r106:SI=[r175:DI+0x8]
  137: r176:DI=[r77:DI-0x28]
  138: r107:SI=[r176:DI+0x4]
  139: {sp:DI=sp:DI-0x8;clobber flags:CC;}
      REG_ARGS_SIZE 0x8
  140: r177:SI=[r77:DI-0x14]
  141: [pre sp:DI+=0xfffffffffffffff8]=r177:SI
      REG_ARGS_SIZE 0x10
  142: r9:SI=r104:SI
  143: r8:SI=r105:SI
  144: cx:SI=r106:SI
  145: dx:SI=r107:SI
  146: si:DI=`__FUNCTION__.0'
  147: di:DI=`*.LC139'
  148: ax:QI=0
  149: call [`rhp_log'] argc:0x10
  150: {sp:DI=sp:DI+0x10;clobber flags:CC;}
      REG_ARGS_SIZE 0
  151: r108:DI=[r77:DI-0x30]
  152: r178:SI=[r77:DI-0x14]
  153: r109:DI=sign_extend(r178:SI)
  154: r110:DI=[`rhp_sp_master_node_list_sorted']
  155: dx:DI=r108:DI
  156: si:DI=r109:DI
  157: di:DI=r110:DI
  158: call [`rhp_sp_insert'] argc:0
  159: {[r77:DI-0x14]=[r77:DI-0x14]+0x1;clobber flags:CC;}
  160: r179:DI=[r77:DI-0x8]
  161: r111:DI=[r179:DI]
  162: r112:DI=[`rhp_sp_master_node_list']
  163: si:DI=r111:DI
  164: di:DI=r112:DI
  165: ax:DI=call [`rhp_sp_next'] argc:0
  166: r180:DI=ax:DI
  167: [r77:DI-0x8]=r180:DI
" ]

	node [ id 15487 graphics [ fill "#d3d3d3" ] label "  349: L349:
  350: NOTE_INSN_BASIC_BLOCK 23
  351: r224:DI=[r77:DI-0x20]
  352: r141:SI=[r224:DI]
  354: flags:CCGC=cmp([r77:DI-0x10],r141:SI)
  355: pc={(flags:CCGC&lt;0)?L353:pc}
" ]

	node [ id 15488 graphics [ fill "#d3d3d3" ] label "  353: L353:
  257: NOTE_INSN_BASIC_BLOCK 22
  258: r190:DI=[r77:DI-0x20]
  259: r119:DI=[r190:DI+0x8]
  260: r191:SI=[r77:DI-0x10]
  261: r120:DI=sign_extend(r191:SI)
  262: {r121:DI=r120:DI&lt;&lt;0x3;clobber flags:CC;}
  263: {r122:DI=r119:DI+r121:DI;clobber flags:CC;}
  264: r192:DI=[r122:DI]
  265: [r77:DI-0x28]=r192:DI
  266: dx:SI=0x106a
  267: si:DI=`__FUNCTION__.0'
  268: di:DI=0x50
  269: ax:DI=call [`rhp_malloc'] argc:0
  270: r193:DI=ax:DI
  271: [r77:DI-0x30]=r193:DI
  272: r194:DI=[r77:DI-0x30]
  273: r195:SI=[r77:DI-0x14]
  274: [r194:DI]=r195:SI
  275: r196:DI=[r77:DI-0x28]
  276: r123:SI=[r196:DI+0x4]
  277: r197:DI=[r77:DI-0x30]
  278: [r197:DI+0x4]=r123:SI
  279: r198:DI=[r77:DI-0x28]
  280: r124:SI=[r198:DI+0x8]
  281: r199:DI=[r77:DI-0x30]
  282: [r199:DI+0x8]=r124:SI
  283: r200:DI=[r77:DI-0x28]
  284: r125:DI=[r200:DI+0x10]
  285: r201:DI=[r77:DI-0x30]
  286: [r201:DI+0x10]=r125:DI
  287: r202:DI=[r77:DI-0x28]
  288: r126:SI=[r202:DI+0x18]
  289: r203:DI=[r77:DI-0x30]
  290: [r203:DI+0x18]=r126:SI
  291: r204:DI=[r77:DI-0x28]
  292: r127:SI=[r204:DI+0x1c]
  293: r205:DI=[r77:DI-0x30]
  294: [r205:DI+0x1c]=r127:SI
  295: r206:DI=[r77:DI-0x28]
  296: r128:SI=[r206:DI+0x20]
  297: r207:DI=[r77:DI-0x30]
  298: [r207:DI+0x20]=r128:SI
  299: r208:DI=[r77:DI-0x28]
  300: r129:DI=[r208:DI+0x28]
  301: r209:DI=[r77:DI-0x30]
  302: [r209:DI+0x28]=r129:DI
  303: r210:DI=[r77:DI-0x28]
  304: r130:DI=[r210:DI+0x30]
  305: r211:DI=[r77:DI-0x30]
  306: [r211:DI+0x30]=r130:DI
  307: r212:DI=[r77:DI-0x28]
  308: r131:SI=[r212:DI+0x38]
  309: r213:DI=[r77:DI-0x30]
  310: [r213:DI+0x38]=r131:SI
  311: r214:DI=[r77:DI-0x28]
  312: r132:DI=[r214:DI+0x40]
  313: r215:DI=[r77:DI-0x30]
  314: [r215:DI+0x40]=r132:DI
  315: r216:DI=[r77:DI-0x28]
  316: r133:DI=[r216:DI+0x48]
  317: r217:DI=[r77:DI-0x30]
  318: [r217:DI+0x48]=r133:DI
  319: r218:DI=[r77:DI-0x28]
  320: r134:SI=[r218:DI+0x38]
  321: r219:DI=[r77:DI-0x28]
  322: r135:SI=[r219:DI+0x18]
  323: r220:DI=[r77:DI-0x28]
  324: r136:SI=[r220:DI+0x8]
  325: r221:DI=[r77:DI-0x28]
  326: r137:SI=[r221:DI+0x4]
  327: {sp:DI=sp:DI-0x8;clobber flags:CC;}
      REG_ARGS_SIZE 0x8
  328: r222:SI=[r77:DI-0x14]
  329: [pre sp:DI+=0xfffffffffffffff8]=r222:SI
      REG_ARGS_SIZE 0x10
  330: r9:SI=r134:SI
  331: r8:SI=r135:SI
  332: cx:SI=r136:SI
  333: dx:SI=r137:SI
  334: si:DI=`__FUNCTION__.0'
  335: di:DI=`*.LC139'
  336: ax:QI=0
  337: call [`rhp_log'] argc:0x10
  338: {sp:DI=sp:DI+0x10;clobber flags:CC;}
      REG_ARGS_SIZE 0
  339: r138:DI=[r77:DI-0x30]
  340: r223:SI=[r77:DI-0x14]
  341: r139:DI=sign_extend(r223:SI)
  342: r140:DI=[`rhp_sp_master_node_list_sorted']
  343: dx:DI=r138:DI
  344: si:DI=r139:DI
  345: di:DI=r140:DI
  346: call [`rhp_sp_insert'] argc:0
  347: {[r77:DI-0x14]=[r77:DI-0x14]+0x1;clobber flags:CC;}
  348: {[r77:DI-0x10]=[r77:DI-0x10]+0x1;clobber flags:CC;}
" ]

	node [ id 15489 graphics [ fill "#d3d3d3" ] label "  359: L359:
  360: NOTE_INSN_BASIC_BLOCK 25
  361: r142:SI=[`rhp_nlevels']
  363: flags:CCGC=cmp([r77:DI-0xc],r142:SI)
  364: pc={(flags:CCGC&lt;0)?L362:pc}
" ]

	node [ id 15490 graphics [ fill "#d3d3d3" ] label "  362: L362:
  186: NOTE_INSN_BASIC_BLOCK 13
  187: r181:SI=[r77:DI-0xc]
  188: r114:DI=sign_extend(r181:SI)
  189: r115:DI=[`rhp_sp_layers']
  190: si:DI=r114:DI
  191: di:DI=r115:DI
  192: ax:DI=call [`rhp_sp_lookup'] argc:0
  193: r182:DI=ax:DI
  194: [r77:DI-0x8]=r182:DI
  195: flags:CCZ=cmp([r77:DI-0x8],0)
  196: pc={(flags:CCZ!=0)?L206:pc}
" ]

	node [ id 15491 graphics [ fill "#d3d3d3" ] label "  197: NOTE_INSN_BASIC_BLOCK 14
  198: r183:SI=[r77:DI-0xc]
  199: dx:SI=r183:SI
  200: si:DI=`__FUNCTION__.0'
  201: di:DI=`*.LC96'
  202: ax:QI=0
  203: call [`rhp_log'] argc:0
  204: pc=L356
" ]

	node [ id 15492 graphics [ fill "#d3d3d3" ] label "  206: L206:
  207: NOTE_INSN_BASIC_BLOCK 15
  208: r184:DI=[r77:DI-0x8]
  209: r116:DI=[r184:DI+0x8]
  210: [r77:DI-0x20]=r116:DI
  211: flags:CCZ=cmp([r77:DI-0x20],0)
  212: pc={(flags:CCZ!=0)?L222:pc}
" ]

	node [ id 15493 graphics [ fill "#d3d3d3" ] label "  356: L356:
  357: NOTE_INSN_BASIC_BLOCK 24
  358: {[r77:DI-0xc]=[r77:DI-0xc]+0x1;clobber flags:CC;}
" ]

	node [ id 15494 graphics [ fill "#d3d3d3" ] label "  213: NOTE_INSN_BASIC_BLOCK 16
  214: r185:SI=[r77:DI-0xc]
  215: dx:SI=r185:SI
  216: si:DI=`__FUNCTION__.0'
  217: di:DI=`*.LC97'
  218: ax:QI=0
  219: call [`rhp_log'] argc:0
  220: pc=L356
" ]

	node [ id 15495 graphics [ fill "#d3d3d3" ] label "  222: L222:
  223: NOTE_INSN_BASIC_BLOCK 17
  224: r186:DI=[r77:DI-0x20]
  225: r117:DI=[r186:DI+0x8]
  226: flags:CCZ=cmp(r117:DI,0)
  227: pc={(flags:CCZ!=0)?L237:pc}
" ]

	node [ id 15496 graphics [ fill "#d3d3d3" ] label "  228: NOTE_INSN_BASIC_BLOCK 18
  229: r187:SI=[r77:DI-0xc]
  230: dx:SI=r187:SI
  231: si:DI=`__FUNCTION__.0'
  232: di:DI=`*.LC98'
  233: ax:QI=0
  234: call [`rhp_log'] argc:0
  235: pc=L356
" ]

	node [ id 15497 graphics [ fill "#d3d3d3" ] label "  237: L237:
  238: NOTE_INSN_BASIC_BLOCK 19
  239: r188:DI=[r77:DI-0x20]
  240: r118:SI=[r188:DI]
  241: flags:CCZ=cmp(r118:SI,0)
  242: pc={(flags:CCZ!=0)?L252:pc}
" ]

	node [ id 15498 graphics [ fill "#d3d3d3" ] label "  243: NOTE_INSN_BASIC_BLOCK 20
  244: r189:SI=[r77:DI-0xc]
  245: dx:SI=r189:SI
  246: si:DI=`__FUNCTION__.0'
  247: di:DI=`*.LC97'
  248: ax:QI=0
  249: call [`rhp_log'] argc:0
  250: pc=L356
" ]

	node [ id 15499 graphics [ fill "#d3d3d3" ] label "  252: L252:
  253: NOTE_INSN_BASIC_BLOCK 21
  254: [r77:DI-0x10]=0
  255: pc=L349
" ]



# function number 69
	node [ id 15500 graphics [ fill "#ffffff" ] label "rhp_sorted_nodelist ()
ENTRY" ]

	node [ id 15501 graphics [ fill "#ffffff" ] label "rhp_sorted_nodelist ()
EXIT" ]

	node [ id 15502 graphics [ fill "#d3d3d3" ] label "    3: NOTE_INSN_BASIC_BLOCK 2
    2: NOTE_INSN_FUNCTION_BEG
    5: [r77:DI-0x8]=0
    6: [r77:DI-0x20]=0
    7: [r77:DI-0x28]=0
    8: [r77:DI-0x30]=0
    9: [r77:DI-0xc]=0
   10: [r77:DI-0x10]=0
   11: [r77:DI-0x14]=0
   12: r82:SI=[`rhp_nlevels']
   13: dx:SI=r82:SI
   14: si:DI=`__FUNCTION__.0'
   15: di:DI=`*.LC137'
   16: ax:QI=0
   17: call [`rhp_log'] argc:0
   18: r83:SI=[`rhp_nlevels']
   19: flags:CCZ=cmp(r83:SI,0)
   20: pc={(flags:CCZ!=0)?L28:pc}
" ]

	node [ id 15503 graphics [ fill "#d3d3d3" ] label "   21: NOTE_INSN_BASIC_BLOCK 4
   22: si:DI=`__FUNCTION__.0'
   23: di:DI=`*.LC51'
   24: ax:QI=0
   25: call [`rhp_log'] argc:0
   26: pc=L368
" ]

	node [ id 15504 graphics [ fill "#d3d3d3" ] label "   28: L28:
   29: NOTE_INSN_BASIC_BLOCK 5
   30: r84:DI=[`rhp_sp_master_node_list']
   31: di:DI=r84:DI
   32: ax:SI=call [`rhp_sp_has_data'] argc:0
   33: r85:SI=ax:SI
   34: flags:CCZ=cmp(r85:SI,0)
   35: pc={(flags:CCZ!=0)?L43:pc}
" ]

	node [ id 15505 graphics [ fill "#d3d3d3" ] label "   36: NOTE_INSN_BASIC_BLOCK 6
   37: si:DI=`__FUNCTION__.0'
   38: di:DI=`*.LC138'
   39: ax:QI=0
   40: call [`rhp_log'] argc:0
   41: pc=L368
" ]

	node [ id 15506 graphics [ fill "#d3d3d3" ] label "   43: L43:
   44: NOTE_INSN_BASIC_BLOCK 7
   45: r86:SI=[`rhp_nlevels']
   46: flags:CCZ=cmp(r86:SI,0x1)
   47: pc={(flags:CCZ!=0)?L176:pc}
" ]

	node [ id 15507 graphics [ fill "#d3d3d3" ] label "   48: NOTE_INSN_BASIC_BLOCK 8
   49: [r77:DI-0x14]=0
   50: di:SI=0x1
   51: ax:DI=call [`rhp_sp_new'] argc:0
   52: r87:DI=ax:DI
   53: [`rhp_sp_master_node_list_sorted']=r87:DI
   54: r88:DI=[`rhp_sp_master_node_list']
   55: di:DI=r88:DI
   56: ax:DI=call [`rhp_sp_min'] argc:0
   57: r143:DI=ax:DI
   58: [r77:DI-0x8]=r143:DI
   59: pc=L168
" ]

	node [ id 15508 graphics [ fill "#d3d3d3" ] label "  173: NOTE_INSN_BASIC_BLOCK 11
  174: pc=L368
" ]

	node [ id 15509 graphics [ fill "#d3d3d3" ] label "  176: L176:
  177: NOTE_INSN_BASIC_BLOCK 12
  178: [r77:DI-0x14]=0
  179: di:SI=0x1
  180: ax:DI=call [`rhp_sp_new'] argc:0
  181: r113:DI=ax:DI
  182: [`rhp_sp_master_node_list_sorted']=r113:DI
  183: [r77:DI-0xc]=0
  184: pc=L359
" ]

	node [ id 15510 graphics [ fill "#d3d3d3" ] label "  365: NOTE_INSN_BASIC_BLOCK 26
" ]

	node [ id 15511 graphics [ fill "#d3d3d3" ] label "  368: L368:
  369: NOTE_INSN_BASIC_BLOCK 28
" ]

	edge [ source 15500 target 15502 graphics [ fill "#0000ff" ] ] 
	edge [ source 15502 target 15503 graphics [ fill "#0000ff" ] ] 
	edge [ source 15502 target 15504 graphics [ fill "#000000" ] ] 
	edge [ source 15503 target 15511 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 15504 target 15505 graphics [ fill "#0000ff" ] ] 
	edge [ source 15504 target 15506 graphics [ fill "#000000" ] ] 
	edge [ source 15505 target 15511 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 15506 target 15507 graphics [ fill "#0000ff" ] ] 
	edge [ source 15506 target 15509 graphics [ fill "#000000" ] ] 
	edge [ source 15507 target 15485 graphics [ fill "#000000" ] ] 
	edge [ source 15486 target 15485 graphics [ fill "#0000ff" ] ] 
	edge [ source 15485 target 15486 graphics [ fill "#000000" ] ] 
	edge [ source 15485 target 15508 graphics [ fill "#0000ff" ] ] 
	edge [ source 15508 target 15511 graphics [ fill "#000000" ] label "[100%]"] 
	edge [ source 15509 target 15489 graphics [ fill "#000000" ] ] 
	edge [ source 15490 target 15491 graphics [ fill "#0000ff" ] ] 
	edge [ source 15490 target 15492 graphics [ fill "#000000" ] ] 
	edge [ source 15491 target 15493 graphics [ fill "#000000" ] ] 
	edge [ source 15492 target 15494 graphics [ fill "#0000ff" ] ] 
	edge [ source 15492 target 15495 graphics [ fill "#000000" ] ] 
	edge [ source 15494 target 15493 graphics [ fill "#000000" ] ] 
	edge [ source 15495 target 15496 graphics [ fill "#0000ff" ] ] 
	edge [ source 15495 target 15497 graphics [ fill "#000000" ] ] 
	edge [ source 15496 target 15493 graphics [ fill "#000000" ] ] 
	edge [ source 15497 target 15498 graphics [ fill "#0000ff" ] ] 
	edge [ source 15497 target 15499 graphics [ fill "#000000" ] ] 
	edge [ source 15498 target 15493 graphics [ fill "#000000" ] ] 
	edge [ source 15499 target 15487 graphics [ fill "#000000" ] ] 
	edge [ source 15488 target 15487 graphics [ fill "#0000ff" ] ] 
	edge [ source 15487 target 15488 graphics [ fill "#000000" ] ] 
	edge [ source 15487 target 15493 graphics [ fill "#0000ff" ] ] 
	edge [ source 15493 target 15489 graphics [ fill "#0000ff" ] ] 
	edge [ source 15489 target 15490 graphics [ fill "#000000" ] ] 
	edge [ source 15489 target 15510 graphics [ fill "#0000ff" ] ] 
	edge [ source 15510 target 15511 graphics [ fill "#0000ff" ] ] 
	edge [ source 15511 target 15501 graphics [ fill "#0000ff" ] label "[100%]"] 
]
