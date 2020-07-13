#include <cstdio>

const int MOD = 1e9 + 7;

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    printf("%d\n", int(1ll * n * (n - 1) % MOD * (n - 2) % MOD));
  }
  return 0;
}
