#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define mod 1000000007
using namespace std;
const int N=1e6+5;
int s[N],invs[N];
int m,n,T,p[N],prime[100000],mu[N],cnt,nn[1005],mm[1005],sf[N];
inline int qpower(int a,int b)
{
	int ans=1;for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;return ans;
}
void make(int n)
{
	mu[1]=p[1]=invs[0]=s[1]=invs[1]=sf[1]=1;
	for(int i=2;i<=n;i++)
	{
		s[i]=(s[i-1]+s[i-2])%mod,sf[i]=1ll*sf[i-1]*s[i]%mod;if(!p[i])prime[++cnt]=i,mu[i]=-1;
		for(int j=1,x;j<=cnt&&(x=i*prime[j])<=n;j++)
		{
			p[x]=1;if(i%prime[j])mu[x]=-mu[i];
			else break;
		}
	}
	int sis=qpower(sf[n],mod-2);
	for(int i=n;i>=2;i--)invs[i]=1ll*sis*sf[i-1]%mod,sis=1ll*sis*s[i]%mod;
	for(int i=1;i<=cnt;i++)
	{
		for(int jj=n/prime[i],j=jj*prime[i];jj>=1;jj--,j=jj*prime[i])
		{
			s[j]=1LL*s[j]*invs[jj]%mod;
			invs[j]=1ll*invs[j]*s[jj]%mod;
		}
	}
	for(int i=2;i<=n;i++)s[i]=1ll*s[i]*s[i-1]%mod,invs[i]=1ll*invs[i]*invs[i-1]%mod;;
  // printf("%d %d\n", s[6], invs[6]);
}
int main()
{
	scanf("%d",&T);int maxn=0;
	for(int i=1;i<=T;i++)scanf("%d%d",nn+i,mm+i),maxn=max(maxn,min(nn[i],mm[i]));
	make(maxn);
	for(int TTT=1;TTT<=T;TTT++)
	{
		int n=nn[TTT],m=mm[TTT];
		if(n>m)swap(n,m);int ans=1;
		int i=1,lt=sqrt(n);
		for(;i<=lt;i++)
		{
			ans=(1ll*ans*qpower(1ll*s[i]*invs[i-1]%mod,1ll*(n/i)*(m/i)%(mod-1)))%mod;
		}
		for(;i<=n;i=lt+1)
		{
			lt=min(n/(n/i),m/(m/i));
			ans=(1ll*ans*qpower(1ll*s[lt]*invs[i-1]%mod,(n/i)*(m/i)))%mod;
		}
		printf("%d\n",ans);
	}
}