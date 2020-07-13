#include <algorithm>
#include <cstdio>
#include <set>

const int N = 2e5 + 10;

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
  m -= 1;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    a[i] -= 1;
    s[a[i]].insert(i);
    fa[i] = i;
  }
  int ans = 0;
  for (int i = 0; i < n - 1; ++i)
    if (a[i] != a[i + 1])
      ++ans;
  printf("%d\n", ans);
  while (m--) {
    int x, y;
    scanf("%d%d", &x, &y);
    x -= 1, y -= 1;
    int fx = FindFa(x), fy = FindFa(y);
    if (s[fx].size() > s[fy].size())
      std::swap(fx, fy);
    for (auto i : s[fx]) {
      auto it = s[fy].lower_bound(i);
      if (it != s[fy].end())
        ans -= ((*it) == i + 1);
      if (it != s[fy].begin())
        it--, ans -= (i == (*it) + 1);
    }
    for (auto i : s[fx])
      s[fy].insert(i);
    fa[fx] = fy;
    printf("%d\n", ans);
  }
  return 0;
}
