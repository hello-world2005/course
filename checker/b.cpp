#include <cstdio>
#include <algorithm>
#include <set>
#define qwq(c1,c2,c3,c4,c5) p=max(p,check(i,a_create(c1,c2,c3,c4,c5))),q=max(q,check(i,b_create(c1,c2,c3,c4,c5)))
using namespace std;
inline int read(){
   int s=0;
   char ch=getchar();
   while(ch<'0'||ch>'9') ch=getchar();
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s;
}
struct card{ char kind,num; bool operator <(const card &a)const{ if(a.num!=num) return a.num<num; return a.kind<kind; };};
struct cardset{ card c[13]; };
int four(cardset x)
{
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]++; break;
		case 'T': vis[10]++; break;
		case 'J': vis[11]++; break;
		case 'Q': vis[12]++; break;
		case 'K': vis[13]++; break;
		default: vis[x.c[i].num-48]++; break;
	}
	int res=0;
	for(int i=14; i; i--) if(vis[i]==4) res+=10000*i; else if(vis[i]) res+=i;
	if(res<10000) return 0;
	return res;
} 
//炸弹，不是炸弹返回0，不然返回值越大牌越大 
int three(cardset x)
{
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]++; break;
		case 'T': vis[10]++; break;
		case 'J': vis[11]++; break;
		case 'Q': vis[12]++; break;
		case 'K': vis[13]++; break;
		default: vis[x.c[i].num-48]++; break;
	}
	int res=0,t=15;
	for(int i=14; i; i--) if(vis[i]==3) res+=10000*i; else if(vis[i]) res+=i*t,t/=15;
	if(res<10000) return 0;
	return res;
} 
//三张，不是返回0，不然返回值越大牌越大 
int twopairs(cardset x)
{
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]++; break;
		case 'T': vis[10]++; break;
		case 'J': vis[11]++; break;
		case 'Q': vis[12]++; break;
		case 'K': vis[13]++; break;
		default: vis[x.c[i].num-48]++; break;
	}
	int res=0,t=15*15,ps=0;
	for(int i=14; i; i--) if(vis[i]==2) res+=t*i,t/=15,++ps; else if(vis[i]) res+=i;
	if(ps==2) return res;
	return 0;
} 
//两对，不是返回0，不然返回值越大牌越大 
int pair1(cardset x)
{
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]++; break;
		case 'T': vis[10]++; break;
		case 'J': vis[11]++; break;
		case 'Q': vis[12]++; break;
		case 'K': vis[13]++; break;
		default: vis[x.c[i].num-48]++; break;
	}
	int res=0,t=15*15,ps=0;
	for(int i=14; i; i--) if(vis[i]==2) res+=15*15*15*i,++ps; else if(vis[i]) res+=i*t,t/=15;
	if(ps) return res;
	return 0;
} 
//一对，不是返回0，不然返回值越大牌越大 
int threetwo(cardset x)
{
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]++; break;
		case 'T': vis[10]++; break;
		case 'J': vis[11]++; break;
		case 'Q': vis[12]++; break;
		case 'K': vis[13]++; break;
		default: vis[x.c[i].num-48]++; break;
	}
	int res=0;
	bool two=0;
	for(int i=14; i; i--) if(vis[i]==3) res+=10000*i; else if(vis[i]==2) res+=i,two=1;
	if(res<10000 || !two) return 0;
	return res;
} 
//三带二，不是返回0，不然返回值越大牌越大 
int flush(cardset x) 
{ 
	for(int i=1; i<5; i++) if(x.c[i].kind==x.c[i+1].kind) continue; else return 0;
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]=1; break;
		case 'T': vis[10]=1; break;
		case 'J': vis[11]=1; break;
		case 'Q': vis[12]=1; break;
		case 'K': vis[13]=1; break;
		default: vis[x.c[i].num-48]=1; break;
	}
	int t=15*15*15*15,res=0;
	for(int i=14; i; i--) if(vis[i]) res+=t*i,t/=15;
	return res;
}
//同花，不是同花返回0，不然返回值越大牌越大 
int high(cardset x) 
{ 
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]++; break;
		case 'T': vis[10]++; break;
		case 'J': vis[11]++; break;
		case 'Q': vis[12]++; break;
		case 'K': vis[13]++; break;
		default: vis[x.c[i].num-48]++; break;
	}
	int t=15*15*15*15,res=0;
	for(int i=14; i; i--) while(vis[i]--) res+=t*i,t/=15;
	return res;
}
//散牌，返回值越大牌越大 
int straight(cardset x)
{
	bool vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[1]=vis[14]=1; break;
		case 'T': vis[10]=1; break;
		case 'J': vis[11]=1; break;
		case 'Q': vis[12]=1; break;
		case 'K': vis[13]=1; break;
		default: vis[x.c[i].num-48]=1; break;
	}
	for(int i=1; i<=10; i++) if(vis[i] && vis[i+1] && vis[i+2] && vis[i+3] && vis[i+4]) return i+4;
	return 0;
}
//顺子，不是顺子返回0，不然返回最大的点数 
set<card> S;
card a[13],b[13];
card create(char x,char y) { card tmp; tmp.kind=x,tmp.num=y; return tmp; }
cardset a_create(int n,int m,int p,int q,int r) { cardset tmp; tmp.c[1]=a[n],tmp.c[2]=a[m],tmp.c[3]=a[p],tmp.c[4]=a[q],tmp.c[5]=a[r]; return tmp; }
cardset b_create(int n,int m,int p,int q,int r) { cardset tmp; tmp.c[1]=b[n],tmp.c[2]=b[m],tmp.c[3]=b[p],tmp.c[4]=b[q],tmp.c[5]=b[r]; return tmp; }
char x[13]={'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
char y[4]={'S','H','D','C'};
int check(int type,cardset s)
{
	switch(type)
	{
		case 1:
			if(flush(s) && straight(s)) return straight(s); else return 0;
			break;
		case 2:
			return four(s);
			break;
		case 3:
			return threetwo(s);
			break;
		case 4:
			return flush(s);
			break;
		case 5:
			return straight(s);
			break;
		case 6:
			return three(s);
			break;
		case 7:
			return twopairs(s);
			break;
		case 8:
			return pair1(s);
			break;
		case 9:
			return high(s);
			break;
	}
}
void debug1()
{
	//for(int i=1; i<=7; i++) cout<<a[i].kind<<a[i].num<<' '; puts("");
	//for(int i=1; i<=7; i++) cout<<b[i].kind<<b[i].num<<' '; puts("");
}
int compare()
{
	for(int i=1; i<=9; i++) 
	{
		int p=0,q=0;
		qwq(1,2,3,4,5);
		qwq(1,2,3,4,6);
		qwq(1,2,3,4,7);
		qwq(1,2,3,5,6);
		qwq(1,2,3,5,7);
		qwq(1,2,3,6,7);
		qwq(1,2,4,5,6);
		qwq(1,2,4,5,7);
		qwq(1,2,4,6,7);
		qwq(1,2,5,6,7);
		qwq(1,3,4,5,6);
		qwq(1,3,4,5,7);
		qwq(1,3,4,6,7);
		qwq(1,3,5,6,7);
		qwq(1,4,5,6,7);
		qwq(2,3,4,5,6);
		qwq(2,3,4,5,7);
		qwq(2,3,4,6,7);
		qwq(2,3,5,6,7);
		qwq(2,4,5,6,7);
		qwq(3,4,5,6,7);
		if(p==0 && q==0) continue;
		if(p>q) {
		debug1();return 1; }else return 0;
	}
	
}
void init() { S.clear(); for(int i=0; i<13; i++) for(int j=0; j<4; j++) S.insert(create(y[j],x[i])); }
void input(){ a[1].kind=getchar(),a[1].num=getchar(),getchar(),a[2].kind=getchar(),a[2].num=getchar(),getchar(),b[1].kind=getchar(),b[1].num=getchar(),getchar(),b[2].kind=getchar(),b[2].num=getchar(),getchar(),a[3].kind=b[3].kind=getchar(),a[3].num=b[3].num=getchar(),getchar(),a[4].kind=b[4].kind=getchar(),a[4].num=b[4].num=getchar(),getchar(),a[5].kind=b[5].kind=getchar(),a[5].num=b[5].num=getchar(),getchar(),S.erase(S.find(a[1])),S.erase(S.find(a[2])),S.erase(S.find(a[3])),S.erase(S.find(a[4])),S.erase(S.find(a[5])),S.erase(S.find(b[1])),S.erase(S.find(b[2])); }
void calc()
{
	int ans=0,tot=990;
	for(set<card>::iterator i=S.begin(); i!=S.end(); i++) for(set<card>::iterator j=i; j!=S.end(); j++) if(i!=j) a[6]=b[6]=*i,a[7]=b[7]=*j,ans+=compare();
	if(ans) printf("%d/%d\n",ans/__gcd(ans,tot),tot/__gcd(ans,tot)); else printf("0/1\n");
}
int main()
{
	int T=read();
	while(T--) init(),input(),calc();
	return 0;
}