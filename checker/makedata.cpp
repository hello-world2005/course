#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

int Random(int l, int r) {
  return rand() * rand() % (r - l + 1) + l;
}

char y[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
char x[4] = {'S', 'H', 'D', 'C'};
int a[103];
int main() {
  srand(time(0));
  puts("10");
  for (int t = 1; t <= 10; ++t) {
  for (int i = 0; i < 52; i++)
    a[i] = i;
  for (int i = 0; i < 52; ++i)
    std::swap(a[i], a[rand() % 52]);
  printf("%c%c %c%c\n", x[a[1] % 4], y[a[1] / 4], x[a[2] % 4], y[a[2] / 4]);
  printf("%c%c %c%c\n", x[a[3] % 4], y[a[3] / 4], x[a[4] % 4], y[a[4] / 4]);
  printf("%c%c %c%c %c%c\n", x[a[5] % 4], y[a[5] / 4], x[a[6] % 4], y[a[6] / 4],
         x[a[7] % 4], y[a[7] / 4]);
  }
  return 0;
}
