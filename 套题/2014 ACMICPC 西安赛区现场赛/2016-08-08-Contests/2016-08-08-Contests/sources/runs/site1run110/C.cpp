#include <bits/stdc++.h>

using namespace std;

const double INF = 1e9;
const double eps = 1e-8;

typedef int arr[300010];

arr head, pnt, next, lab, vis, q, a, d;
double cap[300010];
int n, tot, s, t, m;
pair<int, int> E[300010];

inline void add(int a, int b, double c)
{
	next[++tot] = head[a]; head[a] = tot; pnt[tot] = b; cap[tot] = c;
	next[++tot] = head[b]; head[b] = tot; pnt[tot] = a; cap[tot] = 0;
}

inline bool BFS()
{
	int h = 0, ta = 1; q[1] = t;
	for (int i = 1; i <= t; i ++) lab[i] = (int)INF, vis[i] = 0;
	lab[t] = 0; vis[t] = 1;
	while (h < ta)
		{
			int x = q[++h];
			for (int i = head[x]; i; i = next[i])
				if (cap[i ^ 1] > eps && !vis[pnt[i]])
					{
						lab[pnt[i]] = lab[x] + 1; vis[pnt[i]] = 1;
						if (pnt[i] == s) return true;
						q[++ta] = pnt[i];
					}
		}
	return false;
}

inline double DFS(int x, double a)
{
	double flow = 0;
	if (a < eps || x == t) return a;
	
	for (int i = head[x]; i; i = next[i])
		if (cap[i] > eps && lab[pnt[i]] == lab[x] - 1)
			{
				double tt = DFS(pnt[i], min(a, cap[i]));

				flow += tt, a -= tt, cap[i] -= tt, cap[i ^ 1] += tt;
				if (a < eps) return flow;
			}
	lab[x] = (int) INF;
	return flow;
}
			
inline bool check(double g)
{
	memset(head, 0, sizeof(head)); tot = 1;

	for (int i = 1; i <= n; i ++)
		add(s, i, 1.0 * m), add(i, t, 1.0 * m + 2 * g - d[i]);

	for (int i = 1; i <= m; i ++)
		add(E[i].first, E[i].second, 1.0), add(E[i].second, E[i].first, 1.0);

	double ans = 0;
	while (BFS())
		ans += DFS(s, INF);
	return (n * m - ans) / 2 > eps;
}

int main()
{
	//	freopen("C.in", "r", stdin);
	int Test = 0; scanf("%d\n", &Test);

	for (int test = 1; test <= Test; test ++)
		{
			memset(d, 0, sizeof(d)); m = 0;
			
			printf("Case #%d: ", test);
			scanf("%d\n", &n);
			for (int i = 1; i <= n; i ++)
				{
					scanf("%d", a + i);
					for (int j = 1; j < i; j ++)
						if (a[j] > a[i]) E[++m] = make_pair(j, i), d[i] ++, d[j] ++;
				}

			double l = 0, r = m;
			s = n + 1, t = n + 2;
			
			for (; l + eps < r; )
				{
					double mid = (l + r) / 2;
					if (check(mid)) l = mid; else r = mid;
				}
			printf("%.7lf\n", l);
		}
	return 0;
}
