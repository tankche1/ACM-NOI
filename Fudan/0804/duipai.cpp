#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define intl long long
using namespace std;
const int base = 10;

struct str {
	int v[1010],len;

	void init() {
		memset(v,0,sizeof(v));
		len = 0;
	}

	void operator += (str b) {
		len = max(b.len,len);
		for (int i = 1; i <= len; i++) v[i] += b.v[i];
		for (int i = 1; i <= len; i++) {
			if (v[i] >= base) {
				v[i + 1] ++; v[i] -= base;
				if (i == len) len++;
			}
 		}
	}

	void operator -= (str b) {
		len = max(b.len,len);
		for (int i = 1; i <= len; i++) v[i] -= b.v[i];
		for (int i = 1; i <= len; i++) {
			if (v[i] < 0) {
				v[i + 1]--; v[i] += base;
			}
		}
		while (len > 1 && v[len] == 0) len--;
	}

	bool operator < (str b) {
		if (b.len > len) return true;
		if (b.len < len) return false;
		for (int i = len; i; i--) {
			if (b.v[i] > v[i]) return true;
			if (b.v[i] < v[i]) return false;
		}
		return false;
	}

	void set(int a) {
		len = 1;
		v[1] = a;
	}

	void print() {
		intl Mo = 258280327LL;
		intl ans = 0;
		for (int i = len; i; i--) {
            //printf("%d",v[i]);
			ans = ans * 10LL + (intl) v[i];
			ans %= Mo;
		}
		//puts("");
		cout << ans << endl;
	}

} A[1010],B[1010],js,sj,m;

int T,n;
char s[1010];

int main() {
	freopen("1009.in","r",stdin);
	freopen("1009.out","w",stdout);
	A[1].set(1); A[2].set(1);

	for (int i = 3; i <= 1005; i++) {
		A[i] = A[i - 1]; A[i] += A[i - 2];
		//printf("i:%d\n",i);
		//A[i].print();
	}

	B[1] = A[1];
	for (int i = 2; i <= 1002; i++)
		B[i] = A[i + 1], B[i] += B[i - 1];

	for (scanf("%d",&T); T; T--) {
		scanf("%d",&n);
		scanf("%s",s + 1);
		m.init();
		m.len = strlen(s + 1);
		for (int i = 1; i <= m.len; i++) m.v[i] = s[m.len - i + 1] - '0';
		int u = 1;
		for (; B[u] < m; u++);
		u--; js.init(); sj.init();
		js = m; js -= B[u];
		if (u <= 1) {
			sj.set(0);
			sj += js;
			str papa; papa.init(); papa.set(1);
			sj -= papa;
		} else {
			sj = B[u - 2];
			sj += js;
		}
		sj.print();
	}
	return 0;
}
