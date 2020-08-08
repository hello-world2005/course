#include <algorithm>
#include <cstdio>
#include <unordered_map>
#include <vector>

namespace Subtask1 {
// $n \le 100$
// 30pts

typedef std::vector<int> Equi;

void Main(int n, int k, int q) {
  std::vector<Equi> vec(k + 1);
  for (int i = 1; i <= k; ++i) {
    vec[i].resize(n);
    for (int j = 0; j < n; ++j)
      scanf("%d", &vec[i][j]);
  }
  while (q--) {
    int opt, x, y;
    scanf("%d%d%d", &opt, &x, &y);
    if (opt == 1) {
      Equi now(n);
      for (int i = 0; i < n; ++i)
        now[i] = std::max(vec[x][i], vec[y][i]);
      vec.push_back(now);
    } else if (opt == 2) {
      Equi now(n);
      for (int i = 0; i < n; ++i)
        now[i] = std::min(vec[x][i], vec[y][i]);
      vec.push_back(now);
    } else {
      printf("%d\n", vec[x][y - 1]);
    }
  }
}
}  // namespace Subtask1

namespace Subtask2 {
// $n \le 10^5, no operation 2$
// 20pts

typedef std::vector<int> Equi;
typedef int Mask;

void Main(int n, int k, int q) {
  std::vector<Equi> vec(k);
  for (int i = 0; i < k; ++i) {
    vec[i].resize(n);
    for (int j = 0; j < n; ++j)
      scanf("%d", &vec[i][j]);
  }
  std::vector<Mask> mask(k);
  for (int i = 0; i < k; ++i)
    mask[i] = (1 << i);
  while (q--) {
    int opt, x, y;
    scanf("%d%d%d", &opt, &x, &y);
    if (opt == 1) {
      mask.push_back(mask[x - 1] | mask[y - 1]);
    } else {
      int now = mask[x - 1], ans = 0;
      for (int i = 0; i < k; ++i)
        if (now >> i & 1)
          ans = std::max(ans, vec[i][y - 1]);
      printf("%d\n", ans);
    }
  }
}
/*
3 3 7
1 6 9
3 5 1
8 7 2
1 1 2
1 4 3
1 5 1
1 6 6
3 5 2
3 4 3
3 7 1
*/
}  // namespace Subtask2

int main() {
  int n, k, q;
  scanf("%d%d%d", &n, &k, &q);
  if (n <= 100)
    Subtask1::Main(n, k, q);
  else
    Subtask2::Main(n, k, q);
  return 0;
}
