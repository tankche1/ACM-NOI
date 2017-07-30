#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	int T;
	cin>>T;
	for(int tt=1;tt<=T;tt++)
	{
		int N,x;
		bool f=false;
		cin>>N;
		for(int i=1;i<=N;i++)
		{
			cin>>x;
			f|=x%3;
		}
		if(f) printf("Case #%d: No\n",tt);
		else printf("Case #%d: Yes\n",tt);
	}
}
