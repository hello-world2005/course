// by George1123
#include <bits/stdc++.h>
using namespace std;

// Start
typedef long long ll;
typedef double db;
#define mp(a, b) make_pair(a, b)
#define x first
#define y second
#define be(a) a.begin()
#define en(a) a.end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;

// Data
const int N = 300;
int n, k, cmon, Map[N][N];
bool vis[N][N][10][32];
int fx[] = {-1, 1, 0, 0}, fy[] = {0, 0, -1, 1};
bool inmap(int x, int y) {
  return 0 <= x && x < n && 0 <= y && y < n;
}
struct S {
  int x, y, key, mon, step;
  friend bool operator==(S p, S q) {
    return p.x == q.x && p.y == q.y && p.key == q.key;
  }
} sta, exi;

// Main
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < n; j++) {
      if (s[j] == 'Q')
        Map[i][j] = 0, sta = (S){i, j, 0, 0, 0};
      else if (s[j] == 'T')
        Map[i][j] = 0, exi = (S){i, j, k, 0, 0};
      else if (s[j] == '#')
        Map[i][j] = -1;
      else if (isdigit(s[j]))
        Map[i][j] = s[j] - '0';
      else if (s[j] == 'M')
        Map[i][j] = k + (++cmon);
      else if (s[j] == '.')
        Map[i][j] = 0;
    }
  }
  queue<S> q;
  q.push(sta);
  vis[sta.x][sta.y][sta.key][sta.mon] = true;
  while (sz(q)) {
    S now = q.front();
    q.pop();
    // cout<<"now:"<<now.x<<' '<<now.y<<' '<<now.key<<' '<<now.mon<<'
    // '<<now.step<<'\n';
    if (now == exi)
      cout << now.step << '\n', exit(0);
    int kin = Map[now.x][now.y] - k - 1;
    if (kin >= 0 && !(now.mon >> kin & 1)) {
      S to = (S){now.x, now.y, now.key, now.mon | (1 << kin), now.step + 1};
      if (vis[to.x][to.y][to.key][to.mon])
        continue;
      vis[to.x][to.y][to.key][to.mon] = true;
      q.push(to);
    } else {
      for (int d = 0; d < 4; d++) {
        S to =
            (S){now.x + fx[d], now.y + fy[d], now.key, now.mon, now.step + 1};
        if (!inmap(to.x, to.y) || !~Map[to.x][to.y])
          continue;
        if (Map[to.x][to.y] >= 1 && Map[to.x][to.y] <= k) {
          if (Map[to.x][to.y] == to.key + 1)
            to.key++;
        }
        if (vis[to.x][to.y][to.key][to.mon])
          continue;
        vis[to.x][to.y][to.key][to.mon] = true;
        q.push(to);
      }
    }
  }
  cout << -1 << '\n';
  return 0;
}