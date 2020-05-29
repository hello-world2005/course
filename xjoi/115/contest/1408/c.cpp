#include <algorithm>
#include <cstdio>
#include <queue>

const int M = 5010;

int n, m;
int a[M];
bool vis[M];
int ans[M], pre[M];

void Print(int x) {
  if (pre[x])
    Print(pre[x]);
  printf("%d", ans[x]);
}

void Bfs() {
  std::queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (!u && vis[u]) {
      // printf("qwq\n");
      Print(u);
      return;
    }
    // printf("%d\n", u);
    for (int i = 1; i <= m; ++i) {
      int v = (u * 10 + a[i]) % n;
      if (vis[v])
        continue;
      if (v == 0 && a[i] == 0)
        continue;
      q.push(v);
      vis[v] = true;
      ans[v] = a[i];
      pre[v] = u;
      // printf("%d ", i);
    }
    // printf("\n");
  }
  printf("0\n");
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i)
    scanf("%d", &a[i]);
  std::sort(a + 1, a + m + 1);
  Bfs();
  return 0;
}
