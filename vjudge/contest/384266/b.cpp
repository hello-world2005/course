#include <cstdio>

int Gcd(int a, int b) {
  if (b == 0)
    return a;
  return Gcd(b, a % b);
}

int Lcm(int a, int b) {
  return a * b / Gcd(a, b);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= i; ++j)
        for (int k = 1; k <= i; ++k)
          ans += Lcm(Gcd(i, j), Gcd(i, k));
    printf("%d\n", ans);
  }
  return 0;
}
