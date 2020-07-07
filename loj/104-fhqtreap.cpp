#include <cstdio>
#include <cstdlib>

const int N = 1e5 + 10;

struct FhqTreap {
  struct Node {
    int val, rnd;
    int sze;
    int ch[2];

    Node() : val(0), rnd(rand()), sze(0) { ch[0] = ch[1] = 0; }
    Node(int _val) : val(_val), rnd(rand()), sze(1) { ch[0] = ch[1] = 0; }
  } t[N];
  int cnt;

#define lc(rt) t[rt].ch[0]
#define rc(rt) t[rt].ch[1]

  int NewNode(int val) {
    t[++cnt] = Node(val);
    return cnt;
  }

  void PushUp(int rt) { t[rt].sze = t[lc(rt)].sze + t[rc(rt)].sze + 1; }

  void Split(int rt, int v, int& rt1, int& rt2) {
    if (!rt) {
      rt1 = rt2 = 0;
      return;
    }
    if (t[rt].val <= v) {
      rt1 = rt;
      Split(rc(rt), v, rc(rt), rt2);
    } else {
      rt2 = rt;
      Split(lc(rt), v, rt1, lc(rt));
    }
    PushUp(rt);
  }

  int Merge(int rt1, int rt2) {
    if (!rt1 || !rt2)
      return rt1 + rt2;
    if (t[rt1].rnd < t[rt2].rnd) {
      rc(rt1) = Merge(rc(rt1), rt2);
      PushUp(rt1);
      return rt1;
    } else {
      lc(rt2) = Merge(rt1, lc(rt2));
      PushUp(rt2);
      return rt2;
    }
  }

  void Insert(int& rt, int v) {
    int rt1, rt2;
    Split(rt, v, rt1, rt2);
    rt = Merge(Merge(rt1, NewNode(v)), rt2);
  }

  void Delete(int& rt, int v) {
    int rt1, rt2, rt3;
    Split(rt, v, rt1, rt3);
    Split(rt1, v - 1, rt1, rt2);
    rt2 = Merge(lc(rt2), rc(rt2));
    rt = Merge(Merge(rt1, rt2), rt3);
  }

  int Kth(int rt, int k) {
    // printf("%d %d\n", rt, k);
    while (true) {
      // printf("%d %d %d %d\n", rt, t[rt].sze, t[lc(rt)].sze, k);
      if (t[lc(rt)].sze + 1 == k)
        return t[rt].val;
      if (t[lc(rt)].sze >= k)
        rt = lc(rt);
      else
        k -= t[lc(rt)].sze + 1, rt = rc(rt);
    }
  }

  int Rank(int& rt, int v) {
    int rt1, rt2;
    Split(rt, v - 1, rt1, rt2);
    int res = t[rt1].sze + 1;
    rt = Merge(rt1, rt2);
    return res;
  }

  int Pre(int rt, int v) {
    int rt1, rt2;
    Split(rt, v - 1, rt1, rt2);
    int res = Kth(rt1, t[rt1].sze);
    // printf("qwq\n");
    rt = Merge(rt1, rt2);
    return res;
  }

  int Nxt(int rt, int v) {
    int rt1, rt2;
    Split(rt, v, rt1, rt2);
    int res = Kth(rt2, 1);
    rt = Merge(rt1, rt2);
    return res;
  }
  
#undef lc
#undef rc 
} fhq;

int main() {
	int n;
	scanf("%d", &n);
	int rt = 0;
	while (n--) {
    // printf("%d\n", fhq.t[0].sze);
		int opt, x;
		scanf("%d%d", &opt, &x);
		if (opt == 1) {
			fhq.Insert(rt, x);
		} else if (opt == 2) {
			fhq.Delete(rt, x);
		} else if (opt == 3) {
			printf("%d\n", fhq.Rank(rt, x));
		} else if (opt == 4) {
			printf("%d\n", fhq.Kth(rt, x));
		} else if (opt == 5) {
			printf("%d\n", fhq.Pre(rt, x));
		} else {
			printf("%d\n", fhq.Nxt(rt, x));
		}
	}
	return 0;
}
