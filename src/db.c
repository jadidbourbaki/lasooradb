#include "db.h"

#include <signal.h>

db d;

void handle_exit(int sig) {
 printf("saving memory buffer.\n");
 save_mem(&d);
 exit(0);
}

int main() {

 signal(SIGINT, handle_exit);
 signal(SIGTERM, handle_exit);
 signal(SIGQUIT, handle_exit);
 signal(SIGHUP, handle_exit);
 
 // Use 1 MB of memory
 d.mem_cap = (1024 * 1024) / (K_LEN + V_LEN);

 // 1 GB of disk space
 d.disk_cap = 1024;

 d.fname = "main.db"; 

 db_init(&d);

 while (1) {

 }

 db_free(&d);

 return 0;

}

