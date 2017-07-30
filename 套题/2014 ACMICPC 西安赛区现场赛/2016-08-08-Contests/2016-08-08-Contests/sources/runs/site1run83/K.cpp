#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define ll long long

int T,id;
ll A,B;

inline ll Gcd(ll A,ll B)
{
	ll t;
	while(B)
	{
		t = A;
		A = B;
		B = t-t/B*B;
	}
	return A;
}

inline ll Calc(ll a,ll b)
{
	if(a==0||b==0) return 1;
	if(a<b) return Calc(a+b,a)-1;
	ll k = (a-b)/b + 1, na, nb;
	if(k&1) na = b, nb = a-k*b;
	else na = a-k*b, nb = b;
	//printf("%lld %lld %lld\n",a,b,k);
	//printf("--> %lld %lld\n",na,nb);
	return k+Calc(na,nb);
}

int main()
{
//	freopen("K.in","r",stdin);
//	freopen("K.out","w",stdout);
	
	scanf("%d",&T);
	for(id=1;id<=T;id++)
	{
		printf("Case #%d: ",id);
		scanf("%lld%lld",&A,&B);
		if(A==0||B==0)
		{
			if(A==0&&B==0) printf("1\n");
			else printf("2\n");
			continue;
		}
		ll d = Gcd(A,B); A/=d; B/=d;
		printf("%lld\n",Calc(A,B));
	}
	
	return 0;
}

