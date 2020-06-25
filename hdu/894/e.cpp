#include <cstdio>

const int N = 1e5 + 10;

int sze[N];
bool cut[N];

int Find(int u) {
  while (!cut[u] && u > 1)
    u >>= 1;
  return sze[u];
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = n; i >= 1; --i) {
      ++sze[i];
      sze[i >> 1] += sze[i];
    }
    int ans = n * (n - 1) / 2;
    while (m--) {
      int u;
      scanf("%d", &u);
      if (cut[u]) {
        int x = Find(u), y = Find(u >> 1);
        ans -= x * (x - 1) / 2 + y * (y - 1) / 2;
        cut[u] = false;
        for (int x = u; x; x >>= 1) {
          sze[x] = 1;
          for (int y = x << 1; y <= (x << 1 | 1); ++y)
            if (y <= n)
              if (!cut[y])
                sze[x] += sze[y];
        }
        x = Find(u);
        ans += x * (x - 1) / 2;
      } else {
        int x = Find(u), y;
        ans -= x * (x - 1) / 2;
        cut[u] = true;
        for (int x = u; x; x >>= 1) {
          sze[x] = 1;
          for (int y = x << 1; y <= (x << 1 | 1); ++y)
            if (y <= n)
              if (!cut[y])
                sze[x] += sze[y];
        }
        x = Find(u), y = Find(u >> 1);
        ans += x * (x - 1) / 2 + y * (y - 1) / 2;
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}
