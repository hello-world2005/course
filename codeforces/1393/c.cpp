#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>

const int N = 1e5 + 10;

int a[N], b[N];
typedef std::pair<int, int> pii;
bool vis[N];

bool Check(int x, int n) {
  ++x;
  for (int i = 1; i <= n; ++i)
    b[i] = 0, vis[i] = false;
  for (int i = 1; i <= n; ++i)
    ++b[a[i]];
  std::vector<pii> v;
  for (int i = 1; i <= n; ++i)
    v.push_back(std::make_pair(b[i], i));
  std::sort(v.rbegin(), v.rend());
  // for (int i = 0; i < (int)v.size(); ++i)
  //   for (int j = 1; j <= v[i].first; ++j) {
  //     int p = (i + 1) + (j - 1) * x;
  //     for (; p <= n + 1; ++p)
  //       if (!vis[p]) {
  //         vis[p] = true;
  //         break;
  //       }
  //     if (p > n)
  //       return false;
  //   }
  // for (int i = 0; i < (int)v.size(); ++i)
  // int qwq = v[0].first * x;
  // if (qwq > n)
  //   return false;
  // qwq = v[1].first * x;
  // int pre = 0;
  // for (int i = 0; i < (int)v.size(); ++i) {
  //   int qwq = (v[i].first - 1) * x + pre;
  //   if(qwq > n)
  //     return false;
  // }
  // int qwq = (v[0].first - 1) * x;
  // if (qwq > n)
  //   return false;
  // qwq = (v[1].first - 1) * x + (x == 1 ? v[0].first : 0);
  // if (qwq > n)
  //   return false;
  // std::set<pii> s;
  // for (int i = 0; i < x; ++i)
  //   s.insert(std::make_pair(0, i));
  // for (int i = 0; i < (int)v.size(); ++i) {
  //   pii pre = *s.begin();
  //   int qwq = (v[i].first - 1) * x + pre.first + pre.second;
  //   printf(" %d %d %d %d %d\n", v[i].second, v[i].first, qwq, pre.first, pre.second);
  //   if(qwq > n)
  //     return false;
  //   pre.first = qwq;
  //   s.insert(pre);
  // }
  // for ()
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]), ++b[a[i]];
    // int l = 0, r = n - 2, res;
    // while (l <= r) {
    //   int mid = (l + r) >> 1;
    //   if (Check(mid, n))
    //     l = mid + 1, res = mid;
    //   else
    //     r = mid - 1;
    // }
    // printf("%d\n", res);
    // printf("%d\n", Check(4, n));
    int maxn = 0, cnt = 0;
    for (int i = 1; i <= n; ++i)
      maxn = std::max(maxn, b[a[i]]);
    for (int i = 1; i <= n; ++i)
      if (b[i] == maxn)
        ++cnt;
    // printf("%d %d\n", maxn, cnt);
    printf("%d\n", (n - cnt) / (maxn - 1) - 1);
    for (int i = 1; i <= n; ++i)
      b[a[i]] = 0;
  }
  return 0;
}
