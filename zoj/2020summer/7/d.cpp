#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5,M=2e5+5,INF=0x3fffffff;
template<typename T>void read(T &x)
{
 bool neg=false;
 unsigned char c=getchar();
 for(;(c^48)>9;c=getchar())if(c=='-')neg=true;
 for(x=0;(c^48)<10;c=getchar())x=(x<<3)+(x<<1)+(c^48);
 if(neg)x=-x;
}
struct line
{
 int next,to;
}e[2*M];
int n,m,k,tt,s[N],hd[N],cnt,dis[N][2],q[2*N],qt[2*N],qf,qr;
int ans[2][N];bool have[N];
void adline(int u,int v)
{
 e[cnt].to=v;
 e[cnt].next=hd[u];
 hd[u]=cnt++;
}
int solve(int k)
{
 int l=0,r=n+1,mid=0;
 while(r-l>1)
 {
  mid=(l+r)>>1;
  if(ans[k&1][mid-1]<=k)l=mid;
  else r=mid;
 }
 return l;
}
int main()
{
 read(n);read(m);read(k);
 for(int i=0;i<n;++i)hd[i]=-1;
 for(int i=0;i<k;++i)read(s[i]),have[--s[i]]=true;
 k=0;
 for(int i=0;i<n;++i)if(have[i])s[k++]=i;
 for(int i=0;i<m;++i)
 {
  int u,v;read(u);read(v);
  adline(--u,--v);adline(v,u);
 }
 for(int i=0;i<n;++i)dis[i][0]=dis[i][1]=INF;
 for(int i=0;i<k;++i)if(~hd[s[i]])dis[q[qr++]=s[i]][0]=0;
 while(qf<qr)
 {
  int u=q[qf],t=qt[qf++];
  for(int i=hd[u];~i;i=e[i].next)
  {
   int v=e[i].to;
   if(dis[v][t^1]>dis[u][t]+1)
   {
    dis[v][t^1]=dis[u][t]+1;
    qt[qr]=t^1;q[qr++]=v;
   }
  }
 }
 for(int i=0;i<n;++i)
 {
  ans[0][i]=dis[i][0];
  ans[1][i]=dis[i][1];
 }
 sort(ans[0],ans[0]+n);
 sort(ans[1],ans[1]+n);
 read(tt);
 for(int i=0;i<tt;++i)
 {
  int t;read(t);--t;
  if(t==0){printf("%d\n",k);continue;}
  printf("%d\n",solve(t));
 }
 return 0;
}
