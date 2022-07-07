#include <cstdlib>
#include <cstdio>

int main() {
  for (int i = 1; i <= 10; ++i) {
    char com[200];
    // sprintf(com, "time python3 poker.py < \"Texas Hold'em Poker/data/poker%d.in\" > example.out", i);
    // system(com);
    sprintf(com, "time ./poker < \"Texas Hold'em Poker/data/poker%d.in\" > example.out", i);
    system(com);
    printf("==========%d==========\n", i);
    // sprintf(com, "diff \"Problem Poker/data/poker%d.ans\" \"Problem Poker/data/poker%d.out\"", i, i);
    // system(com);
    // sprintf(com, "rm \"Problem Poker/data/poker%d.out\"", i);
    // system(com);
  }
  return 0;
}
