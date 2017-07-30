/*
f[i]=f[j]+(i-j+1)*(i-j)/2=f[j]+(j*j-j)/2+i*(-j)+i*(i+1)/2
Y(j)=f[j]+(j*j-j)/2
X(j)=j
K(i)=-i
*/
//#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
 
using namespace std;

typedef long long int64;

const int MAXN=1000005;

int n;
int64 a[MAXN],b[MAXN];
int64 dp[MAXN];
int64 qu[MAXN][2];

inline int64 calc(int i)
{
	return dp[i]+(int64)i*(i-1)/2;
}

inline int64 cross(int64 x1,int64 y1,int64 x2,int64 y2,int64 x3,int64 y3)
{
	return (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	dp[n]=a[n];
	b[n]=calc(n);
	int head=0,tail=0;
	qu[0][0]=n;
	qu[0][1]=b[n];
	for (int i=n-1;i>=0;i--)
	{
		int64 p=-i;
		while (head<tail&&p*qu[head][0]+qu[head][1]>=p*qu[head+1][0]+qu[head+1][1]) head++;
		dp[i]=p*qu[head][0]+qu[head][1]+a[i]+(int64)i*(i+1)/2;
		b[i]=calc(i);
		tail++;
		qu[tail][0]=i;
		qu[tail][1]=b[i];
		while (tail-head>=2&&cross(qu[tail-2][0],qu[tail-2][1],qu[tail-1][0],qu[tail-1][1],qu[tail][0],qu[tail][1])>=0)
		{
			qu[tail-1][0]=qu[tail][0];
			qu[tail-1][1]=qu[tail][1];
			tail--;
		}
	}
	printf("%lld\n",dp[0]);
	return 0;
}
