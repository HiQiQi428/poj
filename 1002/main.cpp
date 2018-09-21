#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Hash + QuickSort

typedef struct _Entry {
    char key[8];
    int value;
    struct _Entry* next;
} Entry;

Entry** table;s
int mapSize = 0;
int slotSize = 0;
int num = 0;

inline unsigned long hashcode(char* key) {
    unsigned long h = 0;
	unsigned long g;
    for (int i = 0; i < 7; i++) {
        h = (h << 4) + key[i];
        g = h & 0xF0000000L;
        if(g) h ^= g >> 24; 
        h &= ~g; 
    }
    return h ^ (h >> 16);
}

Entry* newEntry(char* key) {
    Entry* ep = (Entry*)malloc(sizeof(Entry));
    for (int i = 0; i < 8; i++)
        ep->key[i] = key[i];
    ep->value = 1;
	ep->next = NULL;
    return ep;
}

inline void print(char* buf, int start, int stop) {
	for (int i = start; i < stop; i++)
		putchar(buf[i]);
}

inline int put(char* key) {
    unsigned long hash = hashcode(key);
    int index = hash % num;
    Entry *entry = table[index], *cur;
    if (entry == NULL) {
        table[index] = newEntry(key);
		slotSize++;
	}
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

int partsort(Entry** array, int left, int right) {
    Entry *&cen = array[right], *tmp;
    while(left < right) {
		while(left < right && strcmp(array[left]->key, cen->key) <= 0) ++left;
		while(left < right && strcmp(array[right]->key, cen->key) >= 0) --right;
		tmp = array[left];
		array[left] = array[right];
		array[right] = tmp;
    }
	tmp = array[left];
	array[left] = cen;
	cen = tmp;
	return left;
}

void fastsort(Entry** array, int left, int right) {
    if(left >= right) return;
    int index = partsort(array, left, right);
    fastsort(array, left, index - 1);
    fastsort(array, index + 1, right);
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
	for (int i = 0; i < num; i++) table[i] = NULL;
	char key[8] = {0};
    for (int i = 0; i < num; i++) {
        // 读取一行
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
    Entry** indexs = (Entry**)malloc(mapSize * sizeof(Entry*));
    int size = 0;
    // ��ȡ����
    for (int i = 0; i < num; i++) {
        Entry *entry = table[i];
        while (entry != NULL) {
			if (entry->value > 1)
				indexs[size++] = entry;
            entry = entry->next;
        }
    }
	// 快排
	fastsort(indexs, 0, size - 1);
    // 输出
    if (size > 0) {
        for (int i = 0; i < size; i++) {
			print(indexs[i]->key, 0, 3);
			putchar('-');
			print(indexs[i]->key, 3, 7);
            printf(" %d\n", indexs[i]->value);
        }
    }
    else printf("No duplicates.\n");
	// printf("mapSize: %d slotSize: %d mapMemSize: %d\n", mapSize, slotSize, num);
    // printf("time: %f ms\n", (double)clock() / CLOCKS_PER_SEC * 1000);
	free(indexs);
    clean();
}

int main() {
    //freopen("input.txt", "rb", stdin);
    //freopen("output.txt", "w", stdout);
    readData();
    output();
    return 0;
}