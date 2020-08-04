#include <cstdio>
#include <cstring>
#include <cmath>

#define double long double

const int N = 1e5 + 10;

int n, l, p;

double FastPow(double a, int b) {
  double res = 1;
  for (; b; b >>= 1, a = a * a)
    if (b & 1)
      res = res * a;
  return res;
}

double dp[N];
int sum[N];

double Check(int i, int j) {
  return dp[j] + FastPow(abs(sum[i] - sum[j] - l - 1), p);
}

int BinarySearch(int ql, int qr) {
  int l = 0, r = n + 1, res;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (Check(mid, ql) < Check(mid, qr))
      l = mid + 1, res = mid + 1;
    else
      r = mid - 1;
  }
  return res;
}

char s[N][40];
int q[N];
int pos[N], pre[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &l, &p);
    for (int i = 1; i <= n; ++i) {
      scanf("%s", s[i] + 1);
      sum[i] = sum[i - 1] + strlen(s[i] + 1) + 1;
    }
    int he = 1, ta = 1;
    q[he] = 0;
    for (int i = 1; i <= n; ++i) {
      while (he < ta && pos[he] <= i)
        ++he;
      dp[i] = Check(i, q[he]), pre[i] = q[he];
      while (he < ta && pos[ta - 1] >= BinarySearch(q[ta], i))
        --ta;
      pos[ta] = BinarySearch(q[ta], i);
      q[++ta] = i;
    }
    if (dp[n] > 1e18) {
      printf("Too hard to arrange\n");
    } else {
      printf("%.0Lf\n", dp[n]);
      int tp = 0;
      q[tp] = n;
      int i = n;
      for (; i; q[++tp] = i = pre[i])
        ;
      for (; tp; --tp) {
        for (i = q[tp] + 1; i < q[tp - 1]; ++i)
          printf("%s ", s[i] + 1);
        puts(s[i] + 1);
      }
    }
    puts("--------------------");
  }
  return 0;
}
