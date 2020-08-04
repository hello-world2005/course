#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define Time std::chrono::system_clock::now()

int main() {
  int cnt = 0;
  auto st = Time;
  auto ed = Time;
  auto cost = std::chrono::duration_cast<std::chrono::microseconds>(ed - st);
  while (true) {
    system("./makedata > .in");
    printf("data ok\n");
    st = Time;
    system("./a < .in > a.out");
    ed = Time;
    cost = std::chrono::duration_cast<std::chrono::microseconds>(ed - st);
    printf("a %.3lfs\n", double(cost.count()) *
                             std::chrono::microseconds::period::num /
                             std::chrono::microseconds::period::den);
    st = Time;
    system("./b < .in > b.out");
    ed = Time;
    cost = std::chrono::duration_cast<std::chrono::microseconds>(ed - st);
    printf("a %.3lfs\n", double(cost.count()) *
                             std::chrono::microseconds::period::num /
                             std::chrono::microseconds::period::den);
    if (system("diff a.out b.out")) {
      printf("Wa %d\n", ++cnt);
      break;
    }
    printf("Ac %d\n", ++cnt);
  }
  return 0;
}
