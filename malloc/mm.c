/* * mm.c - Segregated Free List Malloc
 * Hardest part was the alignment. Standard is 8 bytes.
 * Added a "Prologue" and "Epilogue" to avoid edge cases.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define WSIZE 4
#define DSIZE 8
#define CHUNKSIZE (1<<12)

#define PACK(size, alloc) ((size) | (alloc))
#define GET(p)      (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

// Global heap pointer
static char *heap_listp = 0;

int mm_init(void) {
    if ((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1) return -1;
    
    PUT(heap_listp, 0);                          // Alignment padding
    PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1)); // Prologue header
    PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1)); // Prologue footer
    PUT(heap_listp + (3*WSIZE), PACK(0, 1));     // Epilogue header
    heap_listp += (2*WSIZE);

    if (extend_heap(CHUNKSIZE/WSIZE) == NULL) return -1;
    return 0;
}

/* * malloc: 
 * Always round up to 8 bytes. 
 * FIXME: Search through segregated lists instead of just first-fit.
 */
void *mm_malloc(size_t size) {
    size_t asize; 
    if (size == 0) return NULL;
    
    if (size <= DSIZE) asize = 2*DSIZE;
    else asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);

    // TODO: Actually implement find_fit()
    return NULL; 
}