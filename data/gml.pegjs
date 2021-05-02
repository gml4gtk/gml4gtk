
file = _ head _ id _ list _

head = (pair)*

list = "[" _ some_items* _ "]" _

some_items = id list2 / pair

list2 = _ "[" _ some_items* _ "]" _

pair = (id string) / (id id) / (id fpnum) / (id digit)

digit = (("-"[0-9]+ _ ) / ("+"[0-9]+ _ ) / ([0-9]+ _ ))

fpnum = (("-"[0-9]*["."][0-9]* _ ) / ("+"[0-9]*["."][0-9]* _ ) / ([0-9]*["."][0-9]* _ ))

id	=  [a-zA-Z_]+[a-zA-Z_0-9]*  _

string	= '"'  char*  '"'  _

char	=
	"\\" "\""
	/ "\\" "\\"
	/ "\\" "b"
	/ "\\" "f"
	/ "\\" "n"
	/ "\\" "r"
	/ "\\" "t"
	/ (!"\"" .)

_	=		(space / comment / endofline)*

space	=	(" " / "\t" / endofline)

comment	=	"#" (!endofline .)*

endofline	=	( "\r\n" / "\n" / "\r" / "\n\r" )

