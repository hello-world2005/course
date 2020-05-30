#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define c 1005
int m, n, o[c], u[c][c], t[c], g = 1e9;
const int e = 1e9;
vector<int> v[c];
char j[1 << 21], *h = j, *i = j;
int l() {
  int d = 0, f = 1;
  char g = ' ';
  while (g < '0' || g > '9')
    g = getchar(), f = g == '-' ? -1 : f;
  while (g >= '0' && g <= '9')
    d = d * 10 + g - 48, g = getchar();
  return d * f;
}
void s(int p, int w) {
  int q = e, r = 0, x;
  for (int a = 0; a < v[p].size(); a++) {
    x = v[p][a];
    if (x == w)
      continue;
    s(x, p);
    r = r < t[x] ? t[x] : r;
    q = q > t[x] ? t[x] : q;
    u[p][t[x]]++;
  }
  for (int a = q; a <= r; a++)
    if (u[p][a] >= 2)
      u[p][a - 1 + u[p][a]]++, r = r < a - 1 + u[p][a] ? a - 1 + u[p][a] : r,
                               u[p][a] = 0;
  t[p] = r + 1;
}
void y() {
  memset(t, 0, sizeof(t));
  memset(u, 0, sizeof(u));
}
signed main() {
  m = l();
  int b;
  for (int a = 2; a <= m; a++) {
    b = l();
    v[a].push_back(b);
    v[b].push_back(a);
  }
  for (int a = 1; a <= m; a++)
    y(), s(a, 0), n = t[a] == g ? n + 1 : (t[a] < g ? 1 : n),
                  o[n] = t[a] > g ? o[n] : a, g = g > t[a] ? t[a] : g;
  printf("%d\n", g);
  for (int a = 1; a <= n; a++)
    printf("%d ", o[a]);
  return 0;
}