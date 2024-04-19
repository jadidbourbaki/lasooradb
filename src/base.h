#ifndef BASE_H
#define BASE_H

#include <stdlib.h>

struct db_s {
 uint32_t l;
 char* v;
};

typedef struct db_s db_s;

char* s_serialize(db_s* s);

db_s* s_deserialize(char* buf);

void s_free(db_s* s);

struct db_kv {
 db_s k;
 db_s v;
};

typedef struct db_kv db_kv;

#endif /* BASE_H */
