#include "addr.h"
#include "lexer.h"
#include "expr.h"
#include "emit.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if(argc < 2) {
    printf("error: missing source file name\n");
    return 0;
  }

  FILE* input  = fopen(argv[1], "r");
  FILE* output = fopen(argv[2], "w");

  if(input == NULL) {
    printf("error: could not open the supplied source file\n");
    return 0;
  }

  xpl_lex_stream stream = xpl_lex_stream_init(input);

  xpl_emit_init(output);
  xpl_emit_prologue(output);
  addr result = xpl_parse(stream);
  xpl_emit_display_result(result);
  xpl_emit_epilogue(output);

  xpl_lex_stream_free(stream);
  fclose(input);
  fclose(output);
}
