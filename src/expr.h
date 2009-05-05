#ifndef XPL_EXPR_H
#define XPL_EXPR_H

addr xpl_parse(xpl_lex_stream stream);
addr xpl_parse_factor(xpl_lex_stream stream);
addr xpl_parse_atom(xpl_lex_stream stream);

#endif
