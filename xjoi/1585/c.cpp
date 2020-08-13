#include <cstdio>
#include <cstring>

#define int long long

const int N = 1e6 + 10;

bool vis[N];
int pri[N], cnt;

int ans, n, p;
int sum[N];

void Dfs(int dep, int now) {
  if (pri[dep] == -1 || now * pri[dep] > n)
    return ++ans, void();
  if (now * pri[dep] * pri[dep] > n) {
    int t;
    if (n / now > p)
      t = sum[p];
    else
      t = sum[n / now];
    ans += (t - dep + 2);
    return;
  }
  Dfs(dep + 1, now);
  int k = pri[dep];
  while (k * now <= n) {
    Dfs(dep + 1, now * k);
    k *= pri[dep] * pri[dep];
  }
}

void Sieve(int n) {
  vis[1] = true;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i])
      pri[++cnt] = i;
    for (int j = 1; j <= cnt && i * pri[j] <= n; ++j) {
      vis[i * pri[j]] = true;
      if (i % pri[j] == 0)
        break;
    }
  }
  pri[++cnt] = -1;
}

signed main() {
  scanf("%lld%lld", &n, &p);
  Sieve(p);
  for (int i = 1; i <= p; i++) {
    sum[i] = sum[i - 1];
    if (vis[i] == 0)
      sum[i] = sum[i - 1] + 1;
  }
  Dfs(1, 1);
  printf("%lld\n", ans);
  return 0;
}