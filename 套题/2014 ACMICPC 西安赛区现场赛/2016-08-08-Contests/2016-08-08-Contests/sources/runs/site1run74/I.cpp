#include <bits/stdc++.h>

using namespace std;

const int maxn = 800000;

int T, n, a, b, c, d, l;

int ch[maxn][2];
bool vis[maxn];
int tot, root;

int newNode() {
	ch[tot][0] = ch[tot][1] = 0;
	vis[tot] = 0;
	return tot ++;
}

void insert(int x, int l) {
	int cur = root;
	for(int i = 0; i < l; i ++) {
		int c = (x & (1 << (31-i))) ? 1 : 0;
		if(!ch[cur][c]) ch[cur][c] = newNode();
		cur = ch[cur][c];
	}
	vis[cur] = 1;
}

vector <pair <int, int> > res;

void DFS(int cur, int x, int d) {
	if(vis[x]) return;
	if(ch[x][0]) DFS(cur, ch[x][0], d+1);
	else res.push_back(make_pair(cur, d+1));
	if(ch[x][1]) DFS(cur | (1 << (31-d)), ch[x][1], d+1);
	else res.push_back(make_pair(cur | (1 << (31-d)), d+1));
}

void print(pair <int, int> pr) {
	int x = pr.first, l = pr.second;
	int a = (x >> 24) & 255, b = (x >> 16) & 255, c = (x >> 8) & 255, d = x & 255;
	printf("%d.%d.%d.%d/%d\n", a, b, c, d, l);
}

int main() {
	//freopen("I.in", "r", stdin);
	scanf("%d", &T);
	for(int cas = 1; cas <= T; cas ++) {
		scanf("%d", &n);
		tot = 0; root = newNode();
		for(int i = 0; i < n; i ++) {
			scanf("%d.%d.%d.%d/%d", &a, &b, &c, &d, &l);
			insert((a << 24) + (b << 16) + (c << 8) + d, l);
		}
		
		res.clear();
		DFS(0, root, 0);
		printf("Case #%d:\n", cas);
		if(n == 0) printf("1\n0.0.0.0/0\n");
		else {
			printf("%d\n", (int)res.size());
			for(unsigned i = 0; i < res.size(); i ++) print(res[i]);
		}
	}
	return 0;
}
