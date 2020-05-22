#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);
    if (k % 3 == 0) {
      n %= (k + 1);
      if (n % 3 == 0 && n != k)
        printf("Bob\n");
      else
        printf("Alice\n");
    } else {
      if (n % 3 == 0)
        printf("Bob\n");
      else
        printf("Alice\n");
    }
  }
  return 0;
}

// 1 2 3
// 1 2 3 4 5 6 7 8 9
// A A A B A A A B A

// 1 2 4
// 1 2 3 4 5 6 7 8 9
// A A B A A B A A B

// 1 2 5
// 1 2 3 4 5 6 7 8 9
// A A B A A B A A B
