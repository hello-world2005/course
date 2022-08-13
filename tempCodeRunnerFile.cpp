#include <cstdio>
const int N = 1e5 + 10;

bool vis[N];
int pri[N], cnt;
int phi[N];

void Sieve(int n) {
  for (int i = 2; i <= n; ++i) {
    if (!vis[i])
      pri[++cnt] = i, phi[i] = i - 1;
    for (int j = 1; j <= cnt && i * pri[j] <= n; ++j) {
      vis[i * pri[j]] = true;
      if (i % pri[j] == 0) {
        phi[i * pri[j]] = phi[i] * pri[j];
        break;
      }
      phi[i * pri[j]] = phi[i] * pri[pri[j]];
    }
  }
}

int main() {
    Sieve(N - 10);
    for (int i = 2; i <= cnt; ++i) printf("%d,", pri[i]);
    printf("\n");
    return 0;
}
