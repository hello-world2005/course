#include <cstdio>
#include <cstring>

#define int long long

const int N = 15;

int f[N][N][N][2][2][2][2];
int n[N], len;

int Dfs(int pos,
        int pre1,
        int pre2,
        bool qwq,
        bool ismax,
        bool four,
        bool eight) {
  if (four && eight)
    return 0;
  if (pos < 1)
    return qwq;
  if (~f[pos][pre1][pre2][qwq][ismax][four][eight])
    return f[pos][pre1][pre2][qwq][ismax][four][eight];
  int lim = ismax ? n[pos] : 9, res = 0;
  for (int i = 0; i <= lim; ++i)
    res += Dfs(pos - 1, i, pre1, qwq || (i == pre1 && pre1 == pre2),
               ismax && (i == lim), four || i == 4, eight || i == 8);
  // if (!ismax)
    f[pos][pre1][pre2][qwq][ismax][four][eight] = res;
  return res;
}

int Solve(long long x) {
  // if (x <= (int)1e10)
  //   return 0;
  // len = 0;
  // while (x) {
  //   n[++len] = x % 10;
  //   x /= 10;
  // }
  // return Dfs(len, 11, 11, false, true, true, false, false);
  if (x < 1e10)
    return 0;
  memset(f, -1, sizeof(f));
  for (len = 0; x; x /= 10)
    n[++len] = x % 10;
  int res = 0;
  for (int i = 1; i <= n[len]; i++)
    res += Dfs(10, i, 0, 0, i == n[len], i == 4, i == 8);
  return res;
}

signed main() {
  long long a, b;
  scanf("%lld%lld", &a, &b);
  memset(f, -1, sizeof(f));
  // printf("%lld %lld\n", Solve(a - 1), Solve(b));
  printf("%lld\n", Solve(b) - Solve(a - 1));
  return 0;
}
