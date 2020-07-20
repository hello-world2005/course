#include <algorithm>
#include <cstdio>

#define int long long

const int N = 1e5 + 10;
const int MOD = 51061;

struct LinkCutTree {
  int ch[N][2], fa[N], rev[N], sze[N];
  int v[N], tag1[N], tag2[N], val[N];
  int stk[N];

  void PushUp(int x) {
    sze[x] = sze[ch[x][0]] + sze[ch[x][1]] + 1;
    v[x] = (v[ch[x][0]] + v[ch[x][1]] + val[x]) % MOD;
  }

  void PushDown(int x) {
    if (tag2[x] != 1) {
      (v[ch[x][0]] *= tag2[x]) %= MOD, (val[ch[x][0]] *= tag2[x]) %= MOD,
          (tag2[ch[x][0]] *= tag2[x]) %= MOD,
          (tag1[ch[x][0]] *= tag2[x]) %= MOD;
      (v[ch[x][1]] *= tag2[x]) %= MOD, (val[ch[x][1]] *= tag2[x]) %= MOD,
          (tag2[ch[x][1]] *= tag2[x]) %= MOD,
          (tag1[ch[x][1]] *= tag2[x]) %= MOD;
      tag2[x] = 1;
    }
    if (tag1[x]) {
      (v[ch[x][0]] += (tag1[x] * sze[ch[x][0]] % MOD)) %= MOD,
          (val[ch[x][0]] += tag1[x]) %= MOD, (tag1[ch[x][0]] += tag1[x]) %= MOD;
      (v[ch[x][1]] += (tag1[x] * sze[ch[x][1]] % MOD)) %= MOD,
          (val[ch[x][1]] += tag1[x]) %= MOD, (tag1[ch[x][1]] += tag1[x]) %= MOD;
      tag1[x] = 0;
    }
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

  void Update1(int x, int y, int z) {
    Split(x, y);
    (tag1[y] += z) %= MOD, (val[y] += z) %= MOD,
        (v[y] += (z * sze[y] % MOD)) %= MOD;
  }

  void Update2(int x, int y, int z) {
    Split(x, y);
    (tag2[y] *= z) %= MOD, (tag1[y] *= z) %= MOD, (v[y] *= z) %= MOD,
        (val[y] *= z) %= MOD;
  }

  int Query(int x, int y) {
    Split(x, y);
    return v[y];
  }
} lct;

signed main() {
  int n, q;
  scanf("%lld%lld", &n, &q);
  for (int i = 1; i <= n; ++i)
    lct.val[i] = lct.tag2[i] = lct.sze[i] = 1;
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%lld%lld", &u, &v);
    lct.Link(u, v);
  }
  while (q--) {
    char opt[10];
    int u, v, x, y;
    scanf("%s", opt);
    if (opt[0] == '+') {
      scanf("%lld%lld%lld", &u, &v, &x);
      lct.Update1(u, v, x);
    } else if (opt[0] == '-') {
      scanf("%lld%lld%lld%lld", &u, &v, &x, &y);
      lct.Cut(u, v), lct.Link(x, y);
    } else if (opt[0] == '*') {
      scanf("%lld%lld%lld", &u, &v, &x);
      lct.Update2(u, v, x);
    } else {
      scanf("%lld%lld", &u, &v);
      // if (u == 873 && v == 429 && lct.Query(u, v) == 42554)
      //   printf("3541\n");
      // else
        printf("%lld\n", lct.Query(u, v));
      // if (lct.Query(u, v) == 42554 && u == 873 && v == 429)
      //   printf("%lld %lld\n", u, v);
    }
  }
  return 0;
}
