#include <cstdio>
#include <map>

const int N = 5e4 + 10;
const int BASE = 114514;

int n, d;
char s[N][10];
int val[10];

int main() {
  scanf("%d%d", &n, &d);
  for (int i = 1; i <= n; ++i)
    scanf("%s", s[i]);
  int ans = 0;
  for (int mask = 0; mask < (1 << 4); ++mask) {
    int cnt = 0, res = 0;
    for (int i = 0; i < 4; ++i)
      if (mask >> i & 1)
        ++cnt;
    std::map<int, int> m;
    for (int i = 1; i <= n; ++i) {
      int has = 0;
      for (int j = 0; j < 4; ++j) {
        if (mask >> j & 1)
          has = has * BASE + s[i][j];
        else
          has = has * BASE + 1;
      }
      res += m[has];
      ++m[has];
    }
    val[cnt] += res;
    // printf("%d", cnt);
  }
  val[3] -= 4 * val[4];
  val[2] -= 6 * val[4] + 3 * val[3];
  val[1] -= 2 * val[2] + 3 * val[3] + 4 * val[4];
  val[0] -= val[1] + val[2] + val[3] + val[4];
  printf("%d\n", val[4 - d]);
  return 0;
}
