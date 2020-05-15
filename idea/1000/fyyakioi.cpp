#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
#define int long long
#define N 300005
int ch[N][2],le[N][2],ri[N],d[N],val[N],sum[N],add[N],mul[N],mov[N],pri[N],len[N],sz;
const int mod=1e6+3;
inline int ne(int l0,int r,int l1,int di){
	pri[++sz]=rand(),mul[sz]=1;
	le[sz][0]=l0,le[sz][1]=l1,len[sz]=r-l0+1,ri[sz]=r,d[sz]=di,
	sum[sz]=val[sz]=(((l1<<1)+(r-l0)*di)*(r-l0+1)>>1)%mod;
	return sz;
}
inline void update(int now){
	len[now]=ri[now]-le[now][0]+1+len[ch[now][0]]+len[ch[now][1]];
	sum[now]=(val[now]+sum[ch[now][0]]+sum[ch[now][1]])%mod;
}
inline void addtag(int now,int ad,int mu,int mo){
	mul[now]=mul[now]*mu%mod;
	add[now]=(add[now]*mu+ad)%mod;
	mov[now]+=mo,le[now][0]+=mo,ri[now]+=mo;
	le[now][1]=(le[now][1]*mu+ad)%mod,d[now]=d[now]*mu%mod;
	val[now]=((le[now][1]<<1)+(ri[now]-le[now][0])*d[now])%mod*(ri[now]-le[now][0]+1)%mod*500002%mod;
	sum[now]=(sum[now]*mu+ad*len[now])%mod;
}
inline void pushdown(int now){
	if(!add[now]&&mul[now]==1&&!mov[now])return;
	if(ch[now][0])addtag(ch[now][0],add[now],mul[now],mov[now]);
	if(ch[now][1])addtag(ch[now][1],add[now],mul[now],mov[now]);
	add[now]=mov[now]=0,mul[now]=1;
}
inline int merge(int x,int y){
	if(!x||!y)return x+y;
	if(pri[x]<pri[y]){
		pushdown(x);
		ch[x][1]=merge(ch[x][1],y);
		update(x);
		return x;
	}
	else{
		pushdown(y);
		ch[y][0]=merge(x,ch[y][0]);
		update(y);
		return y;
	}
}
inline void split(int now,int k,int &x,int &y){
	if(!now)x=y=0;
	else{
		pushdown(now);
		if(le[now][0]<=k)x=now,split(ch[now][1],k,ch[now][1],y);
		else y=now,split(ch[now][0],k,x,ch[now][0]);
		update(now);
	}
}
int root,x,y,z;
inline void insert(int l0,int r,int l1,int di){
	split(root,l0,x,y);
	root=merge(merge(x,ne(l0,r,l1,di)),y);
}
inline void erase(int l){
	split(root,l,x,z);
	split(x,l-1,x,y);
	y=merge(ch[y][0],ch[y][1]);
	root=merge(merge(x,y),z);
}
inline int qql(int u){
	int now=root,res;
	while(now){
		pushdown(now);
		if(le[now][0]<u)res=now,now=ch[now][1];
		else now=ch[now][0];
	}
	return res;
}
inline void solve1(int l,int r,int k,int op){
	int a=qql(l+1),b=qql(r+1);
	if(l==le[a][0]&&r==ri[b]){
		split(root,r,x,z);
		split(x,l-1,x,y);
		if(op==1)addtag(y,k,1,0);
		else if(op==2)addtag(y,0,k,0);
		else if(op==3)root=merge(merge(x,ne(l,r,k,0)),z);
		if(op<3)root=merge(merge(x,y),z);
		return;
	}
	if(a==b){
		erase(le[a][0]);
		if(le[a][0]<=l-1)insert(le[a][0],l-1,le[a][1],d[a]);
		if(r+1<=ri[a])insert(r+1,ri[a],(le[a][1]+(r-le[a][0]+1)*d[a])%mod,d[a]);
		if(op==1)insert(l,r,(le[a][1]+(l-le[a][0])*d[a]+k)%mod,d[a]);
		else if(op==2)insert(l,r,((le[a][1]+(l-le[a][0])*d[a])*k)%mod,d[a]*k%mod);
		else if(op==3)insert(l,r,k,0);
		return;
	}
	if(l!=le[a][0]){
		erase(le[a][0]);
		if(le[a][0]<=l-1)insert(le[a][0],l-1,le[a][1],d[a]);
	}
	if(r!=ri[b]){
		erase(le[b][0]);
		if(r+1<=ri[b])insert(r+1,ri[b],(le[b][1]+(r-le[b][0]+1)*d[b])%mod,d[b]);
	}
	if(op==1){
		if(l!=le[a][0])insert(l,ri[a],(le[a][1]+(l-le[a][0])*d[a])%mod,d[a]);
		if(r!=ri[b])insert(le[b][0],r,le[b][1],d[b]);
		split(root,r,x,z);
		split(x,l-1,x,y);
		addtag(y,k,1,0);
		root=merge(merge(x,y),z);
	}
	else if(op==2){
		if(l!=le[a][0])insert(l,ri[a],(le[a][1]+(l-le[a][0])*d[a])%mod,d[a]);
		if(r!=ri[b])insert(le[b][0],r,le[b][1],d[b]);
		split(root,r,x,z);
		split(x,l-1,x,y);
		addtag(y,0,k,0);
		root=merge(merge(x,y),z);
	}
	else{
		split(root,l-1,x,y);
		split(y,r,y,z);
		root=merge(merge(x,ne(l,r,k,0)),z);
	}
}
inline void solve2(int l,int r,int k){
	int a=qql(l+1),b=qql(r+1);
}
inline void print(int now){
	if(!now)return;
	pushdown(now);
	print(ch[now][0]);
//	printf("%lld %lld %lld %lld %lld:\n",le[now][0],ri[now],now,ch[now][0],ch[now][1]);
	for(int i=le[now][0];i<=ri[now];i++)
		printf("%lld ",((le[now][1]+(i-le[now][0])*d[now])%mod+mod)%mod);
//	printf("\n=%lld,%lld\n\n",val[now],sum[now]);
	print(ch[now][1]);
}
inline int query(int l,int r){
	int a=qql(l+1),b=qql(r+1);
	split(root,le[b][0],x,z);
	split(x,le[a][0]-1,x,y);
	int res=sum[y];
//	cout<<res<<' '<<y<<endl;
//	print(y);
//	puts("IEE");
	root=merge(merge(x,y),z);
	return ((res-((((le[a][1]<<1)+(l-le[a][0]-1)*d[a])*(l-le[a][0]))%mod*500002%mod)-(((le[b][1]<<1)+(r+ri[b]+1-(le[b][0]<<1))*d[b])*(ri[b]-r)%mod*500002%mod))%mod+mod)%mod;
}
signed main(){
	int n,m,op,l,r,k;
	scanf("%lld%lld",&n,&m);
	insert(1,n,1,1);
	while(m--){
		scanf("%lld%lld%lld",&op,&l,&r);
		if(op<4){
			scanf("%lld",&k);
			solve1(l,r,k,op);
		}
		else if(op==6)printf("%lld\n",query(l,r));
		else solve2(l,r,op-3);
		// print(root);
		// puts("");
	}
	return 0;
}