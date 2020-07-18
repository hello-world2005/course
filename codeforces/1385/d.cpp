#include <algorithm>
#include <cstdio>

const int N = 1e6 + 10;

char s[N];
int a[N];
int ans;

void Dfs(int u, int l, int r, int c) {
  if (c >= ans)
    return;
  if (l == r) {
    if (a[l] == u)
      ans = std::min(ans, c);
    else
      ans = std::min(ans, c + 1);
    return;
  }
  int mid = (l + r) >> 1, res = 0;
  for (int i = mid + 1; i <= r; ++i)
    if (a[i] != u)
      ++res;
  Dfs(u + 1, l, mid, c + res);
  res = 0;
  for (int i = l; i <= mid; ++i)
    if (a[i] != u)
      ++res;
  Dfs(u + 1, mid + 1, r, c + res);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i)
      a[i] = s[i] - 'a' + 1;
    ans = n, Dfs(1, 1, n, 0);
    printf("%d\n", ans);
  }
  return 0;
}