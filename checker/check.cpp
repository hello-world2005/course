#include <cstdio>
#include <cstdlib>

int main() {
  int cnt = 0;
  while (true) {
    // system("makedata > .in");
    // printf("data ok\n");
    system("a < .in > a.out");
    printf("a\n");
    system("b < .in > b.out");
    printf("b\n");
    if (system("fc b.out a.out")) {
      printf("Wa %d\n", ++cnt);
      break;
    }
    printf("Ac %d\n", ++cnt);
  }
  return 0;
}
