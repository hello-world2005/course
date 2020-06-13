#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

const int N = 5e3 + 10;
const int M = 1e6 + 10;

struct Edge {
  int v, w, f, nxt;

  Edge() : v(0), w(0), f(0), nxt(0) {}
  Edge(int _v, int _w, int _f, int _nxt) : v(_v), w(_w), f(_f), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt = 1;
int totn;

void AddEdge(int u, int v, int w, int f) {
  e[++edge_cnt] = Edge(v, w, f, head[u]);
  head[u] = edge_cnt;
}

int dis[N];

bool in_que[N];
int flow[N], pre[N], idx[N];

bool Spfa(int s, int t) {
  std::queue<int> q;
  memset(flow, 0x3f, sizeof(flow));
  memset(dis, 0x3f, sizeof(dis));
  memset(in_que, false, sizeof(in_que));
  q.push(s);
  dis[s] = 0;
  in_que[s] = true;
  pre[t] = -1;
  while (!q.empty()) {
    int u = q.front();
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

int Ek(int s, int t) {
  int res1 = 0, res2 = 0;
  while (Spfa(s, t)) {
    res1 += flow[t];
    res2 += flow[t] * dis[t];
    int u = t;
    while (u != s) {
      e[idx[u]].w -= flow[t];
      e[(idx[u] & 1) ? idx[u] - 1 : idx[u] + 1].w += flow[t];
      u = pre[u];
    }
  }
  return res2;
}

int mp[N][N], deg[N];

struct T {
  int u, v, id;

  T() : u(0), v(0), id(0) {}
  T(int _u, int _v, int _id) : u(_u), v(_v), id(_id) {}
};

int uk[N];  // unknow direct

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      mp[i][j] = 2;
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    mp[u][v] = 1, mp[v][u] = 0;
  }
  // for (int i = 1; i <= n; ++i) {
  //   for (int j = 1; j <= n; ++j)
  //     printf("%d ", mp[i][j]);
  //   printf("\n");
  // }
  int cnt = 0;
  std::vector<T> v;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      if (i == j)
        continue;
      if (mp[i][j] == 1) {
        ++deg[j];
      } else if (mp[i][j] == 2 && i < j) {
        v.push_back(T(i, j, ++cnt));
        ++uk[i], ++uk[j];
      }
    }
  int s = n + cnt + 1, t = totn = s + 1, sum = 0;
  for (int i = 1; i <= n; ++i) {
    sum += deg[i] * (deg[i] - 1) / 2;
    for (int j = 1; j <= uk[i]; ++j) {
      AddEdge(i + cnt, t, 1,
              (deg[i] + j) * (deg[i] + j - 1) / 2 -
                  (deg[i] + j - 1) * (deg[i] + j - 2) / 2);
      AddEdge(t, i + cnt, 0,
              -((deg[i] + j) * (deg[i] + j - 1) / 2 -
                (deg[i] + j - 1) * (deg[i] + j - 2) / 2));
    }
  }
  for (auto i : v) {
    AddEdge(s, i.id, 1, 0);
    AddEdge(i.id, s, 0, 0);
    AddEdge(i.id, cnt + i.u, 1, 0);
    AddEdge(cnt + i.u, i.id, 0, 0);
    AddEdge(i.id, i.v + cnt, 1, 0);
    AddEdge(cnt + i.v, i.id, 0, 0);
  }
  // printf("%d\n", Ek(s, t));
  printf("%d\n", n * (n - 1) * (n - 2) / 6 - Ek(s, t) - sum);
  return 0;
}
