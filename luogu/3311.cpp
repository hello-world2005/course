#include <cstdio>
#include <cstring>
#include <queue>

const int MOD = 1e9 + 7;
const int N = 1510;
const int M = 1510;

int len;
char n[N], s[M][N];
std::vector<int> v;

struct AcAutoMaton {
  int ch[N][10], ed[N], tot = 1;
  int fl[N];

  void Insert(char* s, int id) {
    int n = strlen(s + 1), now = 1;
    for (int i = 1; i <= n; ++i) {
      int u = s[i] - '0';
      if (!ch[now][u])
        ch[now][u] = ++tot;
      now = ch[now][u];
    }
    ed[now] = id;
  }

  // void Build() {
  //   std::queue<int> q;
  //   for (int i = 0; i < 10; ++i)
  //     if (ch[0][i])
  //       q.push(ch[0][i]);
  //   while (!q.empty()) {
  //     int u = q.front();
  //     q.pop();
  //     for (int i = 0; i < 10; ++i)
  //       if (ch[u][i]) {
  //         fl[ch[u][i]] = ch[fl[u]][i];
  //         q.push(ch[u][i]);
  //       } else {
  //         ch[u][i] = ch[fl[u]][i];
  //       }
  //   }
  // }

  int que[N];

  void Build() {
    for (int i = 0; i < 10; i++)
      ch[0][i] = 1;
    fl[1] = 0, que[1] = 1;
    for (int l = 1, r = 1; l <= r; l++) {
      int u = que[l];
      for (int i = 0; i < 10; i++) {
        if (!ch[u][i])
          ch[u][i] = ch[fl[u]][i];
        else {
          que[++r] = ch[u][i];
          fl[ch[u][i]] = ch[fl[u]][i];
        }
      }
    }
  }

  int f[N][N];

  int Dfs(int pos, int pre, bool lim, bool zero) {
    // printf("%d %d %d %d\n", pos, pre, lim, zero);
    if (pos > len)
      return f[pos][pre] = !zero;
    if (lim && ~f[pos][pre])
      return f[pos][pre];
    int _lim = lim ? 9 : n[pos] - '0', res = 0;
    for (int i = 0; i <= _lim; ++i)
      if (zero) {
        if (!ed[ch[1][i]])
          res = (res + Dfs(pos + 1, ch[1][i], lim || i != _lim, zero && !i)) %
                MOD;
      } else {
        if (!ed[ch[pre][i]])
          res = (res + Dfs(pos + 1, ch[pre][i], lim || i != _lim, false)) % MOD;
      }
    if (lim && !zero)
      f[pos][pre] = res;
    return res;
  }
} ac;

int main() {
  scanf("%s", n + 1);
  len = strlen(n + 1);
  int m;
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i)
    scanf("%s", s[i] + 1), ac.Insert(s[i], i);
  ac.Build();
  for (int i = 0; i <= ac.tot; ++i)
    ac.ed[ac.que[i]] = ac.ed[ac.que[i]] || ac.ed[ac.fl[ac.que[i]]];
  memset(ac.f, -1, sizeof(ac.f));
  printf("%d\n", ac.Dfs(1, 1, false, true));
  // for (int i = 0; i <= 10; ++i) {
  //   for (int j = 0; j < 10; ++j)
  //     printf("%d ", ac.f[i][j]);
  //   printf("\n");
  // }
  return 0;
}
