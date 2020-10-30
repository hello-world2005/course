#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e5 + 10;

char s[N];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		memset(s, 0, sizeof(s));
		scanf("%d%s", &n, s);
		std::queue<int> q;
		for (int i = 0, j = 0; i < n; ++i) {
			if (i > 0 && s[i] == s[i - 1])
				q.push(j);
			if (i > 0 && s[i] != s[i - 1])
				++j;
		}
		int cnt = 0, ans = 0;
		for (int i = 0; i < n; ++i) {
			if (q.empty())
				break;
			q.pop();
			++cnt, ++ans;
			while (!q.empty() && q.front() == i)
				q.pop(), ++cnt;
			++cnt;
		}
		printf("%d\n", ans + (n - cnt + 1) / 2);
	}
	return 0;
}

