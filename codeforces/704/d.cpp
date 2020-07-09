#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

#define int long long

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 0x3f3f3f3f;

struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt = 1, cur[N];
int d[N];

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

void AddEdge(int u, int v, int l, int r) {
  AddEdge(u, v, r - l);
  AddEdge(v, u, 0);
  d[u] -= l;
  d[v] += l;
}

bool Bfs(int s, int t) {
  memset(d, 0, sizeof(d));
  memcpy(cur, head, sizeof(head));
  std::queue<int> q;
  q.push(s);
  d[s] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (d[v] || !w)
        continue;
      q.push(v);
      d[v] = d[u] + 1;
    }
  }
  return d[t] > 0;
}

int Dfs(int u, int flow, int t) {
  // printf("%lld %lld\n", u, flow);
  if (u == t)
    return flow;
  int res = flow;
  for (int i = cur[u]; i && res; i = e[i].nxt) {
    // cur[u] = i;
    int v = e[i].v, w = e[i].w;
    if (d[v] != d[u] + 1 || !w)
      continue;
    int now = Dfs(v, std::min(res, w), t);
    if (!now) {
      d[v] = 0;
    } else {
      e[i].w -= now;
      e[i ^ 1].w += now;
      res -= now;
    }
  }
  return flow - res;
}

int Dinic(int s, int t) {
  int res = 0;
  while (Bfs(s, t))
    res += Dfs(s, INF, t);
  return res;
}

std::map<int, int> xx, yy;
int cnt[N], minn[N], row[N];

signed main() {
  int n, m, r, b, flag = false, idx = 0;
  scanf("%lld%lld%lld%lld", &n, &m, &r, &b);
  if (r > b)
    std::swap(r, b), flag = true;
  for (int i = 1, x, y; i <= n; ++i) {
    scanf("%lld%lld", &x, &y);
    if (!xx[x])
      xx[x] = ++idx, minn[idx] = INF, row[idx] = true;
    ++cnt[xx[x]];
    if (!yy[y])
      yy[y] = ++idx, minn[idx] = INF;
    ++cnt[yy[y]];
    AddEdge(xx[x], yy[y], 1);
    AddEdge(yy[y], xx[x], 0);
  }
  int s = idx + 1, t = s + 1, S = t + 1, T = S + 1;
  // printf("%lld %lld %lld %lld\n", s, t, S, T);
  for (int i = 1, t, l, d; i <= m; ++i) {
    scanf("%lld%lld%lld", &t, &l, &d);
    if (t == 1) {
      l = xx[l];
      if (l)
        minn[l] = std::min(minn[l], d);
    } else {
      l = yy[l];
      if (l)
        minn[l] = std::min(minn[l], d);
    }
    // printf("%lld\n", minn[l]);
  }
  for (int i = 1; i <= idx; ++i) {
    int x = std::min(cnt[i], minn[i]);
    int l = (cnt[i] - x + 1) >> 1, r = (cnt[i] + x) >> 1;
    // printf("%lld %lld %lld %lld %lld\n", i, l, r, cnt[i], minn[i]);
    if (l > r) {
      printf("-1\n");
      return 0;
    }
    if (row[i])
      AddEdge(s, i, l, r);
    else
      AddEdge(i, t, l, r);
  }
  int sum = 0;
  for (int i = 1; i <= t; ++i) {
    if (d[i] > 0)
      AddEdge(S, i, d[i]), AddEdge(i, S, 0), sum += d[i];
    else if (d[i] < 0)
      AddEdge(i, T, -d[i]), AddEdge(T, i, 0);
  }
  // for (int u = 1; u <= T; ++u)
  //   for (int i = head[u]; i; i = e[i].nxt)
  //     printf("%lld %lld %lld\n", u, e[i].v, e[i].w);
  AddEdge(t, s, 0, INF);
  int flow = Dinic(S, T);
  if (flow != sum) {
    printf("-1\n");
  } else {
    flow = Dinic(s, t);
    printf("%lld\n", 1ll * flow * r + 1ll * (n - flow) * b);
    for (int i = 1; i <= n; ++i) {
      if (e[i * 2 + 1].w ^ flag)
        printf("r");
      else
        printf("b");
    }
  }
  return 0;
}
