#include "base.h"

#include <string.h>

char* s_serialize(db_s* s) {
 char* buf = malloc(s->l + 4);
 if (buf == NULL) {
  return NULL;
 }

 memcpy(buf, &s->l, 4);
 memcpy(buf + 4, s->v, s->l);

 return buf;
}

db_s* s_deserialize(char* buf) {
 db_s* s = malloc(sizeof(db_s));
 if (s == NULL) {
  return NULL;
 }

 memcpy(&s->l, buf, 4);
 
 s->v = malloc(sizeof(s->l));
 if (s->v == NULL) {
  free(s);
  return NULL;
 }

 memcpy(s->v, buf + 4, s->l);
 return s;
}

void s_free(db_s* s) {
 free(s->v);
 free(s);
}
