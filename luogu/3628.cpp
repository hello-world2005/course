// $dp_i = \max\limits_{1 \le j < i}\{dp_j + a(s_i - s_j)^2 + b(s_i - s_{j
// + 1}) + c\}$

// $dp_i = \max\limits_{1 \le j < i}\{dp_j - 2 as_is_j + as_j^2 -
// bs_j\} + bs_i + as_i^2 + c$

// $k = 2as_i$

// $x = s_j$

// $b = dp_i - as_i^2 - bs_i - c$

// $y = dp_j + as_j^2 - bs_j$

#include <algorithm>
#include <cstdio>
#include <deque>

#define int long long

const int N = 1e6 + 10;

int a, b, c;
int d[N], s[N];
int dp[N];

int A(int i) {
  return 2 * a * s[i];
}

int B(int i) {
  return dp[i] - a * s[i] * s[i] - b * s[i] - c;
}

int GetX(int i) {
  return s[i];
}

int GetY(int i) {
  return dp[i] + a * s[i] * s[i] - b * s[i];
}

double Slope(int x, int y) {
  return 1.0 * (GetY(x) - GetY(y)) / (GetX(x) - GetX(y));
}

signed main() {
  int n;
  scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
  ;
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &d[i]), s[i] = s[i - 1] + d[i];
  std::deque<int> q;
  q.push_back(0);
  for (int i = 1; i <= n; ++i) {
    while (q.size() >= 2 && Slope(q[0], q[1]) > A(i))
      q.pop_front();
    // printf("%lld %lld\n", i, q[0]);
    dp[i] = dp[q[0]] + a * (s[i] - s[q[0]]) * (s[i] - s[q[0]]) +
            b * (s[i] - s[q[0]]) + c;
    while (q.size() >= 2 &&
           Slope(q[q.size() - 2], q[q.size() - 1]) < Slope(q[q.size() - 1], i))
      q.pop_back();
    q.push_back(i);
  }
  // for (int i = 1; i <= n; ++i)
  //   printf("%lld ", dp[i]);
  // printf("\n");
  printf("%lld\n", dp[n]);
  return 0;
}
