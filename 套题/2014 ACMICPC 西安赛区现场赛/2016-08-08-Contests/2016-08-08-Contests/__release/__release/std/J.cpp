#include<bits/stdc++.h>

using namespace std;
#define For(i,l,r) for (int i = l; i <= r; ++i)
#define Cor(i,l,r) for (int i = l; i >= r; --i)
#define Fill(a,b) memset(a,b,sizeof(a))
#define FI first
#define SE second
#define MP make_pair
#define PII pair<int,int>
#define flt double
#define INF (0x3f3f3f3f)
#define MaxN 1020304
#define MaxNode 1020304
#define MD 1000000007
#define UPD(a,b) { a += (b); }

int d[100], MAP[100][100];
bool ancestor(int x, int y) {
	if (y == 0) return true;
	return d[y] - d[x] == MAP[x][y];
}

bool covered[100];
int n, A[100], vis[100], q[100], s[100], who[100];
long long cnt[100], f[100][100][100][2], tmp[100][100][100][2], sum[100][100][2], F[100][100][2];
vector<int> edges[100];
double dp[1 << 20];
int control[100][100];
int Main() {
	scanf("%d", &n);

	assert(1 <= n && n <= 50);

	For(i,1,n) For(j,1,n) {
		MAP[i][j] = (i != j) ? INF : 0;
	} 
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &A[i]);
		assert(0 <= A[i] && A[i] <= 100);
	}
	for (int i = 1; i <= n; ++i) edges[i].clear();
	for (int i = 2; i <= n; ++i) {
		int b = i, e;
		scanf("%d", &e);

		assert(1 <= b && b <= n);
		assert(1 <= e && e <= n);
		assert(b != e);

		edges[b].push_back(e);
		edges[e].push_back(b);
	
		MAP[b][e] = MAP[e][b] = 1;
	}

	For(k,1,n) For(i,1,n) For(j,1,n) MAP[i][j] = min(MAP[i][j], MAP[i][k] + MAP[k][j]);
	memset(vis, 0, sizeof(vis[0]) * (n + 10));
	int hd = 0, tl = 1;
	vis[q[1] = 1] = true;
	d[1] = 0;
	while (hd < tl) {
		int vex = q[++hd];
		for (vector<int> :: iterator it = edges[vex].begin(); it != edges[vex].end(); ++it) {
			if (vis[*it]) continue ;
			vis[q[++tl] = *it] = true;
			d[*it] = d[vex] + 1;
		}
	}
	q[n + 1] = 0; d[0] = INF;

	assert(tl == n); // connect.

	memset(vis, 0, sizeof(vis[0]) * (n + 10));

	for (int I = tl; I >= 1; --I) {
		int vex = q[I];
		int tot = 0;
		vis[vex] = true;
		s[vex] = 1;
		for (auto y : edges[vex]) {
			if (!vis[y]) continue ;
			s[vex] += s[y];
			who[++tot] = y;
			memcpy(tmp[tot], f[y], sizeof(f[y])); 
		}
		for (int i = 0; i <= tot + 2; ++i) memset(sum[i], 0, sizeof(sum[i]));

		memset(f[vex], 0, sizeof(f[vex]));
		Cor(J,n + 1,1) {
			int far = q[J];
			if (!ancestor(vex, far) || vex == far) continue ;
			For(i,1,tot) For(j,0,n) For(w,0,1) UPD(sum[i][j][w], tmp[i][far][j][w]);
			For(i,0,tot + 2) memset(F[i], 0, sizeof(F[i]));
			F[0][0][0] = 1;
			int curS = 0;
			For(i,0,tot - 1) {
				int newS = s[who[i + 1]];
				For(j,0,curS) For(w,0,1) if (F[i][j][w]) {
					For(tj, 0, newS) For(ww,0,1) {
						long long c = ancestor(who[i + 1], far) ? tmp[i + 1][far][tj][ww] : sum[i + 1][tj][ww];
						if (c) {
							UPD(F[i + 1][j + tj][w ^ ww], F[i][j][w] * c);
						}
					}
				}
				curS += s[who[i + 1]];
			}

			bool add = (d[far] - d[vex] > A[vex]);
			For(i,0,s[vex]) For(w,0,1) if (F[tot][i][w]) {
				UPD(f[vex][far][i + add][w], F[tot][i][w]); // 这个位置随便按，因为影响不到所选集合内的灯
				UPD(f[vex][vex][i][w ^ 1], F[tot][i][w]); // 这个位置被选进集合中
			}
		}
	}

	Fill(cnt, 0);
	For(i,1,n) For(j,0,n) {
		cnt[j] += f[1][i][j][1] - f[1][i][j][0];
	}

	//For(i,1,n) printf("%lld ", cnt[i]); puts("");
	double ans = 0;
	For(i,0,n - 1) {
		int c = n - i;
		ans += (double)(cnt[i] * n % (1000 * c)) / (c);
	}
	
	ans = fmod(ans, 1000);
	if (ans < 0) ans += 1000;
	printf("%.12f\n", ans);

	/*
	// ************************BRUTE for n <= 20 *************************
	For(i,1,n) For(j,1,n) control[i][j] = ancestor(i,j) && (d[j] - d[i] <= A[i]); 
	dp[0] = 0;
	For(S,1,(1 << n) - 1) {
		double pself = 0;
		double sumsucc = 0;
		For(i,1,n) {
			int ns = S; double sp = 0;
			For(j,1,n) if (control[i][j] && (ns >> j - 1 & 1)) ns -= (1 << j - 1);
			if (ns == S) pself += 1. / n;
			else {
				sumsucc += 1. / n * dp[ns];
			}
		}
		dp[S] = (sumsucc + 1) / (1 - pself);
	}
	double ans2 = dp[(1 << n) - 1];
	// ************************BRUTE*************************
	*/

	//printf("%.12f\n", ans2);

	return 0;
}

int main() {
	//freopen("input.txt","r",stdin); //freopen("output.txt","w",stdout);
	
	int T; cin >> T;
	
	assert(1 <= T && T <= 1000);

	for (int TK = 1; TK <= T; ++TK) {
		//if (TK % 1000 == 0) printf("%d testcases done.\n", TK);
		printf("Case #%d: ", TK);

		Main();

	}

	return 0;
}

