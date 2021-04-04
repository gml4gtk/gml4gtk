
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
 * SPDX-License-Identifier: GPL-3.0+
 * License-Filename: LICENSE
 */

/* dphl.* is about Dot Parsing Html Labels */

#ifndef DPHL_H
#define DPHL_H 1

/* parse html label of one node */
extern int htmlparse (struct dpnode *node);

/* unknown attribute */
extern void dphl_attr_huh (char *tag, char *attr, char *value);

/* check data before/after <table> */
extern void dphl_tabledata(char *str);

/* html.l */
extern int hllineno;

/* html.l init */
extern void html_lex_init (int debug, char *str, int line);

/* html.l de-init */
extern void html_lex_deinit (void);

/* html.l lex token */
extern int html_lex (void);

/* reset <table> */
extern void dphl_rtable (void);

/* end <table> */
extern void dphl_etable (void);

/* reset <td> */
extern void dphl_rtd (void);

/* end <td> */
extern void dphl_etd (int code);

/* reset <br> */
extern void dphl_rbr (void);

/* end <br> */
extern void dphl_ebr (void);

/* reset <i> */
extern void dphl_ri (void);

/* end </i> */
extern void dphl_ei (void);

/* reset <b> */
extern void dphl_rb (void);

/* end </b> */
extern void dphl_eb (void);

/* reset <u> */
extern void dphl_ru (void);

/* end </u> */
extern void dphl_eu (void);

/* reset <o> */
extern void dphl_ro (void);

/* end </o> */
extern void dphl_eo (void);

/* reset <sub> */
extern void dphl_rsub (void);

/* end </sub> */
extern void dphl_esub (void);

/* reset <sup> */
extern void dphl_rsup (void);

/* end </sup> */
extern void dphl_esup (void);

/* reset <s> */
extern void dphl_rs (void);

/* end </s> */
extern void dphl_es (void);

/* reset <tr> */
extern void dphl_rtr (void);

/* end </tr> */
extern void dphl_etr (void);

/* reset <font> */
extern void dphl_rfont (void);

/* end <font> */
extern void dphl_efont (void);

/* reset <vr/> */
extern void dphl_rvr (void);

/* reset <hr/> */
extern void dphl_rhr (void);

/* reset <img> */
extern void dphl_rimg (void);

/* end <img> */
extern void dphl_eimg (void);

/* check for error message */
extern int dphl_chk_err (void);

/* check align value */
extern int dphl_chk_align (char *str, int mode);

/* check balign value */
extern int dphl_chk_balign (char *str);

/* check bgcolor value */
extern int dphl_chk_bgcolor (char *str, int mode);

/* check border value */
extern int dphl_chk_border (char *str, int mode);

/* check cellborder value */
extern int dphl_chk_cellborder (char *str);

/* check cellpadding value */
extern int dphl_chk_cellpadding (char *str, int mode);

/* check cellspacing value */
extern int dphl_chk_cellspacing (char *str, int mode);

/* check color value */
extern int dphl_chk_color (char *str, int mode);

/* check columns value <table> */
extern int dphl_chk_columns (char *str);

/* check colspan value <td> */
extern int dphl_chk_colspan (char *str);

/* check face value for <font> */
extern int dphl_chk_face (char *str);

/* check fixedsize value */
extern int dphl_chk_fixedsize (char *str, int mode);

/* check gradientangle value */
extern int dphl_chk_gradientangle (char *str, int mode);

/* check height value */
extern int dphl_chk_height (char *str, int mode);

/* check href value */
extern int dphl_chk_href (char *str, int mode);

/* check id value */
extern int dphl_chk_id (char *str, int mode);

/* check port value */
extern int dphl_chk_port (char *str, int mode);

/* check point-size value for <font> */
extern int dphl_chk_pointsize (char *str);

/* check rows value <table> */
extern int dphl_chk_rows (char *str);

/* check rowspan value <td> */
extern int dphl_chk_rowspan (char *str);

/* check scale value for <img> */
extern int dphl_chk_scale (char *str);

/* check sides value */
extern int dphl_chk_sides (char *str, int mode);

/* check src value for <img> */
extern int dphl_chk_src (char *str);

/* check style value */
extern int dphl_chk_style (char *str, int mode);

/* check target value */
extern int dphl_chk_target (char *str, int mode);

/* check title value */
extern int dphl_chk_title (char *str, int mode);

/* check valign value */
extern int dphl_chk_valign (char *str, int mode);

/* check width value */
extern int dphl_chk_width (char *str, int mode);

/* gets data part */
extern void dphl_data (char *str);

/* free mem */
extern void dphl_freemem (void);

#endif

/* end */
