# set the fontcolor in the labelgraphics section example
graph
[ hierarchic  1
  directed  1
  defaultnodesize "labelsize"
  node  [ id  0  LabelGraphics [ text  "January" color "#00ff00" ]  ]  
  node  [ id  1  LabelGraphics [ text  "December" color "#0000ff" ]  ]  
  node  [ id  2 label "label2"  LabelGraphics  [ text  "April" color "#ff0000" ]  ]  
  edge  [ source  1  target  0  ]
  edge  [ source  1  target  2  ]
]
