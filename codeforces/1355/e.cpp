#include <algorithm>
#include <cstdio>

#define int long long

const int N = 1e5 + 10;

int n, a, r, m;
int h[N], sum;

int Abs(int x) {
  if (x < 0)
    return -x;
  return x;
}

int Check(int mid) {
  int x = 0, y = 0;
  for (int i = 1; i <= n; ++i)
    if (h[i] < mid)
      x += mid - h[i];
    else
      y += h[i] - mid;
  int k = std::min(a + r, m), m = std::min(x, y);
  return k * m + a * (x - m) + r * (y - m);
}

signed main() {
  scanf("%lld%lld%lld%lld", &n, &a, &r, &m);
  int maxn = 0;
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &h[i]), maxn = std::max(maxn, h[i]);
  int l = 0, r = maxn, ans;
  while (l < r) {
    if (l + 1 == r)
      break;
    int mid = (l + r) >> 1;
    if (Check(mid) > Check(mid + 1))
      l = mid + 1;
    else
      r = mid;
  }
  ans = std::min(Check(l), Check(l + 1));
  printf("%lld\n", ans);
  return 0;
}
