#include <cstdio>
#include <cstring>
#include <queue>

const int N = (1e6 + 10);

int ans[N];

struct AhoCorasickAutoMaton {
  int ch[N][26], sze[N], sm[N], a[N], tot;
  int fl[N];
  bool vis[N];

  void Insert(char* s, int id) {
    int n = strlen(s + 1), now = 0;
    for (int i = 1; i <= n; ++i) {
      int u = s[i] - 'a';
      if (!ch[now][u])
        ch[now][u] = ++tot;
      now = ch[now][u];
      ++sze[now];
      ++ans[now];
    }
    a[id] = now;
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
          q.push(ch[u][i]);
        } else {
          ch[u][i] = ch[fl[u]][i];
        }
    }
  }
} at;

char s[210][N];
std::vector<int> e[N];

void Dfs(int u) {
  for (auto v : e[u])
    Dfs(v), ans[u] += ans[v];
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s[i] + 1);
    at.Insert(s[i], i);
  }
  at.Build();
  for (int i = 1; i <= at.tot; ++i)
    e[at.fl[i]].push_back(i);
  Dfs(0);
  for (int i = 1; i <= n; ++i)
    printf("%d\n", ans[at.a[i]]);
  return 0;
}
