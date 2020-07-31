#include <algorithm>
#include <cstdio>
#include <vector>

const int N = 2010;

int n;
struct Line {
  int xl, xr, y;
} l[N];

double Calc(double slope) {
  double ml = 1e12, mr = -1e12;
  for (int i = 1; i <= n; ++i) {
    ml = std::min(ml, l[i].xl + l[i].y * slope);
    mr = std::max(mr, l[i].xr + l[i].y * slope);
  }
  return mr - ml;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d%d%d", &l[i].xl, &l[i].xr, &l[i].y);
  std::vector<std::pair<double, int> > slope;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (l[i].y > l[j].y) {
        slope.push_back(
            std::make_pair(1.0 * (l[j].xl - l[i].xr) / (l[i].y - l[j].y), 1));
        slope.push_back(
            std::make_pair(1.0 * (l[j].xr - l[i].xl) / (l[i].y - l[j].y), -1));
      }
  std::sort(slope.begin(), slope.end());
  int qwq = 0;
  std::vector<double> _slope;
  for (auto i : slope) {
    if (qwq == 0 && i.second == 1)
      qwq = 1, _slope.push_back(i.first);
    if (qwq == 1 && i.second == -1)
      qwq = 0, _slope.push_back(i.first);
  }
  std::sort(_slope.begin(), _slope.end());
  int l = 0, r = _slope.size() - 1;
  double ans = 1e12;
  while (l <= r) {
    int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
    double ans1 = Calc(_slope[m1]), ans2 = Calc(_slope[m2]);
    if (ans1 < ans2)
      r = m2 - 1;
    else
      l = m1 + 1;
    ans = std::min(ans1, ans2);
  }
  printf("%.9lf\n", ans);
  return 0;
}
