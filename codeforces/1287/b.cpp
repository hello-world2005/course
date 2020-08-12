#include <cstdio>
#include <iostream>
#include <map>
#include <string>

const int N = 1510;
const int K = 40;

std::string s[N];
std::map<std::string, int> vis;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    std::cin >> s[i];
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      std::string t;
      for (int k = 0; k < m; ++k)
        if (s[i][k] == s[j][k]) {
          t += s[i][k];
        } else {
          if (s[i][k] != 'S' && s[j][k] != 'S')
            t += 'S';
          if (s[i][k] != 'E' && s[j][k] != 'E')
            t += 'E';
          if (s[i][k] != 'T' && s[j][k] != 'T')
            t += 'T';
        }
      ans += vis[t];
    }
    ++vis[s[i]];  
  }
  printf("%d\n", ans);
  return 0;
}
