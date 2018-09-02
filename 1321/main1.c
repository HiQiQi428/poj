#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
using namespace std;
typedef long long int LL;
const int MAXN =  0x7fffffff;
const int  MINN =  -0x7fffffff;
const double eps = 1e-9;
const int dir[8][2] = {{0,1},{1,0},{0,-1},{-1,0},{-1,1},
  {1,1},{1,-1},{-1,-1}};
const int MAX = 10;
char m[MAX][MAX];int cnt, n, k, sum;
bool p[MAX];
bool judge(int i, int j) {
  if (p[j] == false && m[i][j] == '#') return true;
  else return false;
}
void dfs(int x) {
  if (sum == k) {cnt++; return;}
  if (x >= n) return;
  int i;
  for (i = 0; i < n; ++i) {
    if (judge(x, i)) {
      p[i] = true; sum++; dfs(x+1);
      p[i] = false; sum--;
    }
  }
  dfs(x + 1);
}
int main(void){
#ifndef ONLINE_JUDGE
  freopen("poj1321.in", "r", stdin);
#endif
  while (~scanf("%d%d", &n, &k)) {
    int i, j;
    if (k == -1 && n == -1) break;
    //getchar();
    for (i  = 0; i <n ; ++i) {
      for (j = 0; j < n; ++j) {
        //scanf("%c", &m[i][j]);
        cin>>m[i][j];
      }
      //getchar();
    }
    cnt = 0;
    memset(p, false, sizeof(p));
    sum = 0;
    dfs(0);
    printf("%d\n", cnt);
  }

  return 0;
}