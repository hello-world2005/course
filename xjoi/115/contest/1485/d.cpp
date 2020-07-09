#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

const int N = 1010;
const double EPS = 1e-7;

int n;
struct Circle {
  double x, y, r;

  Circle() : x(0), y(0), r(0) {}
} c[N];

double Sqr(double x) {
  return x * x;
}

double Dis(Circle c, Circle b) {
  return sqrt(Sqr(c.x - b.x) * Sqr(c.y - b.y));
}

struct Segment {
  double l, r;

  Segment() : l(0), r(0) {}
  Segment(double _l, double _r) : l(_l), r(_r) {}
} b[N];

bool del[N];

double F(double x) {
  int cnt = 0;
  std::vector<Segment> b;
  for (int i = 1; i <= n; ++i) {
    if (fabs(c[i].x - x) < c[i].r) {
      b.push_back(Segment(c[i].y - sqrt(Sqr(c[i].r) - Sqr(c[i].x - x)),
                          c[i].y + sqrt(Sqr(c[i].r) - Sqr(c[i].x - x))));
    }
  }
  std::sort(b.begin(), b.end(), [](Segment x, Segment y) {
    return x.l == y.l ? x.r < y.r : x.l < y.l;
  });
  double ans = 0, lst = -2000;
  for (auto i : b)
    if (lst < i.r)
      ans += i.r - std::max(lst, i.l), lst = i.r;
  return ans;
}

double Simpson(double l, double r) {
  return (r - l) * (F(l) + 4 * F((l + r) / 2) + F(r)) / 6;
}

double Solve(double l, double r, double pre) {
  double mid = (l + r) / 2;
  double x = Simpson(l, mid), y = Simpson(mid, r);
  // if (x == 0 || y == 0)
  //   return Solve(l, mid, x) + Solve(mid, r, y);
  if (fabs(x + y - pre) < EPS * 15)
    return x + y + (x + y - pre) / 15;
  return Solve(l, mid, x) + Solve(mid, r, y);
}

int main() {
#ifdef DEBUG
  freopen("d.in", "r", stdin);
#endif
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lf%lf%lf", &c[i].x, &c[i].y, &c[i].r);
  double ans = 0;
  for (int i = -2000; i <= 2000; i += 100)
    ans += Solve(i, i + 100, Simpson(i, i + 100));
  printf("%.3lf\n", ans);
  return 0;
}
