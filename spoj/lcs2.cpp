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

int maxn[N << 1], minn[N << 1];
int c[N << 1], d[N << 1];

void Lcs(char* s) {
  n = strlen(s + 1);
  int v = 1, l = 0;
  for (int i = 1; i <= n; ++i) {
    while (v && !sam.a[v].ch[s[i] - 'a']) {
      v = sam.a[v].fa;
      l = sam.a[v].len;
    }
    if (v) {
      ++l;
      v = sam.a[v].ch[s[i] - 'a'];
      maxn[v] = std::max(maxn[v], l);
    } else {
      // printf("qwq\n");
      v = 1;
      l = 0;
    }
  }
  // printf("%d %d\n", v, l);
  for (int i = sam.tot; i >= 1; --i) {
    int u = d[i], f = sam.a[u].fa;
    maxn[f] = std::max(maxn[f], std::min(maxn[u], sam.a[f].len));
    minn[u] = std::min(minn[u], maxn[u]);
    maxn[u] = 0;
  }
}

void Sort() {
  for (int i = 1; i <= sam.tot; ++i)
    ++c[sam.a[i].len];
  for (int i = 1; i <= sam.tot; ++i)
    c[i] += c[i - 1];
  for (int i = 1; i <= sam.tot; ++i)
    d[c[sam.a[i].len]--] = i;
}

int main() {
  scanf("%s", s + 1);
  sam.Build(s);
  memset(minn, 0x3f, sizeof(minn));
  Sort();
  while (scanf("%s", s + 1) == 1)
    Lcs(s);
  int ans = 0;
  for (int i = 1; i <= sam.tot; ++i)
    ans = std::max(ans, minn[i]);
  printf("%d\n", ans);
  return 0;
}
