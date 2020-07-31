#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
  int cnt = 0;
  clock_t st = clock();
  clock_t ed = clock();
  while (true) {
    system("./makedata > .in");
    printf("data ok\n");
    st = clock();
    system("./a < .in > a.out");
    ed = clock();
    printf("a %.3lfs\n", 1.0 * (ed - st) / CLOCKS_PER_SEC);
    st = clock();
    system("./b < .in > b.out");
    ed = clock();
    printf("b %.3lfs\n", 1.0 * (ed - st) / CLOCKS_PER_SEC);
    if (system("diff a.out b.out")) {
      printf("Wa %d\n", ++cnt);
      break;
    }
    printf("Ac %d\n", ++cnt);
  }
  return 0;
}
