#include <algorithm>
#include <cstdio>
#include <unordered_map>

typedef long long ll;

const int N = 4e6 + 10;

int a[N];

int Gcd(int a, int b) {
  if (!b)
    return a;
  return Gcd(b, a % b);
}

ll ans[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  std::unordered_map<int, ll> g;
  for (int i = n; i >= 1; --i) {
    std::unordered_map<int, ll> f;
    ++f[a[i]];
    for (auto it = g.begin(); it != g.end(); ++it) {
      int x = Gcd(a[i], it->first);
      f[x] += it->second;
    }
    for (auto it = f.begin(); it != f.end(); ++it)
      ans[it->first] += it->second;
    std::swap(f, g);
  }
  int m;
  scanf("%d", &m);
  while (m--) {
    int x;
    scanf("%d", &x);
    printf("%lld\n", ans[x]);
  }
  return 0;
}
