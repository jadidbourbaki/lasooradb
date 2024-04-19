#include "base.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_s_serialize() {
 printf("test: %s ... ", __func__);

 const char *test_string = "TEST";

 db_s s;
 s.v = strdup(test_string);
 assert(s.v != NULL);
 
 s.l = strlen(test_string) + 1;

 char* buf = s_serialize(&s);
 assert(buf != NULL);

 db_s* s2 = s_deserialize(buf);
 assert(s2 != NULL);

 printf("passed.\n");
}

int main() {
 test_s_serialize();
}



