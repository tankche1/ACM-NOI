#include <cstdio>
#include <cstring>
#include <algorithm>
#define eps (1e-8)
#define INF 100000000 
using namespace std;

struct str { int v,nex; double cap; } edge[1010000];

int vis[210],d[210],fst[210],done[210],p[210],que[1010000];
int s,t,e,cl;
int n,T,t_;

void make_edge(int a,int b,double cap) {
    edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].cap = cap;
    edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].cap = 0;
}

bool bfs() {
    int L = 0, R = 0; que[++R] = s; vis[s] = ++cl; d[s] = 0;
    while (L < R) {
	int u = que[++L];
	for (int i = fst[u]; i; i = edge[i].nex) {
	    int v = edge[i].v;
	    if (edge[i].cap >= eps && vis[v] != cl) {
		vis[v] = cl;
		d[v] = d[u] + 1;
		que[++R] = v;
	    }
	}
    }
    return (vis[t] == cl);
}

double dfs(int u, double ma) {
    if (u == t || ma < eps) return ma;
    double f, flow = 0;
    for (int i = fst[u]; i; i = edge[i].nex) {
	int v = edge[i].v;
	if (d[v] == d[u] + 1 && ((f = dfs(v, min(ma, edge[i].cap))) > 0.0)) {
	    flow += f; ma -= f;
	    edge[i].cap -= f; edge[i ^ 1].cap += f;
	    if (ma < eps) return flow;
	}
    }
    d[u] = INF;
    return flow;
}

void dinic(double &ans) {
    while (bfs()) ans -= dfs(s,INF);
}

bool judge(double k) {
    s = n + 1; t = s + 1;
    for (int i = 1; i <= t; i++) fst[i] = 0;
    e = 1; double ans = 0;
    for (int i = 1; i <= n; i++) make_edge(s, i, done[i] / 2.0);

    for (int i = 1; i <= n; i++) {
	for (int j = i + 1; j <= n; j++) {
	    if (p[i] > p[j]) {
		make_edge(i, j, 0.5);
		make_edge(j, i, 0.5);
		ans++;
	    }
	}
    }
    
    for (int i = 1; i <= n; i++) make_edge(i, t, k);

    dinic(ans);
    return (ans > 0.0);
}

int main() {
    //freopen("C.in","r",stdin);
    //freopen("C.out","w",stdout);
    for (scanf("%d",&T); T; T--) {
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) done[i] = 0;
	
	for (int i = 1; i <= n; i++) {
	    scanf("%d",&p[i]);
	}

	for (int i = 1; i <= n; i++)
	    for (int j = i + 1; j <= n; j++)
		if (p[i] > p[j]) done[i]++, done[j]++;
	
	double L = 0, R = 100000;
	while (L < R - eps) {
	    double mid = (L + R) / 2.0;
	    if (judge(mid)) L = mid;
	    else R = mid;
	}

	printf("Case #%d: %.10lf\n",++t_,(L + R) / 2.0);
    } 
    return 0;
}
