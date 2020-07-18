#include <algorithm>
#include <cstdio>
#include <unordered_map>

#define int long long

const int N = 1e6 + 10;
const int MOD = 998244353;

int prime[N], cnt;
bool vis[N];
int mu[N], sum_mu[N];
int mui[N], muii[N];

void Init() {
  mu[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!vis[i])
      prime[++cnt] = i, mu[i] = 1;
    mui[i] = (mu[i] * i + MOD) % MOD, muii[i] = (mu[i] * i * i + MOD) % MOD;
    for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
      vis[i * prime[j]] = true;
      if (i % prime[j] == 0) {
        mu[i * prime[j]] = 0;
        break;
      }
      mu[i * prime[j]] = -mu[i];
    }
  }
  for (int i = 1; i < N; ++i)
    sum_mu[i] = (sum_mu[i - 1] + mu[i] + MOD) % MOD,
    (mui[i] += mui[i - 1]) %= MOD, (muii[i] += muii[i - 1]) %= MOD;
}

signed main() {
  Init();
  int T;
  scanf("%lld", &T);
  while (T--) {
    int n, m;
    scanf("%lld%lld", &n, &m);
    --n, --m;
    if (n > m)
      std::swap(n, m);
    int ans = 0;
    for (int l = 1, r = 0; l <= n; l = r + 1) {
      r = std::min(n / (n / l), m / (m / l));
      int x = n / l, y = m / l;
      ans = ((ans +
              (x * y % MOD * (n + 1) % MOD * (m + 1) % MOD *
               (sum_mu[r] - sum_mu[l - 1] + MOD) % MOD) -
              ((mui[y] - mui[x - 1] + MOD) % MOD *
               (x * sum_mu[y] % MOD * (n + 1) % MOD +
                sum_mu[x] * y % MOD * (m + 1) % MOD)) +
              (sum_mu[x] * sum_mu[y] % MOD * (muii[r] - muii[l - 1] + MOD) %
               MOD) -
              ((x / 2) * (y / 2) % MOD * (n + 1) % MOD * (m + 1) % MOD *
               (sum_mu[r] - sum_mu[l - 1] + MOD) % MOD) +
              (2 * (mui[r] - mui[l - 1] + MOD) % MOD *
               ((x / 2) * sum_mu[y] % MOD * (n + 1) % MOD +
                (y / 2) * sum_mu[x] % MOD * (m + 1) % MOD)) -
              4 * (sum_mu[x / 2] * sum_mu[y / 2] % MOD *
                   (muii[r] - muii[l - 1] + MOD) % MOD)) %
                 MOD +
             MOD) %
            MOD;
    }
    printf("%lld\n", (ans * 2 % MOD + n + m + 2) % MOD);
  }
}

/*
    #include <bits/stdc++.h>
    using namespace std;
     
    //Start
    typedef long long ll;
    typedef double db;
    #define mp(a,b) make_pair(a,b)
    #define x first
    #define y second
    #define be(a) a.begin()
    #define en(a) a.end()
    #define sz(a) int((a).size())
    #define pb(a) push_back(a)
    const int inf=0x3f3f3f3f;
    const ll INF=0x3f3f3f3f3f3f3f3f;
     
    //Data
    const int N=1e6;
    const int mod=998244353;
    int n,m;
    int sum(int x){return (ll)x*(x+1)/2%mod;}
     
    //Sieve
    bool np[N+1]; 
    int mu[N+1],mud[N+1],mudd[N+1],cp,p[N];
    void Sieve(){
    	mu[1]=mud[1]=mudd[1]=1,np[1]=true;
    	for(int i=2;i<=N;i++){
    		if(!np[i]) mu[i]=-1,p[cp++]=i;
    		mud[i]=(mu[i]*i+mod)%mod;
    		mudd[i]=((ll)mu[i]*i*i%mod+mod)%mod;
    		for(int j=0;j<cp&&i*p[j]<=N;j++){
    			np[i*p[j]]=1;
    			if(i%p[j]==0){mu[i*p[j]]=0;break;}
    			mu[i*p[j]]=mu[i]*mu[p[j]];
    		}
    	}
    	for(int i=2;i<=N;i++){
    		(mu[i]+=mu[i-1]+mod)%=mod;
    		(mud[i]+=mud[i-1])%=mod;
    		(mudd[i]+=mudd[i-1])%=mod;
    		assert(mu[i]>=0);
    		assert(mud[i]>=0);
    		assert(mudd[i]>=0);
    	}
    }
     
    //Main
    int main(){
    //	ios::sync_with_stdio(0);
    //	cin.tie(0),cout.tie(0);
    	Sieve();
    	int t; cin>>t;
    	while(t--){
    		cin>>n>>m,n--,m--;
    		if(n>m) n^=m^=n^=m;
    		if(n==0){
    			cout<<(m==0?0:1)<<'\n';
    			continue;
    		}
    		int ans=0;
    		for(int l=1,r,nd,md,ni,mi;l<=n;l=r+1){
    			r=min(n/(n/l),m/(m/l));
    			nd=n/l,md=m/l,ni=n/l/2,mi=m/l/2;
    			(ans+=(ll)nd*md%mod*(n+1)%mod*(m+1)%mod*(mu[r]-mu[l-1]+mod)%mod)%=mod;
    			(ans-=(ll)nd*sum(md)%mod*(n+1)%mod*(mud[r]-mud[l-1]+mod)%mod)%=mod;
    			(ans-=(ll)md*sum(nd)%mod*(m+1)%mod*(mud[r]-mud[l-1]+mod)%mod)%=mod;
    			(ans+=(ll)sum(nd)*sum(md)%mod*(mudd[r]-mudd[l-1])%mod)%=mod;
    			(ans-=(ll)ni*mi%mod*(n+1)%mod*(m+1)%mod*(mu[r]-mu[l-1]+mod)%mod)%=mod;
    			(ans+=(ll)ni*sum(mi)%mod*(n+1)%mod*(mud[r]-mud[l-1]+mod)%mod*2%mod)%=mod;
    			(ans+=(ll)mi*sum(ni)%mod*(m+1)%mod*(mud[r]-mud[l-1]+mod)%mod*2%mod)%=mod;
    			(ans-=(ll)sum(ni)*sum(mi)%mod*(mudd[r]-mudd[l-1])%mod*4%mod)%=mod;
    		}
    //		for(int d=1;d<=n;d++){
    //			for(int i=1;i<=n/d;i++)
    //				for(int j=1;j<=m/d;j++){
    //					(ans+=mu[d]*min(n+1-i*d,i*d)*(m+1-j*d)%mod)%=mod;
    //					(ans+=mu[d]*min(m+1-j*d,j*d)*(n+1-i*d)%mod)%=mod;
    //					(ans-=mu[d]*min(n+1-i*d,i*d)*min(m+1-j*d,j*d)%mod)%=mod;
    //				}
    //		}
    //		cout<<"ans="<<ans<<'\n';
    		(ans+=mod)%=mod;
    		ans=(ans*2%mod+n+m+2)%mod;
    		cout<<ans<<'\n';
    	}
    	
    	return 0;
    }
    */
