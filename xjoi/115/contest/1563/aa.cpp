#include <cstdio>

#define int long long

const int N = 10;
const int MOD = 323232323;
  
int n;
int a[N], b[N];
int ans;
int qaq[N];
int aewhtr;

bool Check() {
  int qwq = 1, sum = 0;
  for (int i = 1; i <= n; ++i)
    (qwq *= a[i]) %= MOD, (sum += qwq * qaq[i]) %= MOD;
  return sum == aewhtr; 
}

void Dfs(int dep, int lim) {
  if (!dep) {
    (ans += Check()) %= MOD;
    return;
  }
  for (int i = 0; i <= lim; ++i) {
    qaq[dep] = i;
    Dfs(dep - 1, lim * 5);
  }
}

signed main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &b[i]);
  if (n == 2) {
    int x = (a[1] * b[1] + a[1] * a[2] * b[2]) / (a[1] * a[2]);
    printf("%lld\n", x + 1);
  } else {
    int qwq = 1;
    aewhtr = 0;
    for (int i = 1; i <= n; ++i)
      (qwq *= a[i]) %= MOD, (aewhtr += qwq * b[i]) %= MOD;
    Dfs(n, 1);
    printf("%lld\n", ans);
  }
  return 0;
}
