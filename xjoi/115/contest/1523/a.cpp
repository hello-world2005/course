#include <cstdio>
#include <cstring>

const int N = 1e4 + 10;

char s[N];
int a[N];

int main() {
  int n, m;
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 1, p = 1; i <= n; ++i)
    if (s[i] == 'T')
      a[i] = i - p, p = i;
  // for (int i = 1; i <= n; ++i)
  //   printf("%d ", a[i]);
  // printf("\n");
  scanf("%d", &m);
  while (m--) {
    int l, r, k, res = 0;
    scanf("%d%d%d", &l, &r, &k);
    bool fir = true;
    for (int i = l; i <= r; ++i)
      if (s[i] == 'T') {
        if (fir)
          res += (k - ((i - l + 1) % k)) % k, fir = false;
        else
          res += (k - ((a[i]) % k)) % k;
      }
    printf("%d\n", r - l + 1 + res);
  }
  return 0;
}
