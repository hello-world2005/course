#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

#define int long long

const int N = 1e6 + 10;

std::string name[N];

struct FhqTreap {
  struct Node {
    int val;
    int rnd;
    int sze;
    int ch[2];

    Node() : val(0), rnd(rand()), sze(0) { ch[0] = ch[1] = 0; }
    Node(int _val) : val(_val), rnd(rand()), sze(1) { ch[0] = ch[1] = 0; }
  } t[N];
  int cnt;

#define lc(rt) t[rt].ch[0]
#define rc(rt) t[rt].ch[1]

  int NewNode(int val, std::string na) {
    t[++cnt] = Node(val);
    name[cnt] = na;
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

  void Insert(int& rt, int v, std::string na) {
    int rt1, rt2;
    Split(rt, v, rt1, rt2);
    rt = Merge(Merge(rt1, NewNode(v, na)), rt2);
  }

  void Delete(int& rt, int v) {
    int rt1, rt2, rt3;
    Split(rt, v, rt1, rt3);
    Split(rt1, v - 1, rt1, rt2);
    rt2 = Merge(lc(rt2), rc(rt2));
    rt = Merge(Merge(rt1, rt2), rt3);
  }

  int Kth(int rt, int k) {
    // printf("%lld %lld\n", rt, k);
    while (true) {
      // printf("%lld %lld %lld %lld\n", rt, t[rt].sze, t[lc(rt)].sze, k);
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

#undef lc
#undef rc
} fhq;

int rt, tot;

std::map<std::string, int> name_to_id;

void Erase(int val) {
  fhq.Delete(rt, val);
}

void Insert(std::string name, int val, int tim) {
  val *= -1;
  if (!name_to_id[name])
    name_to_id[name] = val * N + tim, ++tot;
  else
    Erase(name_to_id[name]), name_to_id[name] = val * N + tim;
  fhq.Insert(rt, val * N + tim, name);
}

void Print(int u) {
  if (!u)
    return;
  Print(fhq.t[u].ch[0]);
  for (int i = 1; i < (int)name[u].size(); ++i)
    printf("%c", name[u][i]);
  printf(" ");
  Print(fhq.t[u].ch[1]);
}

void Ask(std::string s) {
  int x = 0, y, k1, k2;
  for (int i = 1; i < (int)s.size(); i++)
    x = x * 10 + s[i] - 48;
  y = std::min(x + 9, tot);
  k1 = fhq.Kth(rt, x);
  k2 = fhq.Kth(rt, y);
  int rt1, rt2, rt3;
  fhq.Split(rt, k2, rt1, rt3);
  fhq.Split(rt1, k1 - 1, rt1, rt2);
  Print(rt2);
  rt = fhq.Merge(fhq.Merge(rt1, rt2), rt3);
  printf("\n");
}

signed main() {
  int n, cnt = 0;
  scanf("%lld", &n);
  for (int i = 1; i <=n; ++i) {
    char c[20];
    scanf("%s", c);
    if (c[0] == '+') {
      int x;
      scanf("%lld", &x);
      Insert(c, x, i);
    } else if (c[1] >= '0' && c[1] <= '9') {
      Ask(c);
    } else {
      c[0] = '+';
      int x = name_to_id[c];
      printf("%lld\n", fhq.Rank(rt, x));
    }
  }
  return 0;
}
