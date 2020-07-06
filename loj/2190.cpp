#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <climits>

const int N = 1e5 + 5;
const double eps = 1e-6, PI = acos(-1.0);

std::mt19937 wzcakioi(time(NULL));

double reps() {
  return (1.0 * wzcakioi() / INT_MAX - 0.5) * eps;
}
int Sign(double x) {
  return x < -eps ? -1 : x > eps;
}

struct Point {
  double x, y;

  Point() {}
  Point(double _x, double _y) : x(_x), y(_y) {}

  Point operator+(const Point& b) const { return Point(x + b.x, y + b.y); }
  Point operator-(const Point& b) const { return Point(x - b.x, y - b.y); }
  double operator*(const Point& b) const { return x * b.y - y * b.x; }
  Point operator*(const double& b) const { return Point(x * b, y * b); }
  double operator^(const Point& b) const { return x * b.x + y * b.y; }

  double len2() { return x * x + y * y; }
  Point rot(double s, double c) { return Point(x * c - y * s, x * s + y * c); }
  Point rot90() { return Point(-y, x); }
  void shake() { x += reps(), y += reps(); }
} p[N], o;

struct Line {
  Point p, v;
  Line() {}
  Line(Point _p, Point _v) : p(_p), v(_v) {}
  friend Point cross(const Line& a, const Line& b) {
    return a.p + a.v * (b.v * (b.p - a.p) / (b.v * a.v));
  }
};

Point circle(const Point& a, const Point& b, const Point& c) {
  return cross(Line((a + b) * 0.5, (b - a).rot90()),
               Line((a + c) * 0.5, (c - a).rot90()));
}

int n;
double s, c, a, b;
double Solve() {
  double r = 0;
  o = Point(0, 0);
  for (int i = 1; i <= n; ++i)
    std::swap(p[i], p[wzcakioi() % n + 1]);
  for (int i = 1; i <= n; ++i)
    if (Sign((p[i] - o).len2() - r) > 0) {
      o = p[i], r = 0;
      for (int j = 1; j <= i - 1; ++j)
        if (Sign((p[j] - o).len2() - r) > 0) {
          o = (p[i] + p[j]) * 0.5, r = (p[j] - o).len2();
          for (int k = 1; k <= j - 1; ++k)
            if (Sign((p[k] - o).len2() - r) > 0)
              o = circle(p[i], p[j], p[k]), r = (p[k] - o).len2();
        }
    }
  return sqrt(r);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lf%lf", &p[i].x, &p[i].y);
    p[i].shake();
  }
  scanf("%lf%lf", &b, &a);
  b = (360 - b) / 180.0 * PI, s = sin(b), c = cos(b),
  a = 1.0 / a;
  for (int i = 1; i <= n; ++i)
    p[i] = p[i].rot(s, c);
  for (int i = 1; i <= n; ++i)
    p[i].x = p[i].x * a;
  printf("%.3lf\n", Solve());
  return 0;
}
