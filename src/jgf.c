
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
 *
 * SPDX-License-Identifier: GPL-3.0+
 * License-Filename: LICENSE
 */

/* parse jgf json graph data using json.c */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splay-tree.h"
#include "main.h"
#include "hier.h"
#include "uniqnode.h"
#include "uniqstr.h"
#include "jgf.h"
#include "json.h"
#include "dpmem.h"

/* update sizes */
#undef LIBJSON_DEFAULT_STACK_SIZE
#undef LIBJSON_DEFAULT_BUFFER_SIZE
#define LIBJSON_DEFAULT_STACK_SIZE (4*256)
#define LIBJSON_DEFAULT_BUFFER_SIZE (4*4096)

static splay_tree jgftree = NULL;

/* no errors */
static int jgferror = 0;

/* debug option */
static int jgfdebug = 0;

static char *jgfstring_of_errors[] = {
	[JSON_ERROR_NO_MEMORY] = "out of memory",
	[JSON_ERROR_BAD_CHAR] = "bad character",
	[JSON_ERROR_POP_EMPTY] = "stack empty",
	[JSON_ERROR_POP_UNEXPECTED_MODE] = "pop unexpected mode",
	[JSON_ERROR_NESTING_LIMIT] = "nesting limit",
	[JSON_ERROR_DATA_LIMIT] = "data limit",
	[JSON_ERROR_COMMENT_NOT_ALLOWED] = "comment not allowed by config",
	[JSON_ERROR_UNEXPECTED_CHAR] = "unexpected char",
	[JSON_ERROR_UNICODE_MISSING_LOW_SURROGATE] = "missing unicode low surrogate",
	[JSON_ERROR_UNICODE_UNEXPECTED_LOW_SURROGATE] = "unexpected unicode low surrogate",
	[JSON_ERROR_COMMA_OUT_OF_STRUCTURE] = "error comma out of structure",
	[JSON_ERROR_CALLBACK] = "error in a callback",
	[JSON_ERROR_UTF8] = "utf8 validation error"
};

static void jgfparse_clear(void)
{
	if (jgftree) {
		jgftree = splay_tree_delete(jgftree);
	}
	return;
}

static int jgfprocess_file(json_parser * parser, FILE * input, int *retlines, int *retcols)
{
	char buffer[(32 * 1024)];
	int ret = 0;
	int32_t read = 0;
	int lines = 0;
	int col = 0;
	uint32_t i = 0;
	uint32_t processed = 0;

	lines = 1;
	col = 0;
	while (1) {
		read = fread(buffer, 1, (32 * 1024), input);
		if (read <= 0) {
			/* eof */
			break;
		}
		ret = json_parser_string(parser, buffer, read, &processed);
		for (i = 0; i < processed; i++) {
			if (buffer[i] == '\n') {
				col = 0;
				lines++;
			} else {
				col++;
			}
		}
		if (ret) {
			/* at parse error stop. */
			break;
		}
	}
	if (retlines) {
		*retlines = lines;
	}
	if (retcols) {
		*retcols = col;
	}
	return ret;
}

#define MODE_NONE 0
#define MODE_INGRAPH 1
#define MODE_INNODE 2
#define MODE_INEDGE 3

static int nkeys = 0;

static int nodenr = 0;
static char *nodelabel = NULL;
static char *nodename = NULL;

static char *fn = NULL;
static char *tn = NULL;
static int inesource = 0;
static int inetarget = 0;
static int inelabel = 0;
static char *elabel = NULL;

static int inlabel = 0;

static int mode = 0;

static struct gml_graph *curg = NULL;

static void jgfaddnode(char *nnodename, int nr)
{
	splay_tree_node node1 = NULL;
	node1 = splay_tree_lookup(jgftree, (splay_tree_key) nnodename);
	if (node1) {
		printf("%s(): node \"%s\" did already exist\n", __func__, nnodename);
		return;
	}
	if (jgfdebug || 0) {
		printf("%s(): adding node \"%s\"\n", __func__, nnodename);
	}
	splay_tree_insert(jgftree, (splay_tree_key) nnodename, (splay_tree_value) nr);
	return;
}

static void do_string(char *str)
{
	if (mode == MODE_INNODE) {
		if (inlabel) {
			nodelabel = uniqstr(str);
			inlabel = 0;
		}
	} else if (mode == MODE_INEDGE) {
		if (inelabel) {
			elabel = uniqstr(str);
			inelabel = 0;
		}
		if (inesource) {
			fn = uniqstr(str);
			inesource = 0;
		}
		if (inetarget) {
			tn = uniqstr(str);
			inetarget = 0;
		}
	} else {

	}
	return;
}

static void do_data(void)
{
	struct gml_node *fnn = NULL;
	struct gml_node *tnn = NULL;
	/* struct gml_node *nn = NULL; todo */
	splay_tree_node node1 = NULL;
	splay_tree_node node2 = NULL;
	char *ns = NULL;

	if (jgftree == NULL) {
		jgftree = splay_tree_new(splay_tree_compare_strings, NULL, NULL);
	}

	if (mode == MODE_INEDGE) {
		if (fn && tn) {
			/* if from or to node name does not exist yet, add it as nodes */
			node1 = splay_tree_lookup(jgftree, (splay_tree_key) fn);
			if (node1 == NULL) {
				printf("%s(): from \"%s\" did not exist\n", __func__, fn);
				/* uniq node number starting at 1 */
				maingraph->nodenum++;
				nodenr = maingraph->nodenum;
				ns = uniqstr(fn);
				jgfaddnode(ns, nodenr);
				add_new_node(curg, maingraph, nodenr, /* pvnl->nr */ (-1), ns, ns, /* ncolor */ 0x00ffffff, /* nbcolor */ 0,	/* rlabel */
					     NULL, /* hlabel */ NULL, /* fontcolor */ 0, /* ishtml */ 0);
			}
			node1 = splay_tree_lookup(jgftree, (splay_tree_key) fn);
			fnn = uniqnode(curg, node1->value);
			/* */
			node2 = splay_tree_lookup(jgftree, (splay_tree_key) tn);
			if (node2 == NULL) {
				printf("%s(): to \"%s\" did not exist\n", __func__, tn);

				/* uniq node number starting at 1 */
				maingraph->nodenum++;
				nodenr = maingraph->nodenum;
				ns = uniqstr(tn);
				jgfaddnode(ns, nodenr);
				add_new_node(curg, maingraph, nodenr, /* pvnl->nr */ (-1), ns, ns, /* ncolor */ 0x00ffffff, /* nbcolor */ 0,	/* rlabel */
					     NULL, /* hlabel */ NULL, /* fontcolor */ 0, /* ishtml */ 0);
			}
			node2 = splay_tree_lookup(jgftree, (splay_tree_key) tn);
			tnn = uniqnode(curg, node2->value);
			if (fnn && tnn) {
				if (fnn == tnn) {
					/* add selfedge count at this node */
					fnn->nselfedges++;
				} else {
					add_new_edge(curg, maingraph, /* foundsource */ fnn->nr, /* foundtarget */ tnn->nr,
						     elabel,
						     /* ecolor */ 0, /* style */ 0, /* fcompass */ NULL, /* tcompass */ NULL,
						     /* constraint */ 1, /* ishtml */ 0);
				}
			}
		}
		fn = NULL;
		tn = NULL;
		elabel = NULL;
	}
	if (mode == MODE_INNODE) {
		if (nodename) {
			node1 = splay_tree_lookup(jgftree, (splay_tree_key) nodename);
			if (jgfdebug || 0) {
				printf("%s(): %p for node name %s\n", __func__, (void *)node1, nodename);
			}
			/* */
			if (node1 == NULL) {
				/* add new node with uniq node number starting at 1 */
				maingraph->nodenum++;
				nodenr = maingraph->nodenum;
				/* in jgf all nodes are located in rootgraph
				 * use -1 for foundid then gml id check is not applied.
				 */
				if (nodelabel == NULL) {
					nodelabel = nodename;
				}
				jgfaddnode(nodename, nodenr);
				add_new_node(curg, maingraph, nodenr, /* pvnl->nr */ (-1), nodename, nodelabel, /* ncolor */ 0x00ffffff, /* nbcolor */ 0,	/* rlabel */
					     NULL, /* hlabel */ NULL, /* fontcolor */ 0, /* ishtml */ 0);
			}
			/* */
		}
		nodename = NULL;
		nodelabel = NULL;
	}
	return;
}

static int do_key(char *str)
{
	if (jgfdebug || 0) {
		printf("%s(): key=\"%s\" mode=%d\n", __func__, str, mode);
	}
	if (strcmp(str, "graph") == 0) {
		mode = MODE_INGRAPH;
		return (0);
	}
	if (strcmp(str, "graphs") == 0) {
		mode = MODE_INGRAPH;
		return (0);
	}
	if (nkeys == 0) {
		if (mode == MODE_NONE) {
			/* error first key should have been a graph or graphs */
			return (JSON_ERROR_UNEXPECTED_CHAR);
		}
	}
	nkeys++;
	/* skip all data until graph seen */
	if (mode == MODE_NONE) {
		return (0);
	}
	if (strcmp(str, "nodes") == 0) {
		mode = MODE_INNODE;
		return (0);
	}
	if (strcmp(str, "edges") == 0) {
		mode = MODE_INEDGE;
		return (0);
	}
	if (mode == MODE_INNODE) {
		if (strcmp(str, "label") == 0) {
			nodelabel = NULL;
			inlabel = 1;
		} else if (strcmp(str, "id") == 0) {
		} else if (strcmp(str, "metadata") == 0) {
		} else if (strcmp(str, "fillcolor") == 0) {
		} else if (strcmp(str, "bordercolor") == 0) {
		} else if (strcmp(str, "fontcolor") == 0) {
		} else {
			nodename = uniqstr(str);
		}
	} else if (mode == MODE_INEDGE) {
		if (strcmp(str, "source") == 0) {
			inesource = 1;
		} else if (strcmp(str, "target") == 0) {
			inetarget = 1;
		} else if (strcmp(str, "relation") == 0) {
		} else if (strcmp(str, "label") == 0) {
			inelabel = 1;
		} else {
		}
	} else {
	}
	return (0);
}

static int my_callback(void *userdata, int type, const char *data, uint32_t length)
{
	int status = 0;
	FILE *output = (userdata) ? userdata : stdout;
	switch (type) {
	case JSON_OBJECT_BEGIN:
		if (jgfdebug || 0) {
			fprintf(output, "entering %s\n", (type == JSON_ARRAY_BEGIN) ? "array" : "object");
		}
		break;

	case JSON_ARRAY_BEGIN:
		if (jgfdebug || 0) {
			fprintf(output, "entering %s\n", (type == JSON_ARRAY_BEGIN) ? "array" : "object");
		}
		break;

	case JSON_OBJECT_END:
		if (jgfdebug || 0) {
			fprintf(output, "leaving %s\n", (type == JSON_ARRAY_END) ? "array" : "object");
		}
		do_data();
		break;

	case JSON_ARRAY_END:
		if (jgfdebug || 0) {
			fprintf(output, "leaving %s\n", (type == JSON_ARRAY_END) ? "array" : "object");
		}
		break;

	case JSON_KEY:
		if (jgfdebug || 0) {
			fprintf(output, "value \"%*s\" key\n", length, data);
		}
		status = do_key((char *)data);
		if (jgfdebug || 0) {
			printf("%d status\n", status);
		}
		break;

	case JSON_STRING:
		if (jgfdebug || 0) {
			fprintf(output, "value \"%*s\" string\n", length, data);
		}
		do_string((char *)data);
		break;

	case JSON_INT:
		if (jgfdebug || 0) {
			fprintf(output, "value \"%*s\" int\n", length, data);
		}
		break;

	case JSON_FLOAT:
		if (jgfdebug || 0) {
			fprintf(output, "value \"%*s\" float\n", length, data);
		}
		break;
	case JSON_NULL:
		if (jgfdebug || 0) {
			fprintf(output, "constant null\n");
		}
		break;
	case JSON_TRUE:
		if (jgfdebug || 0) {
			fprintf(output, "constant true\n");
		}
		break;
	case JSON_FALSE:
		if (jgfdebug || 0) {
			fprintf(output, "constant false\n");
		}
		break;
	default:
		/* shouldnothappen */
		printf("%s(): in default\n", __func__);
		break;
	}
	return (status);
}

/* */
int jgfparse(struct gml_graph *g, FILE * jgfinput, char *fname, char *argv0)
{
	json_config jgfconfig;
	json_parser jgfparser;
	int ret = 0;
	int jgfcol = 0;
	int jgflines = 0;

	/* todo make a parse tree first. */

	nkeys = 0;

	curg = g;

	mode = MODE_NONE;

	/* no errors */
	jgferror = 0;

	memset(&jgfparser, 0, sizeof(json_parser));
	memset(&jgfconfig, 0, sizeof(json_config));

	/* read buffer size */
	jgfconfig.buffer_initial_size = LIBJSON_DEFAULT_BUFFER_SIZE;

	/* unlimited {} nesting */
	jgfconfig.max_nesting = 0;

	/* max. allowed memory usage */
	jgfconfig.max_data = 0;

	/* allow c style comments */
	jgfconfig.allow_c_comments = 1;

	/* allow yaml # style coments */
	jgfconfig.allow_yaml_comments = 1;

	/* wrap to own dpmem.c calloc/realloc/free */
	jgfconfig.user_calloc = dp_calloc;
	jgfconfig.user_realloc = dp_realloc;
	jgfconfig.user_free = dp_free;

	jgfdebug = 0;

	/* */
	if (strcmp(argv0, "gml4gtkd") == 0) {
		/* debug option */
		jgfdebug = 1;
	} else {
		/* debug option */
		jgfdebug = 0;
	}

	ret = json_parser_init(&jgfparser, &jgfconfig, &my_callback, /* (void *)userdata */ NULL);

	if (ret) {
		/* shouldnothappen */
	}

	/* parse */
	ret = jgfprocess_file(&jgfparser, jgfinput, &jgflines, &jgfcol);

	if (ret) {
		fprintf(stderr, "jgf %s(): parse error at line %d, col %d code=%d %s in file %s\n", __func__, jgflines, jgfcol, ret,
			jgfstring_of_errors[ret], fname);
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "jgf %s(): parse error at line %d, col %d code=%d %s in file %s\n", __func__,
			 jgflines, jgfcol, ret, jgfstring_of_errors[ret], fname);
		jgfparse_clear();
		json_parser_free(&jgfparser);
		return (1);
	}

	ret = json_parser_is_done(&jgfparser);

	if (ret == 0) {
		/* parser is not in final state */
		fprintf(stderr, "jgf %s(): is_done parse error at line %d, col %d code=%d %s in file %s\n", __func__, jgflines,
			jgfcol, ret, jgfstring_of_errors[ret], fname);
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "jgf %s(): is_done parse error at line %d, col %d code=%d %s in file %s\n",
			 __func__, jgflines, jgfcol, ret, jgfstring_of_errors[ret], fname);
		jgfparse_clear();
		json_parser_free(&jgfparser);
		return (1);
	}

	jgfparse_clear();

	json_parser_free(&jgfparser);

	/* parsed oke. */
	return (0);
}

/* end. */
