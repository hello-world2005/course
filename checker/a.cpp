#include <bitset>
#include <cstdio>
#include <unordered_map>

typedef long long ll;

const int N = 1e5 + 10;
const int K = 1e4;
const int M = 5e5 + 10;

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
  if (x < M)
    return mu[x];
  if (_mu.find(x) != _mu.end())
    return _mu[x];
  int tot = 0;
  ll t = x;
  for (int i = 1; i <= cnt && 1ll * pri[i] * pri[i] <= x; ++i)
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

int n, q;
int a[N];

struct FenwickTree {
  ll sum[N];

#define LowBit(x) (x & -x)

  void Add(int p, int k) {
    for (; p <= n; p += LowBit(p))
      sum[p] += k;
  }

  ll Query(int p) {
    ll res = 0;
    for (; p; p -= LowBit(p))
      res += sum[p];
    return res;
  }

  void Change(int p, int k) {
    int pre = (int)(Query(p) - Query(p - 1));
    Add(p, k - pre);
  }
} ft;

struct SegmentTree {
  struct Node {
    std::bitset<K> s;
    int tag;

    Node() : tag(0) { s.reset(); }

    Node operator=(const int& x) {
      int r = x;
      tag = 1;
      s.reset();
      // printf("%d: ", x);
      for (int i = 1; i <= cnt && pri[i] <= x; ++i)
        if (r % pri[i] == 0) {
          int _i = r / pri[i];
          if (_i % pri[i] == 0)
            tag = 0;
          while (r % pri[i] == 0)
            r /= pri[i];
          s.set(i);
          // printf("%d ", i);
        }
      // printf("\n");
      return *this;
    }
    Node operator+(const Node& rhs) {
      Node res;
      std::bitset<K> qwq = s & rhs.s;
      if (qwq.none())
        res.tag = 1;
      res.tag &= tag & rhs.tag;
      res.s = s | rhs.s;
      return res;
    }

    int Val() {
      // printf("%d %d\n", tag, s.count());
      return tag * ((s.count() & 1) ? -1 : 1);
    }
  } t[N << 2];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void PushUp(int rt) { t[rt] = t[lc] + t[rc]; }

  void Build(int rt, int l, int r) {
    if (l == r)
      return t[rt] = a[l], void();
    int mid = (l + r) >> 1;
    Build(ls), Build(rs);
    PushUp(rt);
  }

  void Change(int rt, int l, int r, int p, int k) {
    if (l == r)
      return t[rt] = a[l] = k, void();
    int mid = (l + r) >> 1;
    if (p <= mid)
      Change(ls, p, k);
    else
      Change(rs, p, k);
    PushUp(rt);
  }

  Node Query(int rt, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
      return t[rt];
    int mid = (l + r) >> 1;
    if (qr <= mid)
      return Query(ls, ql, qr);
    if (ql > mid)
      return Query(rs, ql, qr);
    return Query(ls, ql, qr) + Query(rs, ql, qr);
  }
} st;

int main() {
  Sieve();
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), ft.Add(i, a[i]);
  st.Build(1, 1, n);
  while (q--) {
    int opt, l, r;
    scanf("%d%d%d", &opt, &l, &r);
    if (opt == 1) {
      ft.Change(l, r), st.Change(1, 1, n, l, r);
    } else if (opt == 2) {
      printf("%d\n", Mu(ft.Query(r) - ft.Query(l - 1)));
    } else {
      printf("%d\n", st.Query(1, 1, n, l, r).Val());
    }
  }
  return 0;
}