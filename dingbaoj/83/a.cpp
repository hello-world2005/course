#include <algorithm>
#include <cstdio>
#include <cstdlib>

const int N = 1e5 + 10;

struct FhqTreap {
  struct Node {
    int val, rnd, tag;
    int sze;
    int ch[2];

    Node() : val(0), rnd(rand()), tag(0), sze(0) { ch[0] = ch[1] = 0; }
    Node(int _val) : val(_val), rnd(rand()), tag(0), sze(1) {
      ch[0] = ch[1] = 0;
    }
  } t[N];
  int cnt;

#define lc(rt) t[rt].ch[0]
#define rc(rt) t[rt].ch[1]

  int NewNode(int val) {
    t[++cnt] = Node(val);
    return cnt;
  }

  void PushUp(int rt) { t[rt].sze = t[lc(rt)].sze + t[rc(rt)].sze + 1; }

  void PushDown(int rt) {
    if (t[rt].tag)
      t[t[rt].ch[0]].tag ^= 1, t[t[rt].ch[1]].tag ^= 1,
          t[rt].tag = 0, std::swap(t[rt].ch[0], t[rt].ch[1]);
  }

  void Split(int rt, int v, int& rt1, int& rt2) {
    if (!rt) {
      rt1 = rt2 = 0;
      return;
    }
    PushDown(rt);
    if (t[lc(rt)].sze + 1 <= v) {
      rt1 = rt;
      Split(rc(rt), v - t[lc(rt)].sze - 1, rc(rt), rt2);
    } else {
      rt2 = rt;
      Split(lc(rt), v, rt1, lc(rt));
    }
    PushUp(rt);
  }

  int Merge(int rt1, int rt2) {
    if (!rt1 || !rt2)
      return rt1 + rt2;
    if (t[rt1].rnd < t[rt2].rnd) {
      PushDown(rt1);
      rc(rt1) = Merge(rc(rt1), rt2);
      PushUp(rt1);
      return rt1;
    } else {
      PushDown(rt2);
      lc(rt2) = Merge(rt1, lc(rt2));
      PushUp(rt2);
      return rt2;
    }
  }

  void Print(int rt) {
    PushDown(rt);
    if (lc(rt))
      Print(lc(rt));
    printf("%d ", t[rt].val);
    if (rc(rt))
      Print(rc(rt));
  }
} fhq;

int main() {
  int n, m, rt = 0;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    fhq.NewNode(i);
    rt = fhq.Merge(rt, i);
  }
  for (int i = 1, l, r, x, y, z; i <= m; ++i) {
    scanf("%d%d", &l, &r);
    fhq.Split(rt, r, x, y);
    fhq.Split(x, l - 1, x, z);
    fhq.t[z].tag ^= 1;
    rt = fhq.Merge(fhq.Merge(x, z), y);
  }
  fhq.Print(rt);
  return 0;
}
