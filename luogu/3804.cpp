#include <algorithm>
#include <cstdio>
#include <cstring>
#include<iostream>
using namespace std;
const int N = 1e6 + 10;

struct SuffixAutoMaton {
  struct Node {
    int ch[26];
    int len, fa;
    int sze;

    Node() {
      memset(ch, 0, sizeof(ch));
      len = 0;
    }
  } a[N << 1];
  int lst, tot;

  void Insert(int c) {
    int p = lst;
    int np = lst = ++tot;
    a[np].len = a[p].len + 1;
    for (; p && !a[p].ch[c]; p = a[p].fa)
      a[p].ch[c] = np;
    if (!p) {
      a[np].fa = 1;
    } else {
      int q = a[p].ch[c];
      if (a[q].len == a[p].len + 1) {
        a[np].fa = q;
      } else {
        int nq = ++tot;
        a[nq] = a[q];
        a[nq].len = a[p].len + 1;
        a[nq].sze=0;
        a[q].fa = a[np].fa = nq;
        for (;a[p].ch[c] == q; p = a[p].fa)
          a[p].ch[c] = nq;
      }
    }
    a[np].sze = 1;
  }
  void Build(char* s) {
    lst = tot = 1;
    int n = strlen(s + 1);
    for (int i = 1; i <= n; ++i)
      Insert(s[i] - 'a');
  }
} sa;

int n;
char s[N << 1];
int c[N << 1], d[N << 1];

long long Solve() {
  for (int i = 1; i <= sa.tot; ++i)
    ++c[sa.a[i].len];
  for (int i = 1; i <= sa.tot; ++i)
    c[i] += c[i - 1];
  for (int i = sa.tot; i >= 1; --i)
    d[c[sa.a[i].len]--] = i;
  long long ans = 0;
  for (int i = sa.tot; i; --i) {
    int p = d[i];
    sa.a[sa.a[p].fa].sze += sa.a[p].sze;
    if (sa.a[p].sze > 1)
      ans = std::max(ans, 1ll * sa.a[p].sze * sa.a[p].len);
  }
  return ans;
}

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  sa.Build(s);
  printf("%lld\n", Solve());
  return 0;
}
