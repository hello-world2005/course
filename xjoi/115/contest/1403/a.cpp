#include <cstdio>

#define int long long

#define LowBit(x) (x & -x)

const int N = 1e6 + 10;

int n, q;
int t[N];

void Add(int a, int b) {
  for (; a <= n; a += LowBit(a))
    t[a] += b;
}

int Query(int a) {
  int res = 0;
  for (; a; a -= LowBit(a))
    res += t[a];
  return res;
}

signed main() {
  scanf("%lld%lld", &n, &q);
  for (int i = 1, x; i <= n; ++i)
    scanf("%lld", &x), Add(i, x);
  while (q--) {
    int opt, a, b;
    scanf("%lld%lld%lld", &opt, &a, &b);
    if (opt == 1)
      Add(a, b);
    else
      printf("%lld\n", Query(b) - Query(a - 1));
  }
  return 0;
}
