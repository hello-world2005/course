template <int N>
class Bitset {
 public:
  long long a[N / 64 + 1];

  Bitset operator<<(const int k) {}
  Bitset operator>>(const int k) {}
  Bitset operator&(const Bitset& rhs) {}
  Bitset operator|(const Bitset& rhs) {}

  bool At(int k) { return a[GetBlock(k)] >> GetId(k) & 1; }
  void Set(int k) { a[GetBlock(k)] |= (GetId(k)); }
  void Reset() { memset(a, 0, sizeof(a)); }

 private:
  int GetBlock(int k) { return k >> 6; }
  int GetId(int k) { return k & 63; }
};