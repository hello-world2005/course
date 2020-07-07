#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int, int>
#define mem0(x) memset((x), 0, sizeof(x))
#define mem1(x) memset((x), 0x3f, sizeof(x))
il char gc() {
  static const int BS = 1 << 22;
  static unsigned char buf[BS], *st, *ed;
  if (st == ed)
    ed = buf + fread(st = buf, 1, BS, stdin);
  return st == ed ? EOF : *st++;
}
#define gc getchar
template <class T>
void in(T& x) {
  x = 0;
  bool f = 0;
  char c = gc();
  while (c < '0' || c > '9') {
    if (c == '-')
      f = 1;
    c = gc();
  }
  while ('0' <= c && c <= '9') {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = gc();
  }
  if (f)
    x = -x;
}
#undef gc
#define pb push_back
#define N 100010
#define B 320
int n, m;
int a[N];
int block, bl[N];
int l[B];
int f[B][B];
int cnt[B][N];
int st[N], top;
int num[N];
// bitset<N>h[B][B], tmp;
signed main() {
#ifndef ONLINE_JUDGE
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif
  int ans = 0, cc, ql, qr;
  in(n), in(cc), in(m);
  block = 320;
  for (ri i = 1; i <= n; ++i) {
    in(a[i]);
    bl[i] = (i - 1) / block + 1;
    if (bl[i] != bl[i - 1])
      l[bl[i]] = i;
  }
  bl[n + 1] = bl[n] + 1;
  l[bl[n + 1]] = n + 1;
  for (ri i = 1; i <= bl[n]; ++i) {
    int t = 0;
    for (ri j = l[i]; j <= n; ++j) {
      cnt[i][a[j]]++;
      if ((cnt[i][a[j]] & 1) && (cnt[i][a[j]] > 1))
        t--;
      else if ((cnt[i][a[j]] & 1) == 0)
        t++;
      if (bl[j] != bl[j + 1]) {
        f[i][bl[j]] = t;
      }
    }
  }
  while (m--) {
    in(ql), in(qr);
    ql = (ql + ans) % n + 1, qr = (qr + ans) % n + 1;
    if (ql > qr)
      swap(ql, qr);
    ans = 0;
    if (bl[ql] == bl[qr]) {
      for (ri i = ql; i <= qr; ++i) {
        num[a[i]]++;
        st[++top] = a[i];
      }
      while (top) {
        if (num[st[top]] != 0) {
          ans += (num[st[top]] & 1) ^ 1;
          num[st[top]] = 0;
        }
        top--;
      }
      printf("%d\n", ans);
      continue;
    }
    if (bl[ql] + 1 <= bl[qr] - 1)
      ans = f[bl[ql] + 1][bl[qr] - 1];
    for (ri i = ql; i < l[bl[ql] + 1]; ++i) {
      num[a[i]]++;
      st[++top] = a[i];
    }
    for (ri i = l[bl[qr]]; i <= qr; ++i) {
      num[a[i]]++;
      st[++top] = a[i];
    }
    printf("%d\n", top);
    while (top) {
      int t = st[top];
      if (num[t] != 0) {
        if ((cnt[bl[ql] + 1][t] - cnt[bl[qr]][t] > 0) &&
            ((cnt[bl[ql] + 1][t] - cnt[bl[qr]][t]) & 1) == 0 &&
            (num[st[top]] & 1)) {
          ans--;
        } else if (((cnt[bl[ql] + 1][t] - cnt[bl[qr]][t] > 0) &&
                    ((cnt[bl[ql] + 1][t] - cnt[bl[qr]][t]) & 1)) &&
                   (num[st[top]] & 1)) {
          ans++;
        } else if ((cnt[bl[ql] + 1][t] - cnt[bl[qr]][t] == 0) &&
                   (num[st[top]] & 1) == 0) {
          ans++;
        }
        num[st[top]] = 0;
      }
      top--;
    }
    printf("%d\n", ans);
  }
  return 0;
}