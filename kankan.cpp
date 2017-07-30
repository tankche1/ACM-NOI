#include <bits/stdc++.h>
#define ll long long
#define db double
#define fir first
#define sec second
#define mkp make_pair
#define pb push_back
#define uint unsigned int
#define vint vector <int> int
#define clr(a) memset(a, 0, sizeof a)
using namespace std;

const int MaxN = 100010, Block = 800, TB = 300;
struct query {
	int l, r, id;
	bool operator < (const query &a) const {
		if (l / TB != a.l / TB) return l / TB < a.l / TB;
		return r < a.r;
	}
}	q[MaxN];
ll ans[MaxN];

int cnt[MaxN], num[MaxN], a[MaxN];
vector <int> large;
bool vis[MaxN];
int n, m;

int tmp[MaxN];

ll get_ans() {
	for (int i = 1; i <= Block * 2; ++i) tmp[i] = num[i];
	ll ret = 0;
	int x = 1;
	for (int i = 1; i <= Block; ++i) {
		if (!tmp[i]) continue;
		if (tmp[i] >= 2) {
			ret += (tmp[i] / 2) * i * 2;
			tmp[i * 2] += tmp[i] / 2;
			tmp[i] &= 1;
		}

		if (tmp[i] & 1) {
			x = max(i + 1, x);
			while (tmp[x] == 0 && i + x <= Block * 2) ++x;
			if (i + x > Block * 2) break;
			ret += i + x;
			++tmp[i + x];
			--tmp[x];
		}
		tmp[i] = 0;
	}

	priority_queue <int, vector <int>, greater<int> > Q;
	for (int i = 1; i <= Block * 2; ++i)
		for (int j = 1; j <= tmp[i]; ++j) Q.push(i);
	for (auto i : large)
		if (cnt[i] > Block * 2) Q.push(cnt[i]);

	while (Q.size() >= 2) {
		int x = Q.top(); Q.pop();
		int y = Q.top(); Q.pop();
		ret += x + y;
		Q.push(x + y);
	}
	return ret;
}

void reverse(int x) {
	int u = a[x];
	if (vis[x]) {
		--num[cnt[u]];
		--cnt[u];
		++num[cnt[u]];
	} else {
		--num[cnt[u]];
		++cnt[u];
		++num[cnt[u]];
	}
	vis[x] ^= 1;
}
void move(int &x, int p) {
	while (x > p) {
		reverse(x);
		--x;
	}
	while (x < p) {
		++x;
		reverse(x);
	}
}

int main() {
	scanf("%d", &n);
	int mx = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		++cnt[a[i]];
		mx = max(mx, a[i]);
	}
	for (int i = 1; i <= mx; ++i)
		if (cnt[i] > Block * 2) large.pb(i);
	memset(cnt, 0, sizeof(cnt));

	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].id = i;
	}
	sort(q + 1, q + m + 1);
	int l = 0, r = 0;
	for (int i = 1; i <= m; ++i) {
		move(l, q[i].l - 1);
		move(r, q[i].r);
		if (q[i].l == q[i - 1].l && q[i].r == q[i - 1].r) ans[q[i].id] = ans[q[i - 1].id];
		else ans[q[i].id] = get_ans();
	}
	for (int i = 1; i <= m; ++i) printf("%I64d\n", ans[i]);
	return 0;
}