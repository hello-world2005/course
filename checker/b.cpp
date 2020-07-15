#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 210
#define ll long long
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
bool hav[N][N];
int mp[N],ans;
void pre()
{
    mp['S']=0,mp['H']=1,mp['D']=2,mp['C']=3;
    mp['A']=14,mp['K']=13,mp['Q']=12,mp['J']=11,mp['T']=10;
    for(int i=2;i<=9;i++)
    {
        mp[48+i]=i;
    }
}
struct poker
{
    int col;
    int val;
    void clear()
    {
        col=val=0;
    }
}Mokou[N],Kaguya[N],common[N];
poker mx_S[6],mx_K[6],now_SK[6],stk_A[6],stk_B[6];
int top_A,top_B;
bool cmp_col(const poker &a,const poker &b)
{return a.col==b.col?a.val>b.val:a.col<b.col;}
bool cmp_val(const poker &a,const poker &b)
{return a.val>b.val;}
char str[N];
poker pread()
{
    poker ret;ret.clear();
    ret.col=mp[(int)str[0]];
    ret.val=mp[(int)str[1]];
    hav[ret.col][ret.val]=1;
    return ret;
}
int get_type(poker A[6])
{
    for(int i=1;i<=5;i++)if(A[i].val==1)A[i].val=14;
    bool pd=0;
    sort(A+1,A+6,cmp_col);
    if(A[1].col==A[5].col)//鍚岃姳
    {
        //鍚岃姳澶ч『
        for(int i=1;i<=5;i++)
        if(A[i].val!=14-i+1)
        {
            pd=1;
            break ;
        }
        if(pd==0)return 10;
        //鍚岃姳椤?
        pd=0;
        for(int i=2;i<=5;i++)
        if(A[i].val!=A[i-1].val-1)
        {
            pd=1;
            break ;
        }
        if(pd==0)return 9;

        if(A[1].val==14)A[1].val=1;
        sort(A+1,A+6,cmp_col);
        pd=0;
        for(int i=2;i<=5;i++)
        if(A[i].val!=A[i-1].val-1)
        {
            pd=1;
            break ;
        }
        if(pd==0)return 9;
        for(int i=1;i<=5;i++)
        if(A[i].val==1)A[i].val=14;
    }
    //鍥涙潯
    sort(A+1,A+6,cmp_val);
    if(A[1].val==A[2].val&&A[2].val==A[3].val&&A[3].val==A[4].val)return 8;
    if(A[2].val==A[3].val&&A[3].val==A[4].val&&A[4].val==A[5].val)return 8;
    //婊″爞绾?
    sort(A+1,A+6,cmp_val);
    if(A[1].val==A[2].val&&A[2].val==A[3].val&&A[4].val==A[5].val)return 7;
    if(A[3].val==A[4].val&&A[4].val==A[5].val&&A[1].val==A[2].val)return 7;
    //鍚岃姳
    sort(A+1,A+6,cmp_col);
    if(A[1].col==A[5].col)return 6;
    //椤哄瓙
    sort(A+1,A+6,cmp_val);
    pd=0;
    for(int i=2;i<=5;i++)
    if(A[i].val!=A[i-1].val-1)
    {
        pd=1;
        break ;
    }
    if(pd==0)return 5;
    if(A[1].val==14)A[1].val=1;
    sort(A+1,A+6,cmp_val);
    pd=0;
    for(int i=2;i<=5;i++)
    if(A[i].val!=A[i-1].val-1)
    {
        pd=1;
        break ;
    }
    if(pd==0)return 5;
    for(int i=1;i<=5;i++)
    if(A[i].val==1)A[i].val=14;
    //涓夋潯
    sort(A+1,A+6,cmp_val);
    if(A[1].val==A[2].val&&A[2].val==A[3].val)return 4;
    if(A[2].val==A[3].val&&A[3].val==A[4].val)return 4;
    if(A[3].val==A[4].val&&A[4].val==A[5].val)return 4;
    //鍙屽
    sort(A+1,A+6,cmp_val);
    if(A[1].val==A[2].val&&A[3].val==A[4].val)return 3;
    if(A[1].val==A[2].val&&A[4].val==A[5].val)return 3;
    if(A[2].val==A[3].val&&A[4].val==A[5].val)return 3;
    //瀵瑰瓙
    sort(A+1,A+6,cmp_val);
    for(int i=1;i<=4;i++)
    if(A[i].val==A[i+1].val)return 2;

    sort(A+1,A+6,cmp_val);
    return 1;


}
int hhh;
bool comp(poker A[6],poker B[6])//A > B
{

    if(A[1].col==A[1].val&&A[1].val==0)return 0;
    if(B[1].col==B[1].val&&B[1].val==0)return 1;
    sort(A+1,A+6,cmp_val);sort(B+1,B+6,cmp_val);hhh++;
    int typea=get_type(A),typeb=get_type(B);
    if(typea>typeb)return 1;
    if(typea<typeb)return 0;
    if(typea==10)return 0;
    sort(A+1,A+6,cmp_val),sort(B+1,B+6,cmp_val);
    if(typea==9)
    {
        return A[1].val>B[1].val;
    }
    if(typea==8)
    {
        int sa=0,sb=0;
        if(A[2].val>B[2].val)return 1;
        if(A[2].val<B[2].val)return 0;

        if(A[1].val==A[2].val)sa=A[5].val;
        else sa=A[1].val;

        if(B[1].val==B[2].val)sb=B[5].val;
        else sb=B[1].val;

        return sa>sb;
    }
    if(typea==7)
    {
        int sa=0,sb=0;
        if(A[3].val>B[3].val)return 1;
        if(A[3].val<B[3].val)return 0;

        if(A[1].val==A[3].val)sa=A[5].val;
        else sa=A[1].val;

        if(B[1].val==B[3].val)sb=B[5].val;
        else sb=B[1].val;

        return sa>sb;
    }
    if(typea==6)
    {
        for(int i=1;i<=5;i++)
        {
            if(A[i].val>B[i].val)return 1;
            if(A[i].val<B[i].val)return 0;
        }
        return 0;
    }
    if(typea==5)
    {
        return A[1].val>B[1].val;
    }
    if(typea==4)
    {
        int A_s=0,A_d1=0,A_d2=0;
        int B_s=0,B_d1=0,B_d2=0;
        if(A[1].val==A[3].val)
        {
            A_s=A[1].val;A_d1=A[4].val,A_d2=A[5].val;
            if(A_d2>A_d1)swap(A_d2,A_d1);
        }
        else if(A[2].val==A[4].val)
        {
            A_s=A[2].val;A_d1=A[1].val,A_d2=A[5].val;
            if(A_d2>A_d1)swap(A_d2,A_d1);
        }
        else if(A[3].val==A[5].val)
        {
            A_s=A[3].val;A_d1=A[1].val,A_d2=A[2].val;
            if(A_d2>A_d1)swap(A_d2,A_d1);
        }

        if(B[1].val==B[3].val)
        {
            B_s=B[1].val;B_d1=B[4].val,B_d2=B[5].val;
            if(B_d2>B_d1)swap(B_d2,B_d1);
        }
        else if(B[2].val==B[4].val)
        {
            B_s=B[2].val;B_d1=B[1].val,B_d2=B[5].val;
            if(B_d2>B_d1)swap(B_d2,B_d1);
        }
        else if(B[3].val==B[5].val)
        {
            B_s=B[3].val;B_d1=B[1].val,B_d2=B[2].val;
            if(B_d2>B_d1)swap(B_d2,B_d1);
        }

        if(A_s>B_s)return 1;
        if(A_s<B_s)return 0;
        if(A_d1>B_d1)return 1;
        if(A_d1<B_d1)return 0;
        if(A_d2>B_d2)return 1;
        return 0;
    }
    if(typea==3)
    {
        top_A=top_B=0;
        if(A[1].val==A[2].val&&A[3].val==A[4].val)//5
        {
            if(A[1].val>A[3].val)
            stk_A[++top_A]=A[1],stk_A[++top_A]=A[2],stk_A[++top_A]=A[3],stk_A[++top_A]=A[4];
            else
            stk_A[++top_A]=A[3],stk_A[++top_A]=A[4],stk_A[++top_A]=A[1],stk_A[++top_A]=A[2];

            stk_A[++top_A]=A[5];
        }
        else if(A[1].val==A[2].val&&A[4].val==A[5].val)//3
        {
            if(A[1].val>A[4].val)
            stk_A[++top_A]=A[1],stk_A[++top_A]=A[2],stk_A[++top_A]=A[4],stk_A[++top_A]=A[5];
            else
            stk_A[++top_A]=A[4],stk_A[++top_A]=A[5],stk_A[++top_A]=A[1],stk_A[++top_A]=A[2];
            stk_A[++top_A]=A[3];
        }
        else if(A[2].val==A[3].val&&A[4].val==A[5].val)//1
        {
            if(A[2].val>A[4].val)
            stk_A[++top_A]=A[2],stk_A[++top_A]=A[3],stk_A[++top_A]=A[4],stk_A[++top_A]=A[5];
            else
            stk_A[++top_A]=A[4],stk_A[++top_A]=A[5],stk_A[++top_A]=A[2],stk_A[++top_A]=A[3];
            stk_A[++top_A]=A[1];
        }

        if(B[1].val==B[2].val&&B[3].val==B[4].val)//5
        {
            if(B[1].val>B[3].val)
            stk_B[++top_B]=B[1],stk_B[++top_B]=B[2],stk_B[++top_B]=B[3],stk_B[++top_B]=B[4];
            else
            stk_B[++top_B]=B[3],stk_B[++top_B]=B[4],stk_B[++top_B]=B[1],stk_B[++top_B]=B[2];

            stk_B[++top_B]=B[5];
        }
        else if(B[1].val==B[2].val&&B[4].val==B[5].val)//3
        {
            if(B[1].val>B[4].val)
            stk_B[++top_B]=B[1],stk_B[++top_B]=B[2],stk_B[++top_B]=B[4],stk_B[++top_B]=B[5];
            else
            stk_B[++top_B]=B[4],stk_B[++top_B]=B[5],stk_B[++top_B]=B[1],stk_B[++top_B]=B[2];
            stk_B[++top_B]=B[3];
        }
        else if(B[2].val==B[3].val&&B[4].val==B[5].val)//1
        {
            if(B[2].val>B[4].val)
            stk_B[++top_B]=B[2],stk_B[++top_B]=B[3],stk_B[++top_B]=B[4],stk_B[++top_B]=B[5];
            else
            stk_B[++top_B]=B[4],stk_B[++top_B]=B[5],stk_B[++top_B]=B[2],stk_B[++top_B]=B[3];
            stk_B[++top_B]=B[1];
        }
        for(int i=1;i<=top_A;i++)
        {
            if(stk_A[i].val>stk_B[i].val)return 1;
            if(stk_A[i].val<stk_B[i].val)return 0;
        }
        return 0;
    }
    if(typea==2)
    {
        int DA=0,DB=0;
        for(int i=1;i<=4;i++)
        if(A[i].val==A[i+1].val)DA=A[i].val;
        for(int i=1;i<=4;i++)
        if(B[i].val==B[i+1].val)DB=B[i].val;
        top_A=top_B=0;
        if(DA>DB)return 1;
        if(DA<DB)return 0;
        for(int i=1;i<=5;i++)
        if(A[i].val!=DA)stk_A[++top_A]=A[i];
        for(int i=1;i<=5;i++)
        if(B[i].val!=DB)stk_B[++top_B]=B[i];
        sort(stk_A+1,stk_A+top_A+1,cmp_val);
        sort(stk_B+1,stk_B+top_B+1,cmp_val);
        for(int i=1;i<=top_A;i++)
        {
            if(stk_A[i].val>stk_B[i].val)return 1;
            if(stk_A[i].val<stk_B[i].val)return 0;
        }
        return 0;

    }
    if(typea==1)
    {
        for(int i=1;i<=5;i++)
        {
            if(A[i].val>B[i].val)return 1;
            if(A[i].val<B[i].val)return 0;
        }
        return 0;
    }
}
int hh;
poker tmp[6];
void dfs_comp(int x,int cnt,int now)
{

    if(cnt==5)
    {    hh++;
        for(int i=1;i<=5;i++)tmp[i]=now_SK[i];

        if(now==0)
        {
            if(comp(tmp,mx_S))
            {
                for(int i=1;i<=5;i++)
                mx_S[i]=now_SK[i];
            }
        }
        else
        {
            if(comp(tmp,mx_K))
            {
                for(int i=1;i<=5;i++)
                mx_K[i]=now_SK[i];
            }
        }
        return ;
    }
    if(x==8)return ;

    if(now==0)
    now_SK[cnt+1]=Mokou[x];
    else now_SK[cnt+1]=Kaguya[x];
    dfs_comp(x+1,cnt+1,now);
    dfs_comp(x+1,cnt,now);
}
void dfs_poker(int x)
{
    if(x==3)
    {
        for(int i=1;i<=5;i++)mx_S[i].clear(),mx_K[i].clear(),now_SK[i].clear();
        dfs_comp(1,0,0);
        for(int i=1;i<=5;i++)now_SK[i].clear();
        dfs_comp(1,0,1);
        if(comp(mx_S,mx_K))ans++;
        return ;
    }
    for(int i=0;i<=3;i++)
    for(int j=2;j<=14;j++)
    {
        if(hav[i][j])continue ;
        hav[i][j]=1;
        Mokou[5+x].col=i,Mokou[5+x].val=j;
        Kaguya[5+x].col=i,Kaguya[5+x].val=j;
        dfs_poker(x+1);
        hav[i][j]=0;
    }
}
poker Ta[6],Tb[6];
int T;
int main()
{
//    freopen("poker.in","r",stdin);
//    freopen("poker.out","w",stdout);
    T=read();
    pre();
    while(T--)
    {
        memset(hav,0,sizeof(hav));
        ans=0;
        scanf("%s",str);
        Mokou[1]=pread();
        scanf("%s",str);Mokou[2]=pread();
        for(int i=1;i<=2;i++)
        {
            scanf("%s",str);
            Kaguya[i]=pread();
        }
        for(int i=1;i<=3;i++)
        {
            scanf("%s",str);
            common[i]=pread();
            Mokou[i+2]=Kaguya[i+2]=common[i];
        }
        dfs_poker(1);
        if(ans==0){
            puts("0/1");
        }
        else{
            int tmp=__gcd(ans,1980);
            printf("%d/%d\n",ans/tmp,1980/tmp);
        }
    }
}