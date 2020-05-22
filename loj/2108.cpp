#include <algorithm>
#include <cstdio>

const int N = 510;
const double EPS = 1e-5;

int n, m;
struct Node {
  double v[N];
  int val;

  bool operator<(const Node& rhs) const { return val < rhs.val; }
} a[N];
int b[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%lf", &a[i].v[j]);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i].val);
  std::sort(a + 1, a + n + 1);
  int ans1 = 0, ans2 = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      if (a[i].v[j] < EPS && a[i].v[j] > -EPS)
        continue;
      if (!b[j]) {
        b[j] = i;
        ++ans1;
        ans2 += a[i].val;
        break;
      }
      double t = a[i].v[j] / a[b[j]].v[j];
      for (int k = j; k <= m; ++k)
        a[i].v[k] -= a[b[j]].v[k] * t;
    }
  printf("%d %d\n", ans1, ans2);
  return 0;
}
