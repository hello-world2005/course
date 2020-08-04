#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
//#define getchar()
//(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++) char
// buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
  int x = 0, f = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (isdigit(ch))
    x = x * 10 + (ch ^ 48), ch = getchar();
  return x * f;
}
const int N = 100010;
int n, m, a[N], sze;
int bel[N], ans[N], cnt[N];
struct QUE {
  int opt, l, r, x, id;
} q[N];
inline bool cmp(const QUE& a, const QUE& b) {
  return bel[a.l] != bel[b.l] ? a.l < b.l
                              : bel[a.l] & 1 ? a.r < b.r : a.r > b.r;
}
template <int N>
struct Bitset {
  const static int M = (N & 0x3f) ? ((N >> 6) + 1) : (N >> 6);
  unsigned long long a[M];

  Bitset() { memset(a, 0, sizeof(a)); }

  void Reset() { *this = Bitset(); }
  void Set(int x, bool k = true) {
    if (k)
      a[x >> 6] |= (1ull << (x & 0x3f));
    else
      a[x >> 6] &= ~(1ull << (x & 0x3f));
  }
  bool At(int x) { return a[x >> 6] >> (x & 0x3f) & 1; }
  int Count() {
    int res = 0;
    for (int i = 0; i < M; ++i)
      res += __builtin_popcountll(i);
    return res;
  }
  std::vector<int> Every() {
    std::vector<int> res;
    for (int i = 0; i < M; ++i)
      for (ull j = a[i]; j; j -= (1 << __builtin_ctzll(j)))
        res.push_back((i << 6) | __builtin_ctzll(j));
    return res;
  }
  bool All() {
    bool res = true;
    for (int i = 0; i < M; ++i)
      if (__builtin_popcountll(i) != 0x3f)
        return false;
    return true;
  }
  bool any() {
    bool res = false;
    for (int i = 0; i < M; ++i)
      if (__builtin_popcountll(i))
        return true;
    return false;
  }
  bool None() {
    for (int i = 0; i < M; ++i)
      if (__builtin_popcountll(i))
        return false;
    return true;
  }
  void Flip(int x) { a[x >> 6] ^= (1 << (x & 0x3f)); }

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
    for (int i = 0; i < M - x; ++i) {
      res.a[i + x] = (lst | (a[i] << y));
      if (y)
        lst = (a[i] >> (0x40 - y));
    }
    return res;
  }
  Bitset operator>>(const int k) {
    Bitset res;
    int x = k >> 6, y = k & 0x3f;
    ull lst = 0;
    for (int i = M - 1; i >= x; --i) {
      res.a[i - x] = (lst | (a[i] >> y));
      if (y)
        lst = (a[i] << (0x40 - y));
    }
    return res;
  }
  // void Set(int x,ull d) { a[x >> 6] |= (d << (x & 0x3f)); }
  Bitset operator&=(const Bitset& rhs) { return *this = *this & rhs; }
  Bitset operator|=(const Bitset& rhs) { return *this = *this | rhs; }
  Bitset operator^=(const Bitset& rhs) { return *this = *this ^ rhs; }
  Bitset operator<<=(const int k) { return *this = *this << k; }
  Bitset operator>>=(const int k) { return *this = *this >> k; }
};

Bitset<N> A, B, C;
void add(int x) {
  ++cnt[a[x]];
  if (cnt[a[x]])
    A.Set(a[x], 1), B.Set(N - a[x], 1);
  else
    A.Set(a[x], 0), B.Set(N - a[x], 0);
}
void pop(int x) {
  --cnt[a[x]];
  if (cnt[a[x]])
    A.Set(a[x], 1), B.Set(N - a[x], 1);
  else
    A.Set(a[x], 0), B.Set(N - a[x], 0);
}
int Q1(int x) {
  C = A, C <<= x, C &= A;
  return C.any();
}
int Q2(int x) {
  C = B, C >>= (N - x), C &= A;
  return C.any();
}
int Q3(int x) {
  for (int i = 1; i * i <= x; ++i) {
    if (x % i)
      continue;
    if (A.At(i) && A.At(x / i))
      return 1;
  }
  return 0;
}
signed main() {
  n = rd(), m = rd(), sze = sqrt(n);
  for (int i = 1; i <= n; ++i)
    a[i] = rd(), bel[i] = (i - 1) / sze + 1;
  for (int i = 1; i <= m; ++i)
    q[i].opt = rd(), q[i].l = rd(), q[i].r = rd(), q[i].x = rd(), q[i].id = i;
  sort(q + 1, q + m + 1, cmp);
  int l = 1, r = 0;
  for (int i = 1; i <= m; ++i) {
    while (l < q[i].l)
      pop(l++);
    while (l > q[i].l)
      add(--l);
    while (r < q[i].r)
      add(++r);
    while (r > q[i].r)
      pop(r--);
    if (q[i].opt == 1)
      ans[q[i].id] = Q1(q[i].x);
    else if (q[i].opt == 2)
      ans[q[i].id] = Q2(q[i].x);
    else if (q[i].opt == 3)
      ans[q[i].id] = Q3(q[i].x);
  }
  for (int i = 1; i <= m; ++i)
    puts(ans[i] ? "hana" : "bi");
  return 0;
}