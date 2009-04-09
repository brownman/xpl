#ifndef XPL_EXP_H
#define XPL_EXPR_H

void xpl_parse(xpl_lex_stream stream);
void xpl_parse_factor(xpl_lex_stream stream);
void xpl_parse_atom(xpl_lex_stream stream);

#endif
