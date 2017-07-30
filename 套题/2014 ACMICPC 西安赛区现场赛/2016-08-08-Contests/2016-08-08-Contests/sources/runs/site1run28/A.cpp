#include <bits/stdc++.h>
#define N 100 + 5

int Case, T, A[N], ans, n;

int main()
{
	scanf("%d", &Case);
	for (T = 1; T <= Case; T ++)
		{
		scanf("%d", &n);
		ans = 0;
		for (int i = 1; i <= n; i ++) scanf("%d\n", &A[i]), ans += A[i] % 3 == 0;
		if (ans == n) printf("Case #%d: Yes\n", T);
		else printf("Case #%d: No\n", T);
	}
	return 0;
}
