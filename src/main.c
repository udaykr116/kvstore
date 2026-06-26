#include <stdio.h>
#include <kv.h>

int main() {
    kv_t *table = kv_init(1024);

    printf("%p\n",table);
    printf("%ld\n",table->capacity);

    kv_put(table,"key1","value1");
    kv_put(table,"key1","overwrite");
    kv_put(table,"key2","overwrite");
    for(int i =0 ; i < table->capacity ; i++)
    {
       if (table->entries[i].key)
       {
           printf("[%d] %s: %s\n",i ,table->entries[i].key,table->entries[i].value);
       }
    }
}