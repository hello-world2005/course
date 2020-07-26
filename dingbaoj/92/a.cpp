#include <bitset>
#include <cstdio>
#include <cstring>
#include <queue>

#define int long long

#undef DEBUG

typedef long long ll;

const int N = 2010;

int n;
ll a[N][N];
ll cur[N], o[N], oo[N];
int g[N];
int ans;

void Bfs(int s) {
  for (int i = 0; i < 35; ++i)
    cur[i] = o[i] = 0;
  o[s / 60] = cur[s / 60] = 1ll << (s % 60);
  int qwq = 1, d = 0, sum = 1;
  while (qwq) {
    int t = 0;
    qwq = 0;
    ++d;
    for (int i = 0; i < 35; ++i)
      for (int j = 0; j < 60; ++j)
        if (cur[i] >> j & 1)
          g[t++] = i * 60 + j;
    for (int i = 0; i < 35; ++i)
      oo[i] = o[i];
    for (int i = 0; i < t; ++i)
      for (int j = 0; j < 35; ++j)
        o[j] |= a[g[i]][j];
    for (int i = 0; i < 35; ++i) {
      cur[i] = o[i] ^ oo[i];
      qwq += __builtin_popcountll(cur[i]);
      // printf("%lld ", cur[i]);
    }
    // printf("\n");
    ans += d * d * qwq;
    sum += qwq;
    // printf("%lld\n", qwq);
  }
  ans += n * n * (n - sum);
}

char s[N];

signed main() {
  scanf("%lld", &n);
  for (int i = 0, x; i < n; ++i) {
    scanf("%s", s);
    for (int j = 0; j < 35; ++j)
      for (int k = 0; k < 60; ++k)
        if (j * 60 + k < n && s[j * 60 + k] == '1')
          a[i][j] |= (1ll << k);
  }
  for (int i = 0; i < n; ++i)
    Bfs(i);
  printf("%lld\n", ans);
  return 0;
}
