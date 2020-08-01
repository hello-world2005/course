#include <algorithm>
#include <cstdio>

const int N = 2e5 + 10;

struct SegmentTree {
  int sum[N * 40], ch[N * 40][2];
  int cnt;

  int Build(int l, int r) {
    int rt = ++cnt;
    if (l == r)
      return rt;
    int mid = (l + r) >> 1;
    ch[rt][0] = Build(l, mid), ch[rt][1] = Build(mid + 1, r);
    return rt;
  }

  int Add(int pre, int l, int r, int pos) {
    int rt = ++cnt;
    sum[rt] = sum[pre] + 1;
    ch[rt][0] = ch[pre][0], ch[rt][1] = ch[pre][1];
    if (l == r)
      return rt;
    int mid = (l + r) >> 1;
    if (pos <= mid)
      ch[rt][0] = Add(ch[pre][0], l, mid, pos);
    else
      ch[rt][1] = Add(ch[pre][1], mid + 1, r, pos);
    return rt;
  }

  int Query(int rt1, int rt2, int l, int r, int k) {
    if (l == r)
      return l;
    int mid = (l + r) >> 1, x = sum[ch[rt2][0]] - sum[ch[rt1][0]];
    if (x >= k)
      return Query(ch[rt1][0], ch[rt2][0], l, mid, k);
    else
      return Query(ch[rt1][1], ch[rt2][1], mid + 1, r, k - x);
  }
} st;

int a[N], b[N];
int rt[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), b[i] = a[i];
  std::sort(b + 1, b + n + 1);
  int _n = std::unique(b + 1, b + n + 1) - b - 1;
  rt[0] = st.Build(1, _n);
  for (int i = 1; i <= n; ++i) {
    a[i] = std::lower_bound(b + 1, b + _n + 1, a[i]) - b;
    rt[i] = st.Add(rt[i - 1], 1, _n, a[i]);
  }
  while (m--) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    printf("%d\n", b[st.Query(rt[l - 1], rt[r], 1, _n, k)]);
  }
  return 0;
}
