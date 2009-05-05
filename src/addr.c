#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "addr.h"

static int current_local = 0;
static int next_local_addr() { return current_local-- * 4; }

addr xpl_addr_new_const(int value) {
  addr addr     = malloc(sizeof(struct addr));
  addr->type    = CONST;
  addr->v.value = value;
  return addr;
}

addr xpl_addr_new_local() {
  addr addr     = malloc(sizeof(struct addr));
  addr->type    = LOCAL;
  addr->v.value = next_local_addr();
  return addr;
}

addr xpl_addr_new_register(char name[4]) {
  addr addr    = malloc(sizeof(struct addr));
  addr->type   = REGISTER;
  strcpy(addr->v.name, name);
  return addr;
}

void xpl_addr_free(addr addr) {
  free(addr);
}

void xpl_addr_to_str(addr addr, char* str) {
  if(addr->type == CONST) {
    sprintf(str, "$%d", addr->v.value);
  }
  else if(addr->type == REGISTER) {
    sprintf(str, "%%%s", addr->v.name);
  }
  else if (addr->type == LOCAL) {
    sprintf(str, "%d(%%ebp)", addr->v.value);
  }
}
