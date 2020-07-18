#include <cstdio>
#include <algorithm>
#include <iostream>
    using namespace std;
    int a[200001],n,t;
    int fan(int aa,int b,int c)
    {
    	if(aa>=b)return 1;
    	if(c>min(a[aa],a[b]))return 0;
    	if(a[aa]<a[b])
    	return fan(aa+1,b,a[aa]);
    	else
    	return fan(aa,b-1,a[b]);
    }
    int main(){
        cin>>t;
        while(t--){ 
        int az=1;
    	cin>>n;
    	for(int i=1;i<=n;i++)cin>>a[i];
    	int l=1,y=n;
    	while(l<y)
    	{
    		int mid=(l+y)/2;
    		if(fan(mid,n,0))
    		y=mid;
    		else
    		l=mid+1;
    	}
    	cout<<l-1<<endl;
    	}
    	return 0;
    }