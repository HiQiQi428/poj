#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _Entry {
    char key[8];
    int value;
    struct _Entry* next;
} Entry;

Entry** table;
int mapSize;
int num;

unsigned long ELFhash(char* key) {
    unsigned long h = 0;
    for (int i = 0; i < 7; i++) {
        h = (h << 4) + key[i];
        unsigned long g = h & 0xF0000000L;
        if(g) h ^= g >> 24; 
        h &= ~g; 
    }
    return h;
}

Entry* newEntry(char key[7]) {
    Entry* ep = (Entry*)malloc(sizeof(Entry));
    for (int i = 0; i < 7; i++)
        ep->key[i] = key[i];
    ep->value = 1;
    return ep;
}

int put(char key[7]) {
    unsigned long hash = ELFhash(key);
    int index = hash % num;
    Entry *entry = table[index], *cur;
    if (entry == NULL)
        table[index] = newEntry(key);
    else {
        do {
            if (strcmp(entry->key, key) == 0) {
                entry->value++;
                return index;
            }
            cur = entry;
        } while ((entry = entry->next) != NULL);
        cur->next = newEntry(key);
    }
    mapSize++;
    return index;
}

void clean() {
    for (int i = 0; i < num; i++) {
        Entry *entry = table[i], *pre;
        while (entry != NULL) {
            pre = entry;
            entry = entry->next;
            free(pre);
        }
    }
    free(table);
}

void readData() {
    scanf("%d\n", &num);
    table = (Entry**)malloc(num * sizeof(Entry*));
    char key[7];
    for (int i = 0; i < num; i++) {
        // 读号码,并做预处理
        char c;
        int n = 0;
        while ((c = getchar()) != '\n' && c > 0) {
            if (48 <= c && c <= 57) key[n++] = c;
            else if (65 <= c && c <= 90) {
                if (c < 80) key[n++] = (c - 65) / 3 + 2 + 48;
                else if (c < 'T') key[n++] = 7 + 48;
                else if (c < 'W') key[n++] = 8 + 48;
                else key[n++] = 9 + 48;
            }
        }
        put(key);
    }
}

void output() {
    Entry* indexs[mapSize];
    int size = 0;
    // 创建字典序索引
    for (int i = 0; i < num; i++) {
        Entry *entry = table[i];
        while (entry != NULL) {
            if (entry->value > 1) {
                // 排序
                indexs[size] = entry;
                for (int j = 0; j < size; j++) {
                    if (strcmp(indexs[j]->key, entry->key) > 0) {
                        for (int k = size; k > j; k--)
                            indexs[k] = indexs[k - 1];
                        indexs[j] = entry;
                        break;
                    }
                }
                size++;
            }
            entry = entry->next;
        }
    }
    // 输出
    if (size > 0) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < 7; j++) {
                if (j == 3) putchar('-');
                putchar(indexs[i]->key[j]);
            }
            printf(" %d\n", indexs[i]->value);
        }
    }
    else printf("No duplicates.\n");
    printf("%d\n", size);
    clean();
}

int main() {
    freopen("test/input.txt", "rb", stdin);
    freopen("test/output-result.txt", "w", stdout);
    readData();
    output();
    printf("time: %f ms\n", (double)clock() / CLOCKS_PER_SEC * 1000);
    return 0;
}