#include <cstdio>
typedef long long LL;

int Case, T;
LL a, b, cnt;

inline LL Solve(LL x, LL y)
{
	if (x % y == 0) return x / y - 2;
	LL res = x / y;
	return Solve(y, x % y) + res;
}

int main()
{
	scanf("%d", &Case);
	for (T = 1; T <= Case; T ++)
	{
		scanf("%lld%lld", &a, &b);
		if (a == b) cnt = 2;
		else cnt = Solve(a, b) + 3;
		printf("Case #%d: %lld\n", T, cnt);
	}
	return 0;
}
