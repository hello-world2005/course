#include <algorithm>
#include <cstdio>

const int N = 510;

struct Edge {
  int u, v, w;

  Edge() : u(0), v(0), w(0) {}

  bool operator<(const Edge& rhs) const { return w < rhs.w; }
} e[N * N];
int fa[N];

int FindFa(int u) {
  if (fa[u] == u)
    return u;
  return fa[u] = FindFa(fa[u]);
}

void Merge(int u, int v) {
  int fu = FindFa(u), fv = FindFa(v);
  if (fu != fv)
    fa[fv] = fu;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    fa[i] = i;
  for (int i = 1; i <= m; ++i)
    scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
  std::sort(e + 1, e + m + 1);
  int cnt = 0, maxn = 0;
  for (int i = 1; i <= m; ++i) {
    if (FindFa(e[i].u) != FindFa(e[i].v)) {
      Merge(e[i].u, e[i].v);
      maxn = std::max(maxn, e[i].w);
      if ((++cnt) == n - 1)
        return printf("%d\n", e[i].w), 0;
    }
  }
  printf("%d\n", maxn);
  return 0;
}
