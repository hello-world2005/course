#include <cstdio>

const int N = 2e5 + 10;
const int K = 31;

int d[K];

bool Insert(int k) {
  for (int i = 30; i >= 0; --i)
    if (k >> i & 1) {
      if (!d[i]) {
        d[i] = k;
        return true;
      } else {
        k ^= d[i];
      }
    }
  return false;
}

int n;
int a[N], s[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), s[i] = a[i] ^ s[i - 1];
  if (!s[n]) {
    printf("-1\n");
    return 0;
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    if (Insert(a[i]))
      ++ans;
  printf("%d\n", ans);
  return 0;
}
