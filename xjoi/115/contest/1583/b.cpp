#include <cstdio>

#define int long long

const int MOD = 1e9 + 7;
const int N = 20;

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = a * a % MOD)
    if (b & 1)
      res = res * a % MOD;
  return res;
}

int n;
int l[N], a[N][2530];
int ans[N];

const int FAC = 318608048;
const int INV = 800396831;

char s[N];

signed main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &l[i]);
    scanf("%s", s + 1);
    for (int j = 1; j <= l[i]; ++j)
      a[i][j] = (s[j] == 'O');
  }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= l[i]; ++j)
      for (int k = l[i] + j; k <= 2520; k += l[i])
        a[i][k] = a[i][j];
  for (int i = 1; i <= 2520; ++i) {
    int t = 0;
    for (int j = 1; j <= n; ++j)
      t += a[j][i];
    ++ans[t];
  }
  for (int i = 1; i <= n; ++i)
    printf("%lld\n", ans[i] * FAC % MOD * INV % MOD);
  return 0;
}
