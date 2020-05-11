#include <algorithm>
#include <cmath>
#include <cstdio>

const int N = 1e5 + 10;

struct Node {
  int val, idx;

  bool operator<(const Node& rhs) const { return val < rhs.val; }
} a[N];
int ans[N];

int main() {
  int n;
  scanf("%d", &n);
  int x = 0, y = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i].val);
    a[i].idx = i;
    if (a[i].val < 0)
      ++x;
    if (a[i].val == 0)
      ++y;
  }
  for (int i = 1; i <= n; ++i)
    if (a[i].val >= 0)
      a[i].val = -a[i].val - 1;
  if (n & 1) {
    int minn = 0x3f3f3f3f, p = 0;
    for (int i = 1; i <= n; ++i)
      if (minn > a[i].val)
        minn = a[i].val, p = i;
    a[p].val = -a[p].val - 1;
  }
  for (int i = 1; i <= n; ++i)
    ans[a[i].idx] = a[i].val;
  for (int i = 1; i <= n; ++i)
    printf("%d ", ans[i]);
  return 0;
}
