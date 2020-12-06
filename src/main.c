
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

#ifndef M_PI
#define M_PI 3.141592
#endif

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <cairo.h>
#include <cairo-svg.h>

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
#define DEFAULT_FONTNAME "Sans"

/* name of slant to use, example "Italic", "Oblique" or "Roman" */
#define DEFAULT_FONTSLANT " "

/* name of weight to use, example "Bold", "Book", "Light", "Medium", "Semi-bold", "Ultra-light" */
#define DEFAULT_FONTWEIGHT " "

/* name of condensed to use, example "Semi-Condensed", "Condensed" */
#define DEFAULT_FONTCONDENSED " "

/* font size to use, example "10", "18", "20" etc. */
#define DEFAULT_FONTSIZE "14"

#endif
#endif

/* Linux defaults */

/* name of font to use, example "Sans" */
#define DEFAULT_FONTNAME "Sans"

/* name of slant to use, example "Italic", "Oblique" or "Roman" */
#define DEFAULT_FONTSLANT "ROMAN"

/* name of weight to use, example "Bold", "Book", "Light", "Medium", "Semi-bold", "Ultra-light" */
#define DEFAULT_FONTWEIGHT "Light"

/* name of condensed to use, example "Semi-Condensed", "Condensed" */
#define DEFAULT_FONTCONDENSED "Condensed"

/* font size to use, example "10", "18", "20" etc. */
#define DEFAULT_FONTSIZE "12"

/* edge line thickness double value for example 0.5, 1.0, 1.5 */
#define DEFAULT_EDGE_THICKNESS 1.0

/* pixels in padding for gtk_box_pack try values 0, 1, 5, 20 */
#define PACKPADDING 0

/* window initial (x,y) size in pixels */
#define TOP_LEVEL_WINDOW_XSIZE 700
#define TOP_LEVEL_WINDOW_YSIZE 600

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

/* status line gtk buffers */
static GtkTextBuffer *entry1buffer = NULL;
static char charentry1buffer[80];

/* old mouse (x,y) left button clicked used for dragging drawing */
static int mouse_oldx = 0;
static int mouse_oldy = 0;

/* if set, draw dummy nodes */
static int drawdummy = 0;

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
static void on_top_level_window_svg1_activate(GtkMenuItem * menuitem, gpointer user_data);
static void on_top_level_window_dia1_activate(GtkMenuItem * menuitem, gpointer user_data);
static void on_top_level_window_quit1_activate(GtkMenuItem * menuitem, gpointer user_data);
static void pos1_clicked(GtkWidget * widget, gpointer window);
static void xspin_changed(GtkWidget * widget, gpointer spinbutton);
static void yspin_changed(GtkWidget * widget, gpointer spinbutton);
static void check1_toggle(GtkWidget * widget, gpointer window);
static void dummy1_toggle(GtkWidget * widget, gpointer window);
static void topo1_toggle(GtkWidget * widget, gpointer window);
static void bary1_toggle(GtkWidget * widget, gpointer window);
static void elabel1_toggle(GtkWidget * widget, gpointer window);

static void on_top_level_window_drawingarea1_expose_event_edges(cairo_t * crp);

static void on_top_level_window_drawingarea1_expose_event_nodes_record_r(cairo_t * crp, struct gml_node
									 *node, struct gml_rl
									 *info);

static void on_top_level_window_drawingarea1_expose_event_nodes_record(cairo_t * crp, struct gml_node
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

/* fit drawing in window */
static void dofit(void);

static void do_layout_all(struct gml_graph *g);
static void do_relayout_all(struct gml_graph *g);

static void finalxy(struct gml_graph *g);

static struct gml_p static_maingtk_textsizes1sz(struct gml_rl *info);

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
	GtkWidget *vbox1;
	GtkWidget *menubar1;
	GtkWidget *menuitem1;
	GtkWidget *menuitem1_menu;
	GtkWidget *open1;	/* open gml file */
	GtkWidget *open2;	/* open dot file */
	GtkWidget *open3;	/* open vcg file */
	GtkWidget *svg1;
	GtkWidget *dia1;
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
	GtkWidget *check1;
	GtkWidget *dummy1;
	GtkWidget *topo1;
	GtkWidget *entry1;
	GtkWidget *bary1;
	GtkWidget *elabel1;

	argv0 = argv[0];

	/* get the home dir */
	s = getenv("HOME");
	if (s) {
		lastopendir = calloc(1, (strlen(s) + 1));
		if (lastopendir) {
			strcpy(lastopendir, s);
		}
		lastsavedir = calloc(1, (strlen(s) + 1));
		if (lastsavedir) {
			strcpy(lastsavedir, s);
		}
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

	/* */
	gtk_widget_set_events((drawingarea1), (GDK_BUTTON_PRESS_MASK | GDK_BUTTON1_MOTION_MASK));

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
	pos1 = gtk_button_new_with_label("pos");

	gtk_box_pack_start( /* box */ GTK_BOX(hbox2), /* child */ pos1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	g_signal_connect(G_OBJECT(pos1), "clicked", G_CALLBACK(pos1_clicked), G_OBJECT(mainwindow1));

	gtk_widget_set_tooltip_text(pos1, "toggle layout modus");

	gtk_widget_show(pos1);

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

	/* topological */
	topo1 = gtk_check_button_new_with_label("topo");
	gtk_box_pack_start( /* box */ GTK_BOX(hbox3), /* child */ topo1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	/* */
	if (topological) {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(topo1), TRUE);
	} else {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(topo1), FALSE);
	}

	g_signal_connect(G_OBJECT(topo1), "clicked", G_CALLBACK(topo1_toggle), (gpointer) mainwindow1);
	gtk_widget_set_tooltip_text(topo1, "topological placement");
	gtk_widget_show(topo1);

	/* barycenter */
	bary1 = gtk_check_button_new_with_label("bary");
	gtk_box_pack_start( /* box */ GTK_BOX(hbox3), /* child */ bary1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	/* */
	if (barytype) {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(bary1), TRUE);
	} else {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(bary1), FALSE);
	}

	g_signal_connect(G_OBJECT(bary1), "clicked", G_CALLBACK(bary1_toggle), (gpointer) mainwindow1);
	gtk_widget_set_tooltip_text(bary1, "barycenter type");
	gtk_widget_show(bary1);

	/* edgelabels on/off */
	elabel1 = gtk_check_button_new_with_label("elabel");
	gtk_box_pack_start( /* box */ GTK_BOX(hbox3), /* child */ elabel1,
			   /* expand */ FALSE, /* fill */ FALSE,	/* padding */
			   PACKPADDING);

	/* */
	if (edgelabelsonoff) {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(elabel1), TRUE);
	} else {
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(elabel1), FALSE);
	}

	g_signal_connect(G_OBJECT(elabel1), "clicked", G_CALLBACK(elabel1_toggle), (gpointer) mainwindow1);
	gtk_widget_set_tooltip_text(elabel1, "edgelabels on/off");
	gtk_widget_show(elabel1);

	/*
	 * here additional gtk elements
	 */

	/* put on screen */
	gtk_widget_show(mainwindow1);

	/* check for optinal gml file on commandline */
	if (argc > 1) {
		fnam = argv[1];
		if ((*fnam) != '-') {
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
					f = fopen(fnam, "r");
					if (f) {
						/* create root graph */
						create_maingraph();

						/* parse the gml data */
						if (gmlparse(maingraph, f, fnam)) {
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
					/* end of gml file at start */
				}

			}
		}
	}

	/* run the gui */
	gtk_main();

	do_clear_all(0);

	return (0);
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
	GdkModifierType state;

	/* check if there is node data to draw */
	if (validdata == 0) {
		return (TRUE);
	}

	if (event) {
		/* */
	}

	/* where mouse click is on window and mouse status */
#if GTK_HAVE_API_VERSION_2 == 1
	gdk_window_get_pointer(widget->window, &x, &y, &state);
#endif
#if GTK_HAVE_API_VERSION_3 == 1
	gdk_window_get_device_position(gtk_widget_get_window(widget), event->device, &x, &y, &state);
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
			gsld = gdelta;
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
			gsld = gdelta;
			gsld = gdelta / maxy;
			gsld = gsld * 100;
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

	return (TRUE);
}

/* mouse click on drawing area
 *
 * guint event->type has this info
 * enum GdkEventType
 * {
 * .
 * GDK_BUTTON_PRESS	= 4, (single click)
 * GDK_2BUTTON_PRESS	= 5, (double click)
 * GDK_3BUTTON_PRESS	= 6, (triple click)
 * GDK_BUTTON_RELEASE	= 7, (released)
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

	/* use position 1 */
	posmode = 1;
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

		/* clear optional record label of node */
		if (mode == 0) {
			clear_rlabel_r(maingraph);
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
			free(maingraph);

			maingraph = NULL;
		}
	}

	return;
}

	/* finally stop the gui */
static void top_level_window_main_quit(void)
{

	do_clear_all(0);

	/* run the gtk internal routine to stop gtk_main() which is a for(){} loop */
	gtk_main_quit();

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
	FILE *f = NULL;
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
			(void)g_free(lastopendir);
		}
		lastopendir = calloc(1, (strlen(file_chooser_dir) + 1));
		if (lastopendir) {
			strcpy(lastopendir, file_chooser_dir);
		}
		(void)g_free(file_chooser_dir);
	}

	/* copy the input filename from gtk */
	if (file_chooser_filename) {
		inputfilename = calloc(1, (strlen(file_chooser_filename) + 1));
		if (inputfilename) {
			strcpy(inputfilename, file_chooser_filename);
		}
		(void)g_free(file_chooser_filename);
	} else {
		return;
	}

	/* set filename in window */
	bname = g_path_get_basename(inputfilename);
	baseinputfilename2 = calloc(1, (strlen(bname) + 1));
	if (baseinputfilename2) {
		strcpy(baseinputfilename2, bname);
	}
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
		free(inputfilename);
		free(baseinputfilename2);
		/* data is unchanged, so keep validdata status */
		return;
	}

	do_clear_all(0);

	/* background r/g/b of drawing */
	bgcr = 0xff;
	bgcg = 0xff;
	bgcb = 0xff;

	/* create root graph */
	create_maingraph();

	/* parse the gml data */
	if (gmlparse(maingraph, f, baseinputfilename2)) {
		/* parse error */
		if (strlen(parsermessage) == 0) {
			strcpy(parsermessage, "no parser message");
		}
		pdialog = gtk_message_dialog_new(GTK_WINDOW(mainwindow1),
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", parsermessage);
		gtk_dialog_run(GTK_DIALOG(pdialog));
		gtk_widget_destroy(pdialog);
		free(inputfilename);
		free(baseinputfilename2);
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
		(void)g_free(inputfilename);
		free(baseinputfilename2);

		/* fit drawing in window */
		dofit();

		validdata = 1;
	} else {
		/* filename is not saved */
		(void)g_free(inputfilename);
		free(baseinputfilename2);
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
			(void)g_free(lastopendir);
		}
		lastopendir = calloc(1, (strlen(file_chooser_dir) + 1));
		if (lastopendir) {
			strcpy(lastopendir, file_chooser_dir);
		}
		(void)g_free(file_chooser_dir);
	}

	/* copy the input filename from gtk */
	if (file_chooser_filename) {
		inputfilename = calloc(1, (strlen(file_chooser_filename) + 1));
		if (inputfilename) {
			strcpy(inputfilename, file_chooser_filename);
		}
		(void)g_free(file_chooser_filename);
	} else {
		return;
	}

	/* set filename in window */
	bname = g_path_get_basename(inputfilename);
	baseinputfilename2 = calloc(1, (strlen(bname) + 1));;
	if (baseinputfilename2) {
		strcpy(baseinputfilename2, bname);
	}
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
		free(inputfilename);
		free(baseinputfilename2);
		/* data is unchanged, so keep validdata status */
		return;
	}

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
		free(inputfilename);
		free(baseinputfilename2);
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
		(void)g_free(inputfilename);
		free(baseinputfilename2);

		/* fit drawing in window */
		dofit();

		validdata = 1;
	} else {
		/* filename is not saved */
		(void)g_free(inputfilename);
		free(baseinputfilename2);
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
			(void)g_free(lastopendir);
		}
		lastopendir = calloc(1, (strlen(file_chooser_dir) + 1));
		if (lastopendir) {
			strcpy(lastopendir, file_chooser_dir);
		}
		(void)g_free(file_chooser_dir);
	}

	/* copy the input filename from gtk */
	if (file_chooser_filename) {
		inputfilename = calloc(1, (strlen(file_chooser_filename) + 1));
		if (inputfilename) {
			strcpy(inputfilename, file_chooser_filename);
		}
		(void)g_free(file_chooser_filename);
	} else {
		return;
	}

	/* set filename in window */
	bname = g_path_get_basename(inputfilename);
	baseinputfilename2 = calloc(1, (strlen(bname) + 1));;
	if (baseinputfilename2) {
		strcpy(baseinputfilename2, bname);
	}
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
		free(inputfilename);
		free(baseinputfilename2);
		/* data is unchanged, so keep validdata status */
		return;
	}

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
		free(inputfilename);
		free(baseinputfilename2);
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
		(void)g_free(inputfilename);
		free(baseinputfilename2);

		/* fit drawing in window */
		dofit();

		validdata = 1;
	} else {
		/* filename is not saved */
		(void)g_free(inputfilename);
		free(baseinputfilename2);
		/* update status text */
		update_status_text("Empty graph ... No Nodes");
		validdata = 0;
	}

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
		lastsavedir = gtk_file_chooser_get_current_folder(chooser);
	} else {
		/* cancel button */
		(void)gtk_widget_destroy(dialog);
		return;
	}

	/* */
	(void)gtk_widget_destroy(dialog);

	/* */
	if (file_chooser_filename) {
		svgfilename = calloc(1, (strlen(file_chooser_filename) + 1));
		if (svgfilename) {
			strcpy(svgfilename, file_chooser_filename);
		}
		/* */
		(void)g_free(file_chooser_filename);
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
		free(svgfilename);
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
	free(svgfilename);

	return;
}

/* save as dia xml diagram */
static void on_top_level_window_dia1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkWidget *dialog = (GtkWidget *) 0;
	GtkWidget *edialog = (GtkWidget *) 0;
	char *file_chooser_filename = (char *)0;
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
		lastsavedir = gtk_file_chooser_get_current_folder(chooser);
	} else {
		/* cancel button */
		(void)gtk_widget_destroy(dialog);
		return;
	}

	/* */
	(void)gtk_widget_destroy(dialog);

	/* */
	if (file_chooser_filename) {
		diafilename = calloc(1, (strlen(file_chooser_filename) + 1));
		if (diafilename) {
			strcpy(diafilename, file_chooser_filename);
		}
		/* */
		(void)g_free(file_chooser_filename);
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
		free(diafilename);
		return;
	}

	/* write the dia diagram */
	graph2dia(maingraph, fstream);

	fclose(fstream);
	free(diafilename);

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
					/* black selfedge */
					r = 0;
					g = 0;
					b = 0;
					/* draw in black */
					cairo_set_source_rgb(crp, r / 255.0, g / 255.0, b / 255.0);
					/* draw the self-edge, start at 1/4 circle */
					cairo_arc(crp, x0, y0 + nl->node->bby, 6 /* radius */ ,
						  45 * (180 * M_PI), 2 * M_PI);
					/* opt. arrow, which is too big here */
					if (1) {
						drarrow(crp, x0 - 10, y0 + nl->node->bby - 6, x0, y0 + nl->node->bby - 6, 3);
					}
					cairo_stroke(crp);
				}
			}

			/* fillcolor of node white default or color */
			r = (nl->node->ncolor & 0x00ff0000) >> 16;
			g = (nl->node->ncolor & 0x0000ff00) >> 8;
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

			/* calculate the scaled font size */
			dfs = (zfactor * atoi(default_fontsize));

			/* somewhat rounded version */
			fs = (int)dfs;

			/* too small to draw readable text then skip the following text drawing area */
			if (fs < 4) {
				nl = nl->next;
				continue;
			}

			/* draw regular text in node, or record label */
			if (nl->node->rlabel == NULL) {

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
			} else {
				/* draw record label */
				on_top_level_window_drawingarea1_expose_event_nodes_record(crp, nl->node);
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
		if (option_gdebug > 1 || 1) {
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

/* pos 1 is button when clicked, advance positioning mode */
static void pos1_clicked(GtkWidget * widget, gpointer window)
{
	if (widget) {
	}
	if (window) {
	}
	/* check if there is node data to draw */
	if (validdata == 0) {
		return;
	}

	/* advance pos. mode, cycle from 1,2,3 to 1 */
	posmode++;

	if (posmode > 3) {
		posmode = 1;
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

/* checkbox 3 is use topological placement */
static void topo1_toggle(GtkWidget * widget, gpointer window)
{
	if (widget) {
	}
	if (window) {
	}
	/* toggle the splines option */
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		topological = 1;
	} else {
		topological = 0;
	}
	/* nop if no data */
	if (validdata == 0) {
		return;
	}

	/* re-layout */
	do_relayout_all(maingraph);

	/* now a re-draw needed */
	gtk_widget_queue_draw(drawingarea1);
	return;
}

/* checkbox 4 is switch barycenter placement */
static void bary1_toggle(GtkWidget * widget, gpointer window)
{
	if (widget) {
	}
	if (window) {
	}
	/* toggle the splines option */
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		barytype = 1;
	} else {
		barytype = 0;
	}
	/* nop if no data */
	if (validdata == 0) {
		return;
	}

	/* re-layout */
	do_relayout_all(maingraph);

	/* now a re-draw needed */
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
	/* toggle the splines option */
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		edgelabelsonoff = 1;
	} else {
		edgelabelsonoff = 0;
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
static struct gml_p static_maingtk_textsizes1sz(struct gml_rl *info)
{
	struct gml_p d;
	struct gml_p dsub;
	int i = 0;

	d.x = 0;
	d.y = 0;

	if (info == NULL) {
		return (d);
	}

	if (info->hd) {
		d.x = info->txsize;
		d.y = info->tysize;
	} else {
		for (i = 0; i < info->nparts; i++) {
			dsub = static_maingtk_textsizes1sz(info->parts[i]);
			if (info->dir == 0) {
				d.x = d.x + dsub.x;
				if (dsub.y > d.y) {
					d.y = dsub.y;
				}
			} else {
				if (dsub.x > d.x) {
					d.x = dsub.x;
				}
				d.y = d.y + dsub.y;
			}
		}
	}

	info->bbx = d.x;
	info->bby = d.y;

	if (yydebug || 0) {
		printf
		    ("%s(): hd=%d dir=%d bb(x,y) size is (%d,%d) t(x,x) is (%d,%d) for `%s'\n",
		     __func__, info->hd, info->dir, info->bbx, info->bby, info->txsize, info->tysize, info->ulabel);
	}

	return (d);
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
		/* zzz  */
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
				tmpb = (char *)calloc(1, (len + 1));
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
				free(tmpb);
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

				if (yydebug) {
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
		ibbx = bbx;
		ibby = bby;
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
	struct gml_p d;

	/* calc (x,y) text size of all parts in record label */
	static_maingtk_textsizes1rl(node->rlabel);

	d = static_maingtk_textsizes1sz(node->rlabel);

	if (yydebug || 0) {
		printf("%s(): d is (%d,%d) versus bbxy(%d,%d)\n", __func__, d.x, d.y, node->bbx, node->bby);
	}

	/* check for use of step of bb */
	static_maingtk_textsizes1eq(node->rlabel);

	/* now position the text parts and result in the rlabel structs */
	node->bbx = d.x;
	node->bby = d.y;

	static_maingtk_textsizes2rl(node->rlabel, 0, 0, 0, node->bbx, node->bby);

	return;
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
			/* node or edgelabel text */
			if (nl->node->nlabel == NULL) {
				/* shouldnothappen */
				nl->node->nlabel = uniqstr("  ");
			}

			/* if the labeltext is "" replace it with " " */
			if (strlen(nl->node->nlabel) == 0) {
				/* to avoid cairo assert */
				nl->node->nlabel = uniqstr("  ");
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
				printf("%s(): size (%d,%d) for \"%s\"\n",
				       __func__, (w / PANGO_SCALE), (h / PANGO_SCALE), nl->node->nlabel);
				fflush(stdout);
			}

			/* set in unode the text area size */
			nl->node->tx = (w / PANGO_SCALE);
			nl->node->ty = (h / PANGO_SCALE);

			/* for a box */
			nl->node->bbx = nl->node->tx + 4;
			nl->node->bby = nl->node->ty + 4;

			/* record node label */
			if ((nl->node->rlabel != NULL) && (nl->node->rlabeldone == 0)) {
				static_maingtk_textsizes1n(nl->node);
				nl->node->rlabeldone = 1;
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
	g->nume = (int *)calloc(1, (maingraph->maxlevel + 1) * sizeof(int));

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
			my = lnl->node->ly0 = 0;
			my = lnl->node->ly1 = my;
			lnl = lnl->next;
		}

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

	switch (posmode) {
	case 1:
		finalxy1(g);
		break;
	case 2:
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

/* show about with ok button */
static void show_about(GtkWidget * widget, gpointer data)
{
	GtkWidget *dialog = NULL;
	if (widget) {
	}
	if (data) {
	}

	dialog = gtk_about_dialog_new();
#if GTK_HAVE_API_VERSION_2 == 1
	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), PACKAGE_NAME);
#endif
#if GTK_HAVE_API_VERSION_3 == 1
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), PACKAGE_NAME);
#endif
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), PACKAGE_VERSION);
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "Copyright is GNU GPL Version 3, see http://www.gnu.org/");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),
				      "This is a GML (Graph-Markup_Language) graph viewer program.\n"
				      "This program is free to share, copy, use, modify or fork.\n"
				      "See gml4gtk at sourceforge.net\nemail: mooigraph AT gmail.com\n");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), PACKAGE_URL);
	/* suppress warning */
	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(mainwindow1));
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	return;
}

/* end */
