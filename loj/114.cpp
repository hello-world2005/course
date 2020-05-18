#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")

#include <cstdio>

#define int long long

const int N = 1e5 + 10;

int n, m, k;
int a[N];
int d[N];

bool Insert(int k) {
  for (int i = 52; i >= 0; --i)
    if (k >> i & 1ll) {
      if (d[i]) {
        k ^= d[i];
      } else {
        d[i] = k;
        return true;
      }
    }
  return false;
}

int p[N], cnt;

int Query(int k, bool flag) {
  if (flag)
    --k;
  if ((1ll << cnt) <= k)
    return -1;
  if (!k)
    return 0;
  int res = 0;
  for (int i = 0; i < cnt; ++i)
    if (k >> i & 1) {
      k ^= (1ll << i);
      res ^= p[i];
    }
  return res;
}

signed main() {
  scanf("%lld", &n);
  bool flag = false;
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
    if (!Insert(a[i]))
      flag = true;
  }
  for (int i = 1; i <= 52; ++i)
    for (int j = 0; j < i; ++j)
      if (d[i] >> j & 1ll)
        d[i] ^= d[j];
  for (int i = 0; i <= 52; ++i)
    if (d[i])
      p[cnt++] = d[i];
  // for (int i = 0; i <= cnt; ++i)
  //   printf("%lld ", p[i]);
  // printf("\n");
  scanf("%lld", &m);
  while (m--) {
    scanf("%lld", &k);
    printf("%lld\n", Query(k, flag));
  }
  return 0;
}
