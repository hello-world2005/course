#include <cstdio>
#include <unordered_set>

typedef unsigned long long ull;

const int N = 2e5 + 10;

char s[N], t[N];
ull pre[N], suf[N];

int main() {
  int T;
  scanf("%d", &T);
  std::unordered_set<ull> has;
  while (T--) {
    has.clear();
    int n, m;
    scanf("%d", &n), m = n, ++n;
    scanf("%s%s", s + 1, t + 1);
    bool flag = false;
    const ull BASE = 631;
    pre[0] = 26324, suf[m + 1] = 765;
    for (int i = 1; i <= m; ++i)
      pre[i] = pre[i - 1] * BASE + t[i];
    for (int i = m; i >= 1; --i)
      suf[i] = suf[i + 1] * BASE + t[i];
    for (int i = 1; i <= m; ++i) {
      has.insert(pre[i] + suf[i + 1]);
      printf("> %llu\n", pre[i] + suf[i + 1]);
    }
    suf[n + 1] = suf[m + 1];
    for (int i = 1; i <= n; ++i)
      pre[i] = pre[i - 1] * BASE + s[i];
    for (int i = n; i >= 1; --i)
      suf[i] = suf[i + 1] + BASE + s[i];
    for (int i = 1; i <= n; ++i)
      if (has.find(pre[i - 1] + suf[i + 1]) != has.end()) {
        flag = true;
        break;
      } else {
        printf("%llu\n", pre[i - 1] * suf[i + 1]);
      }
    printf("%s\n", flag ? "YES" : "NO");
  }
  return 0;
}
