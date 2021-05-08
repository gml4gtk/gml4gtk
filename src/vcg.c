
/*
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

/* parse the vcg data generated with gcc -fcallgraph-info option which is a subset of vcg language.
 * for other vcg data this file must be updated.
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splay-tree.h"
#include "main.h"
#include "hier.h"
#include "uniqnode.h"
#include "uniqstr.h"
#include "vcg.h"
#include "vcgus.h"
#include "vcgun.h"
#include "vcg.yy.h"
#include "vcg.tab.h"
#include "dpmem.h"

/* like yydebug, set via lexer init */
int vcgdebug = 0;

/* current lexed token */
static int vcgtoken = 0;

/* set at parse error */
static int vcgerror = 0;

/* nodes list */
static struct vcgn *vnl = NULL;
static struct vcgn *vnlend = NULL;

/* edges list */
static struct vcge *vel = NULL;
static struct vcge *velend = NULL;

/* graph title */
static char *graphtitle = NULL;

/* current file name */
static char *curfname = NULL;

/* uniq node number */
static int vcgnn = 0;

/* uniq edge number */
static int vcgen = 0;

/* clear edge list */
static void vel_clear(void)
{
	struct vcge *pvnl = NULL;
	struct vcge *pvnlnext = NULL;

	pvnl = vel;

	while (pvnl) {
		pvnlnext = pvnl->next;
		dp_free(pvnl);
		pvnl = NULL;
		pvnl = pvnlnext;
	}

	return;
}

/* clear node list */
static void vnl_clear(void)
{
	struct vcgn *pvnl = NULL;
	struct vcgn *pvnlnext = NULL;

	pvnl = vnl;

	while (pvnl) {
		pvnlnext = pvnl->next;
		dp_free(pvnl);
		pvnl = NULL;
		pvnl = pvnlnext;
	}

	return;
}

/* clear all at parse error */
static void vcgparse_clear(void)
{

	/* clear edge list */
	vel_clear();

	/* clear node list */
	vnl_clear();

	/* in vcg.l */
	vcg_lex_clear();

	/* node db */
	clear_vcguniqnode();

	/* uniq strings db */
	vcg_clear_uniqstr();

	/* no debug */
	vcgdebug = 0;

	/* current lexed token */
	vcgtoken = 0;

	/* set at parse error */
	vcgerror = 0;

	/* nodes list */
	vnl = NULL;
	vnlend = NULL;

	/* edges list */
	vel = NULL;
	velend = NULL;

	/* global graph title */
	graphtitle = NULL;

	/* current filename */
	curfname = NULL;

	/* uniq node number */
	vcgnn = 0;

	/* uniq edge number */
	vcgen = 0;

	return;
}

/* handle graph title statement */
static void vcggraphtitle(void)
{
	vcgtoken = vcglex();

	if (vcgtoken != VCG_COLON) {
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "vcg %s(): expected ':' after \"title\" at line %d in file %s\n", __func__,
			 vcglineno, curfname);
		vcgerror = 1;
		return;
	}

	vcgtoken = vcglex();

	if (vcgtoken != VCG_STRING) {
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "vcg %s(): expected string after \"title:\" at line %d in file %s\n", __func__,
			 vcglineno, curfname);
		vcgerror = 1;
		return;
	}

	graphtitle = vcglaststring;

	return;
}

/* handle a node statement */
static void vcgnode(void)
{
	int shape = 0;
	char *title = NULL;
	char *label = NULL;
	struct vcgn *newnode = NULL;

	vcgtoken = vcglex();

	if (vcgtoken != VCG_COLON) {
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "vcg %s(): expected ':' after \"node\" at line %d in file %s\n", __func__,
			 vcglineno, curfname);
		vcgerror = 1;
		return;
	}

	vcgtoken = vcglex();

	if (vcgtoken != VCG_BO) {
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "vcg %s(): expected '{' after \"node:\" at line %d in file %s\n", __func__,
			 vcglineno, curfname);
		vcgerror = 1;
		return;
	}

	for (;;) {
		if (vcgerror) {
			break;
		}

		vcgtoken = vcglex();

		if (vcgtoken == EOF) {
			memset(parsermessage, 0, 256);
			snprintf(parsermessage, (256 - 1), "vcg %s(): unexpected end-of-file in \"node:\" at line %d in file %s\n",
				 __func__, vcglineno, curfname);
			vcgerror = 1;
			break;
		}

		/* an brace close at end of node statement */
		if (vcgtoken == VCG_BC) {
			break;
		}

		if (vcgtoken == VCG_TITLE) {
			vcgtoken = vcglex();

			if (vcgtoken != VCG_COLON) {
				memset(parsermessage, 0, 256);
				snprintf(parsermessage, (256 - 1), "vcg %s(): expected ':' after \"title\" at line %d in file %s\n",
					 __func__, vcglineno, curfname);
				vcgerror = 1;
				break;
			}

			vcgtoken = vcglex();

			if (vcgtoken != VCG_STRING) {
				memset(parsermessage, 0, 256);
				snprintf(parsermessage, (256 - 1),
					 "vcg %s(): expected string after \"title:\" at line %d in file %s\n", __func__, vcglineno,
					 curfname);
				vcgerror = 1;
				break;
			}

			title = vcglaststring;
			vcglaststring = NULL;

		} else if (vcgtoken == VCG_LABEL) {
			vcgtoken = vcglex();

			if (vcgtoken != VCG_COLON) {
				memset(parsermessage, 0, 256);
				snprintf(parsermessage, (256 - 1), "vcg %s(): expected ':' after \"label\" at line %d in file %s\n",
					 __func__, vcglineno, curfname);
				vcgerror = 1;
				break;
			}
			vcgtoken = vcglex();

			if (vcgtoken != VCG_STRING) {
				memset(parsermessage, 0, 256);
				snprintf(parsermessage, (256 - 1),
					 "vcg %s(): expected string after \"label:\" at line %d in file %s\n", __func__, vcglineno,
					 curfname);
				vcgerror = 1;
				break;
			}

			label = vcglaststring;
			vcglaststring = NULL;

		} else if (vcgtoken == VCG_SHAPE) {
			vcgtoken = vcglex();

			if (vcgtoken != VCG_COLON) {
				memset(parsermessage, 0, 256);
				snprintf(parsermessage, (256 - 1), "vcg %s(): expected ':' after \"shape\" at line %d in file %s\n",
					 __func__, vcglineno, curfname);
				vcgerror = 1;
				break;
			}

			vcgtoken = vcglex();

			if (vcgtoken != VCG_ELLIPSE) {
				memset(parsermessage, 0, 256);
				snprintf(parsermessage, (256 - 1),
					 "vcg %s(): expected ellipse after \"shape:\" at line %d in file %s\n", __func__, vcglineno,
					 curfname);
				vcgerror = 1;
				break;
			}

			shape = 1;

		} else {
			memset(parsermessage, 0, 256);
			snprintf(parsermessage, (256 - 1), "vcg %s(): unknown node statement `%s' at line %d in file %s\n",
				 __func__, vcgtext, vcglineno, curfname);
			vcgerror = 1;
			break;
		}

	}

	if (vcgerror) {
		return;
	}

	if (title == NULL) {
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "vcg %s(): node has no \"title:\" statement at line %d in file %s\n", __func__,
			 vcglineno, curfname);
		vcgerror = 1;
	}

	/* when no label specified, use the node name */
	if (label == NULL) {
		label = title;
	}

	newnode = dp_calloc(1, sizeof(struct vcgn));

	if (newnode == NULL) {
		vcgerror = 1;
		return;
	}

	/* uniq node number starts at 1 */
	vcgnn++;

	newnode->nr = vcgnn;
	newnode->name = title;
	newnode->label = label;
	newnode->shape = shape;

	if (vnl == NULL) {
		vnl = newnode;
		vnlend = newnode;
	} else {
		vnlend->next = newnode;
		vnlend = newnode;
	}

	/* add node to db */
	vcguniqnode_add(newnode);

	return;
}

/* handle a edge statement */
static void vcgedge(void)
{
	struct vcge *newedge = NULL;
	char *sn = NULL;
	char *tn = NULL;
	char *label = NULL;

	vcgtoken = vcglex();

	if (vcgtoken != VCG_COLON) {
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "vcg %s(): expected ':' after \"edge\" at line %d in file %s\n", __func__,
			 vcglineno, curfname);
		vcgerror = 1;
		return;
	}

	vcgtoken = vcglex();

	if (vcgtoken != VCG_BO) {
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "vcg %s(): expected '{' after \"edge:\" at line %d in file %s\n", __func__,
			 vcglineno, curfname);
		vcgerror = 1;
		return;
	}

	for (;;) {
		if (vcgerror) {
			break;
		}

		vcgtoken = vcglex();

		if (vcgtoken == EOF) {
			memset(parsermessage, 0, 256);
			snprintf(parsermessage, (256 - 1), "vcg %s(): unexpected end-of-file in \"edge:\" at line %d in file %s\n",
				 __func__, vcglineno, curfname);
			vcgerror = 1;
			break;
		}

		/* an brace close at end of node statement */
		if (vcgtoken == VCG_BC) {
			break;
		}

		if (vcgtoken == VCG_SOURCENAME) {
			vcgtoken = vcglex();

			if (vcgtoken != VCG_COLON) {
				memset(parsermessage, 0, 256);
				snprintf(parsermessage, (256 - 1),
					 "vcg %s(): expected ':' after \"sourcename\" at line %d in file %s\n", __func__, vcglineno,
					 curfname);
				vcgerror = 1;
				break;
			}

			vcgtoken = vcglex();

			if (vcgtoken != VCG_STRING) {
				memset(parsermessage, 0, 256);
				snprintf(parsermessage, (256 - 1),
					 "vcg %s(): expected string after \"sourcename:\" at line %d in file %s\n", __func__,
					 vcglineno, curfname);
				vcgerror = 1;
				break;
			}

			sn = vcglaststring;
			vcglaststring = NULL;

		} else if (vcgtoken == VCG_TARGETNAME) {
			vcgtoken = vcglex();

			if (vcgtoken != VCG_COLON) {
				memset(parsermessage, 0, 256);
				snprintf(parsermessage, (256 - 1),
					 "vcg %s(): expected ':' after \"targetname\" at line %d in file %s\n", __func__, vcglineno,
					 curfname);
				vcgerror = 1;
				break;
			}

			vcgtoken = vcglex();

			if (vcgtoken != VCG_STRING) {
				memset(parsermessage, 0, 256);
				snprintf(parsermessage, (256 - 1),
					 "vcg %s(): expected string after \"targetname:\" at line %d in file %s\n", __func__,
					 vcglineno, curfname);
				vcgerror = 1;
				break;
			}

			tn = vcglaststring;
			vcglaststring = NULL;

		} else if (vcgtoken == VCG_LABEL) {
			vcgtoken = vcglex();

			if (vcgtoken != VCG_COLON) {
				memset(parsermessage, 0, 256);
				snprintf(parsermessage, (256 - 1), "vcg %s(): expected ':' after \"label\" at line %d in file %s\n",
					 __func__, vcglineno, curfname);
				vcgerror = 1;
				break;
			}

			vcgtoken = vcglex();

			if (vcgtoken != VCG_STRING) {
				memset(parsermessage, 0, 256);
				snprintf(parsermessage, (256 - 1),
					 "vcg %s(): expected string after \"label:\" at line %d in file %s\n", __func__, vcglineno,
					 curfname);
				vcgerror = 1;
				break;
			}

			label = vcglaststring;
			vcglaststring = NULL;
		} else {
			memset(parsermessage, 0, 256);
			snprintf(parsermessage, (256 - 1), "vcg %s(): unknown edge statement `%s' at line %d in file %s\n",
				 __func__, vcgtext, vcglineno, curfname);
			vcgerror = 1;
			break;
		}

	}

	if (vcgerror) {
		return;
	}

	if (sn == NULL) {
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "vcg %s(): edge has no \"sourcenode:\" statement at line %d in file %s\n",
			 __func__, vcglineno, curfname);
		vcgerror = 1;
	}

	if (tn == NULL) {
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "vcg %s(): edge has no \"targetnode:\" statement at line %d in file %s\n",
			 __func__, vcglineno, curfname);
		vcgerror = 1;
	}

	if (vcgerror) {
		return;
	}

	newedge = dp_calloc(1, sizeof(struct vcge));

	if (newedge == NULL) {
		vcgerror = 1;
		return;
	}

	/* uniq edge number */
	vcgen++;

	newedge->nr = vcgen;

	newedge->fns = sn;	/* uniq name from-node */
	newedge->fromnode = vcguniqnode(sn);
	newedge->tns = tn;	/* uniq name to-node */
	newedge->tonode = vcguniqnode(tn);
	newedge->label = label;

	if (vel == NULL) {
		vel = newedge;
		velend = newedge;
	} else {
		velend->next = newedge;
		velend = newedge;
	}

	return;
}

/* check if all nodes in edges are defined */
static void chkedges(void)
{
	struct vcge *pvel = NULL;
	struct vcgn *pn = NULL;

	pvel = vel;

	while (pvel) {
		pn = vcguniqnode(pvel->fns);
		if (pn == NULL) {
			memset(parsermessage, 0, 256);
			snprintf(parsermessage, (256 - 1), "vcg %s(): sourcenode `%s' in edge not defined in file %s\n", __func__,
				 pvel->fns, curfname);
			vcgerror = 1;
			break;
		}
		if (pvel->fromnode == NULL) {
			pvel->fromnode = pn;
		}
		/* set node number in edge */
		pvel->fnn = pn->nr;
		pn = vcguniqnode(pvel->tns);
		if (pn == NULL) {
			memset(parsermessage, 0, 256);
			snprintf(parsermessage, (256 - 1), "vcg %s(): targetnode `%s' in edge not defined in file %s\n", __func__,
				 pvel->tns, curfname);
			vcgerror = 1;
			break;
		}
		if (pvel->tonode == NULL) {
			pvel->tonode = pn;
		}
		/* set node number in edge */
		pvel->tnn = pn->nr;
		pvel = pvel->next;
	}

	return;
}

/* copy checked edges and nodes now */
static void copyall(struct gml_graph *g)
{
	struct gml_node *fnn = NULL;
	struct gml_node *tnn = NULL;
	struct vcgn *pvnl = NULL;
	struct vcge *pvel = NULL;
	int nr = 0;

	pvnl = vnl;

	while (pvnl) {
		/* uniq node number starting at 1 */
		maingraph->nodenum++;
		nr = maingraph->nodenum;
		/* in vcg all nodes are located in rootgraph
		 * use -1 for foundid then gml id check is not applied.
		 */
		add_new_node(g, maingraph, nr, /* pvnl->nr */ (-1), uniqstr(pvnl->name), uniqstr(pvnl->label), /* ncolor */ 0x00ffffff, /* nbcolor */ 0,	/* rlabel */
			     NULL, /* hlabel */ NULL, /* fontcolor */ 0, /* ishtml */ 0);
		pvnl->finalnr = nr;
		pvnl = pvnl->next;
	}

	pvel = vel;

	while (pvel) {
		if (pvel->fromnode) {
			fnn = uniqnode(g, pvel->fromnode->finalnr);
		} else {
			fnn = NULL;
		}
		if (pvel->tonode) {
			tnn = uniqnode(g, pvel->tonode->finalnr);
		} else {
			tnn = NULL;
		}
		if (fnn && tnn) {
			if (fnn == tnn) {
				/* add selfedge count at this node */
				fnn->nselfedges++;
			} else {
				add_new_edge(g, maingraph, /* foundsource */ fnn->nr, /* foundtarget */ tnn->nr,
					     uniqstr(pvel->label),
					     /* ecolor */ 0, /* style */ 0, /* fcompass */ NULL, /* tcompass */ NULL,
					     /* constraint */ 1, /* ishtml */ 0);
			}
		} else {
			printf("vcg %s(): missing nodes in edge between nodes ", __func__);
			if (pvel->fns) {
				printf("\"%s\" ", pvel->fns);
			}
			if (pvel->tns) {
				printf("\"%s\" ", pvel->tns);
			}
			printf("\n");
		}
		pvel = pvel->next;
	}
	return;
}

/* */
int vcgparse(struct gml_graph *g, FILE * f, char *fname, char *argv0)
{
	curfname = fname;

	/* uniq node number */
	vcgnn = 0;

	/* uniq edge number */
	vcgen = 0;

	/* no errors */
	vcgerror = 0;

	/* in vcg.l */
	if (strcmp(argv0, "gml4gtkd") == 0) {
		vcg_lex_init(f, /* debugflag */ 0);
	} else {
		vcg_lex_init(f, /* debugflag */ 0);
	}

	/* expect "graph" as first token in vcg graph */
	vcgtoken = vcglex();

	if (vcgtoken != VCG_GRAPH) {
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "vcg %s(): expected \"graph\" at start of graph in file %s\n", __func__, fname);
		vcgparse_clear();
		return (1);
	}

	/* expect : */
	vcgtoken = vcglex();

	if (vcgtoken != VCG_COLON) {
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "vcg %s(): expected ':' after \"graph\" at start of graph in file %s\n",
			 __func__, fname);
		vcgparse_clear();
		return (1);
	}

	/* expect brace open */
	vcgtoken = vcglex();

	if (vcgtoken != VCG_BO) {
		memset(parsermessage, 0, 256);
		snprintf(parsermessage, (256 - 1), "vcg %s(): expected '{' after \"graph:\" at start of graph in file %s\n",
			 __func__, fname);
		vcgparse_clear();
		return (1);
	}

	/* parse until brace close */

	for (;;) {

		/* check if there was parse error */
		if (vcgerror) {
			break;
		}

		vcgtoken = vcglex();

		if (vcgtoken == EOF) {
			memset(parsermessage, 0, 256);
			snprintf(parsermessage, (256 - 1), "vcg %s(): unexpected end-of-file at line %d in file %s\n", __func__,
				 vcglineno, fname);
			vcgerror = 1;
			break;
		}

		/* at brace close end of graph */
		if (vcgtoken == VCG_BC) {
			break;
		}

		/* at top level in graph is in gcc data
		 * title: "string"
		 * node: {...}
		 * edge: {...}
		 */
		if (vcgtoken == VCG_TITLE) {
			vcggraphtitle();
		} else if (vcgtoken == VCG_NODE) {
			vcgnode();
		} else if (vcgtoken == VCG_EDGE) {
			vcgedge();
		} else {
			memset(parsermessage, 0, 256);
			snprintf(parsermessage, (256 - 1), "vcg %s(): unknown graph statement `%s' at line %d in file %s\n",
				 __func__, vcgtext, vcglineno, fname);
			vcgerror = 1;
			break;
		}

	}

	/* check if there was parse error */
	if (vcgerror) {
		vcgparse_clear();
		return (1);
	}

	/* if graph has no nodes, done with oke status */
	if (vnl == NULL) {
		vcgparse_clear();
		return (0);
	}

	/* check if all nodes in edges are defined */
	chkedges();

	/* check if there was parse error */
	if (vcgerror) {
		vcgparse_clear();
		return (1);
	}

	/* copy checked edges and nodes now */
	copyall(g);

	vcgparse_clear();

	return (0);
}

/* end */
