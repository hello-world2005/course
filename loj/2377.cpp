#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e6 + 10;

struct SuffixAutomaton {
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
        a[nq].sze = 0;
        a[q].fa = a[np].fa = nq;
        for (; a[p].ch[c] == q; p = a[p].fa)
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
} sam;

int n;
char s[N << 1];
int c[N << 1], d[N << 1], sze[N << 1];

long long TopSort() {
  for (int i = 1; i <= sam.tot; ++i)
    ++c[sam.a[i].len];
  for (int i = 1; i <= sam.tot; ++i)
    c[i] += c[i - 1];
  for (int i = 1; i <= sam.tot; ++i)
    d[c[sam.a[i].len]--] = i;
  for (int i = 1; i <= sam.tot; ++i)
    sze[i] = sam.a[i].sze;
  long long res = 0;
  for (int i = sam.tot; i; --i) {
    sze[sam.a[d[i]].fa] += sze[d[i]];
    // printf("%d %d\n", sam.a[i].len, sam.a[sam.a[i].fa].len);
    res += 1ll * (sam.a[d[i]].len - sam.a[sam.a[d[i]].fa].len) * sze[d[i]] *
           (n - sze[d[i]]);
  }
  return res;
}

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  sam.Build(s);
  printf("%lld\n", TopSort());
  return 0;
}

// eededeedeedeedde
// 1
// 1
// 1
// 1
// 1
// 1
// 1
// 1
// 1
// 2
// 1
// 2
// 1
// 2
// 1
// 3
// 3
// 3
// 4
// 4
// 4
// 5
// 5
// 10
// 6
// 16
// 2030
