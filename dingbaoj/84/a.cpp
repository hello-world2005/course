#include <algorithm>
#include <cstdio>
#include <unordered_set>

const int N = 2e5 + 10;
const int BASE = 100;
const int MOD1 = 402653189;
const int MOD2 = 805306457;

char s[N], t[N];
int pre1[N], pre2[N];

int FastPow(int a, int b, int MOD) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

struct PairHash {
  const int MOD = 998244353;
  int operator()(const std::pair<int, int>& rhs) const {
    return (1ll * rhs.first * MOD + rhs.second) % MOD;
  }
};

int main() {
  int T;
  scanf("%d", &T);
  std::unordered_set<std::pair<int, int>, PairHash> has;
  while (T--) {
    has.clear();
    int n, m;
    scanf("%d", &n), m = n, ++n;
    scanf("%s%s", s + 1, t + 1);
    pre1[0] = pre2[0] = 0;
    for (int i = 1; i <= m; ++i)
      pre1[i] = (1ll * pre1[i - 1] * BASE + t[i]) % MOD1,
      pre2[i] = (1ll * pre2[i - 1] * BASE + t[i]) % MOD2;
    has.insert(std::make_pair(pre1[m], pre2[m]));
    for (int i = 1; i <= m; ++i) {  // 1~i i + 1~m
      int x1 = pre1[i],
          y1 = (pre1[m] - 1ll * pre1[i] * FastPow(BASE, m - i, MOD1) % MOD1 +
                MOD1) %
               MOD1;
      int z1 = (x1 + 1ll * y1 * FastPow(BASE, i, MOD1) % MOD1) % MOD1;
      int x2 = pre2[i],
          y2 = (pre2[m] - 1ll * pre2[i] * FastPow(BASE, m - i, MOD2) % MOD2 +
                MOD2) %
               MOD2;
      int z2 = (x2 + 1ll * y2 * FastPow(BASE, i, MOD2) % MOD2) % MOD2;
      has.insert(std::make_pair(z1, z2));
    }
    for (int i = 1; i <= n; ++i)
      pre1[i] = (1ll * pre1[i - 1] * BASE + s[i]) % MOD1,
      pre2[i] = (1ll * pre2[i - 1] * BASE + s[i]) % MOD2;
    bool flag = false;
    for (int i = 1; i <= n; ++i) {  // 1~i - 1 i + 1~n
      int x1 = pre1[i - 1],
          y1 = (pre1[n] - 1ll * pre1[i] * FastPow(BASE, n - i, MOD1) % MOD1 +
                MOD1) %
               MOD1;
      int z1 = (x1 + 1ll * y1 * FastPow(BASE, i - 1, MOD1) % MOD1) % MOD1;
      // printf("%d %d %d\n", x1, y1, z1);
      int x2 = pre2[i - 1],
          y2 = (pre2[n] - 1ll * pre2[i] * FastPow(BASE, n - i, MOD2) % MOD2 +
                MOD2) %
               MOD2;
      int z2 = (x2 + 1ll * y2 * FastPow(BASE, i - 1, MOD2) % MOD2) % MOD2;
      if (has.find(std::make_pair(z1, z2)) != has.end()) {
        flag = true;
        break;
      }
    }
    printf("%s\n", flag ? "YES" : "NO");
  }
  return 0;
}
