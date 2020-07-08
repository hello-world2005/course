#include <cstdio>

const int N = 510;

int in[N], ou[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    ++ou[u], ++in[v];
  }
  for (int i = 1; i <= n; ++i)
    if (in[i] != ou[i])
      return printf("No\n"), 0;
  printf("Yes\n");
  return 0;
}
