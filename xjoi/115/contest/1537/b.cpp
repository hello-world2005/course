#include <cmath>
#include <cstdio>
#include <map>

#define MOD p
#define int long long

const int N = 1e5 + 10;

int FastPow(int a, int b, int p) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

int Gcd(int a, int b) {
  if (b == 0)
    return a;
  return Gcd(b, a % b);
}

int ExGcd(int a, int b, int& x, int& y) {
  if (b == 0)
    return x = 1, y = 0, a;
  int d = ExGcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

int Bsgs(int a, int b, int p, int now) {
  std::map<int, int> has;
  int sze = ceil(sqrt(p)), t, x, y;
  ExGcd(now, p, x, y);
  b = (b * x % p + p) % p;
  t = FastPow(a, sze, p);
  ExGcd(t, p, x, y);
  t = (x % p + p) % p;
  for (int i = 1, j = 0; j <= sze; ++j, i = i * a % p)
    if (!has.count(i))
      has[i] = j;
  for (int i = b, j = 0; j <= sze; ++j, i = i * t % p)
    if (has[i])
      return j * sze + has[i];
  return -1;
}

int ExBsgs(int a, int b, int p) {
  int now = 1;
  int k = 0, t = 1;
  if (b == 1)
    return 0;
  while ((t = Gcd(a, p)) > 1) {
    if (b % t)
      return -1;
    ++k;
    b /= t, p /= t;
    now = now * (a / t) % p;
    if (now == b)
      return k;
  }
  t = Bsgs(a, b, p, now);
  if (t == -1)
    return -1;
  return t + k;
}

int Fac(int n, int p, int pk) {
  if (n == 0)
    return 1;
  int rou = 1, rem = 1;
  for (int i = 1; i <= pk; ++i)
    if (i % p)
      rou = rou * i % pk;
  rou = FastPow(rou, n / pk, pk);
  for (int i = pk * (n / pk); i <= n; ++i)
    if (i % p)
      rem = rem * (i % pk) % pk;
  return Fac(n / p, p, pk) * rou % pk * rem % pk;
}

int G(int n, int p) {
  if (n < p)
    return 0;
  return G(n / p, p) + (n / p);
}

int Inv(int a, int p) {
  int x, y;
  ExGcd(a, p, x, y);
  return (x + p) % p;
}

int C(int a, int b, int p, int pk) {
  int fac = Fac(a, p, pk), inv1 = Inv(Fac(b, p, pk), pk),
      inv2 = Inv(Fac(a - b, p, pk), pk);
  // printf("$%lld %lld %lld\n", G(a, p), G())
  int mi = FastPow(p, G(a, p) - G(b, p) - G(a - b, p), pk);
  // printf("@\n");
  return fac * inv1 % pk * inv2 % pk * mi % pk;
}

int a[N], b[N];

int ExLucas(int y, int z, int p) {
  // !@#$%^&*()
  int tot = 0, _p = p;
  // printf("!\n");
  for (int i = 2; i * i <= p; ++i) {
    // printf("%lld\n", i);
    if (p % i == 0) {
      int k = 1;
      while (p % i == 0)
        k *= i, p /= i;
      a[++tot] = k;
      // printf("#\n");
      b[tot] = C(y, z, i, k);
    }
  }
  if (p != 1) {
    a[++tot] = p;
    b[tot] = C(y, z, p, p);
  }
  p = _p;
  int res = 0;
  for (int i = 1; i <= tot; ++i) {
    int t = p / a[i], inv = Inv(t, a[i]);
    res = (res + b[i] * t % MOD * inv % MOD) % MOD;
  }
  return res;
}

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int opt, x, y, z, p;
    scanf("%lld%lld%lld%lld", &opt, &y, &z, &p);
    if (opt == 1) {
      printf("%lld\n", FastPow(y, z, p));
    } else if (opt == 2) {
      x = ExBsgs(y % p, z % p, p);
      if (x == -1)
        printf("Math Error\n");
      else
        printf("%lld\n", x);
    } else if (opt == 3) {
      x = ExLucas(z, y, p);
      if (x == -1)
        printf("Math Error\n");
      else
        printf("%lld\n", x);
    }
  }
  return 0;
}
