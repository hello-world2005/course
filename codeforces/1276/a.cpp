#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1.5e6 + 10;

char s[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, ans = 0;
    scanf("%s", s + 1);
    n = strlen(s + 1);
    std::vector<int> sol;
    for (int i = 1; i <= n; ++i) {
      if (s[i] == 't' && s[i + 1] == 'w' && s[i + 2] == 'o' && s[i + 3] == 'n' && s[i + 4] == 'e')
        ++ans, sol.push_back(i + 2), i = i + 4;
      else if (s[i] == 'o' && s[i + 1] == 'n' && s[i + 2] == 'e')
        ++ans, sol.push_back(i + 1), i = i + 2;
      else if (s[i] == 't' && s[i + 1] == 'w' && s[i + 2] == 'o')
        ++ans, sol.push_back(i + 1), i = i + 2;
    }
    printf("%d\n", ans);
    for (int i : sol)
      printf("%d ", i);
    printf("\n");
  }
  return 0;
}
