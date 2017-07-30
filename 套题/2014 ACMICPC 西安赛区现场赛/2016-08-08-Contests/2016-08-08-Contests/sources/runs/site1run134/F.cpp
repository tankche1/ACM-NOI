#include <bits/stdc++.h>

using namespace std;

const int mo = (int) 1e9 + 7;
typedef long long ll;

int n, m, k;
ll C[1000010], ans;

inline ll Pow(ll a, int b)
{
	ll res = 1;
	for (; b; b >>= 1, a = a * a % mo)
		if (b & 1) res = res * a % mo;
	return res;
}

int main()
{
	//	freopen("F.in", "r", stdin);

	int Test = 0; scanf("%d", &Test);
	for (int test = 1; test <= Test; test ++)
		{
			scanf("%d%d%d", &n, &m, &k);
			ll mul = 1;
			for (ll i = 0; i < k; i ++)
				{
					ll Inv = Pow(i + 1, mo - 2);
					mul = mul * ((ll)m - i) % mo * Inv % mo;
				}
			C[0] = 1;
			for (ll i = 0; i < k; i ++)
				{
					ll Inv = Pow(i + 1, mo - 2);
					C[i + 1] = C[i] * ((ll)m - i) % mo * Inv % mo;
				}
			ans = 0;
			int flag = k & 1;
			for (ll i = k; i >= 2; i --)
				{
					ll tt = Pow(i - 1, n - 1);
					if ((i & 1) == flag) ans += C[i] * tt % mo * i % mo;
					else ans -= C[i] * tt % mo * i % mo;
				}
			ans = ans * mul % mo;
			printf("Case #%d: ", test);
			cout << ans << endl;
		}
	return 0;
}
