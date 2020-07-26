#include <cstdio>
#include <cstring>
#include <vector>

template<int N>
struct Bitset {
  int M = (N & 0x3f) ? ((N >> 6) + 1) : (N >> 6);
  unsigned long long a[M];

  Bitset() { memset(a, 0, sizeof(a)); }

  void Reset() { *this = Bitset(); }
  void Set(int x) { a[x >> 6] |= (1ull << (x & 0x3f)); }
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
      for (int j = a[i]; j; j -= (1 << __builtin_ctzll(j)))
        res.push_back((i << 6) | j);
    return res;
  }

  bool &operator[](const int k) { return a[x >> 6] >> (x & 0x3f) & 1; }
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
    for (int i = M - 1; i >= x; --i) {
      res.a[i - x] = (lst | a[i] >> y);
      if (y)
        lst = (a[i] << (0x40 - y));
    }
    return res;
  }
  Bitset operator&=(const Bitset& rhs) { return *this = *this & rhs; }
  Bitset operator|=(const Bitset& rhs) { return *this = *this | rhs; }
  Bitset operator^=(const Bitset& rhs) { return *this = *this ^ rhs; }
  Bitset operator<<=(const int k) { return *this = *this << k; }
  Bitset operator>>=(const int k) { return *this = *this >> k; }
};
