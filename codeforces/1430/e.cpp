#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 2e5 + 10;

int n;

char s[N], t[N];
int val[N];
int lnk[N];

#define LowBit(x) (x & -x)

void Add(int p, int v) {
	for (; p <= n; p += LowBit(p))
		val[p] += v;
}

long long Query(int p) {
	long long res = 0;
	for (; p >= 1; p -= LowBit(p))
		res += val[p];
	return res;
}

int Sum(int l, int r) {
	return Query(r) - Query(l - 1);
}

int main() {
	long long ans = 0;;
	scanf("%d%s", &n, s + 1);
	for (int i = 1; i <= n; ++i)
		t[i] = s[n - i + 1];
	int l = 1, r = 1;
	for (char i = 'a'; i <= 'z'; ++i, l = r = 1) {
		while (true) {
			while (l <= n && s[l] != i)
				++l;
			if (l > n)
				break;
			while (r <= n && t[r] != i)
				++r;
			if (l > n || r > n)
				break;
			lnk[l] = r;
//			printf("%d %d %c\n", l, r, i);
			++l, ++r;
		}
	}
	for (int i = 1; i <= n; ++i)
		ans += Sum(lnk[i] + 1, n), Add(lnk[i], 1);
	printf("%lld\n", ans);
	return 0;
}

//500
//pqmpmpqmppqqmmmqppqmpqqmmmppmmqmqmqpqmmpmmpmqpmqpppmppmqqmmmpmqqqppqpmpqpmppppqqqqpmppqppqpqmpmpmqqmmpmqmmpqqmqpmqpmpmqpmpmmqppmqmpqmmmmmmpmmqmmqmmqqmmqqpmppqmppmpppmmmmppmmpqqqqmppqqqqqmpqpmpqmmpqmqpqpmmqqqqpmqqqppmmppmppppppmmpmqpmqmpmqmmpqqmqqmpqppqpmqqmpqqmpmmmpqmqmqmpqmpppqqmqmpmqmmpqmpqqmmqqpqpqmmmqmmpmpmmpmqmpqpqpmppqqmpmpppmqpppmmpqpqqpqpmqmppmpqmpqmqpppqmpqppmmqmppmppqpmqpmmppqmpmmmqqmqqmmppppmpmqqqppqmmqpmppqppmmqpqpqqmmqmqpmqmqmqqqppmpqqmpmpqqpmmqqmpqppmmpqpqqmpqqmmpmmqpppmqmppqpmmmqm

