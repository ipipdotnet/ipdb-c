#include <stdio.h>
#include "ipdb.h"

int main() {
    printf("Hello, World!\n");
    printf("%zu, %zu, %zu\n", sizeof(short), sizeof(int), sizeof(long));
    ipdb_reader *reader;
    int err = ipdb_reader_new("/root/cpp/ipdb-c/mydata6vipday4.ipdb", &reader);
    printf("err: %d", err);
    ipdb_reader_free(&reader);
    return 0;
}