Creator	"yFiles"
Version	"2.12"
graph
[
	hierarchic	1
	label	""
	directed	1
	node
	[
		id	0
		label	"Wetlands"
		graphics
		[
			x	233.0
			y	141.0
			w	86.0
			h	30.0
			type	"ellipse"
			fill	"#FFCC00"
			outline	"#000000"
		]
		LabelGraphics
		[
			text	"Wetlands"
			fontSize	12
			fontName	"Dialog"
			anchor	"c"
		]
	]
	node
	[
		id	1
		label	"Fish"
		graphics
		[
			x	454.0
			y	208.0
			w	82.0
			h	30.0
			type	"ellipse"
			fill	"#FFCC00"
			outline	"#000000"
		]
		LabelGraphics
		[
			text	"Fish"
			fontSize	12
			fontName	"Dialog"
			anchor	"c"
		]
	]
	node
	[
		id	2
		label	"Poluution"
		graphics
		[
			x	464.0
			y	352.0
			w	84.0
			h	30.0
			type	"ellipse"
			fill	"#FFCC00"
			outline	"#000000"
		]
		LabelGraphics
		[
			text	"Poluution"
			fontSize	12
			fontName	"Dialog"
			anchor	"c"
		]
	]
	node
	[
		id	3
		label	"Livelihood"
		graphics
		[
			x	293.0
			y	386.0
			w	80.0
			h	30.0
			type	"ellipse"
			fill	"#FFCC00"
			outline	"#000000"
		]
		LabelGraphics
		[
			text	"Livelihood"
			fontSize	12
			fontName	"Dialog"
			anchor	"c"
		]
	]
	node
	[
		id	4
		label	"Laws"
		graphics
		[
			x	138.0
			y	260.0
			w	62.0
			h	30.0
			type	"ellipse"
			fill	"#FFCC00"
			outline	"#000000"
		]
		LabelGraphics
		[
			text	"Laws"
			fontSize	12
			fontName	"Dialog"
			anchor	"c"
		]
	]
	edge
	[
		source	4
		target	0
		label	"0.2"
		graphics
		[
			fill	"#000000"
			targetArrow	"standard"
		]
		LabelGraphics
		[
			text	"0.2"
			fontSize	12
			fontName	"Dialog"
			configuration	"AutoFlippingLabel"
			contentWidth	20.681640625
			contentHeight	18.701171875
			model	"centered"
			position	"center"
		]
	]
	edge
	[
		source	2
		target	0
		label	"-0.2"
		graphics
		[
			smoothBends	1
			fill	"#000000"
			targetArrow	"standard"
			Line
			[
				point
				[
					x	464.0
					y	352.0
				]
				point
				[
					x	412.0
					y	310.0
				]
				point
				[
					x	233.0
					y	141.0
				]
			]
		]
		LabelGraphics
		[
			text	"-0.2"
			fontSize	12
			fontName	"Dialog"
			configuration	"AutoFlippingLabel"
			contentWidth	24.677734375
			contentHeight	18.701171875
			model	"centered"
			position	"center"
		]
	]
	edge
	[
		source	0
		target	1
		label	"1"
		graphics
		[
			fill	"#000000"
			targetArrow	"standard"
		]
		LabelGraphics
		[
			text	"1"
			fontSize	12
			fontName	"Dialog"
			configuration	"AutoFlippingLabel"
			contentWidth	10.673828125
			contentHeight	18.701171875
			model	"centered"
			position	"center"
		]
	]
	edge
	[
		source	4
		target	1
		label	"0.5"
		graphics
		[
			fill	"#000000"
			targetArrow	"standard"
		]
		LabelGraphics
		[
			text	"0.5"
			fontSize	12
			fontName	"Dialog"
			configuration	"AutoFlippingLabel"
			contentWidth	20.681640625
			contentHeight	18.701171875
			model	"centered"
			position	"center"
		]
	]
	edge
	[
		source	0
		target	2
		label	"-0.1"
		graphics
		[
			smoothBends	1
			fill	"#000000"
			targetArrow	"standard"
			Line
			[
				point
				[
					x	233.0
					y	141.0
				]
				point
				[
					x	374.0
					y	207.0
				]
				point
				[
					x	464.0
					y	352.0
				]
			]
		]
		LabelGraphics
		[
			text	"-0.1"
			fontSize	12
			fontName	"Dialog"
			configuration	"AutoFlippingLabel"
			contentWidth	24.677734375
			contentHeight	18.701171875
			model	"centered"
			position	"center"
		]
	]
	edge
	[
		source	2
		target	3
		label	"-0.2"
		graphics
		[
			fill	"#000000"
			targetArrow	"standard"
		]
		LabelGraphics
		[
			text	"-0.2"
			fontSize	12
			fontName	"Dialog"
			configuration	"AutoFlippingLabel"
			contentWidth	24.677734375
			contentHeight	18.701171875
			model	"centered"
			position	"center"
		]
	]
	edge
	[
		source	1
		target	3
		label	"1"
		graphics
		[
			fill	"#000000"
			targetArrow	"standard"
		]
		LabelGraphics
		[
			text	"1"
			fontSize	12
			fontName	"Dialog"
			configuration	"AutoFlippingLabel"
			contentWidth	10.673828125
			contentHeight	18.701171875
			model	"centered"
			position	"center"
		]
	]
	edge
	[
		source	0
		target	3
		label	"0.8"
		graphics
		[
			fill	"#000000"
			targetArrow	"standard"
		]
		LabelGraphics
		[
			text	"0.8"
			fontSize	12
			fontName	"Dialog"
			configuration	"AutoFlippingLabel"
			contentWidth	20.681640625
			contentHeight	18.701171875
			model	"centered"
			position	"center"
		]
	]
	edge
	[
		source	4
		target	3
		label	"-0.2"
		graphics
		[
			fill	"#000000"
			targetArrow	"standard"
		]
		LabelGraphics
		[
			text	"-0.2"
			fontSize	12
			fontName	"Dialog"
			configuration	"AutoFlippingLabel"
			contentWidth	24.677734375
			contentHeight	18.701171875
			model	"centered"
			position	"center"
		]
	]
	edge
	[
		source	4
		target	2
		label	"-0.5"
		graphics
		[
			fill	"#000000"
			targetArrow	"standard"
		]
		LabelGraphics
		[
			text	"-0.5"
			fontSize	12
			fontName	"Dialog"
			configuration	"AutoFlippingLabel"
			contentWidth	24.677734375
			contentHeight	18.701171875
			model	"centered"
			position	"center"
		]
	]
	edge
	[
		source	2
		target	1
		label	"-1"
		graphics
		[
			fill	"#000000"
			targetArrow	"standard"
		]
		LabelGraphics
		[
			text	"-1"
			fontSize	12
			fontName	"Dialog"
			configuration	"AutoFlippingLabel"
			contentWidth	14.669921875
			contentHeight	18.701171875
			model	"centered"
			position	"center"
		]
	]
]
