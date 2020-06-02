#include <cstdio>
#include <vector>

int a[10];

int main() {
  scanf("%d%d%d%d", &a[0], &a[1], &a[2], &a[3]);
  int sum = a[0] + a[1] + a[2] + a[3] - 1;
  for (int i = 0; i < 4; ++i)
    if (a[i]) {
      std::vector<int> res;
      int b[10] = {a[0], a[1], a[2], a[3]};
      --b[i];
      res.push_back(i);
      int lst = i;
      for (int j = 0; j < sum; ++j) {
        if (lst >= 1 && b[lst - 1]) {
          --b[lst - 1];
          res.push_back(lst - 1);
          --lst;
        } else if (b[lst + 1]) {
          --b[lst + 1];
          res.push_back(lst + 1);
          ++lst;
        } else {
          break;
        }
      }
      if ((int)res.size() == sum + 1) {
        printf("YES\n");
        for (auto j : res)
          printf("%d ", j);
        printf("\n");
        return 0;
      }
    }
  printf("NO\n");
  return 0;
}
