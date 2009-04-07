#include "lexer.h"

#include <stdlib.h>
#include <string.h>

static void xpl_lex_stream_free_current_symbol(xpl_lex_stream stream);
static xpl_lex_symbol xpl_lex_symbol_init();

xpl_lex_stream xpl_lex_stream_init(FILE* file) {
  xpl_lex_stream stream = (xpl_lex_stream) malloc(sizeof(struct xpl_lex_stream));
  stream->input = file;
  stream->current_sym = NULL;
  return stream;
}

xpl_lex_symbol xpl_lex_stream_next(xpl_lex_stream stream) {
  xpl_lex_stream_free_current_symbol(stream);

  char ch = getc(stream->input);
  while(ch == '\r' || ch == '\n' || ch == ' ') ch = getc(stream->input);
  if(ch == EOF) { return NULL; }

  xpl_lex_symbol symbol = xpl_lex_symbol_init();

  if(ch >= '0' && ch <= '9') {
    symbol->type  = NUMBER;
    symbol->token = ch;
    symbol->value = ch - '0';
  }
  else if(ch == '+' || ch == '-' || ch == '*' || ch == '/') {
    symbol->type  = OPERATOR;
    symbol->token = ch;
  }

  stream->current_sym = symbol;
  return symbol;
}

void xpl_lex_stream_free(xpl_lex_stream stream) {
  free(stream);
}

static void xpl_lex_stream_free_current_symbol(xpl_lex_stream stream) {
  if(stream->current_sym != NULL) {
    free(stream->current_sym);
    stream->current_sym = NULL;
  }
}

static xpl_lex_symbol xpl_lex_symbol_init() {
  return (xpl_lex_symbol) malloc(sizeof(struct xpl_lex_symbol));
}
