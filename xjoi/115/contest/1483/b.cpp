#include <cstdio>

const int N = 1010;

int a[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    int ans = 0;
    for (int i = n; i >= 1; i -= 2)
      ans ^= (a[i] - a[i - 1]);
    if (ans)
      printf("TAK\n");
    else
      printf("NIE\n");
  }
  return 0;
}
