#include <cstdio>
#include <vector>

#define int long long

const int N = 1e6 + 10;

int n;
int a[N];
std::vector<int> div;
int sum;

signed main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]), sum += a[i];
  if (sum == 0) {
    printf("0\n");
    return 0;
  }
  if (sum == 1) {
    printf("-1\n");
    return 0;
  }
  
}
