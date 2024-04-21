#include "base.h"
#include "persist.h"

#include <assert.h>
#include <string.h>
#include <unistd.h>

void db_init(db* d) {
 d->mem = calloc(d->mem_cap, sizeof(entry));
 assert(d->mem != NULL);


 infer_mem(d);
 infer_disk(d);
}

void db_free(db* d) {
 free(d->mem);
}

int db_put(db* d, char* k, char* v) {
 if (d->mem_len == d->mem_cap) {

  if (d->disk_len == d->disk_cap) {
   return -1;
  }

  char fname[FNAME_LEN];
  sprintf(fname, "%s.%zu", d->fname, d->disk_len);

  FILE* f = fopen(fname, "wb");
  assert(f != NULL);

  fwrite(d->mem, d->mem_len * sizeof(entry), 1, f);
  fclose(f);

  d->mem_len = 0;
  d->disk_len++;
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

 for (int64_t i = d->mem_len - 1; i >= 0; i--) {
  if (key_cmp(k, d->mem[i].k) == 0) {
   if (d->mem[i].op == DEL) {
    return NULL;
   }
   return strndup(d->mem[i].v, V_LEN);
  }
 }

 for (int64_t i = d->disk_len - 1; i >= 0; i--) {
  char fname[FNAME_LEN];
  sprintf(fname, "%s.%zu", d->fname, (size_t)i);

  entry* buf = calloc(d->mem_cap, sizeof(entry));
  assert(buf != NULL);

  FILE* f = fopen(fname, "rb");
  assert(f != NULL);

  size_t bytes_to_read = sizeof(entry) * d->mem_cap;
  fread(buf, bytes_to_read, 1, f);

  fclose(f);

  for (int64_t j = d->mem_cap - 1; j >= 0; j--) {
   if (key_cmp(k, buf[j].k) == 0) {
    if (buf[j].op == DEL) {
     return NULL;
    }
    return strndup(buf[j].v, V_LEN);
   }
  }

  free(buf);
 }

 return NULL;

}

int db_clear(db* d) {
 char fname[FNAME_LEN];
 sprintf(fname, "%s.mem", d->fname);

 int r;

 if (access(fname, F_OK) == 0) {
  r = remove(fname);
  if (r != 0) {
   return -1;
  }
 }

 size_t i;
 for (i = 0; i < d->disk_len; i++) {
  sprintf(fname, "%s.%zu", d->fname, i);
  r = remove(fname);
  if (r != 0) {
   return -1;
  }
 }
 
 return 0;
}
