#include <cmath>
#include <cstdio>
#include <queue>

const int N = 1010;
const int M = 5010;
const double EPS = 1e-4;

int n, m;
int a[N];
struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

double dis[N];
bool vis[N];
int in[N];

bool Spfa(int s, double val) {
  dis[s] = 0;
  vis[s] = false;
  std::queue<int> st;
  st.push(s);
  while (!st.empty()) {
    int u = st.front();
    st.pop();
    vis[u] = false;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (dis[u] + val * w - a[u] < dis[v]) {
        dis[v] = dis[u] + val * w - a[u];
        if (!vis[v]) {
          st.push(v);
          vis[v] = true;
          if (++in[v] > n + 10)
            return true;
        }
      }
    }
  }
  return false;
}

bool Check(double mid) {
  for (int i = 1; i <= n; ++i)
    dis[i] = 1e7, vis[i] = false, in[i] = 0;
  for (int i = 1; i <= n; ++i)
    if (!in[i] && Spfa(i, mid))
      return true;
  return false;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 1, u, v, w; i <= m; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    AddEdge(u, v, w);
  }
  double l = 0, r = 1e4;
  while (fabs(l - r) > EPS) {
    double mid = (l + r) / 2;
    if (Check(mid))
      l = mid;
    else
      r = mid - (1e-3);
  }
  printf("%.2f\n", l);
  return 0;
}
