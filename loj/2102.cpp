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
int c[N << 1], d[N << 1], v[N << 1], sum[N << 1];

void TopSort(int t) {
  for (int i = 1; i <= sam.tot; ++i)
    ++c[sam.a[i].len];
  for (int i = 1; i <= sam.tot; ++i)
    c[i] += c[i - 1];
  for (int i = sam.tot; i; --i)
    d[c[sam.a[i].len]--] = i;
  for (int i = 1; i <= sam.tot; ++i)
    v[i] = sam.a[i].sze;
  for (int i = sam.tot; i; --i)
    if (t)
      v[sam.a[d[i]].fa] += v[d[i]];
    else
      v[d[i]] = 1;
  v[1] = 0;
  for (int i = sam.tot; i; --i) {
    sum[d[i]] = v[d[i]];
    for (int j = 0; j < 26; ++j)
      sum[d[i]] += sum[sam.a[d[i]].ch[j]];
  }
}

void Print(int u, int k) {
  if (k > v[u]) {
    k -= v[u];
    for (int i = 0; i < 26; ++i)
      if (k <= sum[sam.a[u].ch[i]]) {
        printf("%c", i + 'a');
        Print(sam.a[u].ch[i], k);
        return;
      } else {
        k -= sum[sam.a[u].ch[i]];
      }
  }
}

int main() {
  scanf("%s", s + 1);
  sam.Build(s);
  int typ, k;
  scanf("%d%d", &typ, &k);
  TopSort(typ);
  if (k > sum[1])
    printf("-1\n");
  else
    Print(1, k);
  return 0;
}

// akvfeybuemcnruboflzplgsoqaxklypokmtrmunripgzjhnqtofevxvlzuxnsobeawvnqjeyakxkumcpaivxhskjmiygwzlxvimntsluekgywipyslwadglsqjynijmfsyulqhhurnvpyknqvlsbsdtkmrxwdldvl
// akvfeybuemcnruboflzplgsoqaxklypokmtrmunripgzjhnqtofevxvlzuxnsobeawvnqjeyakxkumcpaivxhskjmiygwzlxvimntsluekgywipyslwadglsqjynijmfsyulqhhurnvpyknqvlsbsdtkmrxwdldvl

