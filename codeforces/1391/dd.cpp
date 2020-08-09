#include <cstdio>
#include <vector>

int n, m;
std::vector<int> v;

int a[10][10];

int Count(int x, int y, int a, int b) {
  int res = 0;
  for (int i = x; i <= a; ++i)
    for (int j = y; j <= b; ++j)
      if (::a[i][j])
        ++res;
  return res;
}

bool Check() {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      a[i][j] = v[m * (i - 1) + j - 1];
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      for (int k = 1; i + k <= n && j + k <= m; k += 2) {
          // printf("%d %d %d %d %d\n", i, j, i + k, j + k, Count(i, j, i + k, j + k));
          if (!(Count(i, j, i + k, j + k) & 1))
            return false;
        }
  return true;
}

int ans;

void Dfs(int dep) {
  if (dep == n * m + 1) {
    if (Check()) {
      printf("{");
      for (int i = 1; i <= n; ++i) {
        printf("\"");
        for (int j = 1; j <= m; ++j)
          printf("%d", v[m * (i - 1) + j - 1]);
        printf("\"");
        if (i != n)
          printf(",");
      }
      printf("},");
      ++ans;
    }
    return;
  }
  v.push_back(0);
  Dfs(dep + 1);
  v.pop_back(), v.push_back(1);
  Dfs(dep + 1);
  v.pop_back();
}

int main() {
  // v.push_back(1), v.push_back(0), v.push_back(0), v.push_back(0), v.push_back(0), v.push_back(0), v.push_back(1), v.push_back(0);
  // n = 2, m = 4;
  // printf("%d\n", Check());
  // return 0;
  scanf("%d%d", &n, &m);
  Dfs(1);
  printf("%d\n", ans);
}
