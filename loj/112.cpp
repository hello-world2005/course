#include <algorithm>
#include <cstdio>

const int N = 1e5 + 10;
const int K = 2e5 + 10;

int n, k;
struct Node {
  int a, b, c;

  Node() : a(0), b(0), c(0) {}
  Node(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}

  bool operator<(const Node& rhs) const {
    if (a != rhs.a)
      return a < rhs.a;
    if (b != rhs.b)
      return b < rhs.b;
    return c < rhs.c;
  }
} f[N];

struct SegmentTree {
  struct Node {
    int val;
    int l, r;
    int ch[2];

    Node() : val(0), l(0), r(0) { ch[0] = ch[1] = 0; }
  } t[N * 110];
  int cnt;

#define lc t[rt].ch[0]
#define rc t[rt].ch[1]

  int NewNode(int l, int r) {
    // printf("%d %d\n", l, r);
    t[++cnt].l = l;
    t[cnt].r = r;
    return cnt;
  }

  void PushDown(int rt) {
    if (t[rt].l == t[rt].r)
      return;
    int mid = (t[rt].l + t[rt].r) >> 1;
    if (!lc)
      lc = NewNode(t[rt].l, mid);
    if (!rc)
      rc = NewNode(mid + 1, t[rt].r);
  }

  void Update(int rt, int p) {
    // printf("%d %d %d %d\n", rt, p, t[rt].l, t[rt].r);
    if (t[rt].l > p || t[rt].r < p)
      return;
    PushDown(rt);
    ++t[rt].val;
    if (t[rt].l == t[rt].r)
      return;
    Update(lc, p);
    Update(rc, p);
  }

  int Query(int rt, int p) {
    if (t[rt].l > p || !t[rt].val)
      return 0;
    PushDown(rt);
    if (t[rt].r <= p)
      return t[rt].val;
    return Query(lc, p) + Query(rc, p);
  }

#undef lc
#undef rc
} s;

int ro[K];

struct FenwickTree {
  int t[K];

#define LowBit(x) (x & -x)

  void Add(int a, int b) {
    // printf("%d %d\n", a, b);
    for (; a <= K; a += LowBit(a))
      s.Update(ro[a], b);
  }

  int Ask(int a, int b) {
    int res = 0;
    // printf("%d %d: ", a, b);
    for (; a; a -= LowBit(a))
      res += s.Query(ro[a], b);
    // printf("%d\n", res);
    return res;
  }

#undef LowBit
} ft;

int ans[N], res[N];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i < K; ++i)
    ro[i] = s.NewNode(1, K);
  // for (int i = 1; i <= k + 10; ++i)
  //   printf("%d ", ro[i]);
  // printf("\n");
  for (int i = 1; i <= n; ++i)
    scanf("%d%d%d", &f[i].a, &f[i].b, &f[i].c), ++f[i].b;
  std::sort(f + 1, f + n + 1);
  for (int i = 1, j; i <= n; i = j) {
    ft.Add(f[i].b, f[i].c);
    for (j = i + 1; f[j - 1].a == f[j].a; ++j)
      ft.Add(f[j].b, f[j].c);
    ans[i] = ft.Ask(f[i].b, f[i].c);
    for (j = i + 1; f[j - 1].a == f[j].a; ++j)
      ans[j] = ft.Ask(f[j].b, f[j].c);
  }
  // for (int i = 1; i <= n; ++i)
  //   printf("%d ", ans[i]);
  // printf("\n");
  for (int i = 1; i <= n; ++i)
    ++res[ans[i]];
  for (int i = 1; i <= n; ++i)
    printf("%d\n", res[i]);
  return 0;
}
