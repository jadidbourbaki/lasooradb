#include "persist.h"

#include <assert.h>

int save_mem(db* d) {
  char fname[FNAME_LEN];
  sprintf(fname, "%s.mem", d->fname);

  FILE* f = fopen(fname, "wb");
  if (f == NULL) {
   return -1;
  }

  fwrite(&d->mem_len, sizeof(size_t), 1, f);
  fwrite(d->mem, d->mem_len * sizeof(entry), 1, f);
  fclose(f);

  return 0;
}

int load_mem(db* d) {
  char fname[FNAME_LEN];
  sprintf(fname, "%s.mem", d->fname);

  FILE* f = fopen(fname, "rb");
  if (f == NULL) {
   return -1;
  }

  fread(&d->mem_len, sizeof(size_t), 1, f);

  size_t bytes_to_read = sizeof(entry) * d->mem_len;
  fread(d->mem, bytes_to_read, 1, f);

  fclose(f);

  return 0;
}
