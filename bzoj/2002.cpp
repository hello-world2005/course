#include <algorithm>
#include <cstdio>

const int N = 2e5 + 10;

struct LinkCutTree {
  int ch[N][2], fa[N], rev[N], sze[N];
  int stk[N];

  void PushUp(int x) { sze[x] = sze[ch[x][0]] + sze[ch[x][1]] + 1; }

  void PushDown(int x) {
    if (rev[x]) {
      rev[ch[x][0]] ^= 1, rev[ch[x][1]] ^= 1, rev[x] ^= 1;
      std::swap(ch[x][0], ch[x][1]);
    }
  }

  bool IsRoot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }

  bool Child(int x) { return x == ch[fa[x]][1]; }

  void Rotate(int x) {
    int y = fa[x], z = fa[y], c = Child(x);
    if (!IsRoot(y)) {
      if (ch[z][0] == y)
        ch[z][0] = x;
      else
        ch[z][1] = x;
    }
    fa[x] = z, fa[y] = x, fa[ch[x][c ^ 1]] = y;
    ch[y][c] = ch[x][c ^ 1], ch[x][c ^ 1] = y;
    PushUp(y), PushUp(x);
  }

  void Splay(int x) {
    int top = 0;
    stk[++top] = x;
    for (int i = x; !IsRoot(i); i = fa[i])
      stk[++top] = fa[i];
    while (top)
      PushDown(stk[top--]);
    while (!IsRoot(x)) {
      int y = fa[x];
      if (!IsRoot(y)) {
        if (Child(x) ^ Child(y))
          Rotate(x);
        else
          Rotate(y);
      }
      Rotate(x);
    }
    PushUp(x);
  }

  void Access(int x) {
    for (int i = 0; x; i = x, x = fa[x]) {
      Splay(x), ch[x][1] = i, PushUp(x);
      if (i)
        fa[i] = x;
    }
  }

  void MakeRoot(int x) { Access(x), Splay(x), rev[x] ^= 1; }

  int FindRoot(int x) {
    Access(x), Splay(x);
    while (ch[x][0]) {
      PushDown(x);
      x = ch[x][0];
    }
    return x;
  }

  void Split(int x, int y) { MakeRoot(x), Access(y), Splay(y); }

  void Link(int x, int y) { MakeRoot(x), fa[x] = y; }

  void Cut(int x, int y) {
    Split(x, y);
    if (ch[y][0] == x)
      ch[y][0] = fa[x] = 0;
    PushUp(y);
  }

  int Query(int x, int y) {
    Split(x, y);
    return sze[y];
  }
} lct;

int a[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), lct.sze[i] = 1;
  lct.sze[n + 1] = 1;
  for (int i = 1; i <= n; ++i)
    lct.Link(i, std::min(i + a[i], n + 1));
  int m;
  scanf("%d", &m);
  while (m--) {
    int opt, p, k;
    scanf("%d%d", &opt, &p);
    ++p;
    if (opt == 1)
      printf("%d\n", lct.Query(p, n + 1) - 1);
    else
      scanf("%d", &k), lct.Cut(p, std::min(p + a[p], n + 1)),
          lct.Link(p, std::min(p + (a[p] = k), n + 1));
  }
  return 0;
}
