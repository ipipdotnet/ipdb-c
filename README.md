# ipdb-c
IPIP.net officially supported IP database ipdb format parsing library

## Dependence
```sh
dnf install json-c-devel
```

## Build & Run & Output
```sh
gcc -std=gnu99 main.c ipdb.c -ljson-c -o main

./main

new ipdb reader err: 0
ipdb build time: 1535451865
ipdb ipv4 support: 0
ipdb ipv6 support: 1
ipdb language: CN EN 
ipdb fields: country_name region_name city_name owner_domain isp_domain latitude longitude timezone utc_offset china_admin_code idd_code country_code continent_code idc base_station country_code3 european_union currency_code currency_name anycast 
CN find err: 0
中国	北京	北京	清华大学网络科学与网络空间研究院	教育网	39.904989	116.405285	Asia/Shanghai	UTC+8	110000	86	CN	AP			CHN	0	CNY	Yuan Renminbi	
1: country_name: 中国	
2: region_name: 北京	
3: city_name: 北京	
4: owner_domain: 清华大学网络科学与网络空间研究院	
5: isp_domain: 教育网	
6: latitude: 39.904989	
7: longitude: 116.405285	
8: timezone: Asia/Shanghai	
9: utc_offset: UTC+8	
10: china_admin_code: 110000	
11: idd_code: 86	
12: country_code: CN	
13: continent_code: AP	
14: idc: 	
15: base_station: 	
16: country_code3: CHN	
17: european_union: 0	
18: currency_code: CNY	
19: currency_name: Yuan Renminbi	
20: anycast: 
EN find err: 0
China	Beijing	Beijing		CHINAEDU	39.904989	116.405285	Asia/Shanghai	UTC+8	110000	86	CN	AP			CHN	0	CNY	Yuan Renminbi	
1: country_name: China	
2: region_name: Beijing	
3: city_name: Beijing	
4: owner_domain: 	
5: isp_domain: CHINAEDU	
6: latitude: 39.904989	
7: longitude: 116.405285	
8: timezone: Asia/Shanghai	
9: utc_offset: UTC+8	
10: china_admin_code: 110000	
11: idd_code: 86	
12: country_code: CN	
13: continent_code: AP	
14: idc: 	
15: base_station: 	
16: country_code3: CHN	
17: european_union: 0	
18: currency_code: CNY	
19: currency_name: Yuan Renminbi	
20: anycast: 
time used: 2027772us.
```

## Example
```c
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/time.h>
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
```