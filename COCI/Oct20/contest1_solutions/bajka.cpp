#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)

const int MAXN = 305;
const int inf = 1000000;

int n, m, dp[MAXN][MAXN];
char s[MAXN], p[MAXN];

int rek(int a, int b) {
  if (b == m) return 0;
  if (dp[a][b] != -1) return dp[a][b];
  int ret = inf;
  REP(i, n) {
    if (s[i] == s[a]) {
      FOR(j, -1, 2) {
        if (!j || i + j < 0 || i + j >= n) continue;
        if (s[i + j] != p[b]) continue;
        ret = min(ret, rek(i + j, b + 1) + abs(i - a) + 1);
      }
    }
  }
  return dp[a][b] = ret;
}

int main() {
  scanf("%d %d",&n,&m);
  scanf("%s",s);
  scanf("%s",p);
  memset(dp, -1, sizeof dp);
  int sol = inf;
  REP(i, n) if (s[i] == p[0]) sol = min(sol, rek(i, 1));
  if (sol >= inf) sol = -1;
  printf("%d\n",sol);
  return 0;
}

