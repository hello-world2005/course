#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 250010;

int n, m;
char s[N];

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

int maxn[N << 1];

void Lcs(char* s) {
  n = strlen(s + 1);
  int v = 1, l = 0;
  for (int i = 1; i <= n; ++i) {
    if (v != 1 && sam.a[v].ch[s[i] - 'a']) {
      v = sam.a[v].fa;
      l = sam.a[v].len;
    }
    if (v != 1) {
      v = sam.a[v].fa;
      ++l;
      maxn[v] = std::max(maxn[v], l);
    } else {
      v = 1;
      l = 0;
    }
  }
}

int main() {
  scanf("%s", s + 1);
  sam.Build(s);
  while (scanf("%s", s + 1) == 1) {}
  return 0;
}
