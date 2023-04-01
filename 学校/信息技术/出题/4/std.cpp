#include <cmath>
#include <cstdio>
#include <algorithm>

const int N = 4e4 + 10;
const int M = 2e2 + 10;

int n;
int a[N], b[N];

int m;
int bl[M], br[M], blg[N];

int v[M][N];

int Solve(int l, int r) {
  int ans = 0;
  return ans;
}

int main() {
  int q;
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), b[i] = a[i];
  std::sort(b + 1, b + n + 1);
  int _n = std::unique(b + 1, b + n + 1) - b - 1;
  for (int i = 1; i <= n; ++i)
    a[i] = std::lower_bound(b + 1, b + _n + 1, a[i]) - b;
  m = ceil(n / M);
  for (int i = 1; i <= m - 1; ++i) {
    bl[i] = br[i - 1] + 1;
    br[i] = M * i;
    for (int j = bl[i]; j <= br[i]; ++j) {
      blg[j] = i;
    }
  }
  int last_ans = 0;
  while (q--) {
    int ll, rr, ans = 0, l, r;
    scanf("%d%d", &ll, &rr);
    l = ll ^ last_ans;
    r = rr ^ last_ans;
    if (l > r) l ^= r ^= l ^= r;
    printf("%d\n", last_ans = Solve(l, r));
  }
  return 0;
}
