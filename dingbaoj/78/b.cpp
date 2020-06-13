#include <algorithm>
#include <cstdio>
#include <queue>

const int N = 3e5 + 10;

int n;
int a[N], b[N];
int cnt[N];

struct SegmentTree {
  struct Node {
    int v;
  } t[N];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void PushUp(int rt) { t[rt].v = std::min(t[lc].v, t[rc].v); }

  void Build(int rt, int l, int r) {
    if (l == r) {
      t[rt].v = a[l];
      return;
    }
    int mid = (l + r) >> 1;
    Build(ls);
    Build(rs);
    PushUp(rt);
  }

  void Update(int rt, int l, int r, int p) {
    if (l == r) {
      t[rt].v = 0x3f3f3f3f;
      return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
      Update(ls, p);
    else
      Update(rs, p);
    PushUp(rt);
  }

  int Query(int rt, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
      return t[rt].v;
    int mid = (l + r) >> 1, res = 0x3f3f3f3f;
    if (ql <= mid)
      res = std::min(res, Query(ls, ql, qr));
    if (qr > mid)
      res = std::min(res, Query(rs, ql, qr));
    return res;
  }
} st;

std::queue<int> v[N];
int p[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]), ++cnt[a[i]];
    for (int i = 1; i <= n; ++i)
      scanf("%d", &b[i]), --cnt[b[i]];
    bool flag = true;
    for (int i = 1; i <= n; ++i)
      if (cnt[i]) {
        flag = false;
        break;
      }
    if (!flag) {
      printf("NO\n");
      for (int i = 1; i <= n; ++i)
        cnt[i] = 0;
      continue;
    }
    // [x, x_1] 消去一个逆序对
    for (int i = 1; i <= n; ++i)
      v[a[i]].push(i);
    for (int i = 1; i <= n; ++i)
      p[i] = v[b[i]].front(), v[b[i]].pop();
    st.Build(1, 1, n);
    for (int i = 1; i <= n && flag; ++i) {
      // printf("%d %d\n", i, st.Query(1, 1, n, 1, p[i]));
      if (st.Query(1, 1, n, 1, p[i]) != b[i])
        flag = false;
      st.Update(1, 1, n, p[i]);
    }
    printf("%s\n", flag ? "YES" : "NO");
  }
  return 0;
}
