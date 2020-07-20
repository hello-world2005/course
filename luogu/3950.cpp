#include <algorithm>
#include <cstdio>
#include <vector>

const int N = 3e5 + 10;

struct LinkCutTree {
  int ch[N][2], fa[N], rev[N];
  int stk[N];

  void PushDown(int x) {
    if (rev[x]) {
      rev[ch[x][0]] ^= 1, rev[ch[x][1]] ^= 1, rev[x] ^= 1;
      std::swap(ch[x][0], ch[x][1]);
    }
  }

  bool Child(int x) { return x == ch[fa[x]][1]; }

  bool IsRoot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }

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
  }

  void Access(int x) {
    for (int i = 0; x; i = x, x = fa[x])
      Splay(x), ch[x][1] = i;
  }

  void MakeRoot(int x) { Access(x), Splay(x), rev[x] ^= 1; }

  int FindRoot(int x) {
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
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    lct.Link(u, v);
  }
  // printf("qwq\n");
  std::vector<std::pair<int, int> > war;
  while (m--) {
    char opt[10];
    int x, y;
    scanf("%s", opt);
    if (opt[0] == 'Q') {
      scanf("%d%d", &x, &y);
      printf("%s\n", lct.FindRoot(x) == lct.FindRoot(y) ? "Yes" : "No");
    } else if (opt[0] == 'C') {
      scanf("%d%d", &x, &y);
      war.push_back(std::make_pair(x, y));
      lct.Cut(x, y);
    } else {
      scanf("%d", &x);
      // printf("%d\n", (int)war.size());
      lct.Link(war[x - 1].first, war[x - 1].second);
    }
  }
  return 0;
}
