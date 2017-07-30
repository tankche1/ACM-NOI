#include <bits/stdc++.h>

using namespace std;

const int mo = (int) 1e9 + 7;
typedef long long ll;

int n, m, k, q[1000010], Inv_n[1000010], Inv_mo[1000010];
ll C[1000010], ans;

inline ll Pow(ll a, int b)
{
	ll res = 1;
	for (; b; b >>= 1, a = a * a % mo)
		if (b & 1) res = res * a % mo;
	return res;
}

inline void _Prepare()
{
	for (int i = 1; i <= 1000000; i ++)
		Inv_n[i] = Inv_mo[i] = 0;
	q[0] = 0;
	Inv_n[1] = Inv_mo[1] = 1;
	for (int i = 2; i <= 1000000; i ++)
		{
			if (!Inv_mo[i])
				{
					Inv_mo[i] = Pow(i, mo - 2);
					q[++ q[0]] = i;
				}
			for (int j = 1; j <= q[0] && i * q[j] <= 1000000; j ++)
				{
					Inv_mo[i * q[j]] = 1LL * Inv_mo[i] * Inv_mo[q[j]] % mo;
					if (i % q[j] == 0) break ;
				}
		}	
}

inline void Prepare()
{
	for (int i = 1; i <= k; i ++)
		Inv_n[i] = 0;
    Inv_n[1] = 1;
	for (int i = 2; i <= k; i ++)
		{
			if (!Inv_n[i])
				Inv_n[i] = Pow(i, n - 1);
			for (int j = 1; j <= q[0] && i * q[j] <= k; j ++)
				{
					Inv_n[i * q[j]] = 1LL * Inv_n[i] * Inv_n[q[j]] % mo;
					if (i % q[j] == 0) break ;
				}
		}
}

int main()
{
	//freopen("F.in", "r", stdin);
	_Prepare();
	int Test = 0; scanf("%d", &Test);
	for (int test = 1; test <= Test; test ++)
		{
			scanf("%d%d%d", &n, &m, &k);
			Prepare();
			ll mul = 1;
			for (ll i = 0; i < k; i ++)
				{
					ll Inv = Inv_mo[i + 1];
					mul = mul * ((ll)m - i) % mo * Inv % mo;
				}
			C[0] = 1;
			for (ll i = 0; i < k; i ++)
				{
					ll Inv = Inv_mo[i + 1];  //mo-2cifang
					C[i + 1] = C[i] * ((ll)m - i) % mo * Inv % mo;
				}
			ans = 0;
			int flag = k & 1;
			for (ll i = k; i >= 2; i --)
				{
					ll tt = Inv_n[i - 1]; //n-1cifang
					if ((i & 1) == flag) ans += C[i] * tt % mo * i % mo;
					else ans -= C[i] * tt % mo * i % mo;
				}
			ans = ans * mul % mo;
			printf("Case #%d: ", test);
			cout << ans << endl;
		}
	return 0;
}
