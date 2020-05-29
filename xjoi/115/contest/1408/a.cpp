#include <cstdio>

typedef long long ll;

ll ExGcd(ll a, ll b, ll& x, ll& y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  int d = ExGcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

int main() {
  ll x, y, n, m, l;
  scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &l);
  ll a = n - m, b = l, c = x - y;
  if (a < 0)
    a = -a, c = -c;
  int d = ExGcd(a, b, x, y);
  if (c % d)
    puts("Impossible");
  else
    printf("%lld\n", (c / d * x % (b / d) + b / d) % (b / d));
  return 0;
}