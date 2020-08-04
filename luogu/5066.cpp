#include<bits/stdc++.h>
using namespace std;
#define N 2000005
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
char cltout[1<<21],*oh=cltout,*ot=cltout+(1<<21);
inline void pc(char c){
	if(oh==ot){
		fwrite(cltout,1,1<<21,stdout);
		oh=cltout;
	}
	*oh++=c;
}
inline int read(){
	int w=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')w=w*10+c-48,c=getchar();
	return w;
}
inline void write(int w,char text=-1){
	if(!w)pc(48);
	else{
		int d[10];
		for(d[0]=0;w;d[++d[0]]=w%10,w/=10);
		for(;d[0];pc(d[d[0]--]^48));
	}
	if(text>=0)pc(text);
}
int ch[N][2],le[N],ri[N],val[N],pri[N],siz[N][2],minn[N][2],sum[N],ld[N][2],rd[N][2],sz;
inline int max(const int&x,const int&y){return(x>y?x:y);}
inline int min(const int&x,const int&y){return(x<y?x:y);}
inline void update(int x){
	minn[x][0]=min(val[x]?N:(ri[x]-le[x]+1),min(minn[ch[x][0]][0],minn[ch[x][1]][0]));
	minn[x][1]=min(val[x]?(ri[x]-le[x]+1):N,min(minn[ch[x][0]][1],minn[ch[x][1]][1]));
	siz[x][0]=(val[x]==1)+siz[ch[x][0]][0]+siz[ch[x][1]][0];
	siz[x][1]=1+siz[ch[x][0]][1]+siz[ch[x][1]][1];
	sum[x]=(ri[x]-le[x]+1)*val[x]+sum[ch[x][0]]+sum[ch[x][1]];
}
inline int ne(int l,int r,int v){
	++sz;
	siz[sz][0]=(v==1);
	siz[sz][1]=1;
	minn[sz][v]=r-l+1;
	le[sz]=l;
	ri[sz]=r;
	val[sz]=v;
	sum[sz]=(r-l+1)*v;
	pri[sz]=rand();
	return sz;
}
inline void addtag(int now,int l0,int l1,int r0,int r1){
	ld[now][0]+=l0;
	ld[now][1]+=l1;
	rd[now][0]+=r0;
	rd[now][1]+=r1;
	if(!val[now])le[now]+=l0,ri[now]+=r0;
	else le[now]+=l1,ri[now]+=r1;
	sum[now]+=(r1-l1)*siz[now][0];
	minn[now][0]+=(r0-l0);
	minn[now][1]+=(r1-l1);
}
inline void pushdown(int now){
	if(!ld[now][0]&&!ld[now][1]&&!rd[now][0]&&!rd[now][1])return;
	if(ch[now][0])addtag(ch[now][0],ld[now][0],ld[now][1],rd[now][0],rd[now][1]);
	if(ch[now][1])addtag(ch[now][1],ld[now][0],ld[now][1],rd[now][0],rd[now][1]);
	ld[now][0]=ld[now][1]=rd[now][0]=rd[now][1]=0;
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
		if(le[now]<=k)x=now,split(ch[now][1],k,ch[now][1],y);
		else y=now,split(ch[now][0],k,x,ch[now][0]);
		update(now);
	}
}
int n,root,x,y,z,tot;
struct node{
	int pos,qq,hj;
}de[N>>1];
inline void insert(int l,int r,int v){
	split(root,l,x,y);
	root=merge(merge(x,ne(l,r,v)),y);
}
inline int qql(int u){
	int now=root,res;
	while(now){
		pushdown(now);
		if(le[now]<u)res=now,now=ch[now][1];
		else now=ch[now][0];
	}
	return res;
}
void assign(int l,int r,int v){
	split(root,l-1,x,y);
	split(y,r,y,z);
	root=merge(merge(x,ne(l,r,v)),z);
}
inline void dfs(int now,int l,int r,int v){
	if(!now)return;
	pushdown(now);
	if(minn[ch[now][0]][v]==1&&le[now]>l)dfs(ch[now][0],l,r,v);
	if(val[now]==v&&le[now]==ri[now]&&le[now]>=l&&ri[now]<=r)de[++tot].pos=now;
	if(minn[ch[now][1]][v]==1&&ri[now]<r)dfs(ch[now][1],l,r,v);
}
inline void find(int l,int r,int v){
	tot=0;
	dfs(root,l,r,v);
	for(int i=1;i<=tot;++i)
		de[i].qq=(le[de[i].pos]>1?qql(le[de[i].pos]):de[i].pos),
		de[i].hj=(ri[de[i].pos]<n?qql(ri[de[i].pos]+2):de[i].pos);
	for(int i=1,a,b;i<=tot;){
		a=i;
		for(b=a+1;b<=tot;b++)
			if(de[b].qq!=de[b-1].hj)break;
		assign(le[de[a].qq],ri[de[b-1].hj],v^1);
		i=b;
	}
}
inline void solve1(int l,int r,int v){
	int a=qql(l+1),b=qql(r+1),c,d;
	if(a==b&&val[a]==v)return;
	if(val[a]==v&&v==val[b])assign(le[a],ri[b],v);
	else if(val[a]==v&&v!=val[b]){
		if(r==ri[b]){
			if(ri[b]!=n)assign(le[a],ri[qql(ri[b]+2)],v);
			else assign(le[a],n,v);
		}
		else{
			split(root,le[a]-1,x,y);
			split(y,ri[b],y,z);
			x=merge(x,ne(le[a],r,v));
			root=merge(merge(x,ne(r+1,ri[b],v^1)),z);
		}
	}
	else if(val[a]!=v&&v==val[b]){
		if(l==le[a]){
			if(le[a]!=1)assign(le[qql(le[a])],ri[b],v);
			else assign(1,ri[b],v);
		}
		else{
			split(root,le[a]-1,x,y);
			split(y,ri[b],y,z);
			x=merge(x,ne(le[a],l-1,v^1));
			root=merge(merge(x,ne(l,ri[b],v)),z);
		}
	}
	else{
		if(l==le[a]){
			if(r==ri[b])assign(l==1?1:le[qql(le[a])],r==n?n:ri[qql(ri[b]+2)],v);
			else{
				c=(l==1?1:le[qql(le[a])]);
				split(root,c-1,x,y);
				split(y,ri[b],y,z);
				x=merge(x,ne(c,r,v));
				root=merge(merge(x,ne(r+1,ri[b],v^1)),z);
			}
		}
		else{
			if(r==ri[b]){
				d=(r==n?n:ri[qql(ri[b]+2)]);
				split(root,le[a]-1,x,y);
				split(y,d,y,z);
				x=merge(x,ne(le[a],l-1,v^1));
				root=merge(merge(x,ne(l,d,v)),z);
			}
			else{
				split(root,le[a]-1,x,y);
				split(y,ri[b],y,z);
				x=merge(x,ne(le[a],l-1,v^1));
				x=merge(x,ne(l,r,v));
				root=merge(merge(x,ne(r+1,ri[b],v^1)),z);
			}
		}
	}
}
inline void solve2(int l,int r,int op){
	if(l==r)return;
	if(minn[root][0]==1&&op<3)find(l+(op==2),r-(op==1),0);
	if(minn[root][1]==1&&op>2)find(l+(op==4),r-(op==3),1);
	int a=qql(l+1),b=qql(r+1);
	if(a==b)return;
	if(op==1||op==4){
		if(val[a]){
			if(ri[a]==n)return;
			a=qql(ri[a]+2);
		}
		if(!val[b]){
			if(le[b]==1)return;
			b=qql(le[b]);
		}
	}
	else if(op==2||op==3){
		if(!val[a]){
			if(ri[a]==n)return;
			a=qql(ri[a]+2);
		}
		if(val[b]){
			if(le[b]==1)return;
			b=qql(le[b]);
		}
	}
	if(le[a]>=le[b])return;
	split(root,le[b],x,z);
	split(x,le[a]-1,x,y);
	if(op==1)addtag(y,0,-1,-1,0);
	else if(op==2)addtag(y,1,0,0,1);
	else if(op==3)addtag(y,-1,0,0,-1);
	else addtag(y,0,1,1,0);
	root=merge(merge(x,y),z);
}
inline int query(int l,int r){
	int a=qql(l+1),b=qql(r+1);
	split(root,le[b],x,z);
	split(x,le[a]-1,x,y);
	int res=sum[y];
	root=merge(merge(x,y),z);
	return res-(l-le[a])*val[a]-(ri[b]-r)*val[b];
}
int a[N];
void init(){
	for(register int i=0;i<N;++i)
		minn[i][0]=N;
	for(register int i=0;i<N;++i)
		minn[i][1]=N;
	int l,r;
	for(int i=1;i<=n;){
		l=i;
		for(r=l+1;r<=n;++r)
			if(a[r]!=a[l])break;
		insert(l,r-1,a[l]);
		i=r;
	}
}
int main(){
	srand(time(NULL));
	int m,op,l,r;
	n=read(),m=read();
	for(register int i=1;i<=n;++i)
		a[i]=read();
	init();
	while(m--){
		op=read(),l=read(),r=read();
		if(op<3)solve1(l,r,op-1);
		else if(op==7)write(query(l,r),10);
		else solve2(l,r,op-2);
	}
	fwrite(cltout,1,oh-cltout,stdout),oh=cltout;
	return 0;
}