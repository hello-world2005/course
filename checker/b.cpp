#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
// function<void(void)> ____ = [](){ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);};
const int MAXN = 1e5+7;
int n,w[MAXN],q,son[MAXN],sz[MAXN],ret[MAXN];
vector<int> G[MAXN];
vector<pair<int,int> > Q[MAXN];
struct Trie{
    int tot,ch[MAXN<<4][2];
    void clear(){ tot = 0, ch[0][0] = ch[0][1] = 0; }
    int newnode(){ tot++; ch[tot][0] = ch[tot][1] = 0; return tot; }
    void insert(int x){
        int p = 0;
        for(int i = 30; ~i; i--){
            int nxt = (x&(1<<i))?1:0;
            if(!ch[p][nxt]) ch[p][nxt] = newnode();
            p = ch[p][nxt];
        }
    }
    int match(int x){
        int res = 0, p = 0;
        for(int i = 30; ~i; i--){
            int nxt = (x&(1<<i))?0:1;
            if(ch[p][nxt]) res |= (1<<i), p = ch[p][nxt];
            else p = ch[p][nxt^1];
        }
        return res;
    }
}trie;
void dfs(int u){
    sz[u] = 1; son[u] = 0;
    for(int v : G[u]){
        dfs(v); sz[u] += sz[v];
        if(sz[v]>sz[son[u]]) son[u] = v;
    }
}
void update(int u){
    trie.insert(w[u]);
    for(int v : G[u]) update(v);
}
void search(int u, bool clear){
    for(int v : G[u]) if(v!=son[u]) search(v,true);
    if(son[u]) search(son[u],false);
    for(int v : G[u]) if(v!=son[u]) update(v);
    trie.insert(w[u]);
    for(auto que : Q[u]) ret[que.second] = trie.match(que.first);
    if(clear) trie.clear();
}
void solve(){
    for(int i = 1; i <= n; i++){
        G[i].clear(); Q[i].clear();
        scanf("%d",&w[i]);
    }
    for(int i = 2; i <= n; i++){
        int par; scanf("%d",&par);
        G[par].emplace_back(i);
    }
    dfs(1);
    for(int i = 1; i <= q; i++){
        int u, x; scanf("%d %d",&u,&x);
        Q[u].emplace_back(make_pair(x,i));
    }
    search(1,true);
    for(int i = 1; i <= q; i++) printf("%d\n",ret[i]);
}
int main(){
    while(scanf("%d %d",&n,&q)!=EOF) solve();
    return 0;
}