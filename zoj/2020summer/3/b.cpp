#include <cstdio>
#include <cstring>

const int N = 1e5 + 10;

char s[N];
int nxt[26], fl[30], f[N];

int main() {
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  for (int i = n - 1; i >= 0; --i) {
    nxt[s[i + 1] - 'A'] = i + 1;
    for (int c = 0; c < 26; ++c)
      if (nxt[c])
        fl[f[nxt[c]]] = i;
    int cur = -1;
    while (fl[cur + 1] == i)
      ++cur;
    f[i] = cur + 1;
  }
  printf("%s", f[0] ? "Alif" : "yww");
  return 0;
}
