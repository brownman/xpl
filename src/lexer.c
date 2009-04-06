#include "lexer.h"

#include <stdlib.h>
#include <string.h>

xpl_lex_stream xpl_lex_stream_init(FILE* file) {
  xpl_lex_stream stream = (xpl_lex_stream) malloc(sizeof(struct xpl_lex_stream));
  stream->input = file;
  return stream;
}

xpl_lex_symbol xpl_lex_stream_next(xpl_lex_stream stream) {
  char ch = getc(stream->input);
  while(ch == '\r' || ch == '\n' || ch == ' ') ch = getc(stream->input);
  if(ch == EOF) return NULL;

  xpl_lex_symbol symbol = (xpl_lex_symbol) malloc(sizeof(struct xpl_lex_symbol));

  if(ch >= '0' && ch <= '9') {
    symbol->type  = NUMBER;
    symbol->token = ch;
    symbol->value = ch - '0';
    strcpy(symbol->kind, "DIGIT");
  }
  else if(ch == '+' || ch == '-' || ch == '*' || ch == '/') {
    symbol = (xpl_lex_symbol) malloc(sizeof(struct xpl_lex_symbol));
    symbol->type  = OPERATOR;
    symbol->token = ch;
    strcpy(symbol->kind, "OPERATOR");
  }

  return symbol;
}
