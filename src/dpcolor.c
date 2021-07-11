
/*
 *  Copyright 2021
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0+
 * License-Filename: LICENSE
 *
 * color can be a single number when a colorscheme is used:
 *  node [fontname = courier, shape = box, colorscheme = paired6]
 *  "0R1" [label="R1", fillcolor=3, shape=diamond, style=filled]
 *
 * Usable color info:
 * https://en.wikipedia.org/wiki/RGB_color_model
 * https://en.wikipedia.org/wiki/HSL_and_HSV
 * https://en.wikipedia.org/wiki/X11_color_names
 * color data based on data in x11 server src oscolor.c
 * april 2016
 * https://cgit.freedesktop.org/xorg/xserver/tree/os/oscolor.c
 * blob: 017aab1f2c1ced555230c9899867c0edc5876ba7
 *
 * to workaround GCC compiler colorname bug a second
 * copy of a name with a space is included without space
 * then "light grey" is also known as "lightgrey" and "LightGrey"
 */

/*

Gcc-7 uses wrong colornames in graphviz dot files.
For example lightgrey should be LightGrey.

The dot program does accept this but is wrong because it is not a official x11 colorname.
the program uses x11 colornames and does not accept lightgrey.

This are places in GCC-7 where graphviz graph data is generated:

graph.c:  pp_string (pp, "digraph \"");
graphite-scop-detection.c:  fprintf (file, "digraph all {\n");
sched-rgn.c:  fprintf (f, "digraph Region_%d {\n", rgn);
sched-rgn.c:  pp_printf (&pp, "digraph SchedDG {\n");
sel-sched-dump.c:  fprintf (f, "digraph G {\n"
tree-loop-distribution.c:  fprintf (file, "digraph RDG {\n");
tree-ssa-structalias.c:  fprintf (file, "strict digraph {\n");
tree-ssa-structalias.c:  fprintf (file, "strict digraph {\n");

in graph.c is:

   Copyright (C) 1998 Free Software Foundation, Inc.

   Draw a basic block BB belonging to the function with FUNCDEF_NO
   as its unique number.
static void
draw_cfg_node (pretty_printer *pp, int funcdef_no, basic_block bb)
{
  const char *shape;
  const char *fillcolor;

  if (bb->index == ENTRY_BLOCK || bb->index == EXIT_BLOCK)
    {
      shape = "Mdiamond";
      fillcolor = "white";
    }
  else
    {
      shape = "record";
      fillcolor =
    BB_PARTITION (bb) == BB_HOT_PARTITION ? "lightpink"
    : BB_PARTITION (bb) == BB_COLD_PARTITION ? "lightblue"
    : "lightgrey";
    }

   Draw all the basic blocks in LOOP.  Print the blocks in breath-first
   order to get a good ranking of the nodes.  This function is recursive:
   It first prints inner loops, then the body of LOOP itself.

static void
draw_cfg_nodes_for_loop (pretty_printer *pp, int funcdef_no,
             struct loop *loop)
{
  basic_block *body;
  unsigned int i;
  const char *fillcolors[3] = { "grey88", "grey77", "grey66" };

  if (loop->header != NULL
      && loop->latch != EXIT_BLOCK_PTR_FOR_FN (cfun))
    pp_printf (pp,
           "\tsubgraph cluster_%d_%d {\n"
           "\tstyle=\"filled\";\n"
           "\tcolor=\"darkgreen\";\n"
           "\tfillcolor=\"%s\";\n"
           "\tlabel=\"loop %d\";\n"
           "\tlabeljust=l;\n"
           "\tpenwidth=2;\n",
           funcdef_no, loop->num,
           fillcolors[(loop_depth (loop) - 1) % 3],
           loop->num);

The oficial list of x11 colornames is at freedesktop.org:

https://cgit.freedesktop.org/xorg/app/rgb/tree/rgb.txt

and there is light grey defined:

211 211 211        light grey
211 211 211        LightGrey
255 182 193        light pink
255 182 193        LightPink
173 216 230        light blue
173 216 230        LightBlue
  0 100   0        dark green
  0 100   0        DarkGreen

In graph.c the colornames in GCC data should be renamed to LightGrey,
LightPink, LightBlue and DarkGreen to comply with x11 names.

a gtk+ gui alternative to dot to use with GCC data

for example in a edge color can be a color list using ':'
as in a->b[color=red:blue:green]

when color is "" then the default is taken, example:
digraph {
 node[color=red];
 aaa[color=""];
}

transparent is used as background color

*/

#include "config.h"

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <errno.h>

#include "splay-tree.h"

#include "main.h"
#include "dpcolor.h"
#include "dpus.h"

/* drawing background color */
int dp_bgcr = 0xff;		/* (red) white */
int dp_bgcg = 0xff;		/* (green) white */
int dp_bgcb = 0xff;		/* (blue) white */

/* color names database */
static splay_tree gucolor = NULL;

/* The type of a function used to deallocate any resources associated
   with the key.  */
static void ucolor_splay_tree_delete_key_fn(splay_tree_key keydata);
/* The type of a function used to deallocate any resources associated
   with the value.  */
static void ucolor_splay_tree_delete_value_fn(splay_tree_value valuedata);
/* add color data */
static void colordata(int rev);
/* add 1 color to database */
static void coloradd(const char *name, int code, int rev);

/* The type of a function used to deallocate any resources associated
   with the key.  */
static void ucolor_splay_tree_delete_key_fn(splay_tree_key keydata)
{

	/* char *key is free'ed in uniq string */
	if (keydata) {
	}

	return;
}

/* The type of a function used to deallocate any resources associated
   with the value.  */
static void ucolor_splay_tree_delete_value_fn(splay_tree_value valuedata)
{

	/* value is a static int */
	if (valuedata) {
	}

	return;
}

/* get number code for dot colorscheme 
accent3 color scheme
accent4 color scheme
accent5 color scheme
accent6 color scheme
accent7 color scheme
accent8 color scheme
blues3 color scheme
blues4 color scheme
blues5 color scheme
blues6 color scheme
blues7 color scheme
blues8 color scheme
blues9 color scheme
brbg10 color scheme
brbg11 color scheme
brbg3 color scheme
brbg4 color scheme
brbg5 color scheme
brbg6 color scheme
brbg7 color scheme
brbg8 color scheme
brbg9 color scheme
bugn3 color scheme
bugn4 color scheme
bugn5 color scheme
bugn6 color scheme
bugn7 color scheme
bugn8 color scheme
bugn9 color scheme
bupu3 color scheme
bupu4 color scheme
bupu5 color scheme
bupu6 color scheme
bupu7 color scheme
bupu8 color scheme
bupu9 color scheme
dark23 color scheme
dark24 color scheme
dark25 color scheme
dark26 color scheme
dark27 color scheme
dark28 color scheme
gnbu3 color scheme
gnbu4 color scheme
gnbu5 color scheme
gnbu6 color scheme
gnbu7 color scheme
gnbu8 color scheme
gnbu9 color scheme
greens3 color scheme
greens4 color scheme
greens5 color scheme
greens6 color scheme
greens7 color scheme
greens8 color scheme
greens9 color scheme
greys3 color scheme
greys4 color scheme
greys5 color scheme
greys6 color scheme
greys7 color scheme
greys8 color scheme
greys9 color scheme
oranges3 color scheme
oranges4 color scheme
oranges5 color scheme
oranges6 color scheme
oranges7 color scheme
oranges8 color scheme
oranges9 color scheme
orrd3 color scheme
orrd4 color scheme
orrd5 color scheme
orrd6 color scheme
orrd7 color scheme
orrd8 color scheme
orrd9 color scheme
paired10 color scheme
paired11 color scheme
paired12 color scheme
paired3 color scheme
paired4 color scheme
paired5 color scheme
paired6 color scheme
paired7 color scheme
paired8 color scheme
paired9 color scheme
pastel13 color scheme
pastel14 color scheme
pastel15 color scheme
pastel16 color scheme
pastel17 color scheme
pastel18 color scheme
pastel19 color scheme
pastel23 color scheme
pastel24 color scheme
pastel25 color scheme
pastel26 color scheme
pastel27 color scheme
pastel28 color scheme
piyg10 color scheme
piyg11 color scheme
piyg3 color scheme
piyg4 color scheme
piyg5 color scheme
piyg6 color scheme
piyg7 color scheme
piyg8 color scheme
piyg9 color scheme
prgn10 color scheme
prgn11 color scheme
prgn3 color scheme
prgn4 color scheme
prgn5 color scheme
prgn6 color scheme
prgn7 color scheme
prgn8 color scheme
prgn9 color scheme
pubu3 color scheme
pubu4 color scheme
pubu5 color scheme
pubu6 color scheme
pubu7 color scheme
pubu8 color scheme
pubu9 color scheme
pubugn3 color scheme
pubugn4 color scheme
pubugn5 color scheme
pubugn6 color scheme
pubugn7 color scheme
pubugn8 color scheme
pubugn9 color scheme
puor10 color scheme
puor11 color scheme
puor3 color scheme
puor4 color scheme
puor5 color scheme
puor6 color scheme
puor7 color scheme
puor8 color scheme
puor9 color scheme
purd3 color scheme
purd4 color scheme
purd5 color scheme
purd6 color scheme
purd7 color scheme
purd8 color scheme
purd9 color scheme
purples3 color scheme
purples4 color scheme
purples5 color scheme
purples6 color scheme
purples7 color scheme
purples8 color scheme
purples9 color scheme
rdbu10 color scheme
rdbu11 color scheme
rdbu3 color scheme
rdbu4 color scheme
rdbu5 color scheme
rdbu6 color scheme
rdbu7 color scheme
rdbu8 color scheme
rdbu9 color scheme
rdgy10 color scheme
rdgy11 color scheme
rdgy3 color scheme
rdgy4 color scheme
rdgy5 color scheme
rdgy6 color scheme
rdgy7 color scheme
rdgy8 color scheme
rdgy9 color scheme
rdpu3 color scheme
rdpu4 color scheme
rdpu5 color scheme
rdpu6 color scheme
rdpu7 color scheme
rdpu8 color scheme
rdpu9 color scheme
rdylbu10 color scheme
rdylbu11 color scheme
rdylbu3 color scheme
rdylbu4 color scheme
rdylbu5 color scheme
rdylbu6 color scheme
rdylbu7 color scheme
rdylbu8 color scheme
rdylbu9 color scheme
rdylgn10 color scheme
rdylgn11 color scheme
rdylgn3 color scheme
rdylgn4 color scheme
rdylgn5 color scheme
rdylgn6 color scheme
rdylgn7 color scheme
rdylgn8 color scheme
rdylgn9 color scheme
reds3 color scheme
reds4 color scheme
reds5 color scheme
reds6 color scheme
reds7 color scheme
reds8 color scheme
reds9 color scheme
set13 color scheme
set14 color scheme
set15 color scheme
set16 color scheme
set17 color scheme
set18 color scheme
set19 color scheme
set23 color scheme
set24 color scheme
set25 color scheme
set26 color scheme
set27 color scheme
set28 color scheme
set310 color scheme
set311 color scheme
set312 color scheme
set33 color scheme
set34 color scheme
set35 color scheme
set36 color scheme
set37 color scheme
set38 color scheme
set39 color scheme
spectral10 color scheme
spectral11 color scheme
spectral3 color scheme
spectral4 color scheme
spectral5 color scheme
spectral6 color scheme
spectral7 color scheme
spectral8 color scheme
spectral9 color scheme
ylgn3 color scheme
ylgn4 color scheme
ylgn5 color scheme
ylgn6 color scheme
ylgn7 color scheme
ylgn8 color scheme
ylgn9 color scheme
ylgnbu3 color scheme
ylgnbu4 color scheme
ylgnbu5 color scheme
ylgnbu6 color scheme
ylgnbu7 color scheme
ylgnbu8 color scheme
ylgnbu9 color scheme
ylorbr3 color scheme
ylorbr4 color scheme
ylorbr5 color scheme
ylorbr6 color scheme
ylorbr7 color scheme
ylorbr8 color scheme
ylorbr9 color scheme
ylorrd3 color scheme
ylorrd4 color scheme
ylorrd5 color scheme
ylorrd6 color scheme
ylorrd7 color scheme
ylorrd8 color scheme
ylorrd9 color scheme
*/

/* return -1 on parse error
 * return 0 to tuen colorcheme off with "" 
*/
int dp_colorschemecode(const char *name)
{
	int ret = 0;

	/* check arg */
	if (name == NULL) {
		return (0);
	}
	if (strlen(name) == 0) {
		return (0);
	}

	if (strcasecmp(name, "x11") == 0) {
		return (0);
	}

	switch (*name) {
	case 'a':
		if (strcasecmp(name, "accent3") == 0) {
			ret = COLOR_NS_ACCENT3;
		} else if (strcasecmp(name, "accent4") == 0) {
			ret = COLOR_NS_ACCENT4;
		} else if (strcasecmp(name, "accent5") == 0) {
			ret = COLOR_NS_ACCENT5;
		} else if (strcasecmp(name, "accent6") == 0) {
			ret = COLOR_NS_ACCENT6;
		} else if (strcasecmp(name, "accent7") == 0) {
			ret = COLOR_NS_ACCENT7;
		} else if (strcasecmp(name, "accent8") == 0) {
			ret = COLOR_NS_ACCENT8;
		} else {
			ret = -1;
		}
		break;
	case 'b':
		if (strcasecmp(name, "blues3") == 0) {
			ret = COLOR_NS_BLUES3;
		} else if (strcasecmp(name, "blues4") == 0) {
			ret = COLOR_NS_BLUES4;
		} else if (strcasecmp(name, "blues5") == 0) {
			ret = COLOR_NS_BLUES5;
		} else if (strcasecmp(name, "blues6") == 0) {
			ret = COLOR_NS_BLUES6;
		} else if (strcasecmp(name, "blues7") == 0) {
			ret = COLOR_NS_BLUES7;
		} else if (strcasecmp(name, "blues8") == 0) {
			ret = COLOR_NS_BLUES8;
		} else if (strcasecmp(name, "blues9") == 0) {
			ret = COLOR_NS_BLUES9;
		} else if (strcasecmp(name, "brbg10") == 0) {
			ret = COLOR_NS_BRBG10;
		} else if (strcasecmp(name, "brbg11") == 0) {
			ret = COLOR_NS_BRBG11;
		} else if (strcasecmp(name, "brbg3") == 0) {
			ret = COLOR_NS_BRBG3;
		} else if (strcasecmp(name, "brbg4") == 0) {
			ret = COLOR_NS_BRBG4;
		} else if (strcasecmp(name, "brbg5") == 0) {
			ret = COLOR_NS_BRBG5;
		} else if (strcasecmp(name, "brbg6") == 0) {
			ret = COLOR_NS_BRBG6;
		} else if (strcasecmp(name, "brbg7") == 0) {
			ret = COLOR_NS_BRBG7;
		} else if (strcasecmp(name, "brbg8") == 0) {
			ret = COLOR_NS_BRBG8;
		} else if (strcasecmp(name, "brbg9") == 0) {
			ret = COLOR_NS_BRBG9;
		} else if (strcasecmp(name, "bugn3") == 0) {
			ret = COLOR_NS_BUGN3;
		} else if (strcasecmp(name, "bugn4") == 0) {
			ret = COLOR_NS_BUGN4;
		} else if (strcasecmp(name, "bugn5") == 0) {
			ret = COLOR_NS_BUGN5;
		} else if (strcasecmp(name, "bugn6") == 0) {
			ret = COLOR_NS_BUGN6;
		} else if (strcasecmp(name, "bugn7") == 0) {
			ret = COLOR_NS_BUGN7;
		} else if (strcasecmp(name, "bugn8") == 0) {
			ret = COLOR_NS_BUGN8;
		} else if (strcasecmp(name, "bugn9") == 0) {
			ret = COLOR_NS_BUGN9;
		} else if (strcasecmp(name, "bupu3") == 0) {
			ret = COLOR_NS_BUPU3;
		} else if (strcasecmp(name, "bupu4") == 0) {
			ret = COLOR_NS_BUPU4;
		} else if (strcasecmp(name, "bupu5") == 0) {
			ret = COLOR_NS_BUPU5;
		} else if (strcasecmp(name, "bupu6") == 0) {
			ret = COLOR_NS_BUPU6;
		} else if (strcasecmp(name, "bupu7") == 0) {
			ret = COLOR_NS_BUPU7;
		} else if (strcasecmp(name, "bupu8") == 0) {
			ret = COLOR_NS_BUPU8;
		} else if (strcasecmp(name, "bupu9") == 0) {
			ret = COLOR_NS_BUPU9;
		} else {
			ret = -1;
		}
		break;
	case 'd':
		if (strcasecmp(name, "dark23") == 0) {
			ret = COLOR_NS_DARK23;
		} else if (strcasecmp(name, "dark24") == 0) {
			ret = COLOR_NS_DARK24;
		} else if (strcasecmp(name, "dark25") == 0) {
			ret = COLOR_NS_DARK25;
		} else if (strcasecmp(name, "dark26") == 0) {
			ret = COLOR_NS_DARK26;
		} else if (strcasecmp(name, "dark27") == 0) {
			ret = COLOR_NS_DARK27;
		} else if (strcasecmp(name, "dark28") == 0) {
			ret = COLOR_NS_DARK28;
		} else {
			ret = -1;
		}
		break;
	case 'g':
		if (strcasecmp(name, "gnbu3") == 0) {
			ret = COLOR_NS_GNBU3;
		} else if (strcasecmp(name, "gnbu4") == 0) {
			ret = COLOR_NS_GNBU4;
		} else if (strcasecmp(name, "gnbu5") == 0) {
			ret = COLOR_NS_GNBU5;
		} else if (strcasecmp(name, "gnbu6") == 0) {
			ret = COLOR_NS_GNBU6;
		} else if (strcasecmp(name, "gnbu7") == 0) {
			ret = COLOR_NS_GNBU7;
		} else if (strcasecmp(name, "gnbu8") == 0) {
			ret = COLOR_NS_GNBU8;
		} else if (strcasecmp(name, "gnbu9") == 0) {
			ret = COLOR_NS_GNBU9;
		} else if (strcasecmp(name, "greens3") == 0) {
			ret = COLOR_NS_GREENS3;
		} else if (strcasecmp(name, "greens4") == 0) {
			ret = COLOR_NS_GREENS4;
		} else if (strcasecmp(name, "greens5") == 0) {
			ret = COLOR_NS_GREENS5;
		} else if (strcasecmp(name, "greens6") == 0) {
			ret = COLOR_NS_GREENS6;
		} else if (strcasecmp(name, "greens7") == 0) {
			ret = COLOR_NS_GREENS7;
		} else if (strcasecmp(name, "greens8") == 0) {
			ret = COLOR_NS_GREENS8;
		} else if (strcasecmp(name, "greens9") == 0) {
			ret = COLOR_NS_GREENS9;
		} else if (strcasecmp(name, "greys3") == 0) {
			ret = COLOR_NS_GREYS3;
		} else if (strcasecmp(name, "greys4") == 0) {
			ret = COLOR_NS_GREYS4;
		} else if (strcasecmp(name, "greys5") == 0) {
			ret = COLOR_NS_GREYS5;
		} else if (strcasecmp(name, "greys6") == 0) {
			ret = COLOR_NS_GREYS6;
		} else if (strcasecmp(name, "greys7") == 0) {
			ret = COLOR_NS_GREYS7;
		} else if (strcasecmp(name, "greys8") == 0) {
			ret = COLOR_NS_GREYS8;
		} else if (strcasecmp(name, "greys9") == 0) {
			ret = COLOR_NS_GREYS9;
		} else {
			ret = -1;
		}
		break;
	case 'o':
		if (strcasecmp(name, "oranges3") == 0) {
			ret = COLOR_NS_ORANGES3;
		} else if (strcasecmp(name, "oranges4") == 0) {
			ret = COLOR_NS_ORANGES4;
		} else if (strcasecmp(name, "oranges5") == 0) {
			ret = COLOR_NS_ORANGES5;
		} else if (strcasecmp(name, "oranges6") == 0) {
			ret = COLOR_NS_ORANGES6;
		} else if (strcasecmp(name, "oranges7") == 0) {
			ret = COLOR_NS_ORANGES7;
		} else if (strcasecmp(name, "oranges8") == 0) {
			ret = COLOR_NS_ORANGES8;
		} else if (strcasecmp(name, "oranges9") == 0) {
			ret = COLOR_NS_ORANGES9;
		} else if (strcasecmp(name, "orrd3") == 0) {
			ret = COLOR_NS_ORRD3;
		} else if (strcasecmp(name, "orrd4") == 0) {
			ret = COLOR_NS_ORRD4;
		} else if (strcasecmp(name, "orrd5") == 0) {
			ret = COLOR_NS_ORRD5;
		} else if (strcasecmp(name, "orrd6") == 0) {
			ret = COLOR_NS_ORRD6;
		} else if (strcasecmp(name, "orrd7") == 0) {
			ret = COLOR_NS_ORRD7;
		} else if (strcasecmp(name, "orrd8") == 0) {
			ret = COLOR_NS_ORRD8;
		} else if (strcasecmp(name, "orrd9") == 0) {
			ret = COLOR_NS_ORRD9;
		} else {
			ret = -1;
		}
		break;
	case 'p':
		if (strcasecmp(name, "paired10") == 0) {
			ret = COLOR_NS_PAIRED10;
		} else if (strcasecmp(name, "paired11") == 0) {
			ret = COLOR_NS_PAIRED11;
		} else if (strcasecmp(name, "paired12") == 0) {
			ret = COLOR_NS_PAIRED12;
		} else if (strcasecmp(name, "paired3") == 0) {
			ret = COLOR_NS_PAIRED3;
		} else if (strcasecmp(name, "paired4") == 0) {
			ret = COLOR_NS_PAIRED4;
		} else if (strcasecmp(name, "paired5") == 0) {
			ret = COLOR_NS_PAIRED5;
		} else if (strcasecmp(name, "paired6") == 0) {
			ret = COLOR_NS_PAIRED6;
		} else if (strcasecmp(name, "paired7") == 0) {
			ret = COLOR_NS_PAIRED7;
		} else if (strcasecmp(name, "paired8") == 0) {
			ret = COLOR_NS_PAIRED8;
		} else if (strcasecmp(name, "paired9") == 0) {
			ret = COLOR_NS_PAIRED9;
		} else if (strcasecmp(name, "pastel13") == 0) {
			ret = COLOR_NS_PASTEL13;
		} else if (strcasecmp(name, "pastel14") == 0) {
			ret = COLOR_NS_PASTEL14;
		} else if (strcasecmp(name, "pastel15") == 0) {
			ret = COLOR_NS_PASTEL15;
		} else if (strcasecmp(name, "pastel16") == 0) {
			ret = COLOR_NS_PASTEL16;
		} else if (strcasecmp(name, "pastel17") == 0) {
			ret = COLOR_NS_PASTEL17;
		} else if (strcasecmp(name, "pastel18") == 0) {
			ret = COLOR_NS_PASTEL18;
		} else if (strcasecmp(name, "pastel19") == 0) {
			ret = COLOR_NS_PASTEL19;
		} else if (strcasecmp(name, "pastel23") == 0) {
			ret = COLOR_NS_PASTEL23;
		} else if (strcasecmp(name, "pastel24") == 0) {
			ret = COLOR_NS_PASTEL24;
		} else if (strcasecmp(name, "pastel25") == 0) {
			ret = COLOR_NS_PASTEL25;
		} else if (strcasecmp(name, "pastel26") == 0) {
			ret = COLOR_NS_PASTEL26;
		} else if (strcasecmp(name, "pastel27") == 0) {
			ret = COLOR_NS_PASTEL27;
		} else if (strcasecmp(name, "pastel28") == 0) {
			ret = COLOR_NS_PASTEL28;
		} else if (strcasecmp(name, "piyg10") == 0) {
			ret = COLOR_NS_PIYG10;
		} else if (strcasecmp(name, "piyg11") == 0) {
			ret = COLOR_NS_PIYG11;
		} else if (strcasecmp(name, "piyg3") == 0) {
			ret = COLOR_NS_PIYG3;
		} else if (strcasecmp(name, "piyg4") == 0) {
			ret = COLOR_NS_PIYG4;
		} else if (strcasecmp(name, "piyg5") == 0) {
			ret = COLOR_NS_PIYG5;
		} else if (strcasecmp(name, "piyg6") == 0) {
			ret = COLOR_NS_PIYG6;
		} else if (strcasecmp(name, "piyg7") == 0) {
			ret = COLOR_NS_PIYG7;
		} else if (strcasecmp(name, "piyg8") == 0) {
			ret = COLOR_NS_PIYG8;
		} else if (strcasecmp(name, "piyg9") == 0) {
			ret = COLOR_NS_PIYG9;
		} else if (strcasecmp(name, "prgn10") == 0) {
			ret = COLOR_NS_PRGN10;
		} else if (strcasecmp(name, "prgn11") == 0) {
			ret = COLOR_NS_PRGN11;
		} else if (strcasecmp(name, "prgn3") == 0) {
			ret = COLOR_NS_PRGN3;
		} else if (strcasecmp(name, "prgn4") == 0) {
			ret = COLOR_NS_PRGN4;
		} else if (strcasecmp(name, "prgn5") == 0) {
			ret = COLOR_NS_PRGN5;
		} else if (strcasecmp(name, "prgn6") == 0) {
			ret = COLOR_NS_PRGN6;
		} else if (strcasecmp(name, "prgn7") == 0) {
			ret = COLOR_NS_PRGN7;
		} else if (strcasecmp(name, "prgn8") == 0) {
			ret = COLOR_NS_PRGN8;
		} else if (strcasecmp(name, "prgn9") == 0) {
			ret = COLOR_NS_PRGN9;
		} else if (strcasecmp(name, "pubu3") == 0) {
			ret = COLOR_NS_PUBU3;
		} else if (strcasecmp(name, "pubu4") == 0) {
			ret = COLOR_NS_PUBU4;
		} else if (strcasecmp(name, "pubu5") == 0) {
			ret = COLOR_NS_PUBU5;
		} else if (strcasecmp(name, "pubu6") == 0) {
			ret = COLOR_NS_PUBU6;
		} else if (strcasecmp(name, "pubu7") == 0) {
			ret = COLOR_NS_PUBU7;
		} else if (strcasecmp(name, "pubu8") == 0) {
			ret = COLOR_NS_PUBU8;
		} else if (strcasecmp(name, "pubu9") == 0) {
			ret = COLOR_NS_PUBU9;
		} else if (strcasecmp(name, "pubugn3") == 0) {
			ret = COLOR_NS_PUBUGN3;
		} else if (strcasecmp(name, "pubugn4") == 0) {
			ret = COLOR_NS_PUBUGN4;
		} else if (strcasecmp(name, "pubugn5") == 0) {
			ret = COLOR_NS_PUBUGN5;
		} else if (strcasecmp(name, "pubugn6") == 0) {
			ret = COLOR_NS_PUBUGN6;
		} else if (strcasecmp(name, "pubugn7") == 0) {
			ret = COLOR_NS_PUBUGN7;
		} else if (strcasecmp(name, "pubugn8") == 0) {
			ret = COLOR_NS_PUBUGN8;
		} else if (strcasecmp(name, "pubugn9") == 0) {
			ret = COLOR_NS_PUBUGN9;
		} else if (strcasecmp(name, "puor10") == 0) {
			ret = COLOR_NS_PUOR10;
		} else if (strcasecmp(name, "puor11") == 0) {
			ret = COLOR_NS_PUOR11;
		} else if (strcasecmp(name, "puor3") == 0) {
			ret = COLOR_NS_PUOR3;
		} else if (strcasecmp(name, "puor4") == 0) {
			ret = COLOR_NS_PUOR4;
		} else if (strcasecmp(name, "puor5") == 0) {
			ret = COLOR_NS_PUOR5;
		} else if (strcasecmp(name, "puor6") == 0) {
			ret = COLOR_NS_PUOR6;
		} else if (strcasecmp(name, "puor7") == 0) {
			ret = COLOR_NS_PUOR7;
		} else if (strcasecmp(name, "puor8") == 0) {
			ret = COLOR_NS_PUOR8;
		} else if (strcasecmp(name, "puor9") == 0) {
			ret = COLOR_NS_PUOR9;
		} else if (strcasecmp(name, "purd3") == 0) {
			ret = COLOR_NS_PURD3;
		} else if (strcasecmp(name, "purd4") == 0) {
			ret = COLOR_NS_PURD4;
		} else if (strcasecmp(name, "purd5") == 0) {
			ret = COLOR_NS_PURD5;
		} else if (strcasecmp(name, "purd6") == 0) {
			ret = COLOR_NS_PURD6;
		} else if (strcasecmp(name, "purd7") == 0) {
			ret = COLOR_NS_PURD7;
		} else if (strcasecmp(name, "purd8") == 0) {
			ret = COLOR_NS_PURD8;
		} else if (strcasecmp(name, "purd9") == 0) {
			ret = COLOR_NS_PURD9;
		} else if (strcasecmp(name, "purples3") == 0) {
			ret = COLOR_NS_PURPLES3;
		} else if (strcasecmp(name, "purples4") == 0) {
			ret = COLOR_NS_PURPLES4;
		} else if (strcasecmp(name, "purples5") == 0) {
			ret = COLOR_NS_PURPLES5;
		} else if (strcasecmp(name, "purples6") == 0) {
			ret = COLOR_NS_PURPLES6;
		} else if (strcasecmp(name, "purples7") == 0) {
			ret = COLOR_NS_PURPLES7;
		} else if (strcasecmp(name, "purples8") == 0) {
			ret = COLOR_NS_PURPLES8;
		} else if (strcasecmp(name, "purples9") == 0) {
			ret = COLOR_NS_PURPLES9;
		} else {
			ret = -1;
		}
		break;
	case 'r':
		if (strcasecmp(name, "rdbu10") == 0) {
			ret = COLOR_NS_RDBU10;
		} else if (strcasecmp(name, "rdbu11") == 0) {
			ret = COLOR_NS_RDBU11;
		} else if (strcasecmp(name, "rdbu3") == 0) {
			ret = COLOR_NS_RDBU3;
		} else if (strcasecmp(name, "rdbu4") == 0) {
			ret = COLOR_NS_RDBU4;
		} else if (strcasecmp(name, "rdbu5") == 0) {
			ret = COLOR_NS_RDBU5;
		} else if (strcasecmp(name, "rdbu6") == 0) {
			ret = COLOR_NS_RDBU6;
		} else if (strcasecmp(name, "rdbu7") == 0) {
			ret = COLOR_NS_RDBU7;
		} else if (strcasecmp(name, "rdbu8") == 0) {
			ret = COLOR_NS_RDBU8;
		} else if (strcasecmp(name, "rdbu9") == 0) {
			ret = COLOR_NS_RDBU9;
		} else if (strcasecmp(name, "rdgy10") == 0) {
			ret = COLOR_NS_RDGY10;
		} else if (strcasecmp(name, "rdgy11") == 0) {
			ret = COLOR_NS_RDGY11;
		} else if (strcasecmp(name, "rdgy3") == 0) {
			ret = COLOR_NS_RDGY3;
		} else if (strcasecmp(name, "rdgy4") == 0) {
			ret = COLOR_NS_RDGY4;
		} else if (strcasecmp(name, "rdgy5") == 0) {
			ret = COLOR_NS_RDGY5;
		} else if (strcasecmp(name, "rdgy6") == 0) {
			ret = COLOR_NS_RDGY6;
		} else if (strcasecmp(name, "rdgy7") == 0) {
			ret = COLOR_NS_RDGY7;
		} else if (strcasecmp(name, "rdgy8") == 0) {
			ret = COLOR_NS_RDGY8;
		} else if (strcasecmp(name, "rdgy9") == 0) {
			ret = COLOR_NS_RDGY9;
		} else if (strcasecmp(name, "rdpu3") == 0) {
			ret = COLOR_NS_RDPU3;
		} else if (strcasecmp(name, "rdpu4") == 0) {
			ret = COLOR_NS_RDPU4;
		} else if (strcasecmp(name, "rdpu5") == 0) {
			ret = COLOR_NS_RDPU5;
		} else if (strcasecmp(name, "rdpu6") == 0) {
			ret = COLOR_NS_RDPU6;
		} else if (strcasecmp(name, "rdpu7") == 0) {
			ret = COLOR_NS_RDPU7;
		} else if (strcasecmp(name, "rdpu8") == 0) {
			ret = COLOR_NS_RDPU8;
		} else if (strcasecmp(name, "rdpu9") == 0) {
			ret = COLOR_NS_RDPU9;
		} else if (strcasecmp(name, "rdylbu10") == 0) {
			ret = COLOR_NS_RDYLBU10;
		} else if (strcasecmp(name, "rdylbu11") == 0) {
			ret = COLOR_NS_RDYLBU11;
		} else if (strcasecmp(name, "rdylbu3") == 0) {
			ret = COLOR_NS_RDYLBU3;
		} else if (strcasecmp(name, "rdylbu4") == 0) {
			ret = COLOR_NS_RDYLBU4;
		} else if (strcasecmp(name, "rdylbu5") == 0) {
			ret = COLOR_NS_RDYLBU5;
		} else if (strcasecmp(name, "rdylbu6") == 0) {
			ret = COLOR_NS_RDYLBU6;
		} else if (strcasecmp(name, "rdylbu7") == 0) {
			ret = COLOR_NS_RDYLBU7;
		} else if (strcasecmp(name, "rdylbu8") == 0) {
			ret = COLOR_NS_RDYLBU8;
		} else if (strcasecmp(name, "rdylbu9") == 0) {
			ret = COLOR_NS_RDYLBU9;
		} else if (strcasecmp(name, "rdylgn10") == 0) {
			ret = COLOR_NS_RDYLGN10;
		} else if (strcasecmp(name, "rdylgn11") == 0) {
			ret = COLOR_NS_RDYLGN11;
		} else if (strcasecmp(name, "rdylgn3") == 0) {
			ret = COLOR_NS_RDYLGN3;
		} else if (strcasecmp(name, "rdylgn4") == 0) {
			ret = COLOR_NS_RDYLGN4;
		} else if (strcasecmp(name, "rdylgn5") == 0) {
			ret = COLOR_NS_RDYLGN5;
		} else if (strcasecmp(name, "rdylgn6") == 0) {
			ret = COLOR_NS_RDYLGN6;
		} else if (strcasecmp(name, "rdylgn7") == 0) {
			ret = COLOR_NS_RDYLGN7;
		} else if (strcasecmp(name, "rdylgn8") == 0) {
			ret = COLOR_NS_RDYLGN8;
		} else if (strcasecmp(name, "rdylgn9") == 0) {
			ret = COLOR_NS_RDYLGN9;
		} else if (strcasecmp(name, "reds3") == 0) {
			ret = COLOR_NS_REDS3;
		} else if (strcasecmp(name, "reds4") == 0) {
			ret = COLOR_NS_REDS4;
		} else if (strcasecmp(name, "reds5") == 0) {
			ret = COLOR_NS_REDS5;
		} else if (strcasecmp(name, "reds6") == 0) {
			ret = COLOR_NS_REDS6;
		} else if (strcasecmp(name, "reds7") == 0) {
			ret = COLOR_NS_REDS7;
		} else if (strcasecmp(name, "reds8") == 0) {
			ret = COLOR_NS_REDS8;
		} else if (strcasecmp(name, "reds9") == 0) {
			ret = COLOR_NS_REDS9;
		} else {
			ret = -1;
		}
		break;
	case 's':
		if (strcasecmp(name, "set13") == 0) {
			ret = COLOR_NS_SET13;
		} else if (strcasecmp(name, "set14") == 0) {
			ret = COLOR_NS_SET14;
		} else if (strcasecmp(name, "set15") == 0) {
			ret = COLOR_NS_SET15;
		} else if (strcasecmp(name, "set16") == 0) {
			ret = COLOR_NS_SET16;
		} else if (strcasecmp(name, "set17") == 0) {
			ret = COLOR_NS_SET17;
		} else if (strcasecmp(name, "set18") == 0) {
			ret = COLOR_NS_SET18;
		} else if (strcasecmp(name, "set19") == 0) {
			ret = COLOR_NS_SET19;
		} else if (strcasecmp(name, "set23") == 0) {
			ret = COLOR_NS_SET23;
		} else if (strcasecmp(name, "set24") == 0) {
			ret = COLOR_NS_SET24;
		} else if (strcasecmp(name, "set25") == 0) {
			ret = COLOR_NS_SET25;
		} else if (strcasecmp(name, "set26") == 0) {
			ret = COLOR_NS_SET26;
		} else if (strcasecmp(name, "set27") == 0) {
			ret = COLOR_NS_SET27;
		} else if (strcasecmp(name, "set28") == 0) {
			ret = COLOR_NS_SET28;
		} else if (strcasecmp(name, "set310") == 0) {
			ret = COLOR_NS_SET310;
		} else if (strcasecmp(name, "set311") == 0) {
			ret = COLOR_NS_SET311;
		} else if (strcasecmp(name, "set312") == 0) {
			ret = COLOR_NS_SET312;
		} else if (strcasecmp(name, "set33") == 0) {
			ret = COLOR_NS_SET33;
		} else if (strcasecmp(name, "set34") == 0) {
			ret = COLOR_NS_SET34;
		} else if (strcasecmp(name, "set35") == 0) {
			ret = COLOR_NS_SET35;
		} else if (strcasecmp(name, "set36") == 0) {
			ret = COLOR_NS_SET36;
		} else if (strcasecmp(name, "set37") == 0) {
			ret = COLOR_NS_SET37;
		} else if (strcasecmp(name, "set38") == 0) {
			ret = COLOR_NS_SET38;
		} else if (strcasecmp(name, "set39") == 0) {
			ret = COLOR_NS_SET39;
		} else if (strcasecmp(name, "spectral10") == 0) {
			ret = COLOR_NS_SPECTRAL10;
		} else if (strcasecmp(name, "spectral11") == 0) {
			ret = COLOR_NS_SPECTRAL11;
		} else if (strcasecmp(name, "spectral3") == 0) {
			ret = COLOR_NS_SPECTRAL3;
		} else if (strcasecmp(name, "spectral4") == 0) {
			ret = COLOR_NS_SPECTRAL4;
		} else if (strcasecmp(name, "spectral5") == 0) {
			ret = COLOR_NS_SPECTRAL5;
		} else if (strcasecmp(name, "spectral6") == 0) {
			ret = COLOR_NS_SPECTRAL6;
		} else if (strcasecmp(name, "spectral7") == 0) {
			ret = COLOR_NS_SPECTRAL7;
		} else if (strcasecmp(name, "spectral8") == 0) {
			ret = COLOR_NS_SPECTRAL8;
		} else if (strcasecmp(name, "spectral9") == 0) {
			ret = COLOR_NS_SPECTRAL9;
		} else {
			ret = -1;
		}
		break;
	case 'y':
		if (strcasecmp(name, "ylgn3") == 0) {
			ret = COLOR_NS_YLGN3;
		} else if (strcasecmp(name, "ylgn4") == 0) {
			ret = COLOR_NS_YLGN4;
		} else if (strcasecmp(name, "ylgn5") == 0) {
			ret = COLOR_NS_YLGN5;
		} else if (strcasecmp(name, "ylgn6") == 0) {
			ret = COLOR_NS_YLGN6;
		} else if (strcasecmp(name, "ylgn7") == 0) {
			ret = COLOR_NS_YLGN7;
		} else if (strcasecmp(name, "ylgn8") == 0) {
			ret = COLOR_NS_YLGN8;
		} else if (strcasecmp(name, "ylgn9") == 0) {
			ret = COLOR_NS_YLGN9;
		} else if (strcasecmp(name, "ylgnbu3") == 0) {
			ret = COLOR_NS_YLGNBU3;
		} else if (strcasecmp(name, "ylgnbu4") == 0) {
			ret = COLOR_NS_YLGNBU4;
		} else if (strcasecmp(name, "ylgnbu5") == 0) {
			ret = COLOR_NS_YLGNBU5;
		} else if (strcasecmp(name, "ylgnbu6") == 0) {
			ret = COLOR_NS_YLGNBU6;
		} else if (strcasecmp(name, "ylgnbu7") == 0) {
			ret = COLOR_NS_YLGNBU7;
		} else if (strcasecmp(name, "ylgnbu8") == 0) {
			ret = COLOR_NS_YLGNBU8;
		} else if (strcasecmp(name, "ylgnbu9") == 0) {
			ret = COLOR_NS_YLGNBU9;
		} else if (strcasecmp(name, "ylorbr3") == 0) {
			ret = COLOR_NS_YLORBR3;
		} else if (strcasecmp(name, "ylorbr4") == 0) {
			ret = COLOR_NS_YLORBR4;
		} else if (strcasecmp(name, "ylorbr5") == 0) {
			ret = COLOR_NS_YLORBR5;
		} else if (strcasecmp(name, "ylorbr6") == 0) {
			ret = COLOR_NS_YLORBR6;
		} else if (strcasecmp(name, "ylorbr7") == 0) {
			ret = COLOR_NS_YLORBR7;
		} else if (strcasecmp(name, "ylorbr8") == 0) {
			ret = COLOR_NS_YLORBR8;
		} else if (strcasecmp(name, "ylorbr9") == 0) {
			ret = COLOR_NS_YLORBR9;
		} else if (strcasecmp(name, "ylorrd3") == 0) {
			ret = COLOR_NS_YLORRD3;
		} else if (strcasecmp(name, "ylorrd4") == 0) {
			ret = COLOR_NS_YLORRD4;
		} else if (strcasecmp(name, "ylorrd5") == 0) {
			ret = COLOR_NS_YLORRD5;
		} else if (strcasecmp(name, "ylorrd6") == 0) {
			ret = COLOR_NS_YLORRD6;
		} else if (strcasecmp(name, "ylorrd7") == 0) {
			ret = COLOR_NS_YLORRD7;
		} else if (strcasecmp(name, "ylorrd8") == 0) {
			ret = COLOR_NS_YLORRD8;
		} else if (strcasecmp(name, "ylorrd9") == 0) {
			ret = COLOR_NS_YLORRD9;
		} else {
			ret = -1;
		}
		break;
	default:
		ret = -1;
		break;
	}

	return (ret);
}

/* colorscheme color */
int dp_colornscode(int number, int scheme)
{
	int ret = (-1);
	switch (scheme) {
	case COLOR_NS_ACCENT3:	/* accent3 color scheme */
		switch (number) {
		case 1:
			ret = 0x007fc87f;	/* #7fc97f 1 */
			break;
		case 2:
			ret = 0x00beaed5;	/* #beaed4 2 */
			break;
		case 3:
			ret = 0x00fdc085;	/* #fdc086 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ACCENT4:	/* accent4 color scheme */
		switch (number) {
		case 1:
			ret = 0x007fc87f;	/* #7fc97f 1 */
			break;
		case 2:
			ret = 0x00beaed5;	/* #beaed4 2 */
			break;
		case 3:
			ret = 0x00fdc085;	/* #fdc086 3 */
			break;
		case 4:
			ret = 0x00ffff98;	/* #ffff99 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ACCENT5:	/* accent5 color scheme */
		switch (number) {
		case 1:
			ret = 0x007fc97f;	/* #7fc97f 1 */
			break;
		case 2:
			ret = 0x00beaed4;	/* #beaed4 2 */
			break;
		case 3:
			ret = 0x00fdc086;	/* #fdc086 3 */
			break;
		case 4:
			ret = 0x00ffff99;	/* #ffff99 4 */
			break;
		case 5:
			ret = 0x00386cb0;	/* #386cb0 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ACCENT6:	/* accent6 color scheme */
		switch (number) {
		case 1:
			ret = 0x007fc97f;	/* #7fc97f 1 */
			break;
		case 2:
			ret = 0x00beaed4;	/* #beaed4 2 */
			break;
		case 3:
			ret = 0x00fdc086;	/* #fdc086 3 */
			break;
		case 4:
			ret = 0x00ffff99;	/* #ffff99 4 */
			break;
		case 5:
			ret = 0x00386cb0;	/* #386cb0 5 */
			break;
		case 6:
			ret = 0x00f0027f;	/* #f0027f 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ACCENT7:	/* accent7 color scheme */
		switch (number) {
		case 1:
			ret = 0x007fc97f;	/* #7fc97f 1 */
			break;
		case 2:
			ret = 0x00beaed4;	/* #beaed4 2 */
			break;
		case 3:
			ret = 0x00fdc086;	/* #fdc086 3 */
			break;
		case 4:
			ret = 0x00ffff99;	/* #ffff99 4 */
			break;
		case 5:
			ret = 0x00386cb0;	/* #386cb0 5 */
			break;
		case 6:
			ret = 0x00f0027f;	/* #f0027f 6 */
			break;
		case 7:
			ret = 0x00bf5b17;	/* #bf5b17 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ACCENT8:	/* accent8 color scheme */
		switch (number) {
		case 1:
			ret = 0x007fc97f;	/* #7fc97f 1 */
			break;
		case 2:
			ret = 0x00beaed4;	/* #beaed4 2 */
			break;
		case 3:
			ret = 0x00fdc086;	/* #fdc086 3 */
			break;
		case 4:
			ret = 0x00ffff99;	/* #ffff99 4 */
			break;
		case 5:
			ret = 0x00386cb0;	/* #386cb0 5 */
			break;
		case 6:
			ret = 0x00f0027f;	/* #f0027f 6 */
			break;
		case 7:
			ret = 0x00bf5b17;	/* #bf5b17 7 */
			break;
		case 8:
			ret = 0x00666666;	/* #666666 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BLUES3:	/* blues3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00deebf7;	/* #deebf7 1 */
			break;
		case 2:
			ret = 0x009ecae1;	/* #9ecae1 2 */
			break;
		case 3:
			ret = 0x003182bd;	/* #3182bd 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BLUES4:	/* blues4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00eff3ff;	/* #eff3ff 1 */
			break;
		case 2:
			ret = 0x00bdd7e7;	/* #bdd7e7 2 */
			break;
		case 3:
			ret = 0x006baed6;	/* #6baed6 3 */
			break;
		case 4:
			ret = 0x002171b5;	/* #2171b5 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BLUES5:	/* blues5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00eff3ff;	/* #eff3ff 1 */
			break;
		case 2:
			ret = 0x00bdd7e7;	/* #bdd7e7 2 */
			break;
		case 3:
			ret = 0x006baed6;	/* #6baed6 3 */
			break;
		case 4:
			ret = 0x003182bd;	/* #3182bd 4 */
			break;
		case 5:
			ret = 0x0008519c;	/* #08519c 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BLUES6:	/* blues6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00eff3ff;	/* #eff3ff 1 */
			break;
		case 2:
			ret = 0x00c6dbef;	/* #c6dbef 2 */
			break;
		case 3:
			ret = 0x009ecae1;	/* #9ecae1 3 */
			break;
		case 4:
			ret = 0x006baed6;	/* #6baed6 4 */
			break;
		case 5:
			ret = 0x003182bd;	/* #3182bd 5 */
			break;
		case 6:
			ret = 0x0008519c;	/* #08519c 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BLUES7:	/* blues7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00eff3ff;	/* #eff3ff 1 */
			break;
		case 2:
			ret = 0x00c6dbef;	/* #c6dbef 2 */
			break;
		case 3:
			ret = 0x009ecae1;	/* #9ecae1 3 */
			break;
		case 4:
			ret = 0x006baed6;	/* #6baed6 4 */
			break;
		case 5:
			ret = 0x004292c6;	/* #4292c6 5 */
			break;
		case 6:
			ret = 0x002171b5;	/* #2171b5 6 */
			break;
		case 7:
			ret = 0x00084594;	/* #084594 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BLUES8:	/* blues8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7fbff;	/* #f7fbff 1 */
			break;
		case 2:
			ret = 0x00deebf7;	/* #deebf7 2 */
			break;
		case 3:
			ret = 0x00c6dbef;	/* #c6dbef 3 */
			break;
		case 4:
			ret = 0x009ecae1;	/* #9ecae1 4 */
			break;
		case 5:
			ret = 0x006baed6;	/* #6baed6 5 */
			break;
		case 6:
			ret = 0x004292c6;	/* #4292c6 6 */
			break;
		case 7:
			ret = 0x002171b5;	/* #2171b5 7 */
			break;
		case 8:
			ret = 0x00084594;	/* #084594 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BLUES9:	/* blues9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7fbff;	/* #f7fbff 1 */
			break;
		case 2:
			ret = 0x00deebf7;	/* #deebf7 2 */
			break;
		case 3:
			ret = 0x00c6dbef;	/* #c6dbef 3 */
			break;
		case 4:
			ret = 0x009ecae1;	/* #9ecae1 4 */
			break;
		case 5:
			ret = 0x006baed6;	/* #6baed6 5 */
			break;
		case 6:
			ret = 0x004292c6;	/* #4292c6 6 */
			break;
		case 7:
			ret = 0x002171b5;	/* #2171b5 7 */
			break;
		case 8:
			ret = 0x0008519c;	/* #08519c 8 */
			break;
		case 9:
			ret = 0x0008306b;	/* #08306b 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BRBG10:	/* brbg10 color scheme */
		switch (number) {
		case 1:
			ret = 0x00543005;	/* #543005 1 */
			break;
		case 2:
			ret = 0x008c510a;	/* #8c510a 2 */
			break;
		case 3:
			ret = 0x00bf812d;	/* #bf812d 3 */
			break;
		case 4:
			ret = 0x00dfc27d;	/* #dfc27d 4 */
			break;
		case 5:
			ret = 0x00f6e8c3;	/* #f6e8c3 5 */
			break;
		case 6:
			ret = 0x00c7eae5;	/* #c7eae5 6 */
			break;
		case 7:
			ret = 0x0080cdc1;	/* #80cdc1 7 */
			break;
		case 8:
			ret = 0x0035978f;	/* #35978f 8 */
			break;
		case 9:
			ret = 0x0001665e;	/* #01665e 9 */
			break;
		case 10:
			ret = 0x00003c30;	/* #003c30 10 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BRBG11:	/* brbg11 color scheme */
		switch (number) {
		case 1:
			ret = 0x00543005;	/* #543005 1 */
			break;
		case 2:
			ret = 0x008c510a;	/* #8c510a 2 */
			break;
		case 3:
			ret = 0x00bf812d;	/* #bf812d 3 */
			break;
		case 4:
			ret = 0x00dfc27d;	/* #dfc27d 4 */
			break;
		case 5:
			ret = 0x00f6e8c3;	/* #f6e8c3 5 */
			break;
		case 6:
			ret = 0x00f5f5f5;	/* #f5f5f5 6 */
			break;
		case 7:
			ret = 0x00c7eae5;	/* #c7eae5 7 */
			break;
		case 8:
			ret = 0x0080cdc1;	/* #80cdc1 8 */
			break;
		case 9:
			ret = 0x0035978f;	/* #35978f 9 */
			break;
		case 10:
			ret = 0x0001665e;	/* #01665e 10 */
			break;
		case 11:
			ret = 0x00003c30;	/* #003c30 11 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BRBG3:	/* brbg3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d8b365;	/* #d8b365 1 */
			break;
		case 2:
			ret = 0x00f5f5f5;	/* #f5f5f5 2 */
			break;
		case 3:
			ret = 0x005ab4ac;	/* #5ab4ac 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BRBG4:	/* brbg4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a6611a;	/* #a6611a 1 */
			break;
		case 2:
			ret = 0x00dfc27d;	/* #dfc27d 2 */
			break;
		case 3:
			ret = 0x0080cdc1;	/* #80cdc1 3 */
			break;
		case 4:
			ret = 0x00018571;	/* #018571 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BRBG5:	/* brbg5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a6611a;	/* #a6611a 1 */
			break;
		case 2:
			ret = 0x00dfc27d;	/* #dfc27d 2 */
			break;
		case 3:
			ret = 0x00f5f5f5;	/* #f5f5f5 3 */
			break;
		case 4:
			ret = 0x0080cdc1;	/* #80cdc1 4 */
			break;
		case 5:
			ret = 0x00018571;	/* #018571 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BRBG6:	/* brbg6 color scheme */
		switch (number) {
		case 1:
			ret = 0x008c510a;	/* #8c510a 1 */
			break;
		case 2:
			ret = 0x00d8b365;	/* #d8b365 2 */
			break;
		case 3:
			ret = 0x00f6e8c3;	/* #f6e8c3 3 */
			break;
		case 4:
			ret = 0x00c7eae5;	/* #c7eae5 4 */
			break;
		case 5:
			ret = 0x005ab4ac;	/* #5ab4ac 5 */
			break;
		case 6:
			ret = 0x0001665e;	/* #01665e 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BRBG7:	/* brbg7 color scheme */
		switch (number) {
		case 1:
			ret = 0x008c510a;	/* #8c510a 1 */
			break;
		case 2:
			ret = 0x00d8b365;	/* #d8b365 2 */
			break;
		case 3:
			ret = 0x00f6e8c3;	/* #f6e8c3 3 */
			break;
		case 4:
			ret = 0x00f5f5f5;	/* #f5f5f5 4 */
			break;
		case 5:
			ret = 0x00c7eae5;	/* #c7eae5 5 */
			break;
		case 6:
			ret = 0x005ab4ac;	/* #5ab4ac 6 */
			break;
		case 7:
			ret = 0x0001665e;	/* #01665e 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BRBG8:	/* brbg8 color scheme */
		switch (number) {
		case 1:
			ret = 0x008c510a;	/* #8c510a 1 */
			break;
		case 2:
			ret = 0x00bf812d;	/* #bf812d 2 */
			break;
		case 3:
			ret = 0x00dfc27d;	/* #dfc27d 3 */
			break;
		case 4:
			ret = 0x00f6e8c3;	/* #f6e8c3 4 */
			break;
		case 5:
			ret = 0x00c7eae5;	/* #c7eae5 5 */
			break;
		case 6:
			ret = 0x0080cdc1;	/* #80cdc1 6 */
			break;
		case 7:
			ret = 0x0035978f;	/* #35978f 7 */
			break;
		case 8:
			ret = 0x0001665e;	/* #01665e 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BRBG9:	/* brbg9 color scheme */
		switch (number) {
		case 1:
			ret = 0x008c510a;	/* #8c510a 1 */
			break;
		case 2:
			ret = 0x00bf812d;	/* #bf812d 2 */
			break;
		case 3:
			ret = 0x00dfc27d;	/* #dfc27d 3 */
			break;
		case 4:
			ret = 0x00f6e8c3;	/* #f6e8c3 4 */
			break;
		case 5:
			ret = 0x00f5f5f5;	/* #f5f5f5 5 */
			break;
		case 6:
			ret = 0x00c7eae5;	/* #c7eae5 6 */
			break;
		case 7:
			ret = 0x0080cdc1;	/* #80cdc1 7 */
			break;
		case 8:
			ret = 0x0035978f;	/* #35978f 8 */
			break;
		case 9:
			ret = 0x0001665e;	/* #01665e 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUGN3:	/* bugn3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e5f5f9;	/* #e5f5f9 1 */
			break;
		case 2:
			ret = 0x0099d8c9;	/* #99d8c9 2 */
			break;
		case 3:
			ret = 0x002ca25f;	/* #2ca25f 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUGN4:	/* bugn4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00edf8fb;	/* #edf8fb 1 */
			break;
		case 2:
			ret = 0x00b2e2e2;	/* #b2e2e2 2 */
			break;
		case 3:
			ret = 0x0066c2a4;	/* #66c2a4 3 */
			break;
		case 4:
			ret = 0x00238b45;	/* #238b45 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUGN5:	/* bugn5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00edf8fb;	/* #edf8fb 1 */
			break;
		case 2:
			ret = 0x00b2e2e2;	/* #b2e2e2 2 */
			break;
		case 3:
			ret = 0x0066c2a4;	/* #66c2a4 3 */
			break;
		case 4:
			ret = 0x002ca25f;	/* #2ca25f 4 */
			break;
		case 5:
			ret = 0x00006d2c;	/* #006d2c 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUGN6:	/* bugn6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00edf8fb;	/* #edf8fb 1 */
			break;
		case 2:
			ret = 0x00ccece6;	/* #ccece6 2 */
			break;
		case 3:
			ret = 0x0099d8c9;	/* #99d8c9 3 */
			break;
		case 4:
			ret = 0x0066c2a4;	/* #66c2a4 4 */
			break;
		case 5:
			ret = 0x002ca25f;	/* #2ca25f 5 */
			break;
		case 6:
			ret = 0x00006d2c;	/* #006d2c 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUGN7:	/* bugn7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00edf8fb;	/* #edf8fb 1 */
			break;
		case 2:
			ret = 0x00ccece6;	/* #ccece6 2 */
			break;
		case 3:
			ret = 0x0099d8c9;	/* #99d8c9 3 */
			break;
		case 4:
			ret = 0x0066c2a4;	/* #66c2a4 4 */
			break;
		case 5:
			ret = 0x0041ae76;	/* #41ae76 5 */
			break;
		case 6:
			ret = 0x00238b45;	/* #238b45 6 */
			break;
		case 7:
			ret = 0x00005824;	/* #005824 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUGN8:	/* bugn8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7fcfd;	/* #f7fcfd 1 */
			break;
		case 2:
			ret = 0x00e5f5f9;	/* #e5f5f9 2 */
			break;
		case 3:
			ret = 0x00ccece6;	/* #ccece6 3 */
			break;
		case 4:
			ret = 0x0099d8c9;	/* #99d8c9 4 */
			break;
		case 5:
			ret = 0x0066c2a4;	/* #66c2a4 5 */
			break;
		case 6:
			ret = 0x0041ae76;	/* #41ae76 6 */
			break;
		case 7:
			ret = 0x00238b45;	/* #238b45 7 */
			break;
		case 8:
			ret = 0x00005824;	/* #005824 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUGN9:	/* bugn9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7fcfd;	/* #f7fcfd 1 */
			break;
		case 2:
			ret = 0x00e5f5f9;	/* #e5f5f9 2 */
			break;
		case 3:
			ret = 0x00ccece6;	/* #ccece6 3 */
			break;
		case 4:
			ret = 0x0099d8c9;	/* #99d8c9 4 */
			break;
		case 5:
			ret = 0x0066c2a4;	/* #66c2a4 5 */
			break;
		case 6:
			ret = 0x0041ae76;	/* #41ae76 6 */
			break;
		case 7:
			ret = 0x00238b45;	/* #238b45 7 */
			break;
		case 8:
			ret = 0x00006d2c;	/* #006d2c 8 */
			break;
		case 9:
			ret = 0x0000441b;	/* #00441b 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUPU3:	/* bupu3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e0ecf4;	/* #e0ecf4 1 */
			break;
		case 2:
			ret = 0x009ebcda;	/* #9ebcda 2 */
			break;
		case 3:
			ret = 0x008856a7;	/* #8856a7 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUPU4:	/* bupu4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00edf8fb;	/* #edf8fb 1 */
			break;
		case 2:
			ret = 0x00b3cde3;	/* #b3cde3 2 */
			break;
		case 3:
			ret = 0x008c96c6;	/* #8c96c6 3 */
			break;
		case 4:
			ret = 0x0088419d;	/* #88419d 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUPU5:	/* bupu5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00edf8fb;	/* #edf8fb 1 */
			break;
		case 2:
			ret = 0x00b3cde3;	/* #b3cde3 2 */
			break;
		case 3:
			ret = 0x008c96c6;	/* #8c96c6 3 */
			break;
		case 4:
			ret = 0x008856a7;	/* #8856a7 4 */
			break;
		case 5:
			ret = 0x00810f7c;	/* #810f7c 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUPU6:	/* bupu6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00edf8fb;	/* #edf8fb 1 */
			break;
		case 2:
			ret = 0x00bfd3e6;	/* #bfd3e6 2 */
			break;
		case 3:
			ret = 0x009ebcda;	/* #9ebcda 3 */
			break;
		case 4:
			ret = 0x008c96c6;	/* #8c96c6 4 */
			break;
		case 5:
			ret = 0x008856a7;	/* #8856a7 5 */
			break;
		case 6:
			ret = 0x00810f7c;	/* #810f7c 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUPU7:	/* bupu7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00edf8fb;	/* #edf8fb 1 */
			break;
		case 2:
			ret = 0x00bfd3e6;	/* #bfd3e6 2 */
			break;
		case 3:
			ret = 0x009ebcda;	/* #9ebcda 3 */
			break;
		case 4:
			ret = 0x008c96c6;	/* #8c96c6 4 */
			break;
		case 5:
			ret = 0x008c6bb1;	/* #8c6bb1 5 */
			break;
		case 6:
			ret = 0x0088419d;	/* #88419d 6 */
			break;
		case 7:
			ret = 0x006e016b;	/* #6e016b 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUPU8:	/* bupu8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7fcfd;	/* #f7fcfd 1 */
			break;
		case 2:
			ret = 0x00e0ecf4;	/* #e0ecf4 2 */
			break;
		case 3:
			ret = 0x00bfd3e6;	/* #bfd3e6 3 */
			break;
		case 4:
			ret = 0x009ebcda;	/* #9ebcda 4 */
			break;
		case 5:
			ret = 0x008c96c6;	/* #8c96c6 5 */
			break;
		case 6:
			ret = 0x008c6bb1;	/* #8c6bb1 6 */
			break;
		case 7:
			ret = 0x0088419d;	/* #88419d 7 */
			break;
		case 8:
			ret = 0x006e016b;	/* #6e016b 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_BUPU9:	/* bupu9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7fcfd;	/* #f7fcfd 1 */
			break;
		case 2:
			ret = 0x00e0ecf4;	/* #e0ecf4 2 */
			break;
		case 3:
			ret = 0x00bfd3e6;	/* #bfd3e6 3 */
			break;
		case 4:
			ret = 0x009ebcda;	/* #9ebcda 4 */
			break;
		case 5:
			ret = 0x008c96c6;	/* #8c96c6 5 */
			break;
		case 6:
			ret = 0x008c6bb1;	/* #8c6bb1 6 */
			break;
		case 7:
			ret = 0x0088419d;	/* #88419d 7 */
			break;
		case 8:
			ret = 0x00810f7c;	/* #810f7c 8 */
			break;
		case 9:
			ret = 0x004d004b;	/* #4d004b 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_DARK23:	/* dark23 color scheme */
		switch (number) {
		case 1:
			ret = 0x001b9e77;	/* #1b9e77 1 */
			break;
		case 2:
			ret = 0x00d95f02;	/* #d95f02 2 */
			break;
		case 3:
			ret = 0x007570b3;	/* #7570b3 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_DARK24:	/* dark24 color scheme */
		switch (number) {
		case 1:
			ret = 0x001b9e77;	/* #1b9e77 1 */
			break;
		case 2:
			ret = 0x00d95f02;	/* #d95f02 2 */
			break;
		case 3:
			ret = 0x007570b3;	/* #7570b3 3 */
			break;
		case 4:
			ret = 0x00e7298a;	/* #e7298a 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_DARK25:	/* dark25 color scheme */
		switch (number) {
		case 1:
			ret = 0x001b9e77;	/* #1b9e77 1 */
			break;
		case 2:
			ret = 0x00d95f02;	/* #d95f02 2 */
			break;
		case 3:
			ret = 0x007570b3;	/* #7570b3 3 */
			break;
		case 4:
			ret = 0x00e7298a;	/* #e7298a 4 */
			break;
		case 5:
			ret = 0x0066a61e;	/* #66a61e 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_DARK26:	/* dark26 color scheme */
		switch (number) {
		case 1:
			ret = 0x001b9e77;	/* #1b9e77 1 */
			break;
		case 2:
			ret = 0x00d95f02;	/* #d95f02 2 */
			break;
		case 3:
			ret = 0x007570b3;	/* #7570b3 3 */
			break;
		case 4:
			ret = 0x00e7298a;	/* #e7298a 4 */
			break;
		case 5:
			ret = 0x0066a61e;	/* #66a61e 5 */
			break;
		case 6:
			ret = 0x00e6ab02;	/* #e6ab02 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_DARK27:	/* dark27 color scheme */
		switch (number) {
		case 1:
			ret = 0x001b9e77;	/* #1b9e77 1 */
			break;
		case 2:
			ret = 0x00d95f02;	/* #d95f02 2 */
			break;
		case 3:
			ret = 0x007570b3;	/* #7570b3 3 */
			break;
		case 4:
			ret = 0x00e7298a;	/* #e7298a 4 */
			break;
		case 5:
			ret = 0x0066a61e;	/* #66a61e 5 */
			break;
		case 6:
			ret = 0x00e6ab02;	/* #e6ab02 6 */
			break;
		case 7:
			ret = 0x00a6761d;	/* #a6761d 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_DARK28:	/* dark28 color scheme */
		switch (number) {
		case 1:
			ret = 0x001b9e77;	/* #1b9e77 1 */
			break;
		case 2:
			ret = 0x00d95f02;	/* #d95f02 2 */
			break;
		case 3:
			ret = 0x007570b3;	/* #7570b3 3 */
			break;
		case 4:
			ret = 0x00e7298a;	/* #e7298a 4 */
			break;
		case 5:
			ret = 0x0066a61e;	/* #66a61e 5 */
			break;
		case 6:
			ret = 0x00e6ab02;	/* #e6ab02 6 */
			break;
		case 7:
			ret = 0x00a6761d;	/* #a6761d 7 */
			break;
		case 8:
			ret = 0x00666666;	/* #666666 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GNBU3:	/* gnbu3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e0f3db;	/* #e0f3db 1 */
			break;
		case 2:
			ret = 0x00a8ddb5;	/* #a8ddb5 2 */
			break;
		case 3:
			ret = 0x0043a2ca;	/* #43a2ca 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GNBU4:	/* gnbu4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f0f9e8;	/* #f0f9e8 1 */
			break;
		case 2:
			ret = 0x00bae4bc;	/* #bae4bc 2 */
			break;
		case 3:
			ret = 0x007bccc4;	/* #7bccc4 3 */
			break;
		case 4:
			ret = 0x002b8cbe;	/* #2b8cbe 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GNBU5:	/* gnbu5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f0f9e8;	/* #f0f9e8 1 */
			break;
		case 2:
			ret = 0x00bae4bc;	/* #bae4bc 2 */
			break;
		case 3:
			ret = 0x007bccc4;	/* #7bccc4 3 */
			break;
		case 4:
			ret = 0x0043a2ca;	/* #43a2ca 4 */
			break;
		case 5:
			ret = 0x000868ac;	/* #0868ac 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GNBU6:	/* gnbu6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f0f9e8;	/* #f0f9e8 1 */
			break;
		case 2:
			ret = 0x00ccebc5;	/* #ccebc5 2 */
			break;
		case 3:
			ret = 0x00a8ddb5;	/* #a8ddb5 3 */
			break;
		case 4:
			ret = 0x007bccc4;	/* #7bccc4 4 */
			break;
		case 5:
			ret = 0x0043a2ca;	/* #43a2ca 5 */
			break;
		case 6:
			ret = 0x000868ac;	/* #0868ac 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GNBU7:	/* gnbu7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f0f9e8;	/* #f0f9e8 1 */
			break;
		case 2:
			ret = 0x00ccebc5;	/* #ccebc5 2 */
			break;
		case 3:
			ret = 0x00a8ddb5;	/* #a8ddb5 3 */
			break;
		case 4:
			ret = 0x007bccc4;	/* #7bccc4 4 */
			break;
		case 5:
			ret = 0x004eb3d3;	/* #4eb3d3 5 */
			break;
		case 6:
			ret = 0x002b8cbe;	/* #2b8cbe 6 */
			break;
		case 7:
			ret = 0x0008589e;	/* #08589e 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GNBU8:	/* gnbu8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7fcf0;	/* #f7fcf0 1 */
			break;
		case 2:
			ret = 0x00e0f3db;	/* #e0f3db 2 */
			break;
		case 3:
			ret = 0x00ccebc5;	/* #ccebc5 3 */
			break;
		case 4:
			ret = 0x00a8ddb5;	/* #a8ddb5 4 */
			break;
		case 5:
			ret = 0x007bccc4;	/* #7bccc4 5 */
			break;
		case 6:
			ret = 0x004eb3d3;	/* #4eb3d3 6 */
			break;
		case 7:
			ret = 0x002b8cbe;	/* #2b8cbe 7 */
			break;
		case 8:
			ret = 0x0008589e;	/* #08589e 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GNBU9:	/* gnbu9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7fcf0;	/* #f7fcf0 1 */
			break;
		case 2:
			ret = 0x00e0f3db;	/* #e0f3db 2 */
			break;
		case 3:
			ret = 0x00ccebc5;	/* #ccebc5 3 */
			break;
		case 4:
			ret = 0x00a8ddb5;	/* #a8ddb5 4 */
			break;
		case 5:
			ret = 0x007bccc4;	/* #7bccc4 5 */
			break;
		case 6:
			ret = 0x004eb3d3;	/* #4eb3d3 6 */
			break;
		case 7:
			ret = 0x002b8cbe;	/* #2b8cbe 7 */
			break;
		case 8:
			ret = 0x000868ac;	/* #0868ac 8 */
			break;
		case 9:
			ret = 0x00084081;	/* #084081 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREENS3:	/* greens3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e5f5e0;	/* #e5f5e0 1 */
			break;
		case 2:
			ret = 0x00a1d99b;	/* #a1d99b 2 */
			break;
		case 3:
			ret = 0x0031a354;	/* #31a354 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREENS4:	/* greens4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00edf8e9;	/* #edf8e9 1 */
			break;
		case 2:
			ret = 0x00bae4b3;	/* #bae4b3 2 */
			break;
		case 3:
			ret = 0x0074c476;	/* #74c476 3 */
			break;
		case 4:
			ret = 0x00238b45;	/* #238b45 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREENS5:	/* greens5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00edf8e9;	/* #edf8e9 1 */
			break;
		case 2:
			ret = 0x00bae4b3;	/* #bae4b3 2 */
			break;
		case 3:
			ret = 0x0074c476;	/* #74c476 3 */
			break;
		case 4:
			ret = 0x0031a354;	/* #31a354 4 */
			break;
		case 5:
			ret = 0x00006d2c;	/* #006d2c 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREENS6:	/* greens6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00edf8e9;	/* #edf8e9 1 */
			break;
		case 2:
			ret = 0x00c7e9c0;	/* #c7e9c0 2 */
			break;
		case 3:
			ret = 0x00a1d99b;	/* #a1d99b 3 */
			break;
		case 4:
			ret = 0x0074c476;	/* #74c476 4 */
			break;
		case 5:
			ret = 0x0031a354;	/* #31a354 5 */
			break;
		case 6:
			ret = 0x00006d2c;	/* #006d2c 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREENS7:	/* greens7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00edf8e9;	/* #edf8e9 1 */
			break;
		case 2:
			ret = 0x00c7e9c0;	/* #c7e9c0 2 */
			break;
		case 3:
			ret = 0x00a1d99b;	/* #a1d99b 3 */
			break;
		case 4:
			ret = 0x0074c476;	/* #74c476 4 */
			break;
		case 5:
			ret = 0x0041ab5d;	/* #41ab5d 5 */
			break;
		case 6:
			ret = 0x00238b45;	/* #238b45 6 */
			break;
		case 7:
			ret = 0x00005a32;	/* #005a32 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREENS8:	/* greens8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7fcf5;	/* #f7fcf5 1 */
			break;
		case 2:
			ret = 0x00e5f5e0;	/* #e5f5e0 2 */
			break;
		case 3:
			ret = 0x00c7e9c0;	/* #c7e9c0 3 */
			break;
		case 4:
			ret = 0x00a1d99b;	/* #a1d99b 4 */
			break;
		case 5:
			ret = 0x0074c476;	/* #74c476 5 */
			break;
		case 6:
			ret = 0x0041ab5d;	/* #41ab5d 6 */
			break;
		case 7:
			ret = 0x00238b45;	/* #238b45 7 */
			break;
		case 8:
			ret = 0x00005a32;	/* #005a32 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREENS9:	/* greens9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7fcf5;	/* #f7fcf5 1 */
			break;
		case 2:
			ret = 0x00e5f5e0;	/* #e5f5e0 2 */
			break;
		case 3:
			ret = 0x00c7e9c0;	/* #c7e9c0 3 */
			break;
		case 4:
			ret = 0x00a1d99b;	/* #a1d99b 4 */
			break;
		case 5:
			ret = 0x0074c476;	/* #74c476 5 */
			break;
		case 6:
			ret = 0x0041ab5d;	/* #41ab5d 6 */
			break;
		case 7:
			ret = 0x00238b45;	/* #238b45 7 */
			break;
		case 8:
			ret = 0x00006d2c;	/* #006d2c 8 */
			break;
		case 9:
			ret = 0x0000441b;	/* #00441b 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREYS3:	/* greys3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f0f0f0;	/* #f0f0f0 1 */
			break;
		case 2:
			ret = 0x00bdbdbd;	/* #bdbdbd 2 */
			break;
		case 3:
			ret = 0x00636363;	/* #636363 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREYS4:	/* greys4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7f7f7;	/* #f7f7f7 1 */
			break;
		case 2:
			ret = 0x00cccccc;	/* #cccccc 2 */
			break;
		case 3:
			ret = 0x00969696;	/* #969696 3 */
			break;
		case 4:
			ret = 0x00525252;	/* #525252 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREYS5:	/* greys5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7f7f7;	/* #f7f7f7 1 */
			break;
		case 2:
			ret = 0x00cccccc;	/* #cccccc 2 */
			break;
		case 3:
			ret = 0x00969696;	/* #969696 3 */
			break;
		case 4:
			ret = 0x00636363;	/* #636363 4 */
			break;
		case 5:
			ret = 0x00252525;	/* #252525 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREYS6:	/* greys6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7f7f7;	/* #f7f7f7 1 */
			break;
		case 2:
			ret = 0x00d9d9d9;	/* #d9d9d9 2 */
			break;
		case 3:
			ret = 0x00bdbdbd;	/* #bdbdbd 3 */
			break;
		case 4:
			ret = 0x00969696;	/* #969696 4 */
			break;
		case 5:
			ret = 0x00636363;	/* #636363 5 */
			break;
		case 6:
			ret = 0x00252525;	/* #252525 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREYS7:	/* greys7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7f7f7;	/* #f7f7f7 1 */
			break;
		case 2:
			ret = 0x00d9d9d9;	/* #d9d9d9 2 */
			break;
		case 3:
			ret = 0x00bdbdbd;	/* #bdbdbd 3 */
			break;
		case 4:
			ret = 0x00969696;	/* #969696 4 */
			break;
		case 5:
			ret = 0x00737373;	/* #737373 5 */
			break;
		case 6:
			ret = 0x00525252;	/* #525252 6 */
			break;
		case 7:
			ret = 0x00252525;	/* #252525 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREYS8:	/* greys8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffff;	/* #ffffff 1 */
			break;
		case 2:
			ret = 0x00f0f0f0;	/* #f0f0f0 2 */
			break;
		case 3:
			ret = 0x00d9d9d9;	/* #d9d9d9 3 */
			break;
		case 4:
			ret = 0x00bdbdbd;	/* #bdbdbd 4 */
			break;
		case 5:
			ret = 0x00969696;	/* #969696 5 */
			break;
		case 6:
			ret = 0x00737373;	/* #737373 6 */
			break;
		case 7:
			ret = 0x00525252;	/* #525252 7 */
			break;
		case 8:
			ret = 0x00252525;	/* #252525 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_GREYS9:	/* greys9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffff;	/* #ffffff 1 */
			break;
		case 2:
			ret = 0x00f0f0f0;	/* #f0f0f0 2 */
			break;
		case 3:
			ret = 0x00d9d9d9;	/* #d9d9d9 3 */
			break;
		case 4:
			ret = 0x00bdbdbd;	/* #bdbdbd 4 */
			break;
		case 5:
			ret = 0x00969696;	/* #969696 5 */
			break;
		case 6:
			ret = 0x00737373;	/* #737373 6 */
			break;
		case 7:
			ret = 0x00525252;	/* #525252 7 */
			break;
		case 8:
			ret = 0x00252525;	/* #252525 8 */
			break;
		case 9:
			ret = 0x00000000;	/* #000000 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORANGES3:	/* oranges3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fee6ce;	/* #fee6ce 1 */
			break;
		case 2:
			ret = 0x00fdae6b;	/* #fdae6b 2 */
			break;
		case 3:
			ret = 0x00e6550d;	/* #e6550d 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORANGES4:	/* oranges4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00feedde;	/* #feedde 1 */
			break;
		case 2:
			ret = 0x00fdbe85;	/* #fdbe85 2 */
			break;
		case 3:
			ret = 0x00fd8d3c;	/* #fd8d3c 3 */
			break;
		case 4:
			ret = 0x00d94701;	/* #d94701 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORANGES5:	/* oranges5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00feedde;	/* #feedde 1 */
			break;
		case 2:
			ret = 0x00fdbe85;	/* #fdbe85 2 */
			break;
		case 3:
			ret = 0x00fd8d3c;	/* #fd8d3c 3 */
			break;
		case 4:
			ret = 0x00e6550d;	/* #e6550d 4 */
			break;
		case 5:
			ret = 0x00a63603;	/* #a63603 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORANGES6:	/* oranges6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00feedde;	/* #feedde 1 */
			break;
		case 2:
			ret = 0x00fdd0a2;	/* #fdd0a2 2 */
			break;
		case 3:
			ret = 0x00fdae6b;	/* #fdae6b 3 */
			break;
		case 4:
			ret = 0x00fd8d3c;	/* #fd8d3c 4 */
			break;
		case 5:
			ret = 0x00e6550d;	/* #e6550d 5 */
			break;
		case 6:
			ret = 0x00a63603;	/* #a63603 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORANGES7:	/* oranges7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00feedde;	/* #feedde 1 */
			break;
		case 2:
			ret = 0x00fdd0a2;	/* #fdd0a2 2 */
			break;
		case 3:
			ret = 0x00fdae6b;	/* #fdae6b 3 */
			break;
		case 4:
			ret = 0x00fd8d3c;	/* #fd8d3c 4 */
			break;
		case 5:
			ret = 0x00f16913;	/* #f16913 5 */
			break;
		case 6:
			ret = 0x00d94801;	/* #d94801 6 */
			break;
		case 7:
			ret = 0x008c2d04;	/* #8c2d04 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORANGES8:	/* oranges8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fff5eb;	/* #fff5eb 1 */
			break;
		case 2:
			ret = 0x00fee6ce;	/* #fee6ce 2 */
			break;
		case 3:
			ret = 0x00fdd0a2;	/* #fdd0a2 3 */
			break;
		case 4:
			ret = 0x00fdae6b;	/* #fdae6b 4 */
			break;
		case 5:
			ret = 0x00fd8d3c;	/* #fd8d3c 5 */
			break;
		case 6:
			ret = 0x00f16913;	/* #f16913 6 */
			break;
		case 7:
			ret = 0x00d94801;	/* #d94801 7 */
			break;
		case 8:
			ret = 0x008c2d04;	/* #8c2d04 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORANGES9:	/* oranges9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fff5eb;	/* #fff5eb 1 */
			break;
		case 2:
			ret = 0x00fee6ce;	/* #fee6ce 2 */
			break;
		case 3:
			ret = 0x00fdd0a2;	/* #fdd0a2 3 */
			break;
		case 4:
			ret = 0x00fdae6b;	/* #fdae6b 4 */
			break;
		case 5:
			ret = 0x00fd8d3c;	/* #fd8d3c 5 */
			break;
		case 6:
			ret = 0x00f16913;	/* #f16913 6 */
			break;
		case 7:
			ret = 0x00d94801;	/* #d94801 7 */
			break;
		case 8:
			ret = 0x00a63603;	/* #a63603 8 */
			break;
		case 9:
			ret = 0x007f2704;	/* #7f2704 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORRD3:	/* orrd3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fee8c8;	/* #fee8c8 1 */
			break;
		case 2:
			ret = 0x00fdbb84;	/* #fdbb84 2 */
			break;
		case 3:
			ret = 0x00e34a33;	/* #e34a33 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORRD4:	/* orrd4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fef0d9;	/* #fef0d9 1 */
			break;
		case 2:
			ret = 0x00fdcc8a;	/* #fdcc8a 2 */
			break;
		case 3:
			ret = 0x00fc8d59;	/* #fc8d59 3 */
			break;
		case 4:
			ret = 0x00d7301f;	/* #d7301f 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORRD5:	/* orrd5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fef0d9;	/* #fef0d9 1 */
			break;
		case 2:
			ret = 0x00fdcc8a;	/* #fdcc8a 2 */
			break;
		case 3:
			ret = 0x00fc8d59;	/* #fc8d59 3 */
			break;
		case 4:
			ret = 0x00e34a33;	/* #e34a33 4 */
			break;
		case 5:
			ret = 0x00b30000;	/* #b30000 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORRD6:	/* orrd6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fef0d9;	/* #fef0d9 1 */
			break;
		case 2:
			ret = 0x00fdd49e;	/* #fdd49e 2 */
			break;
		case 3:
			ret = 0x00fdbb84;	/* #fdbb84 3 */
			break;
		case 4:
			ret = 0x00fc8d59;	/* #fc8d59 4 */
			break;
		case 5:
			ret = 0x00e34a33;	/* #e34a33 5 */
			break;
		case 6:
			ret = 0x00b30000;	/* #b30000 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORRD7:	/* orrd7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fef0d9;	/* #fef0d9 1 */
			break;
		case 2:
			ret = 0x00fdd49e;	/* #fdd49e 2 */
			break;
		case 3:
			ret = 0x00fdbb84;	/* #fdbb84 3 */
			break;
		case 4:
			ret = 0x00fc8d59;	/* #fc8d59 4 */
			break;
		case 5:
			ret = 0x00ef6548;	/* #ef6548 5 */
			break;
		case 6:
			ret = 0x00d7301f;	/* #d7301f 6 */
			break;
		case 7:
			ret = 0x00990000;	/* #990000 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORRD8:	/* orrd8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fff7ec;	/* #fff7ec 1 */
			break;
		case 2:
			ret = 0x00fee8c8;	/* #fee8c8 2 */
			break;
		case 3:
			ret = 0x00fdd49e;	/* #fdd49e 3 */
			break;
		case 4:
			ret = 0x00fdbb84;	/* #fdbb84 4 */
			break;
		case 5:
			ret = 0x00fc8d59;	/* #fc8d59 5 */
			break;
		case 6:
			ret = 0x00ef6548;	/* #ef6548 6 */
			break;
		case 7:
			ret = 0x00d7301f;	/* #d7301f 7 */
			break;
		case 8:
			ret = 0x00990000;	/* #990000 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_ORRD9:	/* orrd9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fff7ec;	/* #fff7ec 1 */
			break;
		case 2:
			ret = 0x00fee8c8;	/* #fee8c8 2 */
			break;
		case 3:
			ret = 0x00fdd49e;	/* #fdd49e 3 */
			break;
		case 4:
			ret = 0x00fdbb84;	/* #fdbb84 4 */
			break;
		case 5:
			ret = 0x00fc8d59;	/* #fc8d59 5 */
			break;
		case 6:
			ret = 0x00ef6548;	/* #ef6548 6 */
			break;
		case 7:
			ret = 0x00d7301f;	/* #d7301f 7 */
			break;
		case 8:
			ret = 0x00b30000;	/* #b30000 8 */
			break;
		case 9:
			ret = 0x007f0000;	/* #7f0000 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PAIRED10:	/* paired10 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a6cee3;	/* #a6cee3 1 */
			break;
		case 2:
			ret = 0x001f78b4;	/* #1f78b4 2 */
			break;
		case 3:
			ret = 0x00b2df8a;	/* #b2df8a 3 */
			break;
		case 4:
			ret = 0x0033a02c;	/* #33a02c 4 */
			break;
		case 5:
			ret = 0x00fb9a99;	/* #fb9a99 5 */
			break;
		case 6:
			ret = 0x00e31a1c;	/* #e31a1c 6 */
			break;
		case 7:
			ret = 0x00fdbf6f;	/* #fdbf6f 7 */
			break;
		case 8:
			ret = 0x00ff7f00;	/* #ff7f00 8 */
			break;
		case 9:
			ret = 0x00cab2d6;	/* #cab2d6 9 */
			break;
		case 10:
			ret = 0x006a3d9a;	/* #6a3d9a 10 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PAIRED11:	/* paired11 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a6cee3;	/* #a6cee3 1 */
			break;
		case 2:
			ret = 0x001f78b4;	/* #1f78b4 2 */
			break;
		case 3:
			ret = 0x00b2df8a;	/* #b2df8a 3 */
			break;
		case 4:
			ret = 0x0033a02c;	/* #33a02c 4 */
			break;
		case 5:
			ret = 0x00fb9a99;	/* #fb9a99 5 */
			break;
		case 6:
			ret = 0x00e31a1c;	/* #e31a1c 6 */
			break;
		case 7:
			ret = 0x00fdbf6f;	/* #fdbf6f 7 */
			break;
		case 8:
			ret = 0x00ff7f00;	/* #ff7f00 8 */
			break;
		case 9:
			ret = 0x00cab2d6;	/* #cab2d6 9 */
			break;
		case 10:
			ret = 0x006a3d9a;	/* #6a3d9a 10 */
			break;
		case 11:
			ret = 0x00ffff99;	/* #ffff99 11 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PAIRED12:	/* paired12 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a6cee3;	/* #a6cee3 1 */
			break;
		case 2:
			ret = 0x001f78b4;	/* #1f78b4 2 */
			break;
		case 3:
			ret = 0x00b2df8a;	/* #b2df8a 3 */
			break;
		case 4:
			ret = 0x0033a02c;	/* #33a02c 4 */
			break;
		case 5:
			ret = 0x00fb9a99;	/* #fb9a99 5 */
			break;
		case 6:
			ret = 0x00e31a1c;	/* #e31a1c 6 */
			break;
		case 7:
			ret = 0x00fdbf6f;	/* #fdbf6f 7 */
			break;
		case 8:
			ret = 0x00ff7f00;	/* #ff7f00 8 */
			break;
		case 9:
			ret = 0x00cab2d6;	/* #cab2d6 9 */
			break;
		case 10:
			ret = 0x006a3d9a;	/* #6a3d9a 10 */
			break;
		case 11:
			ret = 0x00ffff99;	/* #ffff99 11 */
			break;
		case 12:
			ret = 0x00b15928;	/* #b15928 12 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PAIRED3:	/* paired3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a6cee3;	/* #a6cee3 1 */
			break;
		case 2:
			ret = 0x001f78b4;	/* #1f78b4 2 */
			break;
		case 3:
			ret = 0x00b2df8a;	/* #b2df8a 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PAIRED4:	/* paired4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a6cee3;	/* #a6cee3 1 */
			break;
		case 2:
			ret = 0x001f78b4;	/* #1f78b4 2 */
			break;
		case 3:
			ret = 0x00b2df8a;	/* #b2df8a 3 */
			break;
		case 4:
			ret = 0x0033a02c;	/* #33a02c 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PAIRED5:	/* paired5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a6cee3;	/* #a6cee3 1 */
			break;
		case 2:
			ret = 0x001f78b4;	/* #1f78b4 2 */
			break;
		case 3:
			ret = 0x00b2df8a;	/* #b2df8a 3 */
			break;
		case 4:
			ret = 0x0033a02c;	/* #33a02c 4 */
			break;
		case 5:
			ret = 0x00fb9a99;	/* #fb9a99 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PAIRED6:	/* paired6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a6cee3;	/* #a6cee3 1 */
			break;
		case 2:
			ret = 0x001f78b4;	/* #1f78b4 2 */
			break;
		case 3:
			ret = 0x00b2df8a;	/* #b2df8a 3 */
			break;
		case 4:
			ret = 0x0033a02c;	/* #33a02c 4 */
			break;
		case 5:
			ret = 0x00fb9a99;	/* #fb9a99 5 */
			break;
		case 6:
			ret = 0x00e31a1c;	/* #e31a1c 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PAIRED7:	/* paired7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a6cee3;	/* #a6cee3 1 */
			break;
		case 2:
			ret = 0x001f78b4;	/* #1f78b4 2 */
			break;
		case 3:
			ret = 0x00b2df8a;	/* #b2df8a 3 */
			break;
		case 4:
			ret = 0x0033a02c;	/* #33a02c 4 */
			break;
		case 5:
			ret = 0x00fb9a99;	/* #fb9a99 5 */
			break;
		case 6:
			ret = 0x00e31a1c;	/* #e31a1c 6 */
			break;
		case 7:
			ret = 0x00fdbf6f;	/* #fdbf6f 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PAIRED8:	/* paired8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a6cee3;	/* #a6cee3 1 */
			break;
		case 2:
			ret = 0x001f78b4;	/* #1f78b4 2 */
			break;
		case 3:
			ret = 0x00b2df8a;	/* #b2df8a 3 */
			break;
		case 4:
			ret = 0x0033a02c;	/* #33a02c 4 */
			break;
		case 5:
			ret = 0x00fb9a99;	/* #fb9a99 5 */
			break;
		case 6:
			ret = 0x00e31a1c;	/* #e31a1c 6 */
			break;
		case 7:
			ret = 0x00fdbf6f;	/* #fdbf6f 7 */
			break;
		case 8:
			ret = 0x00ff7f00;	/* #ff7f00 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PAIRED9:	/* paired9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a6cee3;	/* #a6cee3 1 */
			break;
		case 2:
			ret = 0x001f78b4;	/* #1f78b4 2 */
			break;
		case 3:
			ret = 0x00b2df8a;	/* #b2df8a 3 */
			break;
		case 4:
			ret = 0x0033a02c;	/* #33a02c 4 */
			break;
		case 5:
			ret = 0x00fb9a99;	/* #fb9a99 5 */
			break;
		case 6:
			ret = 0x00e31a1c;	/* #e31a1c 6 */
			break;
		case 7:
			ret = 0x00fdbf6f;	/* #fdbf6f 7 */
			break;
		case 8:
			ret = 0x00ff7f00;	/* #ff7f00 8 */
			break;
		case 9:
			ret = 0x00cab2d6;	/* #cab2d6 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PASTEL13:	/* pastel13 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fbb4ae;	/* #fbb4ae 1 */
			break;
		case 2:
			ret = 0x00b3cde3;	/* #b3cde3 2 */
			break;
		case 3:
			ret = 0x00ccebc5;	/* #ccebc5 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PASTEL14:	/* pastel14 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fbb4ae;	/* #fbb4ae 1 */
			break;
		case 2:
			ret = 0x00b3cde3;	/* #b3cde3 2 */
			break;
		case 3:
			ret = 0x00ccebc5;	/* #ccebc5 3 */
			break;
		case 4:
			ret = 0x00decbe4;	/* #decbe4 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PASTEL15:	/* pastel15 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fbb4ae;	/* #fbb4ae 1 */
			break;
		case 2:
			ret = 0x00b3cde3;	/* #b3cde3 2 */
			break;
		case 3:
			ret = 0x00ccebc5;	/* #ccebc5 3 */
			break;
		case 4:
			ret = 0x00decbe4;	/* #decbe4 4 */
			break;
		case 5:
			ret = 0x00fed9a6;	/* #fed9a6 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PASTEL16:	/* pastel16 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fbb4ae;	/* #fbb4ae 1 */
			break;
		case 2:
			ret = 0x00b3cde3;	/* #b3cde3 2 */
			break;
		case 3:
			ret = 0x00ccebc5;	/* #ccebc5 3 */
			break;
		case 4:
			ret = 0x00decbe4;	/* #decbe4 4 */
			break;
		case 5:
			ret = 0x00fed9a6;	/* #fed9a6 5 */
			break;
		case 6:
			ret = 0x00ffffcc;	/* #ffffcc 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PASTEL17:	/* pastel17 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fbb4ae;	/* #fbb4ae 1 */
			break;
		case 2:
			ret = 0x00b3cde3;	/* #b3cde3 2 */
			break;
		case 3:
			ret = 0x00ccebc5;	/* #ccebc5 3 */
			break;
		case 4:
			ret = 0x00decbe4;	/* #decbe4 4 */
			break;
		case 5:
			ret = 0x00fed9a6;	/* #fed9a6 5 */
			break;
		case 6:
			ret = 0x00ffffcc;	/* #ffffcc 6 */
			break;
		case 7:
			ret = 0x00e5d8bd;	/* #e5d8bd 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PASTEL18:	/* pastel18 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fbb4ae;	/* #fbb4ae 1 */
			break;
		case 2:
			ret = 0x00b3cde3;	/* #b3cde3 2 */
			break;
		case 3:
			ret = 0x00ccebc5;	/* #ccebc5 3 */
			break;
		case 4:
			ret = 0x00decbe4;	/* #decbe4 4 */
			break;
		case 5:
			ret = 0x00fed9a6;	/* #fed9a6 5 */
			break;
		case 6:
			ret = 0x00ffffcc;	/* #ffffcc 6 */
			break;
		case 7:
			ret = 0x00e5d8bd;	/* #e5d8bd 7 */
			break;
		case 8:
			ret = 0x00fddaec;	/* #fddaec 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PASTEL19:	/* pastel19 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fbb4ae;	/* #fbb4ae 1 */
			break;
		case 2:
			ret = 0x00b3cde3;	/* #b3cde3 2 */
			break;
		case 3:
			ret = 0x00ccebc5;	/* #ccebc5 3 */
			break;
		case 4:
			ret = 0x00decbe4;	/* #decbe4 4 */
			break;
		case 5:
			ret = 0x00fed9a6;	/* #fed9a6 5 */
			break;
		case 6:
			ret = 0x00ffffcc;	/* #ffffcc 6 */
			break;
		case 7:
			ret = 0x00e5d8bd;	/* #e5d8bd 7 */
			break;
		case 8:
			ret = 0x00fddaec;	/* #fddaec 8 */
			break;
		case 9:
			ret = 0x00f2f2f2;	/* #f2f2f2 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PASTEL23:	/* pastel23 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b3e2cd;	/* #b3e2cd 1 */
			break;
		case 2:
			ret = 0x00fdcdac;	/* #fdcdac 2 */
			break;
		case 3:
			ret = 0x00cbd5e8;	/* #cbd5e8 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PASTEL24:	/* pastel24 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b3e2cd;	/* #b3e2cd 1 */
			break;
		case 2:
			ret = 0x00fdcdac;	/* #fdcdac 2 */
			break;
		case 3:
			ret = 0x00cbd5e8;	/* #cbd5e8 3 */
			break;
		case 4:
			ret = 0x00f4cae4;	/* #f4cae4 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PASTEL25:	/* pastel25 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b3e2cd;	/* #b3e2cd 1 */
			break;
		case 2:
			ret = 0x00fdcdac;	/* #fdcdac 2 */
			break;
		case 3:
			ret = 0x00cbd5e8;	/* #cbd5e8 3 */
			break;
		case 4:
			ret = 0x00f4cae4;	/* #f4cae4 4 */
			break;
		case 5:
			ret = 0x00e6f5c9;	/* #e6f5c9 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PASTEL26:	/* pastel26 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b3e2cd;	/* #b3e2cd 1 */
			break;
		case 2:
			ret = 0x00fdcdac;	/* #fdcdac 2 */
			break;
		case 3:
			ret = 0x00cbd5e8;	/* #cbd5e8 3 */
			break;
		case 4:
			ret = 0x00f4cae4;	/* #f4cae4 4 */
			break;
		case 5:
			ret = 0x00e6f5c9;	/* #e6f5c9 5 */
			break;
		case 6:
			ret = 0x00fff2ae;	/* #fff2ae 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PASTEL27:	/* pastel27 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b3e2cd;	/* #b3e2cd 1 */
			break;
		case 2:
			ret = 0x00fdcdac;	/* #fdcdac 2 */
			break;
		case 3:
			ret = 0x00cbd5e8;	/* #cbd5e8 3 */
			break;
		case 4:
			ret = 0x00f4cae4;	/* #f4cae4 4 */
			break;
		case 5:
			ret = 0x00e6f5c9;	/* #e6f5c9 5 */
			break;
		case 6:
			ret = 0x00fff2ae;	/* #fff2ae 6 */
			break;
		case 7:
			ret = 0x00f1e2cc;	/* #f1e2cc 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PASTEL28:	/* pastel28 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b3e2cd;	/* #b3e2cd 1 */
			break;
		case 2:
			ret = 0x00fdcdac;	/* #fdcdac 2 */
			break;
		case 3:
			ret = 0x00cbd5e8;	/* #cbd5e8 3 */
			break;
		case 4:
			ret = 0x00f4cae4;	/* #f4cae4 4 */
			break;
		case 5:
			ret = 0x00e6f5c9;	/* #e6f5c9 5 */
			break;
		case 6:
			ret = 0x00fff2ae;	/* #fff2ae 6 */
			break;
		case 7:
			ret = 0x00f1e2cc;	/* #f1e2cc 7 */
			break;
		case 8:
			ret = 0x00cccccc;	/* #cccccc 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PIYG10:	/* piyg10 color scheme */
		switch (number) {
		case 1:
			ret = 0x008e0152;	/* #8e0152 1 */
			break;
		case 2:
			ret = 0x00c51b7d;	/* #c51b7d 2 */
			break;
		case 3:
			ret = 0x00de77ae;	/* #de77ae 3 */
			break;
		case 4:
			ret = 0x00f1b6da;	/* #f1b6da 4 */
			break;
		case 5:
			ret = 0x00fde0ef;	/* #fde0ef 5 */
			break;
		case 6:
			ret = 0x00e6f5d0;	/* #e6f5d0 6 */
			break;
		case 7:
			ret = 0x00b8e186;	/* #b8e186 7 */
			break;
		case 8:
			ret = 0x007fbc41;	/* #7fbc41 8 */
			break;
		case 9:
			ret = 0x004d9221;	/* #4d9221 9 */
			break;
		case 10:
			ret = 0x00276419;	/* #276419 10 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PIYG11:	/* piyg11 color scheme */
		switch (number) {
		case 1:
			ret = 0x008e0152;	/* #8e0152 1 */
			break;
		case 2:
			ret = 0x00c51b7d;	/* #c51b7d 2 */
			break;
		case 3:
			ret = 0x00de77ae;	/* #de77ae 3 */
			break;
		case 4:
			ret = 0x00f1b6da;	/* #f1b6da 4 */
			break;
		case 5:
			ret = 0x00fde0ef;	/* #fde0ef 5 */
			break;
		case 6:
			ret = 0x00f7f7f7;	/* #f7f7f7 6 */
			break;
		case 7:
			ret = 0x00e6f5d0;	/* #e6f5d0 7 */
			break;
		case 8:
			ret = 0x00b8e186;	/* #b8e186 8 */
			break;
		case 9:
			ret = 0x007fbc41;	/* #7fbc41 9 */
			break;
		case 10:
			ret = 0x004d9221;	/* #4d9221 10 */
			break;
		case 11:
			ret = 0x00276419;	/* #276419 11 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PIYG3:	/* piyg3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e9a3c9;	/* #e9a3c9 1 */
			break;
		case 2:
			ret = 0x00f7f7f7;	/* #f7f7f7 2 */
			break;
		case 3:
			ret = 0x00a1d76a;	/* #a1d76a 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PIYG4:	/* piyg4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d01c8b;	/* #d01c8b 1 */
			break;
		case 2:
			ret = 0x00f1b6da;	/* #f1b6da 2 */
			break;
		case 3:
			ret = 0x00b8e186;	/* #b8e186 3 */
			break;
		case 4:
			ret = 0x004dac26;	/* #4dac26 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PIYG5:	/* piyg5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d01c8b;	/* #d01c8b 1 */
			break;
		case 2:
			ret = 0x00f1b6da;	/* #f1b6da 2 */
			break;
		case 3:
			ret = 0x00f7f7f7;	/* #f7f7f7 3 */
			break;
		case 4:
			ret = 0x00b8e186;	/* #b8e186 4 */
			break;
		case 5:
			ret = 0x004dac26;	/* #4dac26 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PIYG6:	/* piyg6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00c51b7d;	/* #c51b7d 1 */
			break;
		case 2:
			ret = 0x00e9a3c9;	/* #e9a3c9 2 */
			break;
		case 3:
			ret = 0x00fde0ef;	/* #fde0ef 3 */
			break;
		case 4:
			ret = 0x00e6f5d0;	/* #e6f5d0 4 */
			break;
		case 5:
			ret = 0x00a1d76a;	/* #a1d76a 5 */
			break;
		case 6:
			ret = 0x004d9221;	/* #4d9221 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PIYG7:	/* piyg7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00c51b7d;	/* #c51b7d 1 */
			break;
		case 2:
			ret = 0x00e9a3c9;	/* #e9a3c9 2 */
			break;
		case 3:
			ret = 0x00fde0ef;	/* #fde0ef 3 */
			break;
		case 4:
			ret = 0x00f7f7f7;	/* #f7f7f7 4 */
			break;
		case 5:
			ret = 0x00e6f5d0;	/* #e6f5d0 5 */
			break;
		case 6:
			ret = 0x00a1d76a;	/* #a1d76a 6 */
			break;
		case 7:
			ret = 0x004d9221;	/* #4d9221 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PIYG8:	/* piyg8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00c51b7d;	/* #c51b7d 1 */
			break;
		case 2:
			ret = 0x00de77ae;	/* #de77ae 2 */
			break;
		case 3:
			ret = 0x00f1b6da;	/* #f1b6da 3 */
			break;
		case 4:
			ret = 0x00fde0ef;	/* #fde0ef 4 */
			break;
		case 5:
			ret = 0x00e6f5d0;	/* #e6f5d0 5 */
			break;
		case 6:
			ret = 0x00b8e186;	/* #b8e186 6 */
			break;
		case 7:
			ret = 0x007fbc41;	/* #7fbc41 7 */
			break;
		case 8:
			ret = 0x004d9221;	/* #4d9221 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PIYG9:	/* piyg9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00c51b7d;	/* #c51b7d 1 */
			break;
		case 2:
			ret = 0x00de77ae;	/* #de77ae 2 */
			break;
		case 3:
			ret = 0x00f1b6da;	/* #f1b6da 3 */
			break;
		case 4:
			ret = 0x00fde0ef;	/* #fde0ef 4 */
			break;
		case 5:
			ret = 0x00f7f7f7;	/* #f7f7f7 5 */
			break;
		case 6:
			ret = 0x00e6f5d0;	/* #e6f5d0 6 */
			break;
		case 7:
			ret = 0x00b8e186;	/* #b8e186 7 */
			break;
		case 8:
			ret = 0x007fbc41;	/* #7fbc41 8 */
			break;
		case 9:
			ret = 0x004d9221;	/* #4d9221 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PRGN10:	/* prgn10 color scheme */
		switch (number) {
		case 1:
			ret = 0x0040004b;	/* #40004b 1 */
			break;
		case 2:
			ret = 0x00762a83;	/* #762a83 2 */
			break;
		case 3:
			ret = 0x009970ab;	/* #9970ab 3 */
			break;
		case 4:
			ret = 0x00c2a5cf;	/* #c2a5cf 4 */
			break;
		case 5:
			ret = 0x00e7d4e8;	/* #e7d4e8 5 */
			break;
		case 6:
			ret = 0x00d9f0d3;	/* #d9f0d3 6 */
			break;
		case 7:
			ret = 0x00a6dba0;	/* #a6dba0 7 */
			break;
		case 8:
			ret = 0x005aae61;	/* #5aae61 8 */
			break;
		case 9:
			ret = 0x001b7837;	/* #1b7837 9 */
			break;
		case 10:
			ret = 0x0000441b;	/* #00441b 10 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PRGN11:	/* prgn11 color scheme */
		switch (number) {
		case 1:
			ret = 0x0040004b;	/* #40004b 1 */
			break;
		case 2:
			ret = 0x00762a83;	/* #762a83 2 */
			break;
		case 3:
			ret = 0x009970ab;	/* #9970ab 3 */
			break;
		case 4:
			ret = 0x00c2a5cf;	/* #c2a5cf 4 */
			break;
		case 5:
			ret = 0x00e7d4e8;	/* #e7d4e8 5 */
			break;
		case 6:
			ret = 0x00f7f7f7;	/* #f7f7f7 6 */
			break;
		case 7:
			ret = 0x00d9f0d3;	/* #d9f0d3 7 */
			break;
		case 8:
			ret = 0x00a6dba0;	/* #a6dba0 8 */
			break;
		case 9:
			ret = 0x005aae61;	/* #5aae61 9 */
			break;
		case 10:
			ret = 0x001b7837;	/* #1b7837 10 */
			break;
		case 11:
			ret = 0x0000441b;	/* #00441b 11 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PRGN3:	/* prgn3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00af8dc3;	/* #af8dc3 1 */
			break;
		case 2:
			ret = 0x00f7f7f7;	/* #f7f7f7 2 */
			break;
		case 3:
			ret = 0x007fbf7b;	/* #7fbf7b 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PRGN4:	/* prgn4 color scheme */
		switch (number) {
		case 1:
			ret = 0x007b3294;	/* #7b3294 1 */
			break;
		case 2:
			ret = 0x00c2a5cf;	/* #c2a5cf 2 */
			break;
		case 3:
			ret = 0x00a6dba0;	/* #a6dba0 3 */
			break;
		case 4:
			ret = 0x00008837;	/* #008837 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PRGN5:	/* prgn5 color scheme */
		switch (number) {
		case 1:
			ret = 0x007b3294;	/* #7b3294 1 */
			break;
		case 2:
			ret = 0x00c2a5cf;	/* #c2a5cf 2 */
			break;
		case 3:
			ret = 0x00f7f7f7;	/* #f7f7f7 3 */
			break;
		case 4:
			ret = 0x00a6dba0;	/* #a6dba0 4 */
			break;
		case 5:
			ret = 0x00008837;	/* #008837 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PRGN6:	/* prgn6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00762a83;	/* #762a83 1 */
			break;
		case 2:
			ret = 0x00af8dc3;	/* #af8dc3 2 */
			break;
		case 3:
			ret = 0x00e7d4e8;	/* #e7d4e8 3 */
			break;
		case 4:
			ret = 0x00d9f0d3;	/* #d9f0d3 4 */
			break;
		case 5:
			ret = 0x007fbf7b;	/* #7fbf7b 5 */
			break;
		case 6:
			ret = 0x001b7837;	/* #1b7837 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PRGN7:	/* prgn7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00762a83;	/* #762a83 1 */
			break;
		case 2:
			ret = 0x00af8dc3;	/* #af8dc3 2 */
			break;
		case 3:
			ret = 0x00e7d4e8;	/* #e7d4e8 3 */
			break;
		case 4:
			ret = 0x00f7f7f7;	/* #f7f7f7 4 */
			break;
		case 5:
			ret = 0x00d9f0d3;	/* #d9f0d3 5 */
			break;
		case 6:
			ret = 0x007fbf7b;	/* #7fbf7b 6 */
			break;
		case 7:
			ret = 0x001b7837;	/* #1b7837 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PRGN8:	/* prgn8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00762a83;	/* #762a83 1 */
			break;
		case 2:
			ret = 0x009970ab;	/* #9970ab 2 */
			break;
		case 3:
			ret = 0x00c2a5cf;	/* #c2a5cf 3 */
			break;
		case 4:
			ret = 0x00e7d4e8;	/* #e7d4e8 4 */
			break;
		case 5:
			ret = 0x00d9f0d3;	/* #d9f0d3 5 */
			break;
		case 6:
			ret = 0x00a6dba0;	/* #a6dba0 6 */
			break;
		case 7:
			ret = 0x005aae61;	/* #5aae61 7 */
			break;
		case 8:
			ret = 0x001b7837;	/* #1b7837 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PRGN9:	/* prgn9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00762a83;	/* #762a83 1 */
			break;
		case 2:
			ret = 0x009970ab;	/* #9970ab 2 */
			break;
		case 3:
			ret = 0x00c2a5cf;	/* #c2a5cf 3 */
			break;
		case 4:
			ret = 0x00e7d4e8;	/* #e7d4e8 4 */
			break;
		case 5:
			ret = 0x00f7f7f7;	/* #f7f7f7 5 */
			break;
		case 6:
			ret = 0x00d9f0d3;	/* #d9f0d3 6 */
			break;
		case 7:
			ret = 0x00a6dba0;	/* #a6dba0 7 */
			break;
		case 8:
			ret = 0x005aae61;	/* #5aae61 8 */
			break;
		case 9:
			ret = 0x001b7837;	/* #1b7837 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBU3:	/* pubu3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ece7f2;	/* #ece7f2 1 */
			break;
		case 2:
			ret = 0x00a6bddb;	/* #a6bddb 2 */
			break;
		case 3:
			ret = 0x002b8cbe;	/* #2b8cbe 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBU4:	/* pubu4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f1eef6;	/* #f1eef6 1 */
			break;
		case 2:
			ret = 0x00bdc9e1;	/* #bdc9e1 2 */
			break;
		case 3:
			ret = 0x0074a9cf;	/* #74a9cf 3 */
			break;
		case 4:
			ret = 0x000570b0;	/* #0570b0 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBU5:	/* pubu5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f1eef6;	/* #f1eef6 1 */
			break;
		case 2:
			ret = 0x00bdc9e1;	/* #bdc9e1 2 */
			break;
		case 3:
			ret = 0x0074a9cf;	/* #74a9cf 3 */
			break;
		case 4:
			ret = 0x002b8cbe;	/* #2b8cbe 4 */
			break;
		case 5:
			ret = 0x00045a8d;	/* #045a8d 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBU6:	/* pubu6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f1eef6;	/* #f1eef6 1 */
			break;
		case 2:
			ret = 0x00d0d1e6;	/* #d0d1e6 2 */
			break;
		case 3:
			ret = 0x00a6bddb;	/* #a6bddb 3 */
			break;
		case 4:
			ret = 0x0074a9cf;	/* #74a9cf 4 */
			break;
		case 5:
			ret = 0x002b8cbe;	/* #2b8cbe 5 */
			break;
		case 6:
			ret = 0x00045a8d;	/* #045a8d 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBU7:	/* pubu7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f1eef6;	/* #f1eef6 1 */
			break;
		case 2:
			ret = 0x00d0d1e6;	/* #d0d1e6 2 */
			break;
		case 3:
			ret = 0x00a6bddb;	/* #a6bddb 3 */
			break;
		case 4:
			ret = 0x0074a9cf;	/* #74a9cf 4 */
			break;
		case 5:
			ret = 0x003690c0;	/* #3690c0 5 */
			break;
		case 6:
			ret = 0x000570b0;	/* #0570b0 6 */
			break;
		case 7:
			ret = 0x00034e7b;	/* #034e7b 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBU8:	/* pubu8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fff7fb;	/* #fff7fb 1 */
			break;
		case 2:
			ret = 0x00ece7f2;	/* #ece7f2 2 */
			break;
		case 3:
			ret = 0x00d0d1e6;	/* #d0d1e6 3 */
			break;
		case 4:
			ret = 0x00a6bddb;	/* #a6bddb 4 */
			break;
		case 5:
			ret = 0x0074a9cf;	/* #74a9cf 5 */
			break;
		case 6:
			ret = 0x003690c0;	/* #3690c0 6 */
			break;
		case 7:
			ret = 0x000570b0;	/* #0570b0 7 */
			break;
		case 8:
			ret = 0x00034e7b;	/* #034e7b 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBU9:	/* pubu9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fff7fb;	/* #fff7fb 1 */
			break;
		case 2:
			ret = 0x00ece7f2;	/* #ece7f2 2 */
			break;
		case 3:
			ret = 0x00d0d1e6;	/* #d0d1e6 3 */
			break;
		case 4:
			ret = 0x00a6bddb;	/* #a6bddb 4 */
			break;
		case 5:
			ret = 0x0074a9cf;	/* #74a9cf 5 */
			break;
		case 6:
			ret = 0x003690c0;	/* #3690c0 6 */
			break;
		case 7:
			ret = 0x000570b0;	/* #0570b0 7 */
			break;
		case 8:
			ret = 0x00045a8d;	/* #045a8d 8 */
			break;
		case 9:
			ret = 0x00023858;	/* #023858 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBUGN3:	/* pubugn3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ece2f0;	/* #ece2f0 1 */
			break;
		case 2:
			ret = 0x00a6bddb;	/* #a6bddb 2 */
			break;
		case 3:
			ret = 0x001c9099;	/* #1c9099 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBUGN4:	/* pubugn4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f6eff7;	/* #f6eff7 1 */
			break;
		case 2:
			ret = 0x00bdc9e1;	/* #bdc9e1 2 */
			break;
		case 3:
			ret = 0x0067a9cf;	/* #67a9cf 3 */
			break;
		case 4:
			ret = 0x0002818a;	/* #02818a 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBUGN5:	/* pubugn5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f6eff7;	/* #f6eff7 1 */
			break;
		case 2:
			ret = 0x00bdc9e1;	/* #bdc9e1 2 */
			break;
		case 3:
			ret = 0x0067a9cf;	/* #67a9cf 3 */
			break;
		case 4:
			ret = 0x001c9099;	/* #1c9099 4 */
			break;
		case 5:
			ret = 0x00016c59;	/* #016c59 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBUGN6:	/* pubugn6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f6eff7;	/* #f6eff7 1 */
			break;
		case 2:
			ret = 0x00d0d1e6;	/* #d0d1e6 2 */
			break;
		case 3:
			ret = 0x00a6bddb;	/* #a6bddb 3 */
			break;
		case 4:
			ret = 0x0067a9cf;	/* #67a9cf 4 */
			break;
		case 5:
			ret = 0x001c9099;	/* #1c9099 5 */
			break;
		case 6:
			ret = 0x00016c59;	/* #016c59 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBUGN7:	/* pubugn7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f6eff7;	/* #f6eff7 1 */
			break;
		case 2:
			ret = 0x00d0d1e6;	/* #d0d1e6 2 */
			break;
		case 3:
			ret = 0x00a6bddb;	/* #a6bddb 3 */
			break;
		case 4:
			ret = 0x0067a9cf;	/* #67a9cf 4 */
			break;
		case 5:
			ret = 0x003690c0;	/* #3690c0 5 */
			break;
		case 6:
			ret = 0x0002818a;	/* #02818a 6 */
			break;
		case 7:
			ret = 0x00016450;	/* #016450 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBUGN8:	/* pubugn8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fff7fb;	/* #fff7fb 1 */
			break;
		case 2:
			ret = 0x00ece2f0;	/* #ece2f0 2 */
			break;
		case 3:
			ret = 0x00d0d1e6;	/* #d0d1e6 3 */
			break;
		case 4:
			ret = 0x00a6bddb;	/* #a6bddb 4 */
			break;
		case 5:
			ret = 0x0067a9cf;	/* #67a9cf 5 */
			break;
		case 6:
			ret = 0x003690c0;	/* #3690c0 6 */
			break;
		case 7:
			ret = 0x0002818a;	/* #02818a 7 */
			break;
		case 8:
			ret = 0x00016450;	/* #016450 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUBUGN9:	/* pubugn9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fff7fb;	/* #fff7fb 1 */
			break;
		case 2:
			ret = 0x00ece2f0;	/* #ece2f0 2 */
			break;
		case 3:
			ret = 0x00d0d1e6;	/* #d0d1e6 3 */
			break;
		case 4:
			ret = 0x00a6bddb;	/* #a6bddb 4 */
			break;
		case 5:
			ret = 0x0067a9cf;	/* #67a9cf 5 */
			break;
		case 6:
			ret = 0x003690c0;	/* #3690c0 6 */
			break;
		case 7:
			ret = 0x0002818a;	/* #02818a 7 */
			break;
		case 8:
			ret = 0x00016c59;	/* #016c59 8 */
			break;
		case 9:
			ret = 0x00014636;	/* #014636 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUOR10:	/* puor10 color scheme */
		switch (number) {
		case 1:
			ret = 0x007f3b08;	/* #7f3b08 1 */
			break;
		case 2:
			ret = 0x00b35806;	/* #b35806 2 */
			break;
		case 3:
			ret = 0x00e08214;	/* #e08214 3 */
			break;
		case 4:
			ret = 0x00fdb863;	/* #fdb863 4 */
			break;
		case 5:
			ret = 0x00fee0b6;	/* #fee0b6 5 */
			break;
		case 6:
			ret = 0x00d8daeb;	/* #d8daeb 6 */
			break;
		case 7:
			ret = 0x00b2abd2;	/* #b2abd2 7 */
			break;
		case 8:
			ret = 0x008073ac;	/* #8073ac 8 */
			break;
		case 9:
			ret = 0x00542788;	/* #542788 9 */
			break;
		case 10:
			ret = 0x002d004b;	/* #2d004b 10 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUOR11:	/* puor11 color scheme */
		switch (number) {
		case 1:
			ret = 0x007f3b08;	/* #7f3b08 1 */
			break;
		case 2:
			ret = 0x00b35806;	/* #b35806 2 */
			break;
		case 3:
			ret = 0x00e08214;	/* #e08214 3 */
			break;
		case 4:
			ret = 0x00fdb863;	/* #fdb863 4 */
			break;
		case 5:
			ret = 0x00fee0b6;	/* #fee0b6 5 */
			break;
		case 6:
			ret = 0x00f7f7f7;	/* #f7f7f7 6 */
			break;
		case 7:
			ret = 0x00d8daeb;	/* #d8daeb 7 */
			break;
		case 8:
			ret = 0x00b2abd2;	/* #b2abd2 8 */
			break;
		case 9:
			ret = 0x008073ac;	/* #8073ac 9 */
			break;
		case 10:
			ret = 0x00542788;	/* #542788 10 */
			break;
		case 11:
			ret = 0x002d004b;	/* #2d004b 11 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUOR3:	/* puor3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f1a340;	/* #f1a340 1 */
			break;
		case 2:
			ret = 0x00f7f7f7;	/* #f7f7f7 2 */
			break;
		case 3:
			ret = 0x00998ec3;	/* #998ec3 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUOR4:	/* puor4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e66101;	/* #e66101 1 */
			break;
		case 2:
			ret = 0x00fdb863;	/* #fdb863 2 */
			break;
		case 3:
			ret = 0x00b2abd2;	/* #b2abd2 3 */
			break;
		case 4:
			ret = 0x005e3c99;	/* #5e3c99 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUOR5:	/* puor5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e66101;	/* #e66101 1 */
			break;
		case 2:
			ret = 0x00fdb863;	/* #fdb863 2 */
			break;
		case 3:
			ret = 0x00f7f7f7;	/* #f7f7f7 3 */
			break;
		case 4:
			ret = 0x00b2abd2;	/* #b2abd2 4 */
			break;
		case 5:
			ret = 0x005e3c99;	/* #5e3c99 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUOR6:	/* puor6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b35806;	/* #b35806 1 */
			break;
		case 2:
			ret = 0x00f1a340;	/* #f1a340 2 */
			break;
		case 3:
			ret = 0x00fee0b6;	/* #fee0b6 3 */
			break;
		case 4:
			ret = 0x00d8daeb;	/* #d8daeb 4 */
			break;
		case 5:
			ret = 0x00998ec3;	/* #998ec3 5 */
			break;
		case 6:
			ret = 0x00542788;	/* #542788 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUOR7:	/* puor7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b35806;	/* #b35806 1 */
			break;
		case 2:
			ret = 0x00f1a340;	/* #f1a340 2 */
			break;
		case 3:
			ret = 0x00fee0b6;	/* #fee0b6 3 */
			break;
		case 4:
			ret = 0x00f7f7f7;	/* #f7f7f7 4 */
			break;
		case 5:
			ret = 0x00d8daeb;	/* #d8daeb 5 */
			break;
		case 6:
			ret = 0x00998ec3;	/* #998ec3 6 */
			break;
		case 7:
			ret = 0x00542788;	/* #542788 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUOR8:	/* puor8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b35806;	/* #b35806 1 */
			break;
		case 2:
			ret = 0x00e08214;	/* #e08214 2 */
			break;
		case 3:
			ret = 0x00fdb863;	/* #fdb863 3 */
			break;
		case 4:
			ret = 0x00fee0b6;	/* #fee0b6 4 */
			break;
		case 5:
			ret = 0x00d8daeb;	/* #d8daeb 5 */
			break;
		case 6:
			ret = 0x00b2abd2;	/* #b2abd2 6 */
			break;
		case 7:
			ret = 0x008073ac;	/* #8073ac 7 */
			break;
		case 8:
			ret = 0x00542788;	/* #542788 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PUOR9:	/* puor9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b35806;	/* #b35806 1 */
			break;
		case 2:
			ret = 0x00e08214;	/* #e08214 2 */
			break;
		case 3:
			ret = 0x00fdb863;	/* #fdb863 3 */
			break;
		case 4:
			ret = 0x00fee0b6;	/* #fee0b6 4 */
			break;
		case 5:
			ret = 0x00f7f7f7;	/* #f7f7f7 5 */
			break;
		case 6:
			ret = 0x00d8daeb;	/* #d8daeb 6 */
			break;
		case 7:
			ret = 0x00b2abd2;	/* #b2abd2 7 */
			break;
		case 8:
			ret = 0x008073ac;	/* #8073ac 8 */
			break;
		case 9:
			ret = 0x00542788;	/* #542788 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURD3:	/* purd3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e7e1ef;	/* #e7e1ef 1 */
			break;
		case 2:
			ret = 0x00c994c7;	/* #c994c7 2 */
			break;
		case 3:
			ret = 0x00dd1c77;	/* #dd1c77 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURD4:	/* purd4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f1eef6;	/* #f1eef6 1 */
			break;
		case 2:
			ret = 0x00d7b5d8;	/* #d7b5d8 2 */
			break;
		case 3:
			ret = 0x00df65b0;	/* #df65b0 3 */
			break;
		case 4:
			ret = 0x00ce1256;	/* #ce1256 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURD5:	/* purd5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f1eef6;	/* #f1eef6 1 */
			break;
		case 2:
			ret = 0x00d7b5d8;	/* #d7b5d8 2 */
			break;
		case 3:
			ret = 0x00df65b0;	/* #df65b0 3 */
			break;
		case 4:
			ret = 0x00dd1c77;	/* #dd1c77 4 */
			break;
		case 5:
			ret = 0x00980043;	/* #980043 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURD6:	/* purd6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f1eef6;	/* #f1eef6 1 */
			break;
		case 2:
			ret = 0x00d4b9da;	/* #d4b9da 2 */
			break;
		case 3:
			ret = 0x00c994c7;	/* #c994c7 3 */
			break;
		case 4:
			ret = 0x00df65b0;	/* #df65b0 4 */
			break;
		case 5:
			ret = 0x00dd1c77;	/* #dd1c77 5 */
			break;
		case 6:
			ret = 0x00980043;	/* #980043 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURD7:	/* purd7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f1eef6;	/* #f1eef6 1 */
			break;
		case 2:
			ret = 0x00d4b9da;	/* #d4b9da 2 */
			break;
		case 3:
			ret = 0x00c994c7;	/* #c994c7 3 */
			break;
		case 4:
			ret = 0x00df65b0;	/* #df65b0 4 */
			break;
		case 5:
			ret = 0x00e7298a;	/* #e7298a 5 */
			break;
		case 6:
			ret = 0x00ce1256;	/* #ce1256 6 */
			break;
		case 7:
			ret = 0x0091003f;	/* #91003f 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURD8:	/* purd8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7f4f9;	/* #f7f4f9 1 */
			break;
		case 2:
			ret = 0x00e7e1ef;	/* #e7e1ef 2 */
			break;
		case 3:
			ret = 0x00d4b9da;	/* #d4b9da 3 */
			break;
		case 4:
			ret = 0x00c994c7;	/* #c994c7 4 */
			break;
		case 5:
			ret = 0x00df65b0;	/* #df65b0 5 */
			break;
		case 6:
			ret = 0x00e7298a;	/* #e7298a 6 */
			break;
		case 7:
			ret = 0x00ce1256;	/* #ce1256 7 */
			break;
		case 8:
			ret = 0x0091003f;	/* #91003f 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURD9:	/* purd9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7f4f9;	/* #f7f4f9 1 */
			break;
		case 2:
			ret = 0x00e7e1ef;	/* #e7e1ef 2 */
			break;
		case 3:
			ret = 0x00d4b9da;	/* #d4b9da 3 */
			break;
		case 4:
			ret = 0x00c994c7;	/* #c994c7 4 */
			break;
		case 5:
			ret = 0x00df65b0;	/* #df65b0 5 */
			break;
		case 6:
			ret = 0x00e7298a;	/* #e7298a 6 */
			break;
		case 7:
			ret = 0x00ce1256;	/* #ce1256 7 */
			break;
		case 8:
			ret = 0x00980043;	/* #980043 8 */
			break;
		case 9:
			ret = 0x0067001f;	/* #67001f 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURPLES3:	/* purples3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00efedf5;	/* #efedf5 1 */
			break;
		case 2:
			ret = 0x00bcbddc;	/* #bcbddc 2 */
			break;
		case 3:
			ret = 0x00756bb1;	/* #756bb1 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURPLES4:	/* purples4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f2f0f7;	/* #f2f0f7 1 */
			break;
		case 2:
			ret = 0x00cbc9e2;	/* #cbc9e2 2 */
			break;
		case 3:
			ret = 0x009e9ac8;	/* #9e9ac8 3 */
			break;
		case 4:
			ret = 0x006a51a3;	/* #6a51a3 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURPLES5:	/* purples5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f2f0f7;	/* #f2f0f7 1 */
			break;
		case 2:
			ret = 0x00cbc9e2;	/* #cbc9e2 2 */
			break;
		case 3:
			ret = 0x009e9ac8;	/* #9e9ac8 3 */
			break;
		case 4:
			ret = 0x00756bb1;	/* #756bb1 4 */
			break;
		case 5:
			ret = 0x0054278f;	/* #54278f 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURPLES6:	/* purples6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f2f0f7;	/* #f2f0f7 1 */
			break;
		case 2:
			ret = 0x00dadaeb;	/* #dadaeb 2 */
			break;
		case 3:
			ret = 0x00bcbddc;	/* #bcbddc 3 */
			break;
		case 4:
			ret = 0x009e9ac8;	/* #9e9ac8 4 */
			break;
		case 5:
			ret = 0x00756bb1;	/* #756bb1 5 */
			break;
		case 6:
			ret = 0x0054278f;	/* #54278f 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURPLES7:	/* purples7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f2f0f7;	/* #f2f0f7 1 */
			break;
		case 2:
			ret = 0x00dadaeb;	/* #dadaeb 2 */
			break;
		case 3:
			ret = 0x00bcbddc;	/* #bcbddc 3 */
			break;
		case 4:
			ret = 0x009e9ac8;	/* #9e9ac8 4 */
			break;
		case 5:
			ret = 0x00807dba;	/* #807dba 5 */
			break;
		case 6:
			ret = 0x006a51a3;	/* #6a51a3 6 */
			break;
		case 7:
			ret = 0x004a1486;	/* #4a1486 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURPLES8:	/* purples8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fcfbfd;	/* #fcfbfd 1 */
			break;
		case 2:
			ret = 0x00efedf5;	/* #efedf5 2 */
			break;
		case 3:
			ret = 0x00dadaeb;	/* #dadaeb 3 */
			break;
		case 4:
			ret = 0x00bcbddc;	/* #bcbddc 4 */
			break;
		case 5:
			ret = 0x009e9ac8;	/* #9e9ac8 5 */
			break;
		case 6:
			ret = 0x00807dba;	/* #807dba 6 */
			break;
		case 7:
			ret = 0x006a51a3;	/* #6a51a3 7 */
			break;
		case 8:
			ret = 0x004a1486;	/* #4a1486 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_PURPLES9:	/* purples9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fcfbfd;	/* #fcfbfd 1 */
			break;
		case 2:
			ret = 0x00efedf5;	/* #efedf5 2 */
			break;
		case 3:
			ret = 0x00dadaeb;	/* #dadaeb 3 */
			break;
		case 4:
			ret = 0x00bcbddc;	/* #bcbddc 4 */
			break;
		case 5:
			ret = 0x009e9ac8;	/* #9e9ac8 5 */
			break;
		case 6:
			ret = 0x00807dba;	/* #807dba 6 */
			break;
		case 7:
			ret = 0x006a51a3;	/* #6a51a3 7 */
			break;
		case 8:
			ret = 0x0054278f;	/* #54278f 8 */
			break;
		case 9:
			ret = 0x003f007d;	/* #3f007d 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDBU10:	/* rdbu10 color scheme */
		switch (number) {
		case 1:
			ret = 0x0067001f;	/* #67001f 1 */
			break;
		case 2:
			ret = 0x00b2182b;	/* #b2182b 2 */
			break;
		case 3:
			ret = 0x00d6604d;	/* #d6604d 3 */
			break;
		case 4:
			ret = 0x00f4a582;	/* #f4a582 4 */
			break;
		case 5:
			ret = 0x00fddbc7;	/* #fddbc7 5 */
			break;
		case 6:
			ret = 0x00d1e5f0;	/* #d1e5f0 6 */
			break;
		case 7:
			ret = 0x0092c5de;	/* #92c5de 7 */
			break;
		case 8:
			ret = 0x004393c3;	/* #4393c3 8 */
			break;
		case 9:
			ret = 0x002166ac;	/* #2166ac 9 */
			break;
		case 10:
			ret = 0x00053061;	/* #053061 10 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDBU11:	/* rdbu11 color scheme */
		switch (number) {
		case 1:
			ret = 0x0067001f;	/* #67001f 1 */
			break;
		case 2:
			ret = 0x00b2182b;	/* #b2182b 2 */
			break;
		case 3:
			ret = 0x00d6604d;	/* #d6604d 3 */
			break;
		case 4:
			ret = 0x00f4a582;	/* #f4a582 4 */
			break;
		case 5:
			ret = 0x00fddbc7;	/* #fddbc7 5 */
			break;
		case 6:
			ret = 0x00f7f7f7;	/* #f7f7f7 6 */
			break;
		case 7:
			ret = 0x00d1e5f0;	/* #d1e5f0 7 */
			break;
		case 8:
			ret = 0x0092c5de;	/* #92c5de 8 */
			break;
		case 9:
			ret = 0x004393c3;	/* #4393c3 9 */
			break;
		case 10:
			ret = 0x002166ac;	/* #2166ac 10 */
			break;
		case 11:
			ret = 0x00053061;	/* #053061 11 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDBU3:	/* rdbu3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ef8a62;	/* #ef8a62 1 */
			break;
		case 2:
			ret = 0x00f7f7f7;	/* #f7f7f7 2 */
			break;
		case 3:
			ret = 0x0067a9cf;	/* #67a9cf 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDBU4:	/* rdbu4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ca0020;	/* #ca0020 1 */
			break;
		case 2:
			ret = 0x00f4a582;	/* #f4a582 2 */
			break;
		case 3:
			ret = 0x0092c5de;	/* #92c5de 3 */
			break;
		case 4:
			ret = 0x000571b0;	/* #0571b0 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDBU5:	/* rdbu5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ca0020;	/* #ca0020 1 */
			break;
		case 2:
			ret = 0x00f4a582;	/* #f4a582 2 */
			break;
		case 3:
			ret = 0x00f7f7f7;	/* #f7f7f7 3 */
			break;
		case 4:
			ret = 0x0092c5de;	/* #92c5de 4 */
			break;
		case 5:
			ret = 0x000571b0;	/* #0571b0 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDBU6:	/* rdbu6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b2182b;	/* #b2182b 1 */
			break;
		case 2:
			ret = 0x00ef8a62;	/* #ef8a62 2 */
			break;
		case 3:
			ret = 0x00fddbc7;	/* #fddbc7 3 */
			break;
		case 4:
			ret = 0x00d1e5f0;	/* #d1e5f0 4 */
			break;
		case 5:
			ret = 0x0067a9cf;	/* #67a9cf 5 */
			break;
		case 6:
			ret = 0x002166ac;	/* #2166ac 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDBU7:	/* rdbu7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b2182b;	/* #b2182b 1 */
			break;
		case 2:
			ret = 0x00ef8a62;	/* #ef8a62 2 */
			break;
		case 3:
			ret = 0x00fddbc7;	/* #fddbc7 3 */
			break;
		case 4:
			ret = 0x00f7f7f7;	/* #f7f7f7 4 */
			break;
		case 5:
			ret = 0x00d1e5f0;	/* #d1e5f0 5 */
			break;
		case 6:
			ret = 0x0067a9cf;	/* #67a9cf 6 */
			break;
		case 7:
			ret = 0x002166ac;	/* #2166ac 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDBU8:	/* rdbu8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b2182b;	/* #b2182b 1 */
			break;
		case 2:
			ret = 0x00d6604d;	/* #d6604d 2 */
			break;
		case 3:
			ret = 0x00f4a582;	/* #f4a582 3 */
			break;
		case 4:
			ret = 0x00fddbc7;	/* #fddbc7 4 */
			break;
		case 5:
			ret = 0x00d1e5f0;	/* #d1e5f0 5 */
			break;
		case 6:
			ret = 0x0092c5de;	/* #92c5de 6 */
			break;
		case 7:
			ret = 0x004393c3;	/* #4393c3 7 */
			break;
		case 8:
			ret = 0x002166ac;	/* #2166ac 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDBU9:	/* rdbu9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b2182b;	/* #b2182b 1 */
			break;
		case 2:
			ret = 0x00d6604d;	/* #d6604d 2 */
			break;
		case 3:
			ret = 0x00f4a582;	/* #f4a582 3 */
			break;
		case 4:
			ret = 0x00fddbc7;	/* #fddbc7 4 */
			break;
		case 5:
			ret = 0x00f7f7f7;	/* #f7f7f7 5 */
			break;
		case 6:
			ret = 0x00d1e5f0;	/* #d1e5f0 6 */
			break;
		case 7:
			ret = 0x0092c5de;	/* #92c5de 7 */
			break;
		case 8:
			ret = 0x004393c3;	/* #4393c3 8 */
			break;
		case 9:
			ret = 0x002166ac;	/* #2166ac 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDGY10:	/* rdgy10 color scheme */
		switch (number) {
		case 1:
			ret = 0x0067001f;	/* #67001f 1 */
			break;
		case 2:
			ret = 0x00b2182b;	/* #b2182b 2 */
			break;
		case 3:
			ret = 0x00d6604d;	/* #d6604d 3 */
			break;
		case 4:
			ret = 0x00f4a582;	/* #f4a582 4 */
			break;
		case 5:
			ret = 0x00fddbc7;	/* #fddbc7 5 */
			break;
		case 6:
			ret = 0x00e0e0e0;	/* #e0e0e0 6 */
			break;
		case 7:
			ret = 0x00bababa;	/* #bababa 7 */
			break;
		case 8:
			ret = 0x00878787;	/* #878787 8 */
			break;
		case 9:
			ret = 0x004d4d4d;	/* #4d4d4d 9 */
			break;
		case 10:
			ret = 0x001a1a1a;	/* #1a1a1a 10 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDGY11:	/* rdgy11 color scheme */
		switch (number) {
		case 1:
			ret = 0x0067001f;	/* #67001f 1 */
			break;
		case 2:
			ret = 0x00b2182b;	/* #b2182b 2 */
			break;
		case 3:
			ret = 0x00d6604d;	/* #d6604d 3 */
			break;
		case 4:
			ret = 0x00f4a582;	/* #f4a582 4 */
			break;
		case 5:
			ret = 0x00fddbc7;	/* #fddbc7 5 */
			break;
		case 6:
			ret = 0x00ffffff;	/* #ffffff 6 */
			break;
		case 7:
			ret = 0x00e0e0e0;	/* #e0e0e0 7 */
			break;
		case 8:
			ret = 0x00bababa;	/* #bababa 8 */
			break;
		case 9:
			ret = 0x00878787;	/* #878787 9 */
			break;
		case 10:
			ret = 0x004d4d4d;	/* #4d4d4d 10 */
			break;
		case 11:
			ret = 0x001a1a1a;	/* #1a1a1a 11 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDGY3:	/* rdgy3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ef8a62;	/* #ef8a62 1 */
			break;
		case 2:
			ret = 0x00ffffff;	/* #ffffff 2 */
			break;
		case 3:
			ret = 0x00999999;	/* #999999 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDGY4:	/* rdgy4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ca0020;	/* #ca0020 1 */
			break;
		case 2:
			ret = 0x00f4a582;	/* #f4a582 2 */
			break;
		case 3:
			ret = 0x00bababa;	/* #bababa 3 */
			break;
		case 4:
			ret = 0x00404040;	/* #404040 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDGY5:	/* rdgy5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ca0020;	/* #ca0020 1 */
			break;
		case 2:
			ret = 0x00f4a582;	/* #f4a582 2 */
			break;
		case 3:
			ret = 0x00ffffff;	/* #ffffff 3 */
			break;
		case 4:
			ret = 0x00bababa;	/* #bababa 4 */
			break;
		case 5:
			ret = 0x00404040;	/* #404040 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDGY6:	/* rdgy6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b2182b;	/* #b2182b 1 */
			break;
		case 2:
			ret = 0x00ef8a62;	/* #ef8a62 2 */
			break;
		case 3:
			ret = 0x00fddbc7;	/* #fddbc7 3 */
			break;
		case 4:
			ret = 0x00e0e0e0;	/* #e0e0e0 4 */
			break;
		case 5:
			ret = 0x00999999;	/* #999999 5 */
			break;
		case 6:
			ret = 0x004d4d4d;	/* #4d4d4d 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDGY7:	/* rdgy7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b2182b;	/* #b2182b 1 */
			break;
		case 2:
			ret = 0x00ef8a62;	/* #ef8a62 2 */
			break;
		case 3:
			ret = 0x00fddbc7;	/* #fddbc7 3 */
			break;
		case 4:
			ret = 0x00ffffff;	/* #ffffff 4 */
			break;
		case 5:
			ret = 0x00e0e0e0;	/* #e0e0e0 5 */
			break;
		case 6:
			ret = 0x00999999;	/* #999999 6 */
			break;
		case 7:
			ret = 0x004d4d4d;	/* #4d4d4d 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDGY8:	/* rdgy8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b2182b;	/* #b2182b 1 */
			break;
		case 2:
			ret = 0x00d6604d;	/* #d6604d 2 */
			break;
		case 3:
			ret = 0x00f4a582;	/* #f4a582 3 */
			break;
		case 4:
			ret = 0x00fddbc7;	/* #fddbc7 4 */
			break;
		case 5:
			ret = 0x00e0e0e0;	/* #e0e0e0 5 */
			break;
		case 6:
			ret = 0x00bababa;	/* #bababa 6 */
			break;
		case 7:
			ret = 0x00878787;	/* #878787 7 */
			break;
		case 8:
			ret = 0x004d4d4d;	/* #4d4d4d 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDGY9:	/* rdgy9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00b2182b;	/* #b2182b 1 */
			break;
		case 2:
			ret = 0x00d6604d;	/* #d6604d 2 */
			break;
		case 3:
			ret = 0x00f4a582;	/* #f4a582 3 */
			break;
		case 4:
			ret = 0x00fddbc7;	/* #fddbc7 4 */
			break;
		case 5:
			ret = 0x00ffffff;	/* #ffffff 5 */
			break;
		case 6:
			ret = 0x00e0e0e0;	/* #e0e0e0 6 */
			break;
		case 7:
			ret = 0x00bababa;	/* #bababa 7 */
			break;
		case 8:
			ret = 0x00878787;	/* #878787 8 */
			break;
		case 9:
			ret = 0x004d4d4d;	/* #4d4d4d 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDPU3:	/* rdpu3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fde0dd;	/* #fde0dd 1 */
			break;
		case 2:
			ret = 0x00fa9fb5;	/* #fa9fb5 2 */
			break;
		case 3:
			ret = 0x00c51b8a;	/* #c51b8a 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDPU4:	/* rdpu4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00feebe2;	/* #feebe2 1 */
			break;
		case 2:
			ret = 0x00fbb4b9;	/* #fbb4b9 2 */
			break;
		case 3:
			ret = 0x00f768a1;	/* #f768a1 3 */
			break;
		case 4:
			ret = 0x00ae017e;	/* #ae017e 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDPU5:	/* rdpu5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00feebe2;	/* #feebe2 1 */
			break;
		case 2:
			ret = 0x00fbb4b9;	/* #fbb4b9 2 */
			break;
		case 3:
			ret = 0x00f768a1;	/* #f768a1 3 */
			break;
		case 4:
			ret = 0x00c51b8a;	/* #c51b8a 4 */
			break;
		case 5:
			ret = 0x007a0177;	/* #7a0177 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDPU6:	/* rdpu6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00feebe2;	/* #feebe2 1 */
			break;
		case 2:
			ret = 0x00fcc5c0;	/* #fcc5c0 2 */
			break;
		case 3:
			ret = 0x00fa9fb5;	/* #fa9fb5 3 */
			break;
		case 4:
			ret = 0x00f768a1;	/* #f768a1 4 */
			break;
		case 5:
			ret = 0x00c51b8a;	/* #c51b8a 5 */
			break;
		case 6:
			ret = 0x007a0177;	/* #7a0177 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDPU7:	/* rdpu7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00feebe2;	/* #feebe2 1 */
			break;
		case 2:
			ret = 0x00fcc5c0;	/* #fcc5c0 2 */
			break;
		case 3:
			ret = 0x00fa9fb5;	/* #fa9fb5 3 */
			break;
		case 4:
			ret = 0x00f768a1;	/* #f768a1 4 */
			break;
		case 5:
			ret = 0x00dd3497;	/* #dd3497 5 */
			break;
		case 6:
			ret = 0x00ae017e;	/* #ae017e 6 */
			break;
		case 7:
			ret = 0x007a0177;	/* #7a0177 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDPU8:	/* rdpu8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fff7f3;	/* #fff7f3 1 */
			break;
		case 2:
			ret = 0x00fde0dd;	/* #fde0dd 2 */
			break;
		case 3:
			ret = 0x00fcc5c0;	/* #fcc5c0 3 */
			break;
		case 4:
			ret = 0x00fa9fb5;	/* #fa9fb5 4 */
			break;
		case 5:
			ret = 0x00f768a1;	/* #f768a1 5 */
			break;
		case 6:
			ret = 0x00dd3497;	/* #dd3497 6 */
			break;
		case 7:
			ret = 0x00ae017e;	/* #ae017e 7 */
			break;
		case 8:
			ret = 0x007a0177;	/* #7a0177 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDPU9:	/* rdpu9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fff7f3;	/* #fff7f3 1 */
			break;
		case 2:
			ret = 0x00fde0dd;	/* #fde0dd 2 */
			break;
		case 3:
			ret = 0x00fcc5c0;	/* #fcc5c0 3 */
			break;
		case 4:
			ret = 0x00fa9fb5;	/* #fa9fb5 4 */
			break;
		case 5:
			ret = 0x00f768a1;	/* #f768a1 5 */
			break;
		case 6:
			ret = 0x00dd3497;	/* #dd3497 6 */
			break;
		case 7:
			ret = 0x00ae017e;	/* #ae017e 7 */
			break;
		case 8:
			ret = 0x007a0177;	/* #7a0177 8 */
			break;
		case 9:
			ret = 0x0049006a;	/* #49006a 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLBU10:	/* rdylbu10 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a50026;	/* #a50026 1 */
			break;
		case 2:
			ret = 0x00d73027;	/* #d73027 2 */
			break;
		case 3:
			ret = 0x00f46d43;	/* #f46d43 3 */
			break;
		case 4:
			ret = 0x00fdae61;	/* #fdae61 4 */
			break;
		case 5:
			ret = 0x00fee090;	/* #fee090 5 */
			break;
		case 6:
			ret = 0x00e0f3f8;	/* #e0f3f8 6 */
			break;
		case 7:
			ret = 0x00abd9e9;	/* #abd9e9 7 */
			break;
		case 8:
			ret = 0x0074add1;	/* #74add1 8 */
			break;
		case 9:
			ret = 0x004575b4;	/* #4575b4 9 */
			break;
		case 10:
			ret = 0x00313695;	/* #313695 10 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLBU11:	/* rdylbu11 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a50026;	/* #a50026 1 */
			break;
		case 2:
			ret = 0x00d73027;	/* #d73027 2 */
			break;
		case 3:
			ret = 0x00f46d43;	/* #f46d43 3 */
			break;
		case 4:
			ret = 0x00fdae61;	/* #fdae61 4 */
			break;
		case 5:
			ret = 0x00fee090;	/* #fee090 5 */
			break;
		case 6:
			ret = 0x00ffffbf;	/* #ffffbf 6 */
			break;
		case 7:
			ret = 0x00e0f3f8;	/* #e0f3f8 7 */
			break;
		case 8:
			ret = 0x00abd9e9;	/* #abd9e9 8 */
			break;
		case 9:
			ret = 0x0074add1;	/* #74add1 9 */
			break;
		case 10:
			ret = 0x004575b4;	/* #4575b4 10 */
			break;
		case 11:
			ret = 0x00313695;	/* #313695 11 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLBU3:	/* rdylbu3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fc8d59;	/* #fc8d59 1 */
			break;
		case 2:
			ret = 0x00ffffbf;	/* #ffffbf 2 */
			break;
		case 3:
			ret = 0x0091bfdb;	/* #91bfdb 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLBU4:	/* rdylbu4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d7191c;	/* #d7191c 1 */
			break;
		case 2:
			ret = 0x00fdae61;	/* #fdae61 2 */
			break;
		case 3:
			ret = 0x00abd9e9;	/* #abd9e9 3 */
			break;
		case 4:
			ret = 0x002c7bb6;	/* #2c7bb6 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLBU5:	/* rdylbu5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d7191c;	/* #d7191c 1 */
			break;
		case 2:
			ret = 0x00fdae61;	/* #fdae61 2 */
			break;
		case 3:
			ret = 0x00ffffbf;	/* #ffffbf 3 */
			break;
		case 4:
			ret = 0x00abd9e9;	/* #abd9e9 4 */
			break;
		case 5:
			ret = 0x002c7bb6;	/* #2c7bb6 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLBU6:	/* rdylbu6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d73027;	/* #d73027 1 */
			break;
		case 2:
			ret = 0x00fc8d59;	/* #fc8d59 2 */
			break;
		case 3:
			ret = 0x00fee090;	/* #fee090 3 */
			break;
		case 4:
			ret = 0x00e0f3f8;	/* #e0f3f8 4 */
			break;
		case 5:
			ret = 0x0091bfdb;	/* #91bfdb 5 */
			break;
		case 6:
			ret = 0x004575b4;	/* #4575b4 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLBU7:	/* rdylbu7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d73027;	/* #d73027 1 */
			break;
		case 2:
			ret = 0x00fc8d59;	/* #fc8d59 2 */
			break;
		case 3:
			ret = 0x00fee090;	/* #fee090 3 */
			break;
		case 4:
			ret = 0x00ffffbf;	/* #ffffbf 4 */
			break;
		case 5:
			ret = 0x00e0f3f8;	/* #e0f3f8 5 */
			break;
		case 6:
			ret = 0x0091bfdb;	/* #91bfdb 6 */
			break;
		case 7:
			ret = 0x004575b4;	/* #4575b4 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLBU8:	/* rdylbu8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d73027;	/* #d73027 1 */
			break;
		case 2:
			ret = 0x00f46d43;	/* #f46d43 2 */
			break;
		case 3:
			ret = 0x00fdae61;	/* #fdae61 3 */
			break;
		case 4:
			ret = 0x00fee090;	/* #fee090 4 */
			break;
		case 5:
			ret = 0x00e0f3f8;	/* #e0f3f8 5 */
			break;
		case 6:
			ret = 0x00abd9e9;	/* #abd9e9 6 */
			break;
		case 7:
			ret = 0x0074add1;	/* #74add1 7 */
			break;
		case 8:
			ret = 0x004575b4;	/* #4575b4 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLBU9:	/* rdylbu9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d73027;	/* #d73027 1 */
			break;
		case 2:
			ret = 0x00f46d43;	/* #f46d43 2 */
			break;
		case 3:
			ret = 0x00fdae61;	/* #fdae61 3 */
			break;
		case 4:
			ret = 0x00fee090;	/* #fee090 4 */
			break;
		case 5:
			ret = 0x00ffffbf;	/* #ffffbf 5 */
			break;
		case 6:
			ret = 0x00e0f3f8;	/* #e0f3f8 6 */
			break;
		case 7:
			ret = 0x00abd9e9;	/* #abd9e9 7 */
			break;
		case 8:
			ret = 0x0074add1;	/* #74add1 8 */
			break;
		case 9:
			ret = 0x004575b4;	/* #4575b4 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLGN10:	/* rdylgn10 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a50026;	/* #a50026 1 */
			break;
		case 2:
			ret = 0x00d73027;	/* #d73027 2 */
			break;
		case 3:
			ret = 0x00f46d43;	/* #f46d43 3 */
			break;
		case 4:
			ret = 0x00fdae61;	/* #fdae61 4 */
			break;
		case 5:
			ret = 0x00fee08b;	/* #fee08b 5 */
			break;
		case 6:
			ret = 0x00d9ef8b;	/* #d9ef8b 6 */
			break;
		case 7:
			ret = 0x00a6d96a;	/* #a6d96a 7 */
			break;
		case 8:
			ret = 0x0066bd63;	/* #66bd63 8 */
			break;
		case 9:
			ret = 0x001a9850;	/* #1a9850 9 */
			break;
		case 10:
			ret = 0x00006837;	/* #006837 10 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLGN11:	/* rdylgn11 color scheme */
		switch (number) {
		case 1:
			ret = 0x00a50026;	/* #a50026 1 */
			break;
		case 2:
			ret = 0x00d73027;	/* #d73027 2 */
			break;
		case 3:
			ret = 0x00f46d43;	/* #f46d43 3 */
			break;
		case 4:
			ret = 0x00fdae61;	/* #fdae61 4 */
			break;
		case 5:
			ret = 0x00fee08b;	/* #fee08b 5 */
			break;
		case 6:
			ret = 0x00ffffbf;	/* #ffffbf 6 */
			break;
		case 7:
			ret = 0x00d9ef8b;	/* #d9ef8b 7 */
			break;
		case 8:
			ret = 0x00a6d96a;	/* #a6d96a 8 */
			break;
		case 9:
			ret = 0x0066bd63;	/* #66bd63 9 */
			break;
		case 10:
			ret = 0x001a9850;	/* #1a9850 10 */
			break;
		case 11:
			ret = 0x00006837;	/* #006837 11 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLGN3:	/* rdylgn3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fc8d59;	/* #fc8d59 1 */
			break;
		case 2:
			ret = 0x00ffffbf;	/* #ffffbf 2 */
			break;
		case 3:
			ret = 0x0091cf60;	/* #91cf60 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLGN4:	/* rdylgn4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d7191c;	/* #d7191c 1 */
			break;
		case 2:
			ret = 0x00fdae61;	/* #fdae61 2 */
			break;
		case 3:
			ret = 0x00a6d96a;	/* #a6d96a 3 */
			break;
		case 4:
			ret = 0x001a9641;	/* #1a9641 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLGN5:	/* rdylgn5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d7191c;	/* #d7191c 1 */
			break;
		case 2:
			ret = 0x00fdae61;	/* #fdae61 2 */
			break;
		case 3:
			ret = 0x00ffffbf;	/* #ffffbf 3 */
			break;
		case 4:
			ret = 0x00a6d96a;	/* #a6d96a 4 */
			break;
		case 5:
			ret = 0x001a9641;	/* #1a9641 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLGN6:	/* rdylgn6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d73027;	/* #d73027 1 */
			break;
		case 2:
			ret = 0x00fc8d59;	/* #fc8d59 2 */
			break;
		case 3:
			ret = 0x00fee08b;	/* #fee08b 3 */
			break;
		case 4:
			ret = 0x00d9ef8b;	/* #d9ef8b 4 */
			break;
		case 5:
			ret = 0x0091cf60;	/* #91cf60 5 */
			break;
		case 6:
			ret = 0x001a9850;	/* #1a9850 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLGN7:	/* rdylgn7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d73027;	/* #d73027 1 */
			break;
		case 2:
			ret = 0x00fc8d59;	/* #fc8d59 2 */
			break;
		case 3:
			ret = 0x00fee08b;	/* #fee08b 3 */
			break;
		case 4:
			ret = 0x00ffffbf;	/* #ffffbf 4 */
			break;
		case 5:
			ret = 0x00d9ef8b;	/* #d9ef8b 5 */
			break;
		case 6:
			ret = 0x0091cf60;	/* #91cf60 6 */
			break;
		case 7:
			ret = 0x001a9850;	/* #1a9850 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLGN8:	/* rdylgn8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d73027;	/* #d73027 1 */
			break;
		case 2:
			ret = 0x00f46d43;	/* #f46d43 2 */
			break;
		case 3:
			ret = 0x00fdae61;	/* #fdae61 3 */
			break;
		case 4:
			ret = 0x00fee08b;	/* #fee08b 4 */
			break;
		case 5:
			ret = 0x00d9ef8b;	/* #d9ef8b 5 */
			break;
		case 6:
			ret = 0x00a6d96a;	/* #a6d96a 6 */
			break;
		case 7:
			ret = 0x0066bd63;	/* #66bd63 7 */
			break;
		case 8:
			ret = 0x001a9850;	/* #1a9850 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_RDYLGN9:	/* rdylgn9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d73027;	/* #d73027 1 */
			break;
		case 2:
			ret = 0x00f46d43;	/* #f46d43 2 */
			break;
		case 3:
			ret = 0x00fdae61;	/* #fdae61 3 */
			break;
		case 4:
			ret = 0x00fee08b;	/* #fee08b 4 */
			break;
		case 5:
			ret = 0x00ffffbf;	/* #ffffbf 5 */
			break;
		case 6:
			ret = 0x00d9ef8b;	/* #d9ef8b 6 */
			break;
		case 7:
			ret = 0x00a6d96a;	/* #a6d96a 7 */
			break;
		case 8:
			ret = 0x0066bd63;	/* #66bd63 8 */
			break;
		case 9:
			ret = 0x001a9850;	/* #1a9850 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_REDS3:	/* reds3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fee0d2;	/* #fee0d2 1 */
			break;
		case 2:
			ret = 0x00fc9272;	/* #fc9272 2 */
			break;
		case 3:
			ret = 0x00de2d26;	/* #de2d26 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_REDS4:	/* reds4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fee5d9;	/* #fee5d9 1 */
			break;
		case 2:
			ret = 0x00fcae91;	/* #fcae91 2 */
			break;
		case 3:
			ret = 0x00fb6a4a;	/* #fb6a4a 3 */
			break;
		case 4:
			ret = 0x00cb181d;	/* #cb181d 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_REDS5:	/* reds5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fee5d9;	/* #fee5d9 1 */
			break;
		case 2:
			ret = 0x00fcae91;	/* #fcae91 2 */
			break;
		case 3:
			ret = 0x00fb6a4a;	/* #fb6a4a 3 */
			break;
		case 4:
			ret = 0x00de2d26;	/* #de2d26 4 */
			break;
		case 5:
			ret = 0x00a50f15;	/* #a50f15 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_REDS6:	/* reds6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fee5d9;	/* #fee5d9 1 */
			break;
		case 2:
			ret = 0x00fcbba1;	/* #fcbba1 2 */
			break;
		case 3:
			ret = 0x00fc9272;	/* #fc9272 3 */
			break;
		case 4:
			ret = 0x00fb6a4a;	/* #fb6a4a 4 */
			break;
		case 5:
			ret = 0x00de2d26;	/* #de2d26 5 */
			break;
		case 6:
			ret = 0x00a50f15;	/* #a50f15 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_REDS7:	/* reds7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fee5d9;	/* #fee5d9 1 */
			break;
		case 2:
			ret = 0x00fcbba1;	/* #fcbba1 2 */
			break;
		case 3:
			ret = 0x00fc9272;	/* #fc9272 3 */
			break;
		case 4:
			ret = 0x00fb6a4a;	/* #fb6a4a 4 */
			break;
		case 5:
			ret = 0x00ef3b2c;	/* #ef3b2c 5 */
			break;
		case 6:
			ret = 0x00cb181d;	/* #cb181d 6 */
			break;
		case 7:
			ret = 0x0099000d;	/* #99000d 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_REDS8:	/* reds8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fff5f0;	/* #fff5f0 1 */
			break;
		case 2:
			ret = 0x00fee0d2;	/* #fee0d2 2 */
			break;
		case 3:
			ret = 0x00fcbba1;	/* #fcbba1 3 */
			break;
		case 4:
			ret = 0x00fc9272;	/* #fc9272 4 */
			break;
		case 5:
			ret = 0x00fb6a4a;	/* #fb6a4a 5 */
			break;
		case 6:
			ret = 0x00ef3b2c;	/* #ef3b2c 6 */
			break;
		case 7:
			ret = 0x00cb181d;	/* #cb181d 7 */
			break;
		case 8:
			ret = 0x0099000d;	/* #99000d 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_REDS9:	/* reds9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fff5f0;	/* #fff5f0 1 */
			break;
		case 2:
			ret = 0x00fee0d2;	/* #fee0d2 2 */
			break;
		case 3:
			ret = 0x00fcbba1;	/* #fcbba1 3 */
			break;
		case 4:
			ret = 0x00fc9272;	/* #fc9272 4 */
			break;
		case 5:
			ret = 0x00fb6a4a;	/* #fb6a4a 5 */
			break;
		case 6:
			ret = 0x00ef3b2c;	/* #ef3b2c 6 */
			break;
		case 7:
			ret = 0x00cb181d;	/* #cb181d 7 */
			break;
		case 8:
			ret = 0x00a50f15;	/* #a50f15 8 */
			break;
		case 9:
			ret = 0x0067000d;	/* #67000d 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET13:	/* set13 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e41a1c;	/* #e41a1c 1 */
			break;
		case 2:
			ret = 0x00377eb8;	/* #377eb8 2 */
			break;
		case 3:
			ret = 0x004daf4a;	/* #4daf4a 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET14:	/* set14 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e41a1c;	/* #e41a1c 1 */
			break;
		case 2:
			ret = 0x00377eb8;	/* #377eb8 2 */
			break;
		case 3:
			ret = 0x004daf4a;	/* #4daf4a 3 */
			break;
		case 4:
			ret = 0x00984ea3;	/* #984ea3 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET15:	/* set15 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e41a1c;	/* #e41a1c 1 */
			break;
		case 2:
			ret = 0x00377eb8;	/* #377eb8 2 */
			break;
		case 3:
			ret = 0x004daf4a;	/* #4daf4a 3 */
			break;
		case 4:
			ret = 0x00984ea3;	/* #984ea3 4 */
			break;
		case 5:
			ret = 0x00ff7f00;	/* #ff7f00 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET16:	/* set16 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e41a1c;	/* #e41a1c 1 */
			break;
		case 2:
			ret = 0x00377eb8;	/* #377eb8 2 */
			break;
		case 3:
			ret = 0x004daf4a;	/* #4daf4a 3 */
			break;
		case 4:
			ret = 0x00984ea3;	/* #984ea3 4 */
			break;
		case 5:
			ret = 0x00ff7f00;	/* #ff7f00 5 */
			break;
		case 6:
			ret = 0x00ffff33;	/* #ffff33 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET17:	/* set17 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e41a1c;	/* #e41a1c 1 */
			break;
		case 2:
			ret = 0x00377eb8;	/* #377eb8 2 */
			break;
		case 3:
			ret = 0x004daf4a;	/* #4daf4a 3 */
			break;
		case 4:
			ret = 0x00984ea3;	/* #984ea3 4 */
			break;
		case 5:
			ret = 0x00ff7f00;	/* #ff7f00 5 */
			break;
		case 6:
			ret = 0x00ffff33;	/* #ffff33 6 */
			break;
		case 7:
			ret = 0x00a65628;	/* #a65628 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET18:	/* set18 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e41a1c;	/* #e41a1c 1 */
			break;
		case 2:
			ret = 0x00377eb8;	/* #377eb8 2 */
			break;
		case 3:
			ret = 0x004daf4a;	/* #4daf4a 3 */
			break;
		case 4:
			ret = 0x00984ea3;	/* #984ea3 4 */
			break;
		case 5:
			ret = 0x00ff7f00;	/* #ff7f00 5 */
			break;
		case 6:
			ret = 0x00ffff33;	/* #ffff33 6 */
			break;
		case 7:
			ret = 0x00a65628;	/* #a65628 7 */
			break;
		case 8:
			ret = 0x00f781bf;	/* #f781bf 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET19:	/* set19 color scheme */
		switch (number) {
		case 1:
			ret = 0x00e41a1c;	/* #e41a1c 1 */
			break;
		case 2:
			ret = 0x00377eb8;	/* #377eb8 2 */
			break;
		case 3:
			ret = 0x004daf4a;	/* #4daf4a 3 */
			break;
		case 4:
			ret = 0x00984ea3;	/* #984ea3 4 */
			break;
		case 5:
			ret = 0x00ff7f00;	/* #ff7f00 5 */
			break;
		case 6:
			ret = 0x00ffff33;	/* #ffff33 6 */
			break;
		case 7:
			ret = 0x00a65628;	/* #a65628 7 */
			break;
		case 8:
			ret = 0x00f781bf;	/* #f781bf 8 */
			break;
		case 9:
			ret = 0x00999999;	/* #999999 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET23:	/* set23 color scheme */
		switch (number) {
		case 1:
			ret = 0x0066c2a5;	/* #66c2a5 1 */
			break;
		case 2:
			ret = 0x00fc8d62;	/* #fc8d62 2 */
			break;
		case 3:
			ret = 0x008da0cb;	/* #8da0cb 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET24:	/* set24 color scheme */
		switch (number) {
		case 1:
			ret = 0x0066c2a5;	/* #66c2a5 1 */
			break;
		case 2:
			ret = 0x00fc8d62;	/* #fc8d62 2 */
			break;
		case 3:
			ret = 0x008da0cb;	/* #8da0cb 3 */
			break;
		case 4:
			ret = 0x00e78ac3;	/* #e78ac3 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET25:	/* set25 color scheme */
		switch (number) {
		case 1:
			ret = 0x0066c2a5;	/* #66c2a5 1 */
			break;
		case 2:
			ret = 0x00fc8d62;	/* #fc8d62 2 */
			break;
		case 3:
			ret = 0x008da0cb;	/* #8da0cb 3 */
			break;
		case 4:
			ret = 0x00e78ac3;	/* #e78ac3 4 */
			break;
		case 5:
			ret = 0x00a6d854;	/* #a6d854 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET26:	/* set26 color scheme */
		switch (number) {
		case 1:
			ret = 0x0066c2a5;	/* #66c2a5 1 */
			break;
		case 2:
			ret = 0x00fc8d62;	/* #fc8d62 2 */
			break;
		case 3:
			ret = 0x008da0cb;	/* #8da0cb 3 */
			break;
		case 4:
			ret = 0x00e78ac3;	/* #e78ac3 4 */
			break;
		case 5:
			ret = 0x00a6d854;	/* #a6d854 5 */
			break;
		case 6:
			ret = 0x00ffd92f;	/* #ffd92f 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET27:	/* set27 color scheme */
		switch (number) {
		case 1:
			ret = 0x0066c2a5;	/* #66c2a5 1 */
			break;
		case 2:
			ret = 0x00fc8d62;	/* #fc8d62 2 */
			break;
		case 3:
			ret = 0x008da0cb;	/* #8da0cb 3 */
			break;
		case 4:
			ret = 0x00e78ac3;	/* #e78ac3 4 */
			break;
		case 5:
			ret = 0x00a6d854;	/* #a6d854 5 */
			break;
		case 6:
			ret = 0x00ffd92f;	/* #ffd92f 6 */
			break;
		case 7:
			ret = 0x00e5c494;	/* #e5c494 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET28:	/* set28 color scheme */
		switch (number) {
		case 1:
			ret = 0x0066c2a5;	/* #66c2a5 1 */
			break;
		case 2:
			ret = 0x00fc8d62;	/* #fc8d62 2 */
			break;
		case 3:
			ret = 0x008da0cb;	/* #8da0cb 3 */
			break;
		case 4:
			ret = 0x00e78ac3;	/* #e78ac3 4 */
			break;
		case 5:
			ret = 0x00a6d854;	/* #a6d854 5 */
			break;
		case 6:
			ret = 0x00ffd92f;	/* #ffd92f 6 */
			break;
		case 7:
			ret = 0x00e5c494;	/* #e5c494 7 */
			break;
		case 8:
			ret = 0x00b3b3b3;	/* #b3b3b3 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET310:	/* set310 color scheme */
		switch (number) {
		case 1:
			ret = 0x008dd3c7;	/* #8dd3c7 1 */
			break;
		case 2:
			ret = 0x00ffffb3;	/* #ffffb3 2 */
			break;
		case 3:
			ret = 0x00bebada;	/* #bebada 3 */
			break;
		case 4:
			ret = 0x00fb8072;	/* #fb8072 4 */
			break;
		case 5:
			ret = 0x0080b1d3;	/* #80b1d3 5 */
			break;
		case 6:
			ret = 0x00fdb462;	/* #fdb462 6 */
			break;
		case 7:
			ret = 0x00b3de69;	/* #b3de69 7 */
			break;
		case 8:
			ret = 0x00fccde5;	/* #fccde5 8 */
			break;
		case 9:
			ret = 0x00d9d9d9;	/* #d9d9d9 9 */
			break;
		case 10:
			ret = 0x00bc80bd;	/* #bc80bd 10 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET311:	/* set311 color scheme */
		switch (number) {
		case 1:
			ret = 0x008dd3c7;	/* #8dd3c7 1 */
			break;
		case 2:
			ret = 0x00ffffb3;	/* #ffffb3 2 */
			break;
		case 3:
			ret = 0x00bebada;	/* #bebada 3 */
			break;
		case 4:
			ret = 0x00fb8072;	/* #fb8072 4 */
			break;
		case 5:
			ret = 0x0080b1d3;	/* #80b1d3 5 */
			break;
		case 6:
			ret = 0x00fdb462;	/* #fdb462 6 */
			break;
		case 7:
			ret = 0x00b3de69;	/* #b3de69 7 */
			break;
		case 8:
			ret = 0x00fccde5;	/* #fccde5 8 */
			break;
		case 9:
			ret = 0x00d9d9d9;	/* #d9d9d9 9 */
			break;
		case 10:
			ret = 0x00bc80bd;	/* #bc80bd 10 */
			break;
		case 11:
			ret = 0x00ccebc5;	/* #ccebc5 11 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET312:	/* set312 color scheme */
		switch (number) {
		case 1:
			ret = 0x008dd3c7;	/* #8dd3c7 1 */
			break;
		case 2:
			ret = 0x00ffffb3;	/* #ffffb3 2 */
			break;
		case 3:
			ret = 0x00bebada;	/* #bebada 3 */
			break;
		case 4:
			ret = 0x00fb8072;	/* #fb8072 4 */
			break;
		case 5:
			ret = 0x0080b1d3;	/* #80b1d3 5 */
			break;
		case 6:
			ret = 0x00fdb462;	/* #fdb462 6 */
			break;
		case 7:
			ret = 0x00b3de69;	/* #b3de69 7 */
			break;
		case 8:
			ret = 0x00fccde5;	/* #fccde5 8 */
			break;
		case 9:
			ret = 0x00d9d9d9;	/* #d9d9d9 9 */
			break;
		case 10:
			ret = 0x00bc80bd;	/* #bc80bd 10 */
			break;
		case 11:
			ret = 0x00ccebc5;	/* #ccebc5 11 */
			break;
		case 12:
			ret = 0x00ffed6f;	/* #ffed6f 12 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET33:	/* set33 color scheme */
		switch (number) {
		case 1:
			ret = 0x008dd3c7;	/* #8dd3c7 1 */
			break;
		case 2:
			ret = 0x00ffffb3;	/* #ffffb3 2 */
			break;
		case 3:
			ret = 0x00bebada;	/* #bebada 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET34:	/* set34 color scheme */
		switch (number) {
		case 1:
			ret = 0x008dd3c7;	/* #8dd3c7 1 */
			break;
		case 2:
			ret = 0x00ffffb3;	/* #ffffb3 2 */
			break;
		case 3:
			ret = 0x00bebada;	/* #bebada 3 */
			break;
		case 4:
			ret = 0x00fb8072;	/* #fb8072 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET35:	/* set35 color scheme */
		switch (number) {
		case 1:
			ret = 0x008dd3c7;	/* #8dd3c7 1 */
			break;
		case 2:
			ret = 0x00ffffb3;	/* #ffffb3 2 */
			break;
		case 3:
			ret = 0x00bebada;	/* #bebada 3 */
			break;
		case 4:
			ret = 0x00fb8072;	/* #fb8072 4 */
			break;
		case 5:
			ret = 0x0080b1d3;	/* #80b1d3 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET36:	/* set36 color scheme */
		switch (number) {
		case 1:
			ret = 0x008dd3c7;	/* #8dd3c7 1 */
			break;
		case 2:
			ret = 0x00ffffb3;	/* #ffffb3 2 */
			break;
		case 3:
			ret = 0x00bebada;	/* #bebada 3 */
			break;
		case 4:
			ret = 0x00fb8072;	/* #fb8072 4 */
			break;
		case 5:
			ret = 0x0080b1d3;	/* #80b1d3 5 */
			break;
		case 6:
			ret = 0x00fdb462;	/* #fdb462 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET37:	/* set37 color scheme */
		switch (number) {
		case 1:
			ret = 0x008dd3c7;	/* #8dd3c7 1 */
			break;
		case 2:
			ret = 0x00ffffb3;	/* #ffffb3 2 */
			break;
		case 3:
			ret = 0x00bebada;	/* #bebada 3 */
			break;
		case 4:
			ret = 0x00fb8072;	/* #fb8072 4 */
			break;
		case 5:
			ret = 0x0080b1d3;	/* #80b1d3 5 */
			break;
		case 6:
			ret = 0x00fdb462;	/* #fdb462 6 */
			break;
		case 7:
			ret = 0x00b3de69;	/* #b3de69 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET38:	/* set38 color scheme */
		switch (number) {
		case 1:
			ret = 0x008dd3c7;	/* #8dd3c7 1 */
			break;
		case 2:
			ret = 0x00ffffb3;	/* #ffffb3 2 */
			break;
		case 3:
			ret = 0x00bebada;	/* #bebada 3 */
			break;
		case 4:
			ret = 0x00fb8072;	/* #fb8072 4 */
			break;
		case 5:
			ret = 0x0080b1d3;	/* #80b1d3 5 */
			break;
		case 6:
			ret = 0x00fdb462;	/* #fdb462 6 */
			break;
		case 7:
			ret = 0x00b3de69;	/* #b3de69 7 */
			break;
		case 8:
			ret = 0x00fccde5;	/* #fccde5 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SET39:	/* set39 color scheme */
		switch (number) {
		case 1:
			ret = 0x008dd3c7;	/* #8dd3c7 1 */
			break;
		case 2:
			ret = 0x00ffffb3;	/* #ffffb3 2 */
			break;
		case 3:
			ret = 0x00bebada;	/* #bebada 3 */
			break;
		case 4:
			ret = 0x00fb8072;	/* #fb8072 4 */
			break;
		case 5:
			ret = 0x0080b1d3;	/* #80b1d3 5 */
			break;
		case 6:
			ret = 0x00fdb462;	/* #fdb462 6 */
			break;
		case 7:
			ret = 0x00b3de69;	/* #b3de69 7 */
			break;
		case 8:
			ret = 0x00fccde5;	/* #fccde5 8 */
			break;
		case 9:
			ret = 0x00d9d9d9;	/* #d9d9d9 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SPECTRAL10:	/* spectral10 color scheme */
		switch (number) {
		case 1:
			ret = 0x009e0142;	/* #9e0142 1 */
			break;
		case 2:
			ret = 0x00d53e4f;	/* #d53e4f 2 */
			break;
		case 3:
			ret = 0x00f46d43;	/* #f46d43 3 */
			break;
		case 4:
			ret = 0x00fdae61;	/* #fdae61 4 */
			break;
		case 5:
			ret = 0x00fee08b;	/* #fee08b 5 */
			break;
		case 6:
			ret = 0x00e6f598;	/* #e6f598 6 */
			break;
		case 7:
			ret = 0x00abdda4;	/* #abdda4 7 */
			break;
		case 8:
			ret = 0x0066c2a5;	/* #66c2a5 8 */
			break;
		case 9:
			ret = 0x003288bd;	/* #3288bd 9 */
			break;
		case 10:
			ret = 0x005e4fa2;	/* #5e4fa2 10 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SPECTRAL11:	/* spectral11 color scheme */
		switch (number) {
		case 1:
			ret = 0x009e0142;	/* #9e0142 1 */
			break;
		case 2:
			ret = 0x00d53e4f;	/* #d53e4f 2 */
			break;
		case 3:
			ret = 0x00f46d43;	/* #f46d43 3 */
			break;
		case 4:
			ret = 0x00fdae61;	/* #fdae61 4 */
			break;
		case 5:
			ret = 0x00fee08b;	/* #fee08b 5 */
			break;
		case 6:
			ret = 0x00ffffbf;	/* #ffffbf 6 */
			break;
		case 7:
			ret = 0x00e6f598;	/* #e6f598 7 */
			break;
		case 8:
			ret = 0x00abdda4;	/* #abdda4 8 */
			break;
		case 9:
			ret = 0x0066c2a5;	/* #66c2a5 9 */
			break;
		case 10:
			ret = 0x003288bd;	/* #3288bd 10 */
			break;
		case 11:
			ret = 0x005e4fa2;	/* #5e4fa2 11 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SPECTRAL3:	/* spectral3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fc8d59;	/* #fc8d59 1 */
			break;
		case 2:
			ret = 0x00ffffbf;	/* #ffffbf 2 */
			break;
		case 3:
			ret = 0x0099d594;	/* #99d594 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SPECTRAL4:	/* spectral4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d7191c;	/* #d7191c 1 */
			break;
		case 2:
			ret = 0x00fdae61;	/* #fdae61 2 */
			break;
		case 3:
			ret = 0x00abdda4;	/* #abdda4 3 */
			break;
		case 4:
			ret = 0x002b83ba;	/* #2b83ba 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SPECTRAL5:	/* spectral5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d7191c;	/* #d7191c 1 */
			break;
		case 2:
			ret = 0x00fdae61;	/* #fdae61 2 */
			break;
		case 3:
			ret = 0x00ffffbf;	/* #ffffbf 3 */
			break;
		case 4:
			ret = 0x00abdda4;	/* #abdda4 4 */
			break;
		case 5:
			ret = 0x002b83ba;	/* #2b83ba 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SPECTRAL6:	/* spectral6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d53e4f;	/* #d53e4f 1 */
			break;
		case 2:
			ret = 0x00fc8d59;	/* #fc8d59 2 */
			break;
		case 3:
			ret = 0x00fee08b;	/* #fee08b 3 */
			break;
		case 4:
			ret = 0x00e6f598;	/* #e6f598 4 */
			break;
		case 5:
			ret = 0x0099d594;	/* #99d594 5 */
			break;
		case 6:
			ret = 0x003288bd;	/* #3288bd 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SPECTRAL7:	/* spectral7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d53e4f;	/* #d53e4f 1 */
			break;
		case 2:
			ret = 0x00fc8d59;	/* #fc8d59 2 */
			break;
		case 3:
			ret = 0x00fee08b;	/* #fee08b 3 */
			break;
		case 4:
			ret = 0x00ffffbf;	/* #ffffbf 4 */
			break;
		case 5:
			ret = 0x00e6f598;	/* #e6f598 5 */
			break;
		case 6:
			ret = 0x0099d594;	/* #99d594 6 */
			break;
		case 7:
			ret = 0x003288bd;	/* #3288bd 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SPECTRAL8:	/* spectral8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d53e4f;	/* #d53e4f 1 */
			break;
		case 2:
			ret = 0x00f46d43;	/* #f46d43 2 */
			break;
		case 3:
			ret = 0x00fdae61;	/* #fdae61 3 */
			break;
		case 4:
			ret = 0x00fee08b;	/* #fee08b 4 */
			break;
		case 5:
			ret = 0x00e6f598;	/* #e6f598 5 */
			break;
		case 6:
			ret = 0x00abdda4;	/* #abdda4 6 */
			break;
		case 7:
			ret = 0x0066c2a5;	/* #66c2a5 7 */
			break;
		case 8:
			ret = 0x003288bd;	/* #3288bd 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_SPECTRAL9:	/* spectral9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00d53e4f;	/* #d53e4f 1 */
			break;
		case 2:
			ret = 0x00f46d43;	/* #f46d43 2 */
			break;
		case 3:
			ret = 0x00fdae61;	/* #fdae61 3 */
			break;
		case 4:
			ret = 0x00fee08b;	/* #fee08b 4 */
			break;
		case 5:
			ret = 0x00ffffbf;	/* #ffffbf 5 */
			break;
		case 6:
			ret = 0x00e6f598;	/* #e6f598 6 */
			break;
		case 7:
			ret = 0x00abdda4;	/* #abdda4 7 */
			break;
		case 8:
			ret = 0x0066c2a5;	/* #66c2a5 8 */
			break;
		case 9:
			ret = 0x003288bd;	/* #3288bd 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGN3:	/* ylgn3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00f7fcb9;	/* #f7fcb9 1 */
			break;
		case 2:
			ret = 0x00addd8e;	/* #addd8e 2 */
			break;
		case 3:
			ret = 0x0031a354;	/* #31a354 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGN4:	/* ylgn4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffcc;	/* #ffffcc 1 */
			break;
		case 2:
			ret = 0x00c2e699;	/* #c2e699 2 */
			break;
		case 3:
			ret = 0x0078c679;	/* #78c679 3 */
			break;
		case 4:
			ret = 0x00238443;	/* #238443 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGN5:	/* ylgn5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffcc;	/* #ffffcc 1 */
			break;
		case 2:
			ret = 0x00c2e699;	/* #c2e699 2 */
			break;
		case 3:
			ret = 0x0078c679;	/* #78c679 3 */
			break;
		case 4:
			ret = 0x0031a354;	/* #31a354 4 */
			break;
		case 5:
			ret = 0x00006837;	/* #006837 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGN6:	/* ylgn6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffcc;	/* #ffffcc 1 */
			break;
		case 2:
			ret = 0x00d9f0a3;	/* #d9f0a3 2 */
			break;
		case 3:
			ret = 0x00addd8e;	/* #addd8e 3 */
			break;
		case 4:
			ret = 0x0078c679;	/* #78c679 4 */
			break;
		case 5:
			ret = 0x0031a354;	/* #31a354 5 */
			break;
		case 6:
			ret = 0x00006837;	/* #006837 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGN7:	/* ylgn7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffcc;	/* #ffffcc 1 */
			break;
		case 2:
			ret = 0x00d9f0a3;	/* #d9f0a3 2 */
			break;
		case 3:
			ret = 0x00addd8e;	/* #addd8e 3 */
			break;
		case 4:
			ret = 0x0078c679;	/* #78c679 4 */
			break;
		case 5:
			ret = 0x0041ab5d;	/* #41ab5d 5 */
			break;
		case 6:
			ret = 0x00238443;	/* #238443 6 */
			break;
		case 7:
			ret = 0x00005a32;	/* #005a32 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGN8:	/* ylgn8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffe5;	/* #ffffe5 1 */
			break;
		case 2:
			ret = 0x00f7fcb9;	/* #f7fcb9 2 */
			break;
		case 3:
			ret = 0x00d9f0a3;	/* #d9f0a3 3 */
			break;
		case 4:
			ret = 0x00addd8e;	/* #addd8e 4 */
			break;
		case 5:
			ret = 0x0078c679;	/* #78c679 5 */
			break;
		case 6:
			ret = 0x0041ab5d;	/* #41ab5d 6 */
			break;
		case 7:
			ret = 0x00238443;	/* #238443 7 */
			break;
		case 8:
			ret = 0x00005a32;	/* #005a32 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGN9:	/* ylgn9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffe5;	/* #ffffe5 1 */
			break;
		case 2:
			ret = 0x00f7fcb9;	/* #f7fcb9 2 */
			break;
		case 3:
			ret = 0x00d9f0a3;	/* #d9f0a3 3 */
			break;
		case 4:
			ret = 0x00addd8e;	/* #addd8e 4 */
			break;
		case 5:
			ret = 0x0078c679;	/* #78c679 5 */
			break;
		case 6:
			ret = 0x0041ab5d;	/* #41ab5d 6 */
			break;
		case 7:
			ret = 0x00238443;	/* #238443 7 */
			break;
		case 8:
			ret = 0x00006837;	/* #006837 8 */
			break;
		case 9:
			ret = 0x00004529;	/* #004529 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGNBU3:	/* ylgnbu3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00edf8b1;	/* #edf8b1 1 */
			break;
		case 2:
			ret = 0x007fcdbb;	/* #7fcdbb 2 */
			break;
		case 3:
			ret = 0x002c7fb8;	/* #2c7fb8 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGNBU4:	/* ylgnbu4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffcc;	/* #ffffcc 1 */
			break;
		case 2:
			ret = 0x00a1dab4;	/* #a1dab4 2 */
			break;
		case 3:
			ret = 0x0041b6c4;	/* #41b6c4 3 */
			break;
		case 4:
			ret = 0x00225ea8;	/* #225ea8 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGNBU5:	/* ylgnbu5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffcc;	/* #ffffcc 1 */
			break;
		case 2:
			ret = 0x00a1dab4;	/* #a1dab4 2 */
			break;
		case 3:
			ret = 0x0041b6c4;	/* #41b6c4 3 */
			break;
		case 4:
			ret = 0x002c7fb8;	/* #2c7fb8 4 */
			break;
		case 5:
			ret = 0x00253494;	/* #253494 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGNBU6:	/* ylgnbu6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffcc;	/* #ffffcc 1 */
			break;
		case 2:
			ret = 0x00c7e9b4;	/* #c7e9b4 2 */
			break;
		case 3:
			ret = 0x007fcdbb;	/* #7fcdbb 3 */
			break;
		case 4:
			ret = 0x0041b6c4;	/* #41b6c4 4 */
			break;
		case 5:
			ret = 0x002c7fb8;	/* #2c7fb8 5 */
			break;
		case 6:
			ret = 0x00253494;	/* #253494 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGNBU7:	/* ylgnbu7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffcc;	/* #ffffcc 1 */
			break;
		case 2:
			ret = 0x00c7e9b4;	/* #c7e9b4 2 */
			break;
		case 3:
			ret = 0x007fcdbb;	/* #7fcdbb 3 */
			break;
		case 4:
			ret = 0x0041b6c4;	/* #41b6c4 4 */
			break;
		case 5:
			ret = 0x001d91c0;	/* #1d91c0 5 */
			break;
		case 6:
			ret = 0x00225ea8;	/* #225ea8 6 */
			break;
		case 7:
			ret = 0x000c2c84;	/* #0c2c84 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGNBU8:	/* ylgnbu8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffd9;	/* #ffffd9 1 */
			break;
		case 2:
			ret = 0x00edf8b1;	/* #edf8b1 2 */
			break;
		case 3:
			ret = 0x00c7e9b4;	/* #c7e9b4 3 */
			break;
		case 4:
			ret = 0x007fcdbb;	/* #7fcdbb 4 */
			break;
		case 5:
			ret = 0x0041b6c4;	/* #41b6c4 5 */
			break;
		case 6:
			ret = 0x001d91c0;	/* #1d91c0 6 */
			break;
		case 7:
			ret = 0x00225ea8;	/* #225ea8 7 */
			break;
		case 8:
			ret = 0x000c2c84;	/* #0c2c84 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLGNBU9:	/* ylgnbu9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffd9;	/* #ffffd9 1 */
			break;
		case 2:
			ret = 0x00edf8b1;	/* #edf8b1 2 */
			break;
		case 3:
			ret = 0x00c7e9b4;	/* #c7e9b4 3 */
			break;
		case 4:
			ret = 0x007fcdbb;	/* #7fcdbb 4 */
			break;
		case 5:
			ret = 0x0041b6c4;	/* #41b6c4 5 */
			break;
		case 6:
			ret = 0x001d91c0;	/* #1d91c0 6 */
			break;
		case 7:
			ret = 0x00225ea8;	/* #225ea8 7 */
			break;
		case 8:
			ret = 0x00253494;	/* #253494 8 */
			break;
		case 9:
			ret = 0x00081d58;	/* #081d58 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORBR3:	/* ylorbr3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00fff7bc;	/* #fff7bc 1 */
			break;
		case 2:
			ret = 0x00fec44f;	/* #fec44f 2 */
			break;
		case 3:
			ret = 0x00d95f0e;	/* #d95f0e 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORBR4:	/* ylorbr4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffd4;	/* #ffffd4 1 */
			break;
		case 2:
			ret = 0x00fed98e;	/* #fed98e 2 */
			break;
		case 3:
			ret = 0x00fe9929;	/* #fe9929 3 */
			break;
		case 4:
			ret = 0x00cc4c02;	/* #cc4c02 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORBR5:	/* ylorbr5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffd4;	/* #ffffd4 1 */
			break;
		case 2:
			ret = 0x00fed98e;	/* #fed98e 2 */
			break;
		case 3:
			ret = 0x00fe9929;	/* #fe9929 3 */
			break;
		case 4:
			ret = 0x00d95f0e;	/* #d95f0e 4 */
			break;
		case 5:
			ret = 0x00993404;	/* #993404 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORBR6:	/* ylorbr6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffd4;	/* #ffffd4 1 */
			break;
		case 2:
			ret = 0x00fee391;	/* #fee391 2 */
			break;
		case 3:
			ret = 0x00fec44f;	/* #fec44f 3 */
			break;
		case 4:
			ret = 0x00fe9929;	/* #fe9929 4 */
			break;
		case 5:
			ret = 0x00d95f0e;	/* #d95f0e 5 */
			break;
		case 6:
			ret = 0x00993404;	/* #993404 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORBR7:	/* ylorbr7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffd4;	/* #ffffd4 1 */
			break;
		case 2:
			ret = 0x00fee391;	/* #fee391 2 */
			break;
		case 3:
			ret = 0x00fec44f;	/* #fec44f 3 */
			break;
		case 4:
			ret = 0x00fe9929;	/* #fe9929 4 */
			break;
		case 5:
			ret = 0x00ec7014;	/* #ec7014 5 */
			break;
		case 6:
			ret = 0x00cc4c02;	/* #cc4c02 6 */
			break;
		case 7:
			ret = 0x008c2d04;	/* #8c2d04 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORBR8:	/* ylorbr8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffe5;	/* #ffffe5 1 */
			break;
		case 2:
			ret = 0x00fff7bc;	/* #fff7bc 2 */
			break;
		case 3:
			ret = 0x00fee391;	/* #fee391 3 */
			break;
		case 4:
			ret = 0x00fec44f;	/* #fec44f 4 */
			break;
		case 5:
			ret = 0x00fe9929;	/* #fe9929 5 */
			break;
		case 6:
			ret = 0x00ec7014;	/* #ec7014 6 */
			break;
		case 7:
			ret = 0x00cc4c02;	/* #cc4c02 7 */
			break;
		case 8:
			ret = 0x008c2d04;	/* #8c2d04 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORBR9:	/* ylorbr9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffe5;	/* #ffffe5 1 */
			break;
		case 2:
			ret = 0x00fff7bc;	/* #fff7bc 2 */
			break;
		case 3:
			ret = 0x00fee391;	/* #fee391 3 */
			break;
		case 4:
			ret = 0x00fec44f;	/* #fec44f 4 */
			break;
		case 5:
			ret = 0x00fe9929;	/* #fe9929 5 */
			break;
		case 6:
			ret = 0x00ec7014;	/* #ec7014 6 */
			break;
		case 7:
			ret = 0x00cc4c02;	/* #cc4c02 7 */
			break;
		case 8:
			ret = 0x00993404;	/* #993404 8 */
			break;
		case 9:
			ret = 0x00662506;	/* #662506 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORRD3:	/* ylorrd3 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffeda0;	/* #ffeda0 1 */
			break;
		case 2:
			ret = 0x00feb24c;	/* #feb24c 2 */
			break;
		case 3:
			ret = 0x00f03b20;	/* #f03b20 3 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORRD4:	/* ylorrd4 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffb2;	/* #ffffb2 1 */
			break;
		case 2:
			ret = 0x00fecc5c;	/* #fecc5c 2 */
			break;
		case 3:
			ret = 0x00fd8d3c;	/* #fd8d3c 3 */
			break;
		case 4:
			ret = 0x00e31a1c;	/* #e31a1c 4 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORRD5:	/* ylorrd5 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffb2;	/* #ffffb2 1 */
			break;
		case 2:
			ret = 0x00fecc5c;	/* #fecc5c 2 */
			break;
		case 3:
			ret = 0x00fd8d3c;	/* #fd8d3c 3 */
			break;
		case 4:
			ret = 0x00f03b20;	/* #f03b20 4 */
			break;
		case 5:
			ret = 0x00bd0026;	/* #bd0026 5 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORRD6:	/* ylorrd6 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffb2;	/* #ffffb2 1 */
			break;
		case 2:
			ret = 0x00fed976;	/* #fed976 2 */
			break;
		case 3:
			ret = 0x00feb24c;	/* #feb24c 3 */
			break;
		case 4:
			ret = 0x00fd8d3c;	/* #fd8d3c 4 */
			break;
		case 5:
			ret = 0x00f03b20;	/* #f03b20 5 */
			break;
		case 6:
			ret = 0x00bd0026;	/* #bd0026 6 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORRD7:	/* ylorrd7 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffb2;	/* #ffffb2 1 */
			break;
		case 2:
			ret = 0x00fed976;	/* #fed976 2 */
			break;
		case 3:
			ret = 0x00feb24c;	/* #feb24c 3 */
			break;
		case 4:
			ret = 0x00fd8d3c;	/* #fd8d3c 4 */
			break;
		case 5:
			ret = 0x00fc4e2a;	/* #fc4e2a 5 */
			break;
		case 6:
			ret = 0x00e31a1c;	/* #e31a1c 6 */
			break;
		case 7:
			ret = 0x00b10026;	/* #b10026 7 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORRD8:	/* ylorrd8 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffcc;	/* #ffffcc 1 */
			break;
		case 2:
			ret = 0x00ffeda0;	/* #ffeda0 2 */
			break;
		case 3:
			ret = 0x00fed976;	/* #fed976 3 */
			break;
		case 4:
			ret = 0x00feb24c;	/* #feb24c 4 */
			break;
		case 5:
			ret = 0x00fd8d3c;	/* #fd8d3c 5 */
			break;
		case 6:
			ret = 0x00fc4e2a;	/* #fc4e2a 6 */
			break;
		case 7:
			ret = 0x00e31a1c;	/* #e31a1c 7 */
			break;
		case 8:
			ret = 0x00b10026;	/* #b10026 8 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
	case COLOR_NS_YLORRD9:	/* ylorrd9 color scheme */
		switch (number) {
		case 1:
			ret = 0x00ffffcc;	/* #ffffcc 1 */
			break;
		case 2:
			ret = 0x00ffeda0;	/* #ffeda0 2 */
			break;
		case 3:
			ret = 0x00fed976;	/* #fed976 3 */
			break;
		case 4:
			ret = 0x00feb24c;	/* #feb24c 4 */
			break;
		case 5:
			ret = 0x00fd8d3c;	/* #fd8d3c 5 */
			break;
		case 6:
			ret = 0x00fc4e2a;	/* #fc4e2a 6 */
			break;
		case 7:
			ret = 0x00e31a1c;	/* #e31a1c 7 */
			break;
		case 8:
			ret = 0x00bd0026;	/* #bd0026 8 */
			break;
		case 9:
			ret = 0x00800026;	/* #800026 9 */
			break;
		default:
			ret = (-1);
			break;
		}
		break;
		/* unknown scheme, then unknown color */
	default:
		ret = (-1);
		break;
	}
	return (ret);
}

/* wipe color database */
void dp_colorcode_clear(void)
{

	/* color names database */
	gucolor = splay_tree_delete(gucolor);

	return;
}

/* Comparison function for a splay tree in which the keys are strings.
   K1 and K2 have the dynamic type "const char *".  Returns <0, 0, or
   >0 to indicate whether K1 is less than, equal to, or greater than
   K2, respectively.
   similar issues here when as compare pointers and c portable src.
*/

static int splay_tree_compare_case_strings(splay_tree_key k1, splay_tree_key k2)
{
	const char *s1 = (const char *)k1;
	const char *s2 = (const char *)k2;
	int ret = 0;

	if ((k1 == (splay_tree_key) 0) && (k2 == (splay_tree_key) 0)) {
		return (0);
	}

	if (s1 == (const char *)0) {
		/* to avoid crashes only */
		return (0);
	}

	if (s2 == (const char *)0) {
		/* to avoid crashes only */
		return (0);
	}

	/* check if same pointer. possible not portable c. */
	if (s1 == s2) {
		return (0);
	}

	ret = strcasecmp(s1, s2);

	return ((int)ret);
}

/* create color database */
static void color_init(void)
{

	/* indexed on (char *) */
	gucolor = splay_tree_new(splay_tree_compare_case_strings,	/* splay_tree_compare_fn */
				 ucolor_splay_tree_delete_key_fn,	/* splay_tree_delete_key_fn */
				 ucolor_splay_tree_delete_value_fn	/* splay_tree_delete_value_fn */
	    );
	/* add color data indexed by name */
	colordata(0);
	/* drawing background color white */
	dp_bgcr = 0xff;
	dp_bgcg = 0xff;
	dp_bgcb = 0xff;
	return;
}

/* add color data */
static void colordata(int rev)
{

	/* 782 colors */
	coloradd("alice blue", 0x00f0f8ff, rev);	/* color 0 r/g/b decimal 240 248 255 */
	coloradd("AliceBlue", 0x00f0f8ff, rev);	/* color 1 r/g/b decimal 240 248 255 */
	coloradd("antique white", 0x00faebd7, rev);	/* color 2 r/g/b decimal 250 235 215 */
	coloradd("AntiqueWhite", 0x00faebd7, rev);	/* color 3 r/g/b decimal 250 235 215 */
	coloradd("AntiqueWhite1", 0x00ffefdb, rev);	/* color 4 r/g/b decimal 255 239 219 */
	coloradd("AntiqueWhite2", 0x00eedfcc, rev);	/* color 5 r/g/b decimal 238 223 204 */
	coloradd("AntiqueWhite3", 0x00cdc0b0, rev);	/* color 6 r/g/b decimal 205 192 176 */
	coloradd("AntiqueWhite4", 0x008b8378, rev);	/* color 7 r/g/b decimal 139 131 120 */
	coloradd("aqua", 0x0000ffff, rev);	/* color 8 r/g/b decimal 0 255 255 */
	coloradd("aquamarine", 0x007fffd4, rev);	/* color 9 r/g/b decimal 127 255 212 */
	coloradd("aquamarine1", 0x007fffd4, rev);	/* color 10 r/g/b decimal 127 255 212 */
	coloradd("aquamarine2", 0x0076eec6, rev);	/* color 11 r/g/b decimal 118 238 198 */
	coloradd("aquamarine3", 0x0066cdaa, rev);	/* color 12 r/g/b decimal 102 205 170 */
	coloradd("aquamarine4", 0x00458b74, rev);	/* color 13 r/g/b decimal 69 139 116 */
	coloradd("azure", 0x00f0ffff, rev);	/* color 14 r/g/b decimal 240 255 255 */
	coloradd("azure1", 0x00f0ffff, rev);	/* color 15 r/g/b decimal 240 255 255 */
	coloradd("azure2", 0x00e0eeee, rev);	/* color 16 r/g/b decimal 224 238 238 */
	coloradd("azure3", 0x00c1cdcd, rev);	/* color 17 r/g/b decimal 193 205 205 */
	coloradd("azure4", 0x00838b8b, rev);	/* color 18 r/g/b decimal 131 139 139 */
	coloradd("beige", 0x00f5f5dc, rev);	/* color 19 r/g/b decimal 245 245 220 */
	coloradd("bisque", 0x00ffe4c4, rev);	/* color 20 r/g/b decimal 255 228 196 */
	coloradd("bisque1", 0x00ffe4c4, rev);	/* color 21 r/g/b decimal 255 228 196 */
	coloradd("bisque2", 0x00eed5b7, rev);	/* color 22 r/g/b decimal 238 213 183 */
	coloradd("bisque3", 0x00cdb79e, rev);	/* color 23 r/g/b decimal 205 183 158 */
	coloradd("bisque4", 0x008b7d6b, rev);	/* color 24 r/g/b decimal 139 125 107 */
	coloradd("black", 0x00000000, rev);	/* color 25 r/g/b decimal 0 0 0 */
	coloradd("blanched almond", 0x00ffebcd, rev);	/* color 26 r/g/b decimal 255 235 205 */
	coloradd("BlanchedAlmond", 0x00ffebcd, rev);	/* color 27 r/g/b decimal 255 235 205 */
	coloradd("blue", 0x000000ff, rev);	/* color 28 r/g/b decimal 0 0 255 */
	coloradd("blue violet", 0x008a2be2, rev);	/* color 29 r/g/b decimal 138 43 226 */
	coloradd("blue1", 0x000000ff, rev);	/* color 30 r/g/b decimal 0 0 255 */
	coloradd("blue2", 0x000000ee, rev);	/* color 31 r/g/b decimal 0 0 238 */
	coloradd("blue3", 0x000000cd, rev);	/* color 32 r/g/b decimal 0 0 205 */
	coloradd("blue4", 0x0000008b, rev);	/* color 33 r/g/b decimal 0 0 139 */
	coloradd("BlueViolet", 0x008a2be2, rev);	/* color 34 r/g/b decimal 138 43 226 */
	coloradd("brown", 0x00a52a2a, rev);	/* color 35 r/g/b decimal 165 42 42 */
	coloradd("brown1", 0x00ff4040, rev);	/* color 36 r/g/b decimal 255 64 64 */
	coloradd("brown2", 0x00ee3b3b, rev);	/* color 37 r/g/b decimal 238 59 59 */
	coloradd("brown3", 0x00cd3333, rev);	/* color 38 r/g/b decimal 205 51 51 */
	coloradd("brown4", 0x008b2323, rev);	/* color 39 r/g/b decimal 139 35 35 */
	coloradd("burlywood", 0x00deb887, rev);	/* color 40 r/g/b decimal 222 184 135 */
	coloradd("burlywood1", 0x00ffd39b, rev);	/* color 41 r/g/b decimal 255 211 155 */
	coloradd("burlywood2", 0x00eec591, rev);	/* color 42 r/g/b decimal 238 197 145 */
	coloradd("burlywood3", 0x00cdaa7d, rev);	/* color 43 r/g/b decimal 205 170 125 */
	coloradd("burlywood4", 0x008b7355, rev);	/* color 44 r/g/b decimal 139 115 85 */
	coloradd("cadet blue", 0x005f9ea0, rev);	/* color 45 r/g/b decimal 95 158 160 */
	coloradd("CadetBlue", 0x005f9ea0, rev);	/* color 46 r/g/b decimal 95 158 160 */
	coloradd("CadetBlue1", 0x0098f5ff, rev);	/* color 47 r/g/b decimal 152 245 255 */
	coloradd("CadetBlue2", 0x008ee5ee, rev);	/* color 48 r/g/b decimal 142 229 238 */
	coloradd("CadetBlue3", 0x007ac5cd, rev);	/* color 49 r/g/b decimal 122 197 205 */
	coloradd("CadetBlue4", 0x0053868b, rev);	/* color 50 r/g/b decimal 83 134 139 */
	coloradd("chartreuse", 0x007fff00, rev);	/* color 51 r/g/b decimal 127 255 0 */
	coloradd("chartreuse1", 0x007fff00, rev);	/* color 52 r/g/b decimal 127 255 0 */
	coloradd("chartreuse2", 0x0076ee00, rev);	/* color 53 r/g/b decimal 118 238 0 */
	coloradd("chartreuse3", 0x0066cd00, rev);	/* color 54 r/g/b decimal 102 205 0 */
	coloradd("chartreuse4", 0x00458b00, rev);	/* color 55 r/g/b decimal 69 139 0 */
	coloradd("chocolate", 0x00d2691e, rev);	/* color 56 r/g/b decimal 210 105 30 */
	coloradd("chocolate1", 0x00ff7f24, rev);	/* color 57 r/g/b decimal 255 127 36 */
	coloradd("chocolate2", 0x00ee7621, rev);	/* color 58 r/g/b decimal 238 118 33 */
	coloradd("chocolate3", 0x00cd661d, rev);	/* color 59 r/g/b decimal 205 102 29 */
	coloradd("chocolate4", 0x008b4513, rev);	/* color 60 r/g/b decimal 139 69 19 */
	coloradd("coral", 0x00ff7f50, rev);	/* color 61 r/g/b decimal 255 127 80 */
	coloradd("coral1", 0x00ff7256, rev);	/* color 62 r/g/b decimal 255 114 86 */
	coloradd("coral2", 0x00ee6a50, rev);	/* color 63 r/g/b decimal 238 106 80 */
	coloradd("coral3", 0x00cd5b45, rev);	/* color 64 r/g/b decimal 205 91 69 */
	coloradd("coral4", 0x008b3e2f, rev);	/* color 65 r/g/b decimal 139 62 47 */
	coloradd("cornflower blue", 0x006495ed, rev);	/* color 66 r/g/b decimal 100 149 237 */
	coloradd("CornflowerBlue", 0x006495ed, rev);	/* color 67 r/g/b decimal 100 149 237 */
	coloradd("cornsilk", 0x00fff8dc, rev);	/* color 68 r/g/b decimal 255 248 220 */
	coloradd("cornsilk1", 0x00fff8dc, rev);	/* color 69 r/g/b decimal 255 248 220 */
	coloradd("cornsilk2", 0x00eee8cd, rev);	/* color 70 r/g/b decimal 238 232 205 */
	coloradd("cornsilk3", 0x00cdc8b1, rev);	/* color 71 r/g/b decimal 205 200 177 */
	coloradd("cornsilk4", 0x008b8878, rev);	/* color 72 r/g/b decimal 139 136 120 */
	coloradd("crimson", 0x00dc143c, rev);	/* color 73 r/g/b decimal 220 20 60 */
	coloradd("cyan", 0x0000ffff, rev);	/* color 74 r/g/b decimal 0 255 255 */
	coloradd("cyan1", 0x0000ffff, rev);	/* color 75 r/g/b decimal 0 255 255 */
	coloradd("cyan2", 0x0000eeee, rev);	/* color 76 r/g/b decimal 0 238 238 */
	coloradd("cyan3", 0x0000cdcd, rev);	/* color 77 r/g/b decimal 0 205 205 */
	coloradd("cyan4", 0x00008b8b, rev);	/* color 78 r/g/b decimal 0 139 139 */
	coloradd("dark blue", 0x0000008b, rev);	/* color 79 r/g/b decimal 0 0 139 */
	coloradd("dark cyan", 0x00008b8b, rev);	/* color 80 r/g/b decimal 0 139 139 */
	coloradd("dark goldenrod", 0x00b8860b, rev);	/* color 81 r/g/b decimal 184 134 11 */
	coloradd("dark gray", 0x00a9a9a9, rev);	/* color 82 r/g/b decimal 169 169 169 */
	coloradd("dark green", 0x00006400, rev);	/* color 83 r/g/b decimal 0 100 0 */
	coloradd("dark grey", 0x00a9a9a9, rev);	/* color 84 r/g/b decimal 169 169 169 */
	coloradd("dark khaki", 0x00bdb76b, rev);	/* color 85 r/g/b decimal 189 183 107 */
	coloradd("dark magenta", 0x008b008b, rev);	/* color 86 r/g/b decimal 139 0 139 */
	coloradd("dark olive green", 0x00556b2f, rev);	/* color 87 r/g/b decimal 85 107 47 */
	coloradd("dark orange", 0x00ff8c00, rev);	/* color 88 r/g/b decimal 255 140 0 */
	coloradd("dark orchid", 0x009932cc, rev);	/* color 89 r/g/b decimal 153 50 204 */
	coloradd("dark red", 0x008b0000, rev);	/* color 90 r/g/b decimal 139 0 0 */
	coloradd("dark salmon", 0x00e9967a, rev);	/* color 91 r/g/b decimal 233 150 122 */
	coloradd("dark sea green", 0x008fbc8f, rev);	/* color 92 r/g/b decimal 143 188 143 */
	coloradd("dark slate blue", 0x00483d8b, rev);	/* color 93 r/g/b decimal 72 61 139 */
	coloradd("dark slate gray", 0x002f4f4f, rev);	/* color 94 r/g/b decimal 47 79 79 */
	coloradd("dark slate grey", 0x002f4f4f, rev);	/* color 95 r/g/b decimal 47 79 79 */
	coloradd("dark turquoise", 0x0000ced1, rev);	/* color 96 r/g/b decimal 0 206 209 */
	coloradd("dark violet", 0x009400d3, rev);	/* color 97 r/g/b decimal 148 0 211 */
	coloradd("DarkBlue", 0x0000008b, rev);	/* color 98 r/g/b decimal 0 0 139 */
	coloradd("DarkCyan", 0x00008b8b, rev);	/* color 99 r/g/b decimal 0 139 139 */
	coloradd("DarkGoldenrod", 0x00b8860b, rev);	/* color 100 r/g/b decimal 184 134 11 */
	coloradd("DarkGoldenrod1", 0x00ffb90f, rev);	/* color 101 r/g/b decimal 255 185 15 */
	coloradd("DarkGoldenrod2", 0x00eead0e, rev);	/* color 102 r/g/b decimal 238 173 14 */
	coloradd("DarkGoldenrod3", 0x00cd950c, rev);	/* color 103 r/g/b decimal 205 149 12 */
	coloradd("DarkGoldenrod4", 0x008b6508, rev);	/* color 104 r/g/b decimal 139 101 8 */
	coloradd("DarkGray", 0x00a9a9a9, rev);	/* color 105 r/g/b decimal 169 169 169 */
	coloradd("DarkGreen", 0x00006400, rev);	/* color 106 r/g/b decimal 0 100 0 */
	coloradd("DarkGrey", 0x00a9a9a9, rev);	/* color 107 r/g/b decimal 169 169 169 */
	coloradd("DarkKhaki", 0x00bdb76b, rev);	/* color 108 r/g/b decimal 189 183 107 */
	coloradd("DarkMagenta", 0x008b008b, rev);	/* color 109 r/g/b decimal 139 0 139 */
	coloradd("DarkOliveGreen", 0x00556b2f, rev);	/* color 110 r/g/b decimal 85 107 47 */
	coloradd("DarkOliveGreen1", 0x00caff70, rev);	/* color 111 r/g/b decimal 202 255 112 */
	coloradd("DarkOliveGreen2", 0x00bcee68, rev);	/* color 112 r/g/b decimal 188 238 104 */
	coloradd("DarkOliveGreen3", 0x00a2cd5a, rev);	/* color 113 r/g/b decimal 162 205 90 */
	coloradd("DarkOliveGreen4", 0x006e8b3d, rev);	/* color 114 r/g/b decimal 110 139 61 */
	coloradd("DarkOrange", 0x00ff8c00, rev);	/* color 115 r/g/b decimal 255 140 0 */
	coloradd("DarkOrange1", 0x00ff7f00, rev);	/* color 116 r/g/b decimal 255 127 0 */
	coloradd("DarkOrange2", 0x00ee7600, rev);	/* color 117 r/g/b decimal 238 118 0 */
	coloradd("DarkOrange3", 0x00cd6600, rev);	/* color 118 r/g/b decimal 205 102 0 */
	coloradd("DarkOrange4", 0x008b4500, rev);	/* color 119 r/g/b decimal 139 69 0 */
	coloradd("DarkOrchid", 0x009932cc, rev);	/* color 120 r/g/b decimal 153 50 204 */
	coloradd("DarkOrchid1", 0x00bf3eff, rev);	/* color 121 r/g/b decimal 191 62 255 */
	coloradd("DarkOrchid2", 0x00b23aee, rev);	/* color 122 r/g/b decimal 178 58 238 */
	coloradd("DarkOrchid3", 0x009a32cd, rev);	/* color 123 r/g/b decimal 154 50 205 */
	coloradd("DarkOrchid4", 0x0068228b, rev);	/* color 124 r/g/b decimal 104 34 139 */
	coloradd("DarkRed", 0x008b0000, rev);	/* color 125 r/g/b decimal 139 0 0 */
	coloradd("DarkSalmon", 0x00e9967a, rev);	/* color 126 r/g/b decimal 233 150 122 */
	coloradd("DarkSeaGreen", 0x008fbc8f, rev);	/* color 127 r/g/b decimal 143 188 143 */
	coloradd("DarkSeaGreen1", 0x00c1ffc1, rev);	/* color 128 r/g/b decimal 193 255 193 */
	coloradd("DarkSeaGreen2", 0x00b4eeb4, rev);	/* color 129 r/g/b decimal 180 238 180 */
	coloradd("DarkSeaGreen3", 0x009bcd9b, rev);	/* color 130 r/g/b decimal 155 205 155 */
	coloradd("DarkSeaGreen4", 0x00698b69, rev);	/* color 131 r/g/b decimal 105 139 105 */
	coloradd("DarkSlateBlue", 0x00483d8b, rev);	/* color 132 r/g/b decimal 72 61 139 */
	coloradd("DarkSlateGray", 0x002f4f4f, rev);	/* color 133 r/g/b decimal 47 79 79 */
	coloradd("DarkSlateGray1", 0x0097ffff, rev);	/* color 134 r/g/b decimal 151 255 255 */
	coloradd("DarkSlateGray2", 0x008deeee, rev);	/* color 135 r/g/b decimal 141 238 238 */
	coloradd("DarkSlateGray3", 0x0079cdcd, rev);	/* color 136 r/g/b decimal 121 205 205 */
	coloradd("DarkSlateGray4", 0x00528b8b, rev);	/* color 137 r/g/b decimal 82 139 139 */
	coloradd("DarkSlateGrey", 0x002f4f4f, rev);	/* color 138 r/g/b decimal 47 79 79 */
	coloradd("DarkTurquoise", 0x0000ced1, rev);	/* color 139 r/g/b decimal 0 206 209 */
	coloradd("DarkViolet", 0x009400d3, rev);	/* color 140 r/g/b decimal 148 0 211 */
	coloradd("deep pink", 0x00ff1493, rev);	/* color 141 r/g/b decimal 255 20 147 */
	coloradd("deep sky blue", 0x0000bfff, rev);	/* color 142 r/g/b decimal 0 191 255 */
	coloradd("DeepPink", 0x00ff1493, rev);	/* color 143 r/g/b decimal 255 20 147 */
	coloradd("DeepPink1", 0x00ff1493, rev);	/* color 144 r/g/b decimal 255 20 147 */
	coloradd("DeepPink2", 0x00ee1289, rev);	/* color 145 r/g/b decimal 238 18 137 */
	coloradd("DeepPink3", 0x00cd1076, rev);	/* color 146 r/g/b decimal 205 16 118 */
	coloradd("DeepPink4", 0x008b0a50, rev);	/* color 147 r/g/b decimal 139 10 80 */
	coloradd("DeepSkyBlue", 0x0000bfff, rev);	/* color 148 r/g/b decimal 0 191 255 */
	coloradd("DeepSkyBlue1", 0x0000bfff, rev);	/* color 149 r/g/b decimal 0 191 255 */
	coloradd("DeepSkyBlue2", 0x0000b2ee, rev);	/* color 150 r/g/b decimal 0 178 238 */
	coloradd("DeepSkyBlue3", 0x00009acd, rev);	/* color 151 r/g/b decimal 0 154 205 */
	coloradd("DeepSkyBlue4", 0x0000688b, rev);	/* color 152 r/g/b decimal 0 104 139 */
	coloradd("dim gray", 0x00696969, rev);	/* color 153 r/g/b decimal 105 105 105 */
	coloradd("dim grey", 0x00696969, rev);	/* color 154 r/g/b decimal 105 105 105 */
	coloradd("DimGray", 0x00696969, rev);	/* color 155 r/g/b decimal 105 105 105 */
	coloradd("DimGrey", 0x00696969, rev);	/* color 156 r/g/b decimal 105 105 105 */
	coloradd("dodger blue", 0x001e90ff, rev);	/* color 157 r/g/b decimal 30 144 255 */
	coloradd("DodgerBlue", 0x001e90ff, rev);	/* color 158 r/g/b decimal 30 144 255 */
	coloradd("DodgerBlue1", 0x001e90ff, rev);	/* color 159 r/g/b decimal 30 144 255 */
	coloradd("DodgerBlue2", 0x001c86ee, rev);	/* color 160 r/g/b decimal 28 134 238 */
	coloradd("DodgerBlue3", 0x001874cd, rev);	/* color 161 r/g/b decimal 24 116 205 */
	coloradd("DodgerBlue4", 0x00104e8b, rev);	/* color 162 r/g/b decimal 16 78 139 */
	coloradd("firebrick", 0x00b22222, rev);	/* color 163 r/g/b decimal 178 34 34 */
	coloradd("firebrick1", 0x00ff3030, rev);	/* color 164 r/g/b decimal 255 48 48 */
	coloradd("firebrick2", 0x00ee2c2c, rev);	/* color 165 r/g/b decimal 238 44 44 */
	coloradd("firebrick3", 0x00cd2626, rev);	/* color 166 r/g/b decimal 205 38 38 */
	coloradd("firebrick4", 0x008b1a1a, rev);	/* color 167 r/g/b decimal 139 26 26 */
	coloradd("floral white", 0x00fffaf0, rev);	/* color 168 r/g/b decimal 255 250 240 */
	coloradd("FloralWhite", 0x00fffaf0, rev);	/* color 169 r/g/b decimal 255 250 240 */
	coloradd("forest green", 0x00228b22, rev);	/* color 170 r/g/b decimal 34 139 34 */
	coloradd("ForestGreen", 0x00228b22, rev);	/* color 171 r/g/b decimal 34 139 34 */
	coloradd("fuchsia", 0x00ff00ff, rev);	/* color 172 r/g/b decimal 255 0 255 */
	coloradd("gainsboro", 0x00dcdcdc, rev);	/* color 173 r/g/b decimal 220 220 220 */
	coloradd("ghost white", 0x00f8f8ff, rev);	/* color 174 r/g/b decimal 248 248 255 */
	coloradd("GhostWhite", 0x00f8f8ff, rev);	/* color 175 r/g/b decimal 248 248 255 */
	coloradd("gold", 0x00ffd700, rev);	/* color 176 r/g/b decimal 255 215 0 */
	coloradd("gold1", 0x00ffd700, rev);	/* color 177 r/g/b decimal 255 215 0 */
	coloradd("gold2", 0x00eec900, rev);	/* color 178 r/g/b decimal 238 201 0 */
	coloradd("gold3", 0x00cdad00, rev);	/* color 179 r/g/b decimal 205 173 0 */
	coloradd("gold4", 0x008b7500, rev);	/* color 180 r/g/b decimal 139 117 0 */
	coloradd("goldenrod", 0x00daa520, rev);	/* color 181 r/g/b decimal 218 165 32 */
	coloradd("goldenrod1", 0x00ffc125, rev);	/* color 182 r/g/b decimal 255 193 37 */
	coloradd("goldenrod2", 0x00eeb422, rev);	/* color 183 r/g/b decimal 238 180 34 */
	coloradd("goldenrod3", 0x00cd9b1d, rev);	/* color 184 r/g/b decimal 205 155 29 */
	coloradd("goldenrod4", 0x008b6914, rev);	/* color 185 r/g/b decimal 139 105 20 */
	coloradd("gray", 0x00bebebe, rev);	/* color 186 r/g/b decimal 190 190 190 */
	coloradd("gray0", 0x00000000, rev);	/* color 187 r/g/b decimal 0 0 0 */
	coloradd("gray1", 0x00030303, rev);	/* color 188 r/g/b decimal 3 3 3 */
	coloradd("gray10", 0x001a1a1a, rev);	/* color 189 r/g/b decimal 26 26 26 */
	coloradd("gray100", 0x00ffffff, rev);	/* color 190 r/g/b decimal 255 255 255 */
	coloradd("gray11", 0x001c1c1c, rev);	/* color 191 r/g/b decimal 28 28 28 */
	coloradd("gray12", 0x001f1f1f, rev);	/* color 192 r/g/b decimal 31 31 31 */
	coloradd("gray13", 0x00212121, rev);	/* color 193 r/g/b decimal 33 33 33 */
	coloradd("gray14", 0x00242424, rev);	/* color 194 r/g/b decimal 36 36 36 */
	coloradd("gray15", 0x00262626, rev);	/* color 195 r/g/b decimal 38 38 38 */
	coloradd("gray16", 0x00292929, rev);	/* color 196 r/g/b decimal 41 41 41 */
	coloradd("gray17", 0x002b2b2b, rev);	/* color 197 r/g/b decimal 43 43 43 */
	coloradd("gray18", 0x002e2e2e, rev);	/* color 198 r/g/b decimal 46 46 46 */
	coloradd("gray19", 0x00303030, rev);	/* color 199 r/g/b decimal 48 48 48 */
	coloradd("gray2", 0x00050505, rev);	/* color 200 r/g/b decimal 5 5 5 */
	coloradd("gray20", 0x00333333, rev);	/* color 201 r/g/b decimal 51 51 51 */
	coloradd("gray21", 0x00363636, rev);	/* color 202 r/g/b decimal 54 54 54 */
	coloradd("gray22", 0x00383838, rev);	/* color 203 r/g/b decimal 56 56 56 */
	coloradd("gray23", 0x003b3b3b, rev);	/* color 204 r/g/b decimal 59 59 59 */
	coloradd("gray24", 0x003d3d3d, rev);	/* color 205 r/g/b decimal 61 61 61 */
	coloradd("gray25", 0x00404040, rev);	/* color 206 r/g/b decimal 64 64 64 */
	coloradd("gray26", 0x00424242, rev);	/* color 207 r/g/b decimal 66 66 66 */
	coloradd("gray27", 0x00454545, rev);	/* color 208 r/g/b decimal 69 69 69 */
	coloradd("gray28", 0x00474747, rev);	/* color 209 r/g/b decimal 71 71 71 */
	coloradd("gray29", 0x004a4a4a, rev);	/* color 210 r/g/b decimal 74 74 74 */
	coloradd("gray3", 0x00080808, rev);	/* color 211 r/g/b decimal 8 8 8 */
	coloradd("gray30", 0x004d4d4d, rev);	/* color 212 r/g/b decimal 77 77 77 */
	coloradd("gray31", 0x004f4f4f, rev);	/* color 213 r/g/b decimal 79 79 79 */
	coloradd("gray32", 0x00525252, rev);	/* color 214 r/g/b decimal 82 82 82 */
	coloradd("gray33", 0x00545454, rev);	/* color 215 r/g/b decimal 84 84 84 */
	coloradd("gray34", 0x00575757, rev);	/* color 216 r/g/b decimal 87 87 87 */
	coloradd("gray35", 0x00595959, rev);	/* color 217 r/g/b decimal 89 89 89 */
	coloradd("gray36", 0x005c5c5c, rev);	/* color 218 r/g/b decimal 92 92 92 */
	coloradd("gray37", 0x005e5e5e, rev);	/* color 219 r/g/b decimal 94 94 94 */
	coloradd("gray38", 0x00616161, rev);	/* color 220 r/g/b decimal 97 97 97 */
	coloradd("gray39", 0x00636363, rev);	/* color 221 r/g/b decimal 99 99 99 */
	coloradd("gray4", 0x000a0a0a, rev);	/* color 222 r/g/b decimal 10 10 10 */
	coloradd("gray40", 0x00666666, rev);	/* color 223 r/g/b decimal 102 102 102 */
	coloradd("gray41", 0x00696969, rev);	/* color 224 r/g/b decimal 105 105 105 */
	coloradd("gray42", 0x006b6b6b, rev);	/* color 225 r/g/b decimal 107 107 107 */
	coloradd("gray43", 0x006e6e6e, rev);	/* color 226 r/g/b decimal 110 110 110 */
	coloradd("gray44", 0x00707070, rev);	/* color 227 r/g/b decimal 112 112 112 */
	coloradd("gray45", 0x00737373, rev);	/* color 228 r/g/b decimal 115 115 115 */
	coloradd("gray46", 0x00757575, rev);	/* color 229 r/g/b decimal 117 117 117 */
	coloradd("gray47", 0x00787878, rev);	/* color 230 r/g/b decimal 120 120 120 */
	coloradd("gray48", 0x007a7a7a, rev);	/* color 231 r/g/b decimal 122 122 122 */
	coloradd("gray49", 0x007d7d7d, rev);	/* color 232 r/g/b decimal 125 125 125 */
	coloradd("gray5", 0x000d0d0d, rev);	/* color 233 r/g/b decimal 13 13 13 */
	coloradd("gray50", 0x007f7f7f, rev);	/* color 234 r/g/b decimal 127 127 127 */
	coloradd("gray51", 0x00828282, rev);	/* color 235 r/g/b decimal 130 130 130 */
	coloradd("gray52", 0x00858585, rev);	/* color 236 r/g/b decimal 133 133 133 */
	coloradd("gray53", 0x00878787, rev);	/* color 237 r/g/b decimal 135 135 135 */
	coloradd("gray54", 0x008a8a8a, rev);	/* color 238 r/g/b decimal 138 138 138 */
	coloradd("gray55", 0x008c8c8c, rev);	/* color 239 r/g/b decimal 140 140 140 */
	coloradd("gray56", 0x008f8f8f, rev);	/* color 240 r/g/b decimal 143 143 143 */
	coloradd("gray57", 0x00919191, rev);	/* color 241 r/g/b decimal 145 145 145 */
	coloradd("gray58", 0x00949494, rev);	/* color 242 r/g/b decimal 148 148 148 */
	coloradd("gray59", 0x00969696, rev);	/* color 243 r/g/b decimal 150 150 150 */
	coloradd("gray6", 0x000f0f0f, rev);	/* color 244 r/g/b decimal 15 15 15 */
	coloradd("gray60", 0x00999999, rev);	/* color 245 r/g/b decimal 153 153 153 */
	coloradd("gray61", 0x009c9c9c, rev);	/* color 246 r/g/b decimal 156 156 156 */
	coloradd("gray62", 0x009e9e9e, rev);	/* color 247 r/g/b decimal 158 158 158 */
	coloradd("gray63", 0x00a1a1a1, rev);	/* color 248 r/g/b decimal 161 161 161 */
	coloradd("gray64", 0x00a3a3a3, rev);	/* color 249 r/g/b decimal 163 163 163 */
	coloradd("gray65", 0x00a6a6a6, rev);	/* color 250 r/g/b decimal 166 166 166 */
	coloradd("gray66", 0x00a8a8a8, rev);	/* color 251 r/g/b decimal 168 168 168 */
	coloradd("gray67", 0x00ababab, rev);	/* color 252 r/g/b decimal 171 171 171 */
	coloradd("gray68", 0x00adadad, rev);	/* color 253 r/g/b decimal 173 173 173 */
	coloradd("gray69", 0x00b0b0b0, rev);	/* color 254 r/g/b decimal 176 176 176 */
	coloradd("gray7", 0x00121212, rev);	/* color 255 r/g/b decimal 18 18 18 */
	coloradd("gray70", 0x00b3b3b3, rev);	/* color 256 r/g/b decimal 179 179 179 */
	coloradd("gray71", 0x00b5b5b5, rev);	/* color 257 r/g/b decimal 181 181 181 */
	coloradd("gray72", 0x00b8b8b8, rev);	/* color 258 r/g/b decimal 184 184 184 */
	coloradd("gray73", 0x00bababa, rev);	/* color 259 r/g/b decimal 186 186 186 */
	coloradd("gray74", 0x00bdbdbd, rev);	/* color 260 r/g/b decimal 189 189 189 */
	coloradd("gray75", 0x00bfbfbf, rev);	/* color 261 r/g/b decimal 191 191 191 */
	coloradd("gray76", 0x00c2c2c2, rev);	/* color 262 r/g/b decimal 194 194 194 */
	coloradd("gray77", 0x00c4c4c4, rev);	/* color 263 r/g/b decimal 196 196 196 */
	coloradd("gray78", 0x00c7c7c7, rev);	/* color 264 r/g/b decimal 199 199 199 */
	coloradd("gray79", 0x00c9c9c9, rev);	/* color 265 r/g/b decimal 201 201 201 */
	coloradd("gray8", 0x00141414, rev);	/* color 266 r/g/b decimal 20 20 20 */
	coloradd("gray80", 0x00cccccc, rev);	/* color 267 r/g/b decimal 204 204 204 */
	coloradd("gray81", 0x00cfcfcf, rev);	/* color 268 r/g/b decimal 207 207 207 */
	coloradd("gray82", 0x00d1d1d1, rev);	/* color 269 r/g/b decimal 209 209 209 */
	coloradd("gray83", 0x00d4d4d4, rev);	/* color 270 r/g/b decimal 212 212 212 */
	coloradd("gray84", 0x00d6d6d6, rev);	/* color 271 r/g/b decimal 214 214 214 */
	coloradd("gray85", 0x00d9d9d9, rev);	/* color 272 r/g/b decimal 217 217 217 */
	coloradd("gray86", 0x00dbdbdb, rev);	/* color 273 r/g/b decimal 219 219 219 */
	coloradd("gray87", 0x00dedede, rev);	/* color 274 r/g/b decimal 222 222 222 */
	coloradd("gray88", 0x00e0e0e0, rev);	/* color 275 r/g/b decimal 224 224 224 */
	coloradd("gray89", 0x00e3e3e3, rev);	/* color 276 r/g/b decimal 227 227 227 */
	coloradd("gray9", 0x00171717, rev);	/* color 277 r/g/b decimal 23 23 23 */
	coloradd("gray90", 0x00e5e5e5, rev);	/* color 278 r/g/b decimal 229 229 229 */
	coloradd("gray91", 0x00e8e8e8, rev);	/* color 279 r/g/b decimal 232 232 232 */
	coloradd("gray92", 0x00ebebeb, rev);	/* color 280 r/g/b decimal 235 235 235 */
	coloradd("gray93", 0x00ededed, rev);	/* color 281 r/g/b decimal 237 237 237 */
	coloradd("gray94", 0x00f0f0f0, rev);	/* color 282 r/g/b decimal 240 240 240 */
	coloradd("gray95", 0x00f2f2f2, rev);	/* color 283 r/g/b decimal 242 242 242 */
	coloradd("gray96", 0x00f5f5f5, rev);	/* color 284 r/g/b decimal 245 245 245 */
	coloradd("gray97", 0x00f7f7f7, rev);	/* color 285 r/g/b decimal 247 247 247 */
	coloradd("gray98", 0x00fafafa, rev);	/* color 286 r/g/b decimal 250 250 250 */
	coloradd("gray99", 0x00fcfcfc, rev);	/* color 287 r/g/b decimal 252 252 252 */
	coloradd("green", 0x0000ff00, rev);	/* color 288 r/g/b decimal 0 255 0 */
	coloradd("green yellow", 0x00adff2f, rev);	/* color 289 r/g/b decimal 173 255 47 */
	coloradd("green1", 0x0000ff00, rev);	/* color 290 r/g/b decimal 0 255 0 */
	coloradd("green2", 0x0000ee00, rev);	/* color 291 r/g/b decimal 0 238 0 */
	coloradd("green3", 0x0000cd00, rev);	/* color 292 r/g/b decimal 0 205 0 */
	coloradd("green4", 0x00008b00, rev);	/* color 293 r/g/b decimal 0 139 0 */
	coloradd("GreenYellow", 0x00adff2f, rev);	/* color 294 r/g/b decimal 173 255 47 */
	coloradd("grey", 0x00bebebe, rev);	/* color 295 r/g/b decimal 190 190 190 */
	coloradd("grey0", 0x00000000, rev);	/* color 296 r/g/b decimal 0 0 0 */
	coloradd("grey1", 0x00030303, rev);	/* color 297 r/g/b decimal 3 3 3 */
	coloradd("grey10", 0x001a1a1a, rev);	/* color 298 r/g/b decimal 26 26 26 */
	coloradd("grey100", 0x00ffffff, rev);	/* color 299 r/g/b decimal 255 255 255 */
	coloradd("grey11", 0x001c1c1c, rev);	/* color 300 r/g/b decimal 28 28 28 */
	coloradd("grey12", 0x001f1f1f, rev);	/* color 301 r/g/b decimal 31 31 31 */
	coloradd("grey13", 0x00212121, rev);	/* color 302 r/g/b decimal 33 33 33 */
	coloradd("grey14", 0x00242424, rev);	/* color 303 r/g/b decimal 36 36 36 */
	coloradd("grey15", 0x00262626, rev);	/* color 304 r/g/b decimal 38 38 38 */
	coloradd("grey16", 0x00292929, rev);	/* color 305 r/g/b decimal 41 41 41 */
	coloradd("grey17", 0x002b2b2b, rev);	/* color 306 r/g/b decimal 43 43 43 */
	coloradd("grey18", 0x002e2e2e, rev);	/* color 307 r/g/b decimal 46 46 46 */
	coloradd("grey19", 0x00303030, rev);	/* color 308 r/g/b decimal 48 48 48 */
	coloradd("grey2", 0x00050505, rev);	/* color 309 r/g/b decimal 5 5 5 */
	coloradd("grey20", 0x00333333, rev);	/* color 310 r/g/b decimal 51 51 51 */
	coloradd("grey21", 0x00363636, rev);	/* color 311 r/g/b decimal 54 54 54 */
	coloradd("grey22", 0x00383838, rev);	/* color 312 r/g/b decimal 56 56 56 */
	coloradd("grey23", 0x003b3b3b, rev);	/* color 313 r/g/b decimal 59 59 59 */
	coloradd("grey24", 0x003d3d3d, rev);	/* color 314 r/g/b decimal 61 61 61 */
	coloradd("grey25", 0x00404040, rev);	/* color 315 r/g/b decimal 64 64 64 */
	coloradd("grey26", 0x00424242, rev);	/* color 316 r/g/b decimal 66 66 66 */
	coloradd("grey27", 0x00454545, rev);	/* color 317 r/g/b decimal 69 69 69 */
	coloradd("grey28", 0x00474747, rev);	/* color 318 r/g/b decimal 71 71 71 */
	coloradd("grey29", 0x004a4a4a, rev);	/* color 319 r/g/b decimal 74 74 74 */
	coloradd("grey3", 0x00080808, rev);	/* color 320 r/g/b decimal 8 8 8 */
	coloradd("grey30", 0x004d4d4d, rev);	/* color 321 r/g/b decimal 77 77 77 */
	coloradd("grey31", 0x004f4f4f, rev);	/* color 322 r/g/b decimal 79 79 79 */
	coloradd("grey32", 0x00525252, rev);	/* color 323 r/g/b decimal 82 82 82 */
	coloradd("grey33", 0x00545454, rev);	/* color 324 r/g/b decimal 84 84 84 */
	coloradd("grey34", 0x00575757, rev);	/* color 325 r/g/b decimal 87 87 87 */
	coloradd("grey35", 0x00595959, rev);	/* color 326 r/g/b decimal 89 89 89 */
	coloradd("grey36", 0x005c5c5c, rev);	/* color 327 r/g/b decimal 92 92 92 */
	coloradd("grey37", 0x005e5e5e, rev);	/* color 328 r/g/b decimal 94 94 94 */
	coloradd("grey38", 0x00616161, rev);	/* color 329 r/g/b decimal 97 97 97 */
	coloradd("grey39", 0x00636363, rev);	/* color 330 r/g/b decimal 99 99 99 */
	coloradd("grey4", 0x000a0a0a, rev);	/* color 331 r/g/b decimal 10 10 10 */
	coloradd("grey40", 0x00666666, rev);	/* color 332 r/g/b decimal 102 102 102 */
	coloradd("grey41", 0x00696969, rev);	/* color 333 r/g/b decimal 105 105 105 */
	coloradd("grey42", 0x006b6b6b, rev);	/* color 334 r/g/b decimal 107 107 107 */
	coloradd("grey43", 0x006e6e6e, rev);	/* color 335 r/g/b decimal 110 110 110 */
	coloradd("grey44", 0x00707070, rev);	/* color 336 r/g/b decimal 112 112 112 */
	coloradd("grey45", 0x00737373, rev);	/* color 337 r/g/b decimal 115 115 115 */
	coloradd("grey46", 0x00757575, rev);	/* color 338 r/g/b decimal 117 117 117 */
	coloradd("grey47", 0x00787878, rev);	/* color 339 r/g/b decimal 120 120 120 */
	coloradd("grey48", 0x007a7a7a, rev);	/* color 340 r/g/b decimal 122 122 122 */
	coloradd("grey49", 0x007d7d7d, rev);	/* color 341 r/g/b decimal 125 125 125 */
	coloradd("grey5", 0x000d0d0d, rev);	/* color 342 r/g/b decimal 13 13 13 */
	coloradd("grey50", 0x007f7f7f, rev);	/* color 343 r/g/b decimal 127 127 127 */
	coloradd("grey51", 0x00828282, rev);	/* color 344 r/g/b decimal 130 130 130 */
	coloradd("grey52", 0x00858585, rev);	/* color 345 r/g/b decimal 133 133 133 */
	coloradd("grey53", 0x00878787, rev);	/* color 346 r/g/b decimal 135 135 135 */
	coloradd("grey54", 0x008a8a8a, rev);	/* color 347 r/g/b decimal 138 138 138 */
	coloradd("grey55", 0x008c8c8c, rev);	/* color 348 r/g/b decimal 140 140 140 */
	coloradd("grey56", 0x008f8f8f, rev);	/* color 349 r/g/b decimal 143 143 143 */
	coloradd("grey57", 0x00919191, rev);	/* color 350 r/g/b decimal 145 145 145 */
	coloradd("grey58", 0x00949494, rev);	/* color 351 r/g/b decimal 148 148 148 */
	coloradd("grey59", 0x00969696, rev);	/* color 352 r/g/b decimal 150 150 150 */
	coloradd("grey6", 0x000f0f0f, rev);	/* color 353 r/g/b decimal 15 15 15 */
	coloradd("grey60", 0x00999999, rev);	/* color 354 r/g/b decimal 153 153 153 */
	coloradd("grey61", 0x009c9c9c, rev);	/* color 355 r/g/b decimal 156 156 156 */
	coloradd("grey62", 0x009e9e9e, rev);	/* color 356 r/g/b decimal 158 158 158 */
	coloradd("grey63", 0x00a1a1a1, rev);	/* color 357 r/g/b decimal 161 161 161 */
	coloradd("grey64", 0x00a3a3a3, rev);	/* color 358 r/g/b decimal 163 163 163 */
	coloradd("grey65", 0x00a6a6a6, rev);	/* color 359 r/g/b decimal 166 166 166 */
	coloradd("grey66", 0x00a8a8a8, rev);	/* color 360 r/g/b decimal 168 168 168 */
	coloradd("grey67", 0x00ababab, rev);	/* color 361 r/g/b decimal 171 171 171 */
	coloradd("grey68", 0x00adadad, rev);	/* color 362 r/g/b decimal 173 173 173 */
	coloradd("grey69", 0x00b0b0b0, rev);	/* color 363 r/g/b decimal 176 176 176 */
	coloradd("grey7", 0x00121212, rev);	/* color 364 r/g/b decimal 18 18 18 */
	coloradd("grey70", 0x00b3b3b3, rev);	/* color 365 r/g/b decimal 179 179 179 */
	coloradd("grey71", 0x00b5b5b5, rev);	/* color 366 r/g/b decimal 181 181 181 */
	coloradd("grey72", 0x00b8b8b8, rev);	/* color 367 r/g/b decimal 184 184 184 */
	coloradd("grey73", 0x00bababa, rev);	/* color 368 r/g/b decimal 186 186 186 */
	coloradd("grey74", 0x00bdbdbd, rev);	/* color 369 r/g/b decimal 189 189 189 */
	coloradd("grey75", 0x00bfbfbf, rev);	/* color 370 r/g/b decimal 191 191 191 */
	coloradd("grey76", 0x00c2c2c2, rev);	/* color 371 r/g/b decimal 194 194 194 */
	coloradd("grey77", 0x00c4c4c4, rev);	/* color 372 r/g/b decimal 196 196 196 */
	coloradd("grey78", 0x00c7c7c7, rev);	/* color 373 r/g/b decimal 199 199 199 */
	coloradd("grey79", 0x00c9c9c9, rev);	/* color 374 r/g/b decimal 201 201 201 */
	coloradd("grey8", 0x00141414, rev);	/* color 375 r/g/b decimal 20 20 20 */
	coloradd("grey80", 0x00cccccc, rev);	/* color 376 r/g/b decimal 204 204 204 */
	coloradd("grey81", 0x00cfcfcf, rev);	/* color 377 r/g/b decimal 207 207 207 */
	coloradd("grey82", 0x00d1d1d1, rev);	/* color 378 r/g/b decimal 209 209 209 */
	coloradd("grey83", 0x00d4d4d4, rev);	/* color 379 r/g/b decimal 212 212 212 */
	coloradd("grey84", 0x00d6d6d6, rev);	/* color 380 r/g/b decimal 214 214 214 */
	coloradd("grey85", 0x00d9d9d9, rev);	/* color 381 r/g/b decimal 217 217 217 */
	coloradd("grey86", 0x00dbdbdb, rev);	/* color 382 r/g/b decimal 219 219 219 */
	coloradd("grey87", 0x00dedede, rev);	/* color 383 r/g/b decimal 222 222 222 */
	coloradd("grey88", 0x00e0e0e0, rev);	/* color 384 r/g/b decimal 224 224 224 */
	coloradd("grey89", 0x00e3e3e3, rev);	/* color 385 r/g/b decimal 227 227 227 */
	coloradd("grey9", 0x00171717, rev);	/* color 386 r/g/b decimal 23 23 23 */
	coloradd("grey90", 0x00e5e5e5, rev);	/* color 387 r/g/b decimal 229 229 229 */
	coloradd("grey91", 0x00e8e8e8, rev);	/* color 388 r/g/b decimal 232 232 232 */
	coloradd("grey92", 0x00ebebeb, rev);	/* color 389 r/g/b decimal 235 235 235 */
	coloradd("grey93", 0x00ededed, rev);	/* color 390 r/g/b decimal 237 237 237 */
	coloradd("grey94", 0x00f0f0f0, rev);	/* color 391 r/g/b decimal 240 240 240 */
	coloradd("grey95", 0x00f2f2f2, rev);	/* color 392 r/g/b decimal 242 242 242 */
	coloradd("grey96", 0x00f5f5f5, rev);	/* color 393 r/g/b decimal 245 245 245 */
	coloradd("grey97", 0x00f7f7f7, rev);	/* color 394 r/g/b decimal 247 247 247 */
	coloradd("grey98", 0x00fafafa, rev);	/* color 395 r/g/b decimal 250 250 250 */
	coloradd("grey99", 0x00fcfcfc, rev);	/* color 396 r/g/b decimal 252 252 252 */
	coloradd("honeydew", 0x00f0fff0, rev);	/* color 397 r/g/b decimal 240 255 240 */
	coloradd("honeydew1", 0x00f0fff0, rev);	/* color 398 r/g/b decimal 240 255 240 */
	coloradd("honeydew2", 0x00e0eee0, rev);	/* color 399 r/g/b decimal 224 238 224 */
	coloradd("honeydew3", 0x00c1cdc1, rev);	/* color 400 r/g/b decimal 193 205 193 */
	coloradd("honeydew4", 0x00838b83, rev);	/* color 401 r/g/b decimal 131 139 131 */
	coloradd("hot pink", 0x00ff69b4, rev);	/* color 402 r/g/b decimal 255 105 180 */
	coloradd("HotPink", 0x00ff69b4, rev);	/* color 403 r/g/b decimal 255 105 180 */
	coloradd("HotPink1", 0x00ff6eb4, rev);	/* color 404 r/g/b decimal 255 110 180 */
	coloradd("HotPink2", 0x00ee6aa7, rev);	/* color 405 r/g/b decimal 238 106 167 */
	coloradd("HotPink3", 0x00cd6090, rev);	/* color 406 r/g/b decimal 205 96 144 */
	coloradd("HotPink4", 0x008b3a62, rev);	/* color 407 r/g/b decimal 139 58 98 */
	coloradd("indian red", 0x00cd5c5c, rev);	/* color 408 r/g/b decimal 205 92 92 */
	coloradd("IndianRed", 0x00cd5c5c, rev);	/* color 409 r/g/b decimal 205 92 92 */
	coloradd("IndianRed1", 0x00ff6a6a, rev);	/* color 410 r/g/b decimal 255 106 106 */
	coloradd("IndianRed2", 0x00ee6363, rev);	/* color 411 r/g/b decimal 238 99 99 */
	coloradd("IndianRed3", 0x00cd5555, rev);	/* color 412 r/g/b decimal 205 85 85 */
	coloradd("IndianRed4", 0x008b3a3a, rev);	/* color 413 r/g/b decimal 139 58 58 */
	coloradd("indigo", 0x004b0082, rev);	/* color 414 r/g/b decimal 75 0 130 */
	coloradd("ivory", 0x00fffff0, rev);	/* color 415 r/g/b decimal 255 255 240 */
	coloradd("ivory1", 0x00fffff0, rev);	/* color 416 r/g/b decimal 255 255 240 */
	coloradd("ivory2", 0x00eeeee0, rev);	/* color 417 r/g/b decimal 238 238 224 */
	coloradd("ivory3", 0x00cdcdc1, rev);	/* color 418 r/g/b decimal 205 205 193 */
	coloradd("ivory4", 0x008b8b83, rev);	/* color 419 r/g/b decimal 139 139 131 */
	coloradd("khaki", 0x00f0e68c, rev);	/* color 420 r/g/b decimal 240 230 140 */
	coloradd("khaki1", 0x00fff68f, rev);	/* color 421 r/g/b decimal 255 246 143 */
	coloradd("khaki2", 0x00eee685, rev);	/* color 422 r/g/b decimal 238 230 133 */
	coloradd("khaki3", 0x00cdc673, rev);	/* color 423 r/g/b decimal 205 198 115 */
	coloradd("khaki4", 0x008b864e, rev);	/* color 424 r/g/b decimal 139 134 78 */
	coloradd("lavender", 0x00e6e6fa, rev);	/* color 425 r/g/b decimal 230 230 250 */
	coloradd("lavender blush", 0x00fff0f5, rev);	/* color 426 r/g/b decimal 255 240 245 */
	coloradd("LavenderBlush", 0x00fff0f5, rev);	/* color 427 r/g/b decimal 255 240 245 */
	coloradd("LavenderBlush1", 0x00fff0f5, rev);	/* color 428 r/g/b decimal 255 240 245 */
	coloradd("LavenderBlush2", 0x00eee0e5, rev);	/* color 429 r/g/b decimal 238 224 229 */
	coloradd("LavenderBlush3", 0x00cdc1c5, rev);	/* color 430 r/g/b decimal 205 193 197 */
	coloradd("LavenderBlush4", 0x008b8386, rev);	/* color 431 r/g/b decimal 139 131 134 */
	coloradd("lawn green", 0x007cfc00, rev);	/* color 432 r/g/b decimal 124 252 0 */
	coloradd("LawnGreen", 0x007cfc00, rev);	/* color 433 r/g/b decimal 124 252 0 */
	coloradd("lemon chiffon", 0x00fffacd, rev);	/* color 434 r/g/b decimal 255 250 205 */
	coloradd("LemonChiffon", 0x00fffacd, rev);	/* color 435 r/g/b decimal 255 250 205 */
	coloradd("LemonChiffon1", 0x00fffacd, rev);	/* color 436 r/g/b decimal 255 250 205 */
	coloradd("LemonChiffon2", 0x00eee9bf, rev);	/* color 437 r/g/b decimal 238 233 191 */
	coloradd("LemonChiffon3", 0x00cdc9a5, rev);	/* color 438 r/g/b decimal 205 201 165 */
	coloradd("LemonChiffon4", 0x008b8970, rev);	/* color 439 r/g/b decimal 139 137 112 */
	coloradd("light blue", 0x00add8e6, rev);	/* color 440 r/g/b decimal 173 216 230 */
	coloradd("light coral", 0x00f08080, rev);	/* color 441 r/g/b decimal 240 128 128 */
	coloradd("light cyan", 0x00e0ffff, rev);	/* color 442 r/g/b decimal 224 255 255 */
	coloradd("light goldenrod", 0x00eedd82, rev);	/* color 443 r/g/b decimal 238 221 130 */
	coloradd("light goldenrod yellow", 0x00fafad2, rev);	/* color 444 r/g/b decimal 250 250 210 */
	coloradd("light gray", 0x00d3d3d3, rev);	/* color 445 r/g/b decimal 211 211 211 */
	coloradd("light green", 0x0090ee90, rev);	/* color 446 r/g/b decimal 144 238 144 */
	coloradd("light grey", 0x00d3d3d3, rev);	/* color 447 r/g/b decimal 211 211 211 */
	/* GCC-7 uses lightgrey but it should be LightGrey or "light grey", this patch to get GCC7 colorized */
	/* coloradd ("lightgrey", 0x00d3d3d3, rev);      color 447 r/g/b decimal 211 211 211 --> Not in standard definition */
	coloradd("light pink", 0x00ffb6c1, rev);	/* color 448 r/g/b decimal 255 182 193 */
	coloradd("light salmon", 0x00ffa07a, rev);	/* color 449 r/g/b decimal 255 160 122 */
	coloradd("light sea green", 0x0020b2aa, rev);	/* color 450 r/g/b decimal 32 178 170 */
	coloradd("light sky blue", 0x0087cefa, rev);	/* color 451 r/g/b decimal 135 206 250 */
	coloradd("light slate blue", 0x008470ff, rev);	/* color 452 r/g/b decimal 132 112 255 */
	coloradd("light slate gray", 0x00778899, rev);	/* color 453 r/g/b decimal 119 136 153 */
	coloradd("light slate grey", 0x00778899, rev);	/* color 454 r/g/b decimal 119 136 153 */
	coloradd("light steel blue", 0x00b0c4de, rev);	/* color 455 r/g/b decimal 176 196 222 */
	coloradd("light yellow", 0x00ffffe0, rev);	/* color 456 r/g/b decimal 255 255 224 */
	coloradd("LightBlue", 0x00add8e6, rev);	/* color 457 r/g/b decimal 173 216 230 */
	coloradd("LightBlue1", 0x00bfefff, rev);	/* color 458 r/g/b decimal 191 239 255 */
	coloradd("LightBlue2", 0x00b2dfee, rev);	/* color 459 r/g/b decimal 178 223 238 */
	coloradd("LightBlue3", 0x009ac0cd, rev);	/* color 460 r/g/b decimal 154 192 205 */
	coloradd("LightBlue4", 0x0068838b, rev);	/* color 461 r/g/b decimal 104 131 139 */
	coloradd("LightCoral", 0x00f08080, rev);	/* color 462 r/g/b decimal 240 128 128 */
	coloradd("LightCyan", 0x00e0ffff, rev);	/* color 463 r/g/b decimal 224 255 255 */
	coloradd("LightCyan1", 0x00e0ffff, rev);	/* color 464 r/g/b decimal 224 255 255 */
	coloradd("LightCyan2", 0x00d1eeee, rev);	/* color 465 r/g/b decimal 209 238 238 */
	coloradd("LightCyan3", 0x00b4cdcd, rev);	/* color 466 r/g/b decimal 180 205 205 */
	coloradd("LightCyan4", 0x007a8b8b, rev);	/* color 467 r/g/b decimal 122 139 139 */
	coloradd("LightGoldenrod", 0x00eedd82, rev);	/* color 468 r/g/b decimal 238 221 130 */
	coloradd("LightGoldenrod1", 0x00ffec8b, rev);	/* color 469 r/g/b decimal 255 236 139 */
	coloradd("LightGoldenrod2", 0x00eedc82, rev);	/* color 470 r/g/b decimal 238 220 130 */
	coloradd("LightGoldenrod3", 0x00cdbe70, rev);	/* color 471 r/g/b decimal 205 190 112 */
	coloradd("LightGoldenrod4", 0x008b814c, rev);	/* color 472 r/g/b decimal 139 129 76 */
	coloradd("LightGoldenrodYellow", 0x00fafad2, rev);	/* color 473 r/g/b decimal 250 250 210 */
	coloradd("LightGray", 0x00d3d3d3, rev);	/* color 474 r/g/b decimal 211 211 211 */
	coloradd("LightGreen", 0x0090ee90, rev);	/* color 475 r/g/b decimal 144 238 144 */
	coloradd("LightGrey", 0x00d3d3d3, rev);	/* color 476 r/g/b decimal 211 211 211 */
	coloradd("LightPink", 0x00ffb6c1, rev);	/* color 477 r/g/b decimal 255 182 193 */
	coloradd("LightPink1", 0x00ffaeb9, rev);	/* color 478 r/g/b decimal 255 174 185 */
	coloradd("LightPink2", 0x00eea2ad, rev);	/* color 479 r/g/b decimal 238 162 173 */
	coloradd("LightPink3", 0x00cd8c95, rev);	/* color 480 r/g/b decimal 205 140 149 */
	coloradd("LightPink4", 0x008b5f65, rev);	/* color 481 r/g/b decimal 139 95 101 */
	coloradd("LightSalmon", 0x00ffa07a, rev);	/* color 482 r/g/b decimal 255 160 122 */
	coloradd("LightSalmon1", 0x00ffa07a, rev);	/* color 483 r/g/b decimal 255 160 122 */
	coloradd("LightSalmon2", 0x00ee9572, rev);	/* color 484 r/g/b decimal 238 149 114 */
	coloradd("LightSalmon3", 0x00cd8162, rev);	/* color 485 r/g/b decimal 205 129 98 */
	coloradd("LightSalmon4", 0x008b5742, rev);	/* color 486 r/g/b decimal 139 87 66 */
	coloradd("LightSeaGreen", 0x0020b2aa, rev);	/* color 487 r/g/b decimal 32 178 170 */
	coloradd("LightSkyBlue", 0x0087cefa, rev);	/* color 488 r/g/b decimal 135 206 250 */
	coloradd("LightSkyBlue1", 0x00b0e2ff, rev);	/* color 489 r/g/b decimal 176 226 255 */
	coloradd("LightSkyBlue2", 0x00a4d3ee, rev);	/* color 490 r/g/b decimal 164 211 238 */
	coloradd("LightSkyBlue3", 0x008db6cd, rev);	/* color 491 r/g/b decimal 141 182 205 */
	coloradd("LightSkyBlue4", 0x00607b8b, rev);	/* color 492 r/g/b decimal 96 123 139 */
	coloradd("LightSlateBlue", 0x008470ff, rev);	/* color 493 r/g/b decimal 132 112 255 */
	coloradd("LightSlateGray", 0x00778899, rev);	/* color 494 r/g/b decimal 119 136 153 */
	coloradd("LightSlateGrey", 0x00778899, rev);	/* color 495 r/g/b decimal 119 136 153 */
	coloradd("LightSteelBlue", 0x00b0c4de, rev);	/* color 496 r/g/b decimal 176 196 222 */
	coloradd("LightSteelBlue1", 0x00cae1ff, rev);	/* color 497 r/g/b decimal 202 225 255 */
	coloradd("LightSteelBlue2", 0x00bcd2ee, rev);	/* color 498 r/g/b decimal 188 210 238 */
	coloradd("LightSteelBlue3", 0x00a2b5cd, rev);	/* color 499 r/g/b decimal 162 181 205 */
	coloradd("LightSteelBlue4", 0x006e7b8b, rev);	/* color 500 r/g/b decimal 110 123 139 */
	coloradd("LightYellow", 0x00ffffe0, rev);	/* color 501 r/g/b decimal 255 255 224 */
	coloradd("LightYellow1", 0x00ffffe0, rev);	/* color 502 r/g/b decimal 255 255 224 */
	coloradd("LightYellow2", 0x00eeeed1, rev);	/* color 503 r/g/b decimal 238 238 209 */
	coloradd("LightYellow3", 0x00cdcdb4, rev);	/* color 504 r/g/b decimal 205 205 180 */
	coloradd("LightYellow4", 0x008b8b7a, rev);	/* color 505 r/g/b decimal 139 139 122 */
	coloradd("lime", 0x0000ff00, rev);	/* color 506 r/g/b decimal 0 255 0 */
	coloradd("lime green", 0x0032cd32, rev);	/* color 507 r/g/b decimal 50 205 50 */
	coloradd("LimeGreen", 0x0032cd32, rev);	/* color 508 r/g/b decimal 50 205 50 */
	coloradd("linen", 0x00faf0e6, rev);	/* color 509 r/g/b decimal 250 240 230 */
	coloradd("magenta", 0x00ff00ff, rev);	/* color 510 r/g/b decimal 255 0 255 */
	coloradd("magenta1", 0x00ff00ff, rev);	/* color 511 r/g/b decimal 255 0 255 */
	coloradd("magenta2", 0x00ee00ee, rev);	/* color 512 r/g/b decimal 238 0 238 */
	coloradd("magenta3", 0x00cd00cd, rev);	/* color 513 r/g/b decimal 205 0 205 */
	coloradd("magenta4", 0x008b008b, rev);	/* color 514 r/g/b decimal 139 0 139 */
	coloradd("maroon", 0x00b03060, rev);	/* color 515 r/g/b decimal 176 48 96 */
	coloradd("maroon1", 0x00ff34b3, rev);	/* color 516 r/g/b decimal 255 52 179 */
	coloradd("maroon2", 0x00ee30a7, rev);	/* color 517 r/g/b decimal 238 48 167 */
	coloradd("maroon3", 0x00cd2990, rev);	/* color 518 r/g/b decimal 205 41 144 */
	coloradd("maroon4", 0x008b1c62, rev);	/* color 519 r/g/b decimal 139 28 98 */
	coloradd("medium aquamarine", 0x0066cdaa, rev);	/* color 520 r/g/b decimal 102 205 170 */
	coloradd("medium blue", 0x000000cd, rev);	/* color 521 r/g/b decimal 0 0 205 */
	coloradd("medium orchid", 0x00ba55d3, rev);	/* color 522 r/g/b decimal 186 85 211 */
	coloradd("medium purple", 0x009370db, rev);	/* color 523 r/g/b decimal 147 112 219 */
	coloradd("medium sea green", 0x003cb371, rev);	/* color 524 r/g/b decimal 60 179 113 */
	coloradd("medium slate blue", 0x007b68ee, rev);	/* color 525 r/g/b decimal 123 104 238 */
	coloradd("medium spring green", 0x0000fa9a, rev);	/* color 526 r/g/b decimal 0 250 154 */
	coloradd("medium turquoise", 0x0048d1cc, rev);	/* color 527 r/g/b decimal 72 209 204 */
	coloradd("medium violet red", 0x00c71585, rev);	/* color 528 r/g/b decimal 199 21 133 */
	coloradd("MediumAquamarine", 0x0066cdaa, rev);	/* color 529 r/g/b decimal 102 205 170 */
	coloradd("MediumBlue", 0x000000cd, rev);	/* color 530 r/g/b decimal 0 0 205 */
	coloradd("MediumOrchid", 0x00ba55d3, rev);	/* color 531 r/g/b decimal 186 85 211 */
	coloradd("MediumOrchid1", 0x00e066ff, rev);	/* color 532 r/g/b decimal 224 102 255 */
	coloradd("MediumOrchid2", 0x00d15fee, rev);	/* color 533 r/g/b decimal 209 95 238 */
	coloradd("MediumOrchid3", 0x00b452cd, rev);	/* color 534 r/g/b decimal 180 82 205 */
	coloradd("MediumOrchid4", 0x007a378b, rev);	/* color 535 r/g/b decimal 122 55 139 */
	coloradd("MediumPurple", 0x009370db, rev);	/* color 536 r/g/b decimal 147 112 219 */
	coloradd("MediumPurple1", 0x00ab82ff, rev);	/* color 537 r/g/b decimal 171 130 255 */
	coloradd("MediumPurple2", 0x009f79ee, rev);	/* color 538 r/g/b decimal 159 121 238 */
	coloradd("MediumPurple3", 0x008968cd, rev);	/* color 539 r/g/b decimal 137 104 205 */
	coloradd("MediumPurple4", 0x005d478b, rev);	/* color 540 r/g/b decimal 93 71 139 */
	coloradd("MediumSeaGreen", 0x003cb371, rev);	/* color 541 r/g/b decimal 60 179 113 */
	coloradd("MediumSlateBlue", 0x007b68ee, rev);	/* color 542 r/g/b decimal 123 104 238 */
	coloradd("MediumSpringGreen", 0x0000fa9a, rev);	/* color 543 r/g/b decimal 0 250 154 */
	coloradd("MediumTurquoise", 0x0048d1cc, rev);	/* color 544 r/g/b decimal 72 209 204 */
	coloradd("MediumVioletRed", 0x00c71585, rev);	/* color 545 r/g/b decimal 199 21 133 */
	coloradd("midnight blue", 0x00191970, rev);	/* color 546 r/g/b decimal 25 25 112 */
	coloradd("MidnightBlue", 0x00191970, rev);	/* color 547 r/g/b decimal 25 25 112 */
	coloradd("mint cream", 0x00f5fffa, rev);	/* color 548 r/g/b decimal 245 255 250 */
	coloradd("MintCream", 0x00f5fffa, rev);	/* color 549 r/g/b decimal 245 255 250 */
	coloradd("misty rose", 0x00ffe4e1, rev);	/* color 550 r/g/b decimal 255 228 225 */
	coloradd("MistyRose", 0x00ffe4e1, rev);	/* color 551 r/g/b decimal 255 228 225 */
	coloradd("MistyRose1", 0x00ffe4e1, rev);	/* color 552 r/g/b decimal 255 228 225 */
	coloradd("MistyRose2", 0x00eed5d2, rev);	/* color 553 r/g/b decimal 238 213 210 */
	coloradd("MistyRose3", 0x00cdb7b5, rev);	/* color 554 r/g/b decimal 205 183 181 */
	coloradd("MistyRose4", 0x008b7d7b, rev);	/* color 555 r/g/b decimal 139 125 123 */
	coloradd("moccasin", 0x00ffe4b5, rev);	/* color 556 r/g/b decimal 255 228 181 */
	coloradd("navajo white", 0x00ffdead, rev);	/* color 557 r/g/b decimal 255 222 173 */
	coloradd("NavajoWhite", 0x00ffdead, rev);	/* color 558 r/g/b decimal 255 222 173 */
	coloradd("NavajoWhite1", 0x00ffdead, rev);	/* color 559 r/g/b decimal 255 222 173 */
	coloradd("NavajoWhite2", 0x00eecfa1, rev);	/* color 560 r/g/b decimal 238 207 161 */
	coloradd("NavajoWhite3", 0x00cdb38b, rev);	/* color 561 r/g/b decimal 205 179 139 */
	coloradd("NavajoWhite4", 0x008b795e, rev);	/* color 562 r/g/b decimal 139 121 94 */
	coloradd("navy", 0x00000080, rev);	/* color 563 r/g/b decimal 0 0 128 */
	coloradd("navy blue", 0x00000080, rev);	/* color 564 r/g/b decimal 0 0 128 */
	coloradd("NavyBlue", 0x00000080, rev);	/* color 565 r/g/b decimal 0 0 128 */
	coloradd("old lace", 0x00fdf5e6, rev);	/* color 566 r/g/b decimal 253 245 230 */
	coloradd("OldLace", 0x00fdf5e6, rev);	/* color 567 r/g/b decimal 253 245 230 */
	coloradd("olive", 0x00808000, rev);	/* color 568 r/g/b decimal 128 128 0 */
	coloradd("olive drab", 0x006b8e23, rev);	/* color 569 r/g/b decimal 107 142 35 */
	coloradd("OliveDrab", 0x006b8e23, rev);	/* color 570 r/g/b decimal 107 142 35 */
	coloradd("OliveDrab1", 0x00c0ff3e, rev);	/* color 571 r/g/b decimal 192 255 62 */
	coloradd("OliveDrab2", 0x00b3ee3a, rev);	/* color 572 r/g/b decimal 179 238 58 */
	coloradd("OliveDrab3", 0x009acd32, rev);	/* color 573 r/g/b decimal 154 205 50 */
	coloradd("OliveDrab4", 0x00698b22, rev);	/* color 574 r/g/b decimal 105 139 34 */
	coloradd("orange", 0x00ffa500, rev);	/* color 575 r/g/b decimal 255 165 0 */
	coloradd("orange red", 0x00ff4500, rev);	/* color 576 r/g/b decimal 255 69 0 */
	coloradd("orange1", 0x00ffa500, rev);	/* color 577 r/g/b decimal 255 165 0 */
	coloradd("orange2", 0x00ee9a00, rev);	/* color 578 r/g/b decimal 238 154 0 */
	coloradd("orange3", 0x00cd8500, rev);	/* color 579 r/g/b decimal 205 133 0 */
	coloradd("orange4", 0x008b5a00, rev);	/* color 580 r/g/b decimal 139 90 0 */
	coloradd("OrangeRed", 0x00ff4500, rev);	/* color 581 r/g/b decimal 255 69 0 */
	coloradd("OrangeRed1", 0x00ff4500, rev);	/* color 582 r/g/b decimal 255 69 0 */
	coloradd("OrangeRed2", 0x00ee4000, rev);	/* color 583 r/g/b decimal 238 64 0 */
	coloradd("OrangeRed3", 0x00cd3700, rev);	/* color 584 r/g/b decimal 205 55 0 */
	coloradd("OrangeRed4", 0x008b2500, rev);	/* color 585 r/g/b decimal 139 37 0 */
	coloradd("orchid", 0x00da70d6, rev);	/* color 586 r/g/b decimal 218 112 214 */
	coloradd("orchid1", 0x00ff83fa, rev);	/* color 587 r/g/b decimal 255 131 250 */
	coloradd("orchid2", 0x00ee7ae9, rev);	/* color 588 r/g/b decimal 238 122 233 */
	coloradd("orchid3", 0x00cd69c9, rev);	/* color 589 r/g/b decimal 205 105 201 */
	coloradd("orchid4", 0x008b4789, rev);	/* color 590 r/g/b decimal 139 71 137 */
	coloradd("pale goldenrod", 0x00eee8aa, rev);	/* color 591 r/g/b decimal 238 232 170 */
	coloradd("pale green", 0x0098fb98, rev);	/* color 592 r/g/b decimal 152 251 152 */
	coloradd("pale turquoise", 0x00afeeee, rev);	/* color 593 r/g/b decimal 175 238 238 */
	coloradd("pale violet red", 0x00db7093, rev);	/* color 594 r/g/b decimal 219 112 147 */
	coloradd("PaleGoldenrod", 0x00eee8aa, rev);	/* color 595 r/g/b decimal 238 232 170 */
	coloradd("PaleGreen", 0x0098fb98, rev);	/* color 596 r/g/b decimal 152 251 152 */
	coloradd("PaleGreen1", 0x009aff9a, rev);	/* color 597 r/g/b decimal 154 255 154 */
	coloradd("PaleGreen2", 0x0090ee90, rev);	/* color 598 r/g/b decimal 144 238 144 */
	coloradd("PaleGreen3", 0x007ccd7c, rev);	/* color 599 r/g/b decimal 124 205 124 */
	coloradd("PaleGreen4", 0x00548b54, rev);	/* color 600 r/g/b decimal 84 139 84 */
	coloradd("PaleTurquoise", 0x00afeeee, rev);	/* color 601 r/g/b decimal 175 238 238 */
	coloradd("PaleTurquoise1", 0x00bbffff, rev);	/* color 602 r/g/b decimal 187 255 255 */
	coloradd("PaleTurquoise2", 0x00aeeeee, rev);	/* color 603 r/g/b decimal 174 238 238 */
	coloradd("PaleTurquoise3", 0x0096cdcd, rev);	/* color 604 r/g/b decimal 150 205 205 */
	coloradd("PaleTurquoise4", 0x00668b8b, rev);	/* color 605 r/g/b decimal 102 139 139 */
	coloradd("PaleVioletRed", 0x00db7093, rev);	/* color 606 r/g/b decimal 219 112 147 */
	coloradd("PaleVioletRed1", 0x00ff82ab, rev);	/* color 607 r/g/b decimal 255 130 171 */
	coloradd("PaleVioletRed2", 0x00ee799f, rev);	/* color 608 r/g/b decimal 238 121 159 */
	coloradd("PaleVioletRed3", 0x00cd6889, rev);	/* color 609 r/g/b decimal 205 104 137 */
	coloradd("PaleVioletRed4", 0x008b475d, rev);	/* color 610 r/g/b decimal 139 71 93 */
	coloradd("papaya whip", 0x00ffefd5, rev);	/* color 611 r/g/b decimal 255 239 213 */
	coloradd("PapayaWhip", 0x00ffefd5, rev);	/* color 612 r/g/b decimal 255 239 213 */
	coloradd("peach puff", 0x00ffdab9, rev);	/* color 613 r/g/b decimal 255 218 185 */
	coloradd("PeachPuff", 0x00ffdab9, rev);	/* color 614 r/g/b decimal 255 218 185 */
	coloradd("PeachPuff1", 0x00ffdab9, rev);	/* color 615 r/g/b decimal 255 218 185 */
	coloradd("PeachPuff2", 0x00eecbad, rev);	/* color 616 r/g/b decimal 238 203 173 */
	coloradd("PeachPuff3", 0x00cdaf95, rev);	/* color 617 r/g/b decimal 205 175 149 */
	coloradd("PeachPuff4", 0x008b7765, rev);	/* color 618 r/g/b decimal 139 119 101 */
	coloradd("peru", 0x00cd853f, rev);	/* color 619 r/g/b decimal 205 133 63 */
	coloradd("pink", 0x00ffc0cb, rev);	/* color 620 r/g/b decimal 255 192 203 */
	coloradd("pink1", 0x00ffb5c5, rev);	/* color 621 r/g/b decimal 255 181 197 */
	coloradd("pink2", 0x00eea9b8, rev);	/* color 622 r/g/b decimal 238 169 184 */
	coloradd("pink3", 0x00cd919e, rev);	/* color 623 r/g/b decimal 205 145 158 */
	coloradd("pink4", 0x008b636c, rev);	/* color 624 r/g/b decimal 139 99 108 */
	coloradd("plum", 0x00dda0dd, rev);	/* color 625 r/g/b decimal 221 160 221 */
	coloradd("plum1", 0x00ffbbff, rev);	/* color 626 r/g/b decimal 255 187 255 */
	coloradd("plum2", 0x00eeaeee, rev);	/* color 627 r/g/b decimal 238 174 238 */
	coloradd("plum3", 0x00cd96cd, rev);	/* color 628 r/g/b decimal 205 150 205 */
	coloradd("plum4", 0x008b668b, rev);	/* color 629 r/g/b decimal 139 102 139 */
	coloradd("powder blue", 0x00b0e0e6, rev);	/* color 630 r/g/b decimal 176 224 230 */
	coloradd("PowderBlue", 0x00b0e0e6, rev);	/* color 631 r/g/b decimal 176 224 230 */
	coloradd("purple", 0x00a020f0, rev);	/* color 632 r/g/b decimal 160 32 240 */
	coloradd("purple1", 0x009b30ff, rev);	/* color 633 r/g/b decimal 155 48 255 */
	coloradd("purple2", 0x00912cee, rev);	/* color 634 r/g/b decimal 145 44 238 */
	coloradd("purple3", 0x007d26cd, rev);	/* color 635 r/g/b decimal 125 38 205 */
	coloradd("purple4", 0x00551a8b, rev);	/* color 636 r/g/b decimal 85 26 139 */
	coloradd("rebecca purple", 0x00663399, rev);	/* color 637 r/g/b decimal 102 51 153 */
	coloradd("RebeccaPurple", 0x00663399, rev);	/* color 638 r/g/b decimal 102 51 153 */
	coloradd("red", 0x00ff0000, rev);	/* color 639 r/g/b decimal 255 0 0 */
	coloradd("red1", 0x00ff0000, rev);	/* color 640 r/g/b decimal 255 0 0 */
	coloradd("red2", 0x00ee0000, rev);	/* color 641 r/g/b decimal 238 0 0 */
	coloradd("red3", 0x00cd0000, rev);	/* color 642 r/g/b decimal 205 0 0 */
	coloradd("red4", 0x008b0000, rev);	/* color 643 r/g/b decimal 139 0 0 */
	coloradd("rosy brown", 0x00bc8f8f, rev);	/* color 644 r/g/b decimal 188 143 143 */
	coloradd("RosyBrown", 0x00bc8f8f, rev);	/* color 645 r/g/b decimal 188 143 143 */
	coloradd("RosyBrown1", 0x00ffc1c1, rev);	/* color 646 r/g/b decimal 255 193 193 */
	coloradd("RosyBrown2", 0x00eeb4b4, rev);	/* color 647 r/g/b decimal 238 180 180 */
	coloradd("RosyBrown3", 0x00cd9b9b, rev);	/* color 648 r/g/b decimal 205 155 155 */
	coloradd("RosyBrown4", 0x008b6969, rev);	/* color 649 r/g/b decimal 139 105 105 */
	coloradd("royal blue", 0x004169e1, rev);	/* color 650 r/g/b decimal 65 105 225 */
	coloradd("RoyalBlue", 0x004169e1, rev);	/* color 651 r/g/b decimal 65 105 225 */
	coloradd("RoyalBlue1", 0x004876ff, rev);	/* color 652 r/g/b decimal 72 118 255 */
	coloradd("RoyalBlue2", 0x00436eee, rev);	/* color 653 r/g/b decimal 67 110 238 */
	coloradd("RoyalBlue3", 0x003a5fcd, rev);	/* color 654 r/g/b decimal 58 95 205 */
	coloradd("RoyalBlue4", 0x0027408b, rev);	/* color 655 r/g/b decimal 39 64 139 */
	coloradd("saddle brown", 0x008b4513, rev);	/* color 656 r/g/b decimal 139 69 19 */
	coloradd("SaddleBrown", 0x008b4513, rev);	/* color 657 r/g/b decimal 139 69 19 */
	coloradd("salmon", 0x00fa8072, rev);	/* color 658 r/g/b decimal 250 128 114 */
	coloradd("salmon1", 0x00ff8c69, rev);	/* color 659 r/g/b decimal 255 140 105 */
	coloradd("salmon2", 0x00ee8262, rev);	/* color 660 r/g/b decimal 238 130 98 */
	coloradd("salmon3", 0x00cd7054, rev);	/* color 661 r/g/b decimal 205 112 84 */
	coloradd("salmon4", 0x008b4c39, rev);	/* color 662 r/g/b decimal 139 76 57 */
	coloradd("sandy brown", 0x00f4a460, rev);	/* color 663 r/g/b decimal 244 164 96 */
	coloradd("SandyBrown", 0x00f4a460, rev);	/* color 664 r/g/b decimal 244 164 96 */
	coloradd("sea green", 0x002e8b57, rev);	/* color 665 r/g/b decimal 46 139 87 */
	coloradd("SeaGreen", 0x002e8b57, rev);	/* color 666 r/g/b decimal 46 139 87 */
	coloradd("SeaGreen1", 0x0054ff9f, rev);	/* color 667 r/g/b decimal 84 255 159 */
	coloradd("SeaGreen2", 0x004eee94, rev);	/* color 668 r/g/b decimal 78 238 148 */
	coloradd("SeaGreen3", 0x0043cd80, rev);	/* color 669 r/g/b decimal 67 205 128 */
	coloradd("SeaGreen4", 0x002e8b57, rev);	/* color 670 r/g/b decimal 46 139 87 */
	coloradd("seashell", 0x00fff5ee, rev);	/* color 671 r/g/b decimal 255 245 238 */
	coloradd("seashell1", 0x00fff5ee, rev);	/* color 672 r/g/b decimal 255 245 238 */
	coloradd("seashell2", 0x00eee5de, rev);	/* color 673 r/g/b decimal 238 229 222 */
	coloradd("seashell3", 0x00cdc5bf, rev);	/* color 674 r/g/b decimal 205 197 191 */
	coloradd("seashell4", 0x008b8682, rev);	/* color 675 r/g/b decimal 139 134 130 */
	coloradd("sienna", 0x00a0522d, rev);	/* color 676 r/g/b decimal 160 82 45 */
	coloradd("sienna1", 0x00ff8247, rev);	/* color 677 r/g/b decimal 255 130 71 */
	coloradd("sienna2", 0x00ee7942, rev);	/* color 678 r/g/b decimal 238 121 66 */
	coloradd("sienna3", 0x00cd6839, rev);	/* color 679 r/g/b decimal 205 104 57 */
	coloradd("sienna4", 0x008b4726, rev);	/* color 680 r/g/b decimal 139 71 38 */
	coloradd("silver", 0x00c0c0c0, rev);	/* color 681 r/g/b decimal 192 192 192 */
	coloradd("sky blue", 0x0087ceeb, rev);	/* color 682 r/g/b decimal 135 206 235 */
	coloradd("SkyBlue", 0x0087ceeb, rev);	/* color 683 r/g/b decimal 135 206 235 */
	coloradd("SkyBlue1", 0x0087ceff, rev);	/* color 684 r/g/b decimal 135 206 255 */
	coloradd("SkyBlue2", 0x007ec0ee, rev);	/* color 685 r/g/b decimal 126 192 238 */
	coloradd("SkyBlue3", 0x006ca6cd, rev);	/* color 686 r/g/b decimal 108 166 205 */
	coloradd("SkyBlue4", 0x004a708b, rev);	/* color 687 r/g/b decimal 74 112 139 */
	coloradd("slate blue", 0x006a5acd, rev);	/* color 688 r/g/b decimal 106 90 205 */
	coloradd("slate gray", 0x00708090, rev);	/* color 689 r/g/b decimal 112 128 144 */
	coloradd("slate grey", 0x00708090, rev);	/* color 690 r/g/b decimal 112 128 144 */
	coloradd("SlateBlue", 0x006a5acd, rev);	/* color 691 r/g/b decimal 106 90 205 */
	coloradd("SlateBlue1", 0x00836fff, rev);	/* color 692 r/g/b decimal 131 111 255 */
	coloradd("SlateBlue2", 0x007a67ee, rev);	/* color 693 r/g/b decimal 122 103 238 */
	coloradd("SlateBlue3", 0x006959cd, rev);	/* color 694 r/g/b decimal 105 89 205 */
	coloradd("SlateBlue4", 0x00473c8b, rev);	/* color 695 r/g/b decimal 71 60 139 */
	coloradd("SlateGray", 0x00708090, rev);	/* color 696 r/g/b decimal 112 128 144 */
	coloradd("SlateGray1", 0x00c6e2ff, rev);	/* color 697 r/g/b decimal 198 226 255 */
	coloradd("SlateGray2", 0x00b9d3ee, rev);	/* color 698 r/g/b decimal 185 211 238 */
	coloradd("SlateGray3", 0x009fb6cd, rev);	/* color 699 r/g/b decimal 159 182 205 */
	coloradd("SlateGray4", 0x006c7b8b, rev);	/* color 700 r/g/b decimal 108 123 139 */
	coloradd("SlateGrey", 0x00708090, rev);	/* color 701 r/g/b decimal 112 128 144 */
	coloradd("snow", 0x00fffafa, rev);	/* color 702 r/g/b decimal 255 250 250 */
	coloradd("snow1", 0x00fffafa, rev);	/* color 703 r/g/b decimal 255 250 250 */
	coloradd("snow2", 0x00eee9e9, rev);	/* color 704 r/g/b decimal 238 233 233 */
	coloradd("snow3", 0x00cdc9c9, rev);	/* color 705 r/g/b decimal 205 201 201 */
	coloradd("snow4", 0x008b8989, rev);	/* color 706 r/g/b decimal 139 137 137 */
	coloradd("spring green", 0x0000ff7f, rev);	/* color 707 r/g/b decimal 0 255 127 */
	coloradd("SpringGreen", 0x0000ff7f, rev);	/* color 708 r/g/b decimal 0 255 127 */
	coloradd("SpringGreen1", 0x0000ff7f, rev);	/* color 709 r/g/b decimal 0 255 127 */
	coloradd("SpringGreen2", 0x0000ee76, rev);	/* color 710 r/g/b decimal 0 238 118 */
	coloradd("SpringGreen3", 0x0000cd66, rev);	/* color 711 r/g/b decimal 0 205 102 */
	coloradd("SpringGreen4", 0x00008b45, rev);	/* color 712 r/g/b decimal 0 139 69 */
	coloradd("steel blue", 0x004682b4, rev);	/* color 713 r/g/b decimal 70 130 180 */
	coloradd("SteelBlue", 0x004682b4, rev);	/* color 714 r/g/b decimal 70 130 180 */
	coloradd("SteelBlue1", 0x0063b8ff, rev);	/* color 715 r/g/b decimal 99 184 255 */
	coloradd("SteelBlue2", 0x005cacee, rev);	/* color 716 r/g/b decimal 92 172 238 */
	coloradd("SteelBlue3", 0x004f94cd, rev);	/* color 717 r/g/b decimal 79 148 205 */
	coloradd("SteelBlue4", 0x0036648b, rev);	/* color 718 r/g/b decimal 54 100 139 */
	coloradd("tan", 0x00d2b48c, rev);	/* color 719 r/g/b decimal 210 180 140 */
	coloradd("tan1", 0x00ffa54f, rev);	/* color 720 r/g/b decimal 255 165 79 */
	coloradd("tan2", 0x00ee9a49, rev);	/* color 721 r/g/b decimal 238 154 73 */
	coloradd("tan3", 0x00cd853f, rev);	/* color 722 r/g/b decimal 205 133 63 */
	coloradd("tan4", 0x008b5a2b, rev);	/* color 723 r/g/b decimal 139 90 43 */
	coloradd("teal", 0x00008080, rev);	/* color 724 r/g/b decimal 0 128 128 */
	coloradd("thistle", 0x00d8bfd8, rev);	/* color 725 r/g/b decimal 216 191 216 */
	coloradd("thistle1", 0x00ffe1ff, rev);	/* color 726 r/g/b decimal 255 225 255 */
	coloradd("thistle2", 0x00eed2ee, rev);	/* color 727 r/g/b decimal 238 210 238 */
	coloradd("thistle3", 0x00cdb5cd, rev);	/* color 728 r/g/b decimal 205 181 205 */
	coloradd("thistle4", 0x008b7b8b, rev);	/* color 729 r/g/b decimal 139 123 139 */
	coloradd("tomato", 0x00ff6347, rev);	/* color 730 r/g/b decimal 255 99 71 */
	coloradd("tomato1", 0x00ff6347, rev);	/* color 731 r/g/b decimal 255 99 71 */
	coloradd("tomato2", 0x00ee5c42, rev);	/* color 732 r/g/b decimal 238 92 66 */
	coloradd("tomato3", 0x00cd4f39, rev);	/* color 733 r/g/b decimal 205 79 57 */
	coloradd("tomato4", 0x008b3626, rev);	/* color 734 r/g/b decimal 139 54 38 */
	coloradd("turquoise", 0x0040e0d0, rev);	/* color 735 r/g/b decimal 64 224 208 */
	coloradd("turquoise1", 0x0000f5ff, rev);	/* color 736 r/g/b decimal 0 245 255 */
	coloradd("turquoise2", 0x0000e5ee, rev);	/* color 737 r/g/b decimal 0 229 238 */
	coloradd("turquoise3", 0x0000c5cd, rev);	/* color 738 r/g/b decimal 0 197 205 */
	coloradd("turquoise4", 0x0000868b, rev);	/* color 739 r/g/b decimal 0 134 139 */
	coloradd("violet", 0x00ee82ee, rev);	/* color 740 r/g/b decimal 238 130 238 */
	coloradd("violet red", 0x00d02090, rev);	/* color 741 r/g/b decimal 208 32 144 */
	coloradd("VioletRed", 0x00d02090, rev);	/* color 742 r/g/b decimal 208 32 144 */
	coloradd("VioletRed1", 0x00ff3e96, rev);	/* color 743 r/g/b decimal 255 62 150 */
	coloradd("VioletRed2", 0x00ee3a8c, rev);	/* color 744 r/g/b decimal 238 58 140 */
	coloradd("VioletRed3", 0x00cd3278, rev);	/* color 745 r/g/b decimal 205 50 120 */
	coloradd("VioletRed4", 0x008b2252, rev);	/* color 746 r/g/b decimal 139 34 82 */
	coloradd("web gray", 0x00808080, rev);	/* color 747 r/g/b decimal 128 128 128 */
	coloradd("web green", 0x00008000, rev);	/* color 748 r/g/b decimal 0 128 0 */
	coloradd("web grey", 0x00808080, rev);	/* color 749 r/g/b decimal 128 128 128 */
	coloradd("web maroon", 0x00800000, rev);	/* color 750 r/g/b decimal 128 0 0 */
	coloradd("web purple", 0x00800080, rev);	/* color 751 r/g/b decimal 128 0 128 */
	coloradd("WebGray", 0x00808080, rev);	/* color 752 r/g/b decimal 128 128 128 */
	coloradd("WebGreen", 0x00008000, rev);	/* color 753 r/g/b decimal 0 128 0 */
	coloradd("WebGrey", 0x00808080, rev);	/* color 754 r/g/b decimal 128 128 128 */
	coloradd("WebMaroon", 0x00800000, rev);	/* color 755 r/g/b decimal 128 0 0 */
	coloradd("WebPurple", 0x00800080, rev);	/* color 756 r/g/b decimal 128 0 128 */
	coloradd("wheat", 0x00f5deb3, rev);	/* color 757 r/g/b decimal 245 222 179 */
	coloradd("wheat1", 0x00ffe7ba, rev);	/* color 758 r/g/b decimal 255 231 186 */
	coloradd("wheat2", 0x00eed8ae, rev);	/* color 759 r/g/b decimal 238 216 174 */
	coloradd("wheat3", 0x00cdba96, rev);	/* color 760 r/g/b decimal 205 186 150 */
	coloradd("wheat4", 0x008b7e66, rev);	/* color 761 r/g/b decimal 139 126 102 */
	coloradd("white", 0x00ffffff, rev);	/* color 762 r/g/b decimal 255 255 255 */
	coloradd("white smoke", 0x00f5f5f5, rev);	/* color 763 r/g/b decimal 245 245 245 */
	coloradd("WhiteSmoke", 0x00f5f5f5, rev);	/* color 764 r/g/b decimal 245 245 245 */
	coloradd("x11 gray", 0x00bebebe, rev);	/* color 765 r/g/b decimal 190 190 190 */
	coloradd("x11 green", 0x0000ff00, rev);	/* color 766 r/g/b decimal 0 255 0 */
	coloradd("x11 grey", 0x00bebebe, rev);	/* color 767 r/g/b decimal 190 190 190 */
	coloradd("x11 maroon", 0x00b03060, rev);	/* color 768 r/g/b decimal 176 48 96 */
	coloradd("x11 purple", 0x00a020f0, rev);	/* color 769 r/g/b decimal 160 32 240 */
	coloradd("X11Gray", 0x00bebebe, rev);	/* color 770 r/g/b decimal 190 190 190 */
	coloradd("X11Green", 0x0000ff00, rev);	/* color 771 r/g/b decimal 0 255 0 */
	coloradd("X11Grey", 0x00bebebe, rev);	/* color 772 r/g/b decimal 190 190 190 */
	coloradd("X11Maroon", 0x00b03060, rev);	/* color 773 r/g/b decimal 176 48 96 */
	coloradd("X11Purple", 0x00a020f0, rev);	/* color 774 r/g/b decimal 160 32 240 */
	coloradd("yellow", 0x00ffff00, rev);	/* color 775 r/g/b decimal 255 255 0 */
	coloradd("yellow green", 0x009acd32, rev);	/* color 776 r/g/b decimal 154 205 50 */
	coloradd("yellow1", 0x00ffff00, rev);	/* color 777 r/g/b decimal 255 255 0 */
	coloradd("yellow2", 0x00eeee00, rev);	/* color 778 r/g/b decimal 238 238 0 */
	coloradd("yellow3", 0x00cdcd00, rev);	/* color 779 r/g/b decimal 205 205 0 */
	coloradd("yellow4", 0x008b8b00, rev);	/* color 780 r/g/b decimal 139 139 0 */
	coloradd("YellowGreen", 0x009acd32, rev);	/* color 781 r/g/b decimal 154 205 50 */
	return;
}

/* add 1 color to database */
static void coloradd(const char *name, int code, int rev)
{
	char buf[64];
	char *s = NULL;
	int i = 0;
	int j = 0;

	if (rev) {
		return;
	}

	s = dp_uniqstr((char *)name);
	splay_tree_insert(gucolor,	/* splay_tree */
			  (splay_tree_key) s, (splay_tree_value) code);

	/* workaround GCC colorname bug to add also colornames with a space
	 * " " as one without a space by transforming the name.
	 */
	s = strchr(name, (int)' ');

	if (rev == 0) {
		if (s) {
			/* strip sp from name */
			memset(buf, 0, 64);
			s = (char *)name;
			j = 0;
			for (i = 0; i < 64 - 1; i++) {
				if (*s == '\0') {
					break;
				}
				if (*s == ' ') {
					/* skip */
				} else {
					buf[j] = (*s);
					j++;
				}
				s++;
			}
			/* strdup (buf); */
			s = dp_uniqstr((char *)buf);
			splay_tree_insert(gucolor,	/* splay_tree */
					  (splay_tree_key) s, (splay_tree_value) code);
		}
	}

	return;
}

#include <math.h>

/* input h must be in range 0...360 degrees */
static void hsv2rgb(float *r, float *g, float *b, float h, float s, float v)
{
	int i = 0;
	float f = 0;
	float p = 0;
	float q = 0;
	float t = 0;

	if (s == 0) {
		/* achromatic (grey) */
		*r = *g = *b = v;
		return;
	}

	h /= 60;		/* sector 0 to 5 */
	i = floor(h);
	f = h - i;		/* factorial part of h */
	p = v * (1 - s);
	q = v * (1 - s * f);
	t = v * (1 - s * (1 - f));

	switch (i) {
	case 0:
		*r = v;
		*g = t;
		*b = p;
		break;
	case 1:
		*r = q;
		*g = v;
		*b = p;
		break;
	case 2:
		*r = p;
		*g = v;
		*b = t;
		break;
	case 3:
		*r = p;
		*g = q;
		*b = v;
		break;
	case 4:
		*r = t;
		*g = p;
		*b = v;
		break;
	default:		/* case 5: */
		*r = v;
		*g = p;
		*b = q;
		break;
	}
	return;
}

/* search colorname in database and return argb or -1 on unknown color name or colorlist */
 /* in a colorlist a gradient is possible
  * with colors seperated by ':'
  * and color specified as <color>;value
  * where color is a known color name or hex code
  * and value a floating point number of percentage
  * and all floating point numbers must be 1
  * example with 30% red and the rest green:
  * bgcolor="#ff0000;0.3:#00ff00";
  * return -2 for color "none"
  */
/* todo gradientangle */
/* todo /xxx/yyy and //yyy colors */
int dp_colorcode(const char *name)
{
	splay_tree_node spn = (splay_tree_node) 0;
	int n = 0;
	unsigned int red = 0;
	unsigned int green = 0;
	unsigned int blue = 0;
	unsigned int aa = 0;
	int pe = 0;
	float hnum = 0;
	float snum = 0;
	float vnum = 0;
	float rf = 0;
	float gf = 0;
	float bf = 0;

	if (name == NULL) {
		return ((int)-1);
	}

	/* check for "" */
	if (strlen(name) == 0) {
		/* unknown color, use default */
		return ((int)-3);
	}

	/* check for cr in colorname */
	if (strchr(name, '\n')) {
		/* unknown color, use default */
		return ((int)-3);
	}

	if (gucolor == NULL) {
		color_init();
	}

	/* color for drawing no border for example. special case. */
	if (strcasecmp(name, "none") == 0) {
		return ((int)-3);
	}

	if (strcasecmp(name, "invis") == 0) {
		return ((int)-3);
	}

	/* background color, bgcolor */
	if (strcasecmp(name, "transparent") == 0) {
		return ((int)-3);
	}

	/* check if colorlist with a ':' with optional ';' */
	if (strchr(name, ':')) {
		/* unknown color use default */
		return ((int)-3);
	}

	/* check if colorlist with a '/' */
	if (strchr(name, '/')) {
		/* unknown color use default */
		return ((int)-3);
	}

	/* check for hexa, and it can be like this #ffffff:#333333 */
	if (name[0] == '#') {
		/* todo  n = sscanf (name, "#%02x%02x%02x:#%02x%02x%02x",&red0, &green0, &blue0, &red, &green, &blue); */
		pe = 0;
		/* assume html color #rrggbb or #rrggbbaa */
		if (strlen(name) == 9) {
			n = sscanf(name, "#%02x%02x%02x%02x", &red, &green, &blue, &aa);
			if (n != 4) {
				pe = 1;
			}
		} else if (strlen(name) == 7) {
			n = sscanf(name, "#%02x%02x%02x", &red, &green, &blue);
			if (n != 3) {
				pe = 1;
			}
		} else if (strlen(name) == 5) {
			red = 0;
			n = sscanf(name, "#%02x%02x", &green, &blue);
			if (n != 2) {
				pe = 1;
			}
		} else if (strlen(name) == 3) {
			red = 0;
			green = 0;
			n = sscanf(name, "#%02x", &blue);
			if (n != 1) {
				pe = 1;
			}
		} else {
			/* parse error */
			pe = 1;
		}

		if (pe) {
			return ((int)-1);
		}

		if (0) {
			printf("dot %s(): found aa=%02x rgb=#%02x%02x%02x\n", __func__, aa, red, green, blue);
		}

		return ((red << 16) | (green << 8) | blue);
	}

	/* check for float number as used in hsv color */
	if ((name[0] == '.') || (name[0] >= '0' && name[0] <= '9')) {
		/* try sep cahe ',' or ' ' */
		if (strchr(name, ',')) {
			n = sscanf(name, "%f,%f,%f", &hnum, &snum, &vnum);
		} else {
			n = sscanf(name, "%f %f %f", &hnum, &snum, &vnum);
		}

		if (n != 3) {
			/* parse error */
			return ((int)-1);
		}

		/* check range +0...1.0 */
		if (hnum < 0 || snum < 0 || vnum < 0) {
			/* parse error */
			return ((int)-1);
		}

		if (hnum > 1 || snum > 1 || vnum > 1) {
			/* parse error */
			return ((int)-1);
		}

		/* hsv is in rage 0...1, make h in ragen 0...360 degrees by multiply with 360 */
		hsv2rgb(&rf, &gf, &bf, hnum * 360, snum, vnum);
		rf = rf * 255;
		gf = gf * 255;
		bf = bf * 255;
		/* round float to nearest int number */
		rf = rint(rf);
		gf = rint(gf);
		bf = rint(bf);
		red = (int)rf;
		green = (int)gf;
		blue = (int)bf;

		if (0) {
			printf("dot %s(): found aa=%02x rgb=%02x%02x%02x %f,%f,%f from `%s'\n",
			       __func__, aa, red, green, blue, rf, gf, bf, name);
		}

		return ((red << 16) | (green << 8) | blue);
	}

	spn = splay_tree_lookup((splay_tree) gucolor, (splay_tree_key) name);

	if (spn) {
		return ((int)spn->value);
	}

	/* unknown color name */
	return ((int)-1);
}

/* find color, optional in a scheme */
int dp_findcolor(int scheme, char *str)
{
	long int n = 0;
	char **endstr = NULL;
	int n2 = 0;
	int ret = 0;

	/* try colorscheme if active */
	if (scheme) {
		errno = 0;
		n = strtol(str, endstr, 10);
		if ((errno == 0) && ((endstr) == NULL)) {
			n2 = (int)n;
			/* colorscheme color */
			ret = dp_colornscode(n2, scheme);
			if (ret != (-1)) {
				return (ret);
			}
		}
	}

	/* get argb value for x11 colorname */
	ret = dp_colorcode(str);
	if (ret != (-1)) {
		return (ret);
	}

	/* not found */
	return (-1);
}

/* end */
