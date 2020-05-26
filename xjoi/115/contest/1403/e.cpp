#include <algorithm>
#include <cstdio>
#include <iostream>

const int N = 8e4 + 10;

int n, m;
int t[N * 3], id[N], a[N * 3];

#define LowBit(x) (x & -x)

void Add(int a, int b) {
  for (; a < N * 3; a += LowBit(a))
    t[a] += b;
}

int Query(int a) {
  int res = 0;
  for (; a; a -= LowBit(a))
    res += t[a];
  return res;
}

int BinarySearch(int k) {
  int l = 1, r = N * 3 - 10;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (Query(mid) < k)
      l = mid + 1;
    else
      r = mid;
  }
  return l;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, x; i <= n; ++i)
    scanf("%d", &a[i + N]), x = a[i + N], Add(i + N, 1), id[x] = i + N;
  while (m--) {
    char opt[10];
    int x, y;
    scanf(" %s%d", opt + 1, &x);
    if (opt[1] == 'T') {
      int p = BinarySearch(1);
      a[id[x]] = 0;
      Add(id[x], -1);
      id[x] = p - 1;
      a[id[x]] = x;
      Add(id[x], 1);
    } else if (opt[1] == 'B') {
      int p = BinarySearch(n);
      a[id[x]] = 0;
      Add(id[x], -1);
      id[x] = p + 1;
      a[id[x]] = x;
      Add(id[x], 1);
    } else if (opt[1] == 'I') {
      scanf("%d", &y);
      // printf("%d %d\n", x, y);
      int q = Query(id[x]);
      int bs = BinarySearch(q + y);
      int t = a[bs];
      std::swap(a[bs], a[id[x]]);
      std::swap(id[t], id[x]);
    } else if (opt[1] == 'A') {
      printf("%d\n", Query(id[x]) - 1);
    } else {
      printf("%d\n", a[BinarySearch(x)]);
    }
  }
  return 0;
}
