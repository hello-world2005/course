#include<cstdio>
#include<algorithm>
#define fo(i,a,b) for(i=a;i<=b;i++)
#define fd(i,a,b) for(i=a;i>=b;i--)
using namespace std;
const int maxn=50000+10,B=224;
int f[B+10][B+10],num[B+10],g[maxn][B+10];
int tree[maxn];
int a[maxn],belong[maxn],b[maxn],c[maxn],d[maxn],sum[maxn],cnt[maxn];
int i,j,k,l,r,s,t,n,m,tot,top,ans,now;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
bool cmp(int x,int y){
    return a[x]<a[y];
}
int lowbit(int x){
    return x&-x;
}
void change(int x){
    while (x>0){
        tree[x]++;
        x-=lowbit(x);
    }
}
int query(int x){
    int t=0;
    while (x<=n){
        t+=tree[x];
        x+=lowbit(x);
    }
    return t;
}
int work(int top,int tot){
    int i=1,j=1,t=0;
    while (i<=top&&j<=tot){
        if (c[i]<=d[j]) i++;
        else{
            j++;
            t+=top-i+1;
        }
    }
    return t;
}
int ask(int x,int l,int r){
    int i,t=sum[r]-(l==(x-1)*B+1?0:sum[l-1]);
    top=0;
    fo(i,(x-1)*B+1,min(x*B,n))
        if (b[i]<l) c[++top]=a[b[i]];
    tot=0;
    fo(i,(x-1)*B+1,min(x*B,n))
        if (b[i]>=l&&b[i]<=r) d[++tot]=a[b[i]];
    t-=work(top,tot);
    return t;
}
int main(){
    n=read();
    fo(i,1,n) a[i]=read(),b[i]=a[i];
    sort(b+1,b+n+1);
    top=unique(b+1,b+n+1)-b-1;
    fo(i,1,n) a[i]=lower_bound(b+1,b+top+1,a[i])-b;
    fo(i,1,n) belong[i]=(i-1)/B+1;
    fo(i,1,n) b[i]=i;
    sort(b+1,b+n+1,cmp);
    i=1;
    while (i<=n){
        t=a[b[i]];
        j=i;
        while (i<=n&&a[b[i]]==t){
            fo(k,belong[b[i]]+1,belong[n]) g[b[i]][k]=num[k];
            i++;
        }
        fo(k,j,i-1) num[belong[b[k]]]++;
    }
    fo(i,1,belong[n]) num[i]=0;
    reverse(b+1,b+n+1);
    i=1;
    while (i<=n){
        t=a[b[i]];
        j=i;
        while (i<=n&&a[b[i]]==t){
            fo(k,1,belong[b[i]]-1) g[b[i]][k]=num[k];
            i++;
        }
        fo(k,j,i-1) num[belong[b[k]]]++;
    }
    fo(j,1,belong[n])
        fd(i,(j-1)*B,1)
            if (i%B!=0) g[i][j]+=g[i+1][j];
    fo(j,1,belong[n])
        fo(i,j*B+1,n)
            if (i%B!=1) g[i][j]+=g[i-1][j];
    fo(i,1,n){
        fo(j,1,belong[n]) g[i][j]+=g[i][j-1];
    }
    fo(j,1,belong[n]){
        fo(i,0,n) tree[i]=0;
        l=0;
        fo(i,(j-1)*B+1,min(j*B,n)){
            l+=query(a[i]+1);
            sum[i]=l;
            change(a[i]);
        }
        fo(i,0,n) tree[i]=0;
        l=0;
        fd(i,min(j*B,n),(j-1)*B+1){
            l+=query(n-a[i]+2);
            cnt[i]=l;
            change(n-a[i]+1);
        }
    }
    fo(i,1,n) b[i]=i;
    fo(i,1,belong[n]){
        l=(i-1)*B+1;r=min(i*B,n);
        sort(b+l,b+r+1,cmp);
    }
    fo(i,1,belong[n]) f[i][i]=sum[min(i*B,n)];
    fo(i,1,belong[n]-1)
        fo(j,i+1,belong[n]){
            top=0;
            fo(k,(i-1)*B+1,i*B) c[++top]=a[b[k]];
            tot=0;
            fo(k,(j-1)*B+1,min(j*B,n)) d[++tot]=a[b[k]];
            f[i][j]=work(top,tot);
        }
    fd(i,belong[n]-1,1)
        fo(j,i+1,belong[n])
            f[i][j]+=f[i][j-1]+f[i+1][j]-f[i+1][j-1];
    m=read();
    while (m--){
        j=read();k=read();
        j^=ans;k^=ans;
        l=belong[j];r=belong[k];
        if (l==r){
            ans=ask(l,j,k);
            printf("%d\n",ans);
            continue;
        }
        ans=f[l+1][r-1];
        /*ans+=ask(l,j,l*B);
        ans+=ask(r,(r-1)*B+1,k);*/
        ans+=cnt[j];
        ans+=sum[k];
        top=0;
        fo(i,(l-1)*B+1,l*B)
            if (b[i]>=j) c[++top]=a[b[i]];
        tot=0;
        fo(i,(r-1)*B+1,min(r*B,n))
            if (b[i]<=k) d[++tot]=a[b[i]];
        ans+=work(top,tot);
        /*fo(i,l+1,r-1) ans+=g[j][i];
        fo(i,l+1,r-1) ans+=g[k][i];*/
        ans+=g[j][r-1]-g[j][l];
        ans+=g[k][r-1]-g[k][l];
        printf("%d\n",ans);
    }
}