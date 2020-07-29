#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

const int N = 1e6 + 10;

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

struct AcAutoMaton {
  int ch[N][26], ed[N], at[N], tot = 1;
  int fl[N];

  void Insert(char *s, int id) {
    int n = strlen(s + 1), now = 0;
    for (int i = 1; i <= n; ++i) {
      int u = s[i] - 'a';
      if (!ch[now][u])
        ch[now][u] = ++tot;
      now = ch[now][u];
    }
    ed[now] = id;
    at[id] = now;
  }

  void Build() {
    std::queue<int> q;
    for (int i = 0; i < 26; ++i)
      if (ch[0][i])
        q.push(ch[0][i]), AddEdge(0, ch[0][i]);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < 26; ++i)
        if (ch[u][i]) {
          fl[ch[u][i]] = ch[fl[u]][i];
          ed[ch[u][i]] |= ed[ch[fl[u]][i]];
          AddEdge(fl[ch[u][i]], ch[u][i]);
          q.push(ch[u][i]);
        } else {
          ch[u][i] = ch[fl[u]][i];
        }
    }
  }
} ac;

int in[N], ou[N], idx;

void Dfs(int u, int fa) {
  in[u] = ++idx;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs(v, u);
  }
  ou[u] = idx;
}

int sum[N << 2], tag[N << 2];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

void PushUp(int rt) {
  sum[rt] = sum[lc] + sum[rc];
}

void PushDown(int rt, int l, int r) {
  if (tag[rt]) {
    int mid = (l + r) >> 1;
    sum[lc] += (mid - l + 1) * tag[rt], sum[rc] += (r - mid) * tag[rt];
    tag[lc] += tag[rt], tag[rc] += tag[rt], tag[rt] = 0;
  }
}

void Update(int rt, int l, int r, int ql, int qr, int k) {
  if (ql <= l && r <= qr) {
    sum[rt] += (r - l + 1) * k, tag[rt] += k;
    return;
  }
  PushDown(rt, l, r);
  int mid = (l + r) >> 1;
  if (ql <= mid)
    Update(ls, ql, qr, k);
  if (qr > mid)
    Update(rs, ql, qr, k);
  PushUp(rt);
}

int Query(int rt, int l, int r, int ql, int qr) {
  // printf("%d %d %d %d %d\n", rt, l, r, ql, qr);
  if (ql <= l && r <= qr)
    return sum[rt];
  PushDown(rt, l, r);
  int mid = (l + r) >> 1, res = 0;
  if (ql <= mid)
    res += Query(ls, ql, qr);
  if (qr > mid)
    res += Query(rs, ql, qr);
  return res;
}

char s[N];

bool vis[N];

int main() {
  int n, k;
  std::cin >> n >> k;
  for (int i = 1; i <= k; ++i)
    std::cin >> (s + 1), ac.Insert(s, i);
  ac.Build();
  Dfs(0, 0);
  for (int i = 1; i <= k; ++i)
    vis[i] = true, Update(1, 1, ac.tot, in[ac.at[i]], ou[ac.at[i]], 1);
  while (n--) {
    char opt;
    std::cin >> opt;
  // printf("!\n");
    if (opt == '+') {
      int x;
      std::cin >> x;
      if (vis[x])
        continue;
      vis[x] = true;
      Update(1, 1, ac.tot, in[ac.at[x]], ou[ac.at[x]], 1);
    } else if (opt == '-') {
      int x;
      std::cin >> x;
      if (!vis[x])
        continue;
      vis[x] = false;
      Update(1, 1, ac.tot, in[ac.at[x]], ou[ac.at[x]], -1);
    } else {
      std::cin >> (s + 1);
      int n = strlen(s + 1), now = 0, ans = 0;
      for (int i = 1; i <= n; ++i) {
        int u = s[i] - 'a';
        now = ac.ch[now][u];
        ans += Query(1, 1, ac.tot, in[now], in[now]);
        // std::cout << ">>>>" << Query(1, 1, ac.tot, in[now], in[now]) << std::endl;
      }
      std::cout << ans << std::endl;
    }
  }
  return 0;
}
