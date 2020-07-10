#include <cstdio>

int main() {
  int a, b, c, d, cas = 0;
  while (scanf("%d%d%d%d", &a, &b, &c, &d) == 4 && (~a) && (~b) && (~c) &&
         (~d)) {
    a %= 23, b %= 28, c %= 33;
    for (int i = d + 1;; ++i)
      if (i % 23 == a)
        for (int j = i;; j += 23)
          if (j % 28 == b)
            for (int k = j;; k += 23 * 28)
              if (k % 33 == c) {
                printf("Case %d: the next triple peak occurs in %d days.\n",
                       ++cas, k - d);
                goto ed;
              }
  ed:;
  }
  return 0;
}
