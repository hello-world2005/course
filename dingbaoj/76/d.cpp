#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 10;

int n, q;
char s[N];
int f[N][20];

struct SegmentTree {
  struct Node {
    int val;
    int l, r;
  } t[N * 80];
  int rt[N];
  int cnt;

#define lc t[rt].l
#define rc t[rt].r
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void Init() {
    memset(rt, 0, sizeof(rt));
    memset(t, 0, sizeof(t));
    cnt = 0;
  }

  void PushUp(int rt) { t[rt].val = t[lc].val + t[rc].val; }

  void Update(int& rt, int l, int r, int p) {
    if (!rt)
      rt = ++cnt;
    if (l == r) {
      ++t[rt].val;
      return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
      Update(ls, p);
    else
      Update(rs, p);
    PushUp(rt);
  }

  int Query(int rt, int l, int r, int k) {
    if (t[rt].val < k)
      return -1;
    if (l == r)
      return l;
    int mid = (l + r) >> 1;
    if (t[lc].val >= k)
      return Query(ls, k);
    else
      return Query(rs, k - t[lc].val);
  }

  int Merge(int rt1, int rt2, int l, int r) {
    if (!rt1 || !rt2)
      return rt1 + rt2;
    int rt = ++cnt;
    if (l == r) {
      t[rt].val = t[rt1].val + t[rt2].val;
      return rt;
    }
    int mid = (l + r) >> 1;
    lc = Merge(t[rt1].l, t[rt2].l, l, mid);
    rc = Merge(t[rt1].r, t[rt2].r, mid + 1, r);
    PushUp(rt);
    return rt;
  }
} st;

struct SuffixAutomaton {
  struct Node {
    int ch[26];
    int len, fa;
    int sze;

    Node() {
      memset(ch, 0, sizeof(ch));
      len = 0;
    }
  } a[N << 1];
  int lst, tot;

  void Insert(int c, int id) {
    int p = lst;
    int np = lst = ++tot;
    st.Update(st.rt[np], 1, n, id);
    a[np].len = a[p].len + 1;
    for (; p && !a[p].ch[c]; p = a[p].fa)
      a[p].ch[c] = np;
    if (!p) {
      a[np].fa = 1;
    } else {
      int q = a[p].ch[c];
      if (a[q].len == a[p].len + 1) {
        a[np].fa = q;
      } else {
        int nq = ++tot;
        a[nq] = a[q];
        a[nq].len = a[p].len + 1;
        a[nq].sze = 0;
        a[q].fa = a[np].fa = nq;
        for (; a[p].ch[c] == q; p = a[p].fa)
          a[p].ch[c] = nq;
      }
    }
    a[np].sze = 1;
  }
  void Build(char* s) {
    memset(a, 0, sizeof(a));
    lst = tot = 1;
    int n = strlen(s + 1);
    for (int i = 1; i <= n; ++i)
      Insert(s[i] - 'a', i);
  }

  int c[N << 1], d[N << 1];

  void Sort() {
    memset(f, 0, sizeof(f));
    memset(c, 0, sizeof(c));
    memset(d, 0, sizeof(d));
    for (int i = 1; i <= tot; ++i)
      ++c[a[i].len];
    for (int i = 1; i <= tot; ++i)
      c[i] += c[i - 1];
    for (int i = tot; i; --i)
      d[c[a[i].len]--] = i;
    for (int i = tot; i; --i) {
      f[d[i]][0] = a[d[i]].fa;
      st.rt[a[d[i]].fa] = st.Merge(st.rt[a[d[i]].fa], st.rt[d[i]], 1, n);
      // printf("%d %d\n", a[d[i]].fa, d[i]);
    }
    for (int j = 1; j < 20; ++j)
      for (int i = 1; i <= tot; ++i)
        f[i][j] = f[f[i][j - 1]][j - 1];
  }
} sam;

struct Question {
  int l, r, k, id;

  Question() : l(0), r(0), k(0), id(0) {}
  Question(int _l, int _r, int _k, int _id) : l(_l), r(_r), k(_k), id(_id) {}

  bool operator<(const Question& rhs) const { return r < rhs.r; }
} que[N];

int Find(int u, int len) {
  for (int i = 19; i >= 0; --i)
    if (sam.a[f[u][i]].len >= len)
      u = f[u][i];
  return u;
}

int ans[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &q);
    scanf("%s", s + 1);
    st.Init();
    sam.Build(s);
    sam.Sort();
    for (int i = 1; i <= q; ++i)
      scanf("%d%d%d", &que[i].l, &que[i].r, &que[i].k), que[i].id = i;
    std::sort(que + 1, que + q + 1);
    int now = 1, t = 1;
    for (int i = 1; i <= n; ++i) {
      now = sam.a[now].ch[s[i] - 'a'];
      while (t <= q && que[t].r == i) {
        int len = que[t].r - que[t].l + 1;
        int pos = Find(now, len);
        // printf("%d\n", st.rt[pos]);
        int ed = st.Query(st.rt[pos], 1, n, que[t].k);
        // printf("> %d %d\n", t, ed);
        if (~ed) {
          ans[que[t].id] = ed - len + 1;
        } else {
          ans[que[t].id] = -1;
        }
        ++t;
      }
    }
    for (int i = 1; i <= q; ++i)
      printf("%d\n", ans[i]);
  }
  return 0;
}
