#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

const int N = 3e4 + 10;

struct AcAutoMaton {
  int ch[N][2], ed[N], tot;
  int fl[N];

  void Insert(char* s, int id) {
    int n = strlen(s + 1), now = 0;
    for (int i = 1; i <= n; ++i) {
      int u = s[i] - '0';
      if (!ch[now][u])
        ch[now][u] = ++tot;
      now = ch[now][u];
    }
    ed[now] = id;
  }

  void Build() {
    std::queue<int> q;
    for (int i = 0; i <= 1; ++i)
      if (ch[0][i])
        q.push(ch[0][i]);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i <= 1; ++i)
        if (ch[u][i]) {
          fl[ch[u][i]] = ch[fl[u]][i];
          ed[ch[u][i]] |= ed[ch[fl[u]][i]];
          q.push(ch[u][i]);
        } else {
          ch[u][i] = ch[fl[u]][i];
        }
    }
  }

  bool vis[N], vis_inf[N];

  void Dfs(int u) {
    if (vis[u])
      printf("TAK\n"), exit(0);
    if (vis_inf[u] || ed[u])
      return;
    vis[u] = vis_inf[u] = true;
    for (int i = 0; i <= 1; ++i)
      Dfs(ch[u][i]);
    vis[u] = false;
  }
} ac;

char s[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s + 1);
    ac.Insert(s, i);
  }
  ac.Build();
  ac.Dfs(0);
  printf("NIE\n");
  return 0;
}
