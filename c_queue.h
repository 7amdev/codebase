#ifndef Queue_H
#define Queue_H

#ifndef Queue_Initial_Capacity
#define Queue_Initial_Capacity 256
#endif // Queue_Initial_Capacity

#ifndef Queue_Realloc 
#include <stdlib.h>
#define Queue_Realloc realloc
#endif // Queue_Realloc

#ifndef Queue_Free 
#include <stdlib.h>
#define Queue_Free free
#endif // Queue_Free

#ifndef Queue_Assert 
#include <assert.h>
#define Queue_Assert assert
#endif // Queue_Assert

#define QueueHeader struct { size_t head; size_t tail; size_t count; }
#define Queue_Items_Length(items) (sizeof(items)/sizeof(items[0]))

#define Queue_init() do {} while (0)

#define Queue_insert() do { \
} while (0)

#define Queue_remove() do {} while (0)
#define Queue_is_full() ()
#define Queue_is_empty() ()

#endif // Queue_H