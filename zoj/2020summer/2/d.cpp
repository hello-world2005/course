#include <cstdio>

#define int long long

const int N = 5e6 + 10;

bool vis[N];
int prime[N], cnt;
int phi[N];
int ans[N];

void Init() {
  phi[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!vis[i])
      prime[++cnt] = i, phi[i] = i - 1;
    for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
      vis[i * prime[j]] = true;
      if (i % prime[j] == 0) {
        phi[i * prime[j]] = phi[i] * prime[j];
        break;
      }
      phi[i * prime[j]] = phi[i] * phi[prime[j]];
    }
  }
  for (int i = 1; i < N; ++i)
    phi[i] += phi[i - 1];
  for (int i = 1; i < N; ++i)
    ans[i] = phi[i] * 2 - 1;
}

int Solve(int n) {
  // int res = 0;
  // for (int l = 1, r = 0; l <= n; l = r + 1)
  //   r = n / (n / l), res += 1ll * (n / l) * (n / l) * (mu[r] - mu[l - 1]);
  // return res;
  return ans[n];
}

signed main() {
  Init();
  int T;
  scanf("%lld", &T);
  // for (int i = 1; i <= 10; ++i)
  //   printf("%lld\n", Solve(1));
  while (T--) {
    int n, m;
    scanf("%lld%lld", &n, &m);
    if (m == 1)
      printf("1\n");
    else if (m == n + 1)
      printf("3\n");
    else if (m > n + 1)
      printf("0\n");
    else
      printf("%lld\n", Solve(n / (m - 1)) - Solve(n / m));
  }
}
