#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define dep(i,a,b) for(int i=(a);i>=(b);--i)
#define PB push_back
#define CL clear 
#define C 2730
#define S 5
#define int long long
using namespace std;
const int N = 100010;
inline int rd() {
  char ch = getchar(); int p = 0; int f = 1;
  while(ch<'0' || ch>'9'){if(ch=='-') f=-1; ch=getchar();}
  while(ch>='0' && ch<='9'){p=p*10+ch-'0'; ch=getchar();}
  return p*f;
}

int gcd(int a,int b){return (b==0) ? a : gcd(b,a%b);}
int mul(int a,int b,int mo) {
  return (a*b-(int)(a/(long double)mo*b+1e-3)*mo+mo)%mo;
}
int qpow(int a,int b,int mo) {
  int d = 1; a%=mo;
  while(b) {
    if(b&1) d=mul(d,a,mo);
    a=mul(a,a,mo);
    b>>=1;
	}return d;
}
bool check(int a,int mo) {
  int m = mo-1,x,y; int i,j=0;
  while(!(m&1)) m>>=1,j++;
  x=qpow(a,m,mo);
  for(i=1;i<=j;x=y,i++) {
    y=qpow(x,2,mo);
    if((y==1)&&(x!=1)&&(x!=mo-1)) return 1;
	}return y!=1;
}
bool miller_rabin(int times,int n) {
  int a;
  if(n==1) return 0;
  if(n==2) return 1;
  if(!(n&1)) return 0;
  while(times--) if(check(rand()%(n-1)+1,n)) return 0;
  return 1;
}
int pollard_rho(int n,int c) {
  int i=1,k=2,x=rand()%n,y=x,d;
  while(1) {
    i++,x=(mul(x,x,n)+c)%n,d=gcd(y-x,n);
    if(d>1&&d<n) return d;
    if(y==x) return n;
    if(i==k) y=x,k<<=1;
	}
}

vector<int> fac;

void findfac(int n,int c) {
  if(n==1) return ;
  if(miller_rabin(S,n)) {
  	fac.PB(n);
    return ;
	}
  int m = n;
  while(m==n) m=pollard_rho(n,c--);
  findfac(m,c),findfac(n/m,c);
}


int prime[N],pri; bool v[N]; int id[N],idx = 0;
void pre() {
  memset(v,1,sizeof(v)); v[1] = 0;
  pri = 0;
  for(int i=2;i<=(int)(1e5);i++) {
    if(v[i]) prime[++pri] = i;
    for(int j=1;j<=pri && (i*prime[j] <= (1e5));j++) {
      v[i*prime[j]] = 0;
      if(i%prime[j] == 0) break;
		}
  }
  for(int i=1;i<=(1e5);i++) if(v[i]) id[i] = ++idx;
//  for(int i=1;i<=pri;i++) printf("%d ",prime[i]);
//  printf("%d\n",pri);
}

int a[N]; vector<int> b[N]; int n,m;

void calc(int x) {
  b[x].CL();
	fac.CL(); findfac(a[x],C);
	b[x] = fac;
}

int tr[N]; int low_bit(int x){return x&(-x);}
void add(int x,int c){while(x<=n){tr[x]+=c; x+=low_bit(x);}}
int qry(int x){int s = 0; while(x>=1){s+=tr[x]; x-=low_bit(x);} return s;}

int lc[N<<2],rc[N<<2],tot=0,rt=0; bitset<9600>c[N<<2]; bool bo[N<<2];
void link(int &u,int L,int R,int k) {
  if(!u) u=++tot;
  if(L==R) {
  	c[u].reset(); bo[u] = 0;
    for(int i=0;i<b[k].size();i++) {
		  if(c[u][id[b[k][i]]]) bo[u] = 1;
			c[u].set(id[b[k][i]]);
		}
    return ;
  }
  int mid = (L+R)>>1;
  if(k<=mid) link(lc[u],L,mid,k);
  else link(rc[u],mid+1,R,k);
  bo[u] = bo[lc[u]] | bo[rc[u]];
  if((c[lc[u]] & c[rc[u]]).any()) bo[u] = 1;
  c[u] = c[lc[u]] | c[rc[u]];
}
bitset<9600> ans; bool boo = 0;
bool ask(int u,int L,int R,int l,int r) {
	if(boo) return 1;
  if(L==l && R==r) {
  	if(bo[u]) return boo = boo | bo[u];
  	if((ans & c[u]).any()){boo = 1; return 1;}
    ans |= c[u];
		return boo = boo | bo[u];
	}
	int mid = (L+R)>>1;
	if(r<=mid) return boo = boo | ask(lc[u],L,mid,l,r);
	else if(l>mid) return boo = boo | ask(rc[u],mid+1,R,l,r);
	else {
	  bool bo1 = ask(lc[u],L,mid,l,mid);
	  if(boo || bo1) return boo = 1;
		bool bo2 = ask(rc[u],mid+1,R,mid+1,r);
		return boo = boo | bo1 | bo2 ;
	}
}

signed main() {
	freopen("10.in","r",stdin);
	freopen("10.out","w",stdout);
	srand(time(0));
	pre();	
//	printf("%lld\n",pri);
	n = rd();  m = rd();
	rep(i,1,n) a[i] = rd(),calc(i),add(i,a[i]),link(rt,1,n,i);
	rep(i,1,m) {
	  int op = rd(); int l = rd(); int r = rd();
	  if(op == 1) {
	  	add(l,-a[l]);
	    a[l] = r; calc(l);
	    add(l,a[l]);
			link(rt,1,n,l);
		}
		else if(op==2) {
			fac.CL(); findfac(qry(r) - qry(l-1),C);
		  sort(fac.begin(),fac.end());
		  bool bk = 1;
		  rep(i,1,fac.size()-1) if(fac[i] == fac[i-1]){bk = 0; break;}
		  if(bk) printf("%lld\n",(fac.size() & 1ll) ? -1ll : 1ll);
		  else printf("0\n");
		}
		else {
			ans.reset(); boo = 0;
			bool bk = ask(rt,1,n,l,r);
			if(bk) printf("0\n");
			else printf("%lld\n",(ans.count() & 1ll) ? -1ll : 1ll);
		}
	}
  return 0;
} 