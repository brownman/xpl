#include "addr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define emit(...) fprintf(output, __VA_ARGS__);

static FILE* output;

void xpl_emit_init(FILE* out) {
  output = out;
}

void xpl_emit_prologue() {
  emit(".section .rodata\n");
  emit(".LC0:\n");
  emit(".string \"%%d\\n\"\n");
  emit(".text\n");
  emit(".globl main\n");
  emit(".type main, @function\n");
  emit("main:\n");
  emit("pushl %%ebp\n");
  emit("movl %%esp, %%ebp\n");
}

addr xpl_emit_load_into(addr address, char name[4]) {
  if(address->type == REGISTER && strcmp(address->v.name, name) == 0)
    return address;

  if(address->type == CONST) {
    emit("movl $%d, %%%s\n", address->v.value, name);
  }
  else {
    emit("movl %%%s, %%%s\n", address->v.name, name);
  }

  return xpl_addr_new_register(name);
}

addr xpl_emit_add(addr addr_a, addr addr_b) {
  char* addr_a_str = malloc(sizeof(char) * 10);
  char* addr_b_str = malloc(sizeof(char) * 10);
  xpl_addr_to_str(addr_a, addr_a_str);
  xpl_addr_to_str(addr_b, addr_b_str);

  emit("addl %s, %s\n", addr_a_str, addr_b_str);

  free(addr_a_str);
  free(addr_b_str);

  return addr_b;
}

addr xpl_emit_sub(addr addr_a, addr addr_b) {
  char* addr_a_str = malloc(sizeof(char) * 10);
  char* addr_b_str = malloc(sizeof(char) * 10);
  xpl_addr_to_str(addr_a, addr_a_str);
  xpl_addr_to_str(addr_b, addr_b_str);

  emit("subl %s, %s\n", addr_a_str, addr_b_str);

  free(addr_a_str);
  free(addr_b_str);

  return addr_b;
}

addr xpl_emit_mul() {
  emit("imull %%ebx, %%eax\n");
  return xpl_addr_new_register("eax");
}

addr xpl_emit_div() {
  emit("cltd\n");
  emit("idivl %%ebx\n");
  return xpl_addr_new_register("eax");
}

void xpl_emit_display_result(addr addr) {
  emit("pushl %%%s\n", addr->v.name);
  emit("pushl $.LC0\n");
  emit("call printf\n");
}

void xpl_emit_epilogue() {
  emit("movl %%ebp, %%esp\n");
  emit("popl %%ebp\n");
  emit("ret\n");
  emit(".size main, .-main\n");
}
