#include <cmath>
#include <cstdio>
#include <map>

typedef long long ll;

ll Gcd(ll a, ll b) {
  if (!b)
    return a;
  return Gcd(b, a % b);
}

ll FastPow(ll a, ll b, ll p) {
  ll res = 1;
  for (; b; a = a * a % p, b >>= 1)
    if (b & 1)
      res = res * a % p;
  return res;
}

ll Exgcd(ll a, ll b, ll& x, ll& y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  ll d = Exgcd(b, a % b, y, x);
  y -= x * (a / b);
  return d;
}

ll Bsgs(ll a, ll b, ll p, ll now) {
  std::map<ll, int> has;
  ll sze = ceil(sqrt(p)), t, x, y;
  Exgcd(now, p, x, y);
  b = (b * x % p + p) % p;
  t = FastPow(a, sze, p);
  Exgcd(t, p, x, y);
  t = (x % p + p) % p;
  for (ll i = 1, j = 0; j <= sze; ++j, i = i * a % p)
    if (!has.count(i))
      has[i] = j;
  for (ll i = b, j = 0; j <= sze; ++j, i = i * t % p)
    if (has[i])
      return j * sze + has[i];
  return -1;
}

ll ExBsgs(int a, int b, int p) {
  ll now = 1;
  ll k = 0, t = 1;
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

int main() {
  int a, b, p;
  while (scanf("%d%d%d", &a, &p, &b) == 3 && a && b && p) {
    a %= p, b %= p;
    int res = ExBsgs(a, b, p);
    if (res == -1)
      puts("No Solution");
    else
      printf("%d\n", res);
  }
  return 0;
}
