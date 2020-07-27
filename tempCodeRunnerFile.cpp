#include<bits/stdc++.h>
 
#define int long long
 
#define rd(x) x=read()
 
#define N 5000005
#define M 200005
 
using namespace std;
 
int n,m;
char s[N];
int p[N],t[N],y[N],tot;
int e[N],ss[N];
 
struct Q{
    int l,r,k,id;
}q[M];long long ans[M];
 
inline bool cmp(Q x,Q y){return x.k<y.k;}
 
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+c-'0',c=getchar();
    return x*f;
}
 
signed main()
{
    scanf("%s",s+1),n=strlen(s+1),rd(m);
    for(int i=1;i<=n;i++){if(s[i]=='T')p[++tot]=i;y[i]=tot;}
    for(int i=1;i<=tot;i++)t[i]=p[i]-p[i-1]-1;
    for(int i=1;i<=m;i++)rd(q[i].l),rd(q[i].r),rd(q[i].k),q[i].id=i;
    sort(q+1,q+m+1,cmp);
    for(int i=1;i<=tot;i++)e[i]=i;
    for(int i=1,w;i<=m;i++)
    {
        if(q[i-1].k<q[i].k)
        {
            w=0;for(int j=1;j<=tot;j++)if(t[j]>=q[i].k)t[++w]=t[j],e[w]=e[j];tot=w;
            for(int j=1;j<=tot;j++)ss[j]=ss[j-1]+t[j]/q[i].k;
        }
        if(y[q[i].l-1]==y[q[i].r])ans[q[i].id]=q[i].r-q[i].l+1;
        else
        {
            int k1=y[q[i].l-1]+2,k2=y[q[i].r];
            int l=lower_bound(e+1,e+tot+1,k1)-e,r=upper_bound(e+1,e+tot+1,k2)-e-1;
            ans[q[i].id]=1ll*(ss[r]-ss[l-1]+y[q[i].r]-y[q[i].l-1]+(p[k1-1]-q[i].l)/q[i].k)*q[i].k-p[k2]+q[i].r;
        }
    }
    for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
 
    return 0;
}