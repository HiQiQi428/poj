#include <stdio.h>

void output(char board[9][9]) {
    printf("\n!");
    for (int i = 0; i < 9; i++)
        printf(" %d", i);
    printf("\n");
    for (int i = 0; i < 9; i++) {
        printf("%d", i);
        for (int j = 0; j < 9; j++)
            printf(" %d", board[i][j]);
        printf("\n");
    }
}

void handle() {
    int n, k;
    char board[9][9] = {0}, c;
    scanf("%d %d\n", &n, &k);
    do {
        for (int i = 0; i < n; i++)
            for (int j = 0; (c = getchar()) != '\n'; j++) {
                board[i][j] = c == '#' ? 1 : 0;
            }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {}
        for (int i = 0; i < n; i++) {
            board[8][i] = 0;
            board[i][8] = 0;
        }
        scanf("%d %d\n", &n, &k);
    } while (n > 0);
}

int main() {
    freopen("input.txt", "rb", stdin);
    handle();
    return 0;
}