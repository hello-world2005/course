#include <algorithm>
#include <cstdio>
#include <set>

const int N = 1e5 + 10;

int n, m;
int a[N];
int fa[N];
std::set<int> s[N];

int FindFa(int u) {
  if (fa[u] == u)
    return u;
  return fa[u] = FindFa(fa[u]);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    s[a[i]].insert(i);
    fa[i] = i;
  }
  int ans = 0;
  for (int i = 1; i < n; ++i)
    if (a[i] != a[i + 1])
      ++ans;
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    int fx = FindFa(x), fy = FindFa(y);
    if (s[fx].size() > s[fy].size())
      std::swap(fx, fy);
    for (auto i : s[fx]) {
      auto it = s[y].lower_bound(i);
      if (it != s[fy].end())
        ans += (*it == (i + 1));
      if (it != s[fy].begin())
        it--, ans -= (i == (*it - i));
    }
    printf("%d\n", ans);
  }
  return 0;
}
