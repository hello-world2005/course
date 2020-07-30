#include <algorithm>
#include <cmath>
#include <cstdio>

const int N = 3e5 + 10;
const int K = 23;

int a[N];
int st[N][K];

void Build(int n) {
  for (int i = 1; i <= n; ++i)
    st[i][0] = a[i];
  for (int j = 1; j < K; ++j)
    for (int i = 1; i + (1 << j) - 1 <= n; ++i)
      st[i][j] = std::max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

int Query(int l, int r) {
  int len = log2(r - l + 1);
  return std::max(st[l][len], st[r - (1 << len) + 1][len]);
}

int dp[N];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  Build(n);
  for (int i = 1; i <= n; ++i) {
    int s = a[i];
    dp[i] = dp[i - 1] + a[i];
    for (int j = i - 1; j >= 0; --j) {
      if (s > k)
        break;
      dp[i] = std::min(dp[i], dp[j] + Query(j + 1, i));
      s += a[j];
    }
  }
  printf("%d\n", dp[n]);
  return 0;
}

// 8 17
// 2 2 2 8 1 8 2 1
