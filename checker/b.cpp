#include <bitset>
#include <cstdio>
#include <iostream>

int main() {
  std::bitset<30000> bs;
  int n = 30000;
  int m;
  scanf("%d", &m);
  for (int i = 0, x; i < m; ++i)
    scanf("%d", &x), bs.set(x);
  bs <<= 10;
  bs >>= 15;
  bs <<= 12;
  bs >>= 124;
  bs <<= 1926;
  for (int i = 0; i < n; ++i)
    printf("%d", bs.test(i));
  // std::cout << bs << std::endl;
  return 0;
}
