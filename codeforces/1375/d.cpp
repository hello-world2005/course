#include <bitset>
#include <cstdio>
#include <vector>

const int N = 3e3 + 10;

int a[N];

int Mex(int n) {
  std::bitset<N> vis;
  for (int i = 1; i <= n; ++i)
    vis[a[i]] = true;
  for (int i = 0; i <= n; ++i)
    if (!vis[i])
      return i;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    std::vector<int> ans;
    while (true) {
      int mex = Mex(n);
      // printf("%d\n", mex);
      if (mex == n) {
        a[n] = n;
        ans.push_back(n);
        --n;
        if (n <= 0)
          break;
      } else {
        a[mex + 1] = mex;
        ans.push_back(mex + 1);
      }
    }
    printf("%u\n", ans.size());
    for (auto i : ans)
      printf("%d ", i);
    printf("\n");
  }
  return 0;
}
