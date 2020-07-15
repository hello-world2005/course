#include <cstdio>

const int N = 2e6 + 10;

int n;
int a[N] = {0, 1};

int main() {
  scanf("%d", &n);
  int m = 1;
  while (m < n) {
    for (int i = 1; i <= m; ++i)
      a[i] =  (a[i + m] = a[i] << 1) - 1;
    m <<= 1;
  }
  for (int i = 1; i <= m; ++i)
    if (a[i] <= n)
      printf("%d ", a[i]);
  return 0;
}
