#include <cstdio>
#include <cstring>

const int N = 1e5 + 10;

char s[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    bool flag = true;
    for (int i = 1; i <= n; ++i) {
      if (s[i] != '?' && s[i] == s[i - 1]) {
        printf("-1\n");
        flag = false;
        break;
      }
    }
    if (flag) {
      for (int i = 1; i <= n; ++i) {
        if (s[i] != '?') {
          s[i] = s[i];
          continue;
        }
        bool vis[10] = {false};
        if (i > 1)
          vis[s[i - 1] - 'a'] = true;
        if (i < n && s[i + 1] != '?')
          vis[s[i + 1] - 'a'] = true;
        for (int j = 0; j <= 2; ++j)
          if (!vis[j]) {
            s[i] = 'a' + j;
            break;
          }
      }
      printf("%s\n", s + 1);
    }
  }
  return 0;
}
