#include <algorithm>
#include <cstdio>

typedef long long ll;

const int N = 1e5 + 10;

bool vis[N];
int pri[N], cnt;
int mu[N];

void Sieve() {
  mu[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!vis[i])
      pri[++cnt] = i, mu[i] = -1;
    for (int j = 1; j <= cnt && i * pri[j] < N; ++j) {
      vis[i * pri[j]] = true;
      if (i % pri[j] == 0) {
        mu[i * pri[j]] = 0;
        break;
      }
      mu[i * pri[j]] = -mu[i];
    }
  }
}

int fac[N];

#define MOD p

void Init(int p) {
  fac[0] = 1;
  for (int i = 1; i < N; ++i)
    fac[i] = 1ll * fac[i - 1] * i % MOD;
  for () {
  }
}

int FastPow(int a, int b, int p) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

void Solve1(int a, int b, int c, int p) {
  auto F = [=](int a, int b, int c) {
    return FastPow(fac[a], 1ll * b * c % MOD, p);
  };
  auto G = [=](int a, int b, int c) {
    int res = 0;
    for (int l = 1, r = 0; l <= std::min(a, b); l = r + 1) {
      r = std::min(a / (a / l), b / (b / l));
      (res += FastPow(, 1ll * (a / l) * (b / l) % (MOD - 1), MOD)) %= MOD;
    }
  };
}

void Solve2(int a, int b, int c, int p) {}

void Solve3(int a, int b, int c, int p) {}

int main() {
  Sieve();
  int T, p;
  scanf("%d%d", &T, &p);
  Init(p);
  while (T--) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    Solve1(a, b, c, p), Solve2(a, b, c, p), Solve3(a, b, c, p);
  }
  return 0;
}
