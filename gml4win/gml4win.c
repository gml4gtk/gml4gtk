
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

#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <commctrl.h>

#include "main.h"
#include "hier.h"
#include "dpif.h"
#include "pos.h"
#include "gml_scanner.h"
#include "gml_parser.h"
#include "uniqstr.h"
#include "uniqgraph.h"
#include "uniqnode.h"
#include "bubbling.h"
#include "dot.tab.h"

/* version string */
#define HEADLINE L"gml4win version 2.0"

/* icon number defined in gml4win.rc file */
#define IDI_ICON1 101

/* max line length in chars of a single text line in a node label */
#define NODE_MAXCH (1024)

/* font size at 100% scaling */
#define FONTSZ 12		/* vertical size */
#define FONTSZ2 (FONTSZ / 2)	/* horizontal size */
#define FONTNAME L"Sans"
/* #define FONTNAME L"Times New Roman" */

/* startup window x,y size */
#define DEFAULT_WX 750
#define DEFAULT_WY 650

/* codes for file menu */
#define IDM_FILE_OPEN_DOT 1
#define IDM_FILE_OPEN_GML 2
#define IDM_FILE_ABOUT 3
#define IDM_FILE_QUIT 4

/* sliders pos data */

/* hor slider */
#define HSL_X0 (30)
#define HSL_Y0 (wysize-30)
#define HSL_XS (wxsize-30-30)
#define HSL_YS (30)

/* left vertical slider */
#define LSL_X0 (0)
#define LSL_Y0 (0)
#define LSL_XS (30)
#define LSL_YS (wysize-30)

/* right vertical slider */
#define RSL_X0 (wxsize-30)
#define RSL_Y0 (0)
#define RSL_XS (30)
#define RSL_YS (wysize-30)

/* draw area */
#define DRW_X0 (30)
#define DRW_Y0 (0)
#define DRW_XS (wxsize-30-30)
#define DRW_YS (wysize-30)

/* nr. of pixels hor. edge goes downwards */
#define HEDGE_DY 10

/* window (x,y) size */
static int wxsize = 0;
static int wysize = 0;

/* draw window (x,y) size */
static int drwxsize = 0;
static int drwysize = 0;

/* set if there is data to draw */
static int validdata = 0;

/* zoom scaling factor changed by zoom slider */
static double zfactor = 1.0;

/* x offset changed by x slider */
static int vxmin = 0;

/* y offset changed by y slider */
static int vymin = 0;

/* y size in pixels of the font */
static int thefontsize = FONTSZ;

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/* create sliders */
static void createcontrols(HWND hwnd);
static void addmenus(HWND hwnd);
static void center(HWND hwnd);
static void doopen(HWND hwnd, int what);
static void updatesliders(void);
static void drawit(HWND hwnd);
static int scaleit(int pos);

static HWND hTrackvl;
static HWND hTrackvr;
static HWND hTrackhor;
static HWND mainhwnd;
static HWND drw;
static HDC hdc;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASSW wc = { 0 };

	if (hInstance) {
	}
	if (hPrevInstance) {
	}
	if (lpCmdLine) {
	}
	if (nCmdShow) {
	}

	/* default icon defined using rc file */
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));	/* or: IDI_APPLICATION */
	/* force redraw */
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = HEADLINE;
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&wc);

	/* size of startup window */
	wxsize = DEFAULT_WX;
	wysize = DEFAULT_WY;

	/* start background color */
	bgcr = 0xdc;
	bgcg = 0xdc;
	bgcb = 0xdc;

	mainhwnd = CreateWindowW(wc.lpszClassName, HEADLINE,
				 WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, wxsize, wysize, 0, 0, hInstance, 0);

	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	RECT r;

	switch (msg) {

	case WM_CREATE:
		center(hwnd);
		createcontrols(hwnd);
		addmenus(hwnd);
		break;

	case WM_HSCROLL:
		updatesliders();
		break;

	case WM_VSCROLL:
		updatesliders();
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		drawit(hwnd);
		break;

		/* window moved */
	case WM_MOVE:
		drawit(hwnd);
		break;

	case WM_SIZE:
		GetClientRect(hwnd, &r);
		wxsize = (int)r.right - (int)r.left;
		wysize = (int)r.bottom - (int)r.top;
		SetWindowPos(hTrackhor, NULL, HSL_X0, HSL_Y0, HSL_XS, HSL_YS, SWP_NOZORDER);
		SetWindowPos(hTrackvl, NULL, LSL_X0, LSL_Y0, LSL_XS, LSL_YS, SWP_NOZORDER);
		SetWindowPos(hTrackvr, NULL, RSL_X0, RSL_Y0, RSL_XS, RSL_YS, SWP_NOZORDER);
		SetWindowPos(drw, NULL, DRW_X0, DRW_Y0, DRW_XS, DRW_YS, SWP_NOZORDER);
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam)) {
		case IDM_FILE_OPEN_DOT:
			doopen(hwnd, 0);
			break;
		case IDM_FILE_OPEN_GML:
			doopen(hwnd, 1);
			break;
		case IDM_FILE_ABOUT:
			MessageBoxW(NULL,
				    L"gml4win is GNU GPL Free Software to copy, share or improve at https://gml4gtk.sourceforge.io",
				    L"About gml4win", MB_OK);
			break;
		case IDM_FILE_QUIT:
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		default:
			break;
		}
		break;

	case WM_NOTIFY:
		drawit(hwnd);
		break;

	default:
		break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

/* center window on screen */
static void center(HWND hwnd)
{
	RECT rc = { 0 };
	int win_w = 0;
	int win_h = 0;
	int screen_w = 0;

	int screen_h = 0;
	GetWindowRect(hwnd, &rc);
	win_w = rc.right - rc.left;
	win_h = rc.bottom - rc.top;

	screen_w = GetSystemMetrics(SM_CXSCREEN);
	screen_h = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(hwnd, HWND_TOP, (screen_w - win_w) / 2, (screen_h - win_h) / 2, 0, 0, SWP_NOSIZE);
	return;
}

static void createcontrols(HWND hwnd)
{

	INITCOMMONCONTROLSEX icex;

	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	/* TBS_HORZ is horizontal, TBS_VERT is vertical slider */
	hTrackvl = CreateWindowW(TRACKBAR_CLASSW, L"Trackbar Controll",
				 WS_CHILD | WS_VISIBLE | TBS_NOTICKS | TBS_VERT,
				 LSL_X0, LSL_Y0, LSL_XS, LSL_YS, hwnd, (HMENU) 3, NULL, NULL);

	hTrackvr = CreateWindowW(TRACKBAR_CLASSW, L"Trackbar Controlr",
				 WS_CHILD | WS_VISIBLE | TBS_NOTICKS | TBS_VERT,
				 RSL_X0, RSL_Y0, RSL_XS, RSL_YS, hwnd, (HMENU) 3, NULL, NULL);

	hTrackhor = CreateWindowW(TRACKBAR_CLASSW, L"Trackbar Controlhor",
				  WS_CHILD | WS_VISIBLE | TBS_NOTICKS | TBS_HORZ,
				  HSL_X0, HSL_Y0, HSL_XS, HSL_YS, hwnd, (HMENU) 3, NULL, NULL);

	SendMessageW(hTrackvl, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	SendMessageW(hTrackvr, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	SendMessageW(hTrackhor, TBM_SETRANGE, TRUE, MAKELONG(0, 100));

	/* set zoom slider to 50, 1:1 scaling */
	SendMessageW(hTrackvl, TBM_SETPOS, TRUE, 50);
	SendMessageW(hTrackvr, TBM_SETPOS, TRUE, 0);
	SendMessageW(hTrackhor, TBM_SETPOS, TRUE, 0);

	/* draw window */
	drw = CreateWindowW(L"Static", L"0", WS_CHILD | WS_VISIBLE, DRW_X0, DRW_Y0, DRW_XS, DRW_YS, hwnd, (HMENU) 3, NULL, NULL);

	return;
}

/* one of the sliders moved */
void updatesliders(void)
{
	RECT area;
	LRESULT posvl = 0;
	LRESULT posvr = 0;
	LRESULT poshor = 0;
	double ph = 0.0;
	double pv = 0.0;
	double pz = 0.0;
	int val1 = 0;
	if (validdata == 0) {
		return;
	}
	posvl = SendMessageW(hTrackvl, TBM_GETPOS, 0, 0);
	posvr = SendMessageW(hTrackvr, TBM_GETPOS, 0, 0);
	poshor = SendMessageW(hTrackhor, TBM_GETPOS, 0, 0);
	if (0) {
		printf("left=%d right=%d hor=%d\n", (int)posvl, (int)posvr, (int)poshor);
		fflush(stdout);
	}
	/* set hor/vert values */
	ph = (double)poshor;
	ph = ph * maxx;
	ph = ph / 100;
	vxmin = (int)ph;
	pv = (double)posvr;
	pv = pv * maxy;
	pv = pv / 100;
	vymin = (int)pv;
	/* recalc zoom factor */
	pz = (double)posvl;
	pz = round(pz);
	val1 = (int)pz;
	zfactor = exp((double)(3 * (val1 - 50)) / (double)50);

	if (0) {
		printf("left=%d right=%d hor=%d vxmin=%d vymin=%d\n", (int)posvl, (int)posvr, (int)poshor, vxmin, vymin);
		fflush(stdout);
	}
	area.left = 0;
	area.top = 0;
	area.right = drwxsize;
	area.bottom = drwysize;
	InvalidateRect(drw, &area, FALSE);
	return;
}

/* set menu in menubar */
static void addmenus(HWND hwnd)
{
	HMENU hMenubar;
	HMENU hMenu;

	hMenubar = CreateMenu();
	hMenu = CreateMenu();

	AppendMenuW(hMenu, MF_STRING, IDM_FILE_OPEN_DOT, L"Open &DOT");
	AppendMenuW(hMenu, MF_STRING, IDM_FILE_OPEN_GML, L"Open &GML");
	AppendMenuW(hMenu, MF_STRING, IDM_FILE_ABOUT, L"&About");
	AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
	AppendMenuW(hMenu, MF_STRING, IDM_FILE_QUIT, L"&Quit");

	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&File");
	SetMenu(hwnd, hMenubar);
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
			lnl->node->ly0 = 0;
			lnl->node->ly1 = my;
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

	switch (postype) {
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

/* translate \n in gml string */
static char *unesc_gml(char *str)
{
	char *buf = NULL;
	char *p = NULL;
	char *q = NULL;
	buf = calloc(1, (strlen(str) + 1));
	if (buf == NULL) {
		return (str);
	}
	p = str;
	q = buf;
	while (*p) {
		/* check for \n to change */
		if ((*p) == '\\') {
			if (*(p + 1) == 'n') {
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
			(*q) = (*p);
			q++;
			p++;
		}
	}
	p = uniqstr(buf);
	free(buf);
	buf = NULL;
	return (p);
}

/* translate \n \l \r in dot string */
static char *unesc_dot(char *str)
{
	char *buf = NULL;
	char *p = NULL;
	char *q = NULL;
	buf = calloc(1, (strlen(str) + 1));
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
	free(buf);
	buf = NULL;
	return (p);
}

/* translate esc chars in dot or gml graph */
static char *unesc(char *str)
{
	char *ret = NULL;
	if (str == NULL) {
		/* shouldnothappen */
		return (uniqstr("  "));
	}
	if (strchr(str, '\\') == NULL) {
		/* str has no esc chars */
		return (str);
	}
	if (graphtype == 0) {
		ret = unesc_gml(str);
	} else {
		ret = unesc_dot(str);
	}
	return (ret);
}

/* size of fields */
static struct gml_p static_mainwin_textsizes1sz(struct gml_rl *info)
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
			dsub = static_mainwin_textsizes1sz(info->parts[i]);
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

static void static_mainwin_textsizes1eq(struct gml_rl *info)
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
			static_mainwin_textsizes1eq(info->parts[i]);
		}
	}

	return;
}

static void static_mainwin_textsizes1rl(struct gml_rl *info)
{
	RECT c;
	int i = 0;
	size_t len = 0;
	char *tmpb = NULL;
	char *p = NULL;
	char *q = NULL;
	int ii = 0;
	char lbuf[NODE_MAXCH];

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

				/* copy chars per line into lbuf */
				p = info->ulabel;
				/* determine needed text (x,y) size */
				info->txsize = 0;
				info->tysize = 0;

				ii = 0;
				memset(lbuf, 0, NODE_MAXCH);
				for (;;) {
					if (*p == '\n' || *p == 0) {
						ii = 0;
						if (0) {
							printf("lbuf=\"%s\" len %d\n", lbuf, (int)strlen(lbuf));
						}
						/* do a fake draw text and calculate the used text area */
						c.left = 0;
						c.right = 0;
						c.top = 0;
						c.bottom = 0;
						/* calcrect means do set the (x,y) size of the text in rect c */
						DrawText(hdc, lbuf, strlen(lbuf), &c, DT_CALCRECT);
						if (0) {
							printf("%s(): textsize is (%d,%d) for \"%s\"\n", __func__,
							       (int)c.right, (int)c.bottom, lbuf);
						}
						/* find widest line of text */
						if ((int)c.right > info->txsize) {
							info->txsize = (int)c.right;
						}
						if (thefontsize != (int)c.bottom) {
							/* remember y size of one line of text */
							thefontsize = (int)c.bottom;
						}
						/* update y size of block of text lines */
						info->tysize = info->tysize + (int)c.bottom;
						if (*p == 0) {
							/* end of text */
							break;
						}
						memset(lbuf, 0, NODE_MAXCH);
					} else {
						/* limit the max. length of a single text line */
						if (ii < (NODE_MAXCH - 2)) {
							lbuf[ii] = (*p);
							ii++;
						}
						/* make sure string is 0 terminated */
						lbuf[ii] = 0;
					}
					p++;
				}

				/* now set in unode the text area size */
				if (info->txsize == 0) {
					/* shouldnothappen */
					info->txsize = FONTSZ;
				}
				if (info->tysize == 0) {
					/* shouldnothappen */
					info->tysize = FONTSZ;
				}

				/* for a box can add some border space here */
				info->txsize = info->txsize + 2;
				info->tysize = info->tysize + 2;

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
		/* */
		if (info->parts) {
			static_mainwin_textsizes1rl(info->parts[i]);
		}
	}

	return;
}

static void static_mainwin_textsizes2rl(struct gml_rl *info, int count, int xoff, int yoff, int bbx, int bby)
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

				static_mainwin_textsizes2rl(info->parts[i], i, xoff + xo, yoff + yo, ibbx, ibby);
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
static void static_mainwin_textsizes1n(struct gml_node *node)
{
	struct gml_p d;

	/* calc (x,y) text size of all parts in record label */
	static_mainwin_textsizes1rl(node->rlabel);

	d = static_mainwin_textsizes1sz(node->rlabel);

	if (yydebug || 0) {
		printf("%s(): d is (%d,%d) versus bbxy(%d,%d)\n", __func__, d.x, d.y, node->bbx, node->bby);
	}

	/* check for use of step of bb */
	static_mainwin_textsizes1eq(node->rlabel);

	/* now position the text parts and result in the rlabel structs */
	node->bbx = d.x;
	node->bby = d.y;

	static_mainwin_textsizes2rl(node->rlabel, 0, 0, 0, node->bbx, node->bby);

	return;
}

/* after edge label nodes are created:
 * calculate (x,y) size of text area
 * a label can be in nlabel or rlabel for dot record label
 * this gets the textsize at 100% 1:1 scaling zz
 */
static void static_mainwin_textsizes(void)
{
	struct gml_nlist *nl = NULL;
	char *p = NULL;
	char lbuf[NODE_MAXCH];
	int ll = 0;
	int ii = 0;
	int numl = 0;
	int maxlen = 0;
	PAINTSTRUCT ps;
	RECT c;
	HFONT hfont;
	HFONT holdfont;
	if (holdfont) {
	}

	/* starting fake paint */
	hdc = BeginPaint(drw, &ps);
	hfont = CreateFontW(FONTSZ, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 0, 0, FONTNAME);
	holdfont = SelectObject(hdc, hfont);
	/* y size in pixels of the font */
	thefontsize = FONTSZ;
	nl = maingraph->nodelist;

	while (nl) {
		/* check if size needs to be calculated */
		if (nl->node->txsize == 0) {
			/* preset */
			nl->node->tx = 0;
			nl->node->ty = 0;
			nl->node->bbx = 0;
			nl->node->bby = 0;
			if (nl->node->rlabel) {
				/* this is a dot record style label */
				if (nl->node->rlabeldone == 0) {
					static_mainwin_textsizes1n(nl->node);
					nl->node->rlabeldone = 1;
				}
			} else {
				/* this is a regular label */
				if (nl->node->dummy) {
					/* this is a dummy node with zero size */
					nl->node->tx = 0;
					nl->node->ty = 0;
					nl->node->bbx = 0;
					nl->node->bby = 0;
					nl->node->txsize = 1;	/* text size is set */
				} else {
					/* this is a real or edgelabel node */
					if (nl->node->nlabel == NULL) {
						/* shouldnothappen */
						nl->node->nlabel = uniqstr("  ");
					}

					/* if the labeltext is "" replace it with " " */
					if (strlen(nl->node->nlabel) == 0) {
						/* to avoid cairo assert */
						nl->node->nlabel = uniqstr("  ");
					}

					/* change esc chars if any */
					nl->node->nlabel = unesc(nl->node->nlabel);

					/* get size of area needed tor this text in chars */
					p = nl->node->nlabel;
					ll = 0;
					numl = 1;
					maxlen = 0;
					while (*p) {
						if (*p == '\n') {
							numl++;
							ll = 0;
						} else {
							ll++;
							if (ll > maxlen) {
								maxlen = ll;
							}
						}
						p++;
					}

					/* if no chars on a line, set at least one. */
					if (maxlen == 0) {
						maxlen = 1;
					}

					if (0) {
						printf("%s(): \"%s\" has size (%d,%d)\n", __func__, nl->node->nlabel, maxlen, numl);
					}

					/* copy chars per line into lbuf */
					p = nl->node->nlabel;
					/* determine needed text (x,y) size */
					nl->node->tx = 0;
					nl->node->ty = 0;

					ii = 0;
					memset(lbuf, 0, NODE_MAXCH);
					for (;;) {
						if (*p == '\n' || *p == 0) {
							ii = 0;
							if (0) {
								printf("lbuf=\"%s\" len %d\n", lbuf, (int)strlen(lbuf));
							}
							/* do a fake draw text and calculate the used text area */
							c.left = 0;
							c.right = 0;
							c.top = 0;
							c.bottom = 0;
							/* calcrect means do set the (x,y) size of the text in rect c */
							DrawText(hdc, lbuf, strlen(lbuf), &c, DT_CALCRECT);
							if (0) {
								printf("%s(): textsize is (%d,%d) for \"%s\"\n", __func__,
								       (int)c.right, (int)c.bottom, lbuf);
							}
							/* find widest line of text */
							if ((int)c.right > nl->node->tx) {
								nl->node->tx = (int)c.right;
							}
							if (thefontsize != (int)c.bottom) {
								/* remember y size of one line of text */
								thefontsize = (int)c.bottom;
							}
							/* update y size of block of text lines */
							nl->node->ty = nl->node->ty + (int)c.bottom;
							if (*p == 0) {
								/* end of text */
								break;
							}
							memset(lbuf, 0, NODE_MAXCH);
						} else {
							/* limit the max. length of a single text line */
							if (ii < (NODE_MAXCH - 2)) {
								lbuf[ii] = (*p);
								ii++;
							}
							/* make sure string is 0 terminated */
							lbuf[ii] = 0;
						}
						p++;
					}

					/* now set in unode the text area size */
					if (nl->node->tx == 0) {
						/* shouldnothappen */
						nl->node->tx = FONTSZ;
					}
					if (nl->node->ty == 0) {
						/* shouldnothappen */
						nl->node->ty = FONTSZ;
					}

					/* for a box can add some border space here */
					nl->node->bbx = nl->node->tx + 0;
					nl->node->bby = nl->node->ty + 0;

				}
				nl->node->txsize = 1;	/* text size is set */
			}
		}
		nl = nl->next;
	}
	DeleteObject(hfont);
	EndPaint(drw, &ps);
	return;
}

/* run all stages of the layout */
static void do_layout_all(struct gml_graph *g)
{

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
	static_mainwin_textsizes();

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
	edgeconnections(g);

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

	xzscale = (double)(10 * drwxsize / maxx);
	yzscale = (double)(10 * drwysize / maxy);

	xzscale = xzscale / 10.0;
	yzscale = yzscale / 10.0;

	if ((xzscale - yzscale) > 0) {
		newzscale = yzscale;
	} else {
		newzscale = xzscale;
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
	SendMessageW(hTrackvl, TBM_SETPOS, TRUE, val);

	/* reset v xy min */
	vxmin = 0;
	vymin = 0;

	SendMessageW(hTrackvr, TBM_SETPOS, TRUE, 0);
	SendMessageW(hTrackhor, TBM_SETPOS, TRUE, 0);

	return;
}

/* what is 0 for dot, 1 for gml chosen */
static void doopen(HWND hwnd, int what)
{
	RECT area;
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH];
	FILE *f = NULL;
	int status = 0;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.hwndOwner = hwnd;
	ofn.nMaxFile = sizeof(szFile);
	if (what == 1) {
		ofn.lpstrFilter = TEXT("All files(*.*)\0*.*\0Gml files(*.gml)\0*.gml\0");
	} else {
		ofn.lpstrFilter = TEXT("All files(*.*)\0*.*\0Dot files(*.dot)\0*.dot\0Dot files(*.gv)\0*.gv\0");
	}
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn)) {
		f = fopen(ofn.lpstrFile, "rb");

		if (f == NULL) {
			MessageBoxW(NULL, L"Cannot open file", L"File error", MB_OK);
			return;
		}

		/* data is invalid at this point */
		validdata = 0;

		/* wipe old data if any */
		do_clear_all(0);

		/* default white background */
		bgcr = 0xff;
		bgcg = 0xff;
		bgcb = 0xff;

		/* create root graph */
		create_maingraph();

		/* parse the data */
		if (what == 1) {
			status = gmlparse(maingraph, f, ofn.lpstrFile);
			/* type of graph data 0=gml 1=dot */
			graphtype = 0;
		} else {
			status = dotparse(maingraph, f, ofn.lpstrFile, "gml4win");
			/* type of graph data 0=gml 1=dot */
			graphtype = 1;
		}
		if (status) {
			/* some parse error */
			if (strlen(parsermessage) == 0) {
				strcpy(parsermessage, "no parser message");
			}
			printf("%s\n", parsermessage);
			fflush(stdout);
			fclose(f);
			/* data is invalid at this point */
			validdata = 0;
			MessageBoxW(NULL, L"syntax error in graph file", L"Parse error", MB_OK);
			return;
		}

		/* check for empty graph here */
		if (maingraph->rawnodelist == NULL) {
			printf("%s\n", "empty graph without nodes");
			fflush(stdout);
			/* data is invalid at this point */
			validdata = 0;
			MessageBoxW(NULL, L"empty graph without nodes", L"Empty grph", MB_OK);
			return;
		}

		do_layout_all(maingraph);

		/* set sliders to defaults */
		zfactor = 1.0;
		vxmin = 0;
		vymin = 0;

		SendMessageW(hTrackvl, TBM_SETPOS, TRUE, 50);
		SendMessageW(hTrackvr, TBM_SETPOS, TRUE, 0);
		SendMessageW(hTrackhor, TBM_SETPOS, TRUE, 0);

		/* fit drawing in window */
		dofit();

		validdata = 1;

		fclose(f);
	}

	/* force redraw */
	area.left = 0;
	area.top = 0;
	area.right = drwxsize;
	area.bottom = drwysize;
	InvalidateRect(drw, &area, FALSE /*TRUE*/);
	/* make sure drawing is on screen */
	drawit(mainhwnd);
	return;
}

/* scale down a number */
static int scaleit(int pos)
{
	double num = 0.0;
	int ret = 0;
	num = (double)pos;
	num = num * zfactor;
	num = round(num);
	ret = (int)num;
	return (ret);
}

/* */
static void on_top_level_window_drawingarea1_expose_event_nodes_record_r(struct gml_node
									 *node, struct gml_rl
									 *info)
{
	int i = 0;
	int x0 = 0;
	int y0 = 0;
	int cr = 0;
	int cb = 0;
	int cg = 0;
	int xxo = 0;
	int yyo = 0;
	int szx = 0;
	int szy = 0;
	HPEN pen1;
	HPEN holdpen;
	HFONT hfont;
	HFONT holdfont;
	int snewx = 0;
	int snewy = 0;
	int sbbx = 0;
	int sbby = 0;
	double tsize = 0.0;
	int stsize = 0;
	char lbuf[NODE_MAXCH];
	char *p = NULL;
	int ii = 0;
	int yy = 0;
	int stx0 = 0;
	int sty0 = 0;
	if (holdpen) {
	}
	if (holdfont) {
	}

	x0 = node->finx - vxmin;
	y0 = node->finy - vymin;

	if (info->hd == 0) {
		/* not-has-data */
		for (i = 0; i < info->nparts; i++) {
			on_top_level_window_drawingarea1_expose_event_nodes_record_r(node, info->parts[i]);
		}

	} else {
		/* has-data */

		/* black outline color */
		cr = 0;
		cg = 0;
		cb = 0;

		pen1 = CreatePen(PS_SOLID, 1, RGB(cr, cg, cb));
		holdpen = SelectObject(hdc, pen1);
		SelectObject(hdc, pen1);

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

		/* get scaled coords */
		snewx = scaleit(x0 + info->xoff);
		snewy = scaleit(y0 + info->yoff);
		sbbx = scaleit(szx);
		sbby = scaleit(szy);

		MoveToEx(hdc, snewx, snewy, NULL);
		LineTo(hdc, snewx + sbbx, snewy);
		LineTo(hdc, snewx + sbbx, snewy + sbby);
		LineTo(hdc, snewx, snewy + sbby);
		LineTo(hdc, snewx, snewy);
		DeleteObject(pen1);

		if (yydebug || 0) {
			printf("%s(): rect at (%d,%d) size (%d,%d) for \"%s\"\n", __func__,
			       x0 + info->xoff, y0 + info->yoff, szx, szy, info->ulabel);
		}

		/* scale text size */
		tsize = thefontsize;	/* or: FONTSZ */
		tsize = tsize * zfactor;
		tsize = round(tsize);
		stsize = (int)tsize;

		/* only text if resulting font size is big enough */
		if (stsize > 8) {
			/* set background color of text */
			SetBkMode(hdc, TRANSPARENT);
			/* or:
			 * cr = (n->ncolor & 0x00ff0000) >> 16;
			 * cg = (n->ncolor & 0x0000ff00) >> 8;
			 * cb = (n->ncolor & 0x000000ff);
			 * SetBkColor(hdc, RGB(cr, cg, cb));
			 */

			/* set color of text */
			cr = (node->fontcolor & 0x00ff0000) >> 16;
			cg = (node->fontcolor & 0x0000ff00) >> 8;
			cb = (node->fontcolor & 0x000000ff);
			SetTextColor(hdc, RGB(cr, cg, cb));

			/* start text inside rectangle */
			xxo = 1;
			yyo = 1;

			/* start of text, draw it line by line */
			stx0 = scaleit(x0 + info->xoff + xxo + 0);
			sty0 = scaleit(y0 + info->yoff + yyo + 0);
			/* adjust y start of text */
			sty0 = sty0 - stsize;
			hfont = CreateFontW(stsize, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 0, 0, FONTNAME);

			holdfont = SelectObject(hdc, hfont);
			p = info->ulabel;
			yy = 0;
			ii = 0;
			memset(lbuf, 0, NODE_MAXCH);
			for (;;) {
				if (*p == '\n' || *p == 0) {
					ii = 0;
					if (0) {
						printf("lbuf=\"%s\" len %d\n", lbuf, (int)strlen(lbuf));
					}
					TextOut(hdc, stx0, sty0 + stsize + yy, lbuf, lstrlen(lbuf));
					yy += stsize;
					if (*p == 0) {
						break;
					}
					memset(lbuf, 0, NODE_MAXCH);
				} else {
					/* limit the max. length of a single text line */
					if (ii < (NODE_MAXCH - 2)) {
						lbuf[ii] = (*p);
						ii++;
					}
					/* make sure string is 0 terminated */
					lbuf[ii] = 0;
				}
				p++;
			}
			DeleteObject(hfont);
		}

	}

	return;
}

/* record node drawing */
static void on_top_level_window_drawingarea1_expose_event_nodes_record(struct gml_node
								       *node)
{
	on_top_level_window_drawingarea1_expose_event_nodes_record_r(node, node->rlabel);
	return;
}

/* draw one node */
static void drawnodes1n(struct gml_node *n)
{
	int newx = 0;
	int newy = 0;
	int snewx = 0;
	int snewy = 0;
	int sbbx = 0;
	int sbby = 0;
	HPEN pen1;
	HPEN holdpen;
	int cr = 0;
	int cg = 0;
	int cb = 0;
	int yy = 0;
	double tsize = 0.0;
	int stsize = 0;
	int stx0 = 0;
	int sty0 = 0;
	HFONT hfont;
	HFONT holdfont;
	char lbuf[NODE_MAXCH];
	char *p = NULL;
	int ii = 0;
	if (holdfont) {
	}
	if (holdpen) {
	}
	/* get node (x,y) pos */
	newx = n->finx - vxmin;
	newy = n->finy - vymin;

	if (0) {
		printf("vxymin (%d,%d) newxy (%d,%d) nxy (%d,%d)\n", vxmin, vymin, newx, newy, n->finx, n->finy);
	}

	/* check if needed to draw */
	if (newx < 0) {
		if (newx + n->bbx < 0) {
			return;
		}
	}
	if (newy < 0) {
		if (newy + n->bby < 0) {
			return;
		}
	}

	/* get scaled coords */
	snewx = scaleit(newx);
	snewy = scaleit(newy);
	sbbx = scaleit(n->bbx);
	sbby = scaleit(n->bby);

	/* check if drawable */
	if (snewx > drwxsize) {
		return;
	}
	if (snewy > drwysize) {
		return;
	}

	/* draw the background color of node but not for edgelabel */
	if (n->elabel == 0) {
		cr = (n->ncolor & 0x00ff0000) >> 16;
		cg = (n->ncolor & 0x0000ff00) >> 8;
		cb = (n->ncolor & 0x000000ff);
		if (cr != bgcr || cg != bgcg || cb != bgcb) {
			pen1 = CreatePen(PS_SOLID, 1, RGB(cr, cg, cb));
			holdpen = SelectObject(hdc, pen1);
			SelectObject(hdc, pen1);
			if (0) {
				printf("%s(): rect at (%d,%d) size (%d,%d) color #%02x%02x%02x\n", __func__, snewx, snewy,
				       sbbx, sbby, cr, cg, cb);
			}
			for (yy = 0; yy < sbby; yy++) {
				MoveToEx(hdc, snewx, snewy + yy, NULL);
				LineTo(hdc, snewx + sbbx, snewy + yy);
			}
			DeleteObject(pen1);
		}
	}

	/* outline color black for node, edgelabel node has no outline */
	if (n->elabel == 0) {
		/* bordercolor of node black default or color */
		cr = (n->nbcolor & 0x00ff0000) >> 16;
		cg = (n->nbcolor & 0x0000ff00) >> 8;
		cb = (n->nbcolor & 0x000000ff);
		if (cr != bgcr || cg != bgcg || cb != bgcb) {
			/* the second arg 2 is the line thickness */
			pen1 = CreatePen(PS_SOLID, 2, RGB(cr, cg, cb));
			holdpen = SelectObject(hdc, pen1);
			MoveToEx(hdc, snewx, snewy, NULL);
			LineTo(hdc, snewx + sbbx, snewy);
			LineTo(hdc, snewx + sbbx, snewy + sbby);
			LineTo(hdc, snewx, snewy + sbby);
			LineTo(hdc, snewx, snewy);
			DeleteObject(pen1);
		}
	}

	if (n->rlabel) {
		/* node with dot record label */
		on_top_level_window_drawingarea1_expose_event_nodes_record(n);

	} else {
		/* node with regular label */

		/* scale text size */
		tsize = thefontsize;	/* or: FONTSZ */
		tsize = tsize * zfactor;
		tsize = round(tsize);
		stsize = (int)tsize;

		/* only text if resulting font size is big enough */
		if (stsize > 8) {
			/* set background color of text */
			SetBkMode(hdc, TRANSPARENT);
			/* or:
			 * cr = (n->ncolor & 0x00ff0000) >> 16;
			 * cg = (n->ncolor & 0x0000ff00) >> 8;
			 * cb = (n->ncolor & 0x000000ff);
			 * SetBkColor(hdc, RGB(cr, cg, cb));
			 */

			/* set color of text */
			cr = (n->fontcolor & 0x00ff0000) >> 16;
			cg = (n->fontcolor & 0x0000ff00) >> 8;
			cb = (n->fontcolor & 0x000000ff);
			SetTextColor(hdc, RGB(cr, cg, cb));

			/* start of text, draw it line by line */
			stx0 = scaleit(newx + 0);
			sty0 = scaleit(newy + 0);
			/* adjust y start of text */
			sty0 = sty0 - stsize;
			hfont = CreateFontW(stsize, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 0, 0, FONTNAME);

			holdfont = SelectObject(hdc, hfont);
			p = n->nlabel;
			yy = 0;
			ii = 0;
			memset(lbuf, 0, NODE_MAXCH);
			for (;;) {
				if (*p == '\n' || *p == 0) {
					ii = 0;
					if (0) {
						printf("lbuf=\"%s\" len %d\n", lbuf, (int)strlen(lbuf));
					}
					TextOut(hdc, stx0, sty0 + stsize + yy, lbuf, lstrlen(lbuf));
					yy += stsize;
					if (*p == 0) {
						break;
					}
					memset(lbuf, 0, NODE_MAXCH);
				} else {
					/* limit the max. length of a single text line */
					if (ii < (NODE_MAXCH - 2)) {
						lbuf[ii] = (*p);
						ii++;
					}
					/* make sure string is 0 terminated */
					lbuf[ii] = 0;
				}
				p++;
			}
			DeleteObject(hfont);
		}
	}
	return;
}

/* all nodes */
static void drawnodes(void)
{
	struct gml_nlist *lnl = NULL;
	lnl = maingraph->nodelist;
	while (lnl) {
		/* only draw real or edgelabel nodes */
		if (lnl->node->dummy == 0) {
			drawnodes1n(lnl->node);
		}
		lnl = lnl->next;
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

/* pi must be defined */
#ifndef M_PI
#define M_PI 3.14
#endif

/* draw arrow, option to allow multiple arrow types todo
 * arrow comes from (start_x,start_y) to (end_x,end_y)
 * size is optional, if zero a default size is used
 */
static void drarrow(int start_x, int start_y, int end_x, int end_y, double size)
{
	double angle = 0.0;
	double arrow_lenght = 8.0;
	double arrow_degrees = ( /* degrees */ 30 * (M_PI / 180));
	double x1 = 0.0;
	double y1 = 0.0;
	double x2 = 0.0;
	double y2 = 0.0;
	int sp1x = 0;
	int sp1y = 0;

	if (yydebug || 0) {
		printf("%s(): arrow at (%d,%d) coming from (%d,%d) size %f\n", __func__, end_x, end_y, start_x, start_y, size);
	}

	/* if size is specified, use it, otherwise use default size */
	if (size == 0) {
		arrow_lenght = 6.0;
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
	sp1x = scaleit(end_x);
	sp1y = scaleit(end_y);
	MoveToEx(hdc, sp1x, sp1y, NULL);
	sp1x = scaleit(x1);
	sp1y = scaleit(y1);
	LineTo(hdc, sp1x, sp1y);

	/* set start position of arrow part 2 */
	sp1x = scaleit(end_x);
	sp1y = scaleit(end_y);
	MoveToEx(hdc, sp1x, sp1y, NULL);
	sp1x = scaleit(x2);
	sp1y = scaleit(y2);
	LineTo(hdc, sp1x, sp1y);

	/* make a triangle */
	sp1x = scaleit(x1);
	sp1y = scaleit(y1);
	LineTo(hdc, sp1x, sp1y);

	return;
}

/* return 0 if edge line is out of window */
static int edgeisok(int sfnx1, int sfny1, int stnx1, int stny1)
{
	if (sfnx1 < 0 && stnx1 < 0) {
		return (0);
	}
	if (sfny1 < 0 && stny1 < 0) {
		return (0);
	}
	if (sfnx1 > drwxsize && stnx1 > drwxsize) {
		return (0);
	}
	if (sfny1 > drwysize && stny1 > drwysize) {
		return (0);
	}
	/* edge line is in draw area */
	return (1);
}

/* all edges */
static void drawedges(void)
{
	struct gml_elist *el = NULL;
	struct gml_edge *edge = NULL;
	struct gml_node *sn = NULL;
	struct gml_node *tn = NULL;
	int ecolor = 0;
	int cr = 0;
	int cg = 0;
	int cb = 0;
	int fnx1 = 0;
	int fny1 = 0;
	int tnx1 = 0;
	int tny1 = 0;
	int sfnx1 = 0;
	int sfny1 = 0;
	int stnx1 = 0;
	int stny1 = 0;
	int shx0 = 0;
	int shy0 = 0;
	int shx1 = 0;
	int shy1 = 0;
	int shx2 = 0;
	int shy2 = 0;
	int dx15 = 0;
	HPEN pen1;
	HPEN holdpen;
	int pentype = 0;
	int bezier = 1;		/* set to 0 for straight lines */
	POINT points[4];
	if (holdpen) {
	}
	/* only spline edges here, not raw */
	el = maingraph->edgelist;
	while (el) {
		edge = el->edge;
		sn = edge->from_node;	/* from-node */
		tn = edge->to_node;	/* to-node */
		ecolor = edge->ecolor;	/* edge line color */
		/* black or colored line */
		cr = (ecolor & 0x00ff0000) >> 16;
		cg = (ecolor & 0x0000ff00) >> 8;
		cb = (ecolor & 0x000000ff);
		/* if color is background color do not draw line */
		if (cr == bgcr && cg == bgcg && cb == bgcb) {
			el = el->next;
			continue;
		}
		/* if line is out of window do not draw edge line */
		fnx1 = sn->finx - vxmin;
		fny1 = sn->finy - vymin;
		tnx1 = tn->finx - vxmin;
		tny1 = tn->finy - vymin;
		sfnx1 = scaleit(fnx1);
		sfny1 = scaleit(fny1);
		stnx1 = scaleit(tnx1);
		stny1 = scaleit(tny1);
		if (edgeisok(sfnx1, sfny1, stnx1, stny1) == 0) {
			el = el->next;
			continue;
		}

		/* check edge line style
		 * some windows line styles are:
		 * HPEN hPen1 = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		 * HPEN hPen2 = CreatePen(PS_DASH, 1, RGB(0, 0, 0));
		 * HPEN hPen3 = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		 * HPEN hPen4 = CreatePen(PS_DASHDOT, 1, RGB(0, 0, 0));
		 * HPEN hPen5 = CreatePen(PS_DASHDOTDOT, 1, RGB(0, 0, 0));
		 */
		if (edge->style == 1 /* ESTYLE_DASHED */ ) {
			/* dashed edge line */
			pentype = PS_DASH;
		} else if (edge->style == 2 /* ESTYLE_DOTTED */ ) {
			/* dotted edge line */
			pentype = PS_DOT;
		} else {
			/* solid edge line */
			pentype = PS_SOLID;
		}

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
					sfnx1 = scaleit(fnx1);
					sfny1 = scaleit(fny1);
					stnx1 = scaleit(tn->finx - vxmin);
					stny1 = scaleit((tn->finy + tn->bby / 2) - vymin);

					sfnx1 = scaleit(fnx1);
					sfny1 = scaleit(fny1);
					MoveToEx(hdc, sfnx1, sfny1, NULL);

					sfnx1 = scaleit((tn->finx) - vxmin);
					sfny1 = scaleit((tn->finy + tn->bby / 2) - vymin);
					LineTo(hdc, sfnx1, sfny1);
					/* add arrow */
					if (edge->reversed == 0) {
						drarrow(fnx1, fny1, (tn->finx) - vxmin, (tn->finy + tn->bby / 2) - vymin, 0);
					} else {
						drarrow((tn->finx) - vxmin, (tn->finy + tn->bby / 2) - vymin, fnx1, fny1, 0);
					}

				} else {

					/* distance length of hor. line / 5 */
					dx15 = (tnx1 - fnx1) / 5;
					/* start line at center */
					fnx1 = (sn->finx + sn->bbx / 2) - vxmin;
					fny1 = (sn->finy + sn->bby) - vymin;
					sfnx1 = scaleit(fnx1);
					sfny1 = scaleit(fny1);
					MoveToEx(hdc, sfnx1, sfny1, NULL);
					if ((sn->finy + sn->bby) >= (tn->finy + tn->bby)) {
						/* from node y is lower then target, put hor. line 10px lower */

						sfnx1 = scaleit(fnx1 + dx15);
						sfny1 = scaleit(((sn->finy + sn->bby) + HEDGE_DY) - vymin);
						LineTo(hdc, sfnx1, sfny1);
						sfnx1 = scaleit((fnx1 + dx15) + (3 * dx15));
						sfny1 = scaleit(((sn->finy + sn->bby) + HEDGE_DY) - vymin);
						LineTo(hdc, sfnx1, sfny1);
						sfnx1 = scaleit((tn->finx + tn->bbx / 2) - vxmin);
						sfny1 = scaleit((tn->finy + tn->bby) - vymin);
						LineTo(hdc, sfnx1, sfny1);
						/* add arrow */
						if (edge->reversed == 0) {
							drarrow((fnx1 + dx15) + (3 * dx15),
								((sn->finy + sn->bby) + HEDGE_DY) -
								vymin, (tn->finx + tn->bbx / 2) - vxmin,
								(tn->finy + tn->bby) - vymin, 0);
						} else {
							drarrow((tn->finx + tn->bbx / 2) - vxmin,
								(tn->finy + tn->bby) - vymin,
								(fnx1 + dx15) + (3 * dx15),
								((sn->finy + sn->bby) + HEDGE_DY) - vymin, 0);
						}

					} else {
						/* from-node y is higher */

						sfnx1 = scaleit(fnx1 + dx15);
						sfny1 = scaleit((tn->finy + tn->bby) + HEDGE_DY - vymin);
						LineTo(hdc, sfnx1, sfny1);
						sfnx1 = scaleit((fnx1 + dx15) + (3 * dx15));
						sfny1 = scaleit(((tn->finy + tn->bby) + HEDGE_DY) - vymin);
						LineTo(hdc, sfnx1, sfny1);
						sfnx1 = scaleit((tn->finx + tn->bbx / 2) - vxmin);
						sfny1 = scaleit((tn->finy + tn->bby) - vymin);
						LineTo(hdc, sfnx1, sfny1);
						/* add arrow */
						if (edge->reversed == 0) {
							drarrow((fnx1 + dx15) + (3 * dx15),
								((tn->finy + tn->bby) + HEDGE_DY) -
								vymin,
								(tn->finx + tn->bbx / 2) - vxmin, (tn->finy + tn->bby) - vymin, 0);
						} else {
							drarrow((fnx1 + dx15),
								(tn->finy + tn->bby) + HEDGE_DY - vymin, fnx1, fny1, 0);
						}

					}

				}

			} else {
				/* edge from right to left fnx1>tnx1 */

				if ((sn->relx) == (tn->relx + 1)) {
					/*  printf ("direct-rl\n");  */

					sfnx1 = scaleit((sn->finx) - vxmin);
					sfny1 = scaleit((sn->finy + sn->bby / 2) - vymin);
					MoveToEx(hdc, sfnx1, sfny1, NULL);
					sfnx1 = scaleit(tn->finx + tn->bbx - vxmin);
					sfny1 = scaleit(tn->finy + tn->bby / 2 - vymin);
					LineTo(hdc, sfnx1, sfny1);
					/* add arrow */
					if (edge->reversed == 0) {
						drarrow((sn->finx) - vxmin,
							(sn->finy + sn->bby / 2) - vymin,
							tn->finx + tn->bbx - vxmin, tn->finy + tn->bby / 2 - vymin, 0);
					} else {
						drarrow(tn->finx + tn->bbx - vxmin,
							tn->finy + tn->bby / 2 - vymin,
							(sn->finx) - vxmin, (sn->finy + sn->bby / 2) - vymin, 0);
					}

				} else {

					/* distance length of hor. line / 5 */
					dx15 = (fnx1 - tnx1) / 5;
					/* start line at center */
					fnx1 = (sn->finx + sn->bbx / 2) - vxmin;
					fny1 = (sn->finy + sn->bby) - vymin;
					sfnx1 = scaleit(fnx1);
					sfny1 = scaleit(fny1);
					MoveToEx(hdc, sfnx1, sfny1, NULL);
					if ((sn->finy + sn->bby) >= (tn->finy + tn->bby)) {
						/* from node y is lower then target, put hor. line 10px lower */
						sfnx1 = scaleit(fnx1 - dx15);
						sfny1 = scaleit(((sn->finy + sn->bby) + HEDGE_DY) - vymin);
						LineTo(hdc, sfnx1, sfny1);
						sfnx1 = scaleit((fnx1 - dx15) - (3 * dx15));
						sfny1 = scaleit(((sn->finy + sn->bby) + HEDGE_DY) - vymin);
						LineTo(hdc, sfnx1, sfny1);
						sfnx1 = scaleit((tn->finx + tn->bbx / 2) - vxmin);
						sfny1 = scaleit((tn->finy + tn->bby) - vymin);
						LineTo(hdc, sfnx1, sfny1);
						/* add arrow */
						if (edge->reversed == 0) {
							/* could be improved here todo */
							drarrow((fnx1 - dx15) - (3 * dx15),
								((sn->finy + sn->bby) +
								 HEDGE_DY) - vymin,
								(tn->finx + tn->bbx / 2) - vxmin, (tn->finy + tn->bby) - vymin, 0);
						} else {
							drarrow((fnx1 - dx15),
								((sn->finy + sn->bby) + HEDGE_DY) - vymin, fnx1, fny1, 0);
						}

					} else {
						/* from-node y is higher */
						sfnx1 = scaleit(fnx1 - dx15);
						sfny1 = scaleit((tn->finy + tn->bby) + HEDGE_DY - vymin);
						LineTo(hdc, sfnx1, sfny1);
						sfnx1 = scaleit((fnx1 - dx15) - (3 * dx15));
						sfny1 = scaleit(((tn->finy + tn->bby) + HEDGE_DY) - vymin);
						LineTo(hdc, sfnx1, sfny1);
						sfnx1 = scaleit((tn->finx + tn->bbx / 2) - vxmin);
						sfny1 = scaleit((tn->finy + tn->bby) - vymin);
						LineTo(hdc, sfnx1, sfny1);
						/* add arrow */
						if (edge->reversed == 0) {
							/* this could be improved, todo */
							drarrow((fnx1 - dx15) - (3 * dx15),
								((sn->finy + sn->bby) +
								 HEDGE_DY) - vymin,
								(tn->finx + tn->bbx / 2) - vxmin, (tn->finy + tn->bby) - vymin, 0);
						} else {
							drarrow((fnx1 - dx15),
								(tn->finy + tn->bby) + HEDGE_DY - vymin, fnx1, fny1, 0);
						}

					}

				}

			}

			/* end of horizontal edge */

		} else {
			/* regular vertical edge */
			if (sn->dummy == 0 && tn->dummy == 0) {
				/* from real node to real node.
				 * real nodes are interleaved with dummy nodes
				 * this only does happen from real node to edge-label node
				 */

				fnx1 = sn->finx + sn->bbx / 2 - vxmin;
				fny1 = sn->finy + sn->bby - vymin;
				tnx1 = tn->finx + tn->bbx / 2 - vxmin;
				tny1 = tn->finy - vymin;
				sfnx1 = scaleit(fnx1);
				sfny1 = scaleit(fny1);
				stnx1 = scaleit(tnx1);
				stny1 = scaleit(tny1);
				pen1 = CreatePen(pentype, 1, RGB(cr, cg, cb));
				holdpen = SelectObject(hdc, pen1);
				MoveToEx(hdc, sfnx1, sfny1, NULL);
				LineTo(hdc, stnx1, stny1);

				/* add arrow */
				if (edge->reversed == 0) {
					drarrow(fnx1, fny1, tnx1, tny1, 0);
				} else {
					drarrow(tnx1, tny1, fnx1, fny1, 0);
				}

				DeleteObject(pen1);
			} else if (sn->dummy == 1 && tn->dummy == 0) {
				/* from dummy node to real node */
				fnx1 = sn->finx - vxmin;
				fny1 = sn->finy - vymin;
				tnx1 = d2r_tnx1(edge) - vxmin;
				tny1 = tn->finy - vymin;
				/* point 0 */
				sfnx1 = scaleit(fnx1);
				sfny1 = scaleit(fny1);
				/* point 1 */
				shx1 = scaleit(fnx1);
				shy1 = scaleit(fny1 + (sn->bby / 2));
				/* point 2 */
				shx2 = scaleit(tnx1);
				shy2 = scaleit(tn->ly0 - vymin);
				/* point 3 */
				stnx1 = scaleit(tnx1);
				stny1 = scaleit(tny1);
				/*
				 * cairo_move_to(crp, fnx1, fny1);
				 * cairo_curve_to(crp, fnx1, fny1, fnx1, fny1 + (sn->bby / 2), tnx1, (tn->ly0 - vymin));
				 * cairo_line_to(crp, tnx1, tny1);
				 */
				if (bezier) {
					points[0].x = sfnx1;
					points[0].y = sfny1;
					points[1].x = shx1;
					points[1].y = shy1;
					points[2].x = shx2;
					points[2].y = shy2;
					points[3].x = stnx1;
					points[3].y = stny1;
					pen1 = CreatePen(pentype, 1, RGB(cr, cg, cb));
					holdpen = SelectObject(hdc, pen1);
					PolyBezier(hdc, points, 4);
					/* add arrow */
					if (edge->reversed == 0) {
						drarrow(fnx1, fny1, tnx1, tny1, 0);
					} else {
						/* no arrow */
					}

					DeleteObject(pen1);
				} else {
					pen1 = CreatePen(pentype, 1, RGB(cr, cg, cb));
					holdpen = SelectObject(hdc, pen1);
					MoveToEx(hdc, sfnx1, sfny1, NULL);
					LineTo(hdc, stnx1, stny1);
					/* add arrow */
					if (edge->reversed == 0) {
						drarrow(fnx1, fny1, tnx1, tny1, 0);
					} else {
						/* no arrow */
					}

					DeleteObject(pen1);
				}

			} else if (sn->dummy == 0 && tn->dummy == 1) {
				/* from real node to dummy node */
				fnx1 = r2d_finx(edge) - vxmin;
				fny1 = (sn->finy + sn->bby) - vymin;
				tnx1 = tn->finx - vxmin;
				tny1 = tn->finy - vymin;
				/* point 0 */
				sfnx1 = scaleit(fnx1);
				sfny1 = scaleit(fny1);
				/* point 1 */
				shx1 = scaleit(fnx1);
				shy1 = scaleit(sn->ly1 - vymin);
				/* point 2 */
				shx2 = scaleit(tnx1);
				shy2 = scaleit(tny1 - (tn->bby / 2));
				/* point 3 */
				stnx1 = scaleit(tnx1);
				stny1 = scaleit(tny1);
				/*
				 * cairo_move_to(crp, fnx1, fny1);
				 * cairo_curve_to(crp, fnx1, (sn->ly1 - vymin), tnx1, tny1 - (tn->bby / 2), tnx1, tny1);
				 */
				if (bezier) {
					points[0].x = sfnx1;
					points[0].y = sfny1;
					points[1].x = shx1;
					points[1].y = shy1;
					points[2].x = shx2;
					points[2].y = shy2;
					points[3].x = stnx1;
					points[3].y = stny1;
					pen1 = CreatePen(pentype, 1, RGB(cr, cg, cb));
					holdpen = SelectObject(hdc, pen1);
					PolyBezier(hdc, points, 4);
					/* add arrow */
					if (edge->reversed == 0) {
						/* no arrow */
					} else {
						drarrow(tnx1, tny1, fnx1, fny1, 0);
					}

					DeleteObject(pen1);
				} else {
					/* direct line */
					pen1 = CreatePen(pentype, 1, RGB(cr, cg, cb));
					holdpen = SelectObject(hdc, pen1);
					MoveToEx(hdc, sfnx1, sfny1, NULL);
					LineTo(hdc, stnx1, stny1);
					/* add arrow */
					if (edge->reversed == 0) {
						/* no arrow */
					} else {
						drarrow(tnx1, tny1, fnx1, fny1, 0);
					}

					DeleteObject(pen1);
				}

			} else {
				/* from dummy node to dummy node */
				fnx1 = sn->finx - vxmin;
				fny1 = sn->finy - vymin;
				tnx1 = tn->finx - vxmin;
				tny1 = tn->finy - vymin;
				shx0 = scaleit(fnx1);
				shy0 = scaleit(fny1);
				/* point 0 */
				sfnx1 = scaleit(fnx1);
				sfny1 = scaleit(fny1 + (sn->bby / 2));
				/* point 1 */
				shx1 = scaleit(tnx1);
				shy1 = scaleit(tn->ly0 - vymin);
				/* point 2 */
				shx2 = scaleit(tnx1);
				shy2 = scaleit(tny1 - (tn->bby / 2));
				/* point 3 */
				stnx1 = scaleit(tnx1);
				stny1 = scaleit(tny1);
				/*
				 * cairo_move_to(crp, fnx1, fny1);
				 * cairo_line_to(crp, fnx1, fny1 + (sn->bby / 2));
				 * cairo_move_to(crp, fnx1, fny1 + (sn->bby / 2));
				 * cairo_curve_to(crp, tnx1, (tn->ly0 - vymin), tnx1, tny1 - (tn->bby / 2), tnx1, tny1);
				 */
				/* */
				if (bezier) {

					points[0].x = sfnx1;
					points[0].y = sfny1;
					points[1].x = shx1;
					points[1].y = shy1;
					points[2].x = shx2;
					points[2].y = shy2;
					points[3].x = stnx1;
					points[3].y = stny1;
					pen1 = CreatePen(pentype, 1, RGB(cr, cg, cb));
					holdpen = SelectObject(hdc, pen1);
					MoveToEx(hdc, shx0, shy0, NULL);
					LineTo(hdc, sfnx1, sfny1);
					PolyBezier(hdc, points, 4);
					DeleteObject(pen1);
				} else {
					/* direct */
					pen1 = CreatePen(pentype, 1, RGB(cr, cg, cb));
					holdpen = SelectObject(hdc, pen1);
					MoveToEx(hdc, sfnx1, sfny1, NULL);
					LineTo(hdc, stnx1, stny1);
					DeleteObject(pen1);
				}

				/* no real nodes, no arrows, optional draw arrows at dummy nodes, see tuxsee */

			}
		}

		el = el->next;
	}

	return;
}

/*zz2 draw it */
static void drawit(HWND hwnd)
{
	PAINTSTRUCT ps;
	RECT r;
	HBRUSH b1;
	/* main window (x,y) size */
	GetClientRect(hwnd, &r);
	wxsize = (int)r.right - (int)r.left;
	wysize = (int)r.bottom - (int)r.top;
	/* draw window (x,y) size */
	GetClientRect(drw, &r);
	drwxsize = (int)r.right - (int)r.left;
	drwysize = (int)r.bottom - (int)r.top;
	if (0) {
		printf("dr (%d,%d)\n", (int)r.right, (int)r.bottom);
	}
	hdc = BeginPaint(drw, &ps);
	/* draw the background color */
	b1 = CreateSolidBrush(RGB(bgcr, bgcg, bgcb));
	SelectObject(hdc, b1);
	Rectangle(hdc, 0, 0, drwxsize, drwysize);
	/* if there is a graph, draw nodes+edges */
	if (validdata) {
		drawnodes();
		drawedges();
	}

	EndPaint(drw, &ps);
	return;
}

/* update crossings text in gui */
void update_status_text_cross(char *text)
{
	if (text) {
	}
	/* notused */ return;
}

/* end */
