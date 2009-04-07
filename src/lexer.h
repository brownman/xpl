#include <stdio.h>

#define NUMBER     0
#define OPERATOR   1

struct xpl_lex_symbol {
  char token;
  int type;
  int value;
};

struct xpl_lex_stream {
  FILE* input;
  struct xpl_lex_symbol *current_sym;
};

typedef struct xpl_lex_stream *xpl_lex_stream;
typedef struct xpl_lex_symbol *xpl_lex_symbol;

xpl_lex_stream xpl_lex_stream_init(FILE* file);
xpl_lex_symbol xpl_lex_stream_next(xpl_lex_stream stream);
void           xpl_lex_stream_free(xpl_lex_stream stream);

xpl_lex_symbol xpl_lex_symbol_init();
void           xpl_lex_symbol_free(xpl_lex_symbol symbol);
