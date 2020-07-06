#include <cstdio>

const int N = 3e5 + 10;

int a[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <=n; ++i)
      scanf("%d", &a[i]);
    if (a[1] < a[n])
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}
