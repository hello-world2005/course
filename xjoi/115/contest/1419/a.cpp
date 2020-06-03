#include <algorithm>
#include <cstdio>
#include <unordered_map>
#include <ctime>
#include <random>

char buf[1 << 21], *p1 = buf, *p2 = buf;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)

int Read() {
  int a = 0;
  char c = getchar();
  while (c < '0' || c > '9')
    c = getchar();
  while (c >= '0' && c <= '9')
    a = a * 10 + c - '0', c = getchar();
  return a;
}

const int N = 5e6 + 10;

struct Node {
  int a, b;

  bool operator<(const Node& rhs) const {
    return a < rhs.a;
  }
} a[N];

std::mt19937 rnd;
int rd;

struct CustomHash {
  int operator()(int hs) const {
    return hs + rd;
  }
};

int main() {
  int n;
  rnd.seed(time(NULL));
  for (int i = 1; i <= 100; ++i)
    rnd();
  rd = rnd();
  std::unordered_map<int, int, CustomHash> ma;
  n = Read();
  for (int i = 1; i <= n; ++i)
    ++ma[Read()];
  int cnt = 0;
  for (auto i : ma)
    a[++cnt].a = i.first, a[cnt].b = i.second;
  std::sort(a + 1, a + cnt + 1);
  for (int i = 1; i <= cnt; ++i)
    printf("%d %d\n", a[i].a, a[i].b);
  return 0;
}
