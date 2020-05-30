#include <cstdio>
#include <deque>
 
const int N = 3010;
 
int n;
int a[N];
int sum[N];
int f[N], h[N];
 
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    sum[i] = sum[i - 1] + a[i];
  }
  std::deque<int> q;
  q.push_back(0);
  for (int i = 1; i <= n; ++i) {
    while (q.size() > 1 && h[q[1]] + sum[q[1]] <= sum[i])
      q.pop_front();
    // printf("%d\n", q.front());
    f[i] = f[q.front()] + i - q.front() - 1;
    h[i] = sum[i] - sum[q.front()];
    while (q.size() && h[q.back()] + sum[q.back()] >= sum[i] + h[i])
      q.pop_back();
    q.push_back(i);
  }
  printf("%d\n", f[n]);
  return 0;
}
