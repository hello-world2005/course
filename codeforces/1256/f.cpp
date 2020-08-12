#include <cstdio>

const int N = 2e5 + 10;

char s[N], t[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d%s%s", &n, s + 1, t + 1);
    int a[30] = {0}, b[30] = {0};
    for (int i = 1; i <= n; ++i)
      ++a[s[i] - 'a'], ++b[t[i] - 'a'];
    bool flag = true;
    for (int i = 0; i < 26; ++i)
      if (a[i] != b[i])
        flag = false;
    if (!flag) {
      printf("NO\n");
      continue;
    }
    flag = false;
    for (int i = 0; i < 26; ++i)
      if (a[i] > 1)
        flag = true;
    if (flag) {
      printf("YES\n");
      continue;
    }
    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j < i; ++j) {
        if (s[i] < s[j])
          ++cnt1;
        if (t[i] < t[j])
          ++cnt2;
      }
    printf("%s\n", (cnt1 % 2 == cnt2 % 2) ? "YES" : "NO");
  }
  return 0;
}
