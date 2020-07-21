#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 3e5 + 10;
const int INF = 0x3f3f3f3f;

int a[N];

struct LeftistTree {
  int ch[N][2], fa[N], fa2[N], dis[N];
  int v[N], tag[N];
  int rt, cnt;

  void Init() {
    memset(ch, 0, sizeof(ch));
    memset(dis, 0, sizeof(dis));
    memset(v, 0, sizeof(v));
    memset(tag, 0, sizeof(tag));
    rt = cnt = 0;
  }

  void PushDown(int x) {
    if (tag[x]) {
      if (ch[x][0])
        v[ch[x][0]] += tag[x], tag[ch[x][0]] += tag[x];
      if (ch[x][1])
        v[ch[x][1]] += tag[x], tag[ch[x][1]] += tag[x];
      tag[x] = 0;
    }
  }

  int Merge(int x, int y) {
    if (!x || !y)
      return x + y;
    if (v[x] < v[y] || (v[x] == v[y] && x > y))
      std::swap(x, y);
    PushDown(x);
    ch[x][1] = Merge(ch[x][1], y);
    fa[ch[x][1]] = fa2[ch[x][1]] = x;
    if (dis[ch[x][0]] < dis[ch[x][1]])
      std::swap(ch[x][0], ch[x][1]);
    dis[x] = (ch[x][1] == 0 ? 0 : dis[ch[x][1]] + 1);
    return x;
  }

  int Push(int x, int val) {
    ch[++cnt][0] = ch[cnt][1] = dis[cnt] = 0;
    fa[cnt] = fa2[cnt] = cnt;
    return Merge(x, cnt);
  }

  int Top(int x) { return v[rt]; }

  int Pop(int x) {
    PushDown(x);
    int lc = ch[x][0], rc = ch[x][1];
    ch[x][0] = ch[x][1] = dis[x] = 0, v[x] = -INF;
    fa[lc] = fa2[lc] = lc, fa[rc] = fa2[rc] = rc;
    return fa[x] = Merge(lc, rc);
  }

  int Find(int x) {
    if (fa[x] == x)
      return x;
    return fa[x] = Find(fa[x]);
  }

  int Get(int x) {
    int res = v[x];
    while (x != fa2[x])
      x = fa2[x], res += tag[x];
    printf("> %d\n", res);
    return res;
  }

  int Del(int x) {
    if (fa2[x] == x)
      return Pop(x);
    int t = Find(x);
    PushDown(x);
    int f2 = fa2[x];
    int _rt = Merge(ch[x][0], ch[x][1]);
    fa[_rt] = fa2[_rt] = f2;
    // ch[f2][ch[f2][1] == x] = _rt;
    if (ch[f2][0] == x)
      ch[f2][0] = _rt;
    else
      ch[f2][1] = _rt;
    ch[x][0] = ch[x][1] = dis[x] = 0;
    while (f2 != fa2[f2]) {
      if (dis[ch[f2][0]] < dis[ch[f2][1]])
        std::swap(ch[f2][0], ch[f2][1]);
      if (dis[f2] == dis[ch[f2][1]] + 1)
        return t;
      dis[f2] = dis[ch[f2][1]] + 1;
      f2 = fa2[f2];
    }
    return t;
  }

  int Build(int n) {
    std::queue<int> q;
    for (int i = 1; i <= n; ++i)
      q.push(i);
    while (!q.empty()) {
      if (q.size() == 1)
        break;
      int x = q.front();
      q.pop();
      int y = q.front();
      q.pop();
      q.push(Merge(x, y));
    }
    return q.front();
  }
} lt1, lt2;

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    lt1.v[i] = lt2.v[i] = a[i];
    lt1.fa[i] = lt1.fa2[i] = lt2.fa[i] = lt2.fa2[i] = i;
  }
  lt1.cnt = lt2.cnt = 2;
  int rt = lt2.Build(n);
  int tag = 0;
  int q;
  scanf("%d", &q);
  while (q--) {
    char opt[10];
    int x, y;
    scanf("%s", opt);
    if (opt[0] == 'U') {
      scanf("%d%d", &x, &y);
      x = lt1.Find(x), y = lt2.Find(y);
      if (x != y)
        rt = lt2.Del(lt1.Merge(x, y) == x ? y : x);
    } else if (opt[0] == 'A') {
      if (opt[1] == '1') {
        scanf("%d%d", &x, &y);
        int t = lt1.Get(x) + y;
        int x1 = lt1.Find(x), t1 = lt1.Del(x);
        lt1.v[x] = t, lt1.fa[x] = lt1.fa2[x] = x;
        x = lt1.Merge(x, t1);
        rt = lt2.Del(x1);
        lt2.v[x] = lt1.v[x], lt2.fa[x] = lt2.fa2[x] = x;
        rt = lt2.Merge(rt, x);
      } else if (opt[1] == '2') {
        scanf("%d%d", &x, &y);
        x = lt1.Find(x);
        lt1.v[x] += y, lt1.tag[x] += y;
        printf("x: %d\n", x);
        rt = lt2.Del(x);
        lt2.v[x] = lt1.v[x], lt2.fa[x] = lt2.fa2[x] = x;
        rt = lt2.Merge(rt, x);
        printf("%d\n", rt);
      } else {
        scanf("%d", &x);
        tag += x;
      }
    } else {
      if (opt[1] == '1') {
        scanf("%d", &x);
        printf("%d\n", lt1.Get(x) + tag);
      } else if (opt[1] == '2') {
        scanf("%d", &x);
        x = lt1.Find(x);
        printf("%d\n", lt1.v[x] + tag);
      } else {
        printf("%d\n", lt2.v[rt] + tag);
      }
    }
  }
  return 0;
}
