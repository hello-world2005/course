#include <algorithm>
#include <cstdio>

const int N = 1e5 + 10;

int n, m;
int a[N];
int l[N], r[N];
int ro[N];
int f[N];

struct SegmentTree {
#define lc (rt << 1)
#define rc (rt << 1 | 1)

  int t[200 * N], ch[N * 200][2];
  int cnt;
  void Update(int& rt, int l, int r, int pos, int val) {
    if (l > pos || r < pos)
      return;
    if (!rt)
      rt = ++cnt;
    t[rt] = std::max(t[rt], val);
    if (l == r)
      return;
    int mid = (l + r) >> 1;
    Update(ch[rt][0], l, mid, pos, val);
    Update(ch[rt][1], mid + 1, r, pos, val);
  }

  int Query(int rt, int l, int r, int al, int ar) {
    if (l > ar || r < al || !rt)
      return 0;
    if (l >= al && r <= ar)
      return t[rt];
    int mid = (l + r) >> 1;
    return std::max(Query(ch[rt][0], l, mid, al, ar),
                    Query(ch[rt][1], mid + 1, r, al, ar));
  }
} s;

int main() {
  scanf("%d%d", &n, &m);
  int maxn = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    l[i] = r[i] = a[i];
    maxn = std::max(maxn, a[i]);
  }
  for (int i = 1, x, y; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    l[x] = std::min(l[x], y);
    r[x] = std::max(r[x], y);
    maxn = std::max(maxn, y);
  }
  m = maxn;
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    maxn = 0;
    for (int j = a[i]; j; j -= (j & -j))
      maxn = std::max(maxn, s.Query(ro[j], 1, m, 1, l[i]));
    f[i] = maxn + 1;
    for (int j = r[i]; j <= m; j += (j & -j))
      s.Update(ro[j], 1, m, a[i], f[i]);
    ans = std::max(ans, f[i]);
  }
  printf("%d\n", ans);
  return 0;
}
