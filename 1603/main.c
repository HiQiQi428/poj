#include <stdio.h>
#define beNumber(c) (48 <= c && c <= 57)
#define dis(from, to) list[from].distance[to]

// 最短路径

typedef struct _Node {
    char distance[20];
} Node;

void handle() {
    for (int t = 1; ; t++) {
        Node list[20] = {0};
        // create map, read 16 lines
        for (int i = 0, num, near; i < 19; i++) {
            // read one line
            if (scanf("%d ", &num) < 0) return;
            for (int k = 0; k < num; k++) {
                scanf("%d", &near);
                near--;
                dis(i, near) = 1;
                dis(near, i) = 1;
            }
        }
        // floyd
        for (int base = 0; base < 20; base++)
            for (int tar = 0; tar < 20; tar++)
                if (base != tar)
                    for (int k = 0, newDis; k < 20; k++)
                        if (tar != k && base != k && dis(tar, base) > 0 && dis(base, k) > 0) {
                            newDis = dis(tar, base) + dis(base, k);
                            if (dis(tar, k) == 0 || newDis < dis(tar, k)) {
                                dis(k, tar) = newDis;
                                dis(tar, k) = newDis;
                            }
                        }
        // output
        int num;
        scanf("%d\n", &num);
        printf("Test Set #%d\n", t);
        for (int i = 0, from, to; i < num; i++) {
            scanf("%d %d\n", &from, &to);
            printf("%d to %d: %d\n", from, to, dis(from - 1, to - 1));
        }
        printf("\n");
    }
}

int main() {
    freopen("input.txt", "rb", stdin);
    handle();
    return 0;
}