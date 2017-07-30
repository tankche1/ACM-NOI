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
//	freopen("k.in","r",stdin);
//	freopen("k.out","w",stdout);
	int t;
	ios::sync_with_stdio(false);
	cin>>T;
	fr(t,1,T)
	{
		cout<<"Case #"<<t<<": ";
		cin>>n>>m;
		if(n==0&&m==0){cout<<1<<endl;continue;}
		if(n==0||m==0){cout<<2<<endl;continue;}
		if(n==m){cout<<2<<endl;continue;}
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
