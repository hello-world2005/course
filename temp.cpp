#include <cstdio>

int n = 10;
int a[] = {0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5};
int opt[20];

int Sum() {
  int ans = 0, pre = 0, lstopt = 0;
  for (int i = 1; i <= n; ++i) {
    if (opt[i] == 0) pre = pre * 10 + a[i];
    if (opt[i] == 1) ans += (lstopt == 1 ? 1 : -1) * pre, pre = a[i], lstopt = 1;
    if (opt[i] == 2) ans += (lstopt == 1 ? 1 : -1) * pre, pre = a[i], lstopt = 2;
  }
  ans += (lstopt == 1 ? 1 : -1) * pre;
  return ans;
}

int tot;

void Print() {
  for (int i = 1; i <= n; ++i) {
    if (opt[i] == 1) printf("+");
    if (opt[i] == 2) printf("-");
    printf("%d", a[i]);
  }
  printf("\n");
}

void Dfs(int dep) {
  if (dep == n + 1) {
    if (Sum() == 100) Print(), tot += 1;
    return;
  }
  if (dep == 1) {
    opt[dep] = 1;
    Dfs(dep + 1);
    opt[dep] = 2;
    Dfs(dep + 1);
  } else {
    opt[dep] = 0;
    Dfs(dep + 1);
    opt[dep] = 1;
    Dfs(dep + 1);
    opt[dep] = 2;
    Dfs(dep + 1);
  }
}

int main() {
  Dfs(1);
  printf("%d\n", tot);
  return 0;
}
