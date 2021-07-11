# RTL graph generated with GCC 10.1
graph [

  directed 1



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

]
