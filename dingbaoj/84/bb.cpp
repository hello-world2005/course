#include <algorithm>
#include <bitset>
#include <cstdio>
#include <ctime>
#include <random>
#include <unordered_map>

// #undef DEBUG

const int N = 1e5 + 10;
const int M = 1e6 + 10;
const int K = 1e4;

int n, q;
int a[N];

typedef long long ll;

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
    ll pre = Query(p) - Query(p - 1);
    Add(p, k - pre);
  }
} ft;

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
  int tot = 0, t = x;
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

std::mt19937 rnd(time(NULL));

struct FhqTreap {
  struct Node {
    std::bitset<K> a, s;  // a 是原来的, s 是类似于 tag
    int tag, rnd;
    int sze, ch[2];

    Node() : tag(0), rnd(0), sze(1) { ch[0] = ch[1] = 0, s.reset(); }
    Node(int val) : rnd(::rnd()), sze(1) {
      ch[0] = ch[1] = 0;
      tag = 1;
      int _val = val;
      // for (int i = 1; i <= cnt && pri[i] * pri[i] <= _val; ++i)
      for (int i = 1; i <= cnt; ++i)
        if (val % pri[i] == 0) {
          int _i = val / pri[i];
          if (_i % pri[i] == 0)
            tag = 0;
          while (val % pri[i] == 0)
            val /= pri[i];
          s.set(i);
        }
      a = s;
    }

    int GetVal() {
      // printf("wirgulh %d %d\n", tag, (int)s.count());
      return tag * ((s.count() & 1) ? -1 : 1);
    }
  } t[N];
  int tot;

#define lc(rt) t[rt].ch[0]
#define rc(rt) t[rt].ch[1]

  int NewNode(int val) {
    t[++tot] = Node(val);
    return tot;
  }

  void PushUp(int rt) {
    std::bitset<K> qwq = t[lc(rt)].s & t[rc(rt)].s;
    if (qwq.any())
      t[rt].tag &= 0;
    else
      t[rt].tag &= 1;
    qwq = t[rt].s & t[lc(rt)].s;
    if (qwq.any())
      t[rt].tag &= 0;
    else
      t[rt].tag &= 1;
    qwq = t[rt].s & t[rc(rt)].s;
    if (qwq.any())
      t[rt].tag &= 0;
    else
      t[rt].tag &= 1;
    t[rt].s |= t[lc(rt)].s | t[rc(rt)].s;
    t[rt].sze = t[lc(rt)].sze + t[rc(rt)].sze + 1;
  }

  void Split(int rt, int v, int& rt1, int& rt2) {
    if (!rt) {
      rt1 = rt2 = 0;
      return;
    }
    if (t[lc(rt)].sze <= v) {
      rt1 = rt;
      Split(rc(rt), v - t[lc(rt)].sze - 1, rc(rt), rt2);
    } else {
      rt2 = rt;
      Split(lc(rt), v, rt1, lc(rt));
    }
    if (t[rt].ch[0] == 0 && t[rt].ch[1] == 0)
      t[rt].s = t[rt].a;
    // printf("!!E$y27r3q9uiawgf %d %d\n", rt, (int)t[rt].s.count());
    PushUp(rt);
  }

  int Merge(int rt1, int rt2) {
    if (!rt1)
      return t[rt2].s = t[rt2].a, rt2;
    if (!rt2)
      return t[rt1].s = t[rt1].a, rt1;
    if (t[rt1].rnd < t[rt2].rnd) {
      rc(rt1) = Merge(rc(rt1), rt2);
      PushUp(rt1);
      return rt1;
    } else {
      lc(rt2) = Merge(rt1, lc(rt2));
      PushUp(rt2);
      return rt2;
    }
  }
} fhq;

#ifdef DEBUG
void Print() {
  for (int i = 1; i <= n; ++i)
    printf("%d %d\n%d %d\n", i, fhq.t[i].ch[0], i, fhq.t[i].ch[1]);
}
#else
void Print() {}
#endif

int main() {
  Sieve();
  scanf("%d%d", &n, &q);
  int rt = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    ft.Add(i, a[i]);
    fhq.NewNode(a[i]), rt = fhq.Merge(rt, i);
  }
  while (q--) {
    // printf("> ");
    // for (int i = 1; i <= 5; ++i)
    //   printf("%d ", fhq.t[1].s.test(i));
    // printf("\n");
    int opt, l, r;
    scanf("%d%d%d", &opt, &l, &r);
    if (opt == 1) {
      ft.Change(l, r);
      int x, y, z;
      fhq.Split(rt, l, x, y);
      fhq.Split(x, l - 1, x, z);
      std::bitset<K> s;
      int val = r, tag = 1;
      for (int i = 1; i <= cnt; ++i)
        if (val % pri[i] == 0) {
          int _i = val / pri[i];
          if (_i % pri[i] == 0)
            tag = 0;
          while (val % pri[i] == 0)
            val /= pri[i];
          s.set(i);
        }
      fhq.t[z].tag = tag, fhq.t[z].a = fhq.t[z].s = s;
      fhq.Merge(fhq.Merge(x, z), y);
    } else if (opt == 2) {
      ll sum = ft.Query(r) - ft.Query(l - 1);
      printf("%d\n", Mu(sum));
    } else {
      int x, y, z;
      fhq.Split(rt, r, x, y);
      fhq.Split(x, l - 1, x, z);
      Print();
      printf("%d\n", fhq.t[z].GetVal());
      fhq.Merge(fhq.Merge(x, z), y);
    }
  }
  return 0;
}

// 1 5
// 6
// 1 1 5
// 3 1 1
// 1 1 3
// 1 1 7
// 3 1 1

// 2 5
// 6 8 
// 2 2 2
// 2 2 2
// 3 2 2
// 2 1 1
// 3 1 2
