
/*
 *  Copyright t lefering
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
 *  These are the four essential freedoms with GNU GPL software:
 *  1: freedom to run the program, for any purpose
 *  2: freedom to study how the program works, and change it to make it do what you wish
 *  3: freedom to redistribute copies to help your Free Software friends
 *  4: freedom to distribute copies of your modified versions to your Free Software friends
 *   ,           ,
 *  /             \
 * ((__-^^-,-^^-__))
 * `-_---'  `---_-'
 *  `--|o`   'o|--'
 *      \  `  /
 *       ): :(
 *       :o_o:
 *        "-"
 *
 * SPDX-License-Identifier: GPL-3.0+
 * License-Filename: LICENSE
 */

#include "config.h"

/* needed to get basename() from string.h
 * #define _GNU_SOURCE
 * basename() changed in g_path_get_basename()
 */

/* needed to get M_PI definition from math.h
 * #define _GNU_SOURCE
 * replaced with #define M_PI below after math.h
 */

/* needed to get the proto for strdup() in string.h
 * now strdup changed into calloc() and strcpy()
 * #define _POSIX_C_SOURCE 200809L
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <zlib.h>

/* math.h should have set this */
#ifndef M_PI
#define M_PI 3.141592
#endif

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <cairo.h>
#include <cairo-svg.h>

/* this should be the way check for glib version */
#if GLIB_CHECK_VERSION (2,30,0)
#ifdef WIN32
#else
#include <glib-unix.h>
#endif
#endif

/* check for gtk versions */
#if GTK_CHECK_VERSION (4,0,0)
#elif GTK_CHECK_VERSION (3,0,0)
#elif GTK_CHECK_VERSION (3,2,0)
#elif GTK_CHECK_VERSION (3,4,0)
#elif GTK_CHECK_VERSION (3,6,0)
#elif GTK_CHECK_VERSION (3,8,0)
#elif GTK_CHECK_VERSION (3,12,0)
#elif GTK_CHECK_VERSION (3,14,0)
#elif GTK_CHECK_VERSION (2,0,0)
#elif GTK_CHECK_VERSION (1,0,0)
#else
/* assume gtk-2 */
#endif

#include "splay-tree.h"
#include "main.h"
#include "hier.h"
#include "uniqnode.h"
#include "uniqstr.h"
#include "uniqgraph.h"
#include "bubbling.h"
#include "sugi.h"
#include "pos.h"
#include "gml_scanner.h"
#include "gml_parser.h"
#include "dpif.h"
#include "dot.tab.h"
#include "vcg.h"
#include "jgf.h"
#include "dpmem.h"

/* todo the pango font routines can be improved */

/*
 * a GTK font pattern. These have the syntax
 * fontname [properties] [fontsize]
 *
 * where fontname is the family name,
 * properties is a list of property values separated by spaces,
 * and fontsize is the point size.
 * The properties that you may specify for GTK font patterns are as follows:
 * Slant properties: ‘Italic’ or ‘Oblique’. If omitted, the default (roman) slant is implied.
 * Weight properties: ‘Bold’, ‘Book’, ‘Light’, ‘Medium’, ‘Semi-bold’, or ‘Ultra-light’. If omitted, ‘Medium’ weight is implied.
 * Width properties: ‘Semi-Condensed’ or ‘Condensed’. If omitted, a default width is used.
 * Here are some examples of GTK font patterns:
 * Monospace 12
 * Monospace Bold Italic 12
 */

#if 0				/* this does not work yet for windows, todo */
#ifdef WIN32

/* pango on wine has issues with font options, so use only a font name */

/* name of font to use, example "Sans" */
#define DEFAULT_FONTNAME "sans"

/* name of slant to use, example "Italic", "Oblique" or "Roman" */
#define DEFAULT_FONTSLANT " "

/* name of weight to use, example "Bold", "Book", "Light", "Medium", "Semi-bold", "Ultra-light" */
#define DEFAULT_FONTWEIGHT " "

/* name of condensed to use, example "Semi-Condensed", "Condensed" */
#define DEFAULT_FONTCONDENSED " "

/* font size to use, example "10", "18", "20" etc. */
#define DEFAULT_FONTSIZE "14"
#define DEFAULT_FONTSIZE_INT 14

#endif
#endif

/* Linux defaults */

/* name of font to use, example "Sans" */
#define DEFAULT_FONTNAME "sans"

/* name of slant to use, example "Italic", "Oblique" or "Roman" */
#define DEFAULT_FONTSLANT "roman"

/* name of weight to use, example "Bold", "Book", "Light", "Medium", "Semi-bold", "Ultra-light" */
#define DEFAULT_FONTWEIGHT "light"

/* name of condensed to use, example "Semi-Condensed", "Condensed" */
#define DEFAULT_FONTCONDENSED "condensed"

/* font size to use, example "10", "18", "20" etc. */
#define DEFAULT_FONTSIZE "12"
#define DEFAULT_FONTSIZE_INT 12

/* edge line thickness double value for example 0.5, 1.0, 1.5 */
#define DEFAULT_EDGE_THICKNESS 1.0

/* pixels in padding for gtk_box_pack try values 0, 1, 5, 20 */
#define PACKPADDING 0

/* window initial (x,y) size in pixels */
#define TOP_LEVEL_WINDOW_XSIZE 700
#define TOP_LEVEL_WINDOW_YSIZE 600

/* probed once to check if pango lib support markup overline="single" attribute */
static int pango_overline = -1;

/* last open/save dir */
static char *lastopendir = NULL;
static char *lastsavedir = NULL;

/* main argv[0] */
static char *argv0 = NULL;

/* debug output to stdout */
static int option_gdebug = 0;	/* 0,1,2 */

/* draw edgelines as soft splines */
static int option_splines = 1;

/* exposed size of draw area */
static int drawing_area_xsize = 0;
static int drawing_area_ysize = 0;

/* set if there is data to draw */
static int validdata = 0;

/* r/g/b of drawing alt color "grey82" */
static int altr = 0xd1;
static int altg = 0xd1;
static int altb = 0xd1;

/* zoom scaling factor changed by zoom slider */
static double zfactor = 1.0;

/* x offset changed by x slider */
static int vxmin = 0;

/* y offset changed by y slider */
static int vymin = 0;

/* top level window also used in maingtk2.c */
static GtkWidget *mainwindow1 = (GtkWidget *) 0;

/* where to draw */
static GtkWidget *drawingarea1 = (GtkWidget *) 0;

/* popup level window also used in maingtk2.c */
static GtkWidget *popupwindow1 = (GtkWidget *) 0;

/* edge label tickbox */
static GtkWidget *elabel1 = (GtkWidget *) 0;

/* position mode button */
static GtkWidget *posbutton = (GtkWidget *) 0;

/* status line gtk buffers */
static GtkTextBuffer *entry1buffer = NULL;
static char charentry1buffer[80];

/* old mouse (x,y) left button clicked used for dragging drawing */
static int mouse_oldx = 0;
static int mouse_oldy = 0;

/* if set, draw dummy nodes */
static int drawdummy = 0;

#if GTK_HAVE_API_VERSION_0 == 1
#warning "gtk-0 not implemented"
#endif

#if GTK_HAVE_API_VERSION_1 == 1
#warning "gtk-1 not implemented"
#endif

/* sliders */
#if GTK_HAVE_API_VERSION_2 == 1
static GtkObject *adjvscale1 = NULL;
static GtkObject *adjvscale2 = NULL;
static GtkObject *adjhscale1 = NULL;
#endif

#if GTK_HAVE_API_VERSION_3 == 1
static GtkAdjustment *adjvscale1 = NULL;
static GtkAdjustment *adjvscale2 = NULL;
static GtkAdjustment *adjhscale1 = NULL;
#endif

/* forward decl. */
static void do_clear_all(int mode);
static void top_level_window_main_quit(void);
static void on_top_level_window_open1_activate(GtkMenuItem * menuitem, gpointer user_data);
static void on_top_level_window_open2_activate(GtkMenuItem * menuitem, gpointer user_data);
static void on_top_level_window_open3_activate(GtkMenuItem * menuitem, gpointer user_data);
static void on_top_level_window_open4_activate(GtkMenuItem * menuitem, gpointer user_data);
static void on_top_level_window_svg1_activate(GtkMenuItem * menuitem, gpointer user_data);
static void on_top_level_window_dia1_activate(GtkMenuItem * menuitem, gpointer user_data);
static void on_top_level_window_jgf1_activate(GtkMenuItem * menuitem, gpointer user_data);
static void on_top_level_window_quit1_activate(GtkMenuItem * menuitem, gpointer user_data);
static void on_top_level_window_fullscreen1_activate(GtkMenuItem * menuitem, gpointer user_data);
static void on_top_level_window_unfullscreen1_activate(GtkMenuItem * menuitem, gpointer user_data);
static void xspin_changed(GtkWidget * widget, gpointer spinbutton);
static void yspin_changed(GtkWidget * widget, gpointer spinbutton);
static void pos_changed(GtkWidget * widget, gpointer spinbutton);
static void bary_changed(GtkWidget * widget, gpointer spinbutton);
static void rank_changed(GtkWidget * widget, gpointer spinbutton);
static void check1_toggle(GtkWidget * widget, gpointer window);
static void dummy1_toggle(GtkWidget * widget, gpointer window);
static void elabel1_toggle(GtkWidget * widget, gpointer window);
static void label1_toggle(GtkWidget * widget, gpointer window);
static void nnames1_toggle(GtkWidget * widget, gpointer window);
static void popup1_toggle(GtkWidget * widget, gpointer window);
static void mirrory1_toggle(GtkWidget * widget, gpointer window);

static void on_top_level_window_drawingarea1_expose_event_edges(cairo_t * crp);

static void on_top_level_window_drawingarea1_expose_event_nodes_record_r(cairo_t * crp, struct gml_node
									 *node, struct gml_rl
									 *info);

static void on_top_level_window_drawingarea1_expose_event_nodes_record(cairo_t * crp, struct gml_node
								       *node);
static void on_top_level_window_drawingarea1_expose_event_nodes_html(cairo_t * crp, struct gml_node
								     *node);

static void on_top_level_window_drawingarea1_expose_event_nodes(cairo_t * crp);

static void show_about(GtkWidget * widget, gpointer data);

/* left slider */
static void on_vscale1_changed(GtkAdjustment * adj);

/* right slider */
static void on_vscale2_changed(GtkAdjustment * adj);

/* bottom slider */
static void on_hscale1_changed(GtkAdjustment * adj);

#if GTK_HAVE_API_VERSION_2 == 1
/* redraw drawing area */
static gboolean on_top_level_window_drawingarea1_expose_event(GtkWidget * widget, GdkEventExpose * event, gpointer user_data);
#endif

#if GTK_HAVE_API_VERSION_3 == 1
/* redraw drawing area */
static gboolean on_top_level_window_drawingarea1_draw_event(GtkWidget * widget, cairo_t * crdraw, gpointer user_data);
#endif

#if GTK_HAVE_API_VERSION_2 == 1
/* redraw drawing area */
static gboolean popuparea1_expose_event(GtkWidget * widget, GdkEventExpose * event, gpointer user_data);
#endif

#if GTK_HAVE_API_VERSION_3 == 1
/* redraw drawing area */
static gboolean popuparea1_draw_event(GtkWidget * widget, cairo_t * crdraw, gpointer user_data);
#endif

/* fit drawing in window */
static void dofit(void);

static void do_layout_all(struct gml_graph *g);
static void do_relayout_all(struct gml_graph *g);

static void finalxy(struct gml_graph *g);

static struct gml_p *static_maingtk_textsizes1sz(struct gml_rl *info);

static void static_maingtk_textsizes1rl(struct gml_rl *info);

static void static_maingtk_textsizes1eq(struct gml_rl *info);

static void static_maingtk_textsizes2rl(struct gml_rl *info, int count, int xoff, int yoff, int bbx, int bby);

static void static_maingtk_textsizes1n(struct gml_node *node);

static void static_maingtk_textsizes(void);

static void update_status_text(char *text);

static gboolean on_mouse_clicked(GtkWidget * widget, GdkEventButton * event, gpointer user_data);
static gboolean on_motion_notify_event(GtkWidget * widget, GdkEventMotion * event);

int main(int argc, char *argv[])
{
	int status = 0;
	char *s = NULL;
	char *fnam = NULL;
	FILE *f = NULL;
	gzFile fgml = (gzFile) 0;
	GtkWidget *vbox1;
	GtkWidget *menubar1;
	GtkWidget *menuitem1;
	GtkWidget *menuitem1_menu;
	GtkWidget *open1;	/* open gml file */
	GtkWidget *open2;	/* open dot file */
	GtkWidget *open3;	/* open vcg file */
	GtkWidget *open4;	/* open jgf file */
	GtkWidget *svg1;
	GtkWidget *dia1;
	GtkWidget *jgf1;
	GtkWidget *about1;
	GtkWidget *quit1;
	GtkWidget *hbox1;
	GtkWidget *hbox2;
	GtkWidget *vscale1;
	GtkWidget *vscale2;
	GtkWidget *hscale1;
	GtkWidget *hbox3;
	GtkWidget *xspinlabel;
	GtkAdjustment *xspinadjustment;
	GtkWidget *xspinbutton;
	GtkWidget *yspinlabel;
	GtkAdjustment *yspinadjustment;
	GtkWidget *yspinbutton;
	GtkWidget *pos1;
	GtkAdjustment *posadjustment;
	GtkWidget *check1;
	GtkWidget *dummy1;
	GtkWidget *rank1;
	GtkAdjustment *rankadjustment;
	GtkWidget *rankbutton;
	GtkWidget *entry1;
	GtkWidget *barylabel;
	GtkAdjustment *baryadjustment;
	GtkWidget *barybutton;
	GtkWidget *label1;
	GtkWidget *nnames1;
	GtkWidget *popup1;
	GtkWidget *mirrory1;
	GtkWidget *menuitem2;
	GtkWidget *menuitem2_menu;
	GtkWidget *fullscreen1;
	GtkWidget *unfullscreen1;

	/* */
	dp_meminit();

	argv0 = argv[0];

	/* get the home dir */
	s = getenv("HOME");
	if (s) {
		lastopendir = dp_calloc(1, (strlen(s) + 1));
		strcpy(lastopendir, s);
		lastsavedir = dp_calloc(1, (strlen(s) + 1));
		strcpy(lastsavedir, s);
	} else {
		/* there is no home dir set in env */
		lastopendir = NULL;
		lastsavedir = NULL;
	}

#if !GLIB_CHECK_VERSION (2, 36, 0)
	/* for GDBus */
	g_type_init();
#endif

	/*
	 *    gtk_init (&argc, &argv); in gkt2, gtk3 and gtk_init() in gtk4
	 *
	 * calls the function gtk_init(gint *argc, gchar ***argv) which will be called in all GTK applications. 
	 * This sets up a few things for us such as the default visual and color map and then proceeds to call 
	 * gdk_init(gint *argc, gchar ***argv). This function initializes the library for use, sets up default 
	 * signal handlers, and checks the arguments passed to your application on the command line, 
	 * looking for one of the following:
	 *
	 *    * --gtk-module
	 *    * --g-fatal-warnings
	 *    * --gtk-debug
	 *    * --gtk-no-debug
	 *    * --gdk-debug
	 *    * --gdk-no-debug
	 *    * --display
	 *    * --sync
	 *    * --no-xshm
	 *    * --name
	 *    * --class
	 *
	 * It removes these from the argument list, leaving anything it does not recognize for your application 
	 * to parse or ignore. This creates a set of standard arguments accepted by all GTK applications.
	 *
	 */

	/* do gtk init, gtk will grab the gtk specific options on command line */
#if GTK_HAVE_API_VERSION_4 == 1
	(void)gtk_init();
#else
	/* gtk 2, 3 */
	status = gtk_init_check(&argc, &argv);

	if (status == FALSE) {
		/* this does happen with sudo strace ./mooigraph for some reason */
		printf("%s is in console mode and need in graphical mode to run\n", argv[0]);
		fflush(stdout);
		return (0);
	}
#endif

	/* top level outer window */
	mainwindow1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* make sure to exit oke. */
	g_signal_connect(G_OBJECT(mainwindow1), "destroy", G_CALLBACK(top_level_window_main_quit), NULL);

	/* needed for the cairo drawing */
	gtk_widget_set_app_paintable(mainwindow1, TRUE);

	/* use package string program name as set by configure in config.h */
	gtk_window_set_title(GTK_WINDOW(mainwindow1), PACKAGE_STRING);

	/* pre-set some size */
	gtk_window_set_default_size(GTK_WINDOW(mainwindow1), TOP_LEVEL_WINDOW_XSIZE, TOP_LEVEL_WINDOW_YSIZE);

	/* --- */

	/* vbox1 is a menu bar */
#if GTK_HAVE_API_VERSION_2 == 1
	vbox1 = gtk_vbox_new( /* homogeneous */ FALSE, /* spacing */ 0);
	gtk_widget_show(vbox1);
	gtk_container_add(GTK_CONTAINER(mainwindow1), vbox1);
#endif

#if GTK_HAVE_API_VERSION_3 == 1
	vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, /* spacing */ 0);
	gtk_widget_show(vbox1);
	gtk_container_add(GTK_CONTAINER(mainwindow1), vbox1);
#endif

#if GTK_HAVE_API_VERSION_4 == 1
	/* todo add gtk-4 support */
#endif

	/* --- */

	/* menu bar in vbox1 */
	menubar1 = gtk_menu_bar_new();
	gtk_widget_show(menubar1);
	gtk_box_pack_start( /* box */ GTK_BOX(vbox1), /* child */ menubar1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	/* --- */

	/* menu items in menu bar in vbox1 */
	menuitem1 = gtk_menu_item_new_with_mnemonic("File");
	gtk_container_add(GTK_CONTAINER(menubar1), menuitem1);
	gtk_widget_show(menuitem1);

	/* --- */

	/* 'file' sub menu in menu items in menu bar in vbox1 */
	menuitem1_menu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem1), menuitem1_menu);

	/* --- */
	/* 'open' in 'file' sub menu in menu items in menu bar in vbox1 */
	open2 = gtk_menu_item_new_with_mnemonic("Open DOT graph");
	gtk_container_add(GTK_CONTAINER(menuitem1_menu), open2);
	gtk_widget_show(open2);

	/* run this routine when selected 'open' in 'file' menu */
	g_signal_connect(G_OBJECT(open2), "activate", G_CALLBACK(on_top_level_window_open2_activate), NULL);

	/* 'open' in 'file' sub menu in menu items in menu bar in vbox1 */
	open1 = gtk_menu_item_new_with_mnemonic("Open GML graph");
	gtk_container_add(GTK_CONTAINER(menuitem1_menu), open1);
	gtk_widget_show(open1);

	/* run this routine when selected 'open' in 'file' menu */
	g_signal_connect(G_OBJECT(open1), "activate", G_CALLBACK(on_top_level_window_open1_activate), NULL);

	/* 'open' in 'file' sub menu in menu items in menu bar in vbox1 */
	open3 = gtk_menu_item_new_with_mnemonic("Open VCG graph");
	gtk_container_add(GTK_CONTAINER(menuitem1_menu), open3);
	gtk_widget_show(open3);

	/* run this routine when selected 'open' in 'file' menu */
	g_signal_connect(G_OBJECT(open3), "activate", G_CALLBACK(on_top_level_window_open3_activate), NULL);

	/* 'open' in 'file' sub menu in menu items in menu bar in vbox1 */
	open4 = gtk_menu_item_new_with_mnemonic("Open JGF graph");
	gtk_container_add(GTK_CONTAINER(menuitem1_menu), open4);
	gtk_widget_show(open4);

	/* run this routine when selected 'open' in 'file' menu */
	g_signal_connect(G_OBJECT(open4), "activate", G_CALLBACK(on_top_level_window_open4_activate), NULL);

	svg1 = gtk_menu_item_new_with_mnemonic("Save as SVG");
	gtk_container_add(GTK_CONTAINER(menuitem1_menu), svg1);
	gtk_widget_show(svg1);

	/* run this routine when selected 'svg' in 'file' menu */
	g_signal_connect(G_OBJECT(svg1), "activate", G_CALLBACK(on_top_level_window_svg1_activate), NULL);

	dia1 = gtk_menu_item_new_with_mnemonic("Save as DIA");
	gtk_container_add(GTK_CONTAINER(menuitem1_menu), dia1);
	gtk_widget_show(dia1);

	/* run this routine when selected 'dia' in 'file' menu */
	g_signal_connect(G_OBJECT(dia1), "activate", G_CALLBACK(on_top_level_window_dia1_activate), NULL);

	jgf1 = gtk_menu_item_new_with_mnemonic("Save as JGF");
	gtk_container_add(GTK_CONTAINER(menuitem1_menu), jgf1);
	gtk_widget_show(jgf1);

	/* run this routine when selected 'jgf' in 'file' menu */
	g_signal_connect(G_OBJECT(jgf1), "activate", G_CALLBACK(on_top_level_window_jgf1_activate), NULL);

	/* 'about' in 'file' sub menu in menu items in menu bar in vbox1 */
	about1 = gtk_menu_item_new_with_mnemonic("About");
	gtk_container_add(GTK_CONTAINER(menuitem1_menu), about1);
	gtk_widget_show(about1);

	/* run this routine when selected 'about' in 'file' menu */
	g_signal_connect(G_OBJECT(about1), "activate", G_CALLBACK(show_about), NULL);

	/* 'quit' in 'file' sub menu in menu items in menu bar in vbox1 */
	quit1 = gtk_menu_item_new_with_mnemonic("Quit");
	gtk_container_add(GTK_CONTAINER(menuitem1_menu), quit1);
	gtk_widget_show(quit1);

	/* run this routine when selected 'quit' in 'file' menu */
	g_signal_connect(G_OBJECT(quit1), "activate", G_CALLBACK(on_top_level_window_quit1_activate), NULL);

	/* --- */

	/* menu items in menu bar in vbox1 */
	menuitem2 = gtk_menu_item_new_with_mnemonic("Fullscreen");
	gtk_container_add(GTK_CONTAINER(menubar1), menuitem2);
	gtk_widget_show(menuitem2);

	/* 'fullscreen' sub menu in menu items in menu bar in vbox1 */
	menuitem2_menu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem2), menuitem2_menu);

	/* 'fullscreen->fullscreen' in 'fullscreen' sub menu in menu items in menu bar in vbox1 */
	fullscreen1 = gtk_menu_item_new_with_mnemonic("Fullscreen");
	gtk_container_add(GTK_CONTAINER(menuitem2_menu), fullscreen1);
	gtk_widget_show(fullscreen1);

	/* run this routine when selected 'fullscreen->fullscreen in 'fullscreen' menu */
	g_signal_connect(G_OBJECT(fullscreen1), "activate", G_CALLBACK(on_top_level_window_fullscreen1_activate), NULL);

	/* 'fullscreen->normal' in 'fullscreen' sub menu in menu items in menu bar in vbox1 */
	unfullscreen1 = gtk_menu_item_new_with_mnemonic("Normal");
	gtk_container_add(GTK_CONTAINER(menuitem2_menu), unfullscreen1);
	gtk_widget_show(unfullscreen1);

	/* run this routine when selected 'fullscreen->normal' in 'fullscreen' menu */
	g_signal_connect(G_OBJECT(unfullscreen1), "activate", G_CALLBACK(on_top_level_window_unfullscreen1_activate), NULL);

	/* -- */

	/*
	 * in hbox1
	 * left zoom slider
	 * drawing area
	 * right y slider
	 * below x slider
	 */

	/* add next area to the vbox1 */
#if GTK_HAVE_API_VERSION_2 == 1
	hbox1 = gtk_hbox_new( /* homogeneous */ FALSE, /* spacing */ 0);
	gtk_box_pack_start( /* box */ GTK_BOX(vbox1), /* child */ hbox1,
			   /* expand */ TRUE, /* fill */ TRUE,	/* padding */
			   PACKPADDING);
	gtk_widget_show(hbox1);
#endif

#if GTK_HAVE_API_VERSION_3 == 1
	hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, /* spacing */ 0);
	gtk_box_pack_start( /* box */ GTK_BOX(vbox1), /* child */ hbox1,
			   /* expand */ TRUE, /* fill */ TRUE,	/* padding */
			   PACKPADDING);
	gtk_widget_show(hbox1);
#endif

	/* vertical slider in hbox1 for the zoom factor 50% is 1:1 */
	adjvscale1 = gtk_adjustment_new(50, 0, 100, 0, 0, 0);

#if GTK_HAVE_API_VERSION_2 == 1
	vscale1 = gtk_vscale_new(GTK_ADJUSTMENT(adjvscale1));
	g_signal_connect(G_OBJECT(adjvscale1), "value_changed", GTK_SIGNAL_FUNC(on_vscale1_changed), NULL);
	gtk_box_pack_start( /* box */ GTK_BOX(hbox1), /* child */ vscale1,
			   /* expand */ FALSE, /* fill */ TRUE,	/* padding */
			   PACKPADDING);
	gtk_scale_set_draw_value(GTK_SCALE(vscale1), FALSE);
	gtk_widget_show(vscale1);
#endif

#if GTK_HAVE_API_VERSION_3 == 1
	vscale1 = gtk_scale_new(GTK_ORIENTATION_VERTICAL, GTK_ADJUSTMENT(adjvscale1));
	g_signal_connect(G_OBJECT(adjvscale1), "value_changed", G_CALLBACK(on_vscale1_changed), NULL);
	gtk_box_pack_start( /* box */ GTK_BOX(hbox1), /* child */ vscale1,
			   /* expand */ FALSE, /* fill */ TRUE,	/* padding */
			   PACKPADDING);
	gtk_scale_set_draw_value(GTK_SCALE(vscale1), FALSE);
	gtk_widget_show(vscale1);
#endif

	/* where to draw in hbox1 */
	drawingarea1 = gtk_drawing_area_new();
	gtk_box_pack_start( /* box */ GTK_BOX(hbox1), /* child */ drawingarea1,
			   /* expand */ TRUE, /* fill */ TRUE,	/* padding */
			   PACKPADDING);
	gtk_widget_show(drawingarea1);

#if GTK_HAVE_API_VERSION_2 == 1
	g_signal_connect(G_OBJECT(drawingarea1), "expose_event", G_CALLBACK(on_top_level_window_drawingarea1_expose_event), NULL);
#endif

#if GTK_HAVE_API_VERSION_3 == 1
	g_signal_connect(G_OBJECT(drawingarea1), "draw", G_CALLBACK(on_top_level_window_drawingarea1_draw_event), NULL);
#endif

	/* mouse buttons */
	g_signal_connect(G_OBJECT(drawingarea1), "button-press-event", G_CALLBACK(on_mouse_clicked), NULL);
	g_signal_connect(G_OBJECT(drawingarea1), "motion_notify_event", G_CALLBACK(on_motion_notify_event), NULL);

	/* get button press events to above callback() routines
	 * get button 1 press events
	 * get mouse pointer movement events
	 */
	gtk_widget_set_events((drawingarea1), (GDK_BUTTON_PRESS_MASK | GDK_BUTTON1_MOTION_MASK | GDK_POINTER_MOTION_MASK));

	/* vertical slider in hbox1 for the y position range 0...100% of full image size */
	adjvscale2 = gtk_adjustment_new(0, 0, 100, 0, 0, 0);

#if GTK_HAVE_API_VERSION_2 == 1
	vscale2 = gtk_vscale_new(GTK_ADJUSTMENT(adjvscale2));
	g_signal_connect(G_OBJECT(adjvscale2), "value_changed", GTK_SIGNAL_FUNC(on_vscale2_changed), NULL);
	gtk_box_pack_start( /* box */ GTK_BOX(hbox1), /* child */ vscale2,
			   /* expand */ FALSE, /* fill */ TRUE,	/* padding */
			   PACKPADDING);
	gtk_scale_set_draw_value(GTK_SCALE(vscale2), FALSE);
	gtk_widget_show(vscale2);
#endif

#if GTK_HAVE_API_VERSION_3 == 1
	vscale2 = gtk_scale_new(GTK_ORIENTATION_VERTICAL, GTK_ADJUSTMENT(adjvscale2));
	g_signal_connect(G_OBJECT(adjvscale2), "value_changed", G_CALLBACK(on_vscale2_changed), NULL);
	gtk_box_pack_start( /* box */ GTK_BOX(hbox1), /* child */ vscale2,
			   /* expand */ FALSE, /* fill */ TRUE,	/* padding */
			   PACKPADDING);
	gtk_scale_set_draw_value(GTK_SCALE(vscale2), FALSE);
	gtk_widget_show(vscale2);
#endif

	/* horizontal scroller 0..100% of drawing size */
	adjhscale1 = gtk_adjustment_new(0, 0, 100, 0, 0, 0);

#if GTK_HAVE_API_VERSION_2 == 1
	hscale1 = gtk_hscale_new(GTK_ADJUSTMENT(adjhscale1));
	g_signal_connect(G_OBJECT(adjhscale1), "value_changed", GTK_SIGNAL_FUNC(on_hscale1_changed), NULL);
	gtk_box_pack_start( /* box */ GTK_BOX(vbox1), /* child */ hscale1,
			   /* expand */ FALSE, /* fill */ TRUE,	/* padding */
			   PACKPADDING);
	gtk_scale_set_draw_value(GTK_SCALE(hscale1), FALSE);
	gtk_widget_show(hscale1);
#endif

#if GTK_HAVE_API_VERSION_3 == 1
	hscale1 = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, GTK_ADJUSTMENT(adjhscale1));
	g_signal_connect(G_OBJECT(adjhscale1), "value_changed", G_CALLBACK(on_hscale1_changed), NULL);
	gtk_box_pack_start( /* box */ GTK_BOX(vbox1), /* child */ hscale1,
			   /* expand */ FALSE, /* fill */ TRUE,	/* padding */
			   PACKPADDING);
	gtk_scale_set_draw_value(GTK_SCALE(hscale1), FALSE);
	gtk_widget_show(hscale1);
#endif

	/* --- */

	/* add next area to the vbox1 */
#if GTK_HAVE_API_VERSION_2 == 1
	hbox2 = gtk_hbox_new( /* homogeneous */ FALSE, /* spacing */ 0);
	gtk_box_pack_start( /* box */ GTK_BOX(vbox1), /* child */ hbox2,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);
	gtk_widget_show(hbox2);
#endif

#if GTK_HAVE_API_VERSION_3 == 1
	hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, /* spacing */ 0);
	gtk_box_pack_start( /* box */ GTK_BOX(vbox1), /* child */ hbox2,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);
	gtk_widget_show(hbox2);
#endif

	/* --- */

	xspinlabel = gtk_label_new("dx");

	gtk_box_pack_start( /* box */ GTK_BOX(hbox2), /* child */ xspinlabel,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);
	gtk_widget_set_tooltip_text(xspinlabel, "stretch drawing in x-direction");
	gtk_widget_show(xspinlabel);

	/* spin to change drawing spread factor. note that in gtk2 it is a (GtkObject *) and in gtk3 a (GtkAdjustment *) */
	xspinadjustment = (GtkAdjustment *) gtk_adjustment_new(xspacing /* initial value */ ,
							       0 /* minimum value */ ,
							       99 /* maximum value */ ,
							       1 /* step increment */ ,
							       1 /* page increment */ ,
							       0	/* page size now *must* be zero */
	    );

	xspinbutton = gtk_spin_button_new(xspinadjustment, 1 /* climb rate */ ,
					  0 /* digits achter de comma */ );

	gtk_box_pack_start( /* box */ GTK_BOX(hbox2), /* child */ xspinbutton,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	g_signal_connect(G_OBJECT(xspinadjustment), "value-changed", G_CALLBACK(xspin_changed), (gpointer) xspinbutton);
	gtk_widget_show(xspinbutton);

	yspinlabel = gtk_label_new("dy");

	gtk_box_pack_start( /* box */ GTK_BOX(hbox2), /* child */ yspinlabel,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);
	gtk_widget_set_tooltip_text(yspinlabel, "stretch drawing in y-direction");
	gtk_widget_show(yspinlabel);

	/* spin to change drawing spread factor. note that in gtk2 it is a (GtkObject *) and in gtk3 a (GtkAdjustment *) */
	yspinadjustment = (GtkAdjustment *) gtk_adjustment_new(yspacing /* initial value */ ,
							       0 /* minimum value */ ,
							       99 /* maximum value */ ,
							       1 /* step increment */ ,
							       1 /* page increment */ ,
							       0	/* page size now *must* be zero */
	    );

	yspinbutton = gtk_spin_button_new(yspinadjustment, 1 /* climb rate */ ,
					  0 /* digits achter de comma */ );

	gtk_box_pack_start( /* box */ GTK_BOX(hbox2), /* child */ yspinbutton,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	gtk_widget_set_tooltip_text(yspinbutton, "stretch y-direction");

	g_signal_connect(G_OBJECT(yspinadjustment), "value-changed", G_CALLBACK(yspin_changed), (gpointer) yspinbutton);
	gtk_widget_show(yspinbutton);

	/* at every click, advance positioning mode */
	pos1 = gtk_label_new("pos");
	gtk_box_pack_start( /* box */ GTK_BOX(hbox2), /* child */ pos1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);
	gtk_widget_set_tooltip_text(pos1, "positioning mode");
	gtk_widget_show(pos1);

	posadjustment = (GtkAdjustment *) gtk_adjustment_new(postype /* initial value */ ,
							     1 /* minimum value */ ,
							     3 /* maximum value */ ,
							     1 /* step increment */ ,
							     1 /* page increment */ ,
							     0	/* page size now *must* be zero */
	    );

	posbutton = gtk_spin_button_new(posadjustment, 1 /* climb rate */ ,
					0 /* digits achter de comma */ );

	gtk_box_pack_start( /* box */ GTK_BOX(hbox2), /* child */ posbutton,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	g_signal_connect(G_OBJECT(posadjustment), "value-changed", G_CALLBACK(pos_changed), (gpointer) posbutton);
	gtk_widget_show(posbutton);

	/* draw spline edges or normal */
	check1 = gtk_check_button_new_with_label("splines");
	gtk_box_pack_start( /* box */ GTK_BOX(hbox2), /* child */ check1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	/* */
	if (option_splines) {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check1), TRUE);
	} else {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check1), FALSE);
	}

	g_signal_connect(G_OBJECT(check1), "clicked", G_CALLBACK(check1_toggle), (gpointer) mainwindow1);

	gtk_widget_set_tooltip_text(check1, "edge line splines");

	gtk_widget_show(check1);

	/* draw dummy nodes */
	dummy1 = gtk_check_button_new_with_label("dummy's");
	gtk_box_pack_start( /* box */ GTK_BOX(hbox2), /* child */ dummy1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	/* */
	if (drawdummy) {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dummy1), TRUE);
	} else {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dummy1), FALSE);
	}

	g_signal_connect(G_OBJECT(dummy1), "clicked", G_CALLBACK(dummy1_toggle), (gpointer) mainwindow1);
	gtk_widget_set_tooltip_text(dummy1, "show dummy nodes");
	gtk_widget_show(dummy1);

	/* */
	entry1 = gtk_text_view_new();
	entry1buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(entry1));
	gtk_text_buffer_set_text(entry1buffer, "GML4GTK is free software to copy, share and improve", -1);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(entry1), FALSE);
	gtk_box_pack_start( /* box */ GTK_BOX(hbox2), /* child */ entry1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);
	gtk_widget_set_tooltip_text(entry1, "status information");
	gtk_widget_show(entry1);

	/*
	 * next line with toggle buttons
	 */
	/* add next area to the vbox1 */
#if GTK_HAVE_API_VERSION_2 == 1
	hbox3 = gtk_hbox_new( /* homogeneous */ FALSE, /* spacing */ 0);
	gtk_box_pack_start( /* box */ GTK_BOX(vbox1), /* child */ hbox3,
			   /* expand */ FALSE, /* fill */ TRUE,	/* padding */
			   PACKPADDING);
	gtk_widget_show(hbox3);
#endif

#if GTK_HAVE_API_VERSION_3 == 1
	hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, /* spacing */ 0);
	gtk_box_pack_start( /* box */ GTK_BOX(vbox1), /* child */ hbox3,
			   /* expand */ FALSE, /* fill */ TRUE,	/* padding */
			   PACKPADDING);
	gtk_widget_show(hbox3);
#endif

	/* level placement */
	rank1 = gtk_label_new("rank");
	gtk_box_pack_start( /* box */ GTK_BOX(hbox3), /* child */ rank1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);
	gtk_widget_set_tooltip_text(rank1, "dfs/bfs/topological levels");
	gtk_widget_show(rank1);

	/* spin to change rank type note that in gtk2 it is a (GtkObject *) and in gtk3 a (GtkAdjustment *) */
	rankadjustment = (GtkAdjustment *) gtk_adjustment_new(ranktype /* initial value */ ,
							      1 /* minimum value */ ,
							      3 /* maximum value */ ,
							      1 /* step increment */ ,
							      1 /* page increment */ ,
							      0	/* page size now *must* be zero */
	    );

	rankbutton = gtk_spin_button_new(rankadjustment, 1 /* climb rate */ ,
					 0 /* digits achter de comma */ );

	gtk_box_pack_start( /* box */ GTK_BOX(hbox3), /* child */ rankbutton,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	g_signal_connect(G_OBJECT(rankadjustment), "value-changed", G_CALLBACK(rank_changed), (gpointer) rankbutton);
	gtk_widget_show(rankbutton);

	/* barycenter */
	barylabel = gtk_label_new("bary");

	gtk_box_pack_start( /* box */ GTK_BOX(hbox3), /* child */ barylabel,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);
	gtk_widget_set_tooltip_text(barylabel, "barycenter type");
	gtk_widget_show(barylabel);

	/* spin to change barycenter type note that in gtk2 it is a (GtkObject *) and in gtk3 a (GtkAdjustment *) */
	baryadjustment = (GtkAdjustment *) gtk_adjustment_new(barytype /* initial value */ ,
							      1 /* minimum value */ ,
							      5 /* maximum value */ ,
							      1 /* step increment */ ,
							      1 /* page increment */ ,
							      0	/* page size now *must* be zero */
	    );

	barybutton = gtk_spin_button_new(baryadjustment, 1 /* climb rate */ ,
					 0 /* digits achter de comma */ );

	gtk_box_pack_start( /* box */ GTK_BOX(hbox3), /* child */ barybutton,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	g_signal_connect(G_OBJECT(baryadjustment), "value-changed", G_CALLBACK(bary_changed), (gpointer) barybutton);
	gtk_widget_show(barybutton);

	/* edgelabels on/off */
	elabel1 = gtk_check_button_new_with_label("elabel");
	gtk_box_pack_start( /* box */ GTK_BOX(hbox3), /* child */ elabel1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	/* */
	if (option_edgelabels) {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(elabel1), TRUE);
	} else {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(elabel1), FALSE);
	}

	g_signal_connect(G_OBJECT(elabel1), "clicked", G_CALLBACK(elabel1_toggle), (gpointer) mainwindow1);
	gtk_widget_set_tooltip_text(elabel1, "edgelabels on/off");
	gtk_widget_show(elabel1);

	/* labels on/off */
	label1 = gtk_check_button_new_with_label("labels");
	gtk_box_pack_start( /* box */ GTK_BOX(hbox3), /* child */ label1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	/* */
	if (option_labels) {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(label1), TRUE);
	} else {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(label1), FALSE);
	}

	g_signal_connect(G_OBJECT(label1), "clicked", G_CALLBACK(label1_toggle), (gpointer) mainwindow1);
	gtk_widget_set_tooltip_text(label1, "labels on/off");
	gtk_widget_show(label1);

	/* node names on/off */
	nnames1 = gtk_check_button_new_with_label("names");
	gtk_box_pack_start( /* box */ GTK_BOX(hbox3), /* child */ nnames1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	/* */
	if (option_nnames) {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(nnames1), TRUE);
	} else {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(nnames1), FALSE);
	}

	g_signal_connect(G_OBJECT(nnames1), "clicked", G_CALLBACK(nnames1_toggle), (gpointer) mainwindow1);
	gtk_widget_set_tooltip_text(nnames1, "node names instead of labels");
	gtk_widget_show(nnames1);

	/* popup labels on/off */
	popup1 = gtk_check_button_new_with_label("popup");
	gtk_box_pack_start( /* box */ GTK_BOX(hbox3), /* child */ popup1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	/* */
	if (option_popup) {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(popup1), TRUE);
	} else {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(popup1), FALSE);
	}

	g_signal_connect(G_OBJECT(popup1), "clicked", G_CALLBACK(popup1_toggle), (gpointer) mainwindow1);
	gtk_widget_set_tooltip_text(popup1, "popup labels on/off");
	gtk_widget_show(popup1);

	/* mirror y on/off */
	mirrory1 = gtk_check_button_new_with_label("mirror");
	gtk_box_pack_start( /* box */ GTK_BOX(hbox3), /* child */ mirrory1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	/* */
	if (option_mirrory) {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mirrory1), TRUE);
	} else {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mirrory1), FALSE);
	}

	g_signal_connect(G_OBJECT(mirrory1), "clicked", G_CALLBACK(mirrory1_toggle), (gpointer) mainwindow1);
	gtk_widget_set_tooltip_text(mirrory1, "mirror drawing in y direction");
	gtk_widget_show(mirrory1);

	/*
	 * here additional gtk elements
	 */

	/* put on screen */
	gtk_widget_show(mainwindow1);

	/* check for optinal gml file on commandline
	 * on commandline file.gml.gz is supported
	 * but not dot.gz or vcg.gz
	 */
	if (argc > 1) {
		fnam = argv[1];
		if ((*fnam) != '-') {
			/* find the last '.' 
			 * if (strcmp(s, ".gz") == 0)
			 * then it is gzipped, but need to know the part before
			 */
			s = strrchr(fnam, '.');
			if (s) {

				/*
				 * switch between dot or gml or vcg parser
				 * gcc generates vcg file with file extention .ci
				 */
				if ((strcmp(s, ".vcg") == 0) || (strcmp(s, ".ci") == 0)) {
					/* assume this is a gcc vcg file */
					f = fopen(fnam, "r");
					if (f) {
						/* type of graph data 0=gml 1=dot 2=vcg */
						graphtype = 2;

						/* create root graph */
						create_maingraph();

						/* parse the data */
						if (vcgparse(maingraph, f, fnam, argv0)) {
							/* parse error */
							if (strlen(parsermessage) == 0) {
								strcpy(parsermessage, "no parser message");
							}
							printf("%s\n", parsermessage);
							fflush(stdout);
							fclose(f);
							/* data is invalid at this point */
							validdata = 0;
						} else {
							/* check for empty graph here */
							if (maingraph->rawnodelist) {

								/* update status text */
								update_status_text("Wait ... Calculating Layout");

								while (gtk_events_pending()) {
									gtk_main_iteration();
									/* this updates the status text */
								}

								do_layout_all(maingraph);

								/* update status text */
								update_status_text(NULL);

								/* set sliders to defaults */
								zfactor = 1.0;
								gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale1), 50);

								vxmin = 0;
								vymin = 0;
								gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale2), 0);
								gtk_adjustment_set_value(GTK_ADJUSTMENT(adjhscale1), 0);

								drawing_area_xsize = TOP_LEVEL_WINDOW_XSIZE;
								drawing_area_ysize = TOP_LEVEL_WINDOW_YSIZE;

								/* fit drawing in window */
								dofit();

								validdata = 1;
							} else {
								/* update status text */
								update_status_text("Empty graph ... No Nodes");
								validdata = 0;
							}
						}
						fclose(f);
					} else {
						printf("%s(): cannot open `%s' file for reading\n", __func__, fnam);
						fflush(stdout);
					}
					/* end of vcg file at start */
				} else if ((strcmp(s, ".dot") == 0) || (strcmp(s, ".gv") == 0)) {
					/* assume this is a dot file */
					f = fopen(fnam, "r");
					if (f) {
						/* type of graph data 0=gml 1=dot 2=vcg */
						graphtype = 1;

						/* create root graph */
						create_maingraph();

						/* parse the data */
						if (dotparse(maingraph, f, fnam, argv0)) {
							/* parse error */
							if (strlen(parsermessage) == 0) {
								strcpy(parsermessage, "no parser message");
							}
							printf("%s\n", parsermessage);
							fflush(stdout);
							fclose(f);
							/* data is invalid at this point */
							validdata = 0;
						} else {
							/* check for empty graph here */
							if (maingraph->rawnodelist) {

								/* update status text */
								update_status_text("Wait ... Calculating Layout");

								while (gtk_events_pending()) {
									gtk_main_iteration();
									/* this updates the status text */
								}

								do_layout_all(maingraph);

								/* update status text */
								update_status_text(NULL);

								/* set sliders to defaults */
								zfactor = 1.0;
								gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale1), 50);

								vxmin = 0;
								vymin = 0;
								gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale2), 0);
								gtk_adjustment_set_value(GTK_ADJUSTMENT(adjhscale1), 0);

								drawing_area_xsize = TOP_LEVEL_WINDOW_XSIZE;
								drawing_area_ysize = TOP_LEVEL_WINDOW_YSIZE;

								/* fit drawing in window */
								dofit();

								validdata = 1;
							} else {
								/* update status text */
								update_status_text("Empty graph ... No Nodes");
								validdata = 0;
							}
						}
						fclose(f);
					} else {
						printf("%s(): cannot open `%s' file for reading\n", __func__, fnam);
						fflush(stdout);
					}
					/* end of dot file at start */
				} else {
					/* assume gml file */
					fgml = gzopen(fnam, "r");
					if (fgml) {
						/* type of graph data 0=gml 1=dot 2=vcg */
						graphtype = 0;

						/* create root graph */
						create_maingraph();

						/* parse the gml data */
						if (gmlparse(maingraph, fgml, fnam)) {
							/* parse error */
							if (strlen(parsermessage) == 0) {
								strcpy(parsermessage, "no parser message");
							}
							printf("%s\n", parsermessage);
							fflush(stdout);
							fclose(f);
							/* data is invalid at this point */
							validdata = 0;
						} else {
							/* check for empty graph here */
							if (maingraph->rawnodelist) {

								/* update status text */
								update_status_text("Wait ... Calculating Layout");

								while (gtk_events_pending()) {
									gtk_main_iteration();
									/* this updates the status text */
								}

								do_layout_all(maingraph);

								/* update status text */
								update_status_text(NULL);

								/* set sliders to defaults */
								zfactor = 1.0;
								gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale1), 50);

								vxmin = 0;
								vymin = 0;
								gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale2), 0);
								gtk_adjustment_set_value(GTK_ADJUSTMENT(adjhscale1), 0);

								drawing_area_xsize = TOP_LEVEL_WINDOW_XSIZE;
								drawing_area_ysize = TOP_LEVEL_WINDOW_YSIZE;

								/* fit drawing in window */
								dofit();

								validdata = 1;
							} else {
								/* update status text */
								update_status_text("Empty graph ... No Nodes");
								validdata = 0;
							}
						}
						gzclose(fgml);
					} else {
						printf("%s(): cannot open `%s' file for reading\n", __func__, fnam);
						fflush(stdout);
					}
					/* end of gml file at start */
				}

			}
		}
	}

	/* run the gui */
	gtk_main();

	/* */
	do_clear_all(0);

	if (lastopendir) {
		dp_free(lastopendir);
	}
	if (lastsavedir) {
		dp_free(lastsavedir);
	}

	/* optional memory check report when compiled with -DMEMCHECK */
	dp_memreport();

	return (0);
}

/* scale pos to zvalue */
static int doscaleit(int val)
{
	int ret = 0;
	double x = 0.0;
	x = (double)val;
	x = x * zfactor;
	x = round(x);
	ret = (int)x;
	return (ret);
}

/* check if a node at mouse pointer position */
static struct gml_node *is_node_at_xy(int x, int y)
{
	struct gml_node *found = NULL;
	struct gml_nlist *nl = NULL;
	int x0 = 0;
	int y0 = 0;
	int xs = 0;
	int ys = 0;
	/* first parameters check */
	if (x < 0) {
		return (NULL);
	}
	if (y < 0) {
		return (NULL);
	}
	if (x > drawing_area_xsize) {
		return (NULL);
	}
	if (y > drawing_area_ysize) {
		return (NULL);
	}

	nl = maingraph->nodelist;

	while (nl) {
		/* skip dummy nodes */
		if (nl->node->dummy == 1) {
			nl = nl->next;
			continue;
		}
		/* skip edgelabel nodes */
		if (nl->node->elabel) {
			nl = nl->next;
			continue;
		}
		/* this is a real node and calc screen coords */
		x0 = doscaleit(nl->node->finx - vxmin);
		y0 = doscaleit(nl->node->finy - vymin);
		xs = doscaleit(nl->node->bbx);
		ys = doscaleit(nl->node->bby);
		/* check if on-screen */
		if (x0 < 0 && (x0 + xs) < 0) {
			nl = nl->next;
			continue;
		}
		if (y0 < 0 && (y0 + ys) < 0) {
			nl = nl->next;
			continue;
		}
		if (x0 > drawing_area_xsize) {
			nl = nl->next;
			continue;
		}
		if (y0 > drawing_area_ysize) {
			nl = nl->next;
			continue;
		}
		/* node is on-screen and check wit mouse pointer */
		if ((x > x0 && x < (x0 + xs)) && (y > y0 && y < (y0 + ys))) {
			found = nl->node;
			break;
		}
		/* try other node in drawing */
		nl = nl->next;
	}
	return (found);
}

/* make sure there is no popup windows */
static void no_popup(void)
{
	if (popupwindow1) {
		gtk_widget_destroy(popupwindow1);
		popupwindow1 = NULL;
	}
	return;
}

/* popup the node label text, vars are checked */
static void popup_nodelabel(struct gml_node *n, cairo_t * crp, int xsize, int ysize)
{
	int cr = 0;
	int cg = 0;
	int cb = 0;
	int xo = 0;
	int yo = 0;
	PangoLayout *layout = NULL;
	PangoFontDescription *desc = NULL;
	char buf[128];
	char *s = NULL;
	/* name of font to use, example "Sans" */
	const char *default_fontname = DEFAULT_FONTNAME;
	/* name of slant to use, example "Italic", "Oblique", "Roman" */
	const char *default_fontslant = DEFAULT_FONTSLANT;
	/* name of weight to use, example "Bold", "Book", "Light", "Medium", "Semi-bold", "Ultra-light" */
	const char *default_fontweight = DEFAULT_FONTWEIGHT;
	/* name of condensed to use, example "Semi-Condensed", "Condensed" */
	const char *default_fontcondensed = DEFAULT_FONTCONDENSED;
	/* font size to use, example "10", "18", "20" etc. */
	const char *default_fontsize = DEFAULT_FONTSIZE;

	/* fillcolor of node white default or color */
	cr = (n->ncolor & 0x00ff0000) >> 16;
	cg = (n->ncolor & 0x0000ff00) >> 8;
	cb = (n->ncolor & 0x000000ff);

	cairo_set_source_rgb(crp, cr / 255.0, cg / 255.0, cb / 255.0);
	cairo_rectangle(crp, 0, 0, xsize, ysize);
	cairo_fill(crp);
	cairo_stroke(crp);

	/* bordercolor of node black default or color */
	cr = (n->nbcolor & 0x00ff0000) >> 16;
	cg = (n->nbcolor & 0x0000ff00) >> 8;
	cb = (n->nbcolor & 0x000000ff);

	cairo_set_source_rgb(crp, cr / 255.0, cg / 255.0, cb / 255.0);
	cairo_rectangle(crp, 0, 0, xsize, ysize);
	cairo_stroke(crp);

	if (n->hlabel) {
		/* html label */
		on_top_level_window_drawingarea1_expose_event_nodes_html(crp, n);
	} else if (n->rlabel) {
		/* record label */

		/* draw record label */
		on_top_level_window_drawingarea1_expose_event_nodes_record(crp, n);

	} else {

		/* fontcolor of node black default or color */
		cr = (n->fontcolor & 0x00ff0000) >> 16;
		cg = (n->fontcolor & 0x0000ff00) >> 8;
		cb = (n->fontcolor & 0x000000ff);

		/* draw in text color of node */
		cairo_set_source_rgb(crp, cr / 255.0, cg / 255.0, cb / 255.0);

		xo = 2;
		yo = 2;

		/* set start position of text */
		cairo_move_to(crp, n->finx - vxmin + xo, n->finy - vymin + yo);

		layout = pango_cairo_create_layout(crp);

		/* set the text to draw which is 0 terminated */
		pango_layout_set_text(layout, n->nlabel, -1);

		/* set font parameters */

		/* create the fontname description */
		memset(buf, 0, 128);

		default_fontname = DEFAULT_FONTNAME;

		/* check if node has a specified font slant */
		default_fontslant = DEFAULT_FONTSLANT;

		/* check if node has a specified font weight */
		default_fontweight = DEFAULT_FONTWEIGHT;

		/* check if node has a specified font size */
		default_fontsize = DEFAULT_FONTSIZE;

		/* create the font name string */
		snprintf(buf, (128 - 1), "%s %s %s %s %s", default_fontname,
			 default_fontslant, default_fontweight, default_fontcondensed, default_fontsize);

		/* copy string buffer */
		s = uniqstr(buf);

		/* */
		desc = pango_font_description_from_string(s);

		/* */
		pango_layout_set_font_description(layout, desc);

		/* */
		pango_font_description_free(desc);

		/* */
		pango_cairo_update_layout(crp, layout);

		/* draw the text */
		pango_cairo_show_layout(crp, layout);

		/* */
		cairo_stroke(crp);

		g_object_unref(G_OBJECT(layout));
	}

	return;
}

#if GTK_HAVE_API_VERSION_2 == 1
/* redraw drawing area */
static gboolean popuparea1_expose_event(GtkWidget * widget, GdkEventExpose * event, gpointer user_data)
{
	struct gml_node *n = NULL;
	cairo_t *crp = NULL;
	gint w = 0;		/* xsize of drawing area */
	gint h = 0;		/* ysize of drawing area */
	double zfactor_saved = 0.0;
	int vxmin_saved = 0;
	int vymin_saved = 0;

	if (popupwindow1 == NULL) {
		/* shouldnothappen */
		return (FALSE);
	}

	if (widget) {
	}

	if (event == NULL) {
		return (FALSE);
	}

	/* the user data has the node to draw */
	n = (struct gml_node *)user_data;

	/* get cairo drawing context */
	crp = gdk_cairo_create(event->window);

	if (crp == NULL) {
		/* shouldnothappen */
		return (FALSE);
	}

	/* how large drawing area is */
	(void)gdk_drawable_get_size(event->window, &w, &h);

	if (option_gdebug > 1 || 0) {
		printf("%s(): drawing area size is (%d,%d) node=%p nlabel=\"%s\"\n", __func__, w, h, (void *)n, n->nlabel);
		fflush(stdout);
	}

	if (n == NULL) {
		/* shouldnothappen */
		return (FALSE);
	}

	/* save mainwindow settings */
	zfactor_saved = zfactor;
	vxmin_saved = vxmin;
	vymin_saved = vymin;

	/* draw node label text at 1:1 100% scale */
	zfactor = 1.0;
	vxmin = n->finx;
	vymin = n->finy;

	cairo_scale(crp, zfactor, zfactor);

	/* popup the node label text */
	popup_nodelabel(n, crp, w, h);

	/* restore mainwindow settings */
	zfactor = zfactor_saved;
	vxmin = vxmin_saved;
	vymin = vymin_saved;

	return (FALSE);
}
#endif

#if GTK_HAVE_API_VERSION_3
/* redraw drawing area */
static gboolean popuparea1_draw_event(GtkWidget * widget, cairo_t * crdraw, gpointer user_data)
{
	struct gml_node *n = NULL;
	gint w = 0;		/* xsize of drawing area */
	gint h = 0;		/* ysize of drawing area */
	cairo_t *crp = NULL;
	double zfactor_saved = 0.0;
	int vxmin_saved = 0;
	int vymin_saved = 0;

	if (popupwindow1 == NULL) {
		/* shouldnothappen */
		return (FALSE);
	}

	if (widget) {
	}

	/* the user data has the node to draw */
	n = (struct gml_node *)user_data;

	/* this is a workaround for issue in cairo-lib 1.14.0 with gtk3,
	 * cairo.c cairo_destroy() line 305 assert(), (with gtk2 no problem) */
	crp = cairo_reference(crdraw);

	if (crp == NULL) {
		/* shouldnothappen */
		return (FALSE);
	}

	/* how large drawing area is */
	w = gtk_widget_get_allocated_width(popupwindow1);
	h = gtk_widget_get_allocated_height(popupwindow1);

	if (option_gdebug > 1 || 0) {
		printf("%s(): drawing area size is (%d,%d) node %p\n", __func__, w, h, (void *)n);
		fflush(stdout);
	}

	if (n == NULL) {
		/* shouldnothappen */
		return (FALSE);
	}

	/* save mainwindow settings */
	zfactor_saved = zfactor;
	vxmin_saved = vxmin;
	vymin_saved = vymin;

	/* draw node label text at 1:1 100% scale */
	zfactor = 1.0;
	vxmin = n->finx;
	vymin = n->finy;

	cairo_scale(crp, zfactor, zfactor);

	/* popup the node label text */
	popup_nodelabel(n, crp, w, h);

	/* restore mainwindow settings */
	zfactor = zfactor_saved;
	vxmin = vxmin_saved;
	vymin = vymin_saved;

	return (FALSE);
}
#endif

/* popup window with node label text, (x,y) current mouse pointer */
static void do_popup(struct gml_node *n, int x, int y)
{
	GdkWindow *window = NULL;
	GtkWidget *vbox1 = (GtkWidget *) 0;
	GtkWidget *popuparea1 = (GtkWidget *) 0;
	int xx = 0;
	int yy = 0;
	int pop = 1;

	/* if there is alreay a popup, keep it that way */
	if (popupwindow1) {
		return;
	}

	/* top level outer window
	 * can also be GTK_WINDOW_POPUP but then window is
	 * not managed by window manager
	 * with POPUP the popup window is at (0,0) on the screen
	 * with TOPLEVEL the window can be at mouse position
	 * instead of next to mouse position
	 *the positioning of the popup window can be optimized
	 */
	if (pop) {
		popupwindow1 = gtk_window_new(GTK_WINDOW_POPUP /* or GTK_WINDOW_TOPLEVEL */ );
	} else {
		popupwindow1 = gtk_window_new( /* GTK_WINDOW_POPUP or */ GTK_WINDOW_TOPLEVEL);
	}

	/* make sure to exit oke. */
	g_signal_connect(G_OBJECT(popupwindow1), "destroy", G_CALLBACK(no_popup), NULL);

	/* needed for the cairo drawing */
	gtk_widget_set_app_paintable(popupwindow1, TRUE);

	/* set some title */
	gtk_window_set_title(GTK_WINDOW(popupwindow1), "label");

	/* pre-set size of full sized label text */
	gtk_window_set_default_size(GTK_WINDOW(popupwindow1), (n->fbbx + 5) /* XSIZE */ ,
				    n->fbby + 5 /* YSIZE */ );

	/* decorate the window */
	gtk_window_set_decorated(GTK_WINDOW(popupwindow1), FALSE);

	/* vbox1 */
#if GTK_HAVE_API_VERSION_2 == 1
	vbox1 = gtk_vbox_new( /* homogeneous */ FALSE, /* spacing */ 0);
	gtk_widget_show(vbox1);
	gtk_container_add(GTK_CONTAINER(popupwindow1), vbox1);
#endif

#if GTK_HAVE_API_VERSION_3 == 1
	vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, /* spacing */ 0);
	gtk_widget_show(vbox1);
	gtk_container_add(GTK_CONTAINER(popupwindow1), vbox1);
#endif

#if GTK_HAVE_API_VERSION_4 == 1
	/* todo add gtk-4 support */
#endif

	/* where to draw in hbox1 */
	popuparea1 = gtk_drawing_area_new();
	gtk_box_pack_start( /* box */ GTK_BOX(vbox1), /* child */ popuparea1,
			   /* expand */ TRUE, /* fill */ TRUE,	/* padding */
			   PACKPADDING);
	gtk_widget_show(popuparea1);

#if GTK_HAVE_API_VERSION_2 == 1
	g_signal_connect(G_OBJECT(popuparea1), "expose_event", G_CALLBACK(popuparea1_expose_event), (gpointer) n);
#endif

#if GTK_HAVE_API_VERSION_3 == 1
	g_signal_connect(G_OBJECT(popuparea1), "draw", G_CALLBACK(popuparea1_draw_event), (gpointer) n);
#endif

	/* the label text drawing is in the expose/draw event */
	if (pop) {
		/* get position of window drawarea where mouse is */
		window = gtk_widget_get_window(drawingarea1);
		gdk_window_get_origin(window, &xx, &yy);
		/* move popup right at node */
		gtk_window_move(GTK_WINDOW(popupwindow1), xx + x + 15, yy + y + 0);
	}

	gtk_widget_show(popupwindow1);

	return;
}

/* dragging drawing when left button 1 is held down */
static gboolean on_motion_notify_event(GtkWidget * widget, GdkEventMotion * event)
{
	int x = 0;
	int y = 0;
	int idx = 0;
	int idy = 0;
	double gdelta = 0.0;
	double gsld = 0.0;
	double val = 0.0;
	int ival = 0;
	double dhw = 0.0;
	double dx = 0.0;
	double dy = 0.0;
	double hw = 0.0;
	double hh = 0.0;
	GdkModifierType state = 0;
	struct gml_node *n = NULL;

	/* check if there is node data to draw */
	if (validdata == 0) {
		/* make sure there is no popup windows */
		no_popup();
		return (TRUE);
	}

	if (event == NULL) {
		/* shouldnothappen */
	}

	/* where mouse click is on window and mouse status */
#if GTK_HAVE_API_VERSION_2 == 1
	gdk_window_get_pointer(widget->window, &x, &y, &state);
#endif
#if GTK_HAVE_API_VERSION_3 == 1
	if (event) {
		gdk_window_get_device_position(gtk_widget_get_window(widget), event->device, &x, &y, &state);
	} else {
		/* shouldnothappen */
		state = 0;
		x = 0;
		y = 0;
	}
#endif

	if ((state & GDK_BUTTON1_MASK) != 0) {
		idx = (mouse_oldx - x);
		idy = (mouse_oldy - y);
		if (option_gdebug) {
			printf("%s(): mouse is at (%d,%d) delta is (%d,%d)\n", __func__, x, y, idx, idy);
			fflush(stdout);
		}

		if ((idx == 0) && (idy == 0)) {
			return (TRUE);
		}

		if (idx != 0) {
			hw = (double)(x);
			dx = (double)(mouse_oldx + vxmin) / zfactor;
			dhw = ((double)(hw + vxmin) / zfactor);
			gdelta = dx - dhw;
			vxmin = vxmin + (int)gdelta;
			if (vxmin < 0) {
				vxmin = 0;
			}
			if (vxmin > maxx) {
				vxmin = maxx;
			}
			/* */
			gsld = (gdelta / maxx);
			gsld = (gsld * 100);
			val = gtk_adjustment_get_value(GTK_ADJUSTMENT(adjhscale1));
			ival = (int)val;
			ival = ival + (int)gsld;
			if (ival < 0) {
				ival = 0;
			}
			if (ival > 100) {
				ival = 100;
			}
			gtk_adjustment_set_value(GTK_ADJUSTMENT(adjhscale1), ival);
		}

		if (idy != 0) {
			hh = (double)(y);
			dy = (double)(mouse_oldy + vymin) / zfactor;
			dhw = (hh + vymin) / zfactor;
			gdelta = dy - dhw;
			vymin = vymin + (int)gdelta;
			if (vymin < 0) {
				vymin = 0;
			}
			if (vymin > maxy) {
				vymin = maxy;
			}
			/* */
			gsld = (gdelta / maxy);
			gsld = (gsld * 100);
			val = gtk_adjustment_get_value(GTK_ADJUSTMENT(adjvscale2));
			ival = (int)val;
			ival = ival + (int)gsld;
			if (ival < 0) {
				ival = 0;
			}
			if (ival > 100) {
				ival = 100;
			}
			gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale2), ival);
		}

		/* save */
		mouse_oldx = x;
		mouse_oldy = y;
		/* only redraw needed */
		gtk_widget_queue_draw(drawingarea1);
	}

	/* show popup window with node label text if option is set */
	if (option_popup) {

		/* only if there is no popup */

		/* check if node is at mouse location */
		n = is_node_at_xy(x, y);
		if (n) {
			/* node text must have a size */
			if (n->fbbx && n->fbby) {
				/* popup window with node label text */
				do_popup(n, x, y);
			}
		} else {
			/* make sure there is no popup windows */
			no_popup();
		}

	} else {
		/* make sure there is no popup windows */
		no_popup();
	}

	return (TRUE);
}

/* mouse click on drawing area
	 *
	 * guint event->type has this info
	 * enum GdkEventType
	 * {
	 * .
	 * GDK_BUTTON_PRESS    = 4, (single click)
	 * GDK_2BUTTON_PRESS   = 5, (double click)
	 * GDK_3BUTTON_PRESS   = 6, (triple click)
	 * GDK_BUTTON_RELEASE  = 7, (released)
	 * ...
	 * };
	 * which button is clicked is in guint event->button;
	 * the button which was pressed or released, numbered from 1 to 5.
	 * Normally button 1 is the left mouse button,
	 * 2 is the middle button, and 3 is the right button.
	 * On 2-button mice, the middle button can often be simulated
	 * by pressing both mouse buttons together.
	 * for dragging the mouse (x,y) is saved.
 */
static gboolean on_mouse_clicked(GtkWidget * widget, GdkEventButton * event, gpointer user_data)
{
	int eventbutton = 0;
	double dx = 0.0;
	double dy = 0.0;
	int nx = 0;
	int ny = 0;
	int ex = 0;
	int ey = 0;
	if (widget) {
	}
	if (user_data) {
	}
	/* check if there is node data to draw */
	if (validdata == 0) {
		return (TRUE);
	}
	/* get where clicked in the drawing */
	ex = (event->x);
	ey = (event->y);
	dx = ((double)ex / zfactor);
	dy = ((double)ey / zfactor);
	nx = ((int)dx) + vxmin;
	ny = ((int)dy) + vymin;
	if (nx) {
	}
	if (ny) {
	}
	/* check the buttons */
	eventbutton = (int)(event->button);
	/* check the buttons after modification */
	if (eventbutton == 1) {
		/* left button drag drawing using motion_notify_event */
		mouse_oldx = ex;
		mouse_oldy = ey;
		return (TRUE);
	}
	if (eventbutton == 2) {
		/* middle button clicked */
		return (TRUE);
	}
	if (eventbutton == 3) {
		/* right button clicked */
		return (TRUE);
	}
	if (eventbutton == 4) {
		/* button 4 clicked */
		return (TRUE);
	}
	if (eventbutton == 5) {
		/* button 5 clicked */
		return (TRUE);
	}
	if (eventbutton == 6) {
		return TRUE;
	}
	if (eventbutton == 7) {
		return TRUE;
	}
	if (eventbutton == 8) {
		/* lower side button */
		return TRUE;
	}
	if (eventbutton == 9) {
		/* upper side button */
		return TRUE;
	}
	/* unknown button */
	return TRUE;
}

/* debug print layout of one cluster */
static void do_layout_all_rprint(struct gml_graph *g)
{
	struct gml_nlist *lnl = NULL;
	char *s = NULL;

	lnl = g->nodelist;

	while (lnl) {
		s = "";
		if (lnl->node->dummy) {
			s = "dummynode";
		}
		if (lnl->node->elabel) {
			s = "edgelabel";
		}
		printf("%s(): node %d is at (%d,%d) %s\n", __func__, lnl->node->nr, lnl->node->relx, lnl->node->rely, s);
		lnl = lnl->next;
	}

	return;
}

/* incremental layout */
static void do_layout_all_r(struct gml_graph *g)
{
	struct gml_glist *gl = NULL;

	if (g == NULL) {
		return;
	}

	gl = g->subglist;

	while (gl) {
		do_layout_all_r(gl->sg);
		gl = gl->next;
	}

	/* skip the subgraphs */
	if (g->type != SG_CLUSTER) {
		return;
	}

	printf("%s(): calculation layout of cluster `%s' `%s'\n", __func__, g->graphname, g->label);

	/* this are the incremental layout stages */

	/* re-organize nodelist */
	reorg(g);

	/* change cycles in the graph */
	uncycle(g);

	/* re-organize nodelist */
	reorg(g);

	/* longest path algorithm */
	longestpath(g);

	/* set y level of all nodes */
	ylevels(g);

	/* try to find shorter edges */
	shorteredges(g);

	/* change edge directions downwards */
	edgesdownwards(g, 1);

	/* check length of edges */
	edgelen(g);

	/* doublespace the vertical levels */
	doublespacey(g);

	/* split edges with label into node->label->node */
	edgelabels(g);

	/* after edge label nodes are created:
	 * calculate (x,y) size of text area
	 */
	static_maingtk_textsizes();

	/* split longer edges */
	splitedges(g);

	/* create level node count data */
	nodecounts(g);

	/* run barycenter using defaults (0,0) or a value */
	barycenter(g, 0, 0);

	/* force postype */
	postype = 1;
	/* set the value for the new pos type */
	gtk_spin_button_set_value((GtkSpinButton *) posbutton, postype);

	improve_positions(g);

	/* print results */
	if (yydebug || 0) {
		do_layout_all_rprint(g);
	}

	return;
}

/* run all stages of the layout */
static void do_layout_all(struct gml_graph *g)
{
	struct gml_glist *gl = NULL;

	if (incrlayout /* 0 */  && maingraph->tnclusters) {
		printf("%s(): doing incremental layout for %d clusters\n", __func__, maingraph->tnclusters);

		/* prepare */
		prepincr(g);

		/* recursively layout the clusters */
		gl = maingraph->subglist;

		while (gl) {
			do_layout_all_r(gl->sg);
			gl = gl->next;
		}

	} else {
		/* this are the regular layout stages */

		/* prepare */
		prep(g);

		/* re-organize nodelist */
		reorg(g);

		/* change cycles in the graph */
		uncycle(g);

		/* re-organize nodelist */
		reorg(g);

		/* longest path algorithm */
		longestpath(g);

		/* set y level of all nodes */
		ylevels(g);

		/* try to find shorter edges */
		shorteredges(g);

		/* change edge directions downwards */
		edgesdownwards(g, 1);

		/* check length of edges */
		edgelen(g);

		/* doublespace the vertical levels */
		doublespacey(g);

		/* split edges with label into node->label->node */
		edgelabels(g);

		/* after edge label nodes are created:
		 * calculate (x,y) size of text area
		 */
		static_maingtk_textsizes();

		/* split longer edges */
		splitedges(g);

		/* create level node count data */
		nodecounts(g);

		/* run barycenter using defaults (0,0) or a value */
		barycenter(g, 100, 100);

		/* run priority algorithm */
		improve_positions(g);

		/* final (x,y) positioning of nodes/edges */
		finalxy(g);

		/* calculate edge connections */
		/* XXXX tofix this can fail */
		edgeconnections(g);
	}

	return;
}

/* run all stages of the layout */
static void do_relayout_all(struct gml_graph *g)
{
	/* also possible to re-layout only 1 specific subgraph */
	if (g) {
	}

	do_clear_all( /* keep raw data */ 1);
	do_layout_all(maingraph);
	fflush(stdout);

	/* set sliders to defaults */
	zfactor = 1.0;
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale1), 50);

	vxmin = 0;
	vymin = 0;
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale2), 0);
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjhscale1), 0);

	/* fit drawing in window */
	dofit();

	validdata = 1;

	/* update status text */
	update_status_text(NULL);

	return;
}

/* clear all memory used by the graph data
 * if mode==0 clear all data
 * if mode==1 keep some data
 * used in a re-layout
 */
static void do_clear_all(int mode)
{

	/* no draw data */
	validdata = 0;

	if (mode == 0) {
		/* clear db with strings */
		clear_uniqstr();

		/* clear db with nodes */
		clear_uniqnode(NULL);

		/* clear db with graph pointers */
		clear_uniqgraph(NULL);
	}

	/* clear db with nodes */
	clear_uniqnode2(NULL);

	if (maingraph) {

		/* clear number of edges between level n and n+1 */
		clear_nume_r(maingraph);

		/* clear number of nodes at level */
		clear_nnl_r(maingraph);

		/* clear arrays in/out edges */
		clear_ioedges_r(maingraph);

		/* clear count of crossing edges at level */
		clear_numce_r(maingraph);

		/* clear optional record label and html of node */
		if (mode == 0) {
			clear_rlabel_r(maingraph);
			clear_hlabel_r(maingraph);
		}

		/* clear self-edges list */
		clear_selfedgesnodelist_r(maingraph);

		/* clear single nodes list */
		clear_singlenodelist_r(maingraph);

		/* clear startnodes array */
		clear_startnodes_r(maingraph);

		/* clear nodes list and its data
		 * if mode<>0 then keep record label data
		 * that will be re-used at doing re-layout
		 * if mode==0 clear the rlabel data
		 */
		clear_nodelist_r(maingraph, mode);

		/* clear edges list */
		clear_edgelist_r(maingraph);

		/* clear bubbling algorithm */
		clear_bubbling(maingraph);

		if (mode == 0) {
			/* clear subgraphs and optional summary node */
			clear_sg(maingraph);

			/* clear input nodes */
			clear_rawnodelist(maingraph);

			/* clear input edges */
			clear_rawedgelist(maingraph);

			/* clear main graph structure */
			dp_free(maingraph);

			maingraph = NULL;
		}
	}

	return;
}

/* finally stop the gui */
static void top_level_window_main_quit(void)
{

	do_clear_all(0);

	if (lastopendir) {
		dp_free(lastopendir);
		lastopendir = NULL;
	}
	if (lastsavedir) {
		dp_free(lastsavedir);
		lastsavedir = NULL;
	}

	/* run the gtk internal routine to stop gtk_main() which is a for(){} loop */
	gtk_main_quit();

	return;
}

/* use full screen */
static void on_top_level_window_fullscreen1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	if (menuitem) {
	}
	if (user_data) {
	}
	gtk_window_fullscreen(GTK_WINDOW(mainwindow1));
	return;
}

/* use screen in a window */
static void on_top_level_window_unfullscreen1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	if (menuitem) {
	}
	if (user_data) {
	}
	gtk_window_unfullscreen(GTK_WINDOW(mainwindow1));
	return;
}

/* 'open' in 'file' menu activated - sub menu in menu items in menu bar in vbox1 */
static void on_top_level_window_open1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkWidget *edialog = (GtkWidget *) 0;
	GtkWidget *pdialog = (GtkWidget *) 0;
	GtkWidget *dialog = (GtkWidget *) 0;
	char *file_chooser_filename = (char *)0;
	char *file_chooser_dir = (char *)0;
	GtkFileChooser *chooser = NULL;
	char *inputfilename = (char *)0;
	char *baseinputfilename = (char *)0;
	char *baseinputfilename2 = (char *)0;
	gzFile fgml = (gzFile) 0;
	char *bname = NULL;
	int cnt = 0;

	if (menuitem) {
	}
	if (user_data) {
	}

#if GTK_HAVE_API_VERSION_2 == 1

	/* see gimp source code howto */
	dialog = gtk_file_chooser_dialog_new("Select GML Graph File", 0,	/* parent_window */
					     GTK_FILE_CHOOSER_ACTION_OPEN,
					     GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

#endif

#if GTK_HAVE_API_VERSION_3 == 1

	/* see gimp source code howto */
	dialog = gtk_file_chooser_dialog_new("Select GML Graph File", GTK_WINDOW(mainwindow1)	/* parent_window */
					     ,
					     GTK_FILE_CHOOSER_ACTION_OPEN,
					     "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);

#endif

	chooser = GTK_FILE_CHOOSER(dialog);

	/* use same dir if opened in earlier dir */
	if (lastopendir) {
		gtk_file_chooser_set_current_folder(chooser, lastopendir);
	}

	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(mainwindow1));

	/* run the window to select a input file */
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
		/* open button */
		file_chooser_filename = (char *)gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		file_chooser_dir = (char *)gtk_file_chooser_get_current_folder(chooser);
	} else {
		/* cancel button */
		(void)gtk_widget_destroy(dialog);
		return;
	}

	/* */
	(void)gtk_widget_destroy(dialog);

	/* update last-used-dir */
	if (file_chooser_dir) {
		if (lastopendir) {
			(void)dp_free(lastopendir);
		}
		lastopendir = dp_calloc(1, (strlen(file_chooser_dir) + 1));
		strcpy(lastopendir, file_chooser_dir);
		/* not dp_free() because gtk allocated */
		g_free(file_chooser_dir);
	}

	/* copy the input filename from gtk */
	if (file_chooser_filename) {
		inputfilename = dp_calloc(1, (strlen(file_chooser_filename) + 1));
		strcpy(inputfilename, file_chooser_filename);
		/* not dp_free() because gtk allocated */
		g_free(file_chooser_filename);
	} else {
		return;
	}

	/* set filename in window */
	bname = g_path_get_basename(inputfilename);
	baseinputfilename2 = dp_calloc(1, (strlen(bname) + 1));
	strcpy(baseinputfilename2, bname);
	/* not dp_free() because gtk allocated */
	g_free(bname);

	/* open file to parse */
	errno = 0;
	fgml = gzopen(inputfilename, "r");

	if (fgml == (gzFile) 0) {
		edialog = gtk_message_dialog_new(GTK_WINDOW(mainwindow1),
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR,
						 GTK_BUTTONS_CLOSE,
						 "Cannot open file %s for reading (%s)", inputfilename, g_strerror(errno));
		gtk_dialog_run(GTK_DIALOG(edialog));
		gtk_widget_destroy(edialog);
		dp_free(inputfilename);
		dp_free(baseinputfilename2);
		/* data is unchanged, so keep validdata status */
		return;
	}

	/* type of graph data 0=gml 1=dot 2=vcg */
	graphtype = 0;

	do_clear_all(0);

	/* background r/g/b of drawing */
	bgcr = 0xff;
	bgcg = 0xff;
	bgcb = 0xff;

	/* create root graph */
	create_maingraph();

	/* parse the gml data */
	if (gmlparse(maingraph, fgml, baseinputfilename2)) {
		/* parse error */
		if (strlen(parsermessage) == 0) {
			strcpy(parsermessage, "no parser message");
		}
		pdialog = gtk_message_dialog_new(GTK_WINDOW(mainwindow1),
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", parsermessage);
		gtk_dialog_run(GTK_DIALOG(pdialog));
		gtk_widget_destroy(pdialog);
		dp_free(inputfilename);
		dp_free(baseinputfilename2);
		gzclose(fgml);
		/* data is invalid at this point */
		validdata = 0;
		do_clear_all(0);
		/* use package string program name as set by configure in config.h */
		gtk_window_set_title(GTK_WINDOW(mainwindow1), PACKAGE_STRING);
		/* re draw screen */
		gtk_widget_queue_draw(drawingarea1);
		return;
	}

	gzclose(fgml);

	bname = g_path_get_basename(inputfilename);
	baseinputfilename = uniqstr(bname);
	/* not dp_free because gtk allocated */
	g_free(bname);

	gtk_window_set_title(GTK_WINDOW(mainwindow1), baseinputfilename);

	/* check for empty graph here */
	if (maingraph->rawnodelist) {

		printf("%s(): calculating layout of file %s\n", __func__, baseinputfilename2);
		fflush(stdout);

		/* update status text */
		update_status_text("Wait ... Calculating Layout");

		cnt = 1000;
		while (gtk_events_pending()) {
			cnt--;
			if (cnt > 0) {
				gtk_main_iteration();
				/* this updates the status text */
			}
		}

		do_layout_all(maingraph);

		fflush(stdout);

		/* update status text */
		update_status_text(NULL);

		while (gtk_main_iteration()) {
			/* this should update the status text */ ;
		}

		/* set sliders to defaults */
		zfactor = 1.0;
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale1), 50);

		vxmin = 0;
		vymin = 0;
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale2), 0);
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjhscale1), 0);

		/* filename is not saved */
		dp_free(inputfilename);
		dp_free(baseinputfilename2);

		/* fit drawing in window */
		dofit();

		validdata = 1;
	} else {
		/* filename is not saved */
		dp_free(inputfilename);
		dp_free(baseinputfilename2);
		/* update status text */
		update_status_text("Empty graph ... No Nodes");
		validdata = 0;
	}

	/* re draw screen */
	gtk_widget_queue_draw(drawingarea1);

	return;
}

/* 'open' in 'file' menu activated - sub menu in menu items in menu bar in vbox1 */
static void on_top_level_window_open2_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkWidget *edialog = (GtkWidget *) 0;
	GtkWidget *pdialog = (GtkWidget *) 0;
	GtkWidget *dialog = (GtkWidget *) 0;
	char *file_chooser_filename = (char *)0;
	char *file_chooser_dir = (char *)0;
	GtkFileChooser *chooser = NULL;
	char *inputfilename = (char *)0;
	char *baseinputfilename = (char *)0;
	char *baseinputfilename2 = (char *)0;
	FILE *f = NULL;
	char *bname = NULL;
	int cnt = 0;

	if (menuitem) {
	}
	if (user_data) {
	}

#if GTK_HAVE_API_VERSION_2 == 1

	/* see gimp source code howto */
	dialog = gtk_file_chooser_dialog_new("Select DOT Graph File", 0,	/* parent_window */
					     GTK_FILE_CHOOSER_ACTION_OPEN,
					     GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

#endif

#if GTK_HAVE_API_VERSION_3 == 1

	/* see gimp source code howto */
	dialog = gtk_file_chooser_dialog_new("Select DOT Graph File", GTK_WINDOW(mainwindow1)	/* parent_window */
					     ,
					     GTK_FILE_CHOOSER_ACTION_OPEN,
					     "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);

#endif

	chooser = GTK_FILE_CHOOSER(dialog);

	/* use same dir if opened in earlier dir */
	if (lastopendir) {
		gtk_file_chooser_set_current_folder(chooser, lastopendir);
	}

	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(mainwindow1));

	/* run the window to select a input file */
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
		/* open button */
		file_chooser_filename = (char *)gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		file_chooser_dir = (char *)gtk_file_chooser_get_current_folder(chooser);
	} else {
		/* cancel button */
		(void)gtk_widget_destroy(dialog);
		return;
	}

	/* */
	(void)gtk_widget_destroy(dialog);

	/* update last-used-dir */
	if (file_chooser_dir) {
		if (lastopendir) {
			(void)dp_free(lastopendir);
		}
		lastopendir = dp_calloc(1, (strlen(file_chooser_dir) + 1));
		strcpy(lastopendir, file_chooser_dir);
		/* not dp_free() because gtk allocated */
		g_free(file_chooser_dir);
	}

	/* copy the input filename from gtk */
	if (file_chooser_filename) {
		inputfilename = dp_calloc(1, (strlen(file_chooser_filename) + 1));
		if (inputfilename) {
			strcpy(inputfilename, file_chooser_filename);
		}
		/* not dp_free() because gtk allocated */
		g_free(file_chooser_filename);
	} else {
		return;
	}

	/* set filename in window */
	bname = g_path_get_basename(inputfilename);
	baseinputfilename2 = dp_calloc(1, (strlen(bname) + 1));
	strcpy(baseinputfilename2, bname);

	/* not dp_free() because gtk allocated */
	g_free(bname);

	/* open file to parse */
	errno = 0;
	f = fopen(inputfilename, "r");

	if (f == NULL) {
		edialog = gtk_message_dialog_new(GTK_WINDOW(mainwindow1),
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR,
						 GTK_BUTTONS_CLOSE,
						 "Cannot open file %s for reading (%s)", inputfilename, g_strerror(errno));
		gtk_dialog_run(GTK_DIALOG(edialog));
		gtk_widget_destroy(edialog);
		dp_free(inputfilename);
		dp_free(baseinputfilename2);
		/* data is unchanged, so keep validdata status */
		return;
	}

	/* type of graph data 0=gml 1=dot 2=vcg */
	graphtype = 1;

	do_clear_all(0);

	/* background r/g/b of drawing */
	bgcr = 0xff;
	bgcg = 0xff;
	bgcb = 0xff;

	/* create root graph */
	create_maingraph();

	/* parse the dot data */
	if (dotparse(maingraph, f, baseinputfilename2, argv0)) {
		/* parse error */
		if (strlen(parsermessage) == 0) {
			strcpy(parsermessage, "no parser message");
		}
		pdialog = gtk_message_dialog_new(GTK_WINDOW(mainwindow1),
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", parsermessage);
		gtk_dialog_run(GTK_DIALOG(pdialog));
		gtk_widget_destroy(pdialog);
		dp_free(inputfilename);
		dp_free(baseinputfilename2);
		fflush(stdout);
		fclose(f);
		/* data is invalid at this point */
		validdata = 0;
		do_clear_all(0);
		/* use package string program name as set by configure in config.h */
		gtk_window_set_title(GTK_WINDOW(mainwindow1), PACKAGE_STRING);
		/* re draw screen */
		gtk_widget_queue_draw(drawingarea1);
		return;
	}

	fclose(f);

	bname = g_path_get_basename(inputfilename);

	baseinputfilename = uniqstr(bname);

	/* not dp_free() because gtk allocated */
	g_free(bname);

	gtk_window_set_title(GTK_WINDOW(mainwindow1), baseinputfilename);

	/* check for empty graph here */
	if (maingraph->rawnodelist) {

		printf("%s(): calculating layout of file %s\n", __func__, baseinputfilename2);
		fflush(stdout);

		/* update status text */
		update_status_text("Wait ... Calculating Layout");

		cnt = 1000;
		while (gtk_events_pending()) {
			cnt--;
			if (cnt > 0) {
				gtk_main_iteration();
				/* this updates the status text */
			}
		}

		do_layout_all(maingraph);

		fflush(stdout);

		/* update status text */
		update_status_text(NULL);

		cnt = 1000;
		while (gtk_main_iteration()) {
			cnt--;
			if (cnt > 0) {
				/* this should update the status text */ ;
			}
		}

		/* set sliders to defaults */
		zfactor = 1.0;
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale1), 50);

		vxmin = 0;
		vymin = 0;
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale2), 0);
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjhscale1), 0);

		/* filename is not saved */
		dp_free(inputfilename);
		dp_free(baseinputfilename2);

		/* fit drawing in window */
		dofit();

		validdata = 1;
	} else {
		/* filename is not saved */
		dp_free(inputfilename);
		dp_free(baseinputfilename2);

		/* update status text */
		update_status_text("Empty graph ... No Nodes");
		validdata = 0;
	}

	/* re draw screen */
	gtk_widget_queue_draw(drawingarea1);

	return;
}

/* 'open' in 'file' menu activated - sub menu in menu items in menu bar in vbox1 */
static void on_top_level_window_open3_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkWidget *edialog = (GtkWidget *) 0;
	GtkWidget *pdialog = (GtkWidget *) 0;
	GtkWidget *dialog = (GtkWidget *) 0;
	char *file_chooser_filename = (char *)0;
	char *file_chooser_dir = (char *)0;
	GtkFileChooser *chooser = NULL;
	char *inputfilename = (char *)0;
	char *baseinputfilename = (char *)0;
	char *baseinputfilename2 = (char *)0;
	FILE *f = NULL;
	char *bname = NULL;

	if (menuitem) {
	}
	if (user_data) {
	}

#if GTK_HAVE_API_VERSION_2 == 1

	/* see gimp source code howto */
	dialog = gtk_file_chooser_dialog_new("Select VCG Graph File", 0,	/* parent_window */
					     GTK_FILE_CHOOSER_ACTION_OPEN,
					     GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

#endif

#if GTK_HAVE_API_VERSION_3 == 1

	/* see gimp source code howto */
	dialog = gtk_file_chooser_dialog_new("Select VCG Graph File", GTK_WINDOW(mainwindow1)	/* parent_window */
					     ,
					     GTK_FILE_CHOOSER_ACTION_OPEN,
					     "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);

#endif

	chooser = GTK_FILE_CHOOSER(dialog);

	/* use same dir if opened in earlier dir */
	if (lastopendir) {
		gtk_file_chooser_set_current_folder(chooser, lastopendir);
	}

	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(mainwindow1));

	/* run the window to select a input file */
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
		/* open button */
		file_chooser_filename = (char *)gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		file_chooser_dir = (char *)gtk_file_chooser_get_current_folder(chooser);
	} else {
		/* cancel button */
		(void)gtk_widget_destroy(dialog);
		return;
	}

	/* */
	(void)gtk_widget_destroy(dialog);

	/* update last-used-dir */
	if (file_chooser_dir) {
		if (lastopendir) {
			(void)dp_free(lastopendir);
		}
		lastopendir = dp_calloc(1, (strlen(file_chooser_dir) + 1));
		strcpy(lastopendir, file_chooser_dir);
		/* not dp_free() because gtk allocated */
		g_free(file_chooser_dir);
	}

	/* copy the input filename from gtk */
	if (file_chooser_filename) {
		inputfilename = dp_calloc(1, (strlen(file_chooser_filename) + 1));
		if (inputfilename) {
			strcpy(inputfilename, file_chooser_filename);
		}
		/* not dp_free() because gtk allocated */
		g_free(file_chooser_filename);
	} else {
		return;
	}

	/* set filename in window */
	bname = g_path_get_basename(inputfilename);

	baseinputfilename2 = dp_calloc(1, (strlen(bname) + 1));
	strcpy(baseinputfilename2, bname);

	/* not dp_free() because gtk allocated */
	g_free(bname);

	/* open file to parse */
	errno = 0;
	f = fopen(inputfilename, "r");

	if (f == NULL) {
		edialog = gtk_message_dialog_new(GTK_WINDOW(mainwindow1),
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR,
						 GTK_BUTTONS_CLOSE,
						 "Cannot open file %s for reading (%s)", inputfilename, g_strerror(errno));
		gtk_dialog_run(GTK_DIALOG(edialog));
		gtk_widget_destroy(edialog);
		dp_free(baseinputfilename2);
		dp_free(inputfilename);
		/* data is unchanged, so keep validdata status */
		return;
	}

	/* type of graph data 0=gml 1=dot 2=vcg */
	graphtype = 2;

	do_clear_all(0);

	/* background r/g/b of drawing */
	bgcr = 0xff;
	bgcg = 0xff;
	bgcb = 0xff;

	/* create root graph */
	create_maingraph();

	/* parse the vcg data */
	if (vcgparse(maingraph, f, baseinputfilename2, argv0)) {
		/* parse error */
		if (strlen(parsermessage) == 0) {
			strcpy(parsermessage, "no parser message");
		}
		pdialog = gtk_message_dialog_new(GTK_WINDOW(mainwindow1),
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", parsermessage);
		gtk_dialog_run(GTK_DIALOG(pdialog));
		gtk_widget_destroy(pdialog);
		dp_free(inputfilename);
		dp_free(baseinputfilename2);
		fflush(stdout);
		fclose(f);
		/* data is invalid at this point */
		validdata = 0;
		do_clear_all(0);
		/* use package string program name as set by configure in config.h */
		gtk_window_set_title(GTK_WINDOW(mainwindow1), PACKAGE_STRING);
		/* re draw screen */
		gtk_widget_queue_draw(drawingarea1);
		return;
	}

	fclose(f);

	bname = g_path_get_basename(inputfilename);
	baseinputfilename = uniqstr(bname);
	/* not dp_free because gtk allocated */
	g_free(bname);

	gtk_window_set_title(GTK_WINDOW(mainwindow1), baseinputfilename);

	/* check for empty graph here */
	if (maingraph->rawnodelist) {

		printf("%s(): calculating layout of file %s\n", __func__, baseinputfilename2);
		fflush(stdout);

		/* update status text */
		update_status_text("Wait ... Calculating Layout");

		while (gtk_events_pending()) {
			gtk_main_iteration();
			/* this updates the status text */
		}

		do_layout_all(maingraph);

		fflush(stdout);

		/* update status text */
		update_status_text(NULL);

		while (gtk_main_iteration()) {
			/* this should update the status text */ ;
		}

		/* set sliders to defaults */
		zfactor = 1.0;
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale1), 50);

		vxmin = 0;
		vymin = 0;
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale2), 0);
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjhscale1), 0);

		/* filename is not saved */
		dp_free(inputfilename);
		dp_free(baseinputfilename2);
		/* fit drawing in window */
		dofit();

		validdata = 1;
	} else {
		/* filename is not saved */
		dp_free(inputfilename);
		dp_free(baseinputfilename2);
		/* update status text */
		update_status_text("Empty graph ... No Nodes");
		validdata = 0;
	}

	/* re draw screen */
	gtk_widget_queue_draw(drawingarea1);

	return;
}

/* 'open' in 'file' menu activated - sub menu in menu items in menu bar in vbox1 */
static void on_top_level_window_open4_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkWidget *edialog = (GtkWidget *) 0;
	GtkWidget *pdialog = (GtkWidget *) 0;
	GtkWidget *dialog = (GtkWidget *) 0;
	char *file_chooser_filename = (char *)0;
	char *file_chooser_dir = (char *)0;
	GtkFileChooser *chooser = NULL;
	char *inputfilename = (char *)0;
	char *baseinputfilename = (char *)0;
	char *baseinputfilename2 = (char *)0;
	FILE *f = NULL;
	char *bname = NULL;

	if (menuitem) {
	}
	if (user_data) {
	}

#if GTK_HAVE_API_VERSION_2 == 1

	/* see gimp source code howto */
	dialog = gtk_file_chooser_dialog_new("Select JGF Graph File", 0,	/* parent_window */
					     GTK_FILE_CHOOSER_ACTION_OPEN,
					     GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

#endif

#if GTK_HAVE_API_VERSION_3 == 1

	/* see gimp source code howto */
	dialog = gtk_file_chooser_dialog_new("Select JGF Graph File", GTK_WINDOW(mainwindow1)	/* parent_window */
					     ,
					     GTK_FILE_CHOOSER_ACTION_OPEN,
					     "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);

#endif

	chooser = GTK_FILE_CHOOSER(dialog);

	/* use same dir if opened in earlier dir */
	if (lastopendir) {
		gtk_file_chooser_set_current_folder(chooser, lastopendir);
	}

	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(mainwindow1));

	/* run the window to select a input file */
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
		/* open button */
		file_chooser_filename = (char *)gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		file_chooser_dir = (char *)gtk_file_chooser_get_current_folder(chooser);
	} else {
		/* cancel button */
		(void)gtk_widget_destroy(dialog);
		return;
	}

	/* */
	(void)gtk_widget_destroy(dialog);

	/* update last-used-dir */
	if (file_chooser_dir) {
		if (lastopendir) {
			(void)dp_free(lastopendir);
		}
		lastopendir = dp_calloc(1, (strlen(file_chooser_dir) + 1));
		strcpy(lastopendir, file_chooser_dir);
		/* not dp_free() because gtk allocated */
		g_free(file_chooser_dir);
	}

	/* copy the input filename from gtk */
	if (file_chooser_filename) {
		inputfilename = dp_calloc(1, (strlen(file_chooser_filename) + 1));
		if (inputfilename) {
			strcpy(inputfilename, file_chooser_filename);
		}
		/* node dp_free() because gtk allocated */
		g_free(file_chooser_filename);
	} else {
		return;
	}

	/* set filename in window */
	bname = g_path_get_basename(inputfilename);

	baseinputfilename2 = dp_calloc(1, (strlen(bname) + 1));
	strcpy(baseinputfilename2, bname);

	/* not dp_free() because gtk allocated */
	g_free(bname);

	/* open file to parse */
	errno = 0;
	f = fopen(inputfilename, "r");

	if (f == NULL) {
		edialog = gtk_message_dialog_new(GTK_WINDOW(mainwindow1),
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR,
						 GTK_BUTTONS_CLOSE,
						 "Cannot open file %s for reading (%s)", inputfilename, g_strerror(errno));
		gtk_dialog_run(GTK_DIALOG(edialog));
		gtk_widget_destroy(edialog);
		dp_free(inputfilename);
		dp_free(baseinputfilename2);
		/* data is unchanged, so keep validdata status */
		return;
	}

	/* type of graph data 0=gml 1=dot 2=vcg 3=jgf */
	graphtype = 3;

	do_clear_all(0);

	/* background r/g/b of drawing */
	bgcr = 0xff;
	bgcg = 0xff;
	bgcb = 0xff;

	/* create root graph */
	create_maingraph();

	/* parse the vcg data */
	if (jgfparse(maingraph, f, baseinputfilename2, argv0)) {
		/* parse error */
		if (strlen(parsermessage) == 0) {
			strcpy(parsermessage, "no parser message");
		}
		pdialog = gtk_message_dialog_new(GTK_WINDOW(mainwindow1),
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", parsermessage);
		gtk_dialog_run(GTK_DIALOG(pdialog));
		gtk_widget_destroy(pdialog);
		dp_free(inputfilename);
		dp_free(baseinputfilename2);
		fflush(stdout);
		fclose(f);
		/* data is invalid at this point */
		validdata = 0;
		do_clear_all(0);
		/* use package string program name as set by configure in config.h */
		gtk_window_set_title(GTK_WINDOW(mainwindow1), PACKAGE_STRING);
		/* re draw screen */
		gtk_widget_queue_draw(drawingarea1);
		return;
	}

	fclose(f);

	bname = g_path_get_basename(inputfilename);
	baseinputfilename = uniqstr(bname);

	/* not dp_free() because gtk allocated */
	g_free(bname);

	gtk_window_set_title(GTK_WINDOW(mainwindow1), baseinputfilename);

	/* check for empty graph here */
	if (maingraph->rawnodelist) {

		printf("%s(): calculating layout of file %s\n", __func__, baseinputfilename2);
		fflush(stdout);

		/* update status text */
		update_status_text("Wait ... Calculating Layout");

		while (gtk_events_pending()) {
			gtk_main_iteration();
			/* this updates the status text */
		}

		do_layout_all(maingraph);

		fflush(stdout);

		/* update status text */
		update_status_text(NULL);

		while (gtk_main_iteration()) {
			/* this should update the status text */ ;
		}

		/* set sliders to defaults */
		zfactor = 1.0;
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale1), 50);

		vxmin = 0;
		vymin = 0;
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale2), 0);
		gtk_adjustment_set_value(GTK_ADJUSTMENT(adjhscale1), 0);

		/* fit drawing in window */
		dofit();

		validdata = 1;
	} else {
		/* update status text */
		update_status_text("Empty graph ... No Nodes");
		validdata = 0;
	}

	dp_free(inputfilename);
	dp_free(baseinputfilename2);

	/* re draw screen */
	gtk_widget_queue_draw(drawingarea1);

	return;
}

/* save as gtk svg */
static void on_top_level_window_svg1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkWidget *dialog = (GtkWidget *) 0;
	GtkWidget *edialog = (GtkWidget *) 0;
	char *file_chooser_filename = (char *)0;
	char *file_chooser_dir = (char *)0;
	GtkFileChooser *chooser = NULL;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res = 0;
	char *svgfilename = NULL;
	FILE *fstream = NULL;
	int mymaxx = 0;
	int mymaxy = 0;
	int saved_vxmin = 0;
	int saved_vymin = 0;
	cairo_surface_t *surface = NULL;
	cairo_t *crp = NULL;

	if (validdata == 0) {
		return;
	}

	if (menuitem) {
	}
	if (user_data) {
	}

	dialog = gtk_file_chooser_dialog_new("Save As SVG Image",
					     /* parent_window */ NULL,
					     action, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);

	chooser = GTK_FILE_CHOOSER(dialog);

	/* change to last used dir if any */
	if (lastsavedir) {
		gtk_file_chooser_set_current_folder(chooser, lastsavedir);
	}

	/* ask to override existing */
	gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

	/* get the filename */
	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(mainwindow1));

	res = gtk_dialog_run(GTK_DIALOG(dialog));

	if (res == GTK_RESPONSE_ACCEPT) {
		file_chooser_filename = gtk_file_chooser_get_filename(chooser);
		file_chooser_dir = gtk_file_chooser_get_current_folder(chooser);
	} else {
		/* cancel button */
		(void)gtk_widget_destroy(dialog);
		return;
	}

	/* update last-used-dir */
	if (file_chooser_dir) {
		if (lastsavedir) {
			dp_free(lastsavedir);
		}
		lastsavedir = dp_calloc(1, (strlen(file_chooser_dir) + 1));
		strcpy(lastsavedir, file_chooser_dir);
		/* not dp_free() because gtk allocated */
		g_free(file_chooser_dir);
	}

	/* */
	(void)gtk_widget_destroy(dialog);

	/* */
	if (file_chooser_filename) {
		svgfilename = dp_calloc(1, (strlen(file_chooser_filename) + 1));
		if (svgfilename) {
			strcpy(svgfilename, file_chooser_filename);
		}
		/* not dp_free() because gtk allocated */
		g_free(file_chooser_filename);
	} else {
		/* no filename */
		return;
	}

	errno = 0;
	fstream = fopen(svgfilename, "wb");

	/* check if open */
	if (fstream == NULL) {
		edialog = gtk_message_dialog_new(GTK_WINDOW(mainwindow1),
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR,
						 GTK_BUTTONS_CLOSE,
						 "Cannot open file %s for writing (%s)", svgfilename, g_strerror(errno));
		gtk_dialog_run(GTK_DIALOG(edialog));
		gtk_widget_destroy(edialog);
		dp_free(svgfilename);
		return;
	}

	/* write the svg image data */

	/* save current gui settings */
	saved_vxmin = vxmin;
	saved_vymin = vymin;

	/* output whole drawing with a small border, then edge line at end is in drawing */
	vxmin = 0;
	vymin = 0;
	mymaxx = (int)((maxx + xspacing) * /* 1.0 */ zfactor);
	mymaxy = (int)((maxy + yspacing) * /* 1.0 */ zfactor);

	surface = cairo_svg_surface_create(svgfilename, mymaxx, mymaxy);

	/* */
	crp = cairo_create(surface);

	/* fill drawing background with background color */
	cairo_set_source_rgb(crp, bgcr / 255.0, bgcg / 255.0, bgcb / 255.0);

	/* select whole drawing to fill wth background color */
	cairo_rectangle(crp, 0, 0, mymaxx, mymaxy);

	cairo_fill(crp);

	/* use zoom slider drawing scale */
	cairo_scale(crp, /*1.0 */ zfactor, /*1.0 */ zfactor);

	on_top_level_window_drawingarea1_expose_event_edges(crp);
	on_top_level_window_drawingarea1_expose_event_nodes(crp);

	cairo_destroy(crp);
	cairo_surface_destroy(surface);

	/* restore screen (x,y) min */
	vxmin = saved_vxmin;
	vymin = saved_vymin;

	fclose(fstream);
	dp_free(svgfilename);

	return;
}

/* save as dia xml diagram */
static void on_top_level_window_dia1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkWidget *dialog = (GtkWidget *) 0;
	GtkWidget *edialog = (GtkWidget *) 0;
	char *file_chooser_filename = (char *)0;
	char *file_chooser_dir = (char *)0;
	GtkFileChooser *chooser = NULL;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res = 0;
	char *diafilename = NULL;
	FILE *fstream = NULL;

	if (validdata == 0) {
		return;
	}

	if (menuitem) {
	}
	if (user_data) {
	}

	dialog = gtk_file_chooser_dialog_new("Save As DIA diagram",
					     /* parent_window */ NULL,
					     action, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);

	chooser = GTK_FILE_CHOOSER(dialog);

	/* change to last used dir if any */
	if (lastsavedir) {
		gtk_file_chooser_set_current_folder(chooser, lastsavedir);
	}

	/* ask to override existing */
	gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

	/* get the filename */
	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(mainwindow1));

	res = gtk_dialog_run(GTK_DIALOG(dialog));

	if (res == GTK_RESPONSE_ACCEPT) {
		file_chooser_filename = gtk_file_chooser_get_filename(chooser);
		file_chooser_dir = gtk_file_chooser_get_current_folder(chooser);
	} else {
		/* cancel button */
		(void)gtk_widget_destroy(dialog);
		return;
	}

	/* update last-used-dir */
	if (file_chooser_dir) {
		if (lastsavedir) {
			dp_free(lastsavedir);
		}
		lastsavedir = dp_calloc(1, (strlen(file_chooser_dir) + 1));
		strcpy(lastsavedir, file_chooser_dir);
		/* not dp_free() because gtk allocated */
		g_free(file_chooser_dir);
	}

	/* */
	(void)gtk_widget_destroy(dialog);

	/* */
	if (file_chooser_filename) {
		diafilename = dp_calloc(1, (strlen(file_chooser_filename) + 1));
		strcpy(diafilename, file_chooser_filename);
		/* not dp_free() because gtk allocated */
		g_free(file_chooser_filename);
	} else {
		/* no filename */
		return;
	}

	errno = 0;
	fstream = fopen(diafilename, "wb");

	/* check if open */
	if (fstream == NULL) {
		edialog = gtk_message_dialog_new(GTK_WINDOW(mainwindow1),
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR,
						 GTK_BUTTONS_CLOSE,
						 "Cannot open file %s for writing (%s)", diafilename, g_strerror(errno));
		gtk_dialog_run(GTK_DIALOG(edialog));
		gtk_widget_destroy(edialog);
		dp_free(diafilename);
		return;
	}

	/* write the dia diagram */
	graph2dia(maingraph, fstream);

	fclose(fstream);
	dp_free(diafilename);

	return;
}

/* save as jgf json diagram json jgf version 2.1
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "$id": "http://jsongraphformat.info/v2.1/json-graph-schema.json",
  "title": "JSON Graph Schema",
  "oneOf": [
    {
      "type": "object",
      "properties": {
        "graph": { "$ref": "#/definitions/graph" }
      },
      "additionalProperties": false,
      "required": [
        "graph"
      ]
    },
    {
      "type": "object",
      "properties": {
        "graphs": {
          "type": "array",
          "items": { "$ref": "#/definitions/graph" }
        }
      },
      "additionalProperties": false
    }
  ],
  "definitions": {
    "graph": {
      "oneOf": [
        {
          "type": "object",
          "additionalProperties": false,
          "properties": {
            "id": { "type": "string" },
            "label": { "type": "string" },
            "directed": { "type": [ "boolean" ], "default": true },
            "type": { "type": "string" },
            "metadata": { "type": [ "object" ] },
            "nodes": {
              "type": "object",
              "additionalProperties": { "$ref": "#/definitions/node" }
            },
            "edges": {
              "type": [ "array" ],
              "items": { "$ref": "#/definitions/edge" }
            }
          }
        },
        {
          "type": "object",
          "additionalProperties": false,
          "properties": {
            "id": { "type": "string" },
            "label": { "type": "string" },
            "directed": { "type": [ "boolean" ], "default": true },
            "type": { "type": "string" },
            "metadata": { "type": [ "object" ] },
            "nodes": {
              "type": "object",
              "additionalProperties": { "$ref": "#/definitions/node" }
            },
            "hyperedges": {
              "type": [ "array" ],
              "items": { "$ref": "#/definitions/directedhyperedge" }
            }
          }
        },
        {
          "type": "object",
          "additionalProperties": false,
          "properties": {
            "id": { "type": "string" },
            "label": { "type": "string" },
            "directed": { "type": [ "boolean" ], "enum": [false] },
            "type": { "type": "string" },
            "metadata": { "type": [ "object" ] },
            "nodes": {
              "type": "object",
              "additionalProperties": { "$ref": "#/definitions/node" }
            },
            "hyperedges": {
              "type": [ "array" ],
              "items": { "$ref": "#/definitions/undirectedhyperedge" }
            }
          },
          "required": [ "directed" ]
        }
      ]
    },
    "node": {
      "type": "object",
      "properties": {
        "label": { "type": "string" },
        "metadata": { "type": "object" },
        "additionalProperties": false
      }
    },
    "edge": {
      "type": "object",
      "additionalProperties": false,
      "properties": {
        "id": { "type": "string" },
        "source": { "type": "string" },
        "target": { "type": "string" },
        "relation": { "type": "string" },
        "directed": { "type": [ "boolean" ], "default": true },
        "label": { "type": "string" },
        "metadata": { "type": [ "object" ] }
      },
      "required": [ "source", "target" ]
    },
    "directedhyperedge": {
      "type": "object",
      "additionalProperties": false,
      "properties": {
        "id": { "type": "string" },
        "source": { "type": "array", "items": { "type": "string" } },
        "target": { "type": "array", "items": { "type": "string" } },
        "relation": { "type": "string" },
        "label": { "type": "string" },
        "metadata": { "type": [ "object" ] }
      },
      "required": [ "source", "target" ]
    },
    "undirectedhyperedge": {
      "type": "object",
      "additionalProperties": false,
      "properties": {
        "id": { "type": "string" },
        "nodes": { "type": "array", "items": { "type": "string" } },
        "relation": { "type": "string" },
        "label": { "type": "string" },
        "metadata": { "type": [ "object" ] }
      },
      "required": [ "nodes" ]
    }
  }
}
*/
static void on_top_level_window_jgf1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkWidget *dialog = (GtkWidget *) 0;
	GtkWidget *edialog = (GtkWidget *) 0;
	char *file_chooser_filename = (char *)0;
	char *file_chooser_dir = (char *)0;
	GtkFileChooser *chooser = NULL;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res = 0;
	char *jgffilename = NULL;
	FILE *fstream = NULL;

	if (validdata == 0) {
		return;
	}

	if (menuitem) {
	}
	if (user_data) {
	}

	dialog = gtk_file_chooser_dialog_new("Save As JGF json",
					     /* parent_window */ NULL,
					     action, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);

	chooser = GTK_FILE_CHOOSER(dialog);

	/* change to last used dir if any */
	if (lastsavedir) {
		gtk_file_chooser_set_current_folder(chooser, lastsavedir);
	}

	/* ask to override existing */
	gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

	/* get the filename */
	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(mainwindow1));

	res = gtk_dialog_run(GTK_DIALOG(dialog));

	if (res == GTK_RESPONSE_ACCEPT) {
		file_chooser_filename = gtk_file_chooser_get_filename(chooser);
		file_chooser_dir = gtk_file_chooser_get_current_folder(chooser);
	} else {
		/* cancel button */
		(void)gtk_widget_destroy(dialog);
		return;
	}

	/* update last-used-dir */
	if (file_chooser_dir) {
		if (lastsavedir) {
			dp_free(lastsavedir);
		}
		lastsavedir = dp_calloc(1, (strlen(file_chooser_dir) + 1));
		strcpy(lastsavedir, file_chooser_dir);
		/* not dp_free() because gtk allocated */
		g_free(file_chooser_dir);
	}

	/* */
	(void)gtk_widget_destroy(dialog);

	/* */
	if (file_chooser_filename) {
		jgffilename = dp_calloc(1, (strlen(file_chooser_filename) + 1));
		strcpy(jgffilename, file_chooser_filename);
		/* not dp_free() because gtk allocated */
		g_free(file_chooser_filename);
	} else {
		/* no filename */
		return;
	}

	errno = 0;
	fstream = fopen(jgffilename, "wb");

	/* check if open */
	if (fstream == NULL) {
		edialog = gtk_message_dialog_new(GTK_WINDOW(mainwindow1),
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR,
						 GTK_BUTTONS_CLOSE,
						 "Cannot open file %s for writing (%s)", jgffilename, g_strerror(errno));
		gtk_dialog_run(GTK_DIALOG(edialog));
		gtk_widget_destroy(edialog);
		dp_free(jgffilename);
		return;
	}

	/* write the jgf json */
	graph2jgf(maingraph, fstream);

	fclose(fstream);
	dp_free(jgffilename);

	return;
}

/* 'quit' in 'file' menu activated - sub menu in menu items in menu bar in vbox1 */
static void on_top_level_window_quit1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	if (menuitem) {
	}
	if (user_data) {
	}
	top_level_window_main_quit();
	return;
}

/* left slider zoom factor */
static void on_vscale1_changed(GtkAdjustment * adj)
{
	gdouble val0 = 0.0;
	int val1 = 0;

	if (adj) {
	}

	/* check if there is node data to draw */
	if (validdata == 0) {
		return;
	}

	val0 = gtk_adjustment_get_value(adj);
	val1 = (int)val0;
	zfactor = exp((double)(3 * (val1 - 50)) / (double)50);

	if (option_gdebug > 1) {
		printf("%s(): zoomslider=%d zoomfactor=%f\n", __func__, val1, zfactor);
		fflush(stdout);
	}

	/* do a re-draw */
	gtk_widget_queue_draw(drawingarea1);

	return;
}

/* right slider y offset 0...100% */
static void on_vscale2_changed(GtkAdjustment * adj)
{
	gdouble val = 0.0;
	if (adj) {
	}

	/* check if there is node data to draw */
	if (validdata == 0) {
		return;
	}

	val = gtk_adjustment_get_value(adj);
	vymin = (int)((val * maxy) / 100);

	if (option_gdebug > 1) {
		printf("%s(): yslider=%d vymin=%d (maxy=%d)\n", __func__, (int)val, vymin, maxy);
		fflush(stdout);
	}

	/* do a re-draw */
	gtk_widget_queue_draw(drawingarea1);

	return;
}

/* bottom slider x offset 0...100% */
static void on_hscale1_changed(GtkAdjustment * adj)
{
	gdouble val = 0.0;
	if (adj) {
	}

	/* check if there is node data to draw */
	if (validdata == 0) {
		return;
	}

	val = gtk_adjustment_get_value(adj);
	vxmin = (int)((val * maxx) / 100);

	if (option_gdebug > 1) {
		printf("%s(): xslider=%d vxmin=%d (maxx=%d)\n", __func__, (int)val, vxmin, maxx);
		fflush(stdout);
	}

	/* do a re-draw */
	gtk_widget_queue_draw(drawingarea1);

	return;
}

/* draw arrow, option to allow multiple arrow types todo
 * arrow comes from (start_x,start_y) to (end_x,end_y)
 * size is optional, if zero a default size is used
 */
static void drarrow(cairo_t * crp, int start_x, int start_y, int end_x, int end_y, double size)
{
	double angle = 0.0;
	double arrow_lenght = 8.0;
	double arrow_degrees = ( /* degrees */ 30 * (M_PI / 180));
	double x1 = 0.0;
	double y1 = 0.0;
	double x2 = 0.0;
	double y2 = 0.0;

	if (yydebug || 0) {
		printf("%s(): arrow at (%d,%d) coming from (%d,%d) size %f\n", __func__, end_x, end_y, start_x, start_y, size);
	}

	/* if size is specified, use it, otherwise use default size */
	if (size == 0) {
		arrow_lenght = 8.0;
	} else {
		arrow_lenght = size;
	}

	/* gtk has a gtk_render_arrow() function as alternative to use here */
	angle = atan2(end_y - start_y, end_x - start_x) + M_PI;

	x1 = end_x + arrow_lenght * cos(angle - arrow_degrees);
	y1 = end_y + arrow_lenght * sin(angle - arrow_degrees);
	x2 = end_x + arrow_lenght * cos(angle + arrow_degrees);
	y2 = end_y + arrow_lenght * sin(angle + arrow_degrees);

	/* set start position of arrow part 1 */
	cairo_move_to(crp, end_x, end_y);
	cairo_line_to(crp, x1, y1);

	/* set start position of arrow part 2 */
	cairo_move_to(crp, end_x, end_y);
	cairo_line_to(crp, x2, y2);

	/* make a triangle */
	cairo_line_to(crp, x1, y1);

	return;
}

/* */
static void on_top_level_window_drawingarea1_expose_event_nodes_record_r(cairo_t * crp, struct gml_node
									 *node, struct gml_rl
									 *info)
{
	int i = 0;
	int x0 = 0;
	int y0 = 0;
	int r = 0;
	int b = 0;
	int g = 0;
	int xxo = 0;
	int yyo = 0;
	int szx = 0;
	int szy = 0;
	PangoLayout *layout = NULL;
	PangoFontDescription *desc = NULL;
	char buf[128];
	char *s = NULL;
	/* name of font to use, example "Sans" */
	const char *default_fontname = DEFAULT_FONTNAME;
	/* name of slant to use, example "Italic", "Oblique", "Roman" */
	const char *default_fontslant = DEFAULT_FONTSLANT;
	/* name of weight to use, example "Bold", "Book", "Light", "Medium", "Semi-bold", "Ultra-light" */
	const char *default_fontweight = DEFAULT_FONTWEIGHT;
	/* name of condensed to use, example "Semi-Condensed", "Condensed" */
	const char *default_fontcondensed = DEFAULT_FONTCONDENSED;
	/* font size to use, example "10", "18", "20" etc. */
	const char *default_fontsize = DEFAULT_FONTSIZE;

	x0 = node->finx - vxmin;
	y0 = node->finy - vymin;

	if (info->hd == 0) {
		/* not-has-data */
		for (i = 0; i < info->nparts; i++) {
			on_top_level_window_drawingarea1_expose_event_nodes_record_r(crp, node, info->parts[i]);
		}

	} else {
		/* has-data */

		/* black outline color */
		r = 0;
		g = 0;
		b = 0;
		cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);

		szx = info->bbx;
		szy = info->bby;

		if (info->dir == 0) {
			if (info->xstep) {
				szx = info->xstep;
			} else {
				szx = info->bbx;
			}

		} else {

			if (info->ystep) {
				szy = info->ystep;
			} else {
				szy = info->bby;
			}

		}

		/* this is the box to put the part of the text in */
		cairo_rectangle(crp, x0 + info->xoff, y0 + info->yoff, szx, szy);

		if (yydebug || 0) {
			printf("%s(): rect at (%d,%d) size (%d,%d) for \"%s\"\n", __func__,
			       x0 + info->xoff, y0 + info->yoff, szx, szy, info->ulabel);
		}

		cairo_stroke(crp);

		/* fontcolor of node black default or color */
		r = (node->fontcolor & 0x00ff0000) >> 16;
		g = (node->fontcolor & 0x0000ff00) >> 8;
		b = (node->fontcolor & 0x000000ff);

		/* draw in text fontcolor of node */
		cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);

		/* start text inside rectangle */
		xxo = 2;
		yyo = 2;

		/* set start position of text */
		cairo_move_to(crp, x0 + info->xoff + xxo, y0 + info->yoff + yyo);

		layout = pango_cairo_create_layout(crp);

		/* set the text to draw which is 0 terminated */
		pango_layout_set_text(layout, info->ulabel, -1);

		/* set font parameters */

		/* create the fontname description */
		memset(buf, 0, 128);

		default_fontname = DEFAULT_FONTNAME;

		/* check if node has a specified font slant */
		default_fontslant = DEFAULT_FONTSLANT;

		/* check if node has a specified font weight */
		default_fontweight = DEFAULT_FONTWEIGHT;

		/* check if node has a specified font size */
		default_fontsize = DEFAULT_FONTSIZE;

		/* create the font name string */
		snprintf(buf, (128 - 1), "%s %s %s %s %s", default_fontname,
			 default_fontslant, default_fontweight, default_fontcondensed, default_fontsize);

		/* copy string buffer */
		s = uniqstr(buf);

		/* */
		desc = pango_font_description_from_string(s);

		/* */
		pango_layout_set_font_description(layout, desc);

		/* */
		pango_font_description_free(desc);

		/* */
		pango_cairo_update_layout(crp, layout);

		/* draw the text */
		pango_cairo_show_layout(crp, layout);

		/* */
		cairo_stroke(crp);

		g_object_unref(G_OBJECT(layout));
	}

	return;
}

/* record node drawing */
static void on_top_level_window_drawingarea1_expose_event_nodes_record(cairo_t * crp, struct gml_node
								       *node)
{

	on_top_level_window_drawingarea1_expose_event_nodes_record_r(crp, node, node->rlabel);
	return;
}

/* html 1 item node drawing */
static void on_top_level_window_drawingarea1_expose_event_nodes_html1item(cairo_t * crp, struct gml_node
									  *node, struct gml_hitem *item, int xplus, int yplus)
{
	PangoLayout *layout = NULL;
	PangoFontDescription *desc = NULL;
	char buf[128];
	int x0 = 0;
	int y0 = 0;
	int r = 0;
	int b = 0;
	int g = 0;
	int fontcolor = 0;
	int bgcolor = 0;
	int bgr = 0;
	int bgb = 0;
	int bgg = 0;
	int xxo = 0;
	int yyo = 0;
	char *s = NULL;
	char *fontstr = NULL;
	PangoAttrList *pattrs = NULL;
	GError *errorpos = NULL;
	int status = 0;
	char *ptext = NULL;
	char *em = NULL;
	char *fnam = NULL;
	char *fslant = NULL;
	char *fweight = NULL;
	char *ful = NULL;
	char *fol = NULL;
	char spans[128];
	char spane[64];
	char *fsubs = NULL;
	char *fsube = NULL;
	char *fsups = NULL;
	char *fsupe = NULL;
	char *fstr = NULL;
	int fsize = 0;
	int flen = 0;

	if (item == NULL) {
		/* shouldnothappen */
		return;
	}
	if (item->text == NULL) {
		/* shouldnothappen */
		return;
	}
	if (strlen(item->text) == 0) {
		/* shouldnothappen */
		return;
	}

	/* start positions */
	x0 = node->finx - vxmin;
	y0 = node->finy - vymin;
	x0 = x0 + xplus;
	y0 = y0 + yplus;

	if (yydebug || 0) {
		printf("%s(): text %s at (%d,%d)\n", __func__, item->text, xplus, yplus);
	}

	layout = pango_cairo_create_layout(crp);

	/* background color */
	if (item->ncolor < 0) {
		/* shouldnothappen */
		bgcolor = 0x00ffff;
	} else {
		bgcolor = item->ncolor;
	}

	/* backgroundcolor of node white default or color */
	bgr = (bgcolor & 0x00ff0000) >> 16;
	bgg = (bgcolor & 0x0000ff00) >> 8;
	bgb = (bgcolor & 0x000000ff);

	if (item->fontcolor < 0) {
		/* shouldnothappen */
		fontcolor = 0;	/* black */
	} else {
		fontcolor = item->fontcolor;
	}

	/* fontcolor of node black default or color */
	r = (fontcolor & 0x00ff0000) >> 16;
	g = (fontcolor & 0x0000ff00) >> 8;
	b = (fontcolor & 0x000000ff);

	/* re-use pango font format string */
	if (item->fontstr) {
		fontstr = item->fontstr;
	} else {
		/* create new string */
		if (item->fontname) {
			fnam = item->fontname;
		} else {
			fnam = DEFAULT_FONTNAME;
		}
		if (item->fontslant) {
			fslant = item->fontslant;
		} else {
			fslant = DEFAULT_FONTSLANT;
		}
		if (item->bitflags.i) {
			fslant = "italic";
		}
		if (item->fontweight) {
			fweight = item->fontweight;
		} else {
			fweight = DEFAULT_FONTWEIGHT;
		}
		if (item->bitflags.b) {
			fweight = "bold";
		}
		if (item->bitflags.u || 0) {
			ful = " underline=\"single\"";
			/* also option to set underline color */
		} else {
			ful = "";
		}
		/* also option to set overline color */
		if (item->bitflags.o || 0) {
			if (pango_overline < 0) {
				/* probe pango lib for support at runtime */
				status =
				    pango_parse_markup("<span overline=\"single\">text</span>", -1, 0, &pattrs, &ptext, NULL,
						       &errorpos);
				if (status == 0) {
					printf("%s(): overline <o> in html string is not supported with current pango library\n",
					       __func__);
					pango_overline = 0;
				} else {
					/* supported */
					pango_overline = 1;
				}
			}
			/* it depends on pango version if overline s allowed, if not then no text */
			if (pango_overline) {
				fol = " overline=\"single\"";
			} else {
				fol = "";
			}
		} else {
			fol = "";
		}
		if (item->bitflags.s || 0) {
			fstr = " strikethrough=\"true\"";
		} else {
			fstr = "";
		}
		if (item->fontsize < 0) {
			fsize = DEFAULT_FONTSIZE_INT;
		} else {
			fsize = item->fontsize;
		}
		/* sub and superscript */
		if (item->bitflags.sub || 0) {
			fsubs = "<sub>";
			fsube = "</sub>";
		} else {
			fsubs = "";
			fsube = "";
		}
		if (item->bitflags.sup || 0) {
			fsups = "<sup>";
			fsupe = "</sup>";
		} else {
			fsups = "";
			fsupe = "";
		}

		memset(spans, 0, 128);

		/* start of format string */
		snprintf(spans, (128 - 1), "<span foreground=\"#%02x%02x%02x\" background=\"#%02x%02x%02x\"%s%s%s>%s%s", r, g, b,
			 bgr, bgg, bgb, ful, fstr, fol, fsups, fsubs);

		/* end of format string */
		memset(spane, 0, 64);
		snprintf(spane, (64 - 1), "%s%s</span>", fsube, fsupe);

		flen = strlen(spans) + strlen(spane) + strlen(item->otext) + 1;
		fontstr = dp_calloc(1, flen);
		if (fontstr == NULL) {
			/* shouldnothappen */
			g_object_unref(G_OBJECT(layout));
			return;
		}
		/* create new full format string */
		strcpy(fontstr, spans);
		strcat(fontstr, item->otext);
		strcat(fontstr, spane);
		/* save for re-use */
		item->fontstr = uniqstr(fontstr);
		dp_free(fontstr);
		fontstr = item->fontstr;
	}

	status = pango_parse_markup(fontstr, -1, 0, &pattrs, &ptext, NULL, &errorpos);

	if (status == 0) {
		if (errorpos) {
			em = errorpos->message;
		} else {
			em = "";
		}
		printf("%s(): pango_parse_markup() of '%s' has error status %d \"%s\"\n", __func__, fontstr, status, em);
		pattrs = NULL;
	}

	/* oke */
	pango_layout_set_text(layout, item->text, -1);

	pango_layout_set_attributes(layout, pattrs);

	if (pango_layout_get_character_count(layout) == 0) {
		/* shouldnothappen */
		g_object_unref(G_OBJECT(layout));
		return;
	}

	/* start text inside rectangle */
	xxo = 1;
	yyo = 1;

	/* set start position of text */
	cairo_move_to(crp, x0 + item->txoff + xxo, y0 + item->tyoff + yyo);

	/* set font parameters */

	/* create the fontname description or re-use */
	if (item->fontdesc) {
		s = item->fontdesc;
	} else {
		memset(buf, 0, 128);

		/* create the font name string */
		snprintf(buf, (128 - 1), "%s %s %s %s %d", fnam, fslant, fweight, DEFAULT_FONTCONDENSED, fsize);

		s = uniqstr(buf);
		item->fontdesc = s;
	}

	/* */
	desc = pango_font_description_from_string(s);

	/* */
	pango_layout_set_font_description(layout, desc);

	/* */
	pango_font_description_free(desc);

	/* */
	pango_cairo_update_layout(crp, layout);

	/* draw the text */
	pango_cairo_show_layout(crp, layout);

	/* */
	cairo_stroke(crp);

	g_object_unref(G_OBJECT(layout));

	return;
}

/* html items node drawing */
static void on_top_level_window_drawingarea1_expose_event_nodes_htmlitems(cairo_t * crp, struct gml_node
									  *node, struct gml_hilist *il, int xplus, int yplus)
{
	struct gml_hitem *pitem = NULL;
	struct gml_hilist *pi = NULL;

	if (il == NULL) {
		/* shouldnothappen */
		return;
	}

	if (yydebug || 0) {
		printf("%s(): node=\"%s\" xyplus=(%d,%d)\n", __func__, node->name, xplus, yplus);
	}

	/* scan the text elements */
	pi = il;
	while (pi) {
		pitem = pi->items;
		if (pitem) {
			if (pi->items->bitflags.br) {
			} else if (pi->items->bitflags.hr) {
			} else if (pi->items->bitflags.vr) {
			} else if (pi->items->bitflags.img) {
			} else if (pi->items->bitflags.table) {
			} else {
				on_top_level_window_drawingarea1_expose_event_nodes_html1item(crp, node, pitem, xplus, yplus);
			}
		}
		pi = pi->next;
	}

	return;
}

/* zzz */

/* html tables node drawing */
static void on_top_level_window_drawingarea1_expose_event_nodes_1htmltable(cairo_t * crp, struct gml_node
									   *node, struct gml_htlist *tlptr)
{
	struct gml_tritemlist *trptr = NULL;	/* list of <tr> items in this table */
	struct gml_tditem *tdiptr = NULL;
	struct gml_hilist *ilptr = NULL;	/* list of text items */
	struct gml_htlist *tlptrsub = NULL;
	int yo = 0;
	int xo = 0;
	int nyo = 0;
	int nxo = 0;
	int itemrectanglecolor = 0;	/* color of outline rectangle of item, 0 is black, #rrggbb */
	int r = 0;
	int g = 0;
	int b = 0;
	int tabxoff = 0;
	int tabyoff = 0;
	int tabxsize = 0;
	int tabysize = 0;
	int tabncols = 0;
	int tabnrows = 0;
	int trnumtd = 0;
	int trysize = 0;
	int tdxsize = 0;
	int ytd = 0;

	if (tlptr == NULL) {
		printf("%s(): nil tlptr\n", __func__);
		/* shouldnothappen */
		return;
	}

	if (tlptr->titem == NULL) {
		printf("%s(): nil titem\n", __func__);
		/* shouldnothappen */
		return;
	}

	/* scan the items in this <table> */
	nxo = node->finx - vxmin;
	nyo = node->finy - vymin;

	/* (x,y) offset of <table> */
	tabxoff = tlptr->titem->xoff;
	tabyoff = tlptr->titem->yoff;
	if (tabxoff) {		/* todo */
	}
	if (tabyoff) {		/* todo */
	}
	if (yydebug || 0) {
		printf("%s(): <table> offset is (%d,%d)\n", __func__, tabxoff, tabyoff);
	}
	/* start draw at table offset */
	/* xo = tabxoff; not used here */
	yo = tabyoff;

	/* (x,y) size of <table> */
	tabxsize = tlptr->titem->txsize;
	tabysize = tlptr->titem->tysize;
	if (tabxsize) {		/* todo */
	}
	if (tabysize) {		/* todo */
	}
	/* (x,y) size of table in cols/rows */
	tabncols = tlptr->titem->ncols;
	tabnrows = tlptr->titem->nrows;
	if (tabncols) {		/* todo */
	}
	if (tabnrows) {		/* todo */
	}
	/* */
	if (tlptr->titem->tr) {
		trptr = tlptr->titem->tr;

		while (trptr) {
			/* scan the <tr> items  */
			if (trptr->tritem) {
				/* number of <td> items at this <tr> */
				trnumtd = trptr->tritem->numtd;
				if (trnumtd) {	/* todo */
				}
				/* y size of this <tr> */
				trysize = trptr->tritem->ysize;
				/* */
				tdiptr = trptr->tritem->tdi;
				if (tdiptr) {
					/* scan the <td> items */
					xo = tabxoff;

					while (tdiptr) {
						/* x size of this <td> */
						tdxsize = tdiptr->xsize;
						if (tdxsize) {	/* todo not used here */
						}
						/* there are dummy <td> with no item data in it, but color, size is set */
						ilptr = tdiptr->il;
						if (ilptr) {
							ytd = 0;
							while (ilptr) {
								/* colored rectangle around item, option here. */
								r = ((itemrectanglecolor & 0x00ff0000) >> 16);
								g = ((itemrectanglecolor & 0x0000ff00) >> 8);
								b = (itemrectanglecolor & 0x000000ff);

								/* */
								/* */

								if (yydebug || 0) {
									printf
									    ("%s(): <td> at (%d,%d) size (%d,%d) \"%s\"\n",
									     __func__, xo, yo + ytd, ilptr->items->txsize,
									     ilptr->items->tysize, ilptr->items->text);
								}

								/* */
								if (ilptr->items->bitflags.br) {
								} else if (ilptr->items->bitflags.hr) {
								} else if (ilptr->items->bitflags.vr) {
								} else if (ilptr->items->bitflags.img) {
								} else if (ilptr->items->bitflags.table) {
									if (yydebug || 0) {
										printf
										    ("%s(): table bit set todo xstep=%d xo=%d yo+ytd=%d\n",
										     __func__, tdiptr->xstep, xo, yo + ytd);
									}
									ilptr->items->table->xoff = xo;
									ilptr->items->table->yoff = yo + ytd;
								} else {
									if (yydebug || 0) {
										printf("%s(): items at (%d,%d)\n", __func__, xo,
										       yo + ytd);
									}
									/* html items node drawing */
									on_top_level_window_drawingarea1_expose_event_nodes_html1item
									    (crp, node, ilptr->items,
									     /* int xplus */
									     xo,
									     /* int yplus */
									     yo + ytd);

								}

								ytd = ytd + ilptr->items->tysize;
								ilptr = ilptr->next;
							}

						}
						/* there can be dummy <td> */
						/* test */
						if (0) {
							/* test only */
							cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);
							cairo_rectangle(crp, xo + nxo, yo + nyo, tdxsize, trysize);
							cairo_stroke(crp);	/* ccx */
						} else {
							cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);
							cairo_rectangle(crp, xo + nxo, yo + nyo, tdiptr->xstep, tdiptr->ystep);
							cairo_stroke(crp);	/* ccx */
						}
						/* */

						/* to next <td> */
						xo = xo + 2;
						xo = xo + tdiptr->xstep;
						tdiptr = tdiptr->next;
					}
					/* end of <td> */
					yo = yo + trysize;

				}
			}
			trptr = trptr->next;
		}
	}

	/* scan the sub <table> items in this <table> */
	if (tlptr->titem->tl) {
		tlptrsub = tlptr->titem->tl;
		while (tlptrsub) {
			on_top_level_window_drawingarea1_expose_event_nodes_1htmltable(crp, node, tlptrsub);
			tlptrsub = tlptrsub->next;
		}
	}

	return;
}

/* html tables node drawing */
static void on_top_level_window_drawingarea1_expose_event_nodes_htmltables(cairo_t * crp, struct gml_node
									   *node)
{
	struct gml_htlist *tlptr = NULL;

	if (node->hlabel->tl == NULL) {
		/* shouldnothappen */
		return;
	}

	/* */
	tlptr = node->hlabel->tl;

	while (tlptr) {
		on_top_level_window_drawingarea1_expose_event_nodes_1htmltable(crp, node, tlptr);
		tlptr = tlptr->next;
	}

	return;
}

/* html node drawing */
static void on_top_level_window_drawingarea1_expose_event_nodes_html(cairo_t * crp, struct gml_node
								     *node)
{
	if (node->hlabel->mode == 0) {
		/* items */
		on_top_level_window_drawingarea1_expose_event_nodes_htmlitems(crp, node, node->hlabel->il, 0, 0);
	} else {
		/* tables */
		on_top_level_window_drawingarea1_expose_event_nodes_htmltables(crp, node);
	}
	return;
}

/* draw all nodes z
zzz*/
static void on_top_level_window_drawingarea1_expose_event_nodes(cairo_t * crp)
{
	int xo = 0;
	int yo = 0;
	double dfs = 0.0;
	int fs = 0;
	int r = 0;
	int g = 0;
	int b = 0;
	PangoLayout *layout = NULL;
	PangoFontDescription *desc = NULL;
	char buf[128];
	char *s = NULL;
	/* name of font to use, example "Sans" */
	const char *default_fontname = DEFAULT_FONTNAME;
	/* name of slant to use, example "Italic", "Oblique", "Roman" */
	const char *default_fontslant = DEFAULT_FONTSLANT;
	/* name of weight to use, example "Bold", "Book", "Light", "Medium", "Semi-bold", "Ultra-light" */
	const char *default_fontweight = DEFAULT_FONTWEIGHT;
	/* name of condensed to use, example "Semi-Condensed", "Condensed" */
	const char *default_fontcondensed = DEFAULT_FONTCONDENSED;
	/* font size to use, example "10", "18", "20" etc. */
	const char *default_fontsize = DEFAULT_FONTSIZE;
	int x0 = 0;
	int y0 = 0;
	struct gml_nlist *nl = NULL;

	nl = maingraph->nodelist;

	while (nl) {
		/* only draw real nodes here or draw edge-label */
		if (nl->node->dummy == 0) {
			x0 = nl->node->finx - vxmin;
			y0 = nl->node->finy - vymin;

			/* first draw circle is node has a selfedge */
			if (nl->node->elabel == 0) {
				if (nl->node->nselfedges) {

					/* black or colored selfedge */
					r = (nl->node->secolor & 0x00ff0000) >> 16;
					g = ((nl->node->secolor & 0x0000ff00) >> 8);
					b = (nl->node->secolor & 0x000000ff);
					cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);
					/* draw the self-edge, whole circle */
					cairo_arc(crp, x0 + nl->node->bbx - 3, y0 + nl->node->bby - 3, 6 /* radius */ ,
						  0 /*  45 * (180 * M_PI) */ , 2 * M_PI);
					/* opt. arrow, which is too big here todo. this looks not good */
					if (0) {
						drarrow(crp, x0 - 10, y0 + nl->node->bby - 6, x0, y0 + nl->node->bby - 6, 3);
					}
					cairo_stroke(crp);
				}
			}

			/* fillcolor of node white default or color */
			r = ((nl->node->ncolor & 0x00ff0000) >> 16);
			g = ((nl->node->ncolor & 0x0000ff00) >> 8);
			b = (nl->node->ncolor & 0x000000ff);

			cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);
			cairo_rectangle(crp, x0, y0, nl->node->bbx, nl->node->bby);
			cairo_fill(crp);
			cairo_stroke(crp);

			/* outline color black for node, edgelabel node has no outline */
			if (nl->node->elabel == 0) {
				/* bordercolor of node black default or color */
				r = (nl->node->nbcolor & 0x00ff0000) >> 16;
				g = (nl->node->nbcolor & 0x0000ff00) >> 8;
				b = (nl->node->nbcolor & 0x000000ff);

				cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);
				cairo_rectangle(crp, x0, y0, nl->node->bbx, nl->node->bby);
				cairo_stroke(crp);
			} else {
				/* this is a edge label, no outline */
			}

			/* draw no text labels if labels==0 */
			if (option_labels == 0) {
				nl = nl->next;
				continue;
			}

			/*
			 * now draw text of label as ususal or record style label
			 */

			/* this below is not oke, todo to fix */

			/* calculate the scaled font size */
			dfs = (zfactor * atoi(default_fontsize));

			/* somewhat rounded version */
			fs = (int)dfs;

			/* too small to draw readable text then skip the following text drawing area */
			if (fs < 4) {
				nl = nl->next;
				continue;
			}

			if (nl->node->drawrh) {
				/* draw regular text in node, or record label */
				if (nl->node->hlabel) {
					/* draw html label */
					on_top_level_window_drawingarea1_expose_event_nodes_html(crp, nl->node);
				} else if (nl->node->rlabel) {
					/* draw record label */
					on_top_level_window_drawingarea1_expose_event_nodes_record(crp, nl->node);
				} else {
					/* draw regular text */
					/* fontcolor of node black default or color */
					r = (nl->node->fontcolor & 0x00ff0000) >> 16;
					g = (nl->node->fontcolor & 0x0000ff00) >> 8;
					b = (nl->node->fontcolor & 0x000000ff);

					/* draw in text color of node */
					cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);

					xo = 2;
					yo = 2;

					/* set start position of text */
					cairo_move_to(crp, nl->node->finx - vxmin + xo, nl->node->finy - vymin + yo);

					layout = pango_cairo_create_layout(crp);

					if (nl->node->nlabel == NULL) {
						printf("%s(): nil nlabel\n", __func__);
						/* shouldnothappen */
						nl->node->nlabel = nl->node->name;
					}

					/* set the text to draw which is 0 terminated */
					pango_layout_set_text(layout, nl->node->nlabel, -1);
					/* set font parameters */

					/* create the fontname description */
					memset(buf, 0, 128);

					default_fontname = DEFAULT_FONTNAME;

					/* check if node has a specified font slant */
					default_fontslant = DEFAULT_FONTSLANT;

					/* check if node has a specified font weight */
					default_fontweight = DEFAULT_FONTWEIGHT;

					/* check if node has a specified font size */
					default_fontsize = DEFAULT_FONTSIZE;

					/* create the font name string */
					snprintf(buf, (128 - 1), "%s %s %s %s %s", default_fontname,
						 default_fontslant, default_fontweight, default_fontcondensed, default_fontsize);

					/* copy string buffer */
					s = uniqstr(buf);

					/* */
					desc = pango_font_description_from_string(s);

					/* */
					pango_layout_set_font_description(layout, desc);

					/* */
					pango_font_description_free(desc);

					/* */
					pango_cairo_update_layout(crp, layout);

					/* draw the text */
					pango_cairo_show_layout(crp, layout);

					/* */
					cairo_stroke(crp);

					g_object_unref(G_OBJECT(layout));
				}
			} else {

				/* draw regular text */
				/* fontcolor of node black default or color */
				r = (nl->node->fontcolor & 0x00ff0000) >> 16;
				g = (nl->node->fontcolor & 0x0000ff00) >> 8;
				b = (nl->node->fontcolor & 0x000000ff);

				/* draw in text color of node */
				cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);

				xo = 2;
				yo = 2;

				/* set start position of text */
				cairo_move_to(crp, nl->node->finx - vxmin + xo, nl->node->finy - vymin + yo);

				layout = pango_cairo_create_layout(crp);

				/* set the text to draw which is 0 terminated */
				pango_layout_set_text(layout, nl->node->name, -1);
				/* set font parameters */

				/* create the fontname description */
				memset(buf, 0, 128);

				default_fontname = DEFAULT_FONTNAME;

				/* check if node has a specified font slant */
				default_fontslant = DEFAULT_FONTSLANT;

				/* check if node has a specified font weight */
				default_fontweight = DEFAULT_FONTWEIGHT;

				/* check if node has a specified font size */
				default_fontsize = DEFAULT_FONTSIZE;

				/* create the font name string */
				snprintf(buf, (128 - 1), "%s %s %s %s %s", default_fontname,
					 default_fontslant, default_fontweight, default_fontcondensed, default_fontsize);

				/* copy string buffer */
				s = uniqstr(buf);

				/* */
				desc = pango_font_description_from_string(s);

				/* */
				pango_layout_set_font_description(layout, desc);

				/* */
				pango_font_description_free(desc);

				/* */
				pango_cairo_update_layout(crp, layout);

				/* draw the text */
				pango_cairo_show_layout(crp, layout);

				/* */
				cairo_stroke(crp);

				g_object_unref(G_OBJECT(layout));

			}

		}

		nl = nl->next;
	}

	return;
}

/* real-to-dummy find edge conn. point */
static int r2d_finx(struct gml_edge *edge)
{
	struct gml_node *sn = NULL;
	struct gml_node *tn = NULL;
	int ret = 0;
	int i = 0;

	sn = edge->from_node;	/* from-node */
	tn = edge->to_node;	/* to-node */

	if (tn) {
	}

	if (edge->vedge) {
		ret = (sn->finx + (sn->bbx / 2));
		return (ret);
	}

	if (sn->dx_oedges == 0) {
		ret = (sn->finx + (sn->bbx / 2));
		return (ret);
	}

	for (i = 0; i < sn->outdegree; i++) {

		if (sn->oedges[i] == edge) {
			break;
		}
	}

	ret = (sn->finx + 5 + (i * sn->dx_oedges));

	return (ret);
}

/* connection edge at real to-node */
static int d2r_tnx1(struct gml_edge *edge)
{
	struct gml_node *sn = NULL;
	struct gml_node *tn = NULL;
	int ret = 0;
	int i = 0;

	sn = edge->from_node;	/* from-node */
	tn = edge->to_node;	/* to-node */

	if (sn) {
	}

	if (edge->vedge) {
		ret = (tn->finx + (tn->bbx / 2));
		return (ret);
	}

	if (tn->dx_iedges == 0) {
		ret = (tn->finx + (tn->bbx / 2));
		return (ret);
	}

	for (i = 0; i < tn->indegree; i++) {

		if (tn->iedges[i] == edge) {
			break;
		}
	}

	ret = (tn->finx + 5 + (i * tn->dx_iedges));

	return (ret);
}

/* nr. of pixels hor. edge goes downwards */
#define HEDGE_DY 10

/* draw all edges */
static void on_top_level_window_drawingarea1_expose_event_edges(cairo_t * crp)
{
	int r = 0;
	int g = 0;
	int b = 0;
	int fnx1 = 0;
	int fny1 = 0;
	int tnx1 = 0;
	int tny1 = 0;
	struct gml_elist *el = NULL;
	struct gml_edge *edge = NULL;
	struct gml_node *sn = NULL;
	struct gml_node *tn = NULL;
	int ecolor = 0;
	int dx15 = 0;
	const double dashed[] = {
		14.0, 2.0	/* 6.0 */
	};
	int lendashed = sizeof(dashed) / sizeof(dashed[0]);
	const double dotted[] = {
		1.0		/* 2.0, 6.0 */
	};
	int lendotted = sizeof(dotted) / sizeof(dotted[0]);

	el = maingraph->edgelist;

	while (el) {
		edge = el->edge;

		sn = edge->from_node;	/* from-node */
		tn = edge->to_node;	/* to-node */

		ecolor = edge->ecolor;	/* edge line color */

		/* thickness of edge line */
		cairo_set_line_width(crp, DEFAULT_EDGE_THICKNESS);

		/* check edge line style */
		if (edge->style == 1 /* ESTYLE_DASHED */ ) {
			/* dashed edge line */
			cairo_set_dash(crp, dashed, lendashed, 1);
		} else if (edge->style == 2 /* ESTYLE_DOTTED */ ) {
			/* dotted edge line */
			cairo_set_dash(crp, dotted, lendotted, 0);
		} else {
			/* solid edge line */
			cairo_set_dash(crp, dotted, 0, 0);
		}

		/* black or colored line */
		r = (ecolor & 0x00ff0000) >> 16;
		g = (ecolor & 0x0000ff00) >> 8;
		b = (ecolor & 0x000000ff);

		/* draw in line color of edge */
		cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);

		if (edge->hedge) {
			/* horizontal edge has original endpoints */

			/* center of from/to nodes */
			fnx1 = (sn->finx + sn->bbx / 2) - vxmin;
			tnx1 = (tn->finx + tn->bbx / 2) - vxmin;

			if (tnx1 > fnx1) {
				/* edge from left to right */

				/* check if nodes are next to each other */
				/* this should also check if to-node is a dummy or real node todo */
				if ((sn->relx + 1) == tn->relx) {
					/*  printf ("direct-lr\n");  */

					fnx1 = (sn->finx + sn->bbx) - vxmin;
					fny1 = (sn->finy + sn->bby / 2) - vymin;
					cairo_move_to(crp, fnx1, fny1);

					cairo_line_to(crp, (tn->finx) - vxmin, (tn->finy + tn->bby / 2) - vymin);

					/* add arrow */
					if (edge->reversed == 0) {
						drarrow(crp, fnx1, fny1, (tn->finx) - vxmin, (tn->finy + tn->bby / 2) - vymin, 0);
					} else {
						drarrow(crp, (tn->finx) - vxmin, (tn->finy + tn->bby / 2) - vymin, fnx1, fny1, 0);
					}

				} else {

					/* distance length of hor. line / 5 */
					dx15 = (tnx1 - fnx1) / 5;

					/* optional draw hor. edges in a different color */
					if (0) {
						cairo_set_source_rgb(crp, 0 / 255.0, 0 / 255.0, 0xff / 255.0);
					}

					/* start line at center */
					fnx1 = (sn->finx + sn->bbx / 2) - vxmin;
					fny1 = (sn->finy + sn->bby) - vymin;
					cairo_move_to(crp, fnx1, fny1);

					if ((sn->finy + sn->bby) >= (tn->finy + tn->bby)) {
						/* from node y is lower then target, put hor. line 10px lower */
						cairo_line_to(crp, (fnx1 + dx15), ((sn->finy + sn->bby) + HEDGE_DY) - vymin);
						cairo_line_to(crp, (fnx1 + dx15) + (3 * dx15),
							      ((sn->finy + sn->bby) + HEDGE_DY) - vymin);
						cairo_line_to(crp, (tn->finx + tn->bbx / 2) - vxmin, (tn->finy + tn->bby) - vymin);

						/* add arrow */
						if (edge->reversed == 0) {
							drarrow(crp, (fnx1 + dx15) + (3 * dx15),
								((sn->finy + sn->bby) + HEDGE_DY) -
								vymin, (tn->finx + tn->bbx / 2) - vxmin,
								(tn->finy + tn->bby) - vymin, 0);
						} else {
							if (0) {	/*old */
								drarrow(crp, (fnx1 + dx15),
									((sn->finy + sn->bby) + HEDGE_DY) - vymin, fnx1, fny1, 0);
							}
							drarrow(crp,
								(tn->finx + tn->bbx / 2) - vxmin,
								(tn->finy + tn->bby) - vymin,
								(fnx1 + dx15) + (3 * dx15),
								((sn->finy + sn->bby) + HEDGE_DY) - vymin, 0);

						}

					} else {
						/* from-node y is higher */
						cairo_line_to(crp, (fnx1 + dx15), (tn->finy + tn->bby) + HEDGE_DY - vymin);
						cairo_line_to(crp, (fnx1 + dx15) + (3 * dx15),
							      ((tn->finy + tn->bby) + HEDGE_DY) - vymin);
						cairo_line_to(crp, (tn->finx + tn->bbx / 2) - vxmin, (tn->finy + tn->bby) - vymin);

						/* add arrow */
						if (edge->reversed == 0) {
							drarrow(crp, (fnx1 + dx15) + (3 * dx15),
								((tn->finy + tn->bby) + HEDGE_DY) -
								vymin,
								(tn->finx + tn->bbx / 2) - vxmin, (tn->finy + tn->bby) - vymin, 0);
						} else {
							drarrow(crp, (fnx1 + dx15),
								(tn->finy + tn->bby) + HEDGE_DY - vymin, fnx1, fny1, 0);
						}

					}

				}

			} else {
				/* edge from right to left fnx1>tnx1 */

				if ((sn->relx) == (tn->relx + 1)) {
					/*  printf ("direct-rl\n");  */

					cairo_move_to(crp, (sn->finx) - vxmin, (sn->finy + sn->bby / 2) - vymin);
					cairo_line_to(crp, tn->finx + tn->bbx - vxmin, tn->finy + tn->bby / 2 - vymin);
					/* add arrow */
					if (edge->reversed == 0) {
						drarrow(crp,
							(sn->finx) - vxmin,
							(sn->finy + sn->bby / 2) - vymin,
							tn->finx + tn->bbx - vxmin, tn->finy + tn->bby / 2 - vymin, 0);
					} else {
						drarrow(crp, tn->finx + tn->bbx - vxmin,
							tn->finy + tn->bby / 2 - vymin,
							(sn->finx) - vxmin, (sn->finy + sn->bby / 2) - vymin, 0);
					}

				} else {

					/* distance length of hor. line / 5 */
					dx15 = (fnx1 - tnx1) / 5;
					/* optional draw hor. edges in a different color */
					if (0) {
						cairo_set_source_rgb(crp, 0 / 255.0, 0 / 255.0, 0xff / 255.0);
					}

					/* start line at center */
					fnx1 = (sn->finx + sn->bbx / 2) - vxmin;
					fny1 = (sn->finy + sn->bby) - vymin;
					cairo_move_to(crp, fnx1, fny1);

					if ((sn->finy + sn->bby) >= (tn->finy + tn->bby)) {
						/* from node y is lower then target, put hor. line 10px lower */
						cairo_line_to(crp, (fnx1 - dx15), ((sn->finy + sn->bby) + HEDGE_DY) - vymin);
						cairo_line_to(crp, (fnx1 - dx15) - (3 * dx15),
							      ((sn->finy + sn->bby) + HEDGE_DY) - vymin);
						cairo_line_to(crp, (tn->finx + tn->bbx / 2) - vxmin, (tn->finy + tn->bby) - vymin);

						/* add arrow */
						if (edge->reversed == 0) {
							/* could be improved here todo */
							drarrow(crp, (fnx1 - dx15) - (3 * dx15),
								((sn->finy + sn->bby) +
								 HEDGE_DY) - vymin,
								(tn->finx + tn->bbx / 2) - vxmin, (tn->finy + tn->bby) - vymin, 0);
						} else {
							drarrow(crp, (fnx1 - dx15),
								((sn->finy + sn->bby) + HEDGE_DY) - vymin, fnx1, fny1, 0);
						}

					} else {
						/* from-node y is higher */
						cairo_line_to(crp, (fnx1 - dx15), (tn->finy + tn->bby) + HEDGE_DY - vymin);
						cairo_line_to(crp, (fnx1 - dx15) - (3 * dx15),
							      ((tn->finy + tn->bby) + HEDGE_DY) - vymin);
						cairo_line_to(crp, (tn->finx + tn->bbx / 2) - vxmin, (tn->finy + tn->bby) - vymin);
						/* add arrow */
						if (edge->reversed == 0) {
							/* this could be improved, todo */
							drarrow(crp, (fnx1 - dx15) - (3 * dx15),
								((sn->finy + sn->bby) +
								 HEDGE_DY) - vymin,
								(tn->finx + tn->bbx / 2) - vxmin, (tn->finy + tn->bby) - vymin, 0);
						} else {
							drarrow(crp, (fnx1 - dx15),
								(tn->finy + tn->bby) + HEDGE_DY - vymin, fnx1, fny1, 0);
						}

					}

				}

			}

		} else {

			/* here if not a horizontal edge */
			if (option_splines) {
				/* drawing spline lines */
				if (0) {
					printf("%s(): edge `%s'->`%s' reversed=%d\n", __func__,
					       sn->nlabel, tn->nlabel, edge->reversed);
				}

				if (sn->dummy == 0 && tn->dummy == 0) {
					/* from real node to real node.
					 * real nodes are interleaved with dummy nodes
					 * this only does happen from real node to edge-label node
					 */
					fnx1 = sn->finx + sn->bbx / 2 - vxmin;
					fny1 = sn->finy + sn->bby - vymin;
					cairo_move_to(crp, fnx1, fny1);
					tnx1 = tn->finx + tn->bbx / 2 - vxmin;
					tny1 = tn->finy - vymin;
					cairo_line_to(crp, tnx1, tny1);

					/* add arrow */
					if (edge->reversed == 0) {
						drarrow(crp, fnx1, fny1, tnx1, tny1, 0);
					} else {
						drarrow(crp, tnx1, tny1, fnx1, fny1, 0);
					}

				} else if (sn->dummy == 1 && tn->dummy == 0) {
					/* from dummy node to real node */
					fnx1 = sn->finx - vxmin;
					fny1 = sn->finy - vymin;
					tnx1 = d2r_tnx1(edge) - vxmin;
					tny1 = tn->finy - vymin;

					/* optional draw dummy node */
					if (drawdummy) {
						cairo_set_source_rgb(crp, 255 / 255.0, 0 / 255.0, 0 / 255.0);
						cairo_rectangle(crp, fnx1 - 1, fny1 - 1, 3, 3);
						cairo_fill(crp);
						/* draw in line color of edge */
						cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);
					}

					if (0) {	/* straight lines */
						cairo_move_to(crp, fnx1, fny1);
						cairo_line_to(crp, fnx1, fny1 + (sn->bby / 2));
						cairo_line_to(crp, tnx1, (tn->ly0 - vymin));
						cairo_line_to(crp, tnx1, tny1);
					} else {
						/* temp fixed */
						cairo_move_to(crp, fnx1, fny1);
						/* this does not work:
						 * cairo_curve_to (crp, fnx1, fny1 + (sn->bby / 2), tnx1,
						 *      (tn->ly0 - vymin), tnx1, tny1);
						 */
						cairo_curve_to(crp, fnx1, fny1, fnx1,
							       fny1 + (sn->bby / 2), tnx1, (tn->ly0 - vymin));
						cairo_line_to(crp, tnx1, tny1);
					}

					/* add arrow */
					if (edge->reversed == 0) {
						drarrow(crp, fnx1, fny1, tnx1, tny1, 0);
					} else {
						/* no arrow */
					}

				} else if (sn->dummy == 0 && tn->dummy == 1) {
					/* from real node to dummy node */
					fnx1 = r2d_finx(edge) - vxmin;
					fny1 = (sn->finy + sn->bby) - vymin;
					tnx1 = tn->finx - vxmin;
					tny1 = tn->finy - vymin;

					/* optional draw dummy node */
					if (drawdummy) {
						cairo_set_source_rgb(crp, 255 / 255.0, 0 / 255.0, 0 / 255.0);
						cairo_rectangle(crp, tnx1 - 1, tny1 - 1, 3, 3);
						cairo_fill(crp);
						/* draw in line color of edge */
						cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);
					}

					if (0) {	/* straight */
						cairo_move_to(crp, fnx1, fny1);
						cairo_line_to(crp, fnx1, (sn->ly1 - vymin));
						cairo_line_to(crp, tnx1, tny1 - (tn->bby / 2));
						cairo_line_to(crp, tnx1, tny1);
					} else {
						/* fixed */
						cairo_move_to(crp, fnx1, fny1);
						cairo_curve_to(crp, fnx1, (sn->ly1 - vymin), tnx1,
							       tny1 - (tn->bby / 2), tnx1, tny1);
					}
					/* add arrow */
					if (edge->reversed == 0) {
						/* no arrow */
					} else {
						drarrow(crp, tnx1, tny1, fnx1, fny1, 0);
					}

				} else {
					/* from dummy node to dummy node */
					fnx1 = sn->finx - vxmin;
					fny1 = sn->finy - vymin;
					tnx1 = tn->finx - vxmin;
					tny1 = tn->finy - vymin;

					/* optional draw dummy node */
					if (drawdummy) {
						cairo_set_source_rgb(crp, 255 / 255.0, 0 / 255.0, 0 / 255.0);
						cairo_rectangle(crp, fnx1 - 1, fny1 - 1, 3, 3);
						cairo_fill(crp);
						cairo_rectangle(crp, tnx1 - 1, tny1 - 1, 3, 3);
						cairo_fill(crp);
						/* draw in line color of edge */
						cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);
					}

					if (0) {	/* straight */
						cairo_move_to(crp, fnx1, fny1);
						cairo_line_to(crp, fnx1, fny1 + (sn->bby / 2));
						cairo_line_to(crp, tnx1, (tn->ly0 - vymin));
						cairo_line_to(crp, tnx1, tny1 - (tn->bby / 2));
						cairo_line_to(crp, tnx1, tny1);
					} else {
						/* fixed */
						cairo_move_to(crp, fnx1, fny1);
						cairo_line_to(crp, fnx1, fny1 + (sn->bby / 2));
						cairo_move_to(crp, fnx1, fny1 + (sn->bby / 2));
						cairo_curve_to(crp, tnx1, (tn->ly0 - vymin), tnx1,
							       tny1 - (tn->bby / 2), tnx1, tny1);
					}

					/* no real nodes, no arrows, optional draw arrows at dummy nodes, see tuxsee */

				}

			} else {
				/* drawing not-spline lines */

				if (sn->dummy == 0 && tn->dummy == 0) {
					/* from real node to real node.
					 * real nodes are interleaved with dummy nodes
					 * this does happen from real node to edge-label node
					 */

					/* from real node to real node */
					fnx1 = sn->finx + sn->bbx / 2 - vxmin;
					fny1 = sn->finy + sn->bby - vymin;
					cairo_move_to(crp, fnx1, fny1);
					tnx1 = tn->finx + tn->bbx / 2 - vxmin;
					tny1 = tn->finy - vymin;
					cairo_line_to(crp, tnx1, tny1);

					/* add arrow */
					if (edge->reversed == 0) {
						drarrow(crp, fnx1, fny1, tnx1, tny1, 0);
					} else {
						drarrow(crp, tnx1, tny1, fnx1, fny1, 0);
					}

				} else if (sn->dummy == 1 && tn->dummy == 0) {
					/* from dummy node to real node */
					fnx1 = sn->finx - vxmin;
					fny1 = sn->finy - vymin;
					tnx1 = d2r_tnx1(edge) - vxmin;
					tny1 = tn->finy - vymin;

					/* optional draw dummy node */
					if (drawdummy) {
						cairo_set_source_rgb(crp, 255 / 255.0, 0 / 255.0, 0 / 255.0);
						cairo_rectangle(crp, fnx1 - 1, fny1 - 1, 3, 3);
						cairo_fill(crp);
						/* draw in line color of edge */
						cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);
					}

					cairo_move_to(crp, fnx1, fny1);
					cairo_line_to(crp, fnx1, fny1 + (sn->bby / 2));
					cairo_line_to(crp, tnx1, (tn->ly0 - vymin));
					cairo_line_to(crp, tnx1, tny1);

					/* add arrow */
					if (edge->reversed == 0) {
						drarrow(crp, fnx1, fny1, tnx1, tny1, 0);
					} else {
						/* no arrow */
					}

				} else if (sn->dummy == 0 && tn->dummy == 1) {
					/* from real node to dummy node */
					fnx1 = r2d_finx(edge) - vxmin;
					fny1 = (sn->finy + sn->bby) - vymin;
					tnx1 = tn->finx - vxmin;
					tny1 = tn->finy - vymin;

					/* optional draw dummy node */
					if (drawdummy) {
						cairo_set_source_rgb(crp, 255 / 255.0, 0 / 255.0, 0 / 255.0);
						cairo_rectangle(crp, tnx1 - 1, tny1 - 1, 3, 3);
						cairo_fill(crp);
						/* draw in line color of edge */
						cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);
					}

					cairo_move_to(crp, fnx1, fny1);
					cairo_line_to(crp, fnx1, (sn->ly1 - vymin));
					cairo_line_to(crp, tnx1, tny1 - (tn->bby / 2));
					cairo_line_to(crp, tnx1, tny1);

					/* add arrow */
					if (edge->reversed == 0) {
						/* no arrow */
					} else {
						drarrow(crp, tnx1, tny1, fnx1, fny1, 0);
					}

				} else {
					/* from dummy node to dummy node */
					fnx1 = sn->finx - vxmin;
					fny1 = sn->finy - vymin;
					tnx1 = tn->finx - vxmin;
					tny1 = tn->finy - vymin;

					/* optional draw dummy node */
					if (drawdummy) {
						cairo_set_source_rgb(crp, 255 / 255.0, 0 / 255.0, 0 / 255.0);
						cairo_rectangle(crp, fnx1 - 1, fny1 - 1, 3, 3);
						cairo_fill(crp);
						cairo_rectangle(crp, tnx1 - 1, tny1 - 1, 3, 3);
						cairo_fill(crp);
						/* draw in line color of edge */
						cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);
					}

					cairo_move_to(crp, fnx1, fny1);
					cairo_line_to(crp, fnx1, fny1 + (sn->bby / 2));
					cairo_line_to(crp, tnx1, (tn->ly0 - vymin));
					cairo_line_to(crp, tnx1, tny1 - (tn->bby / 2));
					cairo_line_to(crp, tnx1, tny1);

					/* no arrow draw because there are no real nodes */
				}

				/* put the lines on screen */
				cairo_stroke(crp);
			}

		}

		cairo_stroke(crp);
		el = el->next;
	}

	return;
}

#if GTK_HAVE_API_VERSION_2 == 1
/* redraw drawing area */
static gboolean on_top_level_window_drawingarea1_expose_event(GtkWidget * widget, GdkEventExpose * event, gpointer user_data)
{
	cairo_t *crdraw = NULL;
	gint w = 0;		/* xsize of drawing area */
	gint h = 0;		/* ysize of drawing area */
	int fit = 0;
	if (widget) {
	}
	if (event == NULL) {
		return (FALSE);
	}
	if (user_data) {
	}

	/* only at first expose */
	if (drawing_area_xsize == 0 && drawing_area_ysize == 0) {
		fit = 1;
	} else {
		fit = 0;
	}

	if (fit) {
	}

	/* get cairo drawing context */
	crdraw = gdk_cairo_create(event->window);
	/* how large drawing area is */
	(void)gdk_drawable_get_size(event->window, &w, &h);
	if (option_gdebug > 1 || 0) {
		printf("%s(): drawing area size is (%d,%d)\n", __func__, w, h);
		fflush(stdout);
	}

	/* save a copy of current size */
	drawing_area_xsize = w;
	drawing_area_ysize = h;
	/* check if there is node data to draw */
	if (validdata == 0) {
		/* white fill drawing area */
		cairo_set_source_rgb(crdraw, altr / 255.0, altg / 255.0, altb / 255.0);
		cairo_rectangle(crdraw, 0, 0, w, h);
		cairo_fill(crdraw);
		cairo_stroke(crdraw);
		cairo_destroy(crdraw);
		/* no data */
		return (FALSE);
	}

	cairo_set_source_rgb(crdraw, bgcr / 255.0, bgcg / 255.0, bgcb / 255.0);
	/* select whole screen to fill with background color */
	cairo_rectangle(crdraw, 0, 0, w, h);
	cairo_fill(crdraw);
	cairo_stroke(crdraw);
	/* use zoom slider drawing scale */
	cairo_scale(crdraw, zfactor, zfactor);
	on_top_level_window_drawingarea1_expose_event_nodes(crdraw);
	on_top_level_window_drawingarea1_expose_event_edges(crdraw);
	/* ready drawing */
	cairo_destroy(crdraw);
	return (FALSE);
}
#endif

#if GTK_HAVE_API_VERSION_3
/* redraw drawing area */
static gboolean on_top_level_window_drawingarea1_draw_event(GtkWidget * widget, cairo_t * crdraw, gpointer user_data)
{
	gint w = 0;		/* xsize of drawing area */
	gint h = 0;		/* ysize of drawing area */
	cairo_t *crp = NULL;

	if (widget) {
	}
	if (user_data) {
	}

	/* this is a workaround for issue in cairo-lib 1.14.0 with gtk3,
	 * cairo.c cairo_destroy() line 305 assert(), (with gtk2 no problem) */
	crp = cairo_reference(crdraw);

	/* how large drawing area is */
	w = gtk_widget_get_allocated_width(drawingarea1);
	h = gtk_widget_get_allocated_height(drawingarea1);

	if (option_gdebug > 1) {
		printf("%s(): drawing area size is (%d,%d)\n", __func__, w, h);
		fflush(stdout);
	}

	/* save a copy of current size */
	drawing_area_xsize = w;
	drawing_area_ysize = h;
	/* check if there is node data to draw */
	if (validdata == 0) {
		/* white fill drawing area */
		cairo_set_source_rgb(crdraw, altr / 255.0, altg / 255.0, altb / 255.0);
		cairo_rectangle(crdraw, 0, 0, w, h);
		cairo_fill(crdraw);
		cairo_stroke(crdraw);
		cairo_destroy(crdraw);
		/* no data */
		return (FALSE);
	}

	cairo_set_source_rgb(crdraw, bgcr / 255.0, bgcg / 255.0, bgcb / 255.0);
	/* select whole screen to fill with background color */
	cairo_rectangle(crdraw, 0, 0, w, h);
	cairo_fill(crdraw);
	cairo_stroke(crdraw);
	/* use zoom slider drawing scale */
	cairo_scale(crdraw, zfactor, zfactor);

	on_top_level_window_drawingarea1_expose_event_nodes(crdraw);
	on_top_level_window_drawingarea1_expose_event_edges(crdraw);
	cairo_destroy(crp);
	return (FALSE);
}
#endif

/* update status text */
static void update_status_text(char *text)
{

	/* update status text line */
	memset(charentry1buffer, 0, 64);

	/* */
	if (text) {
		snprintf(charentry1buffer, (64 - 1), "%s", text);
		if (option_gdebug > 1 || 0) {
			printf("%s(): %s\n", __func__, text);
			fflush(stdout);
		}
	} else {

		if (maingraph) {
			/* some info about the graph, based on parsed data */
			snprintf(charentry1buffer, (64 - 1),
				 "%d nodes, %d edges, %d crossings, size (%d,%d)",
				 maingraph->tnnodes, maingraph->tnedges, maingraph->sugi_fcrossings, maxx, maxy);
		} else {
			snprintf(charentry1buffer, 64 - 1, "no message");
		}

	}

	/* when running in console mode there is no entry1buffer */
	if (entry1buffer) {
		gtk_text_buffer_set_text(entry1buffer, charentry1buffer, -1);
		/* it is visible in the gui */
		/* only a re-draw needed */
		gtk_widget_queue_draw(drawingarea1);
	}

	return;
}

/* */
void update_status_text_cross(char *text)
{
	/* does not work as expected */
	return;
	update_status_text(text);
	while (gtk_main_iteration()) {
		/* this should update the status text */ ;
	}
	return;
}

/* changed type */
static void pos_changed(GtkWidget * widget, gpointer spinbutton)
{
	gfloat val = 0.0;

	if (widget) {
	}
	if (spinbutton) {
	}

	/* check if there is node data to draw */
	if (validdata == 0) {
		return;
	}

	/* at mirrory option force to keep postype 1 because type 2 does not work anymore. */
	if (option_mirrory) {
		/* message why pos value does not changes */
		printf("%s(): because mirror option is active pos mode is fixed to 1 or turn off mirror option\n", __func__);
		fflush(stdout);
		postype = 1;
		/* set the value for the new pos type */
		gtk_spin_button_set_value((GtkSpinButton *) posbutton, postype);
		return;
	}

	/* get the value for the new pos type */
	val = gtk_spin_button_get_value((GtkSpinButton *) spinbutton);

	/* set new pos type, 1,2,3 */
	postype = (int)val;

	/* re-calc positions */
	improve_positions(maingraph);

	/* final (x,y) positioning of nodes/edges */
	finalxy(maingraph);

	/* calculate edge connections */
	edgeconnections(maingraph);

	/* update status text */
	update_status_text(NULL);

	/* only a re-draw needed */
	gtk_widget_queue_draw(drawingarea1);

	return;
}

/* checkbox 1 is 'splines' */
static void check1_toggle(GtkWidget * widget, gpointer window)
{
	if (widget) {
	}
	if (window) {
	}
	/* toggle the splines option */
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		option_splines = 1;
	} else {
		option_splines = 0;
	}
	/* only a re-draw needed */
	gtk_widget_queue_draw(drawingarea1);
	return;
}

/* checkbox 2 is 'dummy's' draw dummy nodes */
static void dummy1_toggle(GtkWidget * widget, gpointer window)
{
	if (widget) {
	}
	if (window) {
	}
	/* toggle the splines option */
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		drawdummy = 1;
	} else {
		drawdummy = 0;
	}
	/* only a re-draw needed */
	gtk_widget_queue_draw(drawingarea1);
	return;
}

/* checkbox 5 is switch edge labels */
static void elabel1_toggle(GtkWidget * widget, gpointer window)
{
	if (widget) {
	}
	if (window) {
	}
	/* when no labels do not draw edge labels */
	if (option_labels == 0) {
		return;
	}
	/* toggle the splines option */
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		option_edgelabels = 1;
	} else {
		option_edgelabels = 0;
	}
	/* nop if no data */
	if (validdata == 0) {
		return;
	}
	/* if no edgelabels, skip */
	if (maingraph->tnedgelabels == 0) {
		return;
	}
	/* do re-layout */
	do_relayout_all(maingraph);
	/* now a re-draw needed */
	gtk_widget_queue_draw(drawingarea1);
	return;
}

/* checkbox 6 is switch labels */
static void label1_toggle(GtkWidget * widget, gpointer window)
{
	if (widget) {
	}
	if (window) {
	}
	/* toggle the splines option */
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		option_labels = 1;
	} else {
		option_labels = 0;
	}
	/* nop if no data */
	if (validdata == 0) {
		return;
	}
	/* force edgelabels off */
	option_edgelabels = 0;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(elabel1), FALSE);
	/* do re-layout */
	do_relayout_all(maingraph);
	/* now a re-draw needed */
	gtk_widget_queue_draw(drawingarea1);
	return;
}

/* checkbox 7 is node names instead of labels */
static void nnames1_toggle(GtkWidget * widget, gpointer window)
{
	if (widget) {
	}
	if (window) {
	}
	/* toggle the splines option */
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		option_nnames = 1;
	} else {
		option_nnames = 0;
	}
	/* nop if no data */
	if (validdata == 0) {
		return;
	}
	/* do re-layout */
	do_relayout_all(maingraph);
	/* now a re-draw needed */
	gtk_widget_queue_draw(drawingarea1);
	return;
}

/* checkbox 8 is mirror in y direction */
static void mirrory1_toggle(GtkWidget * widget, gpointer window)
{
	if (widget) {
	}
	if (window) {
	}
	/* toggle the splines option */
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		option_mirrory = 1;
	} else {
		option_mirrory = 0;
	}
	/* nop if no data */
	if (validdata == 0) {
		return;
	}
	/* force postype */
	postype = 1;
	/* set the value for the new pos type */
	gtk_spin_button_set_value((GtkSpinButton *) posbutton, postype);
	/* do re-layout */
	do_relayout_all(maingraph);
	/* now a re-draw needed */
	gtk_widget_queue_draw(drawingarea1);
	return;
}

/* checkbox 7 is switch popup labels */
static void popup1_toggle(GtkWidget * widget, gpointer window)
{
	if (widget) {
	}
	if (window) {
	}
	/* toggle the splines option */
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		option_popup = 1;
	} else {
		option_popup = 0;
	}
	/* nop if no data */
	if (validdata == 0) {
		return;
	}
	/* no redraw needed */
	return;
}

static void xspin_changed(GtkWidget * widget, gpointer spinbutton)
{
	gfloat val = 0.0;
	if (widget) {
	}
	if (spinbutton) {
	}

	/* get the value for the new drawing spreading factor */
	val = gtk_spin_button_get_value((GtkSpinButton *) spinbutton);

	/* set new spreading factor */
	xspacing = (int)val;

	/* check if there is node data to draw */
	if (validdata == 0) {
		return;
	}

	/* re-calc positions */
	improve_positions(maingraph);

	/* final (x,y) positioning of nodes/edges */
	finalxy(maingraph);

	/* calculate edge connections */
	edgeconnections(maingraph);

	/* update status text */
	update_status_text(NULL);

	/* only a re-draw needed */
	gtk_widget_queue_draw(drawingarea1);

	return;
}

static void yspin_changed(GtkWidget * widget, gpointer spinbutton)
{
	gfloat val = 0.0;

	if (widget) {
	}
	if (spinbutton) {
	}

	/* get the value for the new drawing spreading factor */
	val = gtk_spin_button_get_value((GtkSpinButton *) spinbutton);

	/* set new spreading factor */
	yspacing = (int)val;

	/* check if there is node data to draw */
	if (validdata == 0) {
		return;
	}

	/* re-calc positions */
	improve_positions(maingraph);

	/* final (x,y) positioning of nodes/edges */
	finalxy(maingraph);

	/* calculate edge connections */
	edgeconnections(maingraph);

	/* update status text */
	update_status_text(NULL);

	/* only a re-draw needed */
	gtk_widget_queue_draw(drawingarea1);

	return;
}

/* changed type */
static void bary_changed(GtkWidget * widget, gpointer spinbutton)
{
	gfloat val = 0.0;

	if (widget) {
	}
	if (spinbutton) {
	}

	/* get the value for the new bary type */
	val = gtk_spin_button_get_value((GtkSpinButton *) spinbutton);

	/* set new bary type, 1,2,3 or 4 */
	barytype = (int)val;

	/* check if there is node data to draw */
	if (validdata == 0) {
		return;
	}

	/* re-layout */
	do_relayout_all(maingraph);

	/* now a re-draw needed */
	gtk_widget_queue_draw(drawingarea1);

	return;
}

/* changed type */
static void rank_changed(GtkWidget * widget, gpointer spinbutton)
{
	gfloat val = 0.0;

	if (widget) {
	}
	if (spinbutton) {
	}

	/* get the value for the new bary type */
	val = gtk_spin_button_get_value((GtkSpinButton *) spinbutton);

	/* set new rank type, 1,2,3 or 4 */
	ranktype = (int)val;

	/* check if there is node data to draw */
	if (validdata == 0) {
		return;
	}

	/* re-layout */
	do_relayout_all(maingraph);

	/* now a re-draw needed */
	gtk_widget_queue_draw(drawingarea1);

	return;
}

/* fit drawing in window */
static void dofit(void)
{
	double xzscale = 1.0;
	double yzscale = 1.0;
	double newzscale = 1.0;
	double dval = 1.0;
	int val = 0;

	/* if no maxx, maxy is set */
	if (maxx == 0) {
		maxx = 1;
	}

	if (maxy == 0) {
		maxy = 1;
	}

	xzscale = (double)(1000 * drawing_area_xsize / maxx);
	yzscale = (double)(1000 * drawing_area_ysize / maxy);

	xzscale = xzscale / 1000.0;
	yzscale = yzscale / 1000.0;

	if ((xzscale - yzscale) > 0) {
		newzscale = yzscale;
	} else {
		newzscale = xzscale;
	}

	if (option_gdebug > 1) {
		printf
		    ("%s(): dval=%f fit zoom to %f from xscale=%f and yscale=%f drawingarea=(%d,%d) maxy=(%d,%d)\n",
		     __func__, dval, newzscale, yzscale, xzscale, drawing_area_xsize, drawing_area_ysize, maxx, maxy);
	}

	/* old dval = log ((newzscale * (double) 50.0) / 3.0) - 50.0; */
	dval = log(newzscale) / 3.0;
	dval = (dval * 50.0);
	dval = dval + 50.0;
	val = (int)dval;
	if (val < 0) {
		val = 0;
	}

	if (val > 100) {
		val = 100;
	}

	zfactor = exp((double)(3 * (val - 50)) / (double)50);
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale1), val);

	if (option_gdebug > 1) {
		printf("%s(): new slider value is %d (dval=%f) zfactor=%f\n", "dofit", val, dval, zfactor);
	}

	/* reset v xy min */
	vxmin = 0;
	vymin = 0;

	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjvscale2), 0);
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjhscale1), 0);

	return;
}

/* size of fields */
static struct gml_p *static_maingtk_textsizes1sz(struct gml_rl *info)
{
	struct gml_p *data = NULL;
	struct gml_p *dsub = NULL;
	int i = 0;

	data = dp_calloc(1, sizeof(struct gml_p));

	if (info == NULL) {
		return (data);
	}

	if (info->hd) {
		data->x = info->txsize;
		data->y = info->tysize;
	} else {
		for (i = 0; i < info->nparts; i++) {
			dsub = static_maingtk_textsizes1sz(info->parts[i]);
			if (info->dir == 0) {
				data->x = data->x + dsub->x;
				if (dsub->y > data->y) {
					data->y = dsub->y;
				}
			} else {
				if (dsub->x > data->x) {
					data->x = dsub->x;
				}
				data->y = data->y + dsub->y;
			}
			dp_free(dsub);
		}
	}

	info->bbx = data->x;
	info->bby = data->y;

	if (yydebug || 0) {
		printf
		    ("%s(): hd=%d dir=%d bb(x,y) size is (%d,%d) t(x,x) is (%d,%d) for `%s'\n",
		     __func__, info->hd, info->dir, info->bbx, info->bby, info->txsize, info->tysize, info->ulabel);
	}

	return (data);
}

static void static_maingtk_textsizes1eq(struct gml_rl *info)
{
	int i = 0;
	int eqx = 0;
	int eqy = 0;
	int xs = 0;
	int ys = 0;
	int mbbx = 0;
	int mbby = 0;
	char *sdir = NULL;

	if (info == NULL) {
		return;
	}

	if (info->nparts == 0) {
		if (yydebug || 0) {
			printf("%s(): skip \"%s\"\n", __func__, info->ulabel);
		}
		return;
	}

	if (info->hd == 0) {
		/*  */
		for (i = 0; i < info->nparts; i++) {
			if (info->dir == 0) {
				info->parts[i]->bby = info->bby;
			} else {
				info->parts[i]->bbx = info->bbx;
			}
		}

		for (i = 0; i < info->nparts; i++) {
			if (i == 0) {
				mbbx = info->parts[i]->bbx;
				mbby = info->parts[i]->bby;
			}
			if (info->parts[i]->bbx > mbbx) {
				mbbx = info->parts[i]->bbx;
			}
			if (info->parts[i]->bby > mbby) {
				mbby = info->parts[i]->bby;
			}
		}

		if (yydebug || 0) {
			printf("%s(): info->bbxy(%d,%d) versus mbbxy(%d,%d)\n", __func__, info->bbx, info->bby, mbbx, mbby);
		}

		xs = info->bbx / info->nparts;
		ys = info->bby / info->nparts;
		eqx = 1;
		eqy = 1;

		/* check if parts are same size */
		for (i = 0; i < info->nparts; i++) {

			if (info->parts[i]->bbx > xs) {
				eqx = 0;
			}
			if (info->parts[i]->bby > ys) {
				eqy = 0;
			}

		}

		/* set step factor if equal spread */
		for (i = 0; i < info->nparts; i++) {
			if (eqx) {
				info->parts[i]->xstep = xs;
			} else {
				info->parts[i]->xstep = 0;
			}
			if (eqy) {
				info->parts[i]->ystep = ys;
			} else {
				info->parts[i]->ystep = 0;
			}
			if (yydebug || 0) {
				printf("%s(): \"%s\" eqx=%d eqy=%d\n", __func__, info->parts[i]->ulabel, eqx, eqy);
			}
		}

		/* print summary */
		if (yydebug || 0) {
			if (info->dir == 0) {
				sdir = "x-dir";
			} else {
				sdir = "y-dir";
			}
			printf
			    ("%s(): size (%d,%d) %s %d parts eqx=%d eqy=%d xstep %d ystep %d\n",
			     __func__, info->bbx, info->bby, sdir, info->nparts, eqx, eqy, xs, ys);
			for (i = 0; i < info->nparts; i++) {
				printf("\t[%d] size (%d,%d) \"%s\" xstep=%d ystep=%d\n", i,
				       info->parts[i]->bbx, info->parts[i]->bby,
				       info->parts[i]->ulabel, info->parts[i]->xstep, info->parts[i]->ystep);
			}
		}

		for (i = 0; i < info->nparts; i++) {
			static_maingtk_textsizes1eq(info->parts[i]);
		}
	}

	return;
}

/* text size 1 record label */
static void static_maingtk_textsizes1rl(struct gml_rl *info)
{
	int i = 0;
	size_t len = 0;
	char *tmpb = NULL;
	char *p = NULL;
	char *q = NULL;
	cairo_surface_t *surface = NULL;
	cairo_t *crdraw = NULL;
	PangoLayout *layout = NULL;
	PangoFontDescription *desc = NULL;
	int w = 0;
	int h = 0;
	char buf[128];
	char *s = NULL;
	/* name of font to use, example "Sans" */
	const char *default_fontname = DEFAULT_FONTNAME;
	/* name of slant to use, example "Italic", "Oblique", "Roman" */
	const char *default_fontslant = DEFAULT_FONTSLANT;
	/* name of weight to use, example "Bold", "Book", "Light", "Medium", "Semi-bold", "Ultra-light" */
	const char *default_fontweight = DEFAULT_FONTWEIGHT;
	/* name of condensed to use, example "Semi-Condensed", "Condensed" */
	const char *default_fontcondensed = DEFAULT_FONTCONDENSED;
	/* font size to use, example "10", "18", "20" etc. */
	const char *default_fontsize = DEFAULT_FONTSIZE;

	if (info == NULL) {
		return;
	}

	/* check if has data */
	if (info->hd) {
		if (info->txsize == 0 && info->tysize == 0) {
			if (info->label == NULL) {
				/* shouldnothappen */
				info->label = uniqstr("  ");
			}
			len = strlen(info->label);
			if (len) {
				tmpb = (char *)dp_calloc(1, (len + 1));
				p = info->label;
				q = tmpb;
				/* un-escape the string */
				while (*p) {
					if (*p == '\\') {
						p++;
						if (*p == 0) {
							*q = '\\';
							q++;
							break;
						}
						if (*p == 'n' || *p == 'l' || *p == 'r') {
							*q = '\n';
						} else {
							*q = *p;
						}
						p++;
						q++;
					} else {
						*q = *p;
						p++;
						q++;
					}
				}
				len = strlen(tmpb);
				if (len) {
					if (tmpb[len - 1] == '\n') {
						tmpb[len - 1] = 0;
					}
				} else {
					info->ulabel = uniqstr("  ");
				}
				info->ulabel = uniqstr(tmpb);
				dp_free(tmpb);
				tmpb = NULL;
				/* calculate the text area */
				if (surface == NULL) {
					surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 10, 10);
				}

				/* */
				if (crdraw == NULL) {
					crdraw = cairo_create(surface);
				}

				/* */
				layout = pango_cairo_create_layout(crdraw);
				/* set the text to draw which is 0 terminated */
				pango_layout_set_text(layout, info->ulabel, -1);
				/* create the fontname description */
				memset(buf, 0, 128);
				/* name of font to use */
				default_fontname = uniqstr((char *)DEFAULT_FONTNAME);
				/* check if node has a specified font slant */
				default_fontslant = uniqstr((char *)DEFAULT_FONTSLANT);
				/* check if node has a specified font weight */
				default_fontweight = uniqstr((char *)DEFAULT_FONTWEIGHT);
				/* check if node has a specified font size */
				default_fontsize = uniqstr((char *)DEFAULT_FONTSIZE);
				/* create the font name string */
				snprintf(buf, (128 - 1), "%s %s %s %s %s",
					 default_fontname, default_fontslant, default_fontweight, default_fontcondensed,
					 default_fontsize);
				/* copy string buffer */
				s = uniqstr(buf);
				/* */
				desc = pango_font_description_from_string(s);
				/* */
				pango_layout_set_font_description(layout, desc);
				/* */
				pango_font_description_free(desc);
				/* */
				pango_cairo_update_layout(crdraw, layout);
				/* */
				w = 0;
				h = 0;
				/* */
				pango_layout_get_size(layout, &w, &h);
				/* */
				g_object_unref(G_OBJECT(layout));
				/* */
				cairo_destroy(crdraw);
				crdraw = NULL;
				/* */
				cairo_surface_destroy(surface);
				surface = NULL;
				/* */
				info->txsize = (w / PANGO_SCALE);
				info->tysize = (h / PANGO_SCALE);
				/* add small margin around text */
				info->txsize = info->txsize + 4;
				info->tysize = info->tysize + 4;

				/* */

				if (yydebug || 0) {
					printf("%s(): (%d,%d) size for `%s'\n", __func__, info->txsize, info->tysize, info->ulabel);
				}
			} else {
				/* at "" string */
				info->txsize = 4;
				info->tysize = 4;
				info->ulabel = uniqstr("  ");
			}
		}
	}

	for (i = 0; i < info->nparts; i++) {
		/* XXX todo fixme this can be 0 */
		if (info->parts) {
			static_maingtk_textsizes1rl(info->parts[i]);
		}
	}

	return;
}

static void static_maingtk_textsizes2rl(struct gml_rl *info, int count, int xoff, int yoff, int bbx, int bby)
{
	int i = 0;
	char *sdir = NULL;
	int xo = 0;
	int yo = 0;
	int ibbx = 0;
	int ibby = 0;
	int abbx = 0;
	int abby = 0;

	if (info->hd == 0) {

		if (yydebug || 0) {
			printf
			    ("%s(%d): xyoff(%d,%d) bbxy(%d,%d) nparts=%d info->bbxy(%d,%d)\n",
			     __func__, count, xoff, yoff, bbx, bby, info->nparts, info->bbx, info->bby);
		}

		if (yydebug || 0) {
			if (info->dir == 0) {
				sdir = "x-dir";
			} else {
				sdir = "y-dir";
			}
			printf("%s(): rl=%p %s hd=0 bbxy(%d,%d) nparts=%d\n",
			       __func__, (void *)info, sdir, info->bbx, info->bby, info->nparts);

			for (i = 0; i < info->nparts; i++) {
				if (info->dir == 0) {
					sdir = "x-dir";
				} else {
					sdir = "y-dir";
				}
				printf("\tparts[%d]=%p %s hd=%d \"%s\"\n", i,
				       (void *)info->parts[i], sdir, info->parts[i]->hd, info->parts[i]->ulabel);
			}
		}

		xo = 0;
		yo = 0;
		abbx = 0;
		abby = 0;

		for (i = 0; i < info->nparts; i++) {

			if (info->parts[i]->hd == 0) {
				ibbx = info->parts[i]->bbx;
				ibby = info->parts[i]->bby;
				abbx = ibbx;
				abby = ibby;

				static_maingtk_textsizes2rl(info->parts[i], i, xoff + xo, yoff + yo, ibbx, ibby);
				/*
				 */

				if ((i + 1) < info->nparts) {
					if (info->parts[i + 1]->hd == 0) {
						if (info->parts[i]->dir == 0) {
							yo = yo + abby;
						} else {
							xo = xo + abbx;
						}
					}
				}
				/*
				 *
				 */
			} else {

				if (info->parts[i]->dir == 0) {
					info->parts[i]->xoff = xoff + xo + abbx;
					info->parts[i]->yoff = yoff + yo;
					info->parts[i]->bby = bby;
					if (info->parts[i]->xstep) {
						xo = xo + info->parts[i]->xstep + abbx;
					} else {
						xo = xo + info->parts[i]->bbx + abbx;
					}
				} else {
					info->parts[i]->xoff = xoff + xo;
					info->parts[i]->yoff = yoff + yo + abby;
					info->parts[i]->bbx = bbx;
					if (info->parts[i]->ystep) {
						yo = yo + info->parts[i]->ystep + abby;
					} else {
						yo = yo + info->parts[i]->bby + abby;
					}
				}

				abbx = 0;
				abby = 0;

			}

		}

	} else {

		if (yydebug || 0) {
			if (info->dir == 0) {
				sdir = "x-dir";
			} else {
				sdir = "y-dir";
			}
			printf
			    ("%s(): rl=%p %s hd=1 bbxy(%d,%d) \"%s\" xyoff(%d,%d) bbxy(%d,%d)\n",
			     __func__, (void *)info, sdir, info->bbx, info->bby, info->ulabel, xoff, yoff, bbx, bby);
		}

	}

	return;
}

/* handle record label sizes for one node */
static void static_maingtk_textsizes1n(struct gml_node *node)
{
	struct gml_p *data = NULL;

	/* calc (x,y) text size of all parts in record label */
	static_maingtk_textsizes1rl(node->rlabel);

	data = static_maingtk_textsizes1sz(node->rlabel);

	if (data == NULL) {
		/* shouldnothappen */
		return;
	}

	if (yydebug || 0) {
		printf("%s(): d is (%d,%d) versus bbxy(%d,%d)\n", __func__, data->x, data->y, node->bbx, node->bby);
	}

	/* check for use of step of bb */
	static_maingtk_textsizes1eq(node->rlabel);

	/* now position the text parts and result in the rlabel structs */
	node->bbx = data->x;
	node->bby = data->y;

	/* save copy of full size */
	node->fbbx = data->x;
	node->fbby = data->y;

	/* relocate the parts */
	static_maingtk_textsizes2rl(node->rlabel, 0, 0, 0, node->bbx, node->bby);

	dp_free(data);

	return;
}

/* size of one 1 html item
 * the item has fontsize, name and bitflags of type
 */
static struct gml_p *static_maingtk_textsizes1htmlsz1item(struct gml_hitem *item)
{
	struct gml_p *data = NULL;
	int fsz = 0;
	char *slant = NULL;
	char *weight = NULL;
	char *fn = NULL;
	cairo_surface_t *surface = NULL;
	cairo_t *crdraw = NULL;
	PangoLayout *layout = NULL;
	PangoFontDescription *desc = NULL;
	char buf[128];
	char *s = NULL;
	int w = 0;
	int h = 0;

	data = dp_calloc(1, sizeof(struct gml_p));

	if (item == NULL) {
		/* shouldnothappen */
		return (data);
	}

	if (item->bitflags.table) {
		if (yydebug || 0) {
			printf("%s(): item is a <table>\n", __func__);
		}
		if (item->table == NULL) {
			/* shouldnothappen */
			printf("%s(): item is a <table> but nil table\n", __func__);
			return (data);
		}
		/* set the size of <table> as size of this item */
		item->txsize = item->table->txsizemin;
		item->tysize = item->table->tysizemin;
		/* */
		data->x = item->txsize;
		data->y = item->tysize;

		if (yydebug || 0) {
			printf("%s(): \"%s\" has size (%d,%d) d (%d,%d)\n", __func__, "<table>", item->txsize, item->tysize,
			       data->x, data->y);
		}

		return (data);
	}

	if (yydebug || 0) {
		printf("%s(): item->text is \"%s\"\n", __func__, item->text);
	}

	if (item->text == NULL) {
		/* shouldnothappen */
		return (data);
	}

	if (strlen(item->text) == 0) {
		/* shouldnothappen */
		return (data);
	}

	/* get fontsize */
	if (item->fontsize < 0) {
		/* not specified */
		fsz = DEFAULT_FONTSIZE_INT;
		item->fontsize = fsz;
	} else {
		/* check fontsize */
		if (item->fontsize < 5) {
			/* too small text */
			return (data);
		}
		fsz = item->fontsize;
	}

	/* italic slant */
	if (item->bitflags.i) {
		slant = "italic";
	} else {
		slant = DEFAULT_FONTSLANT;
	}

	item->fontslant = uniqstr(slant);

	/* bold weight */
	if (item->bitflags.b) {
		weight = "bold";
	} else {
		weight = DEFAULT_FONTWEIGHT;
	}

	item->fontweight = uniqstr(weight);

	/* check if fontname set */
	if (item->fontname) {
		/* at unknown fontname, default is used without warning */
		fn = item->fontname;
	} else {
		fn = DEFAULT_FONTNAME;
	}

	if (surface == NULL) {
		surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 10, 10);
	}

	/* */
	if (crdraw == NULL) {
		crdraw = cairo_create(surface);
	}

	/* */
	layout = pango_cairo_create_layout(crdraw);

	/* set the text to draw which is 0 terminated */
	pango_layout_set_text(layout, item->text, -1);

	/* create the fontname description */
	memset(buf, 0, 128);

	/* create the font name string */
	snprintf(buf, (128 - 1), "%s %s %s %s %d", fn, slant, weight, DEFAULT_FONTCONDENSED, fsz);

	s = uniqstr(buf);

	/* */
	desc = pango_font_description_from_string(s);

	/* */
	pango_layout_set_font_description(layout, desc);

	/* */
	pango_font_description_free(desc);

	/* */
	pango_cairo_update_layout(crdraw, layout);

	/* */
	w = 0;
	h = 0;

	/* */
	pango_layout_get_size(layout, &w, &h);

	/* set text (x,y) size */
	item->txsize = (w / PANGO_SCALE);
	item->tysize = (h / PANGO_SCALE);

	/* */
	g_object_unref(G_OBJECT(layout));

	cairo_destroy(crdraw);
	crdraw = NULL;
	/* */
	cairo_surface_destroy(surface);
	surface = NULL;

	data->x = item->txsize;
	data->y = item->tysize;

	if (yydebug || 0) {
		printf("%s(): \"%s\" has size (%d,%d) d (%d,%d)\n", __func__, item->text, item->txsize, item->tysize, data->x,
		       data->y);
	}

	return (data);
}

/* size of html items */
static struct gml_p *static_maingtk_textsizes1htmlszitems(struct gml_node *node, struct gml_hl *info)
{
	struct gml_p *data = NULL;
	struct gml_p *ditem = NULL;
	struct gml_hitem *pitem = NULL;
	struct gml_hitem *pitem2 = NULL;
	struct gml_hilist *pi = NULL;
	struct gml_hilist *pi2 = NULL;
	struct gml_hilist *sl = NULL;
	struct gml_hilist *el = NULL;
	int mxl = 0;
	int mxl2 = 0;
	int myl = 0;
	int my = 0;
	int mx = 0;
	int tof = 0;

	data = dp_calloc(1, sizeof(struct gml_p));

	if (node == NULL) {
		return (data);
	}

	if (info == NULL) {
		return (data);
	}

	if (info->il == NULL) {
		/* shouldnothappen */
		return (data);
	}

	if (yydebug || 0) {
		printf("%s(): items of node \"%s\" are:\n", __func__, node->name);
	}

	/* get size of the text elements */
	pi = info->il;

	while (pi) {
		pitem = pi->items;
		if (pitem) {
			if (pi->items->bitflags.br) {
			} else if (pi->items->bitflags.hr) {
			} else if (pi->items->bitflags.vr) {
			} else if (pi->items->bitflags.img) {
			} else if (pi->items->bitflags.table) {
				if (0) {
					printf("%s(): table bit set. todo\n", __func__);
				}
			} else {
				if (yydebug || 0) {
					printf("\"%s\"\n", pi->items->text);
				}
				ditem = static_maingtk_textsizes1htmlsz1item(pitem);
				if (ditem->x == 0 || ditem->y == 0) {
					/* zero sized text */
				}
				pitem->txsizemin = ditem->x;
				pitem->tysizemin = ditem->y;
				pitem->txsize = ditem->x;
				pitem->tysize = ditem->y;
				dp_free(ditem);
			}
		}
		pi = pi->next;
	}
	/* */
	if (yydebug || 0) {
		printf("\n");
	}

	/* determine the size of these lines */
	mx = 0;
	my = 0;
	/* */
	pi = info->il;
	tof = 0;
	while (pi) {
		/* set start/end line */
		sl = pi;
		el = pi;
		pi2 = pi;
		mxl2 = 0;
		myl = 0;
		while (pi2) {
			pitem2 = pi2->items;
			el = pi2;
			if (pi2->items) {
				if (pi2->items->bitflags.br) {
					/* newline */
					if (myl == 0) {
						/* a <br/> can have a fontsize set */
						if (pi2->items->fontsize > 0) {
							myl = pi2->items->fontsize;
						} else {
							myl = DEFAULT_FONTSIZE_INT;
						}
					}
					/* set x at start of line */
					/* mxl = 0; */
					break;
				} else if (pi2->items->bitflags.hr) {
				} else if (pi2->items->bitflags.vr) {
				} else if (pi2->items->bitflags.img) {
				} else if (pi2->items->bitflags.table) {
					if (0) {
						printf("%s(): table bit set todo\n", __func__);
					}
				} else {
					/* text x offset in this line */
					mxl2 = mxl2 + pitem2->txsize;
					if (mxl2 > mx) {
						mx = mxl2;
					}
					if (pitem2->tysize > myl) {
						myl = pitem2->tysize;
					}
				}
			}
			pi2 = pi2->next;
		}
		/* update */

		mxl = 0;

		pi2 = sl;
		while (pi2) {
			pitem2 = pi2->items;
			if (pitem2) {
				/* text x offset in this line */
				pitem2->txoff = mxl;
				mxl = mxl + pitem2->txsize;
				if (mxl > mx) {
					mx = mxl;
				}
				/* y size of this text line */
				pitem2->lysize = myl;
				/* text y offset in this line */
				pitem2->tyoff = (myl - pitem2->tysize) + tof;
				if (pi2 == el) {
					break;
				}
			}
			pi2 = pi2->next;
		}
		tof = tof + myl;
		if (tof > my) {
			my = tof;
		}
		/* continue scan other parts of item */
		if (pi2) {
			pi = pi2->next;
		} else {
			break;
		}
	}

	/* set node text (x,y) */
	node->tx = mx + 2;
	node->ty = my + 2;

	data->x = node->tx;
	data->y = node->ty;

	/* here update text x pos for br align statements if any todo */

	node->txsize = 1;

	if (yydebug || 0) {
		printf("%s(): size (%d,%d) for node \"%s\"\n", __func__, data->x, data->y, node->name);
	}

	return (data);
}

/* one <table> in table list */
static struct gml_p *static_maingtk_textsizes1htmlsz1table(struct gml_node *node, struct gml_htlist *tlptr)
{
	struct gml_p *data = NULL;
	struct gml_p *subdata = NULL;
	struct gml_p *di = NULL;
	struct gml_titem *titemptr = NULL;
	struct gml_htlist *tlptrsub = NULL;
	struct gml_tritemlist *trptr = NULL;	/* list of <tr> items in this table */
	struct gml_tditem *tdiptr = NULL;
	struct gml_hilist *ilptr = NULL;
	int *tdsz = NULL;
	int ntr = 0;
	int numtd = 0;
	int ntdmax = 0;
	int trysum = 0;
	int ilmaxy = 0;
	int trxsum = 0;
	int trmax = 0;
	int tdcount = 0;
	int tdxtotal = 0;
	int tdytotal = 0;
	int wanttd = 0;
	int i = 0;
	struct gml_tditem *dummytd = NULL;
	int ystep = 0;
	int tablebgcolor = 0x00ffffff;	/* white */

	data = dp_calloc(1, sizeof(struct gml_p));

	titemptr = tlptr->titem;

	if (titemptr == NULL) {
		/* shouldnothappen */
		return (data);
	}

	/* first scan the sub <table> data */
	tlptrsub = titemptr->tl;

	while (tlptrsub) {
		subdata = static_maingtk_textsizes1htmlsz1table(node, tlptrsub);
		/* todo */
		dp_free(subdata);
		tlptrsub = tlptrsub->next;
	}

	/* fillcolor of this <table> */
	tablebgcolor = titemptr->bgcolor;

	trptr = titemptr->tr;	/* list of <tr> items in this table */

	if (trptr == NULL) {
		/* shouldnothappen */
		return (data);
	}

	ntdmax = 0;
	ntr = 0;
	trmax = 0;
	while (trptr) {
		if (trptr->tritem == NULL) {
			/* shouldnothappen */
			return (data);
		}
		/* needed x size for this <tr> */
		trxsum = 0;

		/* <td> in <tr> */
		tdiptr = trptr->tritem->tdi;
		if (tdiptr == NULL) {
			/* shouldnothappen */
			return (data);
		}

		/* number of <td> in this <tr> */
		numtd = 0;
		ilmaxy = 0;

		while (tdiptr) {
			ilptr = tdiptr->il;
			if (ilptr == NULL) {
				/* shouldnothappen */
				return (data);
			}

			/* size of <td> */
			tdxtotal = 0;
			tdytotal = 0;

			while (ilptr) {
				di = static_maingtk_textsizes1htmlsz1item(ilptr->items);
				/* handle item size */
				/* x size of this <td> */

				if (yydebug || 0) {
					printf("%s(): item in td (%d,%d) for \"%s\"\n", __func__, di->x, di->y, ilptr->items->text);
				}
				if (di->x > tdxtotal) {
					tdxtotal = di->x;
				}
				tdytotal = tdytotal + di->y;
				trxsum = trxsum + di->x;

				tdiptr->ysize = di->y;

				/* */
				dp_free(di);
				/* next item */
				ilptr = ilptr->next;
			}

			/* set the size in this <td> */
			tdiptr->xsize = tdxtotal;
			tdiptr->ysize = tdytotal;

			if (tdiptr->ysize > ilmaxy) {
				ilmaxy = tdiptr->ysize;
			}

			if (yydebug || 0) {
				printf("%s(): td (%d,%d) size for this these td items ilmaxy=%d\n", __func__, tdiptr->xsize,
				       tdiptr->ysize, ilmaxy);
			}
			numtd++;
			/* next <td> */
			tdiptr = tdiptr->next;
		}

		if (yydebug || 0) {
			printf("%s(): setting ysize to %d\n", __func__, ilmaxy);
		}
		/* y size in this <tr> for the <td> items */
		trptr->tritem->ysize = ilmaxy;

		/* number of <td> in this <tr> */
		trptr->tritem->numtd = numtd;
		if (numtd > ntdmax) {
			ntdmax = numtd;
		}
		/* number of <tr> statements */
		ntr++;
		/* widest <tr> */
		if (trxsum > trmax) {
			trmax = trxsum;
		}
		/* needed y size for this <td> in this <tr> */
		trysum = trysum + ilmaxy;
		/* next <tr> */
		trptr = trptr->next;
	}

	/* number of <tr> in this <table> */
	titemptr->numtr = ntr;
	titemptr->nrows = ntr;

	/* number of <td> needed for this table */
	titemptr->numtd = ntdmax;
	titemptr->ncols = ntdmax;

	/* needed y size to hold all <td> */
	titemptr->tysize = trysum;
	titemptr->tysizemin = trysum;

	/* re-scan to update the <td> size at <tr> */
	tdsz = dp_calloc(1, (sizeof(int) * ntdmax));

	/* re-scan */
	titemptr = tlptr->titem;

	trptr = titemptr->tr;	/* list of <tr> items in this table */

	/* find the widest <td> at a <tr> */
	while (trptr) {
		/* <td> in <tr> */
		tdiptr = trptr->tritem->tdi;

		tdcount = 0;
		while (tdiptr) {
			if (tdiptr->xsize > tdsz[tdcount]) {
				tdsz[tdcount] = tdiptr->xsize;
			}
			tdcount++;
			/* next <td> */
			tdiptr = tdiptr->next;
		}

		/* next <tr> */
		trptr = trptr->next;
	}

	/* update the x step */
	trptr = titemptr->tr;	/* list of <tr> items in this table */

	trmax = 0;
	while (trptr) {
		/* <td> in <tr> */
		tdiptr = trptr->tritem->tdi;
		trxsum = 0;
		tdcount = 0;
		while (tdiptr) {
			/* (x,y) size of <td> */
			if (yydebug || 0) {
				printf("%s():  at col=%d size (%d,%d) for this td\n", __func__, tdcount, tdiptr->xsize,
				       tdiptr->ysize);
			}
			tdiptr->xstep = tdsz[tdcount];
			tdiptr->ystep = trptr->tritem->ysize;
			trxsum = trxsum + tdiptr->xstep;
			/* set max reached x size */
			if (trxsum > trmax) {
				trmax = trxsum;
			}
			if (yydebug || 0) {
				printf("%s(): at col=%d size (%d,%d) trmax=%d\n", __func__, tdcount, tdiptr->xstep, tdiptr->ystep,
				       trmax);
			}
			tdcount++;
			/* next <td> */
			tdiptr = tdiptr->next;
		}

		/* next <tr> */
		trptr = trptr->next;
	}

	/* needed x size to hold all <tr> */
	titemptr->txsize = trmax;
	titemptr->txsizemin = trmax;

	/* indicate that min. size is set for this <table> */
	titemptr->sizeset = 1;

	/* set <table> (x,y) size */
	data->x = trmax;
	data->y = trysum;

	/* add dummy <td> to fill the tables */
	trptr = titemptr->tr;	/* list of <tr> items in this table */

	/* find the widest <td> at a <tr> */
	while (trptr) {
		/* <td> in <tr> */
		tdiptr = trptr->tritem->tdi;

		/* number of needed <td> */
		wanttd = ntdmax;

		ystep = trptr->tritem->ysize;

		tdcount = 0;

		while (tdiptr) {
			wanttd--;
			/* set min. needed (x,y) size for <td> (x,y) size set earlier */
			tdiptr->xsizemin = tdiptr->xsize;
			tdiptr->ysizemin = tdiptr->ysize;
			tdcount++;
			/* next <td> */
			tdiptr = tdiptr->next;
		}

		if (yydebug || 0) {
			printf("%s(): <tr> has %d <td> but needs %d <td> adding %d dummy <td>\n", __func__, trptr->tritem->numtd,
			       ntdmax, wanttd);
		}

		/* add the dummy <td> */
		for (i = 0; i < wanttd; i++) {
			dummytd = dp_calloc(1, sizeof(struct gml_tditem));
			/* this is a <td> with no data */
			dummytd->dummy = 1;
			/* x size depends on pos. of <td> */
			dummytd->xsize = tdsz[tdcount];
			dummytd->xstep = tdsz[tdcount];
			dummytd->xsizemin = tdsz[tdcount];
			/* y size */
			dummytd->ysize = ystep;
			dummytd->ystep = ystep;
			dummytd->ysizemin = ystep;
			/* fill color */
			dummytd->bgcolor = tablebgcolor;

			/* link in */
			if (trptr->tritem->tdi == NULL) {
				trptr->tritem->tdi = dummytd;
				trptr->tritem->tdiend = dummytd;
			} else {
				trptr->tritem->tdiend->next = dummytd;
				trptr->tritem->tdiend = dummytd;
			}

			tdcount++;
		}
		/* next <tr> */
		trptr = trptr->next;
	}

	/* ready with <td> x size data */
	dp_free(tdsz);

	if (yydebug || 0) {
		printf("%s(): size (%d,%d) <table> in for node \"%s\"\n", __func__, data->x, data->y, node->name);
	}

	return (data);
}

/* size of html tables */
static struct gml_p *static_maingtk_textsizes1htmlsztables(struct gml_node *node, struct gml_hl *info)
{
	struct gml_p *data = NULL;
	struct gml_p *subdata = NULL;
	struct gml_htlist *tlptr = NULL;	/* list of sub table items */
	int trx = 0;
	int try = 0;

	data = dp_calloc(1, sizeof(struct gml_p));

	if (node == NULL) {
		/* shouldnothappen */
		return (data);
	}

	if (info == NULL) {
		/* shouldnothappen */
		return (data);
	}

	if (info->tl == NULL) {
		/* shouldnothappen */
		return (data);
	}

	tlptr = info->tl;
	while (tlptr) {
		subdata = static_maingtk_textsizes1htmlsz1table(node, tlptr);
		/* temp test todo */
		trx = subdata->x;
		try = subdata->y;

		dp_free(subdata);
		tlptr = tlptr->next;
	}

	data->x = trx + 2;
	data->y = try + 2;

	if (yydebug || 0) {
		printf("%s(): size (%d,%d) for node \"%s\"\n", __func__, data->x, data->y, node->name);
	}

	return (data);
}

/* size of html */
static struct gml_p *static_maingtk_textsizes1htmlsz(struct gml_node *node, struct gml_hl *info)
{
	struct gml_p *data = NULL;

	if (info->mode == 0) {
		/* html items */
		data = static_maingtk_textsizes1htmlszitems(node, info);
	} else {
		/* html tables */
		data = static_maingtk_textsizes1htmlsztables(node, info);
	}

	return (data);
}

/* handle html label sizes for one node */
static void static_maingtk_textsizes1htmln(struct gml_node *node)
{
	struct gml_p *data = NULL;

	/* preset with small value */
	node->tx = 0;
	node->ty = 0;

	node->bbx = 10;
	node->bby = 10;

	/* save copy of full size */
	node->fbbx = 10;
	node->fbby = 10;

	data = static_maingtk_textsizes1htmlsz(node, node->hlabel);

	/* for a box */
	node->bbx = data->x;	// node->tx + 4;
	node->bby = data->y;	// node->ty + 4;

	/* save copy of full size */
	node->fbbx = node->bbx;
	node->fbby = node->bby;

	if (yydebug || 0) {
		printf("%s(): size (%d,%d) for node \"%s\"\n", __func__, node->bbx, node->bby, node->name);
	}

	/* */
	dp_free(data);

	return;
}

/* translate \n \l \r in dot string
 * todo \N and this is already done in dpif.c to check.
 */
static char *unesc(char *str)
{
	char *buf = NULL;
	char *p = NULL;
	char *q = NULL;
	if (str == NULL) {
		return (NULL);
	}
	if (strlen(str) == 0) {
		return (str);
	}
	if (strchr(str, '\\') == NULL) {
		/* string has no esc chars */
		return (uniqstr(str));
	}
	buf = dp_calloc(1, (strlen(str) + 1));
	if (buf == NULL) {
		return (str);
	}
	p = str;
	q = buf;
	while (*p) {
		/* check for \n \l \r to change */
		if ((*p) == '\\') {
			if (*(p + 1) == 'n' || *(p + 1) == 'l' || *(p + 1) == 'r') {
				(*q) = '\n';
				q++;
				p++;
				p++;
			} else {
				/* copy other esc char */
				(*q) = (*p);
				p++;
				q++;
				(*q) = (*p);
				p++;
				q++;
			}
		} else {
			/* regular char to copy */
			(*q) = (*p);
			q++;
			p++;
		}
	}
	p = uniqstr(buf);
	dp_free(buf);
	buf = NULL;
	return (p);
}

/*zzz
 * update the (x,y) size of text in the nodes
 *
 * a GTK font pattern. These have the syntax
 * fontname [properties] [fontsize]
 *
 * where fontname is the family name,
 * properties is a list of property values separated by spaces,
 * and fontsize is the point size.
 * The properties that you may specify for GTK font patterns are as follows:
 * Slant properties: ‘Italic’ or ‘Oblique’. If omitted, the default (roman) slant is implied.
 * Weight properties: ‘Bold’, ‘Book’, ‘Light’, ‘Medium’, ‘Semi-bold’, or ‘Ultra-light’. If omitted, ‘Medium’ weight is implied.
 * Width properties: ‘Semi-Condensed’ or ‘Condensed’. If omitted, a default width is used.
 * Here are some examples of GTK font patterns:
 * Monospace 12
 * Monospace Bold Italic 12
 *
 * there are nodes with labels whicj is a piece of text on display
 * and nodes with a record type with multiple small text to layout
 * in multiple steps for the different fields.
 * if option labels is 0 then no label text is draw
 */
static void static_maingtk_textsizes(void)
{
	cairo_surface_t *surface = NULL;
	cairo_t *crdraw = NULL;
	PangoLayout *layout = NULL;
	PangoFontDescription *desc = NULL;
	int w = 0;
	int h = 0;
	char buf[128];
	char *s = NULL;
	int txname = 0;
	int tyname = 0;
	int bbxname = 0;
	int bbyname = 0;
	/* name of font to use, example "Sans" */
	const char *default_fontname = DEFAULT_FONTNAME;
	/* name of slant to use, example "Italic", "Oblique", "Roman" */
	const char *default_fontslant = DEFAULT_FONTSLANT;
	/* name of weight to use, example "Bold", "Book", "Light", "Medium", "Semi-bold", "Ultra-light" */
	const char *default_fontweight = DEFAULT_FONTWEIGHT;
	/* name of condensed to use, example "Semi-Condensed", "Condensed" */
	const char *default_fontcondensed = DEFAULT_FONTCONDENSED;
	/* font size to use, example "10", "18", "20" etc. */
	const char *default_fontsize = DEFAULT_FONTSIZE;
	/* */
	struct gml_nlist *nl = NULL;
	nl = maingraph->nodelist;
	while (nl) {
		if (nl->node->dummy) {
			/* dummynode has no text */
			nl->node->tx = 0;
			nl->node->ty = 0;
			nl->node->bbx = 0;
			nl->node->bby = 0;
			nl->node->txsize = 1;	/* text size is set */
		} else {
			/* first get size of node name */

			if (nl->node->name == NULL) {
				/* shouldnothapen */
				nl->node->name = "fixme-nil-node-name";
			}

			/* calculate the text area */
			if (surface == NULL) {
				surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 10, 10);
			}

			/* */
			if (crdraw == NULL) {
				crdraw = cairo_create(surface);
			}
			/* */
			layout = pango_cairo_create_layout(crdraw);
			/* set the text to draw which is 0 terminated */
			pango_layout_set_text(layout, nl->node->name, -1);
			/* create the fontname description */
			memset(buf, 0, 128);
			/* name of font to use */
			default_fontname = uniqstr((char *)DEFAULT_FONTNAME);
			/* check if node has a specified font slant */
			default_fontslant = uniqstr((char *)DEFAULT_FONTSLANT);
			/* check if node has a specified font weight */
			default_fontweight = uniqstr((char *)DEFAULT_FONTWEIGHT);
			/* check if node has a specified font size */
			default_fontsize = uniqstr((char *)DEFAULT_FONTSIZE);
			/* create the font name string */
			snprintf(buf, (128 - 1), "%s %s %s %s %s",
				 default_fontname, default_fontslant, default_fontweight, default_fontcondensed, default_fontsize);
			/* copy string buffer */
			s = uniqstr(buf);
			/* */
			desc = pango_font_description_from_string(s);
			/* */
			pango_layout_set_font_description(layout, desc);
			/* */
			pango_font_description_free(desc);
			/* */
			pango_cairo_update_layout(crdraw, layout);
			/* */
			w = 0;
			h = 0;
			/* */
			pango_layout_get_size(layout, &w, &h);
			/* */
			g_object_unref(G_OBJECT(layout));
			/* */
			if (option_gdebug > 1 || 0) {
				printf("%s(): size (%d,%d) for node name \"%s\"\n",
				       __func__, (w / PANGO_SCALE), (h / PANGO_SCALE), nl->node->name);
				fflush(stdout);
			}

			/* set in unode the text area size */
			txname = (w / PANGO_SCALE);
			tyname = (h / PANGO_SCALE);

			/* for a box */
			bbxname = txname + 4;
			bbyname = tyname + 4;

			/* change esc chars if any */
			nl->node->nlabel = unesc(nl->node->nlabel);

			/* calculate the text area */
			if (surface == NULL) {
				surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 10, 10);
			}

			/* */
			if (crdraw == NULL) {
				crdraw = cairo_create(surface);
			}

			/* */
			layout = pango_cairo_create_layout(crdraw);
			/* set the text to draw which is 0 terminated */
			pango_layout_set_text(layout, nl->node->nlabel, -1);
			/* create the fontname description */
			memset(buf, 0, 128);
			/* name of font to use */
			default_fontname = uniqstr((char *)DEFAULT_FONTNAME);
			/* check if node has a specified font slant */
			default_fontslant = uniqstr((char *)DEFAULT_FONTSLANT);
			/* check if node has a specified font weight */
			default_fontweight = uniqstr((char *)DEFAULT_FONTWEIGHT);
			/* check if node has a specified font size */
			default_fontsize = uniqstr((char *)DEFAULT_FONTSIZE);
			/* create the font name string */
			snprintf(buf, (128 - 1), "%s %s %s %s %s",
				 default_fontname, default_fontslant, default_fontweight, default_fontcondensed, default_fontsize);
			/* copy string buffer */
			s = uniqstr(buf);
			/* */
			desc = pango_font_description_from_string(s);
			/* */
			pango_layout_set_font_description(layout, desc);
			/* */
			pango_font_description_free(desc);
			/* */
			pango_cairo_update_layout(crdraw, layout);
			/* */
			w = 0;
			h = 0;
			/* */
			pango_layout_get_size(layout, &w, &h);
			/* */
			g_object_unref(G_OBJECT(layout));
			/* */
			if (option_gdebug > 1) {
				printf("%s(): size (%d,%d) for node nlabel \"%s\"\n",
				       __func__, (w / PANGO_SCALE), (h / PANGO_SCALE), nl->node->nlabel);
				fflush(stdout);
			}

			/* set in unode the text area size */
			nl->node->tx = (w / PANGO_SCALE);
			nl->node->ty = (h / PANGO_SCALE);

			/* for a box */
			nl->node->bbx = nl->node->tx + 4;
			nl->node->bby = nl->node->ty + 4;

			/* full sized copy */
			nl->node->fbbx = nl->node->bbx;
			nl->node->fbby = nl->node->bby;

			if (option_gdebug > 1 || 0) {
				printf("%s(): hlabel=%p done=%d and rlabel=%p done=%d\n", __func__, (void *)nl->node->hlabel,
				       nl->node->hlabeldone, (void *)nl->node->rlabel, nl->node->rlabeldone);
			}

			/* html label or record label */
			if ((nl->node->hlabel != NULL) && (nl->node->hlabeldone == 0)) {
				/* html label */
				static_maingtk_textsizes1htmln(nl->node);
				nl->node->hlabeldone = 1;
			} else {
				/* record node label */
				if ((nl->node->rlabel != NULL) && (nl->node->rlabeldone == 0)) {
					static_maingtk_textsizes1n(nl->node);
					nl->node->rlabeldone = 1;
				}
			}

			if (option_nnames == 1) {
				/* use node names instead of labels and do not draw r/h style labels */
				nl->node->drawrh = 0;

				nl->node->tx = txname;
				nl->node->ty = tyname;

				/* for a box */
				nl->node->bbx = bbxname;
				nl->node->bby = bbyname;

			} else {
				nl->node->drawrh = 1;
			}

			/* label==0 then do not draw text label of a node and set small size */
			if (option_labels == 0) {
				nl->node->tx = 10;
				nl->node->ty = 10;

				/* for a box */
				nl->node->bbx = nl->node->tx + 4;
				nl->node->bby = nl->node->ty + 4;
				/* keep fbbx and fbby intact */
			}

			nl->node->txsize = 1;	/* text size is set */

		}
		nl = nl->next;
	}

	/* clear the draw context etc */
	if (layout) {
		layout = NULL;
	}

	if (crdraw) {
		cairo_destroy(crdraw);
		crdraw = NULL;
	}

	if (surface) {
		cairo_surface_destroy(surface);
		surface = NULL;
	}

	return;
}

/* do final (x,y) of nodes/edges for mode 1 */
static void finalxy1(struct gml_graph *g)
{
	struct gml_nlist *lnl = NULL;
	int hw = 0;
	int xoff = 0;
	int yoff = 0;
	int i = 0;
	int ecount = 0;

	/* x positioning */
	make_posnodes(maingraph);

	maxx = 0;
	xoff = 0;

	/* scan hor. to adjust the x positions. */
	for (i = 0; i < (g->widestnnodes + 1); i++) {
		/* x spacing between the hor. levels */
		xoff = xoff + xspacing;
		/* determine half-way of the xpos. */
		if (g->wpos[i] == 0) {
			/* if only dummy nodes */
			hw = xspacing / 2;
		} else {
			hw = (g->wpos[i] / 2);
		}

		/* update with current x */
		hw = hw + xoff;
		lnl = g->posnodes[i];
		/* scan the nodes at this x pos. */
		while (lnl) {
			/* center the node around the half-way */
			lnl->node->finx = (hw - (lnl->node->bbx / 2));
			if ((lnl->node->finx + lnl->node->bbx) > maxx) {
				maxx = (lnl->node->finx + lnl->node->bbx);
			}

			lnl = lnl->next;
		}

		lnl = g->posnodes[i];
		/* scan the nodes at this x pos. */
		while (lnl) {
			/* center the node around the half-way */
			lnl->node->lx0 = xoff;
			lnl->node->lx1 = xoff + g->wpos[i];
			lnl = lnl->next;
		}

		/* x spacing between the hor. levels */
		xoff = xoff + xspacing;
		/* x to next pos. */
		xoff = xoff + g->wpos[i];
	}

	clear_posnodes_r(maingraph);

	/* y positioning */
	make_levelnodes(maingraph);

	maxy = 0;
	yoff = 0;

	/* number of edges between level n and n+1 */
	g->nume = (int *)dp_calloc(1, (maingraph->maxlevel + 1) * sizeof(int));

	/* scan vert. to adjust the y positions. */
	for (i = 0; i < (maingraph->maxlevel + 1); i++) {
		/* y spacing between the vert. levels */
		yoff = yoff + (yspacing / 1);
		/* determine half-way of the ypos. */
		if (g->hpos[i] == 0) {
			/* if only dummy nodes */
			hw = (yspacing / 2);
		} else {
			hw = (g->hpos[i] / 2);
		}

		/* update with current y */
		hw = hw + yoff;
		lnl = g->levelnodes[i];
		ecount = 0;
		/* scan the nodes at this y pos. */
		while (lnl) {
			/* set start, end of y level */
			lnl->node->ly0 = yoff;
			lnl->node->ly1 = (yoff + g->hpos[i]);
			/* center the node around the half-way */
			lnl->node->finy = (hw - (lnl->node->bby / 2));
			/* update drawing max y pos used */
			if ((lnl->node->finy + lnl->node->bby) > maxy) {
				maxy = (lnl->node->finy + lnl->node->bby);
			}

			/* give dummy nodes a vertical size of the level */
			if (lnl->node->dummy) {
				lnl->node->bby = g->hpos[i];
				/* if only dummy nodes at level, use spacing */
				if (g->hpos[i] == 0) {
					lnl->node->bby = yspacing;
				}
			}

			/* number of edges between level n and n+1 */
			ecount = (ecount + lnl->node->outdegree);
			lnl = lnl->next;
		}

		/* number of edges between level n and n+1 */
		g->nume[i] = ecount;

		/* y spacing between the vert. levels */
		yoff = yoff + (yspacing / 1);

		/* yspacing depends on number of edges at this level
		 * turned off because this add too much y-spacing
		 * yoff = yoff + (ecount * 3);
		 */
		/* yspacing depends on number of crossing edges at this level
		 * this has increasing y effect between levels
		 */
		if (g->numce) {
			yoff = yoff + (1 * (g->numce[i] / 8));
		}

		/* y to next pos. */
		yoff = yoff + g->hpos[i];
	}

	clear_levelnodes_r(maingraph);

	/* clear number of edges between level n and n+1 */
	clear_nume_r(maingraph);

	return;
}

/* do final y of nodes/edges for mode 1 */
static void finaly1(struct gml_graph *g)
{
	struct gml_nlist *lnl = NULL;
	int hw = 0;
	int xoff = 0;
	int yoff = 0;
	int i = 0;
	int ecount = 0;

	/* used for pos2 and do not change the x pos */
	if (0) {

		/* x positioning */
		make_posnodes(maingraph);

		maxx = 0;
		xoff = 0;

		/* scan hor. to adjust the x positions. */
		for (i = 0; i < (g->widestnnodes + 1); i++) {
			/* x spacing between the hor. levels */
			xoff = xoff + xspacing;
			/* determine half-way of the xpos. */
			if (g->wpos[i] == 0) {
				/* if only dummy nodes */
				hw = xspacing / 2;
			} else {
				hw = (g->wpos[i] / 2);
			}

			/* update with current x */
			hw = hw + xoff;
			lnl = g->posnodes[i];
			/* scan the nodes at this x pos. */
			while (lnl) {
				/* center the node around the half-way */
				lnl->node->finx = (hw - (lnl->node->bbx / 2));
				if ((lnl->node->finx + lnl->node->bbx) > maxx) {
					maxx = (lnl->node->finx + lnl->node->bbx);
				}

				lnl = lnl->next;
			}

			lnl = g->posnodes[i];
			/* scan the nodes at this x pos. */
			while (lnl) {
				/* center the node around the half-way */
				lnl->node->lx0 = xoff;
				lnl->node->lx1 = xoff + g->wpos[i];
				lnl = lnl->next;
			}

			/* x spacing between the hor. levels */
			xoff = xoff + xspacing;
			/* x to next pos. */
			xoff = xoff + g->wpos[i];
		}

		clear_posnodes_r(maingraph);
	}

	/* y positioning */
	make_levelnodes(maingraph);

	maxy = 0;
	yoff = 0;

	/* number of edges between level n and n+1 */
	g->nume = (int *)dp_calloc(1, (maingraph->maxlevel + 1) * sizeof(int));

	/* scan vert. to adjust the y positions. */
	for (i = 0; i < (maingraph->maxlevel + 1); i++) {
		/* y spacing between the vert. levels */
		yoff = yoff + (yspacing / 1);
		/* determine half-way of the ypos. */
		if (g->hpos[i] == 0) {
			/* if only dummy nodes */
			hw = (yspacing / 2);
		} else {
			hw = (g->hpos[i] / 2);
		}

		/* update with current y */
		hw = hw + yoff;
		lnl = g->levelnodes[i];
		ecount = 0;
		/* scan the nodes at this y pos. */
		while (lnl) {
			/* set start, end of y level */
			lnl->node->ly0 = yoff;
			lnl->node->ly1 = (yoff + g->hpos[i]);
			/* center the node around the half-way */
			lnl->node->finy = (hw - (lnl->node->bby / 2));
			/* update drawing max y pos used */
			if ((lnl->node->finy + lnl->node->bby) > maxy) {
				maxy = (lnl->node->finy + lnl->node->bby);
			}

			/* give dummy nodes a vertical size of the level */
			if (lnl->node->dummy) {
				lnl->node->bby = g->hpos[i];
				/* if only dummy nodes at level, use spacing */
				if (g->hpos[i] == 0) {
					lnl->node->bby = yspacing;
				}
			}

			/* number of edges between level n and n+1 */
			ecount = (ecount + lnl->node->outdegree);
			lnl = lnl->next;
		}

		/* number of edges between level n and n+1 */
		g->nume[i] = ecount;

		/* y spacing between the vert. levels */
		yoff = yoff + (yspacing / 1);

		/* yspacing depends on number of edges at this level
		 * turned off because this add too much y-spacing
		 * yoff = yoff + (ecount * 3);
		 */
		/* yspacing depends on number of crossing edges at this level
		 * this has increasing y effect between levels
		 */
		if (g->numce) {
			yoff = yoff + (1 * (g->numce[i] / 8));
		}

		/* y to next pos. */
		yoff = yoff + g->hpos[i];
	}

	clear_levelnodes_r(maingraph);

	/* clear number of edges between level n and n+1 */
	clear_nume_r(maingraph);

	return;
}

/* for pos2.c which does set finx,finy */
static void finalxy2(struct gml_graph *g)
{
	struct gml_nlist *lnl = NULL;
	int my = 0;

	maxx = 0;
	maxy = 0;

	/* adjust for the y size of single nodes */
	if (g->nsinglenodes) {
		my = 0;
		lnl = maingraph->singlenodelist;
		while (lnl) {

			if (lnl->node->bby > my) {
				my = lnl->node->bby;
			}
			lnl = lnl->next;
		}
		/* update level data for single nodes */
		lnl = maingraph->singlenodelist;
		while (lnl) {
			lnl->node->ly0 = 0;
			lnl->node->ly1 = my;
			lnl = lnl->next;
		}

	} else {
		/* no singlenodes, start at top of drawing */
		my = 0;
	}

	/* determine max. x pos in use */
	lnl = maingraph->nodelist;
	while (lnl) {

		/* adjust the non-singlenodes down */
		if (lnl->node->indegree || lnl->node->outdegree) {
			lnl->node->finy = lnl->node->finy + my;
			lnl->node->ly0 = lnl->node->ly0 + my;
			lnl->node->ly1 = lnl->node->ly1 + my;
		}

		if ((lnl->node->finx + lnl->node->bbx) > maxx) {
			maxx = lnl->node->finx + lnl->node->bbx;
		}

		/* update drawing max y pos used */
		if ((lnl->node->finy + lnl->node->bby) > maxy) {
			maxy = (lnl->node->finy + lnl->node->bby);
		}

		lnl = lnl->next;
	}

	return;
}

/* for pos.c which does set absx,absy */
static void finalxy3(struct gml_graph *g)
{
	struct gml_nlist *lnl = NULL;

	/* recalc drawing size */
	maxx = 0;
	maxy = 0;

	if (g) {
	}

	/* determine max. x pos in use */
	lnl = maingraph->nodelist;
	while (lnl) {
		/* copy abs to fin */
		lnl->node->finx = lnl->node->absx;
		lnl->node->finy = lnl->node->absy;

		if ((lnl->node->finx + lnl->node->bbx) > maxx) {
			maxx = lnl->node->finx + lnl->node->bbx;
		}

		/* update drawing max y pos used */
		if ((lnl->node->finy + lnl->node->bby) > maxy) {
			maxy = (lnl->node->finy + lnl->node->bby);
		}

		lnl = lnl->next;
	}

	return;
}

static void finalxy(struct gml_graph *g)
{
	struct gml_nlist *lnl = NULL;
	int xpos = 0;
	int my = 0;

	/* depends on positioning modus */

	/* if set use priority algorithm for placement otherwise brandes and kopf */
	if (option_priority) {

	}

	switch (postype) {
	case 1:
		finalxy1(g);
		break;
	case 2:
		/* this extra fixes problem with y setting sometines */
		finaly1(g);
		finalxy2(g);
		break;
	case 3:
		finalxy3(g);
		break;
	default:
		finalxy1(g);
		break;
	}

	/* position level 0, single nodes if any */
	if (g->nsinglenodes) {
		my = 0;
		xpos = xspacing;
		lnl = g->singlenodelist;
		while (lnl) {
			lnl->node->finx = xpos;
			lnl->node->finy = 0;
			/* position single nodes at level 0, just next to each other */
			xpos = xpos + lnl->node->bbx + xspacing;
			if (lnl->node->bby > my) {
				my = lnl->node->bby;
			}
			if (xpos > maxx) {
				maxx = xpos;
			}
			lnl = lnl->next;
		}
	}

	return;
}

/* XPM */
static const char *data_visualization_1_xpm[] = {
	"50 50 119 2",
	"  	c #FFFFFF",
	". 	c #ECECEC",
	"+ 	c #B1B1B1",
	"@ 	c #808080",
	"# 	c #6C6C6C",
	"$ 	c #898989",
	"% 	c #C0C0C0",
	"& 	c #F6F6F6",
	"* 	c #BBBBBB",
	"= 	c #1C1C1C",
	"- 	c #000000",
	"; 	c #474747",
	"> 	c #DADADA",
	", 	c #222222",
	"' 	c #DFDFDF",
	") 	c #606060",
	"! 	c #C7C7C7",
	"~ 	c #B9B9B9",
	"{ 	c #383838",
	"] 	c #666666",
	"^ 	c #FCFCFC",
	"/ 	c #F7F7F7",
	"( 	c #E5E5E5",
	"_ 	c #D9D9D9",
	": 	c #F1F1F1",
	"< 	c #E4E4E4",
	"[ 	c #F2F2F2",
	"} 	c #7F7F7F",
	"| 	c #989898",
	"1 	c #B6B6B6",
	"2 	c #E9E9E9",
	"3 	c #7E7E7E",
	"4 	c #767676",
	"5 	c #E3E3E3",
	"6 	c #6D6D6D",
	"7 	c #B2B2B2",
	"8 	c #ACACAC",
	"9 	c #EBEBEB",
	"0 	c #3D3D3D",
	"a 	c #2E2E2E",
	"b 	c #848484",
	"c 	c #C2C2C2",
	"d 	c #979797",
	"e 	c #787878",
	"f 	c #BFBFBF",
	"g 	c #C6C6C6",
	"h 	c #EAEAEA",
	"i 	c #F9F9F9",
	"j 	c #161616",
	"k 	c #838383",
	"l 	c #5F5F5F",
	"m 	c #FDFDFD",
	"n 	c #EFEFEF",
	"o 	c #F8F8F8",
	"p 	c #828282",
	"q 	c #ADADAD",
	"r 	c #424242",
	"s 	c #9A9A9A",
	"t 	c #CECECE",
	"u 	c #9F9F9F",
	"v 	c #818181",
	"w 	c #FAFAFA",
	"x 	c #F0F0F0",
	"y 	c #868686",
	"z 	c #535353",
	"A 	c #555555",
	"B 	c #939393",
	"C 	c #AEAEAE",
	"D 	c #D1D1D1",
	"E 	c #878787",
	"F 	c #777777",
	"G 	c #404040",
	"H 	c #CFCFCF",
	"I 	c #A0A0A0",
	"J 	c #A1A1A1",
	"K 	c #3B3B3B",
	"L 	c #D0D0D0",
	"M 	c #757575",
	"N 	c #565656",
	"O 	c #585858",
	"P 	c #5A5A5A",
	"Q 	c #FBFBFB",
	"R 	c #D8D8D8",
	"S 	c #B4B4B4",
	"T 	c #C1C1C1",
	"U 	c #DEDEDE",
	"V 	c #636363",
	"W 	c #DBDBDB",
	"X 	c #999999",
	"Y 	c #858585",
	"Z 	c #A7A7A7",
	"` 	c #494949",
	" .	c #8C8C8C",
	"..	c #8E8E8E",
	"+.	c #C8C8C8",
	"@.	c #8A8A8A",
	"#.	c #FEFEFE",
	"$.	c #B8B8B8",
	"%.	c #ABABAB",
	"&.	c #B5B5B5",
	"*.	c #C5C5C5",
	"=.	c #9D9D9D",
	"-.	c #5D5D5D",
	";.	c #B7B7B7",
	">.	c #353535",
	",.	c #BEBEBE",
	"'.	c #656565",
	").	c #EDEDED",
	"!.	c #BCBCBC",
	"~.	c #262626",
	"{.	c #E0E0E0",
	"].	c #F3F3F3",
	"^.	c #454545",
	"/.	c #BDBDBD",
	"(.	c #4B4B4B",
	"_.	c #DDDDDD",
	":.	c #323232",
	"<.	c #6E6E6E",
	"[.	c #A8A8A8",
	"                                                                                                    ",
	"                                                                                                    ",
	"                                                                                                    ",
	"            . + @ # $ % &                                                                           ",
	"          * = - - - - - ; >                                                                         ",
	"        * - - - - - - - - , '                                                                       ",
	"      . = - - ) ! > ~ { - - ] ^                                                                     ",
	"      + - - ) /       ( , - - _                                         : < [                       ",
	"      } - - !           | - - 1                                     2 3 - - - 4 5                   ",
	"      6 - - >           7 - - 8                                   9 0 - - - - - a 5                 ",
	"      $ - - ~           b - - c                                   d - - - - - - - e                 ",
	"      f - - { (       g - - - h                                 i j - - - - - - - - [               ",
	"      & ; - - , | 7 k - - - l m                                 n - - - - - - - - - (               ",
	"        > , - - - - - - - - - | ^                               o = - - - - - - - - [               ",
	"          ' ] - - - - - l - - - | ^                             ^ ] - - - - - - - p                 ",
	"            ^ _ 1 q c h m | - - - | ^                         ^ d - - - - - - - r 2                 ",
	"                          ^ | - - - | ^                     ^ d - - - ] = - j s .                   ",
	"                            ^ | - - - d ^ i t u v v u t w ^ d - - - d ^ i x w                       ",
	"                              ^ | - - - y z - - - - - - A y - - - d ^                               ",
	"                                m | - - - - - - - - - - - - - - B ^                                 ",
	"                                  ^ y - - - 0 C D D q 0 - - - E ^                                   ",
	"                                  w z - - F [         [ 4 - - A w                                   ",
	"                                  t - - G [             [ 0 - - H                                   ",
	"                                  u - - C                 q - - I                                   ",
	"                                  v - - D                 D - - p                                   ",
	"                                  v - - D                 D - - p                                   ",
	"                                  u - - q                 8 - - J                                   ",
	"                                  t - - 0 [             : K - - L                                   ",
	"                                  w A - - 4 [         : M - - N w                                   ",
	"                                  ^ E - - - 0 q D D 8 K - - - E ^                                   ",
	"                                m | - - - - - - - - - - - - - - B ^                                 ",
	"                              ^ | - - - y O - - - - - - P y - - - | ^                               ",
	"                            ^ | - - - d ^ Q D 4 - - 4 D Q ^ d - - - | ^                             ",
	"                          m | - - - B ^       + - - +       m | - - - B ^                           ",
	"            ^ R S q T 2 m | - - - | ^         + - - +         ^ | - - - | m 2 T q S R ^             ",
	"          U V - - - - - l - - - | ^           + - - +           ^ | - - - l - - - - - V '           ",
	"        > , - - - - - - - - - | ^             + - - +             ^ | - - - - - - - - - , W         ",
	"      & ; - - , X 7 Y - - - l m               Z - - Z               m l - - - Y 7 X , - - ` /       ",
	"      f - - { (       ! - - - 2           /  .- - - - ../           2 - - - +.      ( { - - %       ",
	"      $ - - ~           b - - c         m @.- - - - - -  .#.        T - - Y           $.- - @.      ",
	"      6 - - >           7 - - 8         > - - - - - - - - W         %.- - 7           _ - - 6       ",
	"      } - - !           d - - 1         Z - - - - - - - - q         &.- - s           *.- - v       ",
	"      7 - - ) /       < = - - >         =.- - - - - - - - Z         R - - , (       & -.- - 7       ",
	"      . = - - l g _ ;.>.- - ] ^         ,.- - - - - - - - ,.        ^ '.- - { ~ _ *.-.- - , ).      ",
	"        !.- - - - - - - - ~.{.          ].^.- - - - - - ^.].          ' , - - - - - - - - ,.        ",
	"          /., - - - - - (.W               _.:.- - - - >._.              W ` - - - - - , ,.          ",
	"            ).7 v # @.% /                   x Z <.<.[.x                   / % @.# p 7 ).            ",
	"                                                                                                    ",
	"                                                                                                    ",
	"                                                                                                    "
};

/* show about with ok button */
static void show_about(GtkWidget * widget, gpointer data)
{
	GtkWidget *dialog = NULL;
	GdkPixbuf *xpmdata = NULL;
	int buflen = 0;
	char *buf = NULL;
	char *pbuf = NULL;
	char *text0 = "This is a GML (Graph-Markup_Language) graph viewer program.\n"
	    "This program is free to share, copy, use, modify or fork.\n"
	    "This program does not have network telemetry or creates files.\n"
	    "See gml4gtk at sourceforge.net\nemail: mooigraph AT gmail.com\n";
#ifdef WIN32
	char *text1 = "Product key: GML4-GTKVE-RSION-74YEA-R2021";
#else
	char *text1 = "Product Key: GNU-GPL";
#endif

	if (widget) {
	}
	if (data) {
	}

	buflen = 512;

	buf = dp_calloc(1, buflen);

	buflen--;

	dialog = gtk_about_dialog_new();
#if GTK_HAVE_API_VERSION_2 == 1
	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), PACKAGE_NAME);
#endif
#if GTK_HAVE_API_VERSION_3 == 1
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), PACKAGE_NAME);
#endif

	/* todo it seems this is depreciated. */
	xpmdata = gdk_pixbuf_new_from_xpm_data(data_visualization_1_xpm);

	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), xpmdata);

	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), PACKAGE_VERSION);
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "Copyright is GNU GPL Version 3+, see http://www.gnu.org/");
	snprintf(buf, (buflen), "%sCompiled on %s\n", text0, COMPILE_DATE);
	pbuf = buf + (int)(strlen(buf));
	/* */
	snprintf(pbuf, (buflen - (int)(strlen(buf))), "%s\n", text1);
	pbuf = buf + (int)(strlen(buf));
	snprintf(pbuf, (buflen - (int)(strlen(buf))), "compiled with gtk %d.%d.%d glib %d.%d.%d pango %s cairo %s\n",
		 GTK_MAJOR_VERSION, GTK_MINOR_VERSION, GTK_MICRO_VERSION,
		 GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION, PANGO_VERSION_STRING, CAIRO_VERSION_STRING);
	pbuf = buf + (int)(strlen(buf));
	/* */
	snprintf(pbuf, (buflen - (int)(strlen(buf))), "running with gtk %d.%d.%d glib %d.%d.%d pango %s cairo %s\n",
		 gtk_major_version, gtk_minor_version, gtk_micro_version,
		 glib_major_version, glib_minor_version, glib_micro_version, pango_version_string(), cairo_version_string());

	pbuf = buf + (int)(strlen(buf));
	snprintf(pbuf, (buflen - (int)(strlen(buf))), "running with zlib version %s\n", zlibVersion());

	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), buf);
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(dialog), PACKAGE_URL);

	/* suppress warning */
	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(mainwindow1));
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	dp_free(buf);
	return;
}

/* end */
