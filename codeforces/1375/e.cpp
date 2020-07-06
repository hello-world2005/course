#include <algorithm>
#include <cstdio>
#include <vector>
#include <numeric>

const int N = 1e3 + 10;

int a[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  std::vector<int> o(n + 1);
  std::iota(o.begin(), o.end(), 1);
  std::sort(o.begin(), o.end(),
       [&](int p, int q) { return a[p] == a[q] ? p < q : a[p] < a[q]; });
  std::vector<std::pair<int, int> > ans;
  for (int i = 1; i <= n; ++i)
    for (int j = 2; j <= n; ++j)
      if (o[j - 1] > o[j])
        ans.push_back(std::make_pair(o[j - 1], o[j])), std::swap(o[j - 1], o[j]);
  printf("%u\n", ans.size());
  for (auto i : ans)
    printf("%d %d\n", i.second, i.first);
  return 0;
}
