#include <stdio.h>

int judge(int b, int s) {
    if (s > 1) {
        b -= s - 1;
        s = 1;
    }
    return b % 2 == 0 ? 0 : 1;
}

int main() {
    freopen("input.txt", "rb", stdin);
    int a, b, result;
    while (scanf("%d %d\n", &a, &b) > 0) {
        result = a == b ? 1 : (a > b ? judge(a, b) : judge(b, a));
        printf("%d\n", result);
    }
    return 0;
}