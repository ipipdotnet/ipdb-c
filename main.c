#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/time.h>
#include "ipdb.h"

int main(const int argc, const char ** argv) {

	char * defaultDB = "/root/cpp/ipdb-c/mydata6vipday4.ipdb";
	char * db;

	if (argc == 1) {
		db = defaultDB;
	}
	else {
		db = (char *) argv[1];
	}

    ipdb_reader *reader;
    int err = ipdb_reader_new(db, &reader);
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

        char body[512];
        char tmp[64];
        char *lang[2];
        lang[0] = "CN";
        lang[1] = "EN";
        for (int i = 0; i < 2; ++i) {
            err = ipdb_reader_find(reader, "2001:250:200::", lang[i], body);
            printf("%s find err: %d\n", lang[i], err);
            if (err) continue;
            printf("%s\n", body);
            int f = 0, p1 = 0, p2 = -1;
            do {
                if (*(body + p1) == '\t' || !*(body + p1)) {
                    strncpy(tmp, body + p2 + 1, (size_t) p1 - p2);
                    tmp[p1 - p2] = 0;
                    printf("%d: %s: %s\n", f + 1, reader->meta->fields[f], tmp);
                    p2 = p1;
                    ++f;
                }
            } while (*(body + p1++));
        }
        int x = 1000000;
        struct timeval start, end;
        gettimeofday(&start, NULL);
        do {
            ipdb_reader_find(reader, "2001:250:200::", "CN", body);
        } while (--x);
        gettimeofday(&end, NULL);
        long timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
        printf("time used: %ldus.\n", timeuse);
    }
    ipdb_reader_free(&reader);
    return 0;
}
