#include <bitset>
#include <cstdio>
#include <unordered_map>

typedef long long ll;

const int N = 5e3 + 10;
const int M = 5e3 + 10;
const int K = N;

int n, q;
int a[N];

int pri[M], cnt;
bool vis[M];
int mu[M];

void Sieve() {
  mu[1] = 1;
  for (int i = 2; i < M; ++i) {
    if (!vis[i])
      pri[++cnt] = i, mu[i] = -1;
    for (int j = 1; j <= cnt && i * pri[j] < M; ++j) {
      vis[i * pri[j]] = true;
      if (i % pri[j] == 0) {
        mu[i * pri[j]] = 0;
        break;
      }
      mu[i * pri[j]] = -mu[i];
    }
  }
}

std::unordered_map<ll, int> _mu;

int Mu(ll x) {
  if (x < N)
    return mu[x];
  if (_mu.find(x) != _mu.end())
    return _mu[x];
  int tot = 0, t = x;
  for (int i = 1; i <= cnt && pri[i] * pri[i] <= x; ++i)
    if (x % pri[i] == 0) {
      if ((x / pri[i]) % pri[i] == 0)
        return _mu[x] = 0;
      ++tot;
      t /= pri[i];
    }
  if (t != 1)
    ++tot;
  return _mu[x] = (tot & 1) ? -1 : 1;
}

std::bitset<K> b[N];
int tag[N];

int main() {
  Sieve();
  scanf("%d%d", &n, &q);
  if (n > 5000)
    return 0;
  for (int l = 1; l <= n; ++l) {
    scanf("%d", &a[l]);
    int r = a[l];
    tag[l] = 1;
    b[l].reset();
    for (int i = 1; i <= cnt; ++i)
      if (r % pri[i] == 0) {
        int _i = r / pri[i];
        if (_i % pri[i] == 0)
          tag[l] = 0;
        while (r % pri[i] == 0)
          r /= pri[i];
        b[l].set(i);
      }
  }
  // printf("%d %d %d %d %d\n", tag[1], tag[2], tag[3], tag[4], tag[5]);
  while (q--) {
    int opt, l, r;
    scanf("%d%d%d", &opt, &l, &r);
    if (opt == 1) {
      a[l] = r;
      tag[l] = 1;
      b[l].reset();
      for (int i = 1; i <= cnt; ++i)
        if (r % pri[i] == 0) {
          int _i = r / pri[i];
          if (_i % pri[i] == 0)
            tag[l] = 0;
          while (r % pri[i] == 0)
            r /= pri[i];
          b[l].set(i);
        }
    } else if (opt == 2) {
      ll sum = 0;
      for (int i = l; i <= r; ++i)
        sum += a[i];
      printf("%d\n", Mu(sum));
    } else {
      std::bitset<K> res, t;
      int tagg = 1;
      for (int i = l; i <= r; ++i) {
        t = res & b[i];
        if (t.any()) {
          tagg = 0;
          break;
        }
        res |= b[i];
        tagg *= tag[i];
      }
      printf("%d\n", tagg * (res.count() & 1 ? -1 : 1));
    }
  }
  return 0;
}
