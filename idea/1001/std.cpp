#include <algorithm>
#include <cstdio>
#include <cstring>

#define int long long

const int N = 1e6 + 10;
const int K = 70;

int n, m;
int a[N];
int d[K], p[K];
int dd[N][K], pp[N][K];

void Insert(int k, int r) {
  int _r = r;
  for (int i = 63; i >= 0; --i)
    if (k >> i & 1ll) {
      if (!d[i]) {
        d[i] = k;
        p[i] = r;
        break;
      } else if (p[i] < r) {
        std::swap(d[i], k);
        std::swap(p[i], r);
      }
      k ^= d[i];
    }
  r = _r;
  for (int i = 63; i >= 0; --i) {
    dd[r][i] = d[i];
    pp[r][i] = p[i];
  }
}

int Query(int l, int r) {
  int res = 0;
  for (int i = 63; i >= 0; --i)
    if (pp[r][i] >= l)
      res = std::max(res, res ^ dd[r][i]);
  return res;
}

signed main() {
  scanf("%lld%lld", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
    Insert(a[i], i);
  }
  int last_ans = 0;
  while (m--) {
    int l, r;
    scanf("%lld%lld", &l, &r);
    l = (l ^ last_ans) % n + 1;
    r = (r ^ last_ans) % n + 1;
    if (l > r)
      std::swap(l, r);
    printf("%lld\n", last_ans = Query(l, r));
  }
  return 0;
}
