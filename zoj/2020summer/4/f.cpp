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
const int A=1000,N=1e5,M=6e5;
int n,sn,len,ans=inf;
string s,ss,b[N];

//Graph
int e[A][A],dep[N];
void add(int u,int v){
	(u+=sn)%=sn,(v+=sn)%=sn,e[u][v]=1;
	// cout<<"("<<u<<","<<v<<")\n";
}
int Bfs(int now){
	for(int i=0;i<len;i++) dep[i]=inf;
	queue<int> q;
	for(int v=0;v<sn;v++)if(e[now][v]){
		dep[v]=1;
		if(v==now) return dep[v];
		q.push(v);
	}
	while(sz(q)){
		int u=q.front(); q.pop();
		for(int v=0;v<sn;v++)if(e[u][v]&&dep[v]>dep[u]+1){
			dep[v]=dep[u]+1;
			if(v==now) return dep[v];
			q.push(v);
		}
	}
	return inf;
}

//ACAM
int ch[M][26],cnt=1,at[N];
vector<int> f[M];
bitset<1000> vis[M];
void insert(int i,int an,string a){
	int p=0;
	for(int i=0;i<an;i++){
		int c=a[i]-'a';
		if(!ch[p][c]) ch[p][c]=cnt++;
		p=ch[p][c];
	}
	at[i]=p;
}
int fa[M];
void Getac(){
	queue<int> q;
	for(int i=0;i<26;i++)
		if(ch[0][i]) q.push(ch[0][i]);
	while(sz(q)){
		int p=q.front(); q.pop();
		for(int c=0;c<26;c++)
			if(ch[p][c]){
				fa[ch[p][c]]=ch[fa[p]][c];
				q.push(ch[p][c]);
			} else ch[p][c]=ch[fa[p]][c];
	}
}
vector<int> ac[M];
void Dfs(int p){
	for(int v:ac[p]){
		Dfs(v);
		for(int x:f[v])if(!vis[p][x])
			f[p].pb(x),vis[p][x]=true;
	}
}
void Runac(){
	int p=0;
	for(int i=0;i<len;i++){
		p=ch[p][ss[i]-'a'];
		f[p].pb(i);
	}
	// cout<<"?\n";
	for(int i=1;i<cnt;i++)
		ac[fa[i]].pb(i);
	Dfs(0);
	for(int i=0;i<n;i++)
		for(int x:f[at[i]]) add(x-sz(b[i]),x);
}

//Main
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>s>>n;
	sn=sz(s),ss=s+s,len=sz(ss);
	for(int i=1;i<sn;i++)if(sn%i==0){
		int ok=1;
		for(int j=0;j<sn;j+=i){
			for(int k=j;k<j+i;k++)
				if(s[k]!=s[k-j]){ok=0;break;}
			if(!ok) break;
		}
		if(ok){s=s.substr(0,i),sn=i; break;}
	}
	// cout<<sn<<' '<<s<<'\n';
	for(int i=0;i<n;i++){
		cin>>b[i];
		if(sn==1){
			int ok=1;
			for(int j=0;j<sz(b[i]);j++)
				if(b[i][j]!=s[0]){ok=0;break;}
			if(ok) cout<<1<<'\n',exit(0);
		}
		insert(i,sz(b[i]),b[i]);
	}
	// cout<<"!\n";
	Getac();
	// cout<<"!\n";
	Runac();
	// cout<<"!\n";
	for(int i=0;i<sn;i++) ans=min(ans,Bfs(i));
	if(ans==inf) cout<<-1<<'\n';
	else cout<<ans<<'\n';
	return 0;
}
