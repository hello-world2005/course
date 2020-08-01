#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>

const double EPS = 1e-8;

double ax1, ay1, ax2, ay2;
double bx1, by1, bx2, by2;

typedef std::pair<double, double> pdd;
typedef std::pair<pdd, int> pddi;
typedef std::pair<double, int> pdi;

pdd po[10][10];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    std::vector<pddi> p;
    std::vector<pdi> xx, yy;
    for (int i = 1; i <= 2; ++i)
      for (int j = 1; j <= 4; ++j) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        po[i][j] = std::make_pair(x, y);
        p.push_back(std::make_pair(std::make_pair(x, y), i));
        xx.push_back(std::make_pair(x, i)), yy.push_back(std::make_pair(y, i));
      }
    // std::sort(p.begin(), p.end(), [&](const pddi lhs, const pddi rhs) {
    //   return lhs.first.first < rhs.first.first;
    // });
    // std::sort(xx.begin(), xx.end(), [&](const pdi lhs, const pdi rhs) {
    //   return ;
    // });
    int qwq = 0, qaq = 0;
    auto Sqr = [&](const double x) { return x * x; };
    auto Dis = [&](const pdd a, const pdd b) {
      return sqrt(Sqr(a.first - b.first) + Sqr(a.second - b.second));
    };
    for (int i = 1; i <= 4; ++i)
      for (int j = 1; j <= 4; ++j)
        if (Dis(po[1][i], po[2][j]))
          qwq = i, qaq = j;
    
  }
  return 0;
}
