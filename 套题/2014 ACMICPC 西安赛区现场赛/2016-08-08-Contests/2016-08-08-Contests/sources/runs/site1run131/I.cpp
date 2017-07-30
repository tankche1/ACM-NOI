#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 30000 + 5
#define M 640000 + 5

int Case, T, n, a, b, c, d, p, tot, m, Trie[M][2], Ans[M][9];
bool Flag[M];

struct Node
{
	int A[4], p;
	Node (int _a = 0, int _b = 0, int _c = 0, int _d = 0, int _p = 0)
	{
		A[0] = _a, A[1] = _b, A[2] = _c, A[3] = _d, p = _p;
	}
	bool operator < (const Node a) const
	{
		return p < a.p;
	}
}E[N];

inline int getint()
{
	char ch = '\n';
	for (; ch > '9' || ch < '0'; ch = getchar()) ;
	int res = ch - '0';
	for (ch = getchar(); ch <= '9' && ch >= '0'; ch = getchar())
		res = res * 10 + ch - '0';
	return res;
}

inline void Add(Node x)
{
	int z = 0;
	for (int i = 1; i <= x.p; i ++)
	{
		int u = (i - 1) >> 3, v = 7 - (i - 1 & 7);
		int j = (x.A[u] >> v) & 1;
		if (!Trie[z][j])
		{
			Trie[z][j] = ++ tot;
			Trie[tot][0] = Trie[tot][1] = 0;
		}
		z = Trie[z][j];
		if (Flag[z]) break ;
	}
	Flag[z] = 1;
}

inline void dfs(int z, int a, int b, int c, int d, int dep)
{
	int u = Trie[z][0], v = Trie[z][1];
	if ((u > 0) ^ (v > 0))
	{
		m ++;
		Ans[m][1] = a;
		Ans[m][2] = b;
		Ans[m][3] = c;
		Ans[m][4] = d;
		Ans[m][5] = dep + 1;
		if (u)
		{
			int t = dep >> 3, s = 7 - (dep & 7);
			Ans[m][t + 1] |= 1 << s;
		}
	}
	if (u) dfs(u, a, b, c, d, dep + 1);
	if (v)
	{
		int t = dep >> 3, s = 7 - (dep & 7);
		if (t == 0) a |= 1 << s;
		else if (t == 1) b |= 1 << s;
		else if (t == 2) c |= 1 << s;
		else if (t == 3) d |= 1 << s;
		dfs(v, a, b, c, d, dep + 1);
	}
}

int main()
{
	Case = getint();
	for (T = 1; T <= Case; T ++)
	{
		n = getint();
		bool ok = 0;
		for (int i = 1; i <= n; i ++)
		{
			a = getint(), b = getint(), c = getint(), d = getint(), p = getint();
			E[i] = Node(a, b, c, d, p);
			if (p == 0) ok = 1;
		}
		printf("Case #%d:\n", T);
		if (n == 0)
		{
			puts("1\n0.0.0.0/0");
			continue ;
		}
		else if (ok)
		{
			puts("0");
			continue ;
		}
		Trie[0][0] = Trie[0][1] = tot = m = 0;
		memset(Flag, 0, sizeof(Flag));
		sort(E + 1, E + n + 1);
		for (int i = 1; i <= n; i ++)
			Add(E[i]);
		dfs(0, 0, 0, 0, 0, 0);
		printf("%d\n", m);
		for (int i = 1; i <= m; i ++)
			printf("%d.%d.%d.%d/%d\n", Ans[i][1], Ans[i][2], Ans[i][3], Ans[i][4], Ans[i][5]);
	}
	return 0;
}
