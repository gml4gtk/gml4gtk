# this is a comment line
# colors in nodes/edges using 'fill'
# background color of a node is set using `fill'
# border color of a node is set using `outline'
# edge line color is set using `fill'
graph [
  directed 1
  node [ id 0 label "n0" graphics [ fill "#f00000" ] ]
  node [ id 1 label "n1" graphics [ outline "#ff0000" fill "#00ff00" ] ]
  node [ id 2 label "n2" graphics [ outline "#00ff00" fill "#f0ff00" ] ]
  node [ id 3 label "n3" graphics [ outline "#0000ff" fill "#f08000" ] ]
  node [ id 4 label "n4" graphics [ fill "#f0000f" ] ]
  node [ id 5 label "n5" graphics [ outline "#f0000f" fill "#ffffff" ] ]
  edge [ source 4 target 0 graphics [ fill "#f000ff" ] ]
  edge [ source 0 target 1 label "foo" graphics [ fill "#0f0ff0" ] ]
  edge [ source 1 target 2 graphics [ fill "#abf000" ] ]
  edge [ source 2 target 3 graphics [ fill "#f0f000" ] ]
  edge [ source 3 target 0 graphics [ fill "#f000f0" ] ]
  edge [ source 3 target 0 graphics [ fill "#ff000b" ] ]
  edge [ source 5 target 0 graphics [ fill "#ff000b" ] ]
]

