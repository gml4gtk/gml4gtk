
/*
 *  Copyright 2021
 *  (C) Universitaet Passau 1986-1991
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

/* this is a re-work of 1 file part of graphlet program */

/*
 * id number as string as in node/edge example id "4" now accepted
 * because yed and other gml tool does accept it too.
 */

/*
 *  parser for the GML-file-format specified in:
 * this file has 1 memory leak
 * splay tree is used to track memory and free all at end.
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <zlib.h>

#include "splay-tree.h"
#include "main.h"
#include "hier.h"
#include "uniqstr.h"
#include "uniqnode.h"
#include "gml_scanner.h"
#include "gml_parser.h"
#include "dpmem.h"

/* struct for node graphics */
struct nodegr {
	int foundncolor;
	int ncolor;
	int foundnbcolor;
	int nbcolor;
};

/* struct for node labelgraphics */
struct nodelgr {
	int foundfontcolor;
	int fontcolor;
	int foundtext;
	char *text;
};

/* struct for edge graphics */
struct edgegr {
	int foundecolor;
	int ecolor;
};

static splay_tree gmlparser_splaytree = NULL;

struct GML_pair *GML_parser(gzFile source, struct GML_stat *stat, int open)
{
	struct GML_token token;
	struct GML_pair *pair = NULL;
	struct GML_pair *list = NULL;
	struct GML_pair *tmp = NULL;
	struct GML_list_elem *tmp_elem = NULL;

	pair = (struct GML_pair *)gmlparser_calloc((size_t)1, sizeof(struct GML_pair));

	list = pair;

	for (;;) {
		token = GML_scanner(source);

		if (token.kind == GML_END) {
			if (open) {
				stat->err.err_num = GML_OPEN_BRACKET;
				stat->err.line = GML_line;
				stat->err.column = GML_column;
				gmlparser_free(pair);

				if (tmp == NULL) {
					return NULL;
				} else {
					tmp->next = NULL;
					return list;
				}
			}

			break;

		} else if (token.kind == GML_R_BRACKET) {
			if (!open) {
				stat->err.err_num = GML_TOO_MANY_BRACKETS;
				stat->err.line = GML_line;
				stat->err.column = GML_column;
				gmlparser_free(pair);

				if (tmp == NULL) {
					return NULL;
				} else {
					tmp->next = NULL;
					return list;
				}
			}

			break;

		} else if (token.kind == GML_ERROR) {
			stat->err.err_num = token.value.err.err_num;
			stat->err.line = token.value.err.line;
			stat->err.column = token.value.err.column;
			gmlparser_free(pair);

			if (tmp == NULL) {
				return NULL;
			} else {
				tmp->next = NULL;
				return list;
			}

		} else if (token.kind != GML_KEY) {
			stat->err.err_num = GML_SYNTAX;
			stat->err.line = GML_line;
			stat->err.column = GML_column;
			gmlparser_free(pair);

			if (token.kind == GML_STRING) {
				gmlparser_free(token.value.string);
			}

			if (tmp == NULL) {
				return NULL;
			} else {
				tmp->next = NULL;
				return list;
			}
		}

		if (!stat->key_list) {
			stat->key_list = (struct GML_list_elem *)
			    gmlparser_calloc((size_t)1, sizeof(struct GML_list_elem));
			stat->key_list->next = NULL;
			stat->key_list->key = token.value.string;
			pair->key = token.value.string;

		} else {
			tmp_elem = stat->key_list;

			while (tmp_elem) {
				if (!strcmp(tmp_elem->key, token.value.string)) {
					gmlparser_free(token.value.string);
					pair->key = tmp_elem->key;

					break;
				}

				tmp_elem = tmp_elem->next;
			}

			if (!tmp_elem) {
				/* #warning "memleak here " */
				tmp_elem = (struct GML_list_elem *)
				    gmlparser_calloc((size_t)1, sizeof(struct GML_list_elem));
				tmp_elem->next = stat->key_list;
				stat->key_list = tmp_elem;
				tmp_elem->key = token.value.string;
				pair->key = token.value.string;
			}
		}

		token = GML_scanner(source);

		switch (token.kind) {
		case GML_KEY:	/* unused */
			break;
		case GML_R_BRACKET:	/* unused */
			break;
		case GML_END:	/* unused */
			break;
		case GML_LIST:	/* unused */
			break;

		case GML_INT:
			pair->kind = GML_INT;
			pair->value.integer = token.value.integer;
			break;

		case GML_DOUBLE:
			pair->kind = GML_DOUBLE;
			pair->value.floating = token.value.floating;
			break;

		case GML_STRING:
			pair->kind = GML_STRING;
			pair->value.string = token.value.string;
			break;

		case GML_L_BRACKET:
			pair->kind = GML_LIST;
			pair->value.list = GML_parser(source, stat, 1);

			if (stat->err.err_num != GML_OK) {
				return list;
			}

			break;

		case GML_ERROR:
			stat->err.err_num = token.value.err.err_num;
			stat->err.line = token.value.err.line;
			stat->err.column = token.value.err.column;
			gmlparser_free(pair);

			if (tmp == NULL) {
				return NULL;
			} else {
				tmp->next = NULL;
				return list;
			}

		default:
			stat->err.line = GML_line;
			stat->err.column = GML_column;
			stat->err.err_num = GML_SYNTAX;
			gmlparser_free(pair);

			if (tmp == NULL) {
				return NULL;
			} else {
				tmp->next = NULL;
				return list;
			}
		}

		tmp = pair;
		pair = (struct GML_pair *)gmlparser_calloc((size_t)1, sizeof(struct GML_pair));
		tmp->next = pair;
	}

	stat->err.err_num = GML_OK;
	gmlparser_free(pair);

	if (tmp == NULL) {
		return NULL;
	} else {
		tmp->next = NULL;
		return list;
	}
}

void GML_free_list(struct GML_pair *list, struct GML_list_elem *keys)
{
	if (list) {
	}
	if (keys) {
	}

	/* old now replaced using splaytree
	   struct GML_pair *tmp = list;
	   struct GML_list_elem *tmp_key;

	   while (keys)
	   {
	   gmlparser_free (keys->key);
	   tmp_key = keys->next;
	   gmlparser_free (keys);
	   keys = tmp_key;
	   }

	   while (list)
	   {

	   switch (list->kind)
	   {
	   case GML_LIST:
	   GML_free_list (list->value.list, NULL);
	   break;

	   case GML_STRING:
	   gmlparser_free (list->value.string);
	   break;

	   default:
	   break;
	   }

	   tmp = list->next;
	   gmlparser_free (list);
	   list = tmp;
	   }
	 */

	gmlparser_splaytree = splay_tree_delete(gmlparser_splaytree);

	return;
}

void GML_print_list(struct GML_pair *list, int level)
{
	struct GML_pair *tmp = list;
	int i;

	while (tmp) {

		for (i = 0; i < level; i++) {
			printf("    ");
		}

		printf("*KEY* : %s", tmp->key);

		switch (tmp->kind) {

		case GML_INT:
			printf("  *VALUE* (long) : %ld \n", tmp->value.integer);
			break;

		case GML_DOUBLE:
			printf("  *VALUE* (double) : %f \n", tmp->value.floating);
			break;

		case GML_STRING:
			printf("  *VALUE* (string) : %s \n", tmp->value.string);
			break;

		case GML_LIST:
			printf("  *VALUE* (list) : \n");
			GML_print_list(tmp->value.list, level + 1);
			break;

		case GML_KEY:
			printf("Unexpected \n");
			break;
		case GML_L_BRACKET:
			printf("Unexpected \n");
			break;
		case GML_R_BRACKET:
			printf("Unexpected \n");
			break;
		case GML_END:
			printf("Unexpected \n");
			break;
		case GML_ERROR:
			printf("Unexpected \n");
			break;

		default:
			printf("Unknown kind %u\n", tmp->kind);
			break;
		}

		tmp = tmp->next;
	}

	return;
}

/* memory wrapping */
void gmlparser_free(void *ptr)
{
	if (ptr) {
		splay_tree_remove(gmlparser_splaytree, (splay_tree_value) ptr);
	}
	return;
}

/* tracking memory allocations in the splay */
void *gmlparser_calloc(size_t nn, size_t sz)
{
	void *ret;
	ret = dp_calloc((size_t)1, (nn * sz));
	if (gmlparser_splaytree == NULL) {
		gmlparser_splaytree = splay_tree_new(splay_tree_compare_pointers, splay_tree_free_key, NULL);
	}
	splay_tree_insert(gmlparser_splaytree, (splay_tree_key) ret, (splay_tree_value) 0);
	return (ret);
}

/************* customize after this **************/

/* parse a list with edge list unknown */
static void GT_parse_list_edge_list(struct GML_pair *pairs)
{
	if (pairs) {
	}
	return;
}

/* parse a list with edge graphics */
static struct edgegr *GT_parse_list_edge_graphics(struct GML_pair *pairs)
{
	struct edgegr *egr;
	int n = 0;
	unsigned int red = 0;
	unsigned int green = 0;
	unsigned int blue = 0;
	int ecolor = 0;
	int foundecolor = 0;
	int pe = 0;

	ecolor = -1;
	foundecolor = 0;
	egr = NULL;

	while (pairs) {

		switch (pairs->kind) {
		case GML_KEY:	/* unused */
			break;
		case GML_L_BRACKET:	/* unused */
			break;
		case GML_R_BRACKET:	/* unused */
			break;
		case GML_END:	/* unused */
			break;
		case GML_ERROR:	/* unused */
			break;

		case GML_INT:
			break;

		case GML_DOUBLE:
			break;

		case GML_STRING:
			/* color of edge */
			if (strcasecmp(pairs->key, "fill") == 0) {
				/* option here to allow agrb too */
				pe = 0;
				if (strlen(pairs->value.string) == 7) {
					n = sscanf(pairs->value.string, "#%02x%02x%02x", &red, &green, &blue);
					if (n != 3) {
						pe = 1;
					}
				} else if (strlen(pairs->value.string) == 5) {
					red = 0;
					n = sscanf(pairs->value.string, "#%02x%02x", &green, &blue);
					if (n != 2) {
						pe = 1;
					}
				} else if (strlen(pairs->value.string) == 3) {
					red = 0;
					green = 0;
					n = sscanf(pairs->value.string, "#%02x", &blue);
					if (n != 1) {
						pe = 1;
					}
				} else {
					pe = 1;
				}

				if (pe == 0) {
					ecolor = (int)(((red << 16) | (green << 8) | blue));
					foundecolor = 1;
				} else {
					printf
					    ("gml %s(): cannot parse edge fillcolor \"%s\" and expected #rrggbb\n",
					     __func__, pairs->value.string);
				}

			}
			break;

		case GML_LIST:
			break;

		default:
			printf("gml %s(): shouldnothappen\n", __func__);
			break;
		}

		pairs = pairs->next;
	}

	if (foundecolor) {
		egr = dp_calloc((size_t)1, sizeof(struct edgegr));
		egr->foundecolor = foundecolor;
		egr->ecolor = ecolor;
		return (egr);
	} else {
		return (NULL);
	}
}

/* edge data list */
static void GT_parse_list_edge(struct gml_graph *g, struct GML_pair *pairs)
{
	int foundsource = -1;
	int foundtarget = -1;
	int foundsourceset = 0;
	int foundtargetset = 0;
	char *elabel = NULL;
	struct edgegr *egr = NULL;
	int ecolor = 0;
	char *strtolhelp = NULL;
	long int rs = 0;
	struct gml_node *fnn = 0;
	struct gml_node *tnn = 0;

	ecolor = 0;		/* black edge line */

	foundsource = -1;
	foundtarget = -1;
	foundsourceset = 0;
	foundtargetset = 0;

	egr = NULL;		/* optional edge graphics */
	elabel = NULL;		/* optional edge label */

	while (pairs) {
		switch (pairs->kind) {
		case GML_KEY:	/* unused */
			break;
		case GML_L_BRACKET:	/* unused */
			break;
		case GML_R_BRACKET:	/* unused */
			break;
		case GML_END:	/* unused */
			break;
		case GML_ERROR:	/* unused */
			break;

		case GML_INT:
			if (strcasecmp(pairs->key, "source") == 0) {
				foundsource = (int)pairs->value.integer;
				foundsourceset++;
			}
			if (strcasecmp(pairs->key, "target") == 0) {
				foundtarget = (int)pairs->value.integer;
				foundtargetset++;
			}
			break;

		case GML_DOUBLE:
			break;

		case GML_STRING:
			if (strcasecmp(pairs->key, "source") == 0) {
				errno = 0;
				rs = strtol(pairs->value.string, &strtolhelp, 10);
				if (errno || (*strtolhelp) != 0) {
					/* error in number */
					printf("gml %s(): string found source id but expecting a number and skipped\n", __func__);
				} else {
					foundsource = (int)rs;
					foundsourceset++;
				}
			}
			if (strcasecmp(pairs->key, "target") == 0) {
				errno = 0;
				rs = strtol(pairs->value.string, &strtolhelp, 10);
				if (errno || (*strtolhelp) != 0) {
					/* error in number */
					printf("gml %s(): string found target id but expecting a number and skipped\n", __func__);
				} else {
					foundtarget = (int)rs;
					foundtargetset++;
				}
			}
			if (strcasecmp(pairs->key, "label") == 0) {
				elabel = uniqstr(pairs->value.string);
			}
			break;

		case GML_LIST:
			if (strcasecmp(pairs->key, "graphics") == 0) {
				egr = GT_parse_list_edge_graphics(pairs->value.list);
			} else {
				GT_parse_list_edge_list(pairs->value.list);
			}
			break;

		default:
			printf("gml %s(): shouldnothappen\n", __func__);
			break;
		}

		/* see if a return from graphics */
		if (egr) {

			if (egr->foundecolor) {
				ecolor = egr->ecolor;
			}
			egr = dp_free(egr);
			if (egr) {
			}
		}

		pairs = pairs->next;
	}

	/* a edge must have source and target */
	if (foundsourceset == 0 || foundtargetset == 0) {
		printf
		    ("gml %s(): edge missing a source and/or target number in edge from %d to %d and skipped\n",
		     __func__, foundsource, foundtarget);
		fflush(stdout);
		return;
	}

	/* check for exactly 1 source and target id in edge,
	 * this could be a (interesting) feature too. */
	if (foundsourceset > 1) {
		printf
		    ("gml %s(): edge has multiple source id's in edge from %d to %d and skipped\n", __func__, foundsource,
		     foundtarget);
		fflush(stdout);
		return;
	}

	if (foundtargetset > 1) {
		printf
		    ("gml %s(): edge has multiple target id's in edge from %d to %d and skipped\n", __func__, foundsource,
		     foundtarget);
		fflush(stdout);
		return;
	}

	/* this happens in radare2 gml data -- todo */
	if (foundsource < 0) {
		printf("gml %s(): edge has negative source number in edge from %d to %d\n", __func__, foundsource, foundtarget);
		fflush(stdout);
	}

	/* in radare2 data */
	if (foundtarget < 0) {
		printf("gml %s(): edge has negative target number in edge from %d to %d\n", __func__, foundsource, foundtarget);
		fflush(stdout);
	}

	if (foundsource == foundtarget) {
		/* at self edge increment count */
		fnn = uniqnodeid(NULL, foundsource);
		if (fnn) {
			fnn->nselfedges++;
		} else {
			printf("gml %s(): from-node not found in selfedge %d->%d\n", __func__, foundsource, foundtarget);
		}
	} else {
		fnn = uniqnodeid(NULL, foundsource);
		if (fnn == NULL) {
			printf("gml %s(): from-node not found in edge %d->%d\n", __func__, foundsource, foundtarget);
		}
		tnn = uniqnodeid(NULL, foundtarget);
		if (tnn == NULL) {
			printf("gml %s(): to-node not found in edge %d->%d\n", __func__, foundsource, foundtarget);
		}
		if (fnn && tnn) {
			add_new_edge(g, maingraph, fnn->nr, tnn->nr, elabel, ecolor, 0, NULL, NULL, 1, /* ishtml */ 0);
		}
	}

	return;
}

/* parse a list with node list unknown */
static void GT_parse_list_node_list(struct GML_pair *pairs)
{
	if (pairs) {
	}
	return;
}

/* parse a list with node labelgraphics */
static struct nodelgr *GT_parse_list_node_labelgraphics(struct GML_pair *pairs)
{
	struct nodelgr *nlgr = NULL;
	unsigned int red = 0;
	unsigned int green = 0;
	unsigned int blue = 0;
	int fontcolor = 0;
	int foundfontcolor = 0;
	int n = 0;
	char *t = NULL;
	int foundtext = 0;
	int pe = 0;		/* parse error flag */

	fontcolor = -1;
	foundfontcolor = 0;

	while (pairs) {

		switch (pairs->kind) {
		case GML_KEY:	/* unused */
			break;
		case GML_L_BRACKET:	/* unused */
			break;
		case GML_R_BRACKET:	/* unused */
			break;
		case GML_END:	/* unused */
			break;
		case GML_ERROR:	/* unused */
			break;

		case GML_INT:
			break;

		case GML_DOUBLE:
			break;

		case GML_STRING:
			/* color of font */
			if (strcasecmp(pairs->key, "color") == 0 || strcasecmp(pairs->key, "fill") == 0) {
				pe = 0;
				if (strlen(pairs->value.string) == 7) {
					n = sscanf(pairs->value.string, "#%02x%02x%02x", &red, &green, &blue);
					if (n != 3) {
						pe = 1;
					}
				} else if (strlen(pairs->value.string) == 5) {
					red = 0;
					n = sscanf(pairs->value.string, "#%02x%02x", &green, &blue);
					if (n != 2) {
						pe = 1;
					}
				} else if (strlen(pairs->value.string) == 3) {
					red = 0;
					green = 0;
					n = sscanf(pairs->value.string, "#%02x", &blue);
					if (n != 1) {
						pe = 1;
					}
				} else {
					pe = 1;
				}
				if (pe == 0) {
					fontcolor = (int)((red << 16) | (green << 8) | blue);
					foundfontcolor = 1;
				} else {
					printf
					    ("gml %s(): cannot parse node font color %s with %d elements\n",
					     __func__, pairs->value.string, n);
				}
			} else if (strcasecmp(pairs->key, "text") == 0) {
				t = uniqstr(pairs->value.string);
				foundtext = 1;
			} else {
				/* something else */
			}
			break;
		case GML_LIST:
			break;

		default:
			printf("gml %s(): shouldnothappen\n", __func__);
			break;
		}

		pairs = pairs->next;
	}

	if (foundtext || foundfontcolor) {
		nlgr = dp_calloc((size_t)1, sizeof(struct nodelgr));
		nlgr->foundfontcolor = foundfontcolor;
		nlgr->fontcolor = fontcolor;
		nlgr->foundtext = foundtext;
		nlgr->text = t;
		return (nlgr);
	} else {
		return (NULL);
	}
}

/* parse a list with node graphics */
static struct nodegr *GT_parse_list_node_graphics(struct GML_pair *pairs)
{
	struct nodegr *ngr = NULL;
	int n = 0;
	unsigned int red = 0;
	unsigned int green = 0;
	unsigned int blue = 0;
	int ncolor = 0;
	int foundncolor = 0;
	int nbcolor = 0;
	int foundnbcolor = 0;
	int pe = 0;

	ncolor = -1;
	foundncolor = 0;
	nbcolor = -1;
	foundnbcolor = 0;
	ngr = NULL;

	while (pairs) {

		switch (pairs->kind) {
		case GML_KEY:	/* unused */
			break;
		case GML_L_BRACKET:	/* unused */
			break;
		case GML_R_BRACKET:	/* unused */
			break;
		case GML_END:	/* unused */
			break;
		case GML_ERROR:	/* unused */
			break;

		case GML_INT:
			break;

		case GML_DOUBLE:
			break;

		case GML_STRING:
			/* background color of node */
			if (strcasecmp(pairs->key, "fill") == 0) {
				pe = 0;
				if (strlen(pairs->value.string) == 7) {
					n = sscanf(pairs->value.string, "#%02x%02x%02x", &red, &green, &blue);
					if (n != 3) {
						pe = 1;
					}
				} else if (strlen(pairs->value.string) == 5) {
					red = 0;
					n = sscanf(pairs->value.string, "#%02x%02x", &green, &blue);
					if (n != 2) {
						pe = 1;
					}
				} else if (strlen(pairs->value.string) == 3) {
					red = 0;
					green = 0;
					n = sscanf(pairs->value.string, "#%02x", &blue);
					if (n != 1) {
						pe = 1;
					}
				} else {
					pe = 1;
				}

				if (pe == 0) {
					ncolor = (int)((red << 16) | (green << 8) | blue);
					foundncolor = 1;
				} else {
					printf("gml %s(): cannot parse node background color %s\n", __func__, pairs->value.string);
				}

			}
			/* border color of node */
			if (strcasecmp(pairs->key, "outline") == 0) {
				pe = 0;
				if (strlen(pairs->value.string) == 7) {
					n = sscanf(pairs->value.string, "#%02x%02x%02x", &red, &green, &blue);
					if (n != 3) {
						pe = 1;
					}
				} else if (strlen(pairs->value.string) == 5) {
					red = 0;
					n = sscanf(pairs->value.string, "#%02x%02x", &green, &blue);
					if (n != 2) {
						pe = 1;
					}
				} else if (strlen(pairs->value.string) == 3) {
					red = 0;
					green = 0;
					n = sscanf(pairs->value.string, "#%02x", &blue);
					if (n != 1) {
						pe = 1;
					}
				} else {
					pe = 1;
				}
				if (pe == 0) {
					nbcolor = (int)((red << 16) | (green << 8) | blue);
					foundnbcolor = 1;
				} else {
					printf("gml %s(): cannot parse node bordercolor %s\n", __func__, pairs->value.string);
				}
			}
			break;

		case GML_LIST:
			break;

		default:
			printf("gml %s(): shouldnothappen\n", __func__);
			break;
		}

		pairs = pairs->next;
	}

	if (foundncolor || foundnbcolor) {
		ngr = dp_calloc((size_t)1, sizeof(struct nodegr));
		ngr->foundncolor = foundncolor;
		ngr->ncolor = ncolor;
		ngr->foundnbcolor = foundnbcolor;
		ngr->nbcolor = nbcolor;
		return (ngr);
	} else {
		return (NULL);
	}
}

static void GT_parse_list_node(struct gml_graph *g, struct GML_pair *pairs)
{
	int ncolor = 0;
	int nbcolor = 0;
	int foundid = -1;
	int foundidset = 0;
	char *nodelabel = NULL;
	char *nodename = NULL;
	struct nodegr *ngr = NULL;
	struct nodelgr *nlgr = NULL;
	char *strtolhelp = NULL;
	long int rs = 0;
	int fontcolor = 0;
	char buf[16];
	int nr = 0;

	/* node default white fill color r/g/b */
	ncolor = 0x00ffffff;
	/* node default border color is black */
	nbcolor = 0;
	fontcolor = 0;
	ngr = NULL;
	nlgr = NULL;

	foundid = -1;
	foundidset = 0;

	while (pairs) {
		switch (pairs->kind) {
		case GML_KEY:	/* unused */
			break;
		case GML_L_BRACKET:	/* unused */
			break;
		case GML_R_BRACKET:	/* unused */
			break;
		case GML_END:	/* unused */
			break;
		case GML_ERROR:	/* unused */
			break;

		case GML_INT:
			if (strcasecmp(pairs->key, "id") == 0) {
				foundid = (int)pairs->value.integer;
				foundidset++;
				memset(buf, 0, (size_t)16);
				snprintf(buf, (size_t)(16 - 1), "%d", foundid);
				nodename = uniqstr(buf);
			}
			break;

		case GML_DOUBLE:
			break;

		case GML_STRING:
			if (strcasecmp(pairs->key, "id") == 0) {
				nodename = uniqstr(pairs->value.string);
				errno = 0;
				rs = strtol(pairs->value.string, &strtolhelp, (int)10);
				if (errno || (*strtolhelp) != 0) {
					/* error in number */
					printf("gml %s(): string found at id but expecting a number and skipped\n", __func__);
				} else {
					foundid = (int)rs;
					foundidset++;
				}
			}
			/* if multiple label statements, it's overwritten without warning */
			if (strcasecmp(pairs->key, "label") == 0) {
				nodelabel = uniqstr(pairs->value.string);
			}
			/* instead of label, gv2gml uses name */
			if (strcasecmp(pairs->key, "name") == 0) {
				nodelabel = uniqstr(pairs->value.string);
			}
			break;

		case GML_LIST:
			if (strcasecmp(pairs->key, "graphics") == 0) {
				ngr = GT_parse_list_node_graphics(pairs->value.list);
			} else if (strcasecmp(pairs->key, "labelgraphics") == 0) {
				nlgr = GT_parse_list_node_labelgraphics(pairs->value.list);
			} else {
				GT_parse_list_node_list(pairs->value.list);
			}
			break;

		default:
			printf("gml %s(): shouldnothappen\n", __func__);
			break;
		}

		/* see if a return from graphics */
		if (ngr) {

			/* optional node background color */
			if (ngr->foundncolor) {
				ncolor = ngr->ncolor;
			}

			/* optional node border color */
			if (ngr->foundnbcolor) {
				nbcolor = ngr->nbcolor;
			}

			ngr = dp_free(ngr);
			if (ngr) {
			}
		}

		/* see if a return from labelgraphics */
		if (nlgr) {
			if (nlgr->foundfontcolor) {
				fontcolor = nlgr->fontcolor;
			}
			if (nlgr->foundtext) {
				nodelabel = nlgr->text;
			}
			nlgr = dp_free(nlgr);
			if (nlgr) {
			}
		}

		pairs = pairs->next;
	}

	/* a node must have a id number */
	if (foundidset == 0) {
		printf("gml %s(): node missing a id number and skipped\n", __func__);
		fflush(stdout);
		return;
	}

	/* a node must have a single id number. this can be a feature too. */
	if (foundidset > 1) {
		printf("gml %s(): node has multiple id numbers and skipped\n", __func__);
		fflush(stdout);
		return;
	}

	/* happens in radare2 data */
	if (foundid < 0) {
		printf("gml %s(): node with negative id found in node %d\n", __func__, foundid);
		fflush(stdout);
	}

	/* todo last arg is int fontcolor */

	/* uniq node number start at 1 */
	maingraph->nodenum++;
	nr = maingraph->nodenum;

	/* in ogdf gml label "" set the nodename */
	if (nodelabel) {
		if (strlen(nodelabel) == 0) {
			/* make nodelabel nodename */
			nodelabel = nodename;
		}
	}

	/* in gml all nodes are located in rootgraph */
	add_new_node(g, maingraph, nr, foundid, nodename, nodelabel, ncolor, nbcolor, NULL /* rl */ , NULL /* hl */ , fontcolor,
		     /* ishtml */ 0);

	return;
}

static void GT_parse_list(struct gml_graph *g, struct GML_pair *pairs)
{

	while (pairs) {

		switch (pairs->kind) {
		case GML_KEY:	/* unused */
			break;
		case GML_L_BRACKET:	/* unused */
			break;
		case GML_R_BRACKET:	/* unused */
			break;
		case GML_END:	/* unused */
			break;
		case GML_ERROR:	/* unused */
			break;

		case GML_INT:
			break;

		case GML_DOUBLE:
			break;

		case GML_STRING:
			break;

		case GML_LIST:
			if (strcasecmp(pairs->key, "node") == 0) {
				GT_parse_list_node(g, pairs->value.list);
			} else if (strcasecmp(pairs->key, "edge") == 0) {
				GT_parse_list_edge(g, pairs->value.list);
			} else {
				GT_parse_list(g, pairs->value.list);
			}
			break;

		default:
			printf("gml %s(): shouldnothappen\n", __func__);
			break;
		}

		pairs = pairs->next;
	}

	return;
}

int gmlparse(struct gml_graph *g, gzFile f, char *fname)
{
	struct GML_pair *data = NULL;
	struct GML_stat *status = NULL;

	status = dp_calloc((size_t)1, sizeof(struct GML_stat));
	memset(parsermessage, 0, (size_t)256);

	data = GML_parser(f, status, 0);

	if (status->err.err_num != GML_OK) {
		/* parsed not oke */
		switch (status->err.err_num) {
		case GML_UNEXPECTED:
			snprintf(parsermessage, (size_t)(256 - 1),
				 "gml %s(): unexpected error near line %u:%u file %s",
				 __func__, status->err.line, status->err.column, fname);
			break;
		case GML_SYNTAX:
			snprintf(parsermessage, (size_t)(256 - 1),
				 "gml %s(): syntax error near line %u:%u file %s", __func__, status->err.line, status->err.column,
				 fname);
			break;
		case GML_PREMATURE_EOF:
			snprintf(parsermessage, (size_t)(256 - 1),
				 "gml %s(): early end of file near line %u:%u file %s",
				 __func__, status->err.line, status->err.column, fname);
			break;
		case GML_TOO_MANY_DIGITS:
			snprintf(parsermessage, (size_t)(256 - 1),
				 "gml %s(): too many digits near line %u:%u file %s",
				 __func__, status->err.line, status->err.column, fname);
			break;
		case GML_OPEN_BRACKET:
			snprintf(parsermessage, (size_t)(256 - 1),
				 "gml %s(): open bracket error near line %u:%u file %s",
				 __func__, status->err.line, status->err.column, fname);
			break;
		case GML_TOO_MANY_BRACKETS:
			snprintf(parsermessage, (size_t)(256 - 1),
				 "%s(gmlparser)(): too many brackets near line %u:%u file %s",
				 __func__, status->err.line, status->err.column, fname);
			break;
		case GML_OK:
			/* parsed oke and no message */
			break;
		default:
			snprintf(parsermessage, (size_t)(256 - 1),
				 "gml %s(): unknown error near line %u:%u file %s", __func__, status->err.line, status->err.column,
				 fname);
			break;
		}

		/* in the gui in a message dialog */
		printf("gml %s(): gml-parsermessage: `%s'\n", __func__, parsermessage);
		fflush(stdout);
	}

	if (0) {
		GML_print_list(data, 0);
	}

	GT_parse_list(g, data);

	GML_free_list(data, 0);
	if (status) {
		status = dp_free(status);
		if (status) {
		}
	}

	if (strlen(parsermessage)) {
		/* parse error status */
		return (1);
	} else {
		/* oke status */
		return (0);
	}

	return (0);
}

/* end */
