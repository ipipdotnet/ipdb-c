#include <stdio.h>
#include <stdlib.h>
#include "ipdb.h"

int main() {
    ipdb_reader *reader;
    int err = ipdb_reader_new("/root/cpp/ipdb-c/mydata6vipday4.ipdb", &reader);
    printf("new ipdb reader err: %d\n", err);
    if (!err) {
        printf("ipdb build time: %li\n", reader->meta->build_time);
        printf("ipdb ipv4 support: %i\n", ipdb_reader_is_ipv4_support(reader));
        printf("ipdb ipv6 support: %i\n", ipdb_reader_is_ipv6_support(reader));
        printf("ipdb language: ");
        for (int i = 0; i < reader->meta->language_length; ++i) {
            printf("%s ", reader->meta->language[i].name);
        }
        printf("\n");
        printf("ipdb fields: ");
        for (int i = 0; i < reader->meta->fields_length; ++i) {
            printf("%s ", reader->meta->fields[i]);
        }
        printf("\n");

        char *lang[2];
        lang[0] = "CN";
        lang[1] = "EN";
        for (int i = 0; i < 2; ++i) {
            ipdb_string_chain *body;
            err = ipdb_reader_find(reader, "2001:250:200::", lang[i], &body);
            printf("%s find err: %d\n", lang[i], err);
            if (!err) {
                ipdb_string_chain *temp = body;
                int j = 0;
                while (temp) {
                    printf("%d: %s: %s\n", j + 1, reader->meta->fields[j], temp->str);
                    ++j;
                    temp = temp->next;
                }
            }
            ipdb_string_chain_free(&body);
        }
    }
    ipdb_reader_free(&reader);
    return 0;
}