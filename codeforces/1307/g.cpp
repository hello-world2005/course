#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

const int N = 60;

struct Edge {
  int v, w, f, nxt;

  Edge() : v(0), w(0), f(0), nxt(0) {}
  Edge(int _v, int _w, int _f, int _nxt) : v(_v), w(_w), f(_f), nxt(_nxt) {}
} e[N * N << 1];
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

std::vector<std::pair<int, int> > f;

void Ek(int s, int t) {
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
    f.push_back(std::make_pair(res1, res2));
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v, w; i <= m; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    AddEdge(u, v, 1, w);
    AddEdge(v, u, 0, -w);
  }
  int s = 1, t = totn = n, q;
  scanf("%d", &q);
  Ek(s, t);
  // printf("3.0000000000\n4.0000000000\n4.5000000000\n5.0000000000\n5.5000000000\n");
  // return 0;
  while (q--) {
    int a;
    scanf("%d", &a);
    double res = 1e12;
    for (auto i : f)
      res = std::min(res, 1.0 * (i.second + a) / i.first);
    printf("%.7f\n", res);
  }
}
