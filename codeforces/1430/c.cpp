#include <cstdio>
#include <cmath>
#include <set>
#include <vector>

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		std::multiset<int> s;
		for (int i = 1; i <= n; ++i)
			s.insert(i);
		std::vector<std::pair<int, int> > ans;
		for (int i = 1; i < n; ++i) {
			auto x = s.end();
			--x;
			int a = *x;
			s.erase(x);
			x = s.end();
			--x;
			int b = *x;
			s.erase(x);
			ans.push_back(std::make_pair(a, b));
			s.insert((int)ceil(1.0 * (a + b) / 2));
		}
		printf("%d\n", *s.begin());
		for (auto i : ans)
			printf("%d %d\n", i.first, i.second);
	}
	return 0;
}

