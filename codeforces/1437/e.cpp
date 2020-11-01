#include <algorithm>
#include <cstdio>

const int N = 5e5 + 10;

int a[N], b[N], qwq[N];
int cho[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 1; i <= m; ++i)
    scanf("%d", &b[i]), qwq[b[i]] = 1;
  b[0] = 0;
  for (int i = 2; i <= m; ++i)
    if (b[i] - b[i - 1] > a[b[i]] - a[b[i - 1]])
      return printf("-1\n"), 0;
  for (int i = 1; i <= n; ++i)
    a[i] -= i;
  int k = 0, qaq = 0;
  for (int i = 1; i <= n; ++i)
    if (k == 0 || a[i] >= cho[k]) {
      cho[++k] = a[i];
      if (qwq[i])
        qaq = k;
    } else {
      int p = std::upper_bound(cho + 1, cho + k + 1, a[i]) - cho;
      if (p > qaq)
        cho[p] = a[i];
      if (qwq[i])
        qaq = k = p;
    }
  printf("%d\n", n - k);
  return 0;
}
