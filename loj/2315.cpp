#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int T, s[1005], n, m, t, now, ans, f;
bool vis[1005], pos[1005], wa;
char a[105], b[105], c[105], d[105];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, a);
    m = 0;
    ans = 0;
    now = 0;
    t = 0;
    wa = 0;
    f = 0;
    memset(vis, 0, sizeof(vis));
    memset(pos, 0, sizeof(pos));
    for (int i = 4; i < strlen(a); ++i)
      if (a[i] >= '0' && a[i] <= '9')
        m = m * 10 + a[i] - 48;
    while (n--) {
      scanf("%s", a);
      if (a[0] == 'F') {
        scanf("%s", b);
        t++;
        if (!vis[b[0]]) {
          vis[b[0]] = 1;
          s[t] = b[0];
        } else
          wa = 1;
        scanf("%s%s", &c, &d);
        if (c[0] != 'n' && d[0] == 'n' && !f)
          now++, pos[t] = 1;
        else if (((strlen(c) > strlen(d)) || (strlen(c) == strlen(d) && strcmp(c, d) > 0) || (c[0] == 'n' && d[0] != 'n')) && !f)
          f = t;
      } else {
        ans = max(ans, now);
        vis[s[t]] = 0;
        if (pos[t])
          now--, pos[t] = 0;
        t--;
        if (f > t)
          f = 0;
      }
    }
    if (wa)
      puts("ERR");
    else if (t != 0)
      puts("ERR");
    else if (ans == m)
      puts("Yes");
    else
      puts("No");
  }
}