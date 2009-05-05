#ifndef XPL_EMIT_H
#define XPL_EMIT_H

void xpl_emit_init(FILE* out);
void xpl_emit_prologue();
addr xpl_emit_load_into(addr address, addr reg);
addr xpl_emit_add();
addr xpl_emit_sub();
addr xpl_emit_mul();
addr xpl_emit_div();
void xpl_emit_display_result(addr address);
void xpl_emit_epilogue();

#endif
