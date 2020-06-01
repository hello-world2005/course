#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    if (m <= n / k) {
      printf("%d\n", m);
    } else if ((m - n / k) % (k - 1) == 0) {
      printf("%d\n", n / k - (m - n / k) / (k - 1));
    } else {
      printf("%d\n", n / k - (m - n / k) / (k - 1) - 1);
    }
  }
  return 0;
}
