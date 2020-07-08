#include <algorithm>
#include <cstdio>

const int N = 2e4 + 10;
const int M = 1e5 + 10;

int n, m;
struct Node {
  int a, b, c;

  Node() : a(0), b(0), c(0) {}

  bool operator<(const Node& rhs) const { return c > rhs.c; }
} a[M];
int b[N];
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

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    fa[i] = i;
  for (int i = 1; i <= m; ++i)
    scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].c);
  std::sort(a + 1, a + m + 1);
  for (int i = 1; i <= m; ++i) {
    if (FindFa(a[i].a) == FindFa(a[i].b)) {
      printf("%d\n", a[i].c);
      return 0;
    }
    if (!b[a[i].a])
      b[a[i].a] = a[i].b;
    else
      Merge(b[a[i].a], a[i].b);
    if (!b[a[i].b])
      b[a[i].b] = a[i].a;
    else
      Merge(b[a[i].b], a[i].a);
  }
  printf("0\n");
  return 0;
}
