#include "lexer.h"
#include "expr.h"

static xpl_lex_symbol symbol;

void xpl_parse(xpl_lex_stream stream) {
  printf("expr\n");
  xpl_parse_factor(stream);
  while(symbol && (symbol->token == '+' || symbol->token == '-')) {
    xpl_parse_factor(stream);
  }
}

void xpl_parse_factor(xpl_lex_stream stream) {
  printf("factor\n");
  xpl_parse_atom(stream);
  symbol = xpl_lex_stream_next(stream);
  while(symbol && (symbol->token == '*' || symbol->token == '/')) {
    xpl_parse_atom(stream);
    xpl_lex_stream_next(stream);
  }
}

void xpl_parse_atom(xpl_lex_stream stream) {
  symbol = xpl_lex_stream_next(stream);
  printf("atom %c\n", symbol->token);
}
