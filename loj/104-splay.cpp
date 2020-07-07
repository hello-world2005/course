#include <cstdio>

const int N = 1e5 + 10;

struct SplayTree {
  struct Node {
    int ch[2], fa;
    int val, cnt;
    int sze;

    Node() : fa(0), val(0), cnt(0), sze(0) { ch[0] = ch[1] = 0; }
    Node(int _val) : fa(0), val(_val), cnt(1), sze(1) { ch[0] = ch[1] = 0; }
  } t[N];
  int rt, cnt;

#define lc(x) t[x].ch[0]
#define rc(x) t[x].ch[1]

  void PushUp(int x) { t[x].sze = t[lc(x)].sze + t[rc(x)].sze + t[x].cnt; }

  bool Child(int x) { return x == rc(t[x].fa); }

  void Clear(int x) { t[x] = Node(); }

  void Rotate(int x) {
    int y = t[x].fa, z = t[y].fa, ch = Child(x);
    t[y].ch[ch] = t[x].ch[ch ^ 1];
    t[t[x].ch[ch ^ 1]].fa = y;
    t[x].ch[ch ^ 1] = y;
    t[y].fa = x;
    t[x].fa = z;
    if (z)
      t[z].ch[y == rc(z)] = x;
    PushUp(x);
    PushUp(y);
  }

  void Splay(int x) {
    for (int f = t[x].fa; f = t[x].fa, f; Rotate(x))
      if (t[f].fa)
        Rotate(Child(x) == Child(f) ? f : x);
    rt = x;
  }

  void Insert(int k) {
    if (!rt) {
      t[++cnt] = Node(k);
      rt = cnt;
      PushUp(rt);
    } else {
      int x = rt, f = 0;
      while (true) {
        if (t[x].val == k) {
          ++t[x].cnt;
          PushUp(x);
          PushUp(f);
          Splay(x);
          break;
        }
        f = x;
        x = t[x].ch[t[x].val < k];
        if (!x) {
          t[++cnt] = Node(k);
          t[cnt].fa = f;
          t[f].ch[t[f].val < k] = cnt;
          PushUp(cnt);
          PushUp(f);
          Splay(cnt);
          break;
        }
      }
    }
  }

  int Rank(int k) {
    int res = 0, x = rt;
    while (true) {
      if (k < t[x].val) {
        x = lc(x);
      } else {
        res += t[lc(x)].sze;
        if (k == t[x].val) {
          Splay(x);
          return res + 1;
        }
        res += t[x].cnt;
        x = rc(x);
      }
    }
  }

  int Kth(int k) {
    int x = rt;
    while (true) {
      if (lc(x) && k <= t[lc(x)].sze) {
        x = lc(x);
      } else {
        k -= t[x].cnt + t[lc(x)].sze;
        if (k <= 0) {
          Splay(x);
          return t[x].val;
        }
        x = rc(x);
      }
    }
  }

  int Pre() {
    int x = lc(rt);
    while (rc(x))
      x = rc(x);
    Splay(x);
    return x;
  }

  int Nxt() {
    int x = rc(rt);
    while (lc(x))
      x = lc(x);
    Splay(x);
    return x;
  }

  void Delete(int k) {
    Rank(k);
    if (t[rt].cnt > 1) {
      --t[rt].cnt;
      PushUp(rt);
      return;
    }
    if (!lc(rt) && !rc(rt)) {
      Clear(rt);
      rt = 0;
      return;
    }
    if (!lc(rt)) {
      int x = rt;
      rt = rc(rt);
      t[rt].fa = 0;
      Clear(x);
      return;
    }
    if (!rc(rt)) {
      int x = rt;
      rt = lc(rt);
      t[rt].fa = 0;
      Clear(x);
      return;
    }
    int x = rt;
    int y = Pre();
    Splay(y);
    t[rc(x)].fa = y;
    rc(y) = rc(x);
    Clear(x);
    PushUp(rt);
  }
} splay;

int main() {
  int n;
  scanf("%d", &n);
  // splay.Insert(-0x7fffffff);
  // splay.Insert(0x7fffffff);
  while (n--) {
    int opt, x;
    scanf("%d%d", &opt, &x);
    if (opt == 1) {
      splay.Insert(x);
    } else if (opt == 2) {
      splay.Delete(x);
    } else if (opt == 3) {
      printf("%d\n", splay.Rank(x));
    } else if (opt == 4) {
      printf("%d\n", splay.Kth(x));
    } else if (opt == 5) {
      splay.Insert(x);
      printf("%d\n", splay.t[splay.Pre()].val);
      splay.Delete(x);
    } else {
      splay.Insert(x);
      printf("%d\n", splay.t[splay.Nxt()].val);
      splay.Delete(x);
    }
  }
  return 0;
}
