#include "base.h"

#include <assert.h>
#include <string.h>

void db_init(db* d) {
 size_t entry_len = K_LEN + V_LEN + 1;

 d->mem = calloc(d->mem_cap, entry_len);
 assert(d->mem != NULL);

 d->disk = fopen(d->fname, "wb+");
 assert(d->disk != NULL);
}

void db_free(db* d) {
 free(d->mem);
 fclose(d->disk);
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

 for (size_t i = d->mem_len - 1; i > 0; i--) {
  if (key_cmp(k, d->mem[i].k) == 0) {
   return strndup(d->mem[i].v, V_LEN);
  }
 }

 return NULL;

}
