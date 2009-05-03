#include <stdio.h>

#define emit(X) fputs(X, output);

static FILE* output;

static int variable = 0;
static int next_addr() { return variable-- * 4; }

void xpl_emit_init(FILE* out) {
  output = out;
}

void xpl_emit_prologue() {
  emit(".section .rodata\n");
  emit(".LC0:\n");
  emit(".string \"%d\\n\"\n");
  emit(".text\n");
  emit(".globl main\n");
  emit(".type main, @function\n");
  emit("main:\n");
  emit("pushl %ebp\n");
  emit("movl %esp, %ebp\n");
}

int xpl_emit_load(int value) {
  int addr = next_addr();
  fprintf(output, "movl $%d, %d(%%ebp)\n", value, addr);
  return addr;
}

void xpl_emit_load_ebx(int value) {
  fprintf(output, "movl $%d, %ebx\n", value);
}

static int xpl_emit_binary(char* instr, int addr_a, int addr_b) {
  fprintf(output, "movl %d(%%ebp), %%eax\n", addr_a);
  fprintf(output, "%s %d(%%ebp), %%eax\n", instr, addr_b);
  fprintf(output, "movl %%eax, %d(%%ebp)\n", addr_b);
  return addr_b;
}

int xpl_emit_add(int addr_a, int addr_b) {
  return xpl_emit_binary("addl", addr_a, addr_b);
}

int xpl_emit_sub(int addr_a, int addr_b) {
  return xpl_emit_binary("subl", addr_a, addr_b);
}

int xpl_emit_mul(int addr_a, int addr_b) {
  return xpl_emit_binary("imull", addr_a, addr_b);
}

int xpl_emit_div(int addr_a, int addr_b) {
  fprintf(output, "movl %d(%%ebp), %%eax\n", addr_a);
  fprintf(output, "cltd\n", addr_b);
  fprintf(output, "idivl %d(%%ebp)\n", addr_b);
  fprintf(output, "movl %%eax, %d(%%ebp)\n", addr_b);
  return addr_b;
}

void xpl_emit_display_result(int addr) {
  fprintf(output, "pushl %d(%%ebp)\n", addr);
  emit("pushl $.LC0\n");
  emit("call printf\n");
}

void xpl_emit_epilogue() {
  emit("movl %ebp, %esp\n");
  emit("popl %ebp\n");
  emit("ret\n");
  emit(".size main, .-main\n");
}
