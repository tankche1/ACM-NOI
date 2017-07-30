#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int Mod = (int)1e9 + 7;

int T;
long long n,m,k,ans;
int inv[1000005];

long long Pow(long long a,long long b)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return ret;
}

long long C(long long m,long long k)
{
	long long ret = 1;
	for (long long i = m-k+1;i <= m;i ++) ret = ret * i % Mod;
	for (int i = 1;i <= k;i ++) ret = ret * inv[i] % Mod;
	return ret;
}

int main()
{
	//freopen("f.in","r",stdin);
	//freopen("f.out","w",stdout);
	ios::sync_with_stdio(false);
	inv[0] = 1;
	for (int i = 1;i <= 1000000;i ++) inv[i] = Pow(i,Mod-2);
	cin >> T;
	for (int cas = 1;cas <= T;cas ++)
	{
		cin >> n >> m >> k;
		long long ans = k * Pow(k-1,n-1) % Mod;
		long long sig = ((k-2)%2 == 0)?1:-1, Com = k;
		for (long long i = 2;i < k;i ++)
		{
			Com = Com * (k-i+1) % Mod * inv[i] % Mod;
			long long tmp = Com * i % Mod * Pow(i-1,n-1) % Mod * sig % Mod;
			while (tmp < 0) tmp += Mod;
			ans = (ans + tmp) % Mod;
			sig *= -1;
		}
		ans = ans * C(m,k) % Mod;
		cout << "Case #" << cas << ": " << ans << endl;
	}
	return 0;
}
