#include <algorithm>
#include <cstdio>
#include <functional>

#define int long long

const int N = 2e5 + 10;

int n, k;
int a[N], d[N];

int t[N];

#define LowBit(x) (x & -x)

void Add(int a, int b) {
  for (; a <= n; a += LowBit(a))
    t[a] += b;
}

int Ask(int a) {
  int res = 0;
  for (; a; a -= LowBit(a))
    res += t[a];
  return res;
}

signed main() {
  scanf("%lld%lld", &n, &k);
  int maxn = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
    Add(a[i], 1);
    maxn = std::max(maxn, a[i]);
  }
  int lst = 0, ans = 0;
  // for (int i = maxn; i; --i) {
  //   int now = Ask(i);
  //   if (lst + now <= k) {
  //     lst += now;
  //   } else {
  //     lst += now;
  //     Add(i, k - lst);
  //     lst -= k;
  //     ++ans;
  //   }
  // }
  std::sort(a + 1, a + n + 1, std::greater<int>());
  for (int i = 1; i < n; ++i)
    d[i] = a[i] - a[i + 1];
  for (int i = 1; i < n; ++i) {
    if (i * d[i] + lst <= k) {
      lst += i * d[i];
    } else {
      int t = (k - lst) / i;
      d[i] -= t;
      lst = 0;
      ++ans;
      t = k / i;
      ans += d[i] / t;
      d[i] %= t;
      lst = d[i] * i;
    }
  }
  if (lst)
    ++ans;
  printf("%lld\n", ans);
  return 0;
}
