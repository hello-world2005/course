#include <algorithm>
#include <cstdio>

const int N = 2e5 + 10;

int a[N];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, k;
		scanf("%d%d", &n, &k);
		long long ans = 0;
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		std::sort(a + 1, a + n + 1);
		std::reverse(a + 1, a + n + 1);
		for (int i = 1; i <= std::min(n, k + 1); ++i)
			ans = ans + a[i];
		printf("%lld\n", ans);
	}
	return 0;
}

