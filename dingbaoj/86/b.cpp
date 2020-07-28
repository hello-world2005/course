#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e5 + 10;

struct AcAutoMaton {
  int ch[N][26], ed[N], tot;
  int fl[N];

  void Insert(char *s, int id) {
    int n = strlen(s + 1), now = 0;
    for (int i = 1; i <= n; ++i) {
      int u = s[i] - 'A';
      if (!ch[now][u])
        ch[now][u] = ++tot;
      now = ch[now][u];
    }
    ed[now] = id;
  }

  void Build() {
    std::queue<int> q;
    for (int i = 0; i < 26; ++i)
      if (ch[0][i])
        q.push(ch[0][i]);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < 26; ++i)
        if (ch[u][i]) {
          fl[ch[u][i]] = ch[fl[u]][i];
          ed[ch[u][i]] |= ed[ch[fl[u]][i]];
          q.push(ch[u][i]);
        } else {
          ch[u][i] = ch[fl[u]][i];
        }
    }
  }
} at;

char s[70][110];

const int MOD = 1e4 + 7;

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = a * a % MOD)
    if (b & 1)
      res = res * a % MOD;
  return res;
}

int dp[110][N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%s", s[i] + 1), at.Insert(s[i], i);
  at.Build();
  dp[0][0] = 1;
  for (int i = 1; i <= m; ++i)
    for (int j = 0; j <= at.tot; ++j)
      for (int k = 0; k < 26; ++k)
        if (!at.ed[at.ch[j][k]])
          dp[i][at.ch[j][k]] = (dp[i][at.ch[j][k]] + dp[i - 1][j]) % MOD;
  int ans = FastPow(26, m);
  for (int i = 0; i <= at.tot; ++i)
    ans = (ans - dp[m][i]) % MOD;
  printf("%d\n", (ans + MOD) % MOD);
  return 0;
}
