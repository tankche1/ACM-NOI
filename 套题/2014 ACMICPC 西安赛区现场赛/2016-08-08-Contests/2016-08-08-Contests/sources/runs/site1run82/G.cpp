#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair <int, int> Pii;
#define N 400000 + 5
#define Mod1 1306213
#define Mod2 1301551
#define Base 233
#define K 5
#define mp make_pair

int Case, T, len_s, len_t, tot, R_s[N], R_t[N], Pow_1[N], Pow_2[N], Id[N << 1];
int Hash_s1[N], Hash_s2[N], Hash_t1[N], Hash_t2[N], Size[2][N << 1];
LL ans;
bool New;
char s[N], t[N];
vector <int> Vec[N << 1];
map <Pii, int> Map;

inline void Prepare()
{
	Pow_1[0] = Pow_2[0] = 1;
	for (int i = 1; i <= 400000; i ++)
	{
		Pow_1[i] = Pow_1[i - 1] * Base % Mod1;
		Pow_2[i] = Pow_2[i - 1] * Base % Mod2;
	}
}

inline void Get_Hash()
{
	for (int i = 1; i <= len_s * 2 + 1; i ++)
	{
		Hash_s1[i] = Hash_s1[i - 1] * Base + s[i] - 'a' + K;
		Hash_s2[i] = Hash_s2[i - 1] * Base + s[i] - 'a' + K;
		Hash_s1[i] %= Mod1, Hash_s2[i] %= Mod2;
	}
	for (int i = 1; i <= len_t * 2 + 1; i ++)
	{
		Hash_t1[i] = Hash_t1[i - 1] * Base + t[i] - 'a' + K;
		Hash_t2[i] = Hash_t2[i - 1] * Base + t[i] - 'a' + K;
		Hash_t1[i] %= Mod1, Hash_t2[i] %= Mod2;
	}
}

inline int Get_Node(int op, int l, int r)
{
	int h_1, h_2;
	if (op == 0)
	{
		h_1 = (Hash_s1[r] + Mod1 - (1LL * Hash_s1[l] * Pow_1[r - l]) % Mod1) % Mod1;
		h_2 = (Hash_s2[r] + Mod2 - (1LL * Hash_s2[l] * Pow_2[r - l]) % Mod2) % Mod2;
	}
	else
	{
		h_1 = (Hash_t1[r] + Mod1 - (1LL * Hash_t1[l] * Pow_1[r - l]) % Mod1) % Mod1;
		h_2 = (Hash_t2[r] + Mod2 - (1LL * Hash_t2[l] * Pow_2[r - l]) % Mod2) % Mod2;
	}
	Pii x = mp(h_1, h_2);
	New = 0;
	if (!Map[x])
		Map[x] = ++ tot, New = 1;
	return Map[x];
}

inline void Manacher(char *p, int *r, int op)
{
	int id = 0, mx = 0, len = strlen(p + 1);
	for (int i = 1; i <= len; i ++)
	{
		if (mx > i) r[i] = min(mx - i, r[id * 2 - i]);
			else r[i] = 1;
		int u = Get_Node(op, i - r[i], i + r[i] - 1);
		while (i - r[i] > 0 && i + r[i] <= len && p[i - r[i]] == p[i + r[i]])
		{
			r[i] ++;
			int v = Get_Node(op, i - r[i], i + r[i] - 1);
			if (New) Vec[u].push_back(v);
			u = v;
		}
		Size[op][u] ++;
		if (i + r[i] > mx)
			mx = i + r[i], id = i;
	}
}

inline void dfs(int z)
{
	Id[z] = T;
	for (int i = 0; i < Vec[z].size(); i ++)
	{
		int d = Vec[z][i];
		dfs(d);
		Size[0][z] += Size[0][d];
		Size[1][z] += Size[1][d];
	}
	ans += 1LL * Size[0][z] * Size[1][z];
}

inline void Handle()
{
	ans = 0;
	for (int i = 1; i <= tot; i ++)
		if (Id[i] != T) dfs(i);
	int x = Get_Node(0, 0, 1);
	ans -= 1LL * Size[0][x] * Size[1][x];
	ans /= 2;
}

int main()
{
	Prepare();
	scanf("%d", &Case);
	for (T = 1; T <= Case; T ++)
	{
		for (int i = 1; i <= tot; i ++)
		{
			Vec[i].clear();
			Size[0][i] = Size[1][i] = 0;
		}
		tot = 0;
		Map.clear();
		memset(s, 0, sizeof(s));
		memset(t, 0, sizeof(t));
		scanf("%s%s", s + 1, t + 1);
		len_s = strlen(s + 1);
		len_t = strlen(t + 1);
		for (int i = len_s * 2; i; i -= 2)
			s[i] = s[i >> 1];
		for (int i = 1; i <= len_s * 2 + 1; i += 2)
			s[i] = 'z' + 1;
		for (int i = len_t * 2; i; i -= 2)
			t[i] = t[i >> 1];
		for (int i = 1; i <= len_t * 2 + 1; i += 2)
			t[i] = 'z' + 1;
		Get_Hash();
		Manacher(s, R_s, 0), Manacher(t, R_t, 1);
		Handle();
		printf("Case #%d: ", T);
		cout << ans << endl;
	}
	return 0;
}
