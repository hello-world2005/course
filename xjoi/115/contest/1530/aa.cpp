#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1e5 + 10;
const int S = 320;

int n, m, k;
int p[N];
int a[S][N], b[S][N];

int l[N], r[N];
int bel[N];

int cnt[N];

void Init() {
  int blo = (n - 1) / S + 1;
  for (int i = 1; i <= blo; ++i) {
    l[i] = r[i - 1] + 1, r[i] = i * S;
    for (int j = l[i]; j <= r[i]; ++j)
      bel[j] = i;
  }
  for (int i = 1; i <= n; ++i) {
    ++cnt[p[i]];
  }
}

int fir[N];

int main() {
  scanf("%d%d%d", &n, &m, &k);
  std::vector<int> v;
  for (int i = 1; i <= m; ++i)
    scanf("%d", &p[i]), v.push_back(p[i]);
  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());
  for (int i = 1; i <= m; ++i) {
    int pos = std::lower_bound(v.begin(), v.end(), p[i]) - v.begin() + 1;
    fir[pos] = p[i], p[i] = pos;
  }
  Init();
  for (int i = 1; i <= m; ++i)
    ;
  for (int i = 1; i <= m; ++i)
    ;
}
