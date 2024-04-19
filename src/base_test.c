#include "base.h"

#include <stdio.h>
#include <assert.h>

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

 printf("passed.\n");
}

int main() {
 test_put();
}
