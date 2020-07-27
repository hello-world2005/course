#include<cstdio>
#include<algorithm>
using namespace std;
const int N=30000,M=938,MAXB=235;
int n,m,block,i,j,k,l,r,cnt[65536],s[M][M],ans;
int A[N],B[N],C[N],D[N],E[N];
unsigned short f[N][M];
struct P{int x1,y1,x2,y2;}a[N];
inline bool cmpa(int x,int y){return a[x].x1<a[y].x1;}
inline bool cmpb(int x,int y){return a[x].x2>a[y].x2;}
inline bool cmpc(int x,int y){return a[x].y1<a[y].y1;}
inline bool cmpd(int x,int y){return a[x].y2>a[y].y2;}
inline bool cmpe(int x,int y){return a[x].y1>a[y].y1;}
inline int popcount(unsigned int x){return cnt[x&65535]+cnt[x>>16];}
struct Bitset{
  unsigned int v[M];
  Bitset(){}
  inline void clear(){for(int i=0;i<=m;i++)v[i]=0;}
  inline void set(int x){v[x>>5]|=1U<<(x&31);}
  inline void copy(const Bitset&p){for(int i=0;i<=m;i++)v[i]=p.v[i];}
  inline void operator&=(const Bitset&p){for(int i=0;i<=m;i++)v[i]&=p.v[i];}
}bA[MAXB],bB[MAXB],bC[MAXB],bD,now,tmp;
inline bool check(const P&a,const P&b){
  return b.x1<a.x2&&b.x2>a.x1&&b.y1<a.y2&&b.y2>a.y1;
}
inline int ask(int x,int y){
  if(x<0||y<0)return 0;
  int ret=0,c=x>>5<<5,d=y>>5<<5,i,j;
  if(x>31&&y>31)ret=s[(x>>5)-1][(y>>5)-1];
  for(i=c;i<=x;i++)for(j=d;j<=y;j++)if(check(a[i],a[j]))ret++;
  if(x>31)for(i=d;i<=y;i++)ret+=f[i][(x>>5)-1];
  if(y>31)for(i=c;i<=x;i++)ret+=f[i][(y>>5)-1];
  return ret;
}
inline void read(int&a){char c;while(!(((c=getchar())>='0')&&(c<='9')));a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';}
int main(){
  read(n);
  for(i=0;i<n;i++)read(a[i].x1),read(a[i].y1),read(a[i].x2),read(a[i].y2);
  m=(n-1)>>5;
  for(i=1;i<65536;i++)cnt[i]=cnt[i>>1]+(i&1);
  block=(n-1)>>7;
  for(i=0;i<n;i++)A[i]=i;
  sort(A,A+n,cmpa);
  for(i=0;i<=block;i++){
    l=i<<7,r=min(l+128,n);
    if(i)bA[i].copy(bA[i-1]);
    while(l<r)bA[i].set(A[l++]);
  }
  for(i=0;i<n;i++)B[i]=i;
  sort(B,B+n,cmpb);
  for(i=0;i<=block;i++){
    l=i<<7,r=min(l+128,n);
    if(i)bB[i].copy(bB[i-1]);
    while(l<r)bB[i].set(B[l++]);
  }
  for(i=0;i<n;i++)C[i]=i;
  sort(C,C+n,cmpc);
  for(i=0;i<=block;i++){
    l=i<<7,r=min(l+128,n);
    if(i)bC[i].copy(bC[i-1]);
    while(l<r)bC[i].set(C[l++]);
  }
  for(i=0;i<n;i++)D[i]=E[i]=i;
  sort(D,D+n,cmpd);
  sort(E,E+n,cmpe);
  for(i=j=0;i<n;i++){
    int x=E[i];P&y=a[x];
    while(j<n&&a[D[j]].y2>y.y1)bD.set(D[j++]);
    now.copy(bD);
    for(k=0;k<=block;k++){
      r=min(k<<7|127,n-1);
      if(a[A[r]].x1>=y.x2)break;
    }
    if(k)tmp.copy(bA[k-1]);else tmp.clear();
    if(k<=block){
      l=k<<7;
      while(a[A[l]].x1<y.x2)tmp.set(A[l++]);
    }
    now&=tmp;
    for(k=0;k<=block;k++){
      r=min(k<<7|127,n-1);
      if(a[B[r]].x2<=y.x1)break;
    }
    if(k)tmp.copy(bB[k-1]);else tmp.clear();
    if(k<=block){
      l=k<<7;
      while(a[B[l]].x2>y.x1)tmp.set(B[l++]);
    }
    now&=tmp;
    for(k=0;k<=block;k++){
      r=min(k<<7|127,n-1);
      if(a[C[r]].y1>=y.y2)break;
    }
    if(k)tmp.copy(bC[k-1]);else tmp.clear();
    if(k<=block){
      l=k<<7;
      while(a[C[l]].y1<y.y2)tmp.set(C[l++]);
    }
    now&=tmp;
    for(k=0;k<=m;k++){
      f[x][k]=popcount(now.v[k]);
      s[x>>5][k]+=f[x][k];
      if(k)f[x][k]+=f[x][k-1];
    }
  }
  for(i=0;i<=m;i++)for(j=0;j<=m;j++){
    if(i)s[i][j]+=s[i-1][j];
    if(j)s[i][j]+=s[i][j-1];
    if(i&&j)s[i][j]-=s[i-1][j-1];
  }
  read(m);
  while(m--){
    read(i),read(j),read(l),read(r);
    i^=ans,j^=ans,l^=ans,r^=ans;
    i--,j--,l--,r--;
    printf("%d\n",ans=ask(j,r)-ask(i-1,r)-ask(j,l-1)+ask(i-1,l-1));
  }
  return 0;
}
