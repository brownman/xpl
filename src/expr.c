#include "addr.h"
#include "lexer.h"
#include "expr.h"
#include "emit.h"

// Each function call here returns the addr of the result of the
// computation it represents

static xpl_lex_symbol symbol;

addr xpl_parse(xpl_lex_stream stream) {
  addr addr_a, addr_b;

  addr_a = xpl_parse_factor(stream);

  if(!symbol || (symbol->token != '+' && symbol->token != '-'))
    return addr_a;

  while(symbol && (symbol->token == '+' || symbol->token == '-')) {
    char op = symbol->token;

    addr_a = xpl_emit_load_into(addr_a, "ecx");
    addr_b = xpl_parse_factor(stream);

    addr_a = op == '+' ? xpl_emit_add(addr_b, addr_a) : xpl_emit_sub(addr_b, addr_a);
  }

  return addr_a;
}

addr xpl_parse_factor(xpl_lex_stream stream) {
  addr addr_a, addr_b;

  addr_a = xpl_parse_atom(stream);

  symbol = xpl_lex_stream_next(stream);
  if(!symbol || (symbol->token != '*' && symbol->token != '/'))
    return addr_a;

  while(symbol && (symbol->token == '*' || symbol->token == '/')) {
    char op = symbol->token;

    addr_b = xpl_parse_atom(stream);

    xpl_emit_load_into(addr_a, "eax");
    xpl_emit_load_into(addr_b, "ebx");
    xpl_addr_free(addr_a);
    xpl_addr_free(addr_b);

    // The next value of addr_a will be the address of the result of
    // the current computation
    addr_a = op == '*' ? xpl_emit_mul() : xpl_emit_div();

    xpl_lex_stream_next(stream);
  }

  return addr_b;
}

addr xpl_parse_atom(xpl_lex_stream stream) {
  symbol = xpl_lex_stream_next(stream);
  return xpl_addr_new_const(symbol->value);
}
