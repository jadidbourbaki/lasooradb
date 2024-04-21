#ifndef PERSIST_H
#define PERSIST_H

#include "base.h"

/* save the memory buffer */
int save_mem(db* d);

/* load the memory buffer.
 * Clears the current memory buffer. 
 */
int load_mem(db* d);

#endif /* PERSIST_H */
