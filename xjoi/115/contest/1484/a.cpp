#include <algorithm>
#include <cstdio>

typedef long long ll;

const int N = 1e5 + 10;

int n, m;
struct Ninja {
  int f, c, l;
} a[N];

int rt[N];
struct Node {
  int ch[2];
  int sze, dis;
  ll sum;
} t[N];

#define lc(x) t[x].ch[0]
#define rc(x) t[x].ch[1]

void Build(int x) {
  t[x].sze = 1;
  rt[x] = x;
  t[x].sum = a[x].c;
}

int Merge(int x, int y) {
  if (!x || !y)
    return x + y;
  if (a[x].c < a[y].c)
    std::swap(x, y);
  rc(x) = Merge(rc(x), y);
  if (t[lc(x)].dis < t[rc(x)].dis)
    std::swap(lc(x), rc(x));
  t[x].dis = t[rc(x)].dis + 1;
  return x;
}

int main() {
  scanf("%d%d", &n, &m);
  ll ans = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", &a[i].f, &a[i].c, &a[i].l);
    ans = std::max(ans, 1ll * a[i].l);
    Build(i);
  }
  for (int i = n; i > 1; --i) {
    int now = a[i].f;
    rt[now] = Merge(rt[i], rt[now]);
    t[now].sze += t[i].sze;
    t[now].sum += t[i].sum;
    while (t[now].sum > m) {
      --t[now].sze;
      t[now].sum -= a[rt[now]].c;
      rt[now] = Merge(lc(rt[now]), rc(rt[now]));
    }
    ans =  std::max(ans, 1ll * t[now].sze * a[now].l);
  }
  printf("%lld\n", ans);
  return 0;
}
