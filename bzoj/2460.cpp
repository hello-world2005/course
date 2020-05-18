#include <algorithm>
#include <cstdio>

#define int long long

const int N = 1010;

int n;
struct Node {
  int val, mag;

  bool operator<(const Node& rhs) const {
    return mag > rhs.mag;
  }
} a[N];
int d[N];

bool Insert(int k) {
  for (int i = 60; i >= 0; --i)
    if (k >> i & 1ll) {
      if (d[i]) {
        k ^= d[i];
      } else {
        d[i] = k;
        return true;
      }
    }
  return false;
}

signed main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lld%lld", &a[i].val, &a[i].mag);
  std::sort(a + 1, a + n + 1);
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (Insert(a[i].val))
      ans += a[i].mag;
  }
  printf("%lld\n", ans);
  return 0;
}
