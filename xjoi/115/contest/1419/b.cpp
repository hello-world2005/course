#include <cstdio>
#include <unordered_map>

#define int long long

int n, m;
int k[10], p[10];
std::unordered_map<int, int> um;

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = a * a)
    if (b & 1)
      res = res * a;
  return res;
}

void Dfs1(int u, int sum) {
  if (u == n / 2 + 1) {
    ++um[sum];
    return;
  }
  for (int i = 1; i <= m; ++i)
    Dfs1(u + 1, sum + FastPow(i, p[u]) * k[u]);
}

int ans;

void Dfs2(int u, int sum) {
  if (u == n + 1) {
    int _sum = -sum;
    ans += um[_sum];
    return;
  }
  for (int i = 1; i <= m; ++i)
    Dfs2(u + 1, sum + FastPow(i, p[u]) * k[u]);
}

signed main() {
  scanf("%lld%lld", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%lld%lld", &k[i], &p[i]);
  Dfs1(1, 0);
  Dfs2(n / 2 + 1, 0);
  printf("%lld\n", ans);
  return 0;
}
