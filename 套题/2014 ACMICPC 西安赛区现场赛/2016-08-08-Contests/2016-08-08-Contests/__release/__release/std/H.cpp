#include<bits/stdc++.h>

using namespace std;
#define For(i,l,r) for (int i = l; i <= r; ++i)
#define Cor(i,l,r) for (int i = l; i >= r; --i)
#define Fill(a,b) memset(a,b,sizeof(a))
#define PII pair<int,int>
#define FI first
#define SE second
#define MP make_pair

const int MaxN = 1020304;
typedef tuple<int,int,bool> status;
int n, m, a, b, out[233], cnt[233][233];
bool A[233][233], f[233][233][2];
status q[MaxN];
int Main() {
	cin >> n >> m;
	assert(2 <= n && n <= 100);
	assert(1 <= m && m <= n * (n - 1));
	For(i,1,n) For(j,1,n) A[i][j] = false ;
	For(i,1,n) out[i] = 0;
	For(i,1,m) {
		int b, e;
		scanf("%d %d", &b, &e);
		assert(!A[e][b]);
		assert(b != e);
		A[e][b] = true;
		++out[b];
	}
	cin >> a >> b;
	assert(a != b);
	For(i,1,n) For(j,1,n) f[i][j][0] = f[i][j][1] = cnt[i][j] = 0;
	int hd = 0, tl = 0;
	For(i,1,n) {
		f[i][i][0] = 1;
		q[++tl] = make_tuple(i, i, 0);
		f[i][i][1] = 1;
		q[++tl] = make_tuple(i, i, 1);
	}

	For(i,1,n) For(j,1,n) if (i != j && !out[i]) {
		f[i][j][0] = 1;
		q[++tl] = make_tuple(i, j, 0);
	}

	while (hd < tl) {
		status vex = q[++hd];
		int x = get<0>(vex), y = get<1>(vex), z = get<2>(vex);
		if (z) {
			For(j,1,n) if (A[x][j]) {
				++cnt[j][y];
				if (cnt[j][y] == out[j]) {
					if (f[j][y][0]) continue ;
					f[j][y][0] = true;
					q[++tl] = make_tuple(j,y,0);
				}
			}
		} else {
			For(j,1,n) if (A[y][j]) {
				if (f[x][j][1]) continue ;
				f[x][j][1] = true;
				q[++tl] = make_tuple(x,j,1);
			}
		}
	}

	if (f[a][b][0]) puts("No"); else puts("Yes");

	return 0;
}

int main() {
	//freopen("input.txt","r",stdin);
	int T; cin >> T;
	For(TTT,1,T) {
		printf("Case #%d: ", TTT);
		Main();
	}
	return 0;
}