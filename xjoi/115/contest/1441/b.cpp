#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>

const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N];
int l[N], r[N];
std::multiset<int> s1, s2;
int minn, ans = INF;

void Insert(int x) {
  auto it = s1.lower_bound(x);
  auto m = *it - x;
  --it;
  ans = std::min(ans, std::min(m, x - *it));
  s1.insert(x);
}

void Update(int p, int x) {
  s2.insert(abs(x - r[p]));
  if (p != n) {
    s2.erase(s2.find(abs(l[p + 1] - r[p])));
    s2.insert(abs(l[p + 1] - x));
  }
  r[p] = x;
}

int main() {
  scanf("%d%d", &n, &m);
  s1.insert(-INF);
  s1.insert(INF);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    l[i] = r[i] = a[i];
    if (i >= 2)
      s2.insert(abs(a[i] - a[i - 1]));
  }
  for (int i = 1; i <= n; ++i)
    Insert(a[i]);
  while (m--) {
    char opt[20];
    scanf("%s", opt + 1);
    if (opt[5] == 'R') {
      int p, k;
      scanf("%d%d", &p, &k);
      Insert(k);
      Update(p, k);
    } else if (opt[5] == 'G') {
      printf("%d\n", *s2.begin());
    } else {
      printf("%d\n", ans);
    }
  }
}
