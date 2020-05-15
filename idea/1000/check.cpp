#include <cstdio>
#include <cstdlib>

int main() {
  // char s1[10], s2[100], s3[100];
  // scanf("%s%s", s2, s3);
  // char s[100];
  // sprintf(s, "cd %s", s1);
  // printf("%s\n", s);
  // system(s);
  int cnt = 0;
  while (true) {
    system("makedata > .in");
    printf("data ok\n");
    system("fyyakioi < .in > fyy.out");
    printf("fyy ak ioi\n");
    system("bruteforce < .in > brute.out");
    printf("brute\n");
    if (system("fc brute.out fyy.out")) {
      printf("Wa %d\n", ++cnt);
      break;
    }
    printf("Ac %d\n", ++cnt);
  }
  return 0;
}
