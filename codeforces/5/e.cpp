#include <cstdio>

const int N = 2e6 + 10;

int a[N], b[N];
int l[N], r[N], cnt[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &a[i]);
  int pos = 0;
  for (int i = 1; i < n; ++i)
    if (a[i] > a[pos])
      pos = i;
  for (int i = 0; i <= n; ++i)
    b[i] = a[(i + pos) % n];
  for (int i = 1; i <= n; ++i) {
    l[i] = i - 1;
    while (l[i] && b[i] >= b[l[i]])
      l[i] = l[l[i]];
  }
  for (int i = n - 1; i >= 0; --i) {
    r[i] = i + 1;
    while (r[i] < n && b[i] > b[r[i]])
      r[i] = r[r[i]];
    if (r[i] < n && b[i] == b[r[i]]) {
      cnt[i] = cnt[r[i]] + 1;
      r[i] = r[r[i]];
    }
  }
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += cnt[i];
    if (b[i] < b[0]) {
      ans += 2;
      if (!l[i] && r[i] == n)
        --ans;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
