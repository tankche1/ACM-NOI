#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
vector<long long>hav;
long long l;
long long getphi(long long x)
{
	long long ret=x;
	long long up=sqrt(x)+1;
	for(int i=2;i<=up;i++)
	{
		if(x%i==0)
		{
			ret/=i;ret*=i-1;
			while(x%i==0)x/=i;
		}
	}
	if(x!=1){ret/=x;ret*=x-1;}
	printf("ret:%I64d\n",ret);
	return ret;
}
long long qmul(long long d,long long c,long long P)
{
	long long ret=0;
	while(c)
	{
		if(c&1)ret=(ret+d)%P;
		d=(d+d)%P;
		c>>=1;
	}
	return ret;
}
long long qpow(long long d,long long c,long long P)
{
	long long ret=1;
	while(c)
	{
		if(c&1)ret=qmul(ret,d,P);
		d=qmul(d,d,P);
		c>>=1;
	}
	return ret;
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	for(int cas=1;;cas++)
	{
		scanf("%d",&l);
		if(l==0)break;
		long long ans=0;
		if(l%16l==0||l%5==0)ans=0;
		else
		{
			while(l%2l==0)l/=2l;
			long long phi=getphi(9l*l);
			hav.clear();
			long long up=sqrt(phi)+1;
			long long x=phi;
			for(int i=2;i<=up;i++)
			{
				while(x%i==0)
				{
					hav.push_back(i);x/=i;
				}
			}
			if(x!=1)hav.push_back(x);
			for(int i=0;i<hav.size();i++)
			{
				if(qpow(10,phi/hav[i],9l*l)==1)phi/=hav[i];
			}
			ans=phi;
		}
		printf("Case %d: %I64d\n",cas,ans);
	}
	return 0;
}
