#include <cstdio>
#include <algorithm>
using namespace std;
#define N 100 + 5

int Case, T, n, A[N], Pos[N], Dp[N][N];

int main()
{
	scanf("%d", &Case);
	for (T = 1; T <= Case; T ++)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j ++)
				Dp[i][j] = 0;
		for (int i = 1; i <= n; i ++)
		{
			scanf("%d", A + i);
			Pos[A[i]] = i;
		}
		for (int i = 1; i <= n; i ++)
			for (int k = 1; k + Pos[i] - 1 <= n; k ++)
				for (int l = 1; l + Pos[i] <= n; l ++)
					Dp[Pos[i]][k] = max(Dp[Pos[i]][k], Dp[l + Pos[i]][k - 1] + k - 1);
		int fz = 0, fm = 1;
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j ++)
				if (Dp[i][j] * fm > fz * j)
					fz = Dp[i][j], fm = j;
		double ans = 1.0 * fz / fm;
		printf("Case #%d: %7lf\n", T, ans);
	}
	return 0;
}
