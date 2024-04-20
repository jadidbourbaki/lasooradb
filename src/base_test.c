#include "base.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_put() {

 printf("%s ... ", __func__);

 db d;
 d.mem_cap = 1;
 d.disk_cap = 1;
 d.fname = "test.db";

 db_init(&d);

 /* their values do not really matter for 
  * this test */
 char key[K_LEN];
 char value[V_LEN];

 int r = db_put(&d, key, value);
 assert(r == 0);

 r = db_put(&d, key, value);
 assert(r == -1);

 db_free(&d);

 printf("passed.\n");
}

void test_get() {
 printf("%s ... ", __func__);

 db d;
 d.mem_cap = 2;
 d.disk_cap = 2;
 d.fname = "test.db";

 db_init(&d);

 char key[K_LEN] = "K1";
 char value[V_LEN] = "VALUE";

 int r = db_put(&d, key, value);
 assert(r == 0);

 char* v = db_get(&d, key);

 assert(strcmp(v, value) == 0);
 free(v);

 sprintf(key, "K2");
 v = db_get(&d, key);

 assert(v == NULL);

 db_free(&d);

 printf("passed.\n");
}


int main() {
 test_put();
 test_get();
}
