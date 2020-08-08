#include <cstdio>

const int N = 2e5 + 10;

int fa[N][2], sze[N][2];

int Find(int u, int col) {
  if (u == fa[u][col])
    return u;
  return fa[u][col] = Find(fa[u][col], col);
}

void Merge(int u, int v, int col) {
  int fu = Find(u, col), fv = Find(v, col);
  if(fu != fv)
    fa[fv][col] = fu, sze[fu][col] += sze[fv][col];
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    fa[i][0] = fa[i][1] = i, sze[i][0] = sze[i][1] = 1;
  for (int i = 2, u, v, w; i <= n; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    Merge(u, v, w);
  }
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (fa[i][0] == i)
      ans = (ans + 1ll * sze[i][0] * (sze[i][0] - 1));
    if (fa[i][1] == i)
      ans = (ans + 1ll * sze[i][1] * (sze[i][1] - 1));
    int qwq = Find(i, 0), qaq = Find(i, 1);
    ans = (ans + 1ll * (sze[qwq][0] - 1) * (sze[qaq][1] - 1));
  }
  printf("%lld\n", ans);
  return 0;
}
