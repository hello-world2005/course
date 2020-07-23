#include <algorithm>
#include <cmath>
#include <cstdio>
#include <queue>

#define int long long

const int N = 1e6 + 10;

int a[N], b[N];

signed main() {
  int n;
  scanf("%lld", &n);
  std::priority_queue<int> q;
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
    q.push(b[i] = (a[i] -= i));
    if (q.size() && q.top() > a[i])
      q.pop(), q.push(a[i]);
    a[i] = q.top();
  }
  for (int i = n - 1; i >= 1; --i)
    a[i] = std::min(a[i], a[i + 1]);
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    ans += abs(a[i] - b[i]);
  printf("%lld\n", ans);
  return 0;
}
