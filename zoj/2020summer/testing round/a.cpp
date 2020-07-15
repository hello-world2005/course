#include <cstdio>

const int N = 1e6 + 10;

int a[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, cnt = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]), cnt += (a[i] >= 80);
    printf("%s\n", cnt > n / 3 ? "No" : "Yes");
  }
  return 0;
}
