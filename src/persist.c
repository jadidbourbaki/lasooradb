#include "persist.h"

#include <assert.h>
#include <stdio.h>
#include <unistd.h>

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
  if (d->mem_len > d->mem_cap) {
   return -1;
  }

  size_t bytes_to_read = sizeof(entry) * d->mem_len;
  fread(d->mem, bytes_to_read, 1, f);

  fclose(f);

  return 0;
}

void infer_disk(db* d) {
 size_t i = 0;
 char fname[FNAME_LEN];

 sprintf(fname, "%s.%zu", d->fname, i);

 while (access(fname, F_OK) == 0) {
  i++;
  sprintf(fname, "%s.%zu", d->fname, i);
 }

 d->disk_len = i;
}

void infer_mem(db* d) {
 char fname[FNAME_LEN];
 sprintf(fname, "%s.mem", d->fname);

 if (access(fname, F_OK) == 0) {
  load_mem(d);
  return;
 }

 d->mem_len = 0;
}
