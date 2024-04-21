#ifndef PERSIST_H
#define PERSIST_H

#include "base.h"

/* save the memory buffer */
int save_mem(db* d);

/* load the memory buffer.
 * Clears the current memory buffer. 
 */
int load_mem(db* d);

/* Checks what disk length to set */
void infer_disk(db* d);

/* Checks if a memory buffer is saved
 * and if so loads it */
void infer_mem(db* d);

#endif /* PERSIST_H */
