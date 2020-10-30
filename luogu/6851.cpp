#include <algorithm>
#include <cstdio>
#include <cstring>

#define int long long

const int N = 1e5 + 10;

int n, m, c, v;

struct Card {
  int a, b, idx;  // 花色 点数

  Card()
      : a(0), b(0), idx(0) {}

  bool operator<(const Card& rhs) const {
    if (a == rhs.a) {
      if (b == rhs.b)
        return idx < rhs.idx;
      return b > rhs.b;
    }
    return a < rhs.a;
  }
} a[N], b[N];

bool used1[N], used2[N];
int ans[N];

int sum;

int QwQ(int n, int m) {
  int i = 1, j = 1;
  for (; i <= n; ++i) {
    if (used1[i])
      continue;
    while (a[i].a > b[j].a && j <= m)
      ++j;
    for (; j <= m && a[i].a == b[j].a; ++j)
      if (!used2[j] && a[i].b >= b[j].b) {
        used1[i] = used2[j] = true;
        sum += (a[i].b + c);
        ans[b[j].idx] = a[i].idx;
        break;
      }
  }
  return sum;
}

int QaQ(int n, int m) {
  int i = 1, j = 1;
  for (; i <= n; ++i) {
    if (used1[i])
      continue;
    while (a[i].a > b[j].a && j <= m)
      ++j;
    for (; j <= m && a[i].a == b[j].a; ++j)
      if (!used2[j]) {
        used1[i] = used2[j] = true;
        sum += (a[i].b - c);
        ans[b[j].idx] = a[i].idx;
        break;
      }
  }
  for (int i = 1; i <= m; ++i)
    if (!used2[i])
      sum -= c;
  return sum;
}

signed main() {
  scanf("%lld%lld%lld%lld", &n, &m, &c, &v);
  sum = v;
  for (int i = 1; i <= n; ++i)
    scanf("%lld%lld", &a[i].a, &a[i].b), a[i].idx = i;
  for (int i = 1; i <= m; ++i)
    scanf("%lld%lld", &b[i].a, &b[i].b), b[i].idx = i;
  std::sort(a + 1, a + n + 1), std::sort(b + 1, b + m + 1);
  memset(ans, -1, sizeof(ans));
  QwQ(n, m), QaQ(n, m);
  printf("%lld\n", sum);
  for (int i = 1; i <= m; ++i)
    printf("%lld\n", ans[i]);
  return 0;
}
