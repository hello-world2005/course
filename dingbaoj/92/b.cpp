// 题目怎么这么毒瘤啊qwq

#include <algorithm>
#include <cstdio>
#include <cstring>

typedef unsigned long long ull;

const int N = 3e4 + 10;
const int M = 470;

struct Bitset {
  ull a[M];

  Bitset() { memset(a, 0, sizeof(a)); }

  void Reset() { *this = Bitset(); }
  void Set(int x) { a[x >> 6] |= (1 << (x & 0x3f)); }
  bool At(int x) { return a[x >> 6] >> (x & 0x3f) & 1; }

  Bitset operator~() {
    Bitset res;
    for (int i = 0; i < M; ++i)
      res.a[i] = ~a[i];
    return res;
  }
  Bitset operator&(const Bitset& rhs) {
    Bitset res;
    for (int i = 0; i < M; ++i)
      res.a[i] = a[i] & rhs.a[i];
    return res;
  }
  Bitset operator|(const Bitset& rhs) {
    Bitset res;
    for (int i = 0; i < M; ++i)
      res.a[i] = a[i] | rhs.a[i];
    return res;
  }
  Bitset operator^(const Bitset& rhs) {
    Bitset res;
    for (int i = 0; i < M; ++i)
      res.a[i] = a[i] ^ rhs.a[i];
    return res;
  }
  Bitset operator<<(const int k) {
    Bitset res;
    int x = k >> 6, y = k & 0x3f;
    ull lst = 0;
    for (int i = 0; i < M; ++i) {
      res.a[i + x] = (lst | a[i] << y);
      if (y)
        lst = (a[i] >> (0x40 - y));
    }
    return res;
  }
  Bitset operator>>(const int k) {
    Bitset res;
    int x = k >> 6, y = k & 0x3f;
    ull lst = 0;
    for (int i = 0; i < M; ++i) {
      res.a[i - x] = (lst | a[i] >> y);
      if (y)
        lst = (a[i] << (0x40 - y));
    }
    return res;
  }
} bsa[N], bsb[N], bsc[N], bsd[N];

struct Rectangle {
  int x1, y1, x2, y2;
  int idx;
} a[N];

bool Cmp1(const int& lhs, const int& rhs) {
  return a[lhs].x1 < a[rhs].x1;
}
bool Cmp2(const int& lhs, const int& rhs) {
  return a[lhs].y1 < a[rhs].y1;
}
bool Cmp3(const int& lhs, const int& rhs) {
  return a[lhs].x2 > a[rhs].x2;
}
bool Cmp4(const int& lhs, const int& rhs) {
  return a[lhs].y2 > a[rhs].y2;
}
bool Cmp5(const int& lhs, const int& rhs) {
  return a[lhs].y1 > a[rhs].y1;
}

int Query(int x, int y) {}

int s[M][M], f[N][M];
int pa[N], pb[N], pc[N], pd[N], pe[N];

int main() {
  int n, q, lastans = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d%d%d%d", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2), a[i].idx = i;
  for (int i = 0; i < n; ++i)
    pa[i] = pb[i] = pc[i] = pd[i] = pe[i] = i;
  std::sort(pa, pa + n, Cmp1);
  std::sort(pb, pb + n, Cmp2);
  std::sort(pc, pc + n, Cmp3);
  std::sort(pd, pd + n, Cmp4);
  std::sort(pe, pe + n, Cmp5);
  for (int i = 0; i <= (n >> 6); ++i) {
    if (i)
      bsa[i] = bsa[i - 1];
    int x = i << 6, y = std::min(x + 0x40, n);
    while (x < y)
      bsa[i].Set(pa[y++]);
  }
  for (int i = 0; i <= (n >> 6); ++i) {
    if (i)
      bsb[i] = bsb[i - 1];
    int x = i << 6, y = std::min(x + 0x40, n);
    while (x < y)
      bsb[i].Set(pb[y++]);
  }
  for (int i = 0; i <= (n >> 6); ++i) {
    if (i)
      bsc[i] = bsc[i - 1];
    int x = i << 6, y = std::min(x + 0x40, n);
    while (x < y)
      bsc[i].Set(pc[y++]);
  }
  for (int i = 0, j = 0; i < n; ++i) {
    int x = pd[i], y = pe[i];
    Rectangle now = a[x];
    while (j < n && a[pd[j]].y2 > now.y1)
      ++j;
  }
  scanf("%d", &q);
  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    x1 ^= lastans, y1 ^= lastans, x2 ^= lastans, y2 = lastans;
    --x1, --y1, --x2, --y2;
    printf("%d\n", lastans = (Query(x1, y1) - Query(x1, y2 - 1) -
                              Query(x2 - 1, y1) + Query(x2 - 1, y2 - 1)));
  }
  return 0;
}
