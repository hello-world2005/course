// test

#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int tree[500010], rank[500010], n;
long long ans;
struct point {
  int num, val;
} a[500010];
inline bool cmp(point q, point w) {
  if (q.val == w.val)
    return q.num < w.num;
  return q.val < w.val;
}
inline void insert(int p, int d) {
  for (; p <= n; p += p & -p)
    tree[p] += d;
}
inline int query(int p) {
  int sum = 0;
  for (; p; p -= p & -p)
    sum += tree[p];
  return sum;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d%d", &a[i].val, &a[i].num);
  sort(a + 1, a + 1 + n, cmp);
  for (int i = 1; i <= n; i++)
    rank[a[i].num] = i;
  for (int i = 1; i <= n; i++) {
    insert(rank[i], 1);
    ans += i - query(rank[i]);
  }
  printf("%lld", ans);
  return 0;
}