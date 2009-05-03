#ifndef XPL_EXP_H
#define XPL_EXPR_H

int xpl_parse(xpl_lex_stream stream);
int xpl_parse_factor(xpl_lex_stream stream);
int xpl_parse_atom(xpl_lex_stream stream);

#endif
