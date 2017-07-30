#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 2010
const int Mo = 1000000007;
using namespace std;

int A[maxn],f[2][maxn],g[2][maxn];
int n,m,ansa,ansb;

void add(int &a,int b) {
	a += b;
	a %= Mo;
}

void solve(int k,int L,int R) {
	if (L == R) {
		f[k][1] = f[k][0] = 0;
		g[k][1] = g[k][0] = 1;
		return;
	}
	int o = k;
	if (A[L] + A[R] < m) {
		solve(k ^ 1,L + 1,R);
		memset(f[o],0,sizeof(f[o]));
		memset(g[o],0,sizeof(g[o]));
		for (int i = 0; i <= R - L; i++) {
			if (!g[k ^ 1][i]) continue;
			if (f[o][i] < f[o ^ 1][i]) {
				f[o][i] = f[o ^ 1][i];
				g[o][i] = g[o ^ 1][i];
			} else if (f[o][i] == f[o ^ 1][i])
				add(g[o][i],g[o ^ 1][i]);
			if (f[o][i + 1] < f[o ^ 1][i]) {
				f[o][i + 1] = f[o ^ 1][i];
				g[o][i + 1] = g[o ^ 1][i];
			} else if (f[o][i + 1] == f[o ^ 1][i]) {
				add(g[o][i + 1],g[o ^ 1][i]);
			}
		}
	} else {
		solve(k ^ 1,L,R - 1);
		memset(f[o],0,sizeof(f[o]));
		memset(g[o],0,sizeof(g[o]));
		for (int i = 0; i <= R - L; i++) {
			if (!g[k ^ 1][i]) continue;
			if (f[o][i] < f[o ^ 1][i] + i) {
				f[o][i] = f[o ^ 1][i] + i;
				g[o][i] = g[o ^ 1][i];
			} else if (f[o][i] == f[o ^ 1][i] + i)
				add(g[o][i],g[o ^ 1][i]);
			if (f[o][i + 1] < f[o ^ 1][i] + R - L - i) {
				f[o][i + 1] = f[o ^ 1][i] + R - L - i;
				g[o][i + 1] = g[o ^ 1][i];
			} else if (f[o][i + 1] == f[o ^ 1][i]) {
				add(g[o][i + 1],g[o ^ 1][i]);
			}
		}
	}
	return;
}

int main() {
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++) scanf("%d",&A[i]);
	//if (n == 1) { printf("%d %d",0,2); return 0; }
	sort(A + 1,A + n + 1);
	/*if (A[n] + A[n - 1] < m) {
		printf("%d ",0);
		int ans = 1;
		for (int i = 1; i <= n; i++) ans = ans * 2 % Mo;
		printf("%d",ans);
		return 0;
		}*/
	solve(0,1,n);
	ansa = 0; ansb = 0;
	for (int i = 0; i <= n; i++) {
		if (!g[0][i]) continue;
		if (ansa < f[0][i])
			ansa = f[0][i], ansb = g[0][i];
		else if (ansa == f[0][i])
			add(ansb,g[0][i]);
	}
	printf("%d %d",ansa,ansb);
	return 0;
}
