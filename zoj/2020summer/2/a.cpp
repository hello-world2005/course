#include <algorithm>
#include <cstdio>

const int N = 1e6 + 10;

int a[N], b[N];
long long ans1[N], ans2[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), a[i] /= 100;
  for (int i = 1; i <= n; i++)
    scanf("%d", &b[i]);
  int p1, p2, p3;
  scanf("%d%d%d", &p1, &p2, &p3);
  ans1[1] = ans2[1] = a[1] * 100;
  for (int i = 2; i <= n; ++i) {
    ans1[i] = std::max(ans1[i - 1], std::max(ans1[i - 2], ans2[i - 2]) + a[i] * 100);
    ans2[i] = std::max(ans2[i - 1] + p3 * a[i],
                  std::max(ans1[i - 2], ans2[i - 2]) + a[i] * 100);
    if (b[i - 1] < b[i])
      ans2[i] = std::max(ans2[i], ans1[i - 1] + a[i] * 100),
      ans1[i] = std::max(ans1[i], ans2[i - 1] + a[i] * p1);
    else if (b[i - 1] > b[i])
      ans1[i] = std::max(ans1[i], ans2[i - 1] + a[i] * 100),
      ans2[i] = std::max(ans2[i], ans1[i - 1] + a[i] * p2);
    else
      ans2[i] = std::max(ans2[i], ans1[i - 1] + a[i] * 100),
      ans1[i] = std::max(ans1[i], ans2[i - 1] + a[i] * 100);
  }
  printf("%lld\n", std::max(ans1[n], ans2[n]));
  return 0;
}
