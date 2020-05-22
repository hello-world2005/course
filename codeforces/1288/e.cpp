#include <algorithm>
#include <cstdio>

const int N = 3e5 + 10;

int n, m;
int a[N];
int p[N], t[N << 1];
int minn[N], maxn[N];

#define LowBit(x) (x & -x)

void Add(int a, int b) {
  for (; a <= n + m; a += LowBit(a))
    t[a] += b;
}

int Ask(int a) {
  int res = 0;
  for (; a; a -= LowBit(a))
    res += t[a];
  return res;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    Add(i + m, 1), p[i] = i + m, minn[i] = i, maxn[i] = i;
  int tp = m;
  // for (int i = 1; i <= n; ++i)
  //   printf("%d\n", Ask(i + m));
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &a[i]);
    minn[a[i]] = 1;
    maxn[a[i]] = std::max(maxn[a[i]], Ask(p[a[i]]));
    Add(p[a[i]], -1);
    // printf("%d\n", i);
    p[a[i]] = tp--;
    Add(p[a[i]], 1);
  }
  // for (int i = 1; i <= n; ++i)
  //   printf("%d\n", p[i]);
  // printf("%d\n", Ask(6));
  for (int i = 1; i <= n; ++i)
    maxn[i] = std::max(maxn[i], Ask(p[i]));
  for (int i = 1; i <= n; ++i)
    printf("%d %d\n", minn[i], maxn[i]);
  return 0;
}
