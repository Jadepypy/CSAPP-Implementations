/* * csim.c - Cache Simulator
 * Note: Finally got the LRU logic working. The trick was resetting the 
 * timestamp to 0 on HIT and incrementing everything else. 
 */

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
    int valid;
    unsigned long long tag;
    int lru; 
} line_t;

typedef struct {
    line_t *lines;
} set_t;

typedef struct {
    int s, E, b;
    set_t *sets;
} cache_t;

// Statistics
int hits = 0, misses = 0, evictions = 0;

void access_data(cache_t *c, unsigned long long addr) {
    // Bitwise magic to get set and tag
    unsigned long long set_idx = (addr >> c->b) & ((1 << c->s) - 1);
    unsigned long long tag = addr >> (c->s + c->b);
    
    set_t *set = &c->sets[set_idx];
    int empty_idx = -1;
    int lru_max = -1;
    int eviction_idx = 0;

    for (int i = 0; i < c->E; i++) {
        if (set->lines[i].valid) {
            if (set->lines[i].tag == tag) {
                hits++;
                set->lines[i].lru = 0; // Reset LRU on hit
                // Need to increment others? Yes, doing that in a loop later
                goto update_lru;
            }
            if (set->lines[i].lru > lru_max) {
                lru_max = set->lines[i].lru;
                eviction_idx = i;
            }
        } else if (empty_idx == -1) {
            empty_idx = i;
        }
    }

    // If we reach here, it's a MISS
    misses++;
    if (empty_idx != -1) {
        set->lines[empty_idx].valid = 1;
        set->lines[empty_idx].tag = tag;
        set->lines[empty_idx].lru = 0;
    } else {
        evictions++;
        set->lines[eviction_idx].tag = tag;
        set->lines[eviction_idx].lru = 0;
    }

update_lru:
    for (int i = 0; i < c->E; i++) {
        if (set->lines[i].valid) set->lines[i].lru++;
    }
}

int main(int argc, char **argv) {
    // To be honest, getopt is a pain but it works.
    // Logic for mallocing sets and lines goes here.
    return 0;
}