#include <algorithm>
#include <cstdio>
#include <cstring>

#define int long long

const int N = 6e5 + 10;

struct LeftishTree {
  int fa[N], val[N], ch[N][2], dis[N];

  int Merge(int x, int y) {
    if (!x || !y)
      return x + y;
    if (val[x] < val[y])
      std::swap(x, y);
    ch[x][1] = Merge(ch[x][1], y);
    if (dis[ch[x][0]] < dis[ch[x][1]])
      std::swap(ch[x][0], ch[x][1]);
    dis[x] = (ch[x][1] == 0 ? 0 : dis[ch[x][1]] + 1);
    return x;
  }

  int Pop(int x) { return Merge(ch[x][0], ch[x][1]); }
} lt;

int fa[N], len[N];
int deg[N];
int rt[N];
int tot;

signed main() {
  int n, m;
  scanf("%lld%lld", &n, &m);
  for (int i = 2; i <= n + m; ++i)
    scanf("%lld%lld", &fa[i], &len[i]), ++deg[fa[i]];
  for (int i = n + m, ql, qr; i > 1; --i) {
    ql = qr = 0;
    if (i <= n) {
      while (--deg[i])
        rt[i] = lt.Pop(rt[i]);
      qr = lt.val[rt[i]], rt[i] = lt.Pop(rt[i]);
      ql = lt.val[rt[i]], rt[i] = lt.Pop(rt[i]);
    }
    lt.val[++tot] = ql + len[i], lt.val[++tot] = qr + len[i];
    rt[i] = lt.Merge(rt[i], lt.Merge(tot - 1, tot));
    rt[fa[i]] = lt.Merge(rt[fa[i]], rt[i]);
  }
  long long ans = 0;
  for (int i = 1; i <= n + m; ++i)
    ans += len[i];
  while (deg[1]--)
    rt[1] = lt.Pop(rt[1]);
  // for (int i = 1; i <= n + m; ++i)
  //   printf("%lld ", lt.val[i]);
  // printf("\n");
  while (rt[1])
    ans -= lt.val[rt[1]], rt[1] = lt.Pop(rt[1]);
  printf("%lld\n", ans);
  return 0;
}
