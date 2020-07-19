#include <cstdio>

const int N = 2010;

int a[N][N];

int main() {
  int n, m, now;
  scanf("%d%d", &n, &m);
  printf("%d\n", n * (n - m));
  now = n * n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      a[(i + j) % n][j] = now--;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      printf("%d ", a[i][j]);
    printf("\n");
  }
  return 0;
}
