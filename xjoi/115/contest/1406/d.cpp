#include <algorithm>
#include <cstdio>

const int N = 60;

int n, h;
int dp[N][N];
struct Node {
  int h, a;

  Node() : h(0), a(0) {}

  bool operator<(const Node& rhs) const {
    return a != rhs.a ? a < rhs.a : h > rhs.h;
  }
} a[N];

int main() {
  scanf("%d%d", &n, &h);
  int sumh = 0, suma = 0;
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i].h), sumh += a[i].h;
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i].a), suma += a[i].a;
  if (sumh < h) {
    printf("0\n");
    return 0;
  }
  std::sort(a + 1, a + n + 1);
  dp[0][0] = sumh;
  for (int i = 1; i <= n; ++i)
    dp[i][0] = 0x3f3f3f3f;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= i; ++j) {
      dp[i][j] = 0x3f3f3f3f;
      for (int k = 0; k < i; ++k)
        if (k >= j - 1)
          dp[i][j] =
              std::min(dp[i][j], dp[k][j - 1] + suma - a[i].h - a[i].a * j);
    }
  for (int i = 1; i <= n; ++i) {
    int t = 0x3f3f3f3f;
    for (int j = i; j <= n; ++j)
      t = std::min(t, dp[j][i]);
    if (t <= h) {
      printf("%d\n", i);
      return 0;
    }
  }
  printf("-1\n");
  return 0;
}
