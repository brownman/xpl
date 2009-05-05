#ifndef XPL_ADDR_H
#define XPL_ADDR_H

struct addr {
  enum { CONST = 0, REGISTER = 1, LOCAL = 2 } type;
  union {
    char name[4];
    int value;
  } v;
};

typedef struct addr * addr;

addr xpl_addr_new_const(int value);
addr xpl_addr_new_local();
addr xpl_addr_new_register(char name[4]);
void xpl_addr_free(addr addr);
void xpl_addr_to_str(addr addr, char* str);

#endif
