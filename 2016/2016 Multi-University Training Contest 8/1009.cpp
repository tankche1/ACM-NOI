#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
# include<algorithm>
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
int n;
int N,M;
const int maxm=100010;
int A[maxm];
LL two[maxm],jie[maxm];
LL inv[maxm];
int t1[maxn],t2[maxn];
int a[maxn],b[maxn],c[maxn];

void prepare(){
    two[0]=jie[0]=1;
    for(int i=1;i<=100000;i++){
        two[i]=two[i-1]*2%Mod;
        jie[i]=jie[i-1]*i%Mod;
    }
    inv[100000]=exp_mod(jie[100000],Mod-2);
    for(int i=99999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}

LL ans[maxn];
bool cmp(int a,int b){
    return a>b;
}

int main()
{
    prepare();
    /*scanf("%d%d",&N,&M);
    ++N; ++M; int t=N+M-1;
    for(int i=0;i<N;i++) scanf("%d",a+i);
    for(int i=0;i<M;i++) scanf("%d",b+i);
    fftinit(t); fft(a,0); fft(b,0);
    for(int i=0;i<K;i++) c[i]=(ll)a[i]*b[i]%MOD;
    fft(c,1);
    for(int i=0;i<t;i++) printf("%d ",c[i]);*/
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&A[i]);
        sort(A+1,A+n+1,cmp);
        for(int i=0;i<n;i++) a[i]=(jie[i]*two[n-(i+1)]%Mod)*A[i+1]%Mod;
        for(int i=0;i<=n;i++){
            b[i]=inv[n-i];
        }
        b[0]=0;
        N=n;M=n+1;

        int t=N+M-1,l=0,len;
        while((1<<l)<=t) l++;

        F.pre(l);len=1<<l;
        for(int i=N;i<len;i++) a[i]=0;
        for(int i=M;i<len;i++) b[i]=0;
        F.FFT(t1,a,l,1);
        F.FFT(t2,b,l,1);
        for(int i=0;i<len;i++) t1[i]=(LL)t1[i]*t2[i]%Mod;
        F.FFT(c,t1,l,-1);
        ans[0]=0;
        for(int i=1;i<=n;i++){
            ans[i]=(ans[i-1]+(LL)c[i+n-1]*inv[i-1])%Mod;
            printf("%I64d",ans[i]);
            printf(" ");
        }puts("");

    }
}
