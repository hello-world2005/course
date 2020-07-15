#include <cstdio>
#include <set>

const int N = 120000;

int n, m;
struct Edge {
  int u, v, idx;

  Edge() : u(0), v(0), idx(0) {}
  Edge(int _u, int _v, int _idx) : u(_u), v(_v), idx(_idx) {}
} e[N];
struct Question {
  int u, v, idx;

  Question() : u(0), v(0) {}
  Question(int _u, int _v, int _idx) : u(_u), v(_v), idx(_idx) {}
} q[N];
std::set<Question> s;
int e_cnt, q_cnt;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, opt, u, v; i <= m; ++i) {
    scanf("%d%d%d", &opt, &u, &v);
    if(opt == 1)
      e[++e_cnt] = Edge(u, v, i);
    else
      q[++q_cnt] = Question(u, v, i);
  }
  for (int i = 1; i <= q_cnt; ++i)
    s.insert(q[i]);
  for (int i = 1; i <= e_cnt; ++i) {}
}
