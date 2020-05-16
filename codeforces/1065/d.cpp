#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>

#define int long long

const int N = 13;
const int DX_H[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int DY_H[] = {-1, 1, -2, 2, -2, 2, -1, 1};
const int DX_E[] = {-1, -1, 1, 1};
const int DY_E[] = {-1, 1, -1, 1};

int n;
int a[N][N];

struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[(int)1e7];
int head[N * N * N * N * 3], edge_cnt;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int dis[N * N * N * N * 3];
bool in_que[N * N * N * N * 3];

int px[N * N], py[N * N];
int f[N][N][3][N * N], cnt;

std::queue<int> q;
void Spfa() {
  // printf("%lld\n", s);
  memset(dis, 0x3f, sizeof(dis));
  // memset(in_que, false, sizeof(in_que));
  // printf("%u\n", q.size());
  int x = px[1], y = py[1];
  int s1 = f[x][y][0][1], s2 = f[x][y][1][1], s3 = f[x][y][2][1];
  q.push(s1);
  q.push(s2);
  q.push(s3);
  // printf("%lld\n", s);
  dis[s1] = 0;
  dis[s2] = 0;
  dis[s3] = 0;
  // printf("qwq\n");
  in_que[s1] = true;
  in_que[s2] = true;
  in_que[s3] = true;
  while (!q.empty()) {
    int u = q.front();
    // printf("%lld ", u);
    q.pop();
    // printf("%u\n", q.size());
    in_que[u] = false;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      // printf("%lld ", v);
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        if (!in_que[v]) {
          q.push(v);
          in_que[v] = true;
        }
      }
    }
    // printf("\n");
  }
  // for (int i = 1; i <= n * n * 3; ++i)
  //   printf("%lld\n", dis[i]);
  // printf("%lld %lld %lld\n", f[1][2][0][9], f[1][2][1][9], f[1][2][2][9]);
  // printf("%lld %lld %lld\n", dis[27], dis[36], dis[45]);
}

const int D = 1e6;

signed main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      scanf("%lld", &a[i][j]);
      px[a[i][j]] = i;
      py[a[i][j]] = j;
    }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      for (int k = 0; k < 3; ++k)
        for (int l = 1; l <= n * n; ++l)
          f[i][j][k][l] = ++cnt;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      for (int k = 1; k <= n * n; ++k) {
        AddEdge(f[i][j][0][k], f[i][j][1][k], D + 1);
        AddEdge(f[i][j][1][k], f[i][j][0][k], D + 1);
        AddEdge(f[i][j][0][k], f[i][j][2][k], D + 1);
        AddEdge(f[i][j][2][k], f[i][j][0][k], D + 1);
        AddEdge(f[i][j][1][k], f[i][j][2][k], D + 1);
        AddEdge(f[i][j][2][k], f[i][j][1][k], D + 1);
        if (k + 1 == a[i][j]) {
          AddEdge(f[i][j][0][k], f[i][j][0][k + 1], 0);
          AddEdge(f[i][j][1][k], f[i][j][1][k + 1], 0);
          AddEdge(f[i][j][2][k], f[i][j][2][k + 1], 0);
        }
        for (int l = 1; l <= n; ++l) {
          if (l != i)
            AddEdge(f[i][j][0][k], f[l][j][0][k], D);
          if (l != j)
            AddEdge(f[i][j][0][k], f[i][l][0][k], D);
        }
        for (int l = 0; l < 8; ++l) {
          int x = i + DX_H[l], y = j + DY_H[l];
          if (x >= 1 && x <= n && y >= 1 && y <= n)
            AddEdge(f[i][j][1][k], f[x][y][1][k], D);
        }
        for (int l = 0; l < 4; ++l)
          for (int p = 1; p <= n; ++p) {
            int x = i + p * DX_E[l], y = j + p * DY_E[l];
            if (x >= 1 && x <= n && y >= 1 && y <= n)
              AddEdge(f[i][j][2][k], f[x][y][2][k], D);
          }
      }
  // printf("%lld %lld %lld\n", i, j, k);
  // printf("qwq\n");
  Spfa();
  int ans = LLONG_MAX;
  for (int i = 0; i < 3; ++i) {
    ans = std::min(ans, dis[f[px[n * n]][py[n * n]][i][n * n]]);
    // printf("%lld\n", dis[f[px[n * n]][py[n * n]][i][n * n]]);
  }
  printf("%lld %lld\n", ans / D, ans % D);
  return 0;
}
