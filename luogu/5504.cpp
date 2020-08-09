#include <cstdio>
#include <deque>

#define int long long

const int N = 1e5 + 10;

int n;
int s[N], b[N], sum[N];
int dp[N];

int Check(int i, int t) {
  return dp[i - 1] + s[i] * t * t;
}

int BinarySearch(int ql, int qr) {
  int l = 1, r = n, res = n + 1;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (Check(ql, mid - sum[ql] + 1) < Check(qr, mid - sum[qr] + 1))
      l = mid + 1;
    else
      r = mid - 1, res = mid;
  }
  return res;
}

std::deque<int> stk[N];

signed main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &s[i]), sum[i] = ++b[s[i]];
  for (int i = 1; i <= n; ++i) {
    while (stk[s[i]].size() >= 2 && BinarySearch(stk[s[i]][stk[s[i]].size() - 2], stk[s[i]][stk[s[i]].size() - 1]) <= BinarySearch(stk[s[i]][stk[s[i]].size() - 1], i))
      stk[s[i]].pop_back();
    stk[s[i]].push_back(i);
    while (stk[s[i]].size() >= 2 && BinarySearch(stk[s[i]][stk[s[i]].size() - 2], stk[s[i]][stk[s[i]].size() - 1]) <= sum[i])
      stk[s[i]].pop_back();
    dp[i] = Check(stk[s[i]][stk[s[i]].size() - 1], sum[i] - sum[stk[s[i]][stk[s[i]].size() - 1]] + 1);
  }
  printf("%lld\n", dp[n]);
  return 0;
}
