#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;

typedef long long LL;

const int maxn = 100086 * 4, Mod = 998244353, G = 3;

int exp_mod(int now, int p)
{
	if (p == 0) return 1;
	int tmp = exp_mod(now, p / 2);
	tmp = ((LL)tmp * tmp) % Mod;
	if (p & 1) tmp = ((LL)tmp * now) % Mod;
	return tmp;
}

struct T
{
	int g[maxn], _g[maxn], z1, z2, tmp, temp;

	inline int reverse(int num, int n)
	{
		int u = 0;
		for (int i = 0; i < n; i++)
			u += ((num >> (n - i - 1)) & 1) << i;
			return u;
	}

	void FFT(int z[], int w[], int n, int style)
	{
		int len=1 << n, d, step;
		for (int i = 0; i < len; i++) z[i] = w[reverse(i,n)];
		for (int i = 1; i <= n; i++)
		{
			d = 1 << i;
			if (style == 1) step = g[i];
			else step = _g[i];
			for (int j = 0; j < len; j += d)
			{
				temp = 1;
				for (int k = j; k < j + d / 2; k++)
				{
					z1 = z[k];
					z2 = ((LL)z[k + d / 2] * temp) % Mod;
					z[k] = (z1 + z2) % Mod;
					z[k + d / 2] = (z1 - z2 + Mod) % Mod;
					temp = ((LL)temp * step) % Mod;
				}
			}
		}
		if (style == -1)
		{
			tmp = exp_mod(len, Mod - 2);
			for (int i = 0; i < len; i++)
				z[i] = ((LL)z[i] * tmp) % Mod;
		}
	}

	void pre(int l)
	{
		g[0] = _g[0] = 1;
		for (int i = 1; i <= l; i++)
		{
			g[i] = exp_mod(G, (Mod - 1) / (1 << i));
			_g[i] = exp_mod(g[i], Mod - 2);
		}
	}
}F;

int num_case, l, len, n, num[maxn], c[maxn], a[maxn], b[maxn], t1[maxn], t2[maxn];
bool cmp(int a, int b)
{
	return a > b;
}
#define qp exp_mod
int A[maxn],fac[maxn],inv[maxn];
void pre()
{
	fac[0]=1;inv[0]=1;
	for(int i=1;i<=100000;i++)
	{
		fac[i]=(LL)fac[i-1]*i%Mod;
		inv[i]=qp(fac[i],Mod-2);
	}
}
inline void read(int &a)
{
	int f=1;
	a=0;
	char ch=getchar();
	while (ch<'0'||ch>'9')
	{
		if (ch=='-') f*=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9')
	{
		a=a*10+ch-48;
		ch=getchar();
	}
	a*=f;
}
#define pc(x) putchar(x)
namespace ib {char b[100];}
inline void pint(int x)
{
    if(x==0) {pc(48); return;}
    if(x<0) {pc('-'); x=-x;}
    char *s=ib::b;
    while(x) *(++s)=x%10, x/=10;
    while(s!=ib::b) pc((*(s--))+48);
}
int main()
{
//	int fac;
//	freopen("1009.in","r",stdin);
//	freopen("1009_1.out","w",stdout);
	pre();
	scanf("%d", &num_case);
	while (num_case--)
	{
		//memset(c, 0, sizeof(c));
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)read(A[i]);
		sort(A+1,A+1+n);reverse(A+1,A+1+n);
		int he=qp(2,n);
		for(int i=1;i<=n;i++)
		{
			he=(LL)he*inv[2]%Mod;
			a[i]=(LL)he*fac[i-1]%Mod*A[i]%Mod;
		}
		for(int i=0;i<=n;i++)b[n-i]=inv[i];
		while ((1 << l) <= n * 2) l++;
		F.pre(l);
		len = 1 << l;
		F.FFT(t1, a, l, 1);
		F.FFT(t2, b, l, 1);
		for (LL i = 0; i < len; i++)
			t1[i] = ((LL)t1[i] * t2[i]) % Mod;
		F.FFT(c, t1, l, -1);
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			ans=(ans+(LL)inv[i-1]*c[n+i]%Mod)%Mod;
			pint(ans);pc(' ');
		}
		printf("\n");
	}
	return 0;
}
