#include <cmath>
#include <cstdio>

const double PI = acos(-1);

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    printf("%.7f\n", 0.5 / sin(PI / n / 4));
  }
  return 0;
}
