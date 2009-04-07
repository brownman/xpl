#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if(argc < 2) {
    printf("error: missing source file name\n");
    return 0;
  }

  FILE* input = fopen(argv[1], "r");

  if(input == NULL) {
    printf("error: could not open the supplied source file\n");
    return 0;
  }

  xpl_lex_stream stream = xpl_lex_stream_init(input);

  xpl_lex_symbol symbol;
  while(symbol = xpl_lex_stream_next(stream)) {
    printf("%d\n", symbol->type);
  }

  xpl_lex_stream_free(stream);

  fclose(input);
}
