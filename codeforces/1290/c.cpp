#include <algorithm>
#include <cstdio>
#include <vector>

const int N = 6e5 + 10;

int n, m;
int a[N];
int fa[N], sze[N][2];
int ans;

int FindFa(int u) {
  if (u == fa[u])
    return u;
  return fa[u] = FindFa(fa[u]);
}

void Merge(int u, int v) {
  int fu = FindFa(u);
  int fv = FindFa(v);
  if (fu == fv)
    return;
  ans -= std::min(sze[fu][0], sze[fu][1]) + std::min(sze[fv][0], sze[fv][1]);
  sze[fu][0] += sze[fv][0];
  sze[fu][1] += sze[fv][1];
  fa[fv] = fu;
  ans += std::min(sze[fu][0], sze[fu][1]);
}

int se[N][2];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i <= (m + 1) * 2; ++i)
    fa[i] = i, sze[i][i >= (m + 1)] = 1;
  for (int i = 1; i <= n; ++i)
    scanf("%1d", &a[i]);
  for (int i = 1, k; i <= m; ++i) {
    scanf("%d", &k);
    for (int j = 1, c; j <= k; ++j) {
      scanf("%d", &c);
      se[c][se[c][0] > 0] = i;
    }
  }
  ++m;
  // for (int i = 1; i <= m; ++i)
  //   std::sort(s[i].begin(), s[i].end());
  for (int i = 1; i <= n; ++i) {
    if (a[i]) {
      Merge(se[i][0], se[i][1]);
      Merge(se[i][0] + m, se[i][1] + m);
    } else {
      Merge(se[i][0], se[i][1] + m);
      Merge(se[i][0] + m, se[i][1]);
    }
    int rt = FindFa(0);
    if (sze[rt][0] < sze[rt][1])
      printf("%d\n", ans / 2 - sze[rt][0] + sze[rt][1]);
    else
      printf("%d\n", ans / 2);
  }
  return 0;
}
