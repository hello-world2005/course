#include <cstdio>
#include <cstdlib>

const int N = 1e5 + 10;
const int MOD = 1e9 + 7;
const int INV2 = 5e8 + 4;

struct FhqTreap {
  struct Node {
    int fir, d;            // 首项，公差
    int l, r;              // 左右区间端点
    int tag1, tag2, tag3;  // 加，减，左移
    int rnd, sze;
    int ch[2];

    Node() {}
    Node(int _fir, int _lst, int _d, int _l, int _r)
        : fir(_fir), d(_d), l(_l), r(_r), rnd(rand()), sze(1) {
      ch[0] = ch[1] = 0;
    }

    int Query() {
      // (fir + fir + (r - l) * d) * (r - l + 1) / 2
      return (1ll * fir * 2 % MOD + 1ll * (r - l) * d % MOD) % MOD *
             (r - l + 1) % MOD * INV2 % MOD;
    }
  } t[N];
  int cnt;

#define lc(rt) t[rt].ch[0]
#define rc(rt) t[rt].ch[1]

  int NewNode(int fir, int lst, int d, int l, int r) {
    // t[++cnt] = Node(fir, lst, d, l, r);
    return cnt;
  }

  void PushUp(int rt) { t[rt].sze = t[lc(rt)].sze + t[rc(rt)].sze + 1; }

  void Split(int rt, int v, int& rt1, int& rt2) {
    if (!rt) {
      rt1 = rt2 = 0;
      return;
    }
    if (t[rt].val <= v) {
      rt1 = rt;
      Split(rc(rt), v, rc(rt), rt2);
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
      rc(rt1) = Merge(rc(rt1), rt2);
      PushUp(rt1);
      return rt1;
    } else {
      lc(rt2) = Merge(rt1, lc(rt2));
      PushUp(rt2);
      return rt2;
    }
  }

  void Insert(int& rt, int v) {
    int rt1, rt2;
    Split(rt, v, rt1, rt2);
    rt = Merge(Merge(rt1, NewNode(v)), rt2);
  }

  void Delete(int& rt, int v) {
    int rt1, rt2, rt3;
    Split(rt, v, rt1, rt3);
    Split(rt1, v - 1, rt1, rt2);
    rt2 = Merge(lc(rt2), rc(rt2));
    rt = Merge(Merge(rt1, rt2), rt3);
  }

#undef lc
#undef rc
} fhq;
