// 6 10 14 15 18 21

#include <cstdio>

const int N = 2e5 + 10;

int p[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    int qwq = n - 6 - 10 - 14;
    if (qwq == 6)
      printf("YES\n%d %d %d %d\n", 5, 10, 6, 15);
    else if (qwq == 10)
      printf("YES\n%d %d %d %d\n", 6, 9, 10, 15);
    else if (qwq == 14)
      printf("YES\n%d %d %d %d\n", 6, 10, 13, 15);
    else if (n <= 30)
      printf("NO\n");
    else
      printf("YES\n%d %d %d %d\n", 6, 10, 14, qwq);
  }
  return 0;
}
