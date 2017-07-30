#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;
#define x first
#define y second
#define pb push_back
#define mp make_pair

set<LL> s;
set<pair<LL, LL> > ss;
LL a, b;


int main() {
#ifdef lol
	freopen("k.in", "r", stdin);
	freopen("k.out", "w", stdout);
#endif

	s.clear();
	int T;
	scanf("%d", &T);
	for (int tt = 1; tt <= T; ++tt) {
		scanf("%lld %lld\n", &a, &b);
		printf("Case #%d: ", tt);
		if (a == b) {
			puts("2");
			continue;
		}
		ss.clear();
		s.clear();

		s.insert(a);
		s.insert(b);
		ss.insert(mp(a, b));
		LL c = abs(a - b);
		if (s.find(c) == s.end())
			s.insert(c);
		while (ss.find(mp(b, c)) == ss.end()) {
			ss.insert(mp(b, c));
			a = b, b = c, c = abs(a - c);
			if (s.find(c) == s.end())
				s.insert(c);
		}
		printf("%d\n", (int)s.size());
	}

	return 0;
}

