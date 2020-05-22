#include <algorithm>
#include <cstdio>

const int N = 2010;

int n;
struct Point {
  double x, y;
  int idx;
  bool flag;

  Point() : flag(true) {}

  bool operator<(const Point& rhs) const {
    return x != rhs.x ? x < rhs.x : y < rhs.y;
  }
} p[N];
char s[N];

double Cross(double x1, double x2, double y1, double y2) {
  return x1 * y2 - x2 * y1;
}

double Compare(Point p1, Point p2, Point p3) {
  return Cross(p2.x - p1.x, p2.y - p1.y, p3.x - p1.x, p3.y - p1.y);
}

int ans[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lf%lf", &p[i].x, &p[i].y), p[i].idx = i;
  std::sort(p + 1, p + n + 1);
  scanf("%s", s + 1);
  int t = 1, la = 1;
  ans[1] = p[1].idx;
  p[1].flag = false;
  for (int i = 1; i <= n - 2; ++i) {
    if (s[i] == 'L')
      for (int j = 1; j <= n; ++j) {
        if (!p[j].flag)
          continue;
        if (!p[t].flag || Compare(p[la], p[j], p[t]) > 0)
          t = j;
      }
    else
      for (int j = 1; j <= n; ++j) {
        if (!p[j].flag)
          continue;
        if (!p[t].flag || Compare(p[la], p[j], p[t]) < 0)
          t = j;
      }
    ans[i + 1] = p[t].idx;
    p[t].flag = false;
    la = t;
  }
  for (int i = 1; i <= n; ++i)
    if (p[i].flag) {
      ans[n] = p[i].idx;
      break;
    }
  for (int i = 1; i <= n; ++i)
    printf("%d ", ans[i]);
  return 0;
}
