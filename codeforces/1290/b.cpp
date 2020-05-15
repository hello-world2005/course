#include <cstdio>
#include <cstring>

const int N = 2e5 + 10;

int n, q;
char s[N];
int sum[N][26];

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < 26; ++j)
      sum[i][j] = sum[i - 1][j];
    ++sum[i][s[i] - 'a'];
  }
  scanf("%d", &q);
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    if (l == r) {
      printf("Yes\n");
      continue;
    }
    if (s[l] != s[r]) {
      printf("Yes\n");
      continue;
    }
    int cnt = 0;
    for (int i = 0; i < 26; ++i) {
      cnt += sum[r][i] > sum[l - 1][i] ? 1 : 0;
      if (sum[l - 1][i] == sum[r][i])
        continue;
    }
    printf("%s\n", cnt > 2 ? "Yes" : "No");
  }
  return 0;
}
