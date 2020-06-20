#include <cstdio>

void Solve1(int n, char s1[], char s2[], char s3[]) {
  s1[0] = s2[0] = s3[0] = '0';
  s1[8] = s2[8] = s3[8] = '\0';
  for (int i = 6; i >= 0; --i)
    if ((1 << i) <= n)
      n -= (1 << i), s1[7 - i] = '1';
    else
      s1[7 - i] = '0';
  for (int i = 1; i <= 7; ++i)
    s2[i] = (s1[i] == '0' ? '1' : '0');
  for (int i = 1; i <= 7; ++i)
    s3[i] = s1[i];
}

void Solve2(int n, char s1[], char s2[], char s3[]) {
  s1[0] = s2[0] = s3[0] = '1';
  s1[8] = s2[8] = s3[8] = '\0';
  for (int i = 6; i >= 0; --i)
    if ((1 << i) <= n)
      n -= (1 << i), s1[7 - i] = '1';
    else
      s1[7 - i] = '0';
  for (int i = 1; i <= 7; ++i)
    s2[i] = (s1[i] == '0' ? '1' : '0');
  int p = 1;
  for (int i = 7; i >= 1; --i) {
    s3[i] = s2[i] + p;
    p = 0;
    if (s3[i] == '2')
      s3[i] = '0', p = 1;
  }
  if (p)
    s3[0] = '0';
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    char opt = getchar();
    while (opt != '+' && opt != '-')
      opt = getchar();
    int n;
    scanf("%d", &n);
    if (n == 0 && opt == '+') {
      printf("00000000\n01111111\n00000000\n");
      continue;
    }
    if (n == 0 && opt == '-') {
      printf("10000000\n11111111\n00000000\n");
      continue;
    }
    char s1[20], s2[20], s3[20];
    if (opt == '+')
      Solve1(n, s1, s2, s3);
    else
      Solve2(n, s1, s2, s3);
    printf("%s\n%s\n%s\n", s1, s2, s3);
  }
  return 0;
}
