#include<iostream>
#include<cstdio>
#include<vector>
#define ll long long
#define fo(i,x,y) for( int i=x;i<=y;++i)
#define go(i,x,y) for( int i=x;i>=y;--i)
using namespace std;
inline int read(){ int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') fh=-1; ch=getchar(); } while(isdigit(ch)){ x=(x<<1)+(x<<3)+ch-'0'; ch=getchar(); } return x*fh; }

vector<int> g;//g用来存储最下面那条线路 

int main(){
	int n=read(),k=(n-1)/6,ans=k*5,t=(n-1)%6,a,b,c,d,e;
	if(n==3){//注意当n等于3时最下面那条线路只会有1个车站，就会WA掉，特判一下就好了 
		puts("2\n2 1 2\n2 1 2\n2 1 2");
		return 0;
	} 
	//由于n-1不一定被6整除，因此在处理完前k个元结构后需要对剩下的t条线路进行特殊处理。 
	switch(t){
		case 1:ans+=2;break;
		case 2:ans+=2;break;
		case 3:ans+=3;break;
		case 4:ans+=4;break;
		case 5:ans+=5;break;	
	}
	cout<<ans<<endl;
	fo(i,1,k){
		a=(i-1)*5+1,b=a+1,c=b+1,d=c+1,e=d+1;//a,b,c,d,e是元结构里的五个顶点 
		printf("2 %d %d\n",a,d);
		printf("2 %d %d\n",a,d);
		printf("2 %d %d\n",b,d);
		printf("2 %d %d\n",b,e);
		printf("2 %d %d\n",c,e);
		g.push_back(a);g.push_back(b);g.push_back(c);
		if(t==1&&i==k){ 
			printf("2 %d %d\n2 %d %d\n",e+1,e+2,e+1,e+2);g.push_back(e+1);
			goto H;
		}
		printf("2 %d %d\n",c,e);
	}
	a=k*5+1,b=a+1,c=b+1,d=c+1,e=d+1;
	switch(t){
		//case 1:printf("2 %d %d\n",a,b);g.push_back(a);break;
		case 2:printf("2 %d %d\n2 %d %d\n",a,b,a,b);g.push_back(a);break;
		case 3:printf("2 %d %d\n2 %d %d\n2 %d %d\n",a,b,a,b,b,c);g.push_back(a);g.push_back(c);break;
		case 4:printf("2 %d %d\n2 %d %d\n2 %d %d\n2 %d %d\n",a,b,a,b,c,d,c,d);g.push_back(a);g.push_back(c);break;
		case 5:printf("2 %d %d\n2 %d %d\n2 %d %d\n2 %d %d\n2 %d %d\n",a,b,a,b,b,c,c,d,d,e);g.push_back(a);g.push_back(c);g.push_back(e);break;	
	}
	H:
	int s=g.size();
	cout<<s<<" ";
	fo(i,0,s-1) printf("%d ",g[i]); 
	return 0;
}
