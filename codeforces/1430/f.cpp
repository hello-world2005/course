#include <algorithm>
#include <cstdio>
#include <cstring>

#define int long long

const int N = 2010;

int l[N], r[N], a[N];
int dp[N];

signed main() {
	int n, k;
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%lld%lld%lld", &l[i], &r[i], &a[i]);
	memset(dp, 0x3f, sizeof(dp));
	dp[1] = 0;
	int ans = dp[n + 1];
	for (int i = 1; i <= n; ++i) {
		int remained = k, sum = dp[i];
		for (int j = i; j <= n; ++j) {
			int needed = (std::max(0ll, a[j] - remained) + k - 1) / k;
			if (needed > r[j] - l[j])
				break;
			int remain = (remained + needed * k) - a[j];
			sum += a[j];
			if (j + 1 <= n) {
				if(l[j] + needed < l[j + 1])
					dp[j + 1] = std::min(dp[j + 1], sum + remain);
			} else {
//				printf("%lld %lld %lld %lld\n", i, j, sum, ans);
				ans = std::min(ans, sum);
			}
			remained = remain;
		}
	}
	printf("%lld\n", ans > dp[n + 1] / 2 ? -1 : ans);
	return 0;
}

