#include <algorithm>
#include <cstdio>
#include <ctime>
#include <random>
#include <unordered_set>
#include <vector>

const int N = 3e5 + 10;

std::mt19937 rnd(time(NULL));

struct LinkCutTree {
  int ch[N][2], fa[N], rev[N], sze[N], v[N];
  int stk[N];

  void PushUp(int x) { sze[x] = sze[ch[x][0]] ^ sze[ch[x][1]] ^ v[x]; }

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
    for (int i = 0; x; i = x, x = fa[x])
      Splay(x), ch[x][1] = i, PushUp(x);
  }

  int FindRoot(int x) {
    Access(x), Splay(x);
    while (ch[x][0]) {
      PushDown(x);
      x = ch[x][0];
    }
    return x;
  }

  void MakeRoot(int x) { Access(x), Splay(x), rev[x] ^= 1; }

  void Split(int x, int y) { MakeRoot(x), Access(y), Splay(y); }

  void Link(int x, int y) {
    if (FindRoot(x) != FindRoot(y))
      MakeRoot(x), fa[x] = y, PushUp(y);
  }

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

  void Update(int x, int y) {
    Access(x), Splay(x);
    v[x] = y;
    PushUp(x);
  }
} lct;

struct Edge {
  int u, v, w;

  Edge() : u(0), v(0), w(0) {}
  Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
} e[N];
int edge_cnt;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &lct.v[i]);
  int ans = 0;
  while (m--) {
    int opt, x, y;
    scanf("%d%d%d", &opt, &x, &y);
    if (opt == 0)
      printf("%d\n", lct.Query(x, y));
    else if (opt == 1)
      lct.Link(x, y);
    else if (opt == 2)
      lct.Cut(x, y);
    else
      lct.Update(x, y);
  }
  return 0;
}
