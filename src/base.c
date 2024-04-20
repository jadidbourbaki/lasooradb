#include "base.h"

#include <assert.h>
#include <string.h>

void db_init(db* d) {
 d->mem = calloc(d->mem_cap, sizeof(entry));
 assert(d->mem != NULL);

 d->mem_len = 0;
}

void db_free(db* d) {
 free(d->mem);
}

int db_put(db* d, char* k, char* v) {
 if (d->mem_len == d->mem_cap) {
  return -1;
 }

 assert(d->mem_len < d->mem_cap);

 entry* e = &d->mem[d->mem_len];
 memcpy(e->k, k, K_LEN);
 memcpy(e->v, v, V_LEN);
 e->op = PUT;

 d->mem_len++;

 return 0;
}

int db_del(db* d, char* k) {
 char* v = "";
 int r = db_put(d, k, v);

 if (r != 0) {
  return r;
 }

 entry* e = &d->mem[d->mem_len - 1];
 e->op = DEL;

 return 0;
}

int key_cmp(char* k1, char* k2) {
 for (size_t i = 0; i < K_LEN; i++) {
  if (k1[i] != k2[i]) {
   return -1;
  }
 }

 return 0;
}

char* db_get(db* d, char* k) {
 if (d->mem_len == 0) {
  return NULL;
 }

 for (int64_t i = d->mem_len - 1; i >= 0; i--) {
  if (key_cmp(k, d->mem[i].k) == 0) {
   if (d->mem[i].op == DEL) {
    return NULL;
   }
   return strndup(d->mem[i].v, V_LEN);
  }
 }

 return NULL;

}
