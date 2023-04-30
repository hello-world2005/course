#include <cstdio>

const int N = 1e3 + 10;

int a[N];

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  int last_ans = 0;
  while (q--) {
    int ll, rr, ans = 0, l, r;
    scanf("%d%d", &ll, &rr);
    ll = (ll ^ last_ans - 1 + n) % n + 1;
    rr = (rr ^ last_ans - 1 + n) % n + 1;
    if (ll > rr) ll ^= rr ^= ll ^= rr;
    l = ll, r = rr;
    for (int i = l; i <= r; ++i)
      for (int j = i + 1; j <= r; ++j)
        if (a[i] > a[j]) ans += 1;
    printf("%d\n", last_ans = ans);
  }
  return 0;
}
