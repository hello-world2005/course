#ifdef Solution1

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e2 + 10;
const int M = 1e4 + 10;

int n, k;
struct Edge {
  int v, w, nxt, f;

  Edge() : v(0), w(0), nxt(0), f(0) {}
  Edge(int _v, int _w, int _nxt, int _f) : v(_v), w(_w), nxt(_nxt), f(_f) {}
} e[M << 1];
int head[N], edge_cnt = 1;

void AddEdge(int u, int v, int w, int f) {
  e[++edge_cnt] = Edge(v, w, head[u], f);
  // printf("%d %d %d %d\n", edge_cnt, u, v, w);
  head[u] = edge_cnt;
}

int dis[N];

bool in_que[N];
int flow[N], pre[N], idx[N];

bool Spfa(int s, int t) {
  std::queue<int> q;
  memset(flow, 0x3f, sizeof(flow));
  memset(dis, 0x3f, sizeof(dis));
  // memset(pre, 0, sizeof(pre));
  memset(in_que, false, sizeof(in_que));
  q.push(s);
  dis[s] = 0;
  in_que[s] = true;
  pre[t] = -1;
  while (!q.empty()) {
    int u = q.front();
    // printf("%d\n", u);
    q.pop();
    in_que[u] = false;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].f;
      if (dis[v] > dis[u] + w && e[i].w) {
        dis[v] = dis[u] + w;
        flow[v] = std::min(flow[u], e[i].w);
        pre[v] = u;
        idx[v] = i;
        if (!in_que[v])
          q.push(v), in_que[v] = true;
      }
    }
  }
  return ~pre[t];
}

int Dinic(int s, int t) {
  int res1 = 0, res2 = 0;
  while (Spfa(s, t)) {
    res1 += flow[t];
    res2 += flow[t] * dis[t];
    // for (int i = 1; i <= n; ++i)
    //   printf("%d ", pre[i]);
    // printf("\n");
    int u = t;
    while (u != s) {
      // printf("%d\n", u);
      e[idx[u]].w -= flow[t];
      e[idx[u] ^ 1].w += flow[t];
      u = pre[u];
    }
    // printf("%d\n", u);
  }
  // printf("%lld %lld\n", res1, res2);
  return res1;
}

int a[N], b[N];
int ans[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    memset(head, 0, sizeof(head));
    edge_cnt = 1;
    memset(e, 0, sizeof(e));
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
      scanf("%d%d", &a[i], &b[i]);
    int s = 0, t = n * 2 + 1;
    for (int i = 1; i <= n; ++i) {
      AddEdge(s, i, 1, 0), AddEdge(i, s, 0, 0);
      AddEdge(i + n, t, 1, 0), AddEdge(t, i + n, 0, 0);
    }
    for (int i = 1; i <= n; ++i)
      for (int j = 1, w; j <= n; ++j) {
        if (j < k)
          w = a[i] + (j - 1) * b[i];
        else if (j < n)
          w = (k - 1) * b[i];
        else
          w = a[i] + (k - 1) * b[i];
        // printf("%d\n", w);
        AddEdge(i, n + j, 1, -w);
        AddEdge(n + j, i, 0, w);
      }
    printf("%d\n", 2 * n - k);
    // for (int i = 2; i <= edge_cnt; ++i)
    //   printf("%d %d %d\n", e[i].v, e[i].w, e[i].f);
    Dinic(s, t);
    for (int u = 1; u <= n; ++u)
      for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v, w = e[i].w;
        if (v <= n)
          continue;
        // printf("%d %d %d\n", u, v, w);
        if (!w)
          ans[v - n] = u;
      }
    for (int i = 1; i <= n; ++i) {
      printf("%d ", ans[i]);
      if (i >= k && i < n)
        printf("%d ", -ans[i]);
    }
    printf("\n");
  }
  return 0;
}

#else

// DP

#include <algorithm>
#include <cstdio>

int main() {}

#endif
