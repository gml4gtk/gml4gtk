graph [
 
 node [id 1 label "  statement_list | 0  | 1   "  ] 
 node [id 2 label "  bind_expr | type  | body   "  ] 
 node [id 3 label "  return_expr | type  | expr   "  ] 
 node [id 4 label "  void_type | name  | algn:8  "  ] 
 node [id 5 label "  return_expr | type  | expr   "  ] 
 node [id 6 label "  modify_expr | type  | op | 0  | op | 1   "  ] 
 node [id 7 label "  type_decl | name  | type   "  ] 
 node [id 8 label "  modify_expr | type  | op | 0  | op | 1   "  ] 
 node [id 9 label "  integer_type | name  | size  | algn:32 | prec:32 | sign:signed | min  | max   "  ] 
 node [id 10 label "  result_decl | type  | scpe  | srcp:a.c:4 | note:artificial | size  | algn:32  "  ] 
 node [id 11 label "  integer_cst | type  | int:0  "  ] 
 node [id 12 label "  identifier_node | strg:void | lngt:4  "  ] 
 node [id 13 label "  type_decl | name  | type   "  ] 
 node [id 14 label "  integer_cst | type  | int:32  "  ] 
 node [id 15 label "  integer_cst | type  | int:-2147483648  "  ] 
 node [id 16 label "  integer_cst | type  | int:2147483647  "  ] 
 node [id 17 label "  function_decl | name  | type  | srcp:a.c:4 | args  | link:extern  "  ] 
 node [id 18 label "  identifier_node | strg:int | lngt:3  "  ] 
 node [id 19 label "  integer_type | name  | size  | algn:128 | prec:128 | sign:unsigned | min  | max   "  ] 
 node [id 20 label "  identifier_node | strg:main | lngt:4  "  ] 
 node [id 21 label "  function_type | size  | algn:8 | retn  | prms   "  ] 
 node [id 22 label "  parm_decl | name  | type  | scpe  | srcp:a.c:4 | argt  | size  | algn:32 | used:0  "  ] 
 node [id 23 label "  identifier_node | strg:bitsizetype | lngt:11  "  ] 
 node [id 24 label "  integer_cst | type  | int:128  "  ] 
 node [id 25 label "  integer_cst | type  | int:0  "  ] 
 node [id 26 label "  integer_cst | type  | int:-1  "  ] 
 node [id 27 label "  integer_cst | type  | int:8  "  ] 
 node [id 28 label "  tree_list | valu  | chan   "  ] 
 node [id 29 label "  identifier_node | strg:argc | lngt:4  "  ] 
 node [id 30 label "  tree_list | valu  | chan   "  ] 
 node [id 31 label "  pointer_type | size  | algn:64 | ptd   "  ] 
 node [id 32 label "  tree_list | valu   "  ] 
 node [id 33 label "  integer_cst | type  | int:64  "  ] 
 node [id 34 label "  pointer_type | size  | algn:64 | ptd   "  ] 
 node [id 35 label "  integer_type | name  | size  | algn:8 | prec:8 | sign:signed | min  | max   "  ] 
 node [id 36 label "  type_decl | name  | type   "  ] 
 node [id 37 label "  integer_cst | type  | int:-128  "  ] 
 node [id 38 label "  integer_cst | type  | int:127  "  ] 
 node [id 39 label "  identifier_node | strg:char | lngt:4  "  ]


 
# node 1 statement_list | 0  | 1 
 edge [ source 1 target 2 ]
 edge [ source 1 target 3 ] 
# node 2 bind_expr | type  | body 
 edge [ source 2 target 4 ]
 edge [ source 2 target 5 ] 
# node 3 return_expr | type  | expr 
 edge [ source 3 target 4 ]
 edge [ source 3 target 6 ] 
# node 4 void_type | name  | algn:8
 edge [ source 4 target 7 ] 
# node 5 return_expr | type  | expr 
 edge [ source 5 target 4 ]
 edge [ source 5 target 8 ] 
# node 6 modify_expr | type  | op | 0  | op | 1 
 edge [ source 6 target 9 ]
 edge [ source 6 target 10 ]
 edge [ source 6 target 11 ] 
# node 7 type_decl | name  | type 
 edge [ source 7 target 12 ]
 edge [ source 7 target 4 ] 
# node 8 modify_expr | type  | op | 0  | op | 1 
 edge [ source 8 target 9 ]
 edge [ source 8 target 10 ]
 edge [ source 8 target 11 ] 
# node 9 integer_type | name  | size  | algn:32 | prec:32 | sign:signed | min  | max 
 edge [ source 9 target 13 ]
 edge [ source 9 target 14 ]
 edge [ source 9 target 15 ]
 edge [ source 9 target 16 ] 
# node 10 result_decl | type  | scpe  | srcp:a.c:4 | note:artificial | size  | algn:32
 edge [ source 10 target 9 ]
 edge [ source 10 target 17 ]
 edge [ source 10 target 14 ] 
# node 11 integer_cst | type  | int:0
 edge [ source 11 target 9 ] 
# node 12 identifier_node | strg:void | lngt:4 
# node 13 type_decl | name  | type 
 edge [ source 13 target 18 ]
 edge [ source 13 target 9 ] 
# node 14 integer_cst | type  | int:32
 edge [ source 14 target 19 ] 
# node 15 integer_cst | type  | int:-2147483648
 edge [ source 15 target 9 ] 
# node 16 integer_cst | type  | int:2147483647
 edge [ source 16 target 9 ] 
# node 17 function_decl | name  | type  | srcp:a.c:4 | args  | link:extern
 edge [ source 17 target 20 ]
 edge [ source 17 target 21 ]
 edge [ source 17 target 22 ] 
# node 18 identifier_node | strg:int | lngt:3 
# node 19 integer_type | name  | size  | algn:128 | prec:128 | sign:unsigned | min  | max 
 edge [ source 19 target 23 ]
 edge [ source 19 target 24 ]
 edge [ source 19 target 25 ]
 edge [ source 19 target 26 ] 
# node 20 identifier_node | strg:main | lngt:4 
# node 21 function_type | size  | algn:8 | retn  | prms 
 edge [ source 21 target 27 ]
 edge [ source 21 target 9 ]
 edge [ source 21 target 28 ] 
# node 22 parm_decl | name  | type  | scpe  | srcp:a.c:4 | argt  | size  | algn:32 | used:0
 edge [ source 22 target 29 ]
 edge [ source 22 target 9 ]
 edge [ source 22 target 17 ]
 edge [ source 22 target 9 ]
 edge [ source 22 target 14 ] 
# node 23 identifier_node | strg:bitsizetype | lngt:11 
# node 24 integer_cst | type  | int:128
 edge [ source 24 target 19 ] 
# node 25 integer_cst | type  | int:0
 edge [ source 25 target 19 ] 
# node 26 integer_cst | type  | int:-1
 edge [ source 26 target 19 ] 
# node 27 integer_cst | type  | int:8
 edge [ source 27 target 19 ] 
# node 28 tree_list | valu  | chan 
 edge [ source 28 target 9 ]
 edge [ source 28 target 30 ] 
# node 29 identifier_node | strg:argc | lngt:4 
# node 30 tree_list | valu  | chan 
 edge [ source 30 target 31 ]
 edge [ source 30 target 32 ] 
# node 31 pointer_type | size  | algn:64 | ptd 
 edge [ source 31 target 33 ]
 edge [ source 31 target 34 ] 
# node 32 tree_list | valu 
 edge [ source 32 target 4 ] 
# node 33 integer_cst | type  | int:64
 edge [ source 33 target 19 ] 
# node 34 pointer_type | size  | algn:64 | ptd 
 edge [ source 34 target 33 ]
 edge [ source 34 target 35 ] 
# node 35 integer_type | name  | size  | algn:8 | prec:8 | sign:signed | min  | max 
 edge [ source 35 target 36 ]
 edge [ source 35 target 27 ]
 edge [ source 35 target 37 ]
 edge [ source 35 target 38 ] 
# node 36 type_decl | name  | type 
 edge [ source 36 target 39 ]
 edge [ source 36 target 35 ] 
# node 37 integer_cst | type  | int:-128
 edge [ source 37 target 35 ] 
# node 38 integer_cst | type  | int:127
 edge [ source 38 target 35 ] 
# node 39 identifier_node | strg:char | lngt:4
]

