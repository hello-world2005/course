#include <cstdio>

const int N = 210;

int a[N];
int dp[N][N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), a[i + n] = a[i];
  n <<= 1;
  for (int i = )
}
