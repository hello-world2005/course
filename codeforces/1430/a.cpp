#include <cstdio>

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i * 3 <= n; ++i)
			for (int j = 0; j * 5 <= n; ++j) {
				if ((n - i * 3 - j * 5) % 7 == 0) {
					int k = (n - i * 3 - j * 5) / 7;
					printf("%d %d %d\n", i, j, k);
					goto ed;
				}
			}
		printf("-1\n");
		ed:;
	}
	return 0;
}

