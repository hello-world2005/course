// 0000...11111

#include <cstdio>
#include <cstring>

typedef long long ll;

const int M = 510;

int qwq[M];

int main() {
  ll n;
  int p;
  scanf("%lld%d", &n, &p);
  int now = 1 % p, vis[M] = {0}, ert[M] = {0}, qwe, wer;
  for (int i = 1; i <= p + 1; ++i) {
    if (vis[now]) {
      qwe = vis[now], wer = i - qwe;
      break;
    }
    vis[now] = i, ++ert[now];
    now = (now * 10 + 1) % p;
  }
  return 0;
}
