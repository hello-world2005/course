#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    char s[10][10];
    std::vector<std::pair<int, int> > v;
    for (int i = 1; i <= 8; ++i) {
      scanf("%s", s[i] + 1);
      for (int j = 1; j <= 8; ++j)
        if (s[i][j] == 'K')
          v.push_back(std::make_pair(i, j));
    }
    if (abs(v[0].first - v[1].first) % 4 == 0 &&
        abs(v[0].second - v[1].second) % 4 == 0)
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}
