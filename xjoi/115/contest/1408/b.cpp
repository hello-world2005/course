#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e6 + 10;

int n, m;
int a[N];
bool vis[N];

int Gcd(int a, int b) {
  if (b == 0)
    return a;
  return Gcd(b, a % b);
}

int dis[N], w[N], cnt;
bool bok[N];

int Dijkstra() {
  memset(dis, 0x7f, sizeof(dis));
  dis[0] = 0;
  for (int i = 2; i <= 3000; ++i)
    if (vis[i])
      w[cnt++] = i;
  int mod = w[0];
  while (true) {
    int i, k, v;
    for (i = 0, k = -1; i < mod; ++i)
      if (!bok[i] && (k == -1 || dis[i] < dis[k]))
        k = i;
    if (k == -1)
      break;
    bok[k] = true;
    for (i = 1; i < cnt; ++i)
      if (!bok[v = (k + w[i]) % mod])
        dis[v] = std::min(dis[v], dis[k] + w[i]);
  }
  int res = -1;
  for (int i = 1; i < mod; ++i)
    res = std::max(res, dis[i] - mod);
  return res;
}

int main() {
  scanf("%d%d", &n, &m);
  int d = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    d = Gcd(a[i], d);
    for (int j = 0; j <= m && j < a[i]; ++j) {
      d = Gcd(d, a[i] - j);
      vis[a[i] - j] = true;
    }
  }
  if (vis[1] || d > 1) {
    printf("-1\n");
    return 0;
  }
  printf("%d\n", Dijkstra());
  return 0;
}
