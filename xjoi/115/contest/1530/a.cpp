#include <algorithm>
#include <cstdio>
#include <unordered_map>
#include <vector>

typedef long long ll;

int n, m, k;
std::vector<std::vector<int> > a;
std::unordered_map<int, int> ma;

void Push() {
  for (int i = 2; i <= n; ++i) {
    ma.clear();
    for (int j = 1; j <= m; ++j)
      ++ma[a[i - 1][j]], a[i][j] = ma[a[i - 1][j]];
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  if (1ll * m * k <= (ll)1e7) {
    a.resize(n + 1);
    for (int i = 1; i <= n; ++i)
      a[i].resize(m + 1);
    for (int i = 1; i <= m; ++i)
      scanf("%d", &a[1][i]);
    bool flag = true;
    while (k--) {
      int opt, x, y;
      scanf("%d%d%d", &opt, &x, &y);
      if (opt == 0) {
        if (flag)
          Push(), flag = false;
        printf("%d\n", a[x][y]);
      } else {
        a[1][x] = y;
        flag = true;
      }
    }
  } else {
    a.resize(4);
    for (int i = 1; i <= 3; ++i)
      a[i].resize(m + 1);
    for (int i = 1; i <= m; ++i)
      scanf("%d", &a[1][i]);
    for (int i = 2; i <= 3; ++i) {
      ma.clear();
      for (int j = 1; j <= m; ++j)
        ++ma[a[i - 1][j]], a[i][j] = ma[a[i - 1][j]];
    }
    while (k--) {
      int opt, x, y;
      scanf("%d%d%d", &opt, &x, &y);
      if (x <= 3)
        printf("%d\n", a[x][y]);
      else
        printf("%d\n", a[x % 2 + 2][y]);
    }
  }
  return 0;
}
