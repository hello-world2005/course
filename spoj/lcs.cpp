#include <cstdio>
#include <cstring>

const int N = 250010;

int n, m;
char s1[N], s2[N];

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

void Lcs(char* s1, char* s2) {
  sam.Build(s1);
  n = strlen(s1 + 1), m = strlen(s2 + 1);
  int v = 1, l = 0, res = 0;
  for (int i = 1; i <= m; ++i) {
    while (v != 1 && !sam.a[v].ch[s2[i] - 'a']) {
      v = sam.a[v].fa;
      l = sam.a[v].len;
    }
    if (sam.a[v].ch[s2[i] - 'a']) {
      v = sam.a[v].ch[s2[i] - 'a'];
      ++l;
    }
    if (l > res)
      res = l;
  }
  printf("%d\n", res);
}

int main() {
  scanf("%s%s", s1 + 1, s2 + 1);
  Lcs(s1, s2);
  return 0;
}
