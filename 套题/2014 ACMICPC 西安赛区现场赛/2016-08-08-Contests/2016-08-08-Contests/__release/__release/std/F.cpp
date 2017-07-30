#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <ctime>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

const int mod = (int) 1e9 + 7;
typedef long long LL;

int fpow(int a, int t, int mod) {
	int res = 1;
	for (; t; t >>= 1, a = (LL) a * a % mod)
		if (t & 1) res = (LL) res * a % mod;
	return res;
}
int fact[1111111];
int invfact[1111111];
int C(int n, int K) {
	if (K > n || K < 0) return 0;
	int res = 1;
	for (int x = n; x > n - K; --x) res = (LL) res * x % mod;
	res = (LL) res * fpow(fact[K], mod-2, mod) % mod;
	return res;
}
int COMB(int n, int K) {
	return (LL) fact[n] * invfact[K] % mod * invfact[n-K] % mod;
}
void pre(int n) {
	fact[0] = invfact[0] = 1;
	for (int i = 1; i <= n; ++i) {
		fact[i] = (LL) fact[i-1] * i % mod;
	}
	invfact[n] = fpow(fact[n], mod-2, mod);
	for (int i = n - 1; i >= 1; --i) {
		invfact[i] = (LL) invfact[i+1] * (i+1) % mod;
	}
}
int main() {

//	freopen("in","r",stdin);

	pre(1000000);

	int n = 0;
	int m = 0;
	int K = 0;
	int TK = 0;
	int cases; scanf("%d", &cases);
	while (cases--) {
		printf("Case #%d: ",++TK);
		assert(scanf("%d %d %d", &n, &m, &K) == 3);
		assert(1 <= n && n <= 1000000000);
		assert(1 <= m && m <= 1000000000);
		assert(1 <= K && K <= 1000000);
		assert(K <= n && K <= m);
		/*
		if (K > n) {
			puts("0");
			continue;
		}*/
		int c = 1;
		int ans = 0;
		for (int j = K; j >= 1; --j) {
			int tmp = (LL) j * fpow(j-1, n-1, mod) % mod;
			tmp = (tmp * c + mod) % mod;
			tmp = (LL) tmp * COMB(K, j) % mod;
			ans = (ans + tmp) % mod;
			c *= -1;
		}
		
		ans = (LL) ans * C(m, K) % mod;
		printf("%d\n", ans);
	}

	return 0;
}
