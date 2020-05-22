#include <algorithm>
#include <bitset>
#include <cstdio>

const int N = 5e3 + 10;

int n;
struct Segment {
  int x1, y1, x2, y2;

  Segment() : x1(0), y1(0), x2(0), y2(0) {}

  bool Direction() { return y1 == y2; }
} s[N], s1[N], s2[N];
int c1, c2;
std::bitset<N> b[N];

signed main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d%d", &s[i].x1, &s[i].y1, &s[i].x2, &s[i].y2);
    if (s[i].x1 > s[i].x2)
      std::swap(s[i].x1, s[i].x2);
    if (s[i].y1 > s[i].y2)
      std::swap(s[i].y1, s[i].y2);
    if (s[i].Direction())
      s1[++c1] = s[i];
    else
      s2[++c2] = s[i];
  }
  // printf("%d %d\n", c1, c2);
  long long ans = 0;
  if (c1 < c2) {
    for (int i = 1; i <= c1; ++i)
      for (int j = 1; j <= c2; ++j) {
        // printf("%d %d %d %d\n", s1[i].x1, s1[i].y1, s1[i].x2, s1[i].y2);
        // printf("%d %d %d %d\n", s2[j].x1, s2[j].y1, s2[j].x2, s2[j].y2);
        if (s1[i].x1 <= s2[j].x1 && s1[i].x2 >= s2[j].x1 &&
            s2[j].y1 <= s1[i].y1 && s2[j].y2 >= s1[i].y2)
          b[i][j] = 1;
      }
    for (int i = 1; i <= c1; ++i)
      for (int j = i + 1; j <= c1; ++j) {
        int t = (b[i] & b[j]).count();
        // printf("%d %d %d\n", i, j, t);
        ans += 1ll * t * (t - 1) / 2;
      }
  } else {
    for (int i = 1; i <= c1; ++i)
      for (int j = 1; j <= c2; ++j) {
        // printf("%d %d %d %d\n", s1[i].x1, s1[i].y1, s1[i].x2, s1[i].y2);
        // printf("%d %d %d %d\n", s2[j].x1, s2[j].y1, s2[j].x2, s2[j].y2);
        if (s1[i].x1 <= s2[j].x1 && s1[i].x2 >= s2[j].x1 &&
            s2[j].y1 <= s1[i].y1 && s2[j].y2 >= s1[i].y2)
          b[j][i] = 1;
      }
    for (int i = 1; i <= c2; ++i)
      for (int j = i + 1; j <= c2; ++j) {
        int t = (b[i] & b[j]).count();
        // printf("%d %d %d\n", i, j, t);
        ans += 1ll * t * (t - 1) / 2;
      }
  }
  printf("%lld\n", ans);
  return 0;
}
