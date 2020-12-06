graph [
 directed 1
 node [ id 0 label " program ::= * stdelimit exprlist enddelimit
	stdelimit ::= * ST_DELIMIT
	 " ]
 node [ id 1 label " program ::= stdelimit * exprlist enddelimit
	exprlist ::= * expr
	expr ::= * expr PLUS expr
	expr ::= * expr MUL expr
	expr ::= * number
	number ::= * INTEGER
	number ::= * FLOAT
	 " ]
 node [ id 2 label " expr ::= * expr PLUS expr
	expr ::= expr PLUS * expr
	expr ::= * expr MUL expr
	expr ::= * number
	number ::= * INTEGER
	number ::= * FLOAT
	 " ]
 node [ id 3 label " expr ::= * expr PLUS expr
	expr ::= * expr MUL expr
	expr ::= expr MUL * expr
	expr ::= * number
	number ::= * INTEGER
	number ::= * FLOAT
	 " ]
 node [ id 4 label " program ::= stdelimit exprlist * enddelimit
	enddelimit ::= * END_DELIMIT
	 " ]
 node [ id 5 label " exprlist ::= expr *
	expr ::= expr * PLUS expr
	expr ::= expr * MUL expr
	 " ]
 node [ id 6 label " program ::= stdelimit exprlist enddelimit *
	 " ]
 node [ id 7 label " expr ::= expr * PLUS expr
	expr ::= expr PLUS expr *
	expr ::= expr * MUL expr
	 " ]
 node [ id 8 label " enddelimit ::= END_DELIMIT *
	 " ]
 node [ id 9 label " expr ::= expr * PLUS expr
	expr ::= expr * MUL expr
	expr ::= expr MUL expr *
	 " ]
 node [ id 10 label " expr ::= number *
	 " ]
 node [ id 11 label " number ::= INTEGER *
	 " ]
 node [ id 12 label " number ::= FLOAT *
	 " ]
 node [ id 13 label " stdelimit ::= ST_DELIMIT *
	 " ]
 edge [ source 0 target 13 label "ST_DELIMIT" ]
 edge [ source 0 target 1 label "stdelimit" ]
 edge [ source 1 target 11 label "INTEGER" ]
 edge [ source 1 target 12 label "FLOAT" ]
 edge [ source 1 target 4 label "exprlist" ]
 edge [ source 1 target 5 label "expr" ]
 edge [ source 1 target 10 label "number" ]
 edge [ source 2 target 11 label "INTEGER" ]
 edge [ source 2 target 12 label "FLOAT" ]
 edge [ source 2 target 7 label "expr" ]
 edge [ source 2 target 10 label "number" ]
 edge [ source 3 target 11 label "INTEGER" ]
 edge [ source 3 target 12 label "FLOAT" ]
 edge [ source 3 target 9 label "expr" ]
 edge [ source 3 target 10 label "number" ]
 edge [ source 4 target 8 label "END_DELIMIT" ]
 edge [ source 4 target 6 label "enddelimit" ]
 edge [ source 5 target 2 label "PLUS" ]
 edge [ source 5 target 3 label "MUL" ]
 edge [ source 7 target 3 label "MUL" ]

]
