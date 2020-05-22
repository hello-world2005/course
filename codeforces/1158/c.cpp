#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 5e5 + 10;

int n;
struct Node {
  int val, idx;

  bool operator<(const Node& rhs) const {
    return val != rhs.val ? val > rhs.val : idx < rhs.idx;
  }
} a[N];
int poi[N], ans[N];
int p[N];

// int deg[N];

// struct Edge {
//   int v, nxt;

//   Edge() : v(0), nxt(0) {}
//   Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
// } e[N << 1];
// int head[N], edge_cnt;

// void AddEdge(int u, int v) {
//   e[++edge_cnt] = Edge(v, head[u]);
//   head[u] = edge_cnt;
// }

// void TopSort(int s) {
//   std::queue<int> q;
//   for (int i = 1; i <= n; ++i)
//     if (!deg[i])
//       q.push(i);
//   while (!q.empty()) {
//     int u = q.front();
//     q.pop();
//     for (int i = head[u]; i; i = e[i].nxt) {
//       int v = e[i].v;
//       if (!(--deg[v]))
//         q.push(v);
//     }
//   }
// }

// int t[N << 2];

// #define lc (rt << 1)
// #define rc (rt << 1 | 1)
// #define ls lc, l, mid
// #define rs rc, mid + 1, r

// void PushUp(int rt) {
//   t[rt] = t[lc] + t[rc];
// }

// void Update(int rt, int l, int r, int ql, int qr, int val) {}

// int Query(int rt, int l, int r, int ql, int qr) {}

int sta[N], tp;

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    sta[tp = 1] = n + 1;
    bool cant = false;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &p[i]);
      while (sta[tp] <= i)
        --tp;
      if (p[i] > sta[tp])
        cant = true;
      sta[++tp] = p[i];
      while (sta[tp] <= i)
        --tp;
      // printf("%d\n", tp);
      a[i] = Node{p[i], i};
    }
    if (cant) {
      printf("-1\n");
      continue;
    }
    for (int i = 1; i <= n; ++i)
      if ((~p[i]) && p[p[i]] == -1)
        a[p[i]].val = p[i] + 1;
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i)
      ans[a[i].idx] = n - i + 1;
    for (int i = 1; i <= n; ++i)
      printf("%d ", ans[i]);
    printf("\n");
  }
  return 0;
}
