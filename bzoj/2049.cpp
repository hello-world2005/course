#include <algorithm>
#include <cstdio>

const int N = 1e4 + 10;

struct LinkCutTree {
  int ch[N][2], fa[N], rev[N];
  int sta[N];

  void PushDown(int x) {
    if (rev[x]) {
      rev[x] ^= 1, rev[ch[x][0]] ^= 1, rev[ch[x][1]] ^= 1;
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
  }

  void Splay(int x) {
    int top = 0;
    sta[++top] = x;
    for (int i = x; !IsRoot(i); i = fa[i])
      sta[++top] = fa[i];
    while (top)
      PushDown(sta[top--]);
    while (!IsRoot(x)) {
      int y = fa[x];
      if (!IsRoot(y)) {
        if ((!Child(x)) ^ (!(Child(y))))
          Rotate(x);
        else
          Rotate(y);
      }
      Rotate(x);
    }
  }

  void Access(int x) {
    for (int i = 0; x; i = x, x = fa[x])
      Splay(x), ch[x][1] = i;
  }

  void MakeRoot(int x) { Access(x), Splay(x), rev[x] ^= 1; }

  int Find(int x) {
    Access(x), Splay(x);
    while (ch[x][0])
      x = ch[x][0];
    return x;
  }

  void Split(int x, int y) { MakeRoot(x), Access(y), Splay(y); }

  void Link(int x, int y) { MakeRoot(x), fa[x] = y; }

  void Cut(int x, int y) {
    Split(x, y);
    if (ch[y][0] == x)
      ch[y][0] = fa[x] = 0;
  }
} lct;

int main() {
  // freopen("2049.in", "r", stdin);
  // freopen("2049.out", "w", stdout);
  int n, m;
  scanf("%d%d", &n, &m);
  while (m--) {
    char opt[10];
    int u, v;
    scanf("%s%d%d", opt, &u, &v);
    if (opt[0] == 'Q')
      printf("%s\n", lct.Find(u) == lct.Find(v) ? "Yes" : "No");
    else if (opt[0] == 'C')
      lct.Link(u, v);
    else
      lct.Cut(u, v);
  }
  return 0;
}
