#include <algorithm>
#include <cstdio>
#include <cstring>

#define int long long

namespace Subtask1 {
const int N = 310;

int k[N][N], dp[N][N];

void Main(int n, int m, int q, int l) {
  while (q--) {
    int opt, a, b, c, d, v;
    scanf("%lld%lld%lld%lld%lld", &opt, &a, &b, &c, &d);
    if (opt == 1) {
      scanf("%lld", &v);
      for (int i = a; i <= c; ++i)
        for (int j = b; j <= d; ++j)
          k[i][j] += v;
    } else {
      memset(dp, 0, sizeof(dp));
      dp[a][b] = 1;
      for (int i = a; i <= n; ++i)
        if (k[i][b] >= l)
          break;
        else
          dp[i][b] = 1;
      for (int i = b; i <= m; ++i)
        if (k[a][i] >= l)
          break;
        else
          dp[a][i] = 1;
      for (int i = a + 1; i <= c; ++i)
        for (int j = b + 1; j <= d; ++j)
          if (k[i][j] >= l)
            dp[i][j] = 0;
          else
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      printf("%s\n", dp[c][d] ? "yes" : "no");
    }
  }
}
}  // namespace Subtask1

namespace Subtask2 {
const int N = 100010;

struct SegmentTree {
  int maxn[N << 2], tag[N << 2];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void PushUp(int rt) { maxn[rt] = std::max(maxn[lc], maxn[rc]); }

  void PushDown(int rt) {
    if (tag[rt]) {
      maxn[lc] += tag[rt], maxn[rc] += tag[rt];
      tag[lc] += tag[rt], tag[rc] += tag[rt];
      tag[rt] = 0;
    }
  }

  void Update(int rt, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr)
      return maxn[rt] += v, tag[rt] += v, void();
    int mid = (l + r) >> 1;
    PushDown(rt);
    if (ql <= mid)
      Update(ls, ql, qr, v);
    if (qr > mid)
      Update(rs, ql, qr, v);
    PushUp(rt);
  }

  int Query(int rt, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
      return maxn[rt];
    int mid = (l + r) >> 1, res = 0;
    PushDown(rt);
    if (ql <= mid)
      res = std::max(res, Query(ls, ql, qr));
    if (qr > mid)
      res = std::max(res, Query(rs, ql, qr));
    return PushUp(rt), res;
  }
} st;

void Main(int n, int m, int q, int l) {
  while (q--) {
    int opt, a, b, c, d, v;
    scanf("%lld%lld%lld%lld%lld", &opt, &a, &b, &c, &d);
    if (opt == 1) {
      scanf("%lld", &v);
      st.Update(1, 1, m, b, d, v);
    } else {
      printf("%s\n", st.Query(1, 1, m, b, d) < l ? "yes" : "no");
    }
  }
}
}  // namespace Subtask2

signed main() {
  int n, m, q, l;
  scanf("%lld%lld%lld%lld", &n, &m, &l, &q);
  if (n == 1)
    Subtask2::Main(n, m, q, l);
  else
    Subtask1::Main(n, m, q, l);
  return 0;
}

/*
3 4 5 6
1 1 2 2 4 3
1 2 2 3 3 2
2 2 1 3 4
1 3 1 3 3 3
2 1 2 3 4
2 2 1 3 4
*/
