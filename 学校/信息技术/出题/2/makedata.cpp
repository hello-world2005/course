#include <cstdlib>
#include <cstdio>
#include <ctime>

void Gen(char *s) {
  int n = rand() % 100;
  for (int i = 0; i < n; ++i) {
    int r = rand() % 62;
    if (r < 10)
      s[i] = char(r + '0');
    else if (r < 36)
      s[i] = char(r - 10 + 'A');
    else
      s[i] = char(r - 36 + 'a');
  }
  s[n] = '\0';
}

int main() {
  srand(time(NULL));
  for (int i = 3; i <= 3; ++i) {
    char arg[110];
    Gen(arg);
    printf("%s\n", arg);
    char com[200];
    sprintf(com, "./gen %s > \"Problem Poker/data/poker%d.in\"", arg, i);
    system(com);
    sprintf(com, "./poker < \"Problem Poker/data/poker%d.in\" > \"Problem Poker/data/poker%d.ans\"", i, i);
    system(com);
  }
  return 0;
}
