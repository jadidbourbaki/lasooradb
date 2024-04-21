#include "persist.h"

#include <assert.h>
#include <string.h>

int test_persist() {
 TEST_START;

 db d;
 d.mem_cap = 3;
 d.disk_cap = 2;
 d.fname = "test.db";

 db_init(&d);

 char key[K_LEN] = "K1";
 char value[V_LEN] = "VALUE";

 int r = db_put(&d, key, value);
 assert(r == 0);

 sprintf(key, "K2");
 r = db_put(&d, key, value);
 assert(r == 0);

 save_mem(&d);

 db_free(&d);

 db d2;
 d2.mem_cap = 3;
 d2.disk_cap = 2;
 d2.fname = "test.db";

 db_init(&d2);

 load_mem(&d2);

 assert(d2.mem_len == 2);
 
 char* v = db_get(&d2, key);
 
 assert(v != NULL);
 assert(strcmp(v, value) == 0);

 free(v);

 sprintf(key, "K1");

 v = db_get(&d2, key);

 assert(v != NULL);
 assert(strcmp(v, value) == 0);

 free(v);

 db_free(&d2);

 TEST_END; 
}

int main() {
 test_persist();
}
