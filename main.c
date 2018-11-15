#include <stdio.h>
#include <stdlib.h>
#include "ipdb.h"

int main() {
    printf("Hello, World!\n");
    printf("%zu, %zu, %zu\n", sizeof(short), sizeof(int), sizeof(long));
    ipdb_reader *reader;
    int err = ipdb_reader_new("/root/cpp/ipdb-c/mydata6vipday4.ipdb", &reader);
    printf("err: %d\n", err);
    {
        ipdb_string_vector *body;
        err = ipdb_reader_find(reader, "2001:250:200::", "CN", &body);
        printf("\nerr: %d\n", err);
        ipdb_string_vector *temp = body;
        int i = 0;
        while (temp) {
            printf("%d: %s\n", ++i, temp->str);
            temp = temp->next;
        }
        ipdb_string_vector_free(&body);
    }
    {
        ipdb_string_vector *body;
        err = ipdb_reader_find(reader, "2001:250:200::", "EN", &body);
        printf("\nerr: %d\n", err);
        ipdb_string_vector *temp = body;
        int i = 0;
        while (temp) {
            printf("%d: %s\n", ++i, temp->str);
            temp = temp->next;
        }
        ipdb_string_vector_free(&body);
    }
    return 0;
}