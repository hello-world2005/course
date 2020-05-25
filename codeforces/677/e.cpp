#include <algorithm>
#include <cmath>
#include <cstdio>

const int N = 1e3 + 10;
const int MOD = 1e9 + 7;

int n;
struct Interger {
  int log_2, log_3;

  Interger() : log_2(0), log_3(0) {}
  Interger(int _log_2, int _log_3) : log_2(_log_2), log_3(_log_3) {}
  Interger(int a) {
    if (a == 1 || a == 0)
      log_2 = log_3 = 0;
    else if (a == 2)
      log_2 = 1, log_3 = 0;
    else
      log_2 = 0, log_3 = 1;
  }

  Interger operator*(const int& rhs) {
    if (rhs == 2)
      return Interger(log_2 + 1, log_3);
    if (rhs == 3)
      return Interger(log_2, log_3 + 1);
    return Interger(log_2, log_3);
  }
  Interger operator/(const int& rhs) {
    if (rhs == 2)
      return Interger(log_2 - 1, log_3);
    if (rhs == 3)
      return Interger(log_2, log_3 - 1);
    return Interger(log_2, log_3);
  }
  Interger operator*(const Interger& rhs) {
    return Interger(log_2 + rhs.log_2, log_3 + rhs.log_3);
  }
  Interger operator/(const Interger& rhs) {
    return Interger(log_2 - rhs.log_2, log_3 - rhs.log_3);
  }
  bool operator<(const Interger& rhs) const {
    if (log_2 < rhs.log_2 && log_3 < rhs.log_3)
      return true;
    if (log_2 > rhs.log_2 && log_3 > rhs.log_3)
      return false;
    int x = log_2 - rhs.log_2, y = rhs.log_3 - log_3;
    return 1.0 * x < log(3) / log(2) * y;
  }
  // bool operator>(const Interger& rhs) const { return log_2 || log_3; }  // >
  // 0
};
int a[N][N];
Interger sumr[N][N], sumc[N][N];
int pr[N][N], pc[N][N], br[N][N], bc[N][N];
Interger sump[N][N], sumn[N][N];  // 撇 捺
int pp[N][N], pn[N][N], bp[N][N], bn[N][N];

int FastPow(int a, int b) {
  int res = 1;
  for (; b; a = 1ll * a * a % MOD, b >>= 1)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

void Print(Interger x) {
  // printf("%d %d\n", x.log_2, x.log_3);
  printf("%d\n", int(1ll * FastPow(2, x.log_2) * FastPow(3, x.log_3) % MOD));
}

int main() {
  scanf("%d", &n);
  bool flag = false;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      scanf("%1d", &a[i][j]), flag |= (a[i][j]);
  // -
  if (!flag) {
    printf("0\n");
    return 0;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j)
      sumr[i][j] = sumr[i][j - 1] * a[i][j];
    for (int j = 0; j <= n; ++j)
      if (a[i][j])
        pr[i][j] = pr[i][j - 1];
      else
        pr[i][j] = j;
    for (int j = n + 1; j >= 1; --j)
      if (a[i][j])
        br[i][j] = br[i][j + 1];
      else
        br[i][j] = j;
  }
  // |
  for (int j = 1; j <= n; ++j) {
    for (int i = 1; i <= n; ++i)
      sumc[i][j] = sumc[i - 1][j] * a[i][j];
    for (int i = 0; i <= n; ++i)
      if (a[i][j])
        pc[i][j] = pc[i - 1][j];
      else
        pc[i][j] = i;
    for (int i = n + 1; i >= 1; --i)
      if (a[i][j])
        bc[i][j] = bc[i + 1][j];
      else
        bc[i][j] = i;
  }
  // ru-ld
  for (int l = 2; l <= 2 * n; ++l) {
    for (int i = std::max(1, l - n); i <= std::min(n, l - 1); ++i) {
      int j = l - i;
      sump[i][j] = sump[i - 1][j + 1] * a[i][j];
    }
    for (int i = std::max(1, l - n) - 1; i <= std::min(n, l - 1); ++i) {
      int j = l - i;
      if (a[i][j])
        pp[i][j] = pp[i - 1][j + 1];
      else
        pp[i][j] = i;
    }
    for (int i = std::min(n, l - 1) + 1; i >= std::max(1, l - n); --i) {
      int j = l - i;
      if (a[i][j])
        bp[i][j] = bp[i + 1][j - 1];
      else
        bp[i][j] = i;
    }
  }
  // lu-rd
  for (int l = -n + 1; l <= n - 1; ++l) {
    for (int i = std::max(1, l + 1); i <= std::min(n, l + n); ++i) {
      int j = i - l;
      sumn[i][j] = sumn[i - 1][j - 1] * a[i][j];
    }
    for (int i = std::max(1, l + 1) - 1; i <= std::min(n, l + n); ++i) {
      int j = i - l;
      if (a[i][j])
        pn[i][j] = pn[i - 1][j - 1];
      else
        pn[i][j] = i;
    }
    for (int i = std::min(n, l + n) + 1; i >= std::max(1, l + 1); --i) {
      int j = i - l;
      if (a[i][j])
        bn[i][j] = bn[i + 1][j + 1];
      else
        bn[i][j] = i;
    }
  }
  Interger ans = 0;
  int ansx = 0, ansy = 0, opt = 0, ansl = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (a[i][j]) {
        int l =
            std::min({j - pr[i][j], br[i][j] - j, i - pc[i][j], bc[i][j] - i});
#ifndef DEBUG
        ans = std::max(ans, sumr[i][j + l - 1] / sumr[i][j - l] *
                                sumc[i + l - 1][j] / sumc[i - l][j] / a[i][j]);
#else
        if (ans < sumr[i][j + l - 1] / sumr[i][j - l] * sumc[i + l - 1][j] /
                      sumc[i - l][j] / a[i][j])
          ans = sumr[i][j + l - 1] / sumr[i][j - l] * sumc[i + l - 1][j] /
                sumc[i - l][j] / a[i][j],
          ansx = i, ansy = j, opt = 1;
#endif
      }
#ifdef DEBUG
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      printf("(%d, %d)%c", sump[i][j].log_2, sump[i][j].log_3, " \n"[j == n]);
#endif
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (a[i][j]) {
        int l =
            std::min({i - pp[i][j], bp[i][j] - i, i - pn[i][j], bn[i][j] - i});
#ifndef DEBUG
        ans = std::max(ans, sump[i + l - 1][j - l + 1] / sump[i - l][j + l] *
                                sumn[i + l - 1][j + l - 1] /
                                sumn[i - l][j - l] / a[i][j]);
#else
        // printf("%d %d: ", i, j);
        // Print(sump[i + l - 1][j - l + 1] / sump[i - l][j + l] *
        //       sumn[i + l - 1][j + l - 1] / sumn[i - l][j - l] / a[i][j]);
        if (ans < sump[i + l - 1][j - l + 1] / sump[i - l][j + l] *
                      sumn[i + l - 1][j + l - 1] / sumn[i - l][j - l] / a[i][j])
          ans = sump[i + l - 1][j - l + 1] / sump[i - l][j + l] *
                sumn[i + l - 1][j + l - 1] / sumn[i - l][j - l] / a[i][j],
          ansx = i, ansy = j, opt = 2, ansl = l;
#endif
      }
  Print(ans);
#ifdef DEBUG
  printf("%d %d %d %d\n", ansx, ansy, opt, ansl);
#endif
  return 0;
}
