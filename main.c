#include <stdio.h>
#include "ipdb.h"

int main() {
    printf("Hello, World!\n");
    printf("%zu, %zu, %zu\n", sizeof(short), sizeof(int), sizeof(long));
    ipdb_reader *reader;
    int err = ipdb_reader_new("/root/cpp/ipdb-c/mydata6vipday4.ipdb", &reader);
    printf("err: %d", err);

    const char* body;
    err = ipdb_find0(reader, "2001:250:200::", &body);
    printf("err: %d, %s", err, body);
    ipdb_reader_free(&reader);
    return 0;
}