#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
long long ans,x,y;
void work(long long x,long long y)
{
	if(!y)
	{
		ans--;
		return ;
	}
	ans+=x/y;
	work(y,x%y);
}
int main()
{
//	freopen("test.in","r",stdin);

	int g,T=0;
	for(scanf("%d",&g);g--;)
	{
		printf("Case #%d: ",++T);
		cin>>x>>y;
		
		if(x!=y)
		{
			ans=2;
			if(x&&y)work(x,y);
		}
		else if(!x)ans=1;
		else ans=2;
		
		cout<<ans<<endl;
	}

	return 0;
}

