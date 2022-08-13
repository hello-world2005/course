#include <cstdio>
#include <algorithm>

bool Check(int a[]) {
  int n = 10;
  for (int i = 1, j = 2; i <= n; ++i, ++j) {
      int t = 0;
      for (int k = i; k <= j; ++k)
        t = t * 10 + a[k];
      if (t == 12 || t == 21 || t == 13 || t == 31 || t == 23 || t == 32)
        return false;
      if (t == 45 || t == 54)
        return false;
    }
  return true;
}

int main() {
  int a[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0}, ans = 0;
  do {
    if (Check(a))
      ++ans;
  } while (std::next_permutation(a + 1, a + 8 + 1));
  printf("%d\n", ans);
  return 0;
}
