#include <algorithm>
#include <cstdio>

const int N = 1e5 + 10;

int f[N];

struct LinkCutTree {
  int ch[N][2], fa[N], rev[N];
  int sta[N];
  int sze[N], cnt[N];

  void Init(int n) {
    for (int i = 1; i <= n; ++i)
      sze[i] = 1;
  }

  void PushUp(int x) { sze[x] = sze[ch[x][0]] + sze[ch[x][1]] + cnt[x]; }

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
    PushUp(y);
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
    PushUp(x);
  }

  void Access(int x) {
    for (int i = 0; x; i = x, x = fa[x])
      Splay(x), cnt[x] += sze[ch[x][1]], cnt[x] -= sze[ch[x][1] = i];
  }

  void MakeRoot(int x) { Access(x), Splay(x), rev[x] ^= 1; }

  int Find(int x) {
    Access(x), Splay(x);
    while (ch[x][0])
      x = ch[x][0];
    return x;
  }

  void Split(int x, int y) { MakeRoot(x), Access(y), Splay(y); }

  void Link(int x, int y) { Splay(x), fa[x] = y, cnt[y] += sze[x], sze[y] += sze[x]; }

  void Cut(int x, int y) {
    Split(x, y);
    if (ch[y][0] == x)
      ch[y][0] = fa[x] = 0;
    PushUp(x);
  }
} lct[2];

struct Edge {
  int v, nxt;
  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

void Dfs(int u, int fa) {
  f[u] = fa;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs(v, u);
    lct[0].Link(v, u);
  }
}

int col[N];

int main() {
  int n, m;
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
    AddEdge(v, u);
  }
  lct[0].Init(n + 1), lct[1].Init(n + 1);
  Dfs(1, 0);
  f[1] = n + 1;
  lct[0].Link(1, n + 1);
  scanf("%d", &m);
  while (m--) {
    int opt, u;
    scanf("%d%d", &opt, &u);
    if (opt == 0)
      printf("%d\n", lct[col[u]].sze[lct[col[u]].ch[lct[col[u]].Find(u)][1]]);
    else
      lct[col[u]].Cut(u, f[u]), lct[col[u] ^= 1].Link(u, f[u]);
  }
  return 0;
}

// 大概记一下吧：
// lct 维护子树大小
// 和树剖一样
// 不想写了
