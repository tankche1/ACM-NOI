#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<ctime>
#include<map>
#include<string>
#include<vector>
#include<set>

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

namespace Max_Density_Subgraph {
	#define MAXN 111
	#define MAXM 42222
	struct Tflow {
		int v[MAXM],next[MAXM],h[MAXN],tot;
		double c[MAXM];
		void clr() { Fill(h,tot = 0); }
		void add(int b,int e,double f) { //cerr << b << ' ' << e << ' ' << f << endl;
			v[++tot] = e; next[tot] = h[b]; h[b] = tot; c[tot] = f;
			v[++tot] = b; next[tot] = h[e]; h[e] = tot; c[tot] = 0;
		}
		int S,T,d[MAXN],found,gap[MAXN],cur[MAXN];
		double ans, flow;
		void aug(int i) {
			if (i == T) {
				ans += flow; found = true;
				return ;
			}
			int mind = T, z;
			double tf = flow;
			for (z = cur[i]; z; z = next[z]) if (c[z] > 0) {
				if (d[v[z]] + 1 == d[i]) {
					flow = min(flow,c[z]); cur[i] = z;
					aug(v[z]);
					if (found) break ; if (d[S] >= T) return ;
					flow = tf; 
				} mind = min(mind,d[v[z]]);
			}
			if (found) {
				c[z] -= flow; c[(z & 1) ? (z + 1) : (z - 1)] += flow;
			} else {
				if (--gap[d[i]] == 0) d[S] = T;
				for (int z = h[i]; z; z = next[z]) if (c[z]) mind = min(mind,d[v[z]]);
				++gap[d[i] = mind + 1]; cur[i] = h[i];
			}
		}
		void isap() {
			ans = 0; Fill(d,0); Fill(gap,0); gap[0] = T; For(i,1,T) cur[i] = h[i];
			while (d[S] < T) {
				flow = INF; found = false ;
				aug(S);
			}
		}
		double Sol(int _s,int _t) {
			S = _s; T = _t;
			isap();
			return ans;
		}
		#undef MAXN
		#undef MAXM
	} TF;

	struct Edge{
		int b, e;
		double weight;
		Edge() {}
		Edge(int _b, int _e, double _wei) : b(_b), e(_e), weight(_wei) {}
	};

	vector<Edge> v;

	int S, T;
	int n;
	double du[1111];
	void init(int n) {
		Max_Density_Subgraph::n = n;
		S = n + 1, T = S + 1;
		memset(du, 0, sizeof(du[0]) * (n + 10));
		v.clear();
	}

	void add_edge(int b, int e, double weight) {
		du[b] += weight / 2.0; du[e] += weight / 2.0; 
		v.push_back(Edge(b, e, weight / 2.0));
	}

	double solve() {
		double L = 0, R = n * n;
		for (int TIME = 0; TIME < 100; ++TIME) {
			//cout << TIME << endl;
			double mid = (L + R) / 2.0;
			TF.clr();
			double sum = 0;
			for (int i = 1; i <= n; ++i) {
				double c = du[i] - mid;
				if (c < 0) {
					TF.add(S, i, -c);
				} else {
					TF.add(i, T, c);
					sum += c;
				}
			}
			for (vector<Edge> :: iterator it = v.begin(); it != v.end(); ++it) {
				TF.add(it->b, it->e, it->weight);
				TF.add(it->e, it->b, it->weight);
			}

			double min_cut = TF.Sol(S,T);

			//printf("mid = %.3f ans = %.3f\n", mid, sum - min_cut);
			if (sum - min_cut > 0) L = mid; else R = mid;

		}

		return L;
	}

};

namespace brute {
	double solve(int n, int *A) {
		double ans = 0;
		For(S,1,(1 << n) - 1) {
			double cnt = __builtin_popcount(S);
			double cnt_inv = 0;
			For(i,1,n) For(j,i + 1,n) if ((S >> i - 1 & 1) && (S >> j - 1 & 1) && A[i] > A[j]) ++cnt_inv;
			ans = max(ans, cnt_inv / cnt);
		}
		return ans;
	}
};

int n;
int A[1111];
int Main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &A[i]);
	}

	Max_Density_Subgraph::init(n);

	for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) if (A[i] > A[j]) {
		Max_Density_Subgraph::add_edge(i,j,1);
	}

	double ans = Max_Density_Subgraph::solve();
	//double ans2 = brute::solve(n, A);

	//if (fabs(ans - ans2) > 1e-8) {
	//	cerr << "WA" << endl;
	//}
	printf("%.12f\n", ans);

	return 0;
}

int main() {

	int T; cin >> T;

	for (int TK = 1; TK <= T; ++TK) {
		printf("Case #%d: ", TK);

		Main();

	}

	return 0;
}

