#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 10;

struct SuffixAutoMaton {
  struct Node {
    int ch[26];
    int len, fa;
    int sze;

    Node() : len(0) { memset(ch, 0, sizeof(ch)); }
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

char s1[N], s2[N];
int c[N << 1], d[N << 1];
int f[N << 1];

void TopSort() {
  for (int i = 1; i <= sam.tot; ++i)
    ++c[sam.a[i].len];
  for (int i = 1; i <= sam.tot; ++i)
    c[i] += c[i - 1];
  for (int i = 1; i <= sam.tot; ++i)
    d[c[sam.a[i].len]--] = i;
  for (int i = sam.tot; i >= 1; --i)
    sam.a[sam.a[d[i]].fa].sze += sam.a[d[i]].sze;
  for (int i = 2; i <= sam.tot; ++i)
    f[d[i]] = (sam.a[d[i]].len - sam.a[sam.a[d[i]].fa].len) * sam.a[d[i]].sze +
              f[sam.a[d[i]].fa];
}

typedef long long ll;

int main() {
  scanf("%s%s", s1 + 1, s2 + 1);
  sam.Build(s1);
  int n2 = strlen(s2 + 1);
  TopSort();
  ll ans = 0;
  for (int l = 0, r = 1, p = 1; r <= n2; ++r) {
    int c = s2[r] - 'a';
    while (p && !sam.a[p].ch[c])
      p = sam.a[p].fa;
    if (!p) {
      p = 1, l = 0;
#ifdef DEBUG
      printf("r: %d\n", r);
#endif
    } else {
      l = std::min(l, sam.a[p].len) + 1;
      p = sam.a[p].ch[c];
      ans += f[sam.a[p].fa] + (l - sam.a[sam.a[p].fa].len) * sam.a[p].sze;
#ifdef DEBUG
      printf("l: %d, p: %d\n", l, p);
#endif
    }
  }
  printf("%lld\n", ans);
  return 0;
}
