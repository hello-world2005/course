#include <cstdio>
typedef long long ll;

const int N = 5e5 + 5, MOD = 1000000007;

int n, h[N], a[N + 1], ans1, ans2, s[N], hh[N], top;

int main() {
  int j = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &h[i]);
  a[0] = h[0];
  for (int i = 1; i < n; ++i)
    a[i] = h[i] - h[i - 1];
  a[n] = -h[n - 1];
  for (int i = 0; i <= n; ++i)
    if (a[i] > 0) {
      while (true)
        if (a[j] < 0) {
          if (a[i] < -a[j]) {
            (ans1 += ((ll)(j - i) * (j - i) % MOD) * a[i] % MOD) %= MOD;
            a[j] += a[i], a[i] = 0;
            break;
          }
          (ans1 += ((ll)(j - i) * (j - i) % MOD) * -a[j] % MOD) %= MOD;
          a[i] += a[j], a[j] = 0;
          ++j;
        } else
          ++j;
    }
  // printf("qwq\n");
  for (int i = 0; i <= n; ++i) {
    int f = i;
    while (top && h[i] <= hh[top - 1]) {
      f = s[--top];
      if (!top || h[i] > hh[top - 1])
        (ans2 += ((ll)(i - s[top]) * (i - s[top]) % MOD) * (hh[top] - h[i]) %
                 MOD) %= MOD;
      else
        (ans2 += ((ll)(i - s[top]) * (i - s[top]) % MOD) *
                 (hh[top] - hh[top - 1]) % MOD) %= MOD;
    }
    if (!top || h[i] > hh[top - 1])
      hh[top] = h[i], s[top++] = f;
  }
  printf("%d %d\n", ans1, ans2);
  return 0;
}
