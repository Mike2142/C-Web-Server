#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hashtable.h"
#include "cache.h"

/**
 * Allocate a cache entry
 */
struct cache_entry *alloc_entry(char *path, char *content_type, void *content, int content_length, int timestamp)
{
    struct cache_entry *cacheentry = malloc(sizeof *cacheentry);
    cacheentry->path = path;
    cacheentry->content_type = content_type;
    cacheentry->content_length = content_length;
    cacheentry->timestamp = timestamp;

    cacheentry->content = malloc(content_length);
    memcpy(cacheentry->content, content, content_length);

    return cacheentry;
}

/**
 * Deallocate a cache entry
 */
void free_entry(struct cache_entry *entry)
{
    free(entry);
}

/**
 * Insert a cache entry at the head of the linked list
 */
void dllist_insert_head(struct cache *cache, struct cache_entry *ce)
{
    // Insert at the head of the list
    if (cache->head == NULL) {
        cache->head = cache->tail = ce;
        ce->prev = ce->next = NULL;
    } else {
        cache->head->prev = ce;
        ce->next = cache->head;
        ce->prev = NULL;
        cache->head = ce;
    }
}

/**
 * Move a cache entry to the head of the list
 */
void dllist_move_to_head(struct cache *cache, struct cache_entry *ce)
{
    if (ce != cache->head) {
        if (ce == cache->tail) {
            // We're the tail
            cache->tail = ce->prev;
            cache->tail->next = NULL;

        } else {
            // We're neither the head nor the tail
            ce->prev->next = ce->next;
            ce->next->prev = ce->prev;
        }

        ce->next = cache->head;
        cache->head->prev = ce;
        ce->prev = NULL;
        cache->head = ce;
    }
}

void dllist_remove(struct cache *cache, struct cache_entry *ce)
{   
    if (cache->head == cache->tail) {
        // if 1 entry 
        cache->head = NULL;
        cache->tail = NULL;
    } 
    else if (ce == cache->head) {
        // if head
        cache->head = ce->next;
        cache->head->prev = NULL;
    } 
    else if (ce->next == NULL) {
        // if tail
        ce->prev->next = ce->next;
    } 
    else {
        // if middle
        ce->prev->next = ce->next;
        ce->next->prev = ce->prev;
    }

    cache->cur_size--;
}


/**
 * Removes the tail from the list and returns it
 * 
 * NOTE: does not deallocate the tail
 */
struct cache_entry *dllist_remove_tail(struct cache *cache)
{
    struct cache_entry *oldtail = cache->tail;

    cache->tail = oldtail->prev;
    cache->tail->next = NULL;

    cache->cur_size--;

    return oldtail;
}

/**
 * Create a new cache
 * 
 * max_size: maximum number of entries in the cache
 * hashsize: hashtable size (0 for default)
 */
struct cache *cache_create(int max_size, int hashsize)
{
    struct cache *cache =  malloc(sizeof *cache);
    cache->index = hashtable_create(max_size, 0);
    cache->max_size = max_size;
    cache->cur_size = 0;

    return cache;
}

void cache_free(struct cache *cache)
{
    struct cache_entry *cur_entry = cache->head;

    hashtable_destroy(cache->index);

    while (cur_entry != NULL) {
        struct cache_entry *next_entry = cur_entry->next;

        free_entry(cur_entry);

        cur_entry = next_entry;
    }

    free(cache);
}

/**
 * Store an entry in the cache
 *
 * This will also remove the least-recently-used items as necessary.
 * 
 * NOTE: doesn't check for duplicate cache entries
 */
void cache_put(struct cache *cache, char *path, char *content_type, void *content, int content_length)
{
    // get timestamp, epoch seconds
    int timestamp = (int)time(NULL);
    
    // add cache entry
    struct cache_entry *cacheentry = alloc_entry(path, content_type, content, content_length, timestamp);
    dllist_insert_head(cache, cacheentry);
    hashtable_put(cache->index, path, cacheentry);
    
    cache->cur_size++;
    if (cache->cur_size <= cache->max_size) {
        return;
    }

    // reduce cache
    struct cache_entry *lastentry = dllist_remove_tail(cache);
    hashtable_delete(cache->index, lastentry->path);
}

/**
 * Retrieve an entry from the cache
 */
struct cache_entry *cache_get(struct cache *cache, char *path)
{
    struct cache_entry *cacheentry = hashtable_get(cache->index, path);

    int ts = (int)time(NULL); 
    
    // if cacheentry older than 10 sec. - remove it
    if (cacheentry && ts - (*cacheentry).timestamp > 10) {
        fprintf(stderr, "cacheentry expired: %s\n", cacheentry->path);

        dllist_remove(cache, cacheentry);
        hashtable_delete(cache->index, cacheentry->path);
        return NULL;
    } 
    else if (cacheentry) {
        dllist_move_to_head(cache, cacheentry);
        return cacheentry;
    }

    return NULL;
}