#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

const int N = 2e5 + 10;

std::vector<int> a[N];
std::priority_queue<int, std::vector<int>, std::greater<int> > q;

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 1, x, y; i <= n; ++i) {
      scanf("%d%d", &x, &y);
      a[x].push_back(y);
    }
    long long ans = 0;
    for (int i = n - 1; i >= 0; --i) {
      for (auto j : a[i])
        q.push(j);
      while (q.size() > n - i)
        ans += q.top(), q.pop();
    }
    printf("%lld\n", ans);
    for (int i = 0; i <= n; ++i)
      a[i].clear();
    while (!q.empty())
      q.pop();
  }
  return 0;
}
