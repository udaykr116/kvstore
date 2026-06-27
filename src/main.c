#include <stdio.h>
#include <kv.h>

int main() {
    kv_t *table = kv_init(1024);

    printf("%p\n",table);
    printf("%ld\n",table->capacity);

    kv_put(table,"key1","value1");
    kv_put(table,"key1","overwrite");
    kv_put(table,"key2","value2");

    char *value = kv_get(table,"key1");
    char *value2 = kv_get(table,"key2");
    char *value3 = kv_get(table,"this does not exist");
    printf("%s , %s , %s\n",value,value2,value3);


    kv_delete(table,"key1");
    value  = NULL;
    value = kv_get(table,"key1");

    printf("%s , %s , %s\n",value,value2,value3);

    kv_free(table);
    table = NULL;

    value = kv_get(table,"key1");
    printf("%s\n",value);
}