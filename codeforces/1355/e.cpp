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
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &h[i]), sum += h[i];
  // if (a + r <= m) {
  //   int x = sum % n;
  //   int y = n - x;
  //   int m1 = sum / n + (x != 0);
  //   int m2 = sum / n;
  //   int s1 = 0, s2 = 0, s;
  //   for (int i = 1; i <= n; ++i)
  //     s1 += Abs(h[i] - m1);
  //   for (int i = 1; i <= n; ++i)
  //     s2 += Abs(h[i] - m2);
  //   s = std::min(s1, s2);
  //   int ans1 = s * (a + r) / 2 + x * r;
  //   int ans2 = s * (a + r) / 2 + y * a;
  //   printf("%lld\n", std::min(ans1, ans2));
  // } else {}
  int l = 0, r = 1e15, ans;
  while (l < r) {
    if (r - l == 1)
      break;
    int mid = (l + r) >> 1;
    if (Check(mid) > Check(mid + 1))
      l = mid + 1;
    else
      r = mid;
  }
  int mid = (l + r) >> 1;
  ans = std::min(Check(l), Check(l + 1));
  printf("%lld\n", ans);
  return 0;
}
