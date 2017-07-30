#include<bits/stdc++.h>
#define N 26
const int M = 200005;
typedef long long LL;
using namespace std;
char s1[M+10], s2[M+10];
int T, l1, l2;
LL ans;

struct P_T{
	int nx[M][N], fail[M], cnt[M], len[M], S[M], n, last, p;
	int New(int l){
		for(int i = 0; i < N; i++) nx[p][i] = 0;
		cnt[p] = 0;
		len[p] = l;
		return p++;
	}
	void init(){
		p = 0, New(0), New(-1);
		last = 0, n = 0, S[n] = -1, fail[0] = 1;
	}
	int g_f(int x){
		while (S[n-len[x]-1] != S[n]) x = fail[x];
		return x;
	}
	void add(int c){
		c -= 'a', S[++n] = c;
		int cur = g_f(last);
		if (!nx[cur][c]){
			int now = New(len[cur]+2);
			fail[now] = nx[g_f(fail[cur])][c];
			nx[cur][c] = now;
		}
		last = nx[cur][c];
		cnt[last]++;
	}
	void count(){
		for(int i = p-1; i >= 0; i--)
			cnt[fail[i]] += cnt[i];
	}
} T1, T2;

void dfs(int x, int y){
	for(int i = 0; i < 26; i++){
		int Nx = T1.nx[x][i], Ny = T2.nx[y][i];
		if (Nx && Ny){
			ans += (LL)T1.cnt[Nx]*T2.cnt[Ny];
			dfs(Nx,Ny);
		}
	}
}

int main(){
	//freopen("sample.in","r",stdin);
	//freopen("sample.out","w",stdout);
	cin >> T;
	for(int cs = 1; cs <= T; cs++){
		printf("Case #%d: ", cs);
		scanf("%s%s", s1, s2);
		T1.init(), T2.init();
		l1 = strlen(s1), l2 = strlen(s2);
		for(int i = 0; i < l1; i++) T1.add(s1[i]);
		for(int i = 0; i < l2; i++) T2.add(s2[i]);
		T1.count(), T2.count();
		ans = 0;
		dfs(0,0);
		dfs(1,1);
		cout << ans << endl;
	}
}
