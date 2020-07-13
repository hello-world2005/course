#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <cmath>
#define pii pair<int,int>
#define mpr(a,b) make_pair(a,b)
#define sit set<pair<int,int> >::iterator
using namespace std;
const int N=210000;
const int sqr=350;
int n,m,blo;
int op[N],u[N],v[N];
int deg[N];
int used[N],tot=0,id[N];
int cnt[sqr][N],f[sqr][N];
int vis[sqr][sqr];
int but[N];
set<pii> s;
vector<int> e[N];
void inst(int u,int t)
{
	for(int i=1;i<=tot;i++)
	{
		if(!f[i][u]) continue;
		vis[i][used[t]]=1;
		vis[used[t]][i]=1;
	}
	return;
}
void inse(int u,int v)
{
	s.insert(mpr(u,v));
	s.insert(mpr(v,u));
	e[u].push_back(v);
	e[v].push_back(u);
	if(used[u]) cnt[used[u]][v]++,f[used[u]][v]=1;
	if(used[v]) cnt[used[v]][u]++,f[used[v]][u]=1;
	if(used[u]) inst(v,u);
	if(used[v]) inst(u,v);
	return;
}
int que(int x,int y)
{
	int flag=0;
	for(int i=0;i<(int)e[x].size();i++)
	{
		int v=e[x][i];
		but[v]++;
	}
	for(int i=0;i<(int)e[y].size();i++)
	{
		int v=e[y][i];
		if(but[v]) flag=1;
	}
	for(int i=0;i<(int)e[x].size();i++)
	{
		int v=e[x][i];
		but[v]--;
	}
	return flag;
}
int quey(int x,int y)
{
	for(int i=0;i<(int)e[x].size();i++)
	{
		int v=e[x][i];
		if(cnt[used[y]][v]>0) return 1;
	}
	return 0;
}
int quer(int u,int v)
{
	sit it=s.find(mpr(u,v));
	if(it!=s.end()) return 0;
	if(!used[u]&&!used[v]) return que(u,v);
	if(used[u]&&used[v]) return vis[used[u]][used[v]];
	if(used[u]) swap(u,v);
	return quey(u,v);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&op[i],&u[i],&v[i]);
		if(op[i]==1) deg[u[i]]++,deg[v[i]]++;
	}
	blo=(int)ceil(sqrt((double)m));
	for(int i=1;i<=n;i++)
	{
		if(deg[i]>=blo)
		{
			used[i]=++tot;
			id[tot]=i;
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(op[i]==1) inse(u[i],v[i]);
		else
		{
			if(quer(u[i],v[i])) printf("Yes\n");
			else printf("No\n");
		}
	}
	return 0;
}