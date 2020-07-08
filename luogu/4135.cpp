#include <cmath>
#include <cstdio>
#include <vector>

const int N = 1e5 + 10;
const int S = 320;

int n, c, q;
int a[N];
int tot[N];
int cnt[S][N], ans[S][S];

struct Block {
  int blocks;
  int le[S], ri[S];
  int belong[N];

  void Build() {
    blocks = (n - 1) / S + 1;
    for (int i = 1; i <= blocks; ++i) {
      le[i] = ri[i - 1] + 1;
      ri[i] = i * S;
    }
    ri[blocks] = n;
    for (int i = 1; i <= blocks; ++i)
      for (int j = le[i]; j <= ri[i]; ++j)
        belong[j] = i;
    for (int i = 1; i <= blocks; ++i) {
      int t = 0;
      for (int j = le[i]; j <= n; ++j) {
        ++cnt[i][a[j]];
        if (cnt[i][a[j]] != 1 && (cnt[i][a[j]] & 1))
          --t;
        else if (!(cnt[i][a[j]] & 1))
          ++t;
        if (belong[j] != belong[j + 1])
          ans[i][belong[j]] = t;
      }
    }
  }

  int Get(int p) { return belong[p]; }

  int Solve(int l, int r, int x, int y) {
    // printf("%d %d %d %d\n", l, r, x, y);
    std::vector<int> vis;
    int res = 0;
    res = ans[x + 1][y - 1];
    for (int i = l; i <= ri[x]; ++i) {
      ++tot[a[i]];
      vis.push_back(a[i]);
    }
    for (int i = le[y]; i <= r; ++i) {
      ++tot[a[i]];
      vis.push_back(a[i]);
    }
    // printf("%u\n", vis.size());
    for (auto i : vis) {
      if (tot[i]) {
        if ((cnt[x + 1][i] > cnt[y][i]) &&
            !((cnt[x + 1][i] - cnt[y][i]) & 1) && (tot[i] & 1))
          --res;
        else if ((cnt[x + 1][i] > cnt[y][i]) &&
                 ((cnt[x + 1][i] - cnt[y][i]) & 1) && (tot[i] & 1))
          ++res;
        else if (!(cnt[x + 1][i] - cnt[y][i]) && !(tot[i] & 1))
          ++res;
        tot[i] = 0;
      }
    }
    vis.clear();
    return res;
  }
} block;

int main() {
  // freopen("a.in", "r", stdin);
  // freopen("a.out", "w", stdout);
  scanf("%d%d%d", &n, &c, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  block.Build();
  int lastans = 0;
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    l = (l + lastans) % n + 1, r = (r + lastans) % n + 1;
    if (l > r)
      l ^= r ^= l ^= r;
    int x = block.Get(l), y = block.Get(r);
    int res = 0;
    if (x == y) {
      std::vector<int> vis;
      for (int i = l; i <= r; ++i) {
        ++tot[a[i]];
        vis.push_back(a[i]);
      }
      for (auto i : vis) {
        if (!tot[i])
          continue;
        if (!(tot[i] & 1))
          ++res;
        tot[i] = 0;
      }
      vis.clear();
    } else {
      res = block.Solve(l, r, x, y);
    }
    printf("%d\n", lastans = res);
  }
  return 0;
}
