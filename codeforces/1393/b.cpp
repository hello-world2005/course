#include <algorithm>
#include <cstdio>

const int N = 1e5 + 10;

int a[N], b[N];

int main() {
  int n, m = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), ++b[a[i]], m = std::max(m, a[i]);
  int _2 = 0, _4 = 0, _6 = 0, _8 = 0;
  for (int i = 1; i <= m; ++i) {
    if (b[i] >= 8)
      ++_8;
    if (b[i] >= 6)
      ++_6;
    if (b[i] >= 4)
      ++_4;
    if (b[i] >= 2)
      ++_2;
  }
  int q;
  scanf("%d", &q);
  while (q--) {
    char opt[10];
    int x;
    scanf("%s%d", opt, &x);
    if (opt[0] == '-') {
      if (b[x] == 8)
        --_8;
      if (b[x] == 6)
        --_6;
      if (b[x] == 4)
        --_4;
      if (b[x] == 2)
        --_2;
      --b[x];
    } else {
      if (b[x] == 7)
        ++_8;
      if (b[x] == 5)
        ++_6;
      if (b[x] == 3)
        ++_4;
      if (b[x] == 1)
        ++_2;
      ++b[x];
    }
    // printf("%d %d %d %d\n", _2, _4, _6, _8);
    if (_8)
      printf("YES\n");
    else if (_6 && _2 - _6)
      printf("YES\n");
    else if (_4 - _6 >= 2)
      printf("YES\n");
    else if (_4 && _2 - _4 >= 2)
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}
