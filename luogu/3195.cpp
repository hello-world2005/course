#include <cstdio>
#include <deque>

#define int long long

const int N = 5e4 + 10;

int n, k;
int a[N], s[N];
int dp[N];

int A(int i) {
  return s[i] + i;
}

int B(int i) {
  return A(i) + k + 1;
}

int GetX(int i) {
  return B(i);
}

int GetY(int i) {
  return dp[i] + B(i) * B(i);
}

double Slope(int x, int y) {
  return 1.0 * (GetY(x) - GetY(y)) / (GetX(x) - GetX(y));
}

signed main() {
  scanf("%lld%lld", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]), s[i] = s[i - 1] + a[i];
  std::deque<int> q;
  q.push_back(0);
  for (int i = 1; i <= n; ++i) {
    while (q.size() >= 2 && Slope(q[0], q[1]) < 2.0 * A(i))
      q.pop_front();
    dp[i] = dp[q[0]] + (A(i) - B(q[0])) * (A(i) - B(q[0]));
    while (q.size() >= 2 &&
           Slope(q[q.size() - 2], q[q.size() - 1]) > Slope(i, q[q.size() - 1]))
      q.pop_back();
    q.push_back(i);
  }
  printf("%lld\n", dp[n]);
  return 0;
}
