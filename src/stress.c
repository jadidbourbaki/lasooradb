#include "base.h"

#include <string.h>
#include <assert.h>

int test_stress() {
 TEST_START;

 db d;
 d.mem_cap = 100;
 d.disk_cap = 100;
 d.fname = "stress.db";

 db_init(&d);

 for (size_t i = 0; i < 10000; i++) {
  char key[K_LEN];
  char value[V_LEN];

  memcpy(key, &i, 4);
  memcpy(value, &i, 4);

  int r = db_put(&d, key, value);
  assert(r == 0);
 }

 for (size_t i = 0; i < 10000; i++) {
  char key[K_LEN];
  char value[V_LEN];

  memcpy(key, &i, 4);
  memcpy(value, &i, 4);

  char* v = db_get(&d, key);
  assert(v != NULL);

  assert(strncmp(v, value, 4) == 0);
 }

 db_clear(&d);
 db_free(&d);

 TEST_END;
}

int main() {
 setbuf(stdout, NULL);

 test_stress();
 return 0;
}
