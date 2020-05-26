#include <cstdio>

const int N = 2e4 + 10;

char opt[10];

#define LowBit(x) (x & -x)

int t[N];

void Add(int a, int b) {
  for (; a < N; a += LowBit(a))
    t[a] ^= b;
}

int Ask(int a) {
  int res = 0;
  for (; a; a -= LowBit(a))
    res ^= t[a];
  return res;
}

int main() {
  while (scanf("%s", opt + 1) == 1)
    if (opt[1] == 'A' || opt[1] == 'R') {
      int x;
      scanf("%d", &x);
      Add(x, x);
    } else {
      int x, y;
      scanf("%s", opt + 1);
      scanf("%d", &x);
      scanf("%s", opt + 1);
      scanf("%d", &y);
      if (x > y)
        printf("0\n");
      else
        printf("%d\n", Ask(y) ^ Ask(x - 1));
    }
  return 0;
}
