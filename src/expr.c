#include "lexer.h"
#include "expr.h"

static xpl_lex_symbol symbol;

// returns the ebp-relative address of the result
int xpl_parse(xpl_lex_stream stream) {
  int addr_a, addr_b;

  addr_a = xpl_parse_factor(stream);

  if(!symbol || (symbol->token != '+' && symbol->token != '-'))
    return addr_a;

  while(symbol && (symbol->token == '+' || symbol->token == '-')) {
    char op = symbol->token;

    addr_b = xpl_parse_factor(stream);

    if(op == '+')
      xpl_emit_add(addr_a, addr_b);
    else
      xpl_emit_sub(addr_a, addr_b);

    addr_a = addr_b;
  }

  return addr_b;
}

// returns the ebp-relative offset of the result in bytes
int xpl_parse_factor(xpl_lex_stream stream) {
  int addr_a, addr_b;

  addr_a = xpl_parse_atom(stream);

  symbol = xpl_lex_stream_next(stream);
  if(!symbol || (symbol->token != '*' && symbol->token != '/'))
    return addr_a;

  while(symbol && (symbol->token == '*' || symbol->token == '/')) {
    char op = symbol->token;

    addr_b = xpl_parse_atom(stream);

    if(op == '*')
      xpl_emit_mul(addr_a, addr_b);
    else
      xpl_emit_div(addr_a, addr_b);

    addr_a = addr_b;
    xpl_lex_stream_next(stream);
  }

  return addr_b;
}

// returns the ebp-relative address of the atom
int xpl_parse_atom(xpl_lex_stream stream) {
  symbol = xpl_lex_stream_next(stream);
  return xpl_emit_load(symbol->value);
}
