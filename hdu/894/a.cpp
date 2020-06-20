#include <cstdio>
#include <cstring>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);
    while (n--) {
      char s[60];
      scanf("%s", s + 1);
      int len = strlen(s + 1);
      for (int i = 1; i <= len; ++i)
        if (s[i] == '-' && s[i + 1] == '>') {
          for (int j = 1; j <= k; ++j)
            printf(" ");
          ++i;
        } else {
          printf("%c", s[i]);
        }
      printf("\n");
    }
  }
  return 0;
}
