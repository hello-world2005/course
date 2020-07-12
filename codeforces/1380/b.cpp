#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 10;

char s[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    int b[200] = {0};
    for (int i = 1; i <= n; ++i)
      ++b[s[i]];
    int a[200];
    for (int i = 1; i <= 128; ++i)
      a[i] = i;
    std::sort(a + 1, a + 128,
              [&](const int& lhs, const int& rhs) { return b[lhs] > b[rhs]; });
    if (a[1] == 'R')
      a[1] = 'P';
    else if (a[1] == 'S')
      a[1] = 'R';
    else
      a[1] = 'S';
    for (int i = 1; i <= n; ++i)
      printf("%c", a[1]);
    printf("\n");
  }
  return 0;
}
