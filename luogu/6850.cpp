#include <cstdio>

int main() {
  int sum = 50;
  for (int i = 1, x; i <= 7; ++i)
    scanf("%d", &x), sum += x;
  int x = 0;
  scanf("%d", &x);
  if (x)
    sum += 5;
  scanf("%d", &x);
  if (sum >= x)
    printf("AKIOI");
  else
    printf("AFO");
  return 0;
}
