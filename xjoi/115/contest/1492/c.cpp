#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <random>
#include <vector>

const int N = 210;
const double EPS = 1e-7;

std::mt19937 rnd(time(NULL));

struct Vector {
  double x, y, z;

  Vector() : x(0), y(0), z(0) {}
  Vector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

  Vector operator+(const Vector& rhs) const {
    return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
  }
  Vector operator-(const Vector& rhs) const {
    return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
  }
  Vector operator*(const double& rhs) const {
    return Vector(x * rhs, y * rhs, z * rhs);
  }
  Vector operator*(const Vector& rhs) {
    return Vector(y * rhs.z - rhs.y * z, z * rhs.x - rhs.z * x,
                  x * rhs.y - rhs.x * y);
  }
  // Vector operator^(const Vector& rhs) const {
  //   return Vector(x * rhs.x, y * rhs.y, z * rhs.z);
  // }
  double operator^(const Vector& rhs) const {  // 懒 就这样写好了
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }

  void Noise(double& x) { x += (rnd() % 1000000 + 500000) / 1000000 * EPS; }
  void Noise() { Noise(x), Noise(y), Noise(z); }

  double Length() { return sqrt(x * x + y * y + z * z); }
};

typedef Vector Point;

double V(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
  // printf("%lf %lf %lf\n", p1.x, p1.y, p1.z);
  // printf("%lf %lf %lf\n", p2.x, p2.y, p2.z);
  // printf("%lf %lf %lf\n", p3.x, p3.y, p3.z);
  // printf("%lf %lf %lf\n", p4.x, p4.y, p4.z);
  // printf("%lf\n", (p2 - p1) * (p3 - p1) ^ (p4 - p1));
  return fabs((p2 - p1) * (p3 - p1) ^ (p4 - p1));
}

int n;
Point p[N], pp[N];

struct Face {
  int v[3];

  Face() { v[0] = v[1] = v[2] = 0; }
  Face(int _x, int _y, int _z) { v[0] = _x, v[1] = _y, v[2] = _z; }

  Vector Normal() { return (p[v[1]] - p[v[0]]) * (p[v[2]] - p[v[0]]); }

  bool InSight(int x) { return ((p[x] - p[v[0]]) ^ Normal()) > 0; }
};

std::vector<Face> cur;
bool vis[N][N];

double Solve() {
  // for (int i = 1; i <= n; ++i)
  //   std::swap(p[i], p[rnd() % n + 1]);
  cur.push_back(Face(1, 2, 3));
  cur.push_back(Face(3, 2, 1));
  for (int i = 4; i <= n; ++i) {
    std::vector<Face> tmp;
    memset(vis, false, sizeof(vis));
    for (int j = 0; j < cur.size(); ++j) {
      Face f = cur[j];
      if (!f.InSight(i))
        tmp.push_back(f);
      else
        for (int k = 0; k < 3; ++k)
          vis[f.v[k]][f.v[(k + 1) % 3]] = 1;
    }
    for (int j = 0; j < cur.size(); ++j) {
      for (int k = 0; k < 3; ++k) {
        int a = cur[j].v[k], b = cur[j].v[(k + 1) % 3];
        if (vis[a][b] != vis[b][a] && vis[a][b])
          tmp.push_back(Face(a, b, i));
      }
    }
    cur = tmp;
  }
  double ans = 0;
  for (int i = 0; i < cur.size(); ++i) {
    // printf("%d %d %d\n", cur[i].v[0], cur[i].v[1], cur[i].v[2]);
    ans += V(pp[1], pp[cur[i].v[0]], pp[cur[i].v[1]], pp[cur[i].v[2]]);
  }
  return ans / 6;
  /*
  2 1 4
  1 3 4
  1 2 5
  3 1 5
  2 4 5
  4 3 5
  */
}

int main() {
  n = 1;
  double x, y, z;
  while (scanf("%lf%lf%lf", &x, &y, &z) == 3) {
    p[n] = Point(x, y, z);
    p[n].Noise();
    pp[n] = Point(x, y, z);
    ++n;
  }
  --n;
  // printf("%d\n", n);
  // for (int i = 1; i <= n; ++i)
  //   printf("%lf %lf %lf\n", pp[i].x, pp[i].y, pp[i].z);
  printf("%.2lf\n", Solve());
  return 0;
}
