#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;

struct Node {
	int x, y, f;
	Node(int _x = 0, int _y = 0, int _f = 0):x(_x), y(_y), f(_f) {}
};

int T, n, m, u, v;
vector <int> G[maxn];
int deg[maxn], cnt[maxn][maxn];
int dp[maxn][maxn][2];
queue <Node> Q;

int main() {
	//freopen("H.in", "r", stdin);
	scanf("%d", &T);
	for(int cas = 1; cas <= T; cas ++) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i ++) G[i].clear();
		memset(deg, 0, sizeof(deg));
		
		for(int i = 1; i <= m; i ++) {
			scanf("%d%d", &u, &v);
			G[v].push_back(u);
			deg[u] ++;
		}
		memset(dp, 0, sizeof(dp));
		for(int x = 1; x <= n; x ++) for(int y = 1; y <= n; y ++) if(x != y && deg[y] == 0) {
			dp[x][y][1] = 1; Q.push(Node(x, y, 1));
		}
		for(int x = 1; x <= n; x ++) {
			dp[x][x][0] = 1; Q.push(Node(x, x, 0));
			dp[x][x][1] = 1; Q.push(Node(x, x, 1));
		}
		
		for(int x = 1; x <= n; x ++) for(int y = 1; y <= n; y ++) cnt[x][y] = deg[y];
		
		while(!Q.empty()) {
			Node St = Q.front(); Q.pop();
			int x = St.x, y = St.y, f = St.f;
			if(f == 0) {
				for(unsigned i = 0; i < G[y].size(); i ++) {
					if(-- cnt[x][G[y][i]] == 0 && !dp[x][G[y][i]][1]) {
						dp[x][G[y][i]][1] = 1;
						Q.push(Node(x, G[y][i], 1));
					}
				}
			} else {
				for(unsigned i = 0; i < G[x].size(); i ++) {
					if(!dp[G[x][i]][y][0]) {
						dp[G[x][i]][y][0] = 1;
						Q.push(Node(G[x][i], y, 0));
					}
				}
			}
		}
		
		scanf("%d%d", &u, &v);
		printf("Case #%d: %s\n", cas, dp[v][u][1] ? "No" : "Yes");
	}
	return 0;
}
