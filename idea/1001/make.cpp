#include <cstdio>
#include <cstdlib>
#include <windows.h>

int main() {
  for (int i = 1; i <= 10; ++i) {
    char s[100];
    sprintf(s, "makedata > %d.in", i);
    system(s);
    sprintf(s, "std < %d.in > %d.out", i, i);
    system(s);
    Sleep(1000);
  }
  return 0;
}
