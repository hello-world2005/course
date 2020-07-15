#include <algorithm>
#include <cstdio>

const int N = 1e5 + 10;

struct Edge {
  int u, v, w;

  Edge() : u(0), v(0), w(0) {}
  Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
} e[N * 10];
int edge_cnt;

int fa[N];

int FindFa(int u) {
  if (u == fa[u])
    return u;
  return fa[u] = FindFa(fa[u]);
}

void Merge(int u, int v) {
  int fu = FindFa(u), fv = FindFa(v);
  if (fu != fv)
    fa[fv] = fu;
}

int f[1000];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v, w; i <= m; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    if (u == v)
      continue;
    e[++edge_cnt] = Edge(u, v, w);
  }
  for (int i = 1; i <= n; ++i)
    fa[i] = i;
  for (int i = 1; i <= edge_cnt; ++i)
    Merge(e[i].u, e[i].v);
  for (int i = 2; i <= n; ++i)
    if (FindFa(i - 1) != FindFa(i))
      return printf("No\n"), 0;
  std::sort(e + 1, e + edge_cnt + 1,
            [&](const Edge lhs, const Edge rhs) { return lhs.w < rhs.w; });
  for (int i = 1; i <= n; ++i)
    fa[i] = i;
  int res1 = 0, res2 = 0, cnt = 0;
  for (int i = 1; i <= edge_cnt; ++i) {
    if (FindFa(e[i].u) != FindFa(e[i].v))
      res1 += e[i].w, Merge(e[i].u, e[i].v), ++cnt;
    if (cnt == n - 1)
      break;
  }
  std::sort(e + 1, e + edge_cnt + 1,
            [&](const Edge lhs, const Edge rhs) { return lhs.w > rhs.w; });
  for (int i = 1; i <= n; ++i)
    fa[i] = i;
  cnt = 0;
  for (int i = 1; i <= edge_cnt; ++i) {
    if (FindFa(e[i].u) != FindFa(e[i].v))
      res2 += e[i].w, Merge(e[i].u, e[i].v), ++cnt;
    if (cnt == n - 1)
      break;
  }
  f[0] = 1, f[1] = 1;
  if (res2 < 1)
    return printf("No\n"), 0;
  if (res1 <= f[1] && f[1] <= res2)
    return printf("Yes\n"), 0;
  for (int i = 2; i <= 1000; ++i) {
    f[i] = f[i - 1] + f[i - 2];
    if (f[i] > res2)
      return printf("No\n"), 0;
    if (res1 <= f[i] && f[i] <= res2)
      return printf("Yes\n"), 0;
  }
  return 0;
}
