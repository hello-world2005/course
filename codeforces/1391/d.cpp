#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<bitset>
#include<string>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<map>

using namespace std;

int read()
{
	int ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}

const int N=1e6+5;
int n,m,mmap[5][N],dp[N][2][2][2],ans;
//因为 n<=m 故第一维只要开到 3 
char s[N];

int main()
{
	n=read();m=read();
	if(n>=4)
		printf("-1\n");
	else if(n==1)
		printf("0\n");
	else if(n==2) //n 为 2 的情况 
	{
		for(int i=1;i<=n;++i)
		{
			scanf("%s",s+1);
			for(int j=1;j<=m;++j)
				mmap[i][j]=s[j]-'0';
		}
		for(int i=1;i<=m;++i)
		{
			//转移 ( 最后一位 0 在这里请无视 
			dp[i][0][0][0]=min(dp[i-1][1][0][0],dp[i-1][0][1][0]);
			dp[i][0][1][0]=min(dp[i-1][1][1][0],dp[i-1][0][0][0]);
			dp[i][1][0][0]=min(dp[i-1][1][1][0],dp[i-1][0][0][0]);
			dp[i][1][1][0]=min(dp[i-1][1][0][0],dp[i-1][0][1][0]);
			
			//按实际情况修改这一列 
			if(mmap[1][i]==1) dp[i][0][0][0]++,dp[i][0][1][0]++;
			else dp[i][1][0][0]++,dp[i][1][1][0]++;
			if(mmap[2][i]==1) dp[i][0][0][0]++,dp[i][1][0][0]++;
			else dp[i][0][1][0]++,dp[i][1][1][0]++;
		}
		
		//统计答案 
		ans=0x7fffffff;
		ans=min(ans,dp[m][0][0][0]);
		ans=min(ans,dp[m][0][1][0]);
		ans=min(ans,dp[m][1][0][0]);
		ans=min(ans,dp[m][1][1][0]);
		printf("%d\n",ans);
	}
	else //n==3 的情况 
	{
		for(int i=1;i<=n;++i)
		{
			scanf("%s",s+1);
			for(int j=1;j<=m;++j)
				mmap[i][j]=s[j]-'0';
		}
		for(int i=1;i<=m;++i)
		{
			dp[i][0][0][0]=min(dp[i-1][1][0][1],dp[i-1][0][1][0]);
			dp[i][0][0][1]=min(dp[i-1][0][1][1],dp[i-1][1][0][0]);
			dp[i][0][1][0]=min(dp[i-1][1][1][1],dp[i-1][0][0][0]);
			dp[i][1][0][0]=min(dp[i-1][1][1][0],dp[i-1][0][0][1]);
			dp[i][0][1][1]=min(dp[i-1][1][1][0],dp[i-1][0][0][1]);
			dp[i][1][0][1]=min(dp[i-1][1][1][1],dp[i-1][0][0][0]);
			dp[i][1][1][0]=min(dp[i-1][0][1][1],dp[i-1][1][0][0]);
			dp[i][1][1][1]=min(dp[i-1][0][1][0],dp[i-1][1][0][1]);
			if(mmap[1][i]==1) dp[i][0][0][0]++,dp[i][0][0][1]++,dp[i][0][1][0]++,dp[i][0][1][1]++;
			else dp[i][1][0][0]++,dp[i][1][0][1]++,dp[i][1][1][0]++,dp[i][1][1][1]++;
			if(mmap[2][i]==1) dp[i][0][0][0]++,dp[i][0][0][1]++,dp[i][1][0][0]++,dp[i][1][0][1]++;
			else dp[i][0][1][0]++,dp[i][0][1][1]++,dp[i][1][1][0]++,dp[i][1][1][1]++;
			if(mmap[3][i]==1) dp[i][0][0][0]++,dp[i][0][1][0]++,dp[i][1][0][0]++,dp[i][1][1][0]++;
			else dp[i][0][0][1]++,dp[i][0][1][1]++,dp[i][1][0][1]++,dp[i][1][1][1]++;
		}
		ans=0x7fffffff;
		ans=min(ans,dp[m][0][0][0]);
		ans=min(ans,dp[m][0][0][1]);
		ans=min(ans,dp[m][0][1][0]);
		ans=min(ans,dp[m][1][0][0]);
		ans=min(ans,dp[m][0][1][1]);
		ans=min(ans,dp[m][1][0][1]);
		ans=min(ans,dp[m][1][1][0]);
		ans=min(ans,dp[m][1][1][1]);
		printf("%d\n",ans);
	}
	return 0;
} 
