#include <kv.h>
#include <string.h>
#include <stdlib.h>


size_t hash(char *val , int capacity)
{
    size_t hash = 0x12345678abcdefa;
    while(*val)
    {
        hash ^= *val ;
        hash = hash << 8 ;
        hash += *val ;

        val++ ;
    }
    return hash % capacity;

}

// function kv_delete
// params:
//  -db:  a pointer to the db
//  -key: a pointer to key
// returns: index of deletion
// -1   if not found
int kv_delete(kv_t *db , char *key){
    if (!db || !key) return -1 ;
    size_t idx = hash(key , db->capacity);
    for(int i = 0 ; i < db->capacity ; i++)
    {
        size_t real_idx = (idx + i) % db->capacity ;
        kv_entry_t *entry  = &db->entries[real_idx];

        if (entry->key == NULL) return -1 ;
        if (entry->key && entry->key != TOMBSTONE && !strcmp(entry->key , key ))
        {
            free(entry->key);
            free(entry->value);
            entry->key = TOMBSTONE;
            entry->value = NULL;
            db->count--;
            return real_idx ;
        }
    }
    return -1 ;
}



// funtion kv_get 
// params:
//  -db:  a pointer to the db
//  -key: a pointer to key
// returns: a pointer to the value , otherwise on
// error return NULL , on not found return NULL

char *kv_get(kv_t *db , char *key){
    if (!db || !key) return NULL ;
    
    size_t idx = hash(key , db->capacity);
    for(int i = 0 ; i < db->capacity ; i++)
    { 
        size_t real_idx = (idx + i) % db->capacity ;
        kv_entry_t *entry  = &db->entries[real_idx];

        // if no key , return nothing 
        if (entry->key == NULL) return NULL ;

        // find an entry and keys match 
        if (entry->key && entry->key != TOMBSTONE && !strcmp(entry->key , key ))
        {
            return entry->value ;
        }
    }
    return NULL ;
}

// funtion kv_put 
// params: 
//  -db:  a pointer to the db 
//  -key: a pointer to key 
//  -value: to pointer to value itself 
// returns: the index of the key , otherwise on 
// error return -1 , on not found return -2 
int kv_put(kv_t *db , char *key , char *value)
{
    if (!db || !key || !value) return -1 ;

    size_t idx = hash(key , db->capacity);
    for (int i = 0 ; i < db->capacity ; i++)
    {
        size_t real_idx = (idx  + i) % db->capacity ;

        kv_entry_t *entry  = &db->entries[real_idx];

        //found the slot , occupied and the key matches 
        if (entry->key && ( entry->key != TOMBSTONE ) && !strcmp(entry->key , key ))
        {
            char *newval = strdup(value);
            if (!newval) return -1 ;
            entry->value = newval;
            return real_idx ;
        }

        // found the slot and its either empty or tombstone
        if(!entry->key || ( entry->key == TOMBSTONE )){
            char *newval = strdup(value);
            char *newkey = strdup(key);
            if (!newval || !newkey)
            {
                free(newkey);
                free(newval);
                return -1 ;
            }
            entry->value = newval;
            entry->key = newkey;
            db->count++;
            return  real_idx ;
        }
    }
    return -2 ;
}

kv_t *kv_init(size_t capacity)
{
    if (capacity ==0) return NULL;

    kv_t *table = malloc(sizeof(kv_t));
    if (table == NULL){
        return NULL;
    }

    table-> capacity = capacity;
    table-> count = 0 ;
    table-> entries = calloc(sizeof(kv_entry_t),capacity);
    if (table-> entries==NULL){
        return NULL;
    }

    return table;
}