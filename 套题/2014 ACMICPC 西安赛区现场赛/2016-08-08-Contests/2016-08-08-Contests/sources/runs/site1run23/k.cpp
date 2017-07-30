#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define  fr(i,x,y) for(i=x;i<=y;i++)
using namespace std;
typedef long long LL;
int T;
LL n,m,ans;
int main()
{
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		if(n==0&&m==0){printf("1\n");continue;}
		if(n==0||m==0){printf("2\n");continue;}
		if(n==m){printf("2\n");continue;}
		ans=2;
		while(true)
		{
			if(n<m)swap(n,m);
			if(n%m==0){ans+=n/m-1;break;}
			ans+=n/m;
			n%=m;
		}
		cout<<ans<<endl;
	}
}
