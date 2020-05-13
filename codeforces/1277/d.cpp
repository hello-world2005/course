#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>

const int N = 2e5 + 10;
const int M = 4e6 + 10;

std::string s[N];
std::set<std::string> s01, s10;

int main() {
  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    bool vis[2] = {false, false};
    s01.clear(), s10.clear();
    for (int i = 1; i <= n; ++i) {
      std::cin >> s[i];
      if (s[i].front() == '0' && s[i].back() == '1')
        s01.insert(s[i]);
      if (s[i].front() == '1' && s[i].back() == '0')
        s10.insert(s[i]);
      vis[s[i].front() - '0'] = vis[s[i].back() - '0'] = true;
    }
    if (s01.size() == 0 && s10.size() == 0 && vis[0] && vis[1]) {
      printf("-1\n");
      continue;
    }
    std::vector<int> rev;
    if (s01.size() > s10.size() + 1) {
      for (int i = 1; i <= n; ++i)
        if (s[i].front() == '0' && s[i].back() == '1') {
          std::string ss(s[i]);
          std::reverse(ss.begin(), ss.end());
          if (!s10.count(ss))
            rev.push_back(i);
        }
    } else if (s10.size() > s01.size() + 1) {
      for (int i = 1; i <= n; ++i)
        if (s[i].front() == '1' && s[i].back() == '0') {
          std::string ss(s[i]);
          std::reverse(ss.begin(), ss.end());
          if (!s01.count(ss))
            rev.push_back(i);
        }
    }
    int ans = std::max(0, (int(std::max(s01.size(), s10.size())) - int(std::min(s01.size(), s10.size()))) / 2);
    printf("%d\n", ans);
    for (int i = 0; i < ans; ++i)
      printf("%d ", rev[i]);
    printf("\n");
  }
  return 0;
}
