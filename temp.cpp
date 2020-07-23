#include <bits/stdc++.h>
using namespace std;
#define fr first
#define sc second
typedef long long ll;
const int inf=0x3f3f3f;
const int N=3e5+5;
struct node
{
    int val,ls,rs,dis,fa,lz;
    int fa2;
};
struct zps
{
    node tree[N];
    int tot=0;
    void init(int n)
    {
        for(int i=0;i<=n;i++){
            tree[i].ls=tree[i].rs=tree[i].dis=tree[i].lz=0;
            tree[i].fa=i;
            tree[i].fa2=i;
        }
        tot=n;
    }
    int get_val(int x)
    {
        int sum=tree[x].val;
        while(x!=tree[x].fa2){
            x=tree[x].fa2;
            sum+=tree[x].lz;
        printf("> %d\n", sum);
        }
        return sum;
    }
    int find(int x)
    {
        //printf("%d %d\n",x,tree[x].fa);
        if(tree[x].fa!=x){
            return tree[x].fa=find(tree[x].fa);
        }
        return x;
    }
    void pushdown(int x)
    {
        if(tree[x].lz){
            if(tree[x].ls){
                tree[tree[x].ls].val+=tree[x].lz;
                tree[tree[x].ls].lz+=tree[x].lz;
            }
            if(tree[x].rs){
                tree[tree[x].rs].val+=tree[x].lz;
                tree[tree[x].rs].lz+=tree[x].lz;
            }
            tree[x].lz=0;
        }
    }
    int merge(int x,int y)
    {
        if(x==0)return y;
        if(y==0)return x;
        if(tree[x].val<tree[y].val||(tree[x].val==tree[y].val&&x>y))swap(x,y);
        pushdown(x);
        //tree[++tot]=tree[x],x=tot;  
        tree[x].rs=merge(tree[x].rs,y);
        tree[tree[x].rs].fa=x;
        tree[tree[x].rs].fa2=x;
        if(tree[tree[x].rs].dis>tree[tree[x].ls].dis)swap(tree[x].rs,tree[x].ls);
        tree[x].dis=tree[x].rs==0?0:tree[tree[x].rs].dis+1;
        return x;
    }
    int build(int n)
    {
        queue<int>q;
        for(int i=1;i<=n;i++){
            q.push(i);
        }
        while(!q.empty()){
            if(q.size()==1)break;
            int x=q.front();q.pop();
            int y=q.front();q.pop();
            q.push(merge(x,y));
        }
        return q.front();
    }
    int add(int val,int x)
    {
        ++tot;
        tree[tot].ls=tree[tot].rs=tree[tot].dis=0;
        tree[tot].fa=tot;
        tree[tot].fa2=tot;
        return merge(tot,x);
    }
    int pop(int x)
    {
        pushdown(x);
        int l=tree[x].ls,r=tree[x].rs;
        tree[x].ls=tree[x].rs=tree[x].dis=0;
        tree[x].val=-inf;
        tree[l].fa=tree[l].fa2=l,tree[r].fa=tree[r].fa2=r;
        return tree[x].fa=merge(l,r);
    }
    void del1(int x)
    {
        pushdown(x);
        int fx=tree[x].fa2;
        int u=merge(tree[x].ls,tree[x].rs);
        tree[u].fa=tree[u].fa2=fx;
        if(tree[fx].ls==x)tree[fx].ls=u;
        else tree[fx].rs=u;
        tree[x].ls=tree[x].rs=tree[x].dis=0;
        while(fx!=tree[fx].fa2){
            if(tree[tree[fx].ls].dis<tree[tree[fx].rs].dis)swap(tree[fx].ls,tree[fx].rs);
            if(tree[fx].dis==tree[tree[fx].rs].dis+1)return ;
            tree[fx].dis=tree[tree[fx].rs].dis+1;
            fx=tree[fx].fa2;
        }
        return ;
    }
    int del(int x)
    {
        if(tree[x].fa2==x){
            return pop(x);
        }
        int tmp=find(x);
        del1(x);
        return tmp;
    }
}H1,H2;
int main()
{
    int n;
    scanf("%d",&n);
    H1.init(n);
    H2.init(n);
    for(int i=1;i<=n;i++){
        scanf("%d",&H1.tree[i].val);
        H2.tree[i].val=H1.tree[i].val;
    }
    int root=H2.build(n);
    int sum=0;
    int q;
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        string a;
        cin>>a;
        if(a=="U"){
            int x,y;
            scanf("%d%d",&x,&y);
            x=H1.find(x);
            y=H1.find(y);
            if(x==y)continue;
            root=H2.del(H1.merge(x,y)==x?y:x);
        }
        if(a=="A1"){
            int x,y;
            scanf("%d%d",&x,&y);
            int tmp=H1.get_val(x)+y;
            int x1=H1.find(x);
            int tmp1=H1.del(x);
            H1.tree[x].val=tmp;
            H1.tree[x].fa=H1.tree[x].fa2=x;
            x=H1.merge(tmp1,x);
            root=H2.del(x1);
            H2.tree[x].val=H1.tree[x].val;
            H2.tree[x].fa=H2.tree[x].fa2=x;
            root=H2.merge(root,x);
        }
        if(a=="A2"){
            int x,y;
            scanf("%d%d",&x,&y);
            x=H1.find(x);
            printf("x: %d\n", x);
            H1.tree[x].val+=y;
            H1.tree[x].lz+=y;
            root=H2.del(x);
            H2.tree[x].val=H1.tree[x].val;
            H2.tree[x].fa=H2.tree[x].fa2=x;
            root=H2.merge(root,x);
            printf("%d\n", root);
        }
        if(a=="A3"){
            int x;
            scanf("%d",&x);
            sum+=x;
        }
        if(a=="F1"){
            int x;
            scanf("%d",&x);
            printf("%d\n",H1.get_val(x)+sum);
        }
        if(a=="F2"){
            int x;
            scanf("%d",&x);
            x=H1.find(x);
            printf("%d\n",H1.tree[x].val+sum);
        }
        if(a=="F3"){
            printf("%d\n",H2.tree[root].val+sum);
        }
    }
}