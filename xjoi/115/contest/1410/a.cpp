#include <cstdio>
#include <vector>
  
using namespace std;
  
const int N = 2010;
  
struct Edge {
    int u, v, nxt;
};
  
int n;
int w[N];
int head[N], cnt;
Edge e[N << 1];
int f[N][5];
  
void addedge(int u, int v) {
    e[++cnt].u =u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
  
void dfs(int u, int fa) {
    bool flag = false;
    int tmp = 0x3f3f3f3f;
    int sum1 = 0, sum2 = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa)
            continue;
        dfs(v, u);
        sum1 += min(f[v][0], min(f[v][1], f[v][2]));
        if (f[v][0] <= f[v][2]) {
            sum2 += f[v][0];
            flag = true;
        } else {
            sum2 += f[v][2];
            tmp = min(tmp, f[v][0] - f[v][2]);
        }
    }
    f[u][0] = sum1 + w[u];
    f[u][1] = sum2;
    f[u][2] = sum2;
    if (!flag)
        f[u][2] += tmp;
}
  
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int u, v, t;
        scanf("%d", &u);
        scanf("%d%d", &w[u], &t);
        for (int j = 1; j <= t; ++j) {
            scanf("%d", &v);
            addedge(u, v);
            addedge(v, u);
        }
        if (t == 0) {
            f[u][1] = 0;
            f[u][0] = f[u][2] = w[u];
        }
    }
    dfs(1, 0);
    printf("%d\n", min(f[1][0], f[1][2]));
    return 0;
}
