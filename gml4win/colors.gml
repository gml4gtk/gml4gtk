# this is a comment line
# colors in nodes/edges are set using 'fill'
# background color of a node is set using `fill'
# border color of a node is set using `outline'
# edge line color is set using `fill'
# the color is html style #rrggbb
# #ff0000 is red, #00ff00 is green, #0000ff is blue
# textcolor or edgelabel color cannot be set and is black
graph [
  directed 1
# this sets the background color of node "n0"
  node [ id 0 label "n0" graphics [ fill "#f00000" ] ]
# this sets the background and border color of node "n1"
  node [ id 1 label "n1" graphics [ outline "#ff0000" fill "#00ff00" ] ]
  node [ id 2 label "n2" graphics [ outline "#00ff00" fill "#f0ff00" ] ]
  node [ id 3 label "n3" graphics [ outline "#0000ff" fill "#f08000" ] ]
  node [ id 4 label "n4" graphics [ fill "#f0000f" ] ]
  node [ id 5 label "n5" graphics [ outline "#f0000f" fill "#ffffff" ] ]
  node [ id 6 label "WWW" ]
  edge [ source 6 target 0 ]
# this sets the edge line color between node 4 and node 0
  edge [ source 4 target 0 graphics [ fill "#f000ff" ] ]
# this sets the edge line color between node 0 and node 1 and a edgelabel with a newline in it
  edge [ source 0 target 1 label "foo
bar" graphics [ fill "#000ff0" ] ]
  edge [ source 1 target 2 graphics [ fill "#abf000" ] ]
  edge [ source 2 target 3 graphics [ fill "#f0f000" ] ]
  edge [ source 3 target 0 graphics [ fill "#f000f0" ] ]
# this sets the edge line color between node 3 and node 0 and a edgelabel
  edge [ source 3 target 0 label "this is a\nedgelabel" graphics [ fill "#ff000b" ] ]
  edge [ source 5 target 0 graphics [ fill "#ff000b" ] ]
]

