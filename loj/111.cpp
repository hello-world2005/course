#include <cstdio>
#include <cstring>

const int N = 1e6 + 10;

int n, m = 200;
char s[N];
int sa[N], rk[N], lst_rk[N], sum[N], idx[N], px[N];

bool Cmp(const int& x, const int& y, const int& w) {
  return (lst_rk[x] == lst_rk[y]) && (lst_rk[x + w] == lst_rk[y + w]);
}

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 1; i <= n; ++i)
    ++sum[rk[i] = s[i]];
  for (int i = 1; i <= m; ++i)
    sum[i] += sum[i - 1];
  for (int i = n; i >= 1; --i)
    sa[sum[rk[i]]--] = i;
  for (int w = 1, p; w < n; w <<= 1, m = p) {
    p = 0;
    for (int i = n; i > n - w; --i)
      idx[++p] = i;
    for (int i = 1; i <= n; ++i)
      if (sa[i] > w)
        idx[++p] = sa[i] - w;
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= n; ++i)
      ++sum[px[i] = rk[idx[i]]];
    for (int i = 1; i <= m; ++i)
      sum[i] += sum[i - 1];
    for (int i = n; i >= 1; --i)
      sa[sum[px[i]]--] = idx[i];
    memcpy(lst_rk, rk, sizeof(rk));
    p = 0;
    for (int i = 1; i <= n; ++i)
      rk[sa[i]] = Cmp(sa[i], sa[i - 1], w) ? p : ++p;
  }
  for (int i = 1; i <= n; ++i)
    printf("%d ", sa[i]);
  return 0;
}
