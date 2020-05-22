#include <cstdio>
#include <string>
#include <iostream>

int s1[100], s2[100], s3[100];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    std::string s, t, p;
    std::cin >> s >> t >> p;
    for (int i = 0; i < 26; ++i)
      s1[i] = s2[i] = s3[i] = 0;
    // bool ans = true;
    // s += '*';
    // for (int i = 0; i < (int)t.length(); ++i) {
    //   int j = i;
    //   while (s[0] != t[j]) {
    //     auto it = p.find(t[j]);
    //     std::cout << j << it << t[j] << std::endl;
    //     if(it > p.length()) {
    //       ans = false;
    //       break;
    //     }
    //     p.erase(it, it + 1);
    //     ++j;
    //   }
    //   i = j;
    //   s.erase(0, 1);
    //   if (!ans)
    //     break;
    // }
    // printf("%s\n", ans ? "YES" : "NO");
    if (s.length() > t.length()) {
      printf("NO\n");
    } else {
      for (int i = 0; i < (int)s.length(); ++i)
        ++s1[s[i] - 'a'];
      for (int i = 0; i < (int)t.length(); ++i)
        ++s2[t[i] - 'a'];
      for (int i = 0; i < (int)p.length(); ++i)
        ++s3[p[i] - 'a'];
      bool ans = true;
      for (int i = 0; i < 26; ++i)
        if (s1[i] + s3[i] < s2[i]) {
          ans = false;
          break;
        }
      if (!ans) {
        printf("NO\n");
        continue;
      }
      int cnt = 0;
      for (int i = 0; i < (int)t.length(); ++i) {
        if (s[cnt] == t[i])
          ++cnt;
        if (cnt == s.length()) {
          printf("YES\n");
          break;
        }
      }
      if (cnt < s.length())
        printf("NO\n");
    }
  }
  return 0;
}
