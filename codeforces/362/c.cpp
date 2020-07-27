#include <algorithm>
#include <cstdio>

const int N = 5e3 + 10;

int a[N];
int f[N][N], g[N][N];  // less than a[i]

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j < i; ++j)
      if (a[j] > a[i])
        ++f[i];
  int maxn = 0, ans = 0, sum = 0;
  for (int i = 1; i <= n; ++i)
    maxn = std::max(maxn, f[i]), sum += f[i];
  for (int i = 1; i <= n; ++i)
    if (maxn == f[i])
      ++ans;
  sum -= maxn;
  printf("%d %d\n", ans, sum);
}
