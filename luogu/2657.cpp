#include <cstdio>
#include <cstring>

const int N = 10;

int len, n[N];
int f[N][N];

int Dfs(int pos, int pre, bool ismax, bool zero) {
  // printf("%d %d %d %d\n", pos, pre, ismax, zero);
  if (pos < 1)
    return 1;
  if (!ismax && !zero && ~f[pos][pre])
    return f[pos][pre];
  int lim = ismax ? n[pos] : 9, res = 0;
  for (int i = 0; i <= lim; ++i)
    if (pre - i <= -2 || pre - i >= 2)
      res += Dfs(pos - 1, (zero && i == 0) ? -2 : i, ismax && (i == lim), zero && (i == 0));
  if (!ismax && !zero)
    f[pos][pre] = res;
  return res;
}

int Solve(int x) {
  len = 0;
  while (x) {
    n[++len] = x % 10;
    x /= 10;
  }
  // printf("> %d\n", len);
  return Dfs(len, -2, true, true);
}

int main() {
  int a, b;
  scanf("%d%d", &a, &b);
  memset(f, -1, sizeof(f));
  // printf("%d %d\n", Solve(a - 1), Solve(b));
  printf("%d\n", Solve(b) - Solve(a - 1));
  return 0;
}
