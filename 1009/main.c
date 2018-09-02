#include <stdio.h>
#include <stdlib.h>

#define max(a, b) (a > b ? a : b)
#define dif(a, b) abs(a - b)
#define compare(r1, c1, r2, c2) { \
    int tmp = dif(numBuf[r1][c1], numBuf[r2][c2]); \
    difBuf[r1][c1] = max(tmp, difBuf[r1][c1]); \
    difBuf[r2][c2] = max(tmp, difBuf[r2][c2]); \
}

void indexHandle(int colNum) {
    int num[1000], size[1000], cursor;
    long imageSize;
    do {
        scanf("%d %d\n", (int*)(num + cursor), (int*)(size + cursor));
        imageSize += size[cursor];
    } while (size[cursor++] != 0);
    for (int i = 0; i < imageSize; i++) {
        
    }
}

void bufferHandle(int colNum) {
    int numBuf[2][colNum], difBuf[2][colNum], rowCur = 0, colCur = 0;
    int inNum = -1, outNum = -1;
    long inSize = -1, outSize;
    while (inSize != 0) {
        scanf("%d %ld\n", &inNum, &inSize);
        int i = 0;
        // 优化
        int r = inSize / colNum;
        char wantOptimize = 0;
        if (r > 2) {
            if (rowCur == 0) {
                r -= 2;
                outNum = 0;
                i = outSize = r * colNum;
            }
            else wantOptimize = 1;
        }
        // 处理
        for (; i < inSize; i++) {
            numBuf[rowCur][colCur] = inNum;
            difBuf[rowCur][colCur] = 0;
            // modify dif buf
            if (colCur > 0) {
                compare(rowCur, colCur, rowCur, colCur - 1);
                if (rowCur > 0) compare(rowCur, colCur, rowCur - 1, colCur - 1);
            }
            if (rowCur > 0) {
                compare(rowCur, colCur, rowCur - 1, colCur);
                if (colCur < colNum - 1) compare(rowCur, colCur, rowCur - 1, colCur + 1);
            }
            // 修改colCur rowCur
            colCur++;
            if (colCur == colNum) {
                rowCur++;
                colCur = 0;
                if (rowCur == 2) {
                    // 输出第0行
                    for (int i = 0; i < colNum; i++) {
                        if (outNum < 0) {
                            outNum = difBuf[0][i];
                            outSize = 1;
                        }
                        else if (difBuf[0][i] == outNum) outSize++;
                        else {
                            printf("%d %ld\n", outNum, outSize);
                            outNum = difBuf[0][i];
                            outSize = 1;
                        }
                        // 拷贝第1行到第0行
                        difBuf[0][i] = difBuf[1][i];
                        numBuf[0][i] = numBuf[1][i];
                    }
                    rowCur = 1;
                    // 优化
                    if (wantOptimize && outSize > colNum) {
                        r = (inSize - i) / colNum;
                        if (r > 2) {
                            r -= 2;
                            if (outNum != 0) {
                                printf("%d %ld\n", outNum, outSize);
                                outNum = 0;
                                outSize = 0;
                            }
                            outSize += r * colNum;
                            i += r * colNum;
                        }
                        wantOptimize = 0;
                    }
                }
            }
        }
    }
    // 输出第1行
    for (int i = 0; i < colNum; i++) {
        if (difBuf[1][i] == outNum) outSize++;
        else {
            printf("%d %ld\n", outNum, outSize);
            outNum = difBuf[1][i];
            outSize = 1;
        }
    }
    printf("%d %ld\n0 0\n", outNum, outSize);
}

int main() {
    freopen("input.txt", "rb", stdin);
    int colNum;
    scanf("%d\n", &colNum);
    while (colNum != 0) {
        printf("%d\n", colNum);
        if (colNum > 1000000) return 1;
        else bufferHandle(colNum);
        scanf("%d\n", &colNum);
    }
    return 0;
}