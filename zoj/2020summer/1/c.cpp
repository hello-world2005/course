#include <algorithm>
#include <bitset>
#include <cstdio>
#include <unordered_set>
#include <unordered_map>

const int N = 120000;

int n, m;
std::unordered_set<int> e[N];
std::unordered_map<int, int> lnk;
int cnt;
std::bitset<N> bs[400];

int main() {
  scanf("%d%d", &n, &m);
  while (m--) {
    int opt, u, v;
    scanf("%d%d%d", &opt, &u, &v);
    if (opt == 1) {
      e[u].insert(v), e[v].insert(u);
      if (e[u].size() >= 350) {
        if (!lnk[u]) {
          lnk[u] = ++cnt;
          for (auto i : e[u])
            bs[cnt][i] = true;
        } else {
          bs[lnk[u]][v] = true;
        }
      }
      if (e[v].size() >= 350) {
        if (!lnk[v]) {
          lnk[v] = ++cnt;
          for (auto i : e[v])
            bs[cnt][i] = true;
        } else {
          bs[lnk[v]][u] = true;
        }
      }
    } else {
      if (e[u].find(v) != e[u].end()) {
        printf("No\n");
      } else {
        if (e[u].size() > e[v].size())
          std::swap(u, v);
        if (e[u].size() < 350) {
          for (auto i : e[u])
            if (e[v].find(i) != e[v].end()) {
              printf("Yes\n");
              goto ed;
            }
          printf("No\n");
        ed:;
        } else {
          if ((bs[lnk[u]] & bs[lnk[v]]).count())
            printf("Yes\n");
          else
            printf("No\n");
        }
      }
    }
  }
  return 0;
}
