#ifndef BASE_H
#define BASE_H

#include <stdlib.h>
#include <stdio.h>

#define DEL 0
#define PUT 1
#define GET 2

#define K_LEN 4
#define V_LEN 255

struct entry {
 char k[K_LEN];
 char v[V_LEN];

 /* acts as a tombstone when op == DEL */
 uint8_t op;
} __attribute__((packed));

typedef struct entry entry;

struct db {
 /* capacity of the memory and disk
  * in terms of number of entries */
 size_t mem_cap;
 size_t disk_cap;

 size_t mem_len;
 size_t disk_len;

 entry* mem;

 FILE* disk;
 char* fname;

};

typedef struct db db;

void db_init(db* d);

void db_free(db* d);

int db_put(db* d, char* k, char* v);

char* db_get(db* d, char* k);

#endif /* BASE_H */
