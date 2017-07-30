#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1000010;
const ll mod = 1e9 + 7;

int T, n, m, k;
ll fac[maxn], inv[maxn];

ll fpow(ll x, int n) {
	ll a = 1;
	while(n) {
		if(n & 1) a = a * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return a;
}

ll C(int n, int m) {
	if(n < 0 || m < 0 || m > n) return 0;
	if(n >= maxn) {
		ll tmp = 1;
		for(int i = n; i >= n-m+1; i --) tmp = tmp * i % mod;
		return tmp * inv[m] % mod;
	}
	return fac[n] * inv[m] % mod * inv[n-m] % mod;
}

ll f(int k) {
	return k * fpow(k-1, n-1) % mod;
}

int main() {
	fac[0] = inv[0] = 1;
	for(int i = 1; i < maxn; i ++) fac[i] = fac[i-1] * i % mod;
	for(int i = 1; i < maxn; i ++) inv[i] = fpow(fac[i], mod - 2);
	
	scanf("%d", &T);
	for(int cas = 1; cas <= T; cas ++) {
		scanf("%d%d%d", &n, &m, &k);
		ll res = 0;
		for(int i = 0; i < k; i ++) {
			ll tmp = C(k, i) * f(k-i) % mod;
			if(i & 1) res = (res - tmp + mod) % mod;
			else res = (res + tmp) % mod; 
		}
		res = res * C(m, k) % mod;
		printf("Case #%d: %d\n", cas, (int)res);
	}
	return 0;
}
