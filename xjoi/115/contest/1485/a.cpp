#include <cstdio>
// #include <unordered_map>

#define int long long

const int N = 2e5;
const int MOD = 1e4 + 7;

// std::unordered_map<std::piar<int, int> > has;
int fac[N], inv[N];

int FastPow(int a, int b) {
  int res = 1;
  for (; b; a = a * a % MOD, b >>= 1)
    if (b & 1)
      res = res * a % MOD;
  return res;
}

void Init() {
  fac[0] = inv[0] = 1;
  for (int i = 1; i < MOD; ++i) {
    fac[i] = fac[i - 1] * i % MOD;
    inv[i] = FastPow(fac[i], MOD - 2);
  }
}

int C(int n, int m) {
  return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

// int Lucas(int a, int b) {
//   if (has[std::make_pair(a, b)])
//     return has[std::make_pair(a, b)];
//   if (a < MOD && b < MOD)
//     return C(a, b);
//   return Lucas(a / MOD, b / MOD) * (Lucas(a % MOD, b % MOD));
// }

int Read() {
  char c = getchar();
  int x = 0;
  while (c < '0' || c > '9')
    c = getchar();
  while (c >= '0' && c <= '9') {
    x = (x * 10 + c - '0') % MOD;
    c = getchar();
  }
  return x;
}

signed main() {
  int n = Read();
  Init();
  n += 2;
  // printf("%lld %lld\n", n, inv[2]);
  printf("%lld\n", C(n, 3));
  return 0;
}
