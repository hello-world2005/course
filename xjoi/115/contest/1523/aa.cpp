#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;

const int N = 5e6 + 10;
const int M = 2e5 + 10;

int p[N], bel[N], a[N], b[N], cnt;
int sum[N];
ll ans[M];
char s[N];

struct Question {
  int l, r, k, id;

  Question() : l(0), r(0), k(0), id(0) {}
} que[M];

int main() {
  int n, m;
  scanf("%s%d", s + 1, &m);
  n = strlen(s + 1);
  for (int i = 1; i <= n; ++i) {
    if (s[i] == 'T')
      p[++cnt] = i, a[cnt] = i - p[cnt - 1] - 1, b[cnt] = cnt;
    bel[i] = cnt;
  }
  for (int i = 1; i <= m; ++i)
    scanf("%d%d%d", &que[i].l, &que[i].r, &que[i].k), que[i].id = i;
  std::sort(que + 1, que + m + 1, [&](const Question lhs, const Question rhs) {
    return lhs.k < rhs.k;
  });
  for (int i = 1; i <= m; ++i) {
    int l = que[i].l, r = que[i].r, k = que[i].k;
    if (k > que[i - 1].k) {
      int len2 = 0;
      for (int j = 1; j <= cnt; ++j)
        if (a[j] >= k)
          a[++len2] = a[j], b[len2] = b[j];
      cnt = len2;
      for (int j = 1; j <= cnt; ++j)
        sum[j] = sum[j - 1] + a[j] / k;
    }
    if (bel[l - 1] == bel[r]) {
      ans[que[i].id] = r - l + 1;
      continue;
    }
    int p1 = std::lower_bound(b + 1, b + cnt + 1, bel[l - 1] + 2) - b;
    int p2 = std::upper_bound(b + 1, b + cnt + 1, bel[r]) - b - 1;
    ans[que[i].id] = 1ll * k *
                         (bel[r] - bel[l - 1] + sum[p2] - sum[p1 - 1] +
                          (p[bel[l - 1] + 1] - l) / k) +
                     r - p[bel[r]];
  }
  for (int i = 1; i <= m; ++i)
    printf("%lld\n", ans[i]);
  return 0;
}
