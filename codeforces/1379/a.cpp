#include <algorithm>
#include <cstdio>
#include <vector>

const int N = 60;

const char str[] = " abacaba";

int n, m;

bool Check(char* t) {
  int cnt = 0;
  for (int i = 0; i <= n - 7; ++i) {
    bool flag = true;
    for (int j = 1; j <= 7; ++j)
      if (t[i + j - 1] != str[j])
        flag = false;
    if (flag)
      ++cnt;
  }
  return cnt == 1;
}

char s[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s);
    int cnt = 0;
    for (int i = 0; i <= n - 7; ++i) {
      bool flag = true;
      for (int j = 1; j <= 7; ++j)
        if (s[i + j - 1] != str[j])
          flag = false;
      if (flag)
        ++cnt;
    }
    if (cnt == 1) {
      for (int i = 0; i < n; ++i)
        if (s[i] == '?')
          s[i] = 'z';
      printf("Yes\n%s\n", s);
      continue;
    }
    if (cnt >= 2) {
      printf("No\n");
      continue;
    }
    bool ans = false;
    for (int i = 0; i <= n - 7; ++i) {
      bool flag = true;
      for (int j = 1; j <= 7; ++j)
        if (s[i + j - 1] != str[j] && s[i + j - 1] != '?')
          flag = false;
      if (flag) {
        std::vector<int> vec;
        for (int j = 1; j <= 7; ++j)
          if (s[i + j - 1] == '?')
            s[i + j - 1] = str[j], vec.push_back(i + j - 1);
        if (Check(s)) {
          ans = true;
          break;
        } else {
          for (auto j : vec)
            s[j] = '?';
        }
      }
    }
    if (!ans) {
      printf("No\n");
    } else {
      for (int i = 0; i < n; ++i)
        if (s[i] == '?')
          s[i] = 'z';
      printf("Yes\n%s\n", s);
    }
  }
  return 0;
}
