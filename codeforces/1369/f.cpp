#include <cstdio>

typedef long long ll;

const int N = 1e5 + 10;

ll s[N], e[N];
bool dp[N][2];

int Solve(ll s, ll e, int op) {
  if ((e & 1) && (!op))
    return (e - s) & 1;
  ll h = e >> 1;
  if (s > h)
    return op ? 1 : (e - s) & 1;
  return Solve(s, h, op ^ 1);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lld%lld", &s[i], &e[i]), dp[i][0] = Solve(s[i], e[i], 0),
                                     dp[i][1] = Solve(s[i], e[i], 1);
  bool flag = dp[n][0];
  for (int i = n - 1; i; --i)
    flag = dp[i][flag];
  printf("%d ", flag);
  flag = dp[n][1];
  for (int i = n - 1; i; --i)
    flag = dp[i][flag];
  printf("%d\n", flag);
  return 0;
}
