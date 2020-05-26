#include <cstdio>
#include <cmath>

const double PI = acos(-1);

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    printf("%.7f\n", 1.0 / tan(PI / 2 / n));
  }
  return 0;
}
