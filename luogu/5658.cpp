#include <cstdio>
#include <stack>

#define int long long

const int N = 5e5 + 10;

char s[N];
struct Edge {
  int v, nxt;

  Edge()
      : v(0), nxt(0) {}
  Edge(int _v, int _nxt)
      : v(_v), nxt(_nxt) {}
} e[N];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int fa[N];
int qwq[N], dp[N];

std::stack<int> st;

void Dfs(int u) {
  int flag = 0;
  if (s[u] == ')') {
    if (!st.empty()) {
      flag = st.top();
      st.pop();
      qwq[u] = qwq[fa[flag]] + 1;
    }
  } else if (s[u] == '(') {
    st.push(u);
  }
  dp[u] = dp[fa[u]] + qwq[u];
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    Dfs(v);
  }
  if (flag)
    st.push(flag);
  else if (!st.empty())
    st.pop();
}

signed main() {
  int n;
  scanf("%lld%s", &n, s + 1);
  for (int i = 2, p; i <= n; ++i) {
    scanf("%lld", &p);
    AddEdge(p, i), fa[i] = p;
  }
  Dfs(1);
  long long ans = 0;
  for (int i = 1; i <= n; ++i)
    ans ^= 1ll * i * dp[i];
  printf("%lld\n", ans);
  return 0;
}
