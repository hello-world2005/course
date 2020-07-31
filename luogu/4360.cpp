#include <algorithm>
#include <cstdio>
#include <deque>

const int N = 2e4 + 10;

int a[N], d[N];
int s[N];
int dp[N];

double Slope(int x, int y) {
  return 1.0 * (d[x] * s[x] - d[y] * s[y]) / (s[x] - s[y]);
}

int main() {
  int n, sum = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d%d", &a[i], &d[i]), s[i] = s[i - 1] + a[i];
  for (int i = n; i >= 1; --i)
    d[i] += d[i + 1], sum += d[i] * a[i];
  std::deque<int> q;
  q.push_back(0);
  for (int i = 1; i <= n; ++i) {
    while (q.size() >= 2 && Slope(q[0], q[1]) > d[i])
      q.pop_front();
    dp[i] = sum - d[q[0]] * s[q[0]] - d[i] * (s[i] - s[q[0]]);
    while (q.size() >= 2 &&
           Slope(q[q.size() - 2], q[q.size() - 1]) < Slope(q[q.size() - 1], i))
      q.pop_back();
    q.push_back(i);
  }
  int ans = 2e9;
  for (int i = 1; i <= n; ++i)
    ans = std::min(ans, dp[i]);
  printf("%d\n", ans);
  return 0;
}
