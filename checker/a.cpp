#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1e5 + 10;

int n, q;
struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;
int a[N];

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

struct Trie {
  int s[N << 5][2], cnt, rt;

  int NewNode() {
    ++cnt;
    s[cnt][0] = s[cnt][1] = 0;
    return cnt;
  }

  void Clear() {
    cnt = 0;
    // rt = 1;
    memset(s, 0, sizeof(s));
  }

  void Insert(int k) {
    int u = rt;
    for (int i = 31; i >= 0; --i) {
      int now = (k >> i & 1);
      if (!s[u][now])
        s[u][now] = NewNode();
      u = s[u][now];
    }
  }

  int Query(int k) {
    int u = rt, res = 0;
    for (int i = 31; i >= 0; --i) {
      int now = (k >> i & 1);
      now ^= 1;
      if (s[u][now]) {
        res |= (1 << i);
        u = s[u][now];
      } else {
        u = s[u][now ^ 1];
      }
    }
    return res;
  }
} trie;

int sze[N], s[N];  // size son

void GetSze(int u) {
  sze[u] = 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    GetSze(v);
    sze[u] += sze[v];
    if (sze[s[u]] < sze[v])
      s[u] = v;
  }
}

int cnt[N], sum;
bool vis[N];
std::vector<std::pair<int, int> > que[N];

int ans[N];

void Insert(int u) {
  trie.Insert(a[u]);
  for (int i = head[u]; i; i = e[i].nxt)
    Insert(e[i].v);
}

void Dfs(int u, bool flag) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == s[u])
      continue;
    Dfs(v, false);
  }
  if (s[u])
    Dfs(s[u], true);
  trie.Insert(a[u]);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == s[u])
      continue;
    Insert(v);
  }
  for (auto q : que[u])
    ans[q.second] = trie.Query(q.first);
  if (!flag)
    trie.Clear();
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 2, f; i <= n; ++i) {
    scanf("%d", &f);
    AddEdge(f, i);
  }
  GetSze(1);
  for (int i = 1, u, x; i <= q; ++i) {
    scanf("%d%d", &u, &x);
    que[u].push_back(std::make_pair(x, i));
  }
  Dfs(1, false);
  for (int i = 1; i <= q; ++i)
    printf("%d\n", ans[i]);
  return 0;
}
