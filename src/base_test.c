#include "base.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_put() {
 TEST_START;

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

 TEST_END;

}

void test_get() {
 TEST_START;

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

 assert(v != NULL);
 assert(strcmp(v, value) == 0);
 free(v);

 sprintf(key, "K2");
 v = db_get(&d, key);

 assert(v == NULL);

 db_free(&d);

 TEST_END;
}

void test_del() {
 TEST_START;

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

 r = db_del(&d, key);
 assert(r == 0);

 v = db_get(&d, key);
 assert(v == NULL);

 db_free(&d);

 TEST_END;
}

int main() {
 setbuf(stdout, NULL);

 test_put();
 test_get();
 test_del();
}
