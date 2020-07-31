#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<math.h>
#define re register int
#define rl register ll
#define lc rt<<1
#define rc rt<<1|1
using namespace std;
typedef long long ll;
int read() {
	re x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9') {
		if(ch=='-')	f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9') {
		x=10*x+ch-'0';
		ch=getchar();
	}
	return x*f;
}
const int Size=1000005;
ll n,q,dp[Size],s[Size],k[Size];
int hd,tl,Queue[Size];
inline double slope(int i,int j) {
	return (s[j]-s[i])/(j-i);
}
int cnt,maxd,head[Size],deep[Size],num[Size];
struct Edge {
	int v,next;
} w[Size<<1];
void AddEdge(int u,int v) {
	w[++cnt].v=v;
	w[cnt].next=head[u];
	head[u]=cnt;
}
void dfs(int x,int fa) {
	deep[x]=deep[fa]+1;
	if(deep[x]>maxd) {
		maxd=deep[x];
	}
	num[deep[x]]++;
	for(int i=head[x]; i; i=w[i].next) {
		dfs(w[i].v,x);
	}
}
int main() {
	n=read();
	q=read();
	int maxk=0;
	for(re i=1; i<=q; i++) {
		k[i]=read();
		if(k[i]>maxk)	maxk=k[i];
	}
	for(re i=2; i<=n; i++) {
		int f=read();
		AddEdge(f,i);
	}
	dfs(1,0);
	for(re i=maxd; i; i--) {
		s[i]=s[i+1]+num[i+1];
	}
	hd=tl=0;
	for(re i=1; i<=maxd; i++) {
		while(hd<tl && slope(Queue[tl],i)>=slope(Queue[tl-1],Queue[tl]))	tl--;
		Queue[++tl]=i;
	}
	for(rl i=1; i<=maxk; i++) {
		while(hd<tl && i*Queue[hd+1]+s[Queue[hd+1]]>=i*Queue[hd]+s[Queue[hd]])	hd++;
		dp[i]=Queue[hd]+ceil(1.0*s[Queue[hd]]/i);
	}
	for(re i=1; i<=q; i++) {
		printf("%lld ",dp[k[i]]);
	}
  printf("\n");
	return 0;
}