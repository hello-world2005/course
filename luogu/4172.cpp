#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>

const int N = 2e5 + 10;

struct Operation {
  int k, u, v, idx;

  Operation() : k(0), u(0), v(0), idx(0) {}
  Operation(int _k, int _u, int _v) : k(_k), u(_u), v(_v) {}
};
struct Edge {
  int u, v, w;

  Edge() : u(0), v(0), w(0) {}
  Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

  bool operator<(const Edge& rhs) const { return w < rhs.w; }
} e[N];
std::vector<Operation> op;
std::map<std::pair<int, int>, int> eton;  // edge to node
bool vis[N];
int ans[N];

struct LinkCutTree {
  int ch[N][2], fa[N], rev[N], v[N], val[N];
  int stk[N];

  // void PushUp(int x) { v[x] = std::min({v[ch[x][0]], v[ch[x][1]], val[x]}); }

  void PushUp(int x) {
    v[x] = val[x];
    if (e[v[ch[x][0]]].w > e[v[x]].w)
      v[x] = v[ch[x][0]];
    if (e[v[ch[x][1]]].w > e[v[x]].w)
      v[x] = v[ch[x][1]];
  }

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

  void Init(int x, int y) {
    ch[x][0] = ch[x][1] = fa[x] = rev[x] = 0;
    v[x] = val[x] = y;
  }
} lct;

int main() {
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1, u, v, w; i <= m; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    if (u > v)
      std::swap(u, v);
    e[i] = Edge(u, v, w);
  }
  std::sort(e + 1, e + m + 1);
  for (int i = 1; i <= m; ++i)
    eton[std::make_pair(e[i].u, e[i].v)] = i;
  op.resize(q + 1);
  for (int i = 1; i <= q; ++i) {
    scanf("%d%d%d", &op[i].k, &op[i].u, &op[i].v);
    if (op[i].u > op[i].v)
      std::swap(op[i].u, op[i].v);
    if (op[i].k == 2) {
      int id = eton[std::make_pair(op[i].u, op[i].v)];
      op[i].idx = id;
      vis[id] = true;
    }
  }
  int tot = n + m, sum = 0;
  for (int i = 1; i <= tot; ++i)
    lct.Init(i, i <= n ? 0 : (i - n));
  for (int i = 1; i <= m; ++i)
    if (!vis[i]) {
      if (sum == n - 1)
        break;
      int u = e[i].u, v = e[i].v;
      if (lct.FindRoot(u) == lct.FindRoot(v))
        continue;
      lct.Link(u, i + n), lct.Link(v, i + n), ++sum;
    }
  for (int i = q; i >= 1; --i) {
    int u = op[i].u, v = op[i].v;
    if (op[i].k == 1) {
      lct.Split(u, v);
      // for (int j = 1; j <= tot; ++j)
      //   printf("%d ", lct.v[j]);
      // printf("\n=====%d=====\n", lct.v[v]);
      ans[i] = e[lct.v[v]].w;
    } else {
      lct.Split(u, v);
      int d = op[i].idx, t = lct.v[v];
      if (e[d].w < e[lct.v[v]].w) {
        lct.Cut(e[t].u, t + n), lct.Cut(e[t].v, t + n);
        lct.Link(u, d + n), lct.Link(v, d + n);
      }
    }
  }
  for (int i = 1; i <= q; ++i)
    if (op[i].k == 1)
      printf("%d\n", ans[i]);
  return 0;
}
