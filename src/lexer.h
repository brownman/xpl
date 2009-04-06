#include <stdio.h>

#define NUMBER     0
#define OPERATOR   1

struct xpl_lex_stream {
  FILE* input;
};

struct xpl_lex_symbol {
  char kind[50];
  char token;
  int type;
  int value;
};

typedef struct xpl_lex_stream *xpl_lex_stream;
typedef struct xpl_lex_symbol *xpl_lex_symbol;

xpl_lex_stream xpl_lex_stream_init(FILE* file);
xpl_lex_symbol xpl_lex_stream_next(xpl_lex_stream stream);
