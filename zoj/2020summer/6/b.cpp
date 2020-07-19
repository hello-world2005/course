#include <cstdio>

int F(int x) {
  int res = 0;
  while (x)
    res += (x >>= 1);
  return res;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  n -= m, m = (m - 1) / 2;
  if (F(n) + F(m) == F(n + m))
    printf("1\n");
  else
    printf("0\n");
  return 0;
}
