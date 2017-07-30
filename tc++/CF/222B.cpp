#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;

#define N 100000
struct student {
    int w, c, n;
    inline bool operator < (const student &x) const {
        return c > x.c;
    }
} b[N + 1];
int n, m, a[N + 1], s, ans[N + 1], seq[N + 1];
priority_queue <student> h;

inline bool cmp(const student &a, const student &b) {
    return a.w < b.w;
}

inline bool cmp2(int x, int y) {
    return a[x] < a[y];
}

bool check(int x) {
    ll cost = 0LL;
    while (!h.empty()) h.pop();
    for (int i = n, p = m; i > 0; ) {
        while (p > 0 && b[p].w >= a[seq[i]]) h.push(b[p--]);
        if (h.empty()) return false;
        student cur = h.top();
        cost += (ll)cur.c;
        if (cost > (ll)s) return false;
        h.pop();
        for (int j = x; j > 0 && i > 0; --i, --j) ans[seq[i]] = cur.n;
    }
    return true;
}

int main(int argc, char *argv[]) {
    
    scanf("%d%d%d", &m, &n, &s);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) seq[i] = i;
    for (int i = 1; i <= m; ++i) scanf("%d", &b[i].w);
    for (int i = 1; i <= m; ++i) scanf("%d", &b[i].c);
    for (int i = 1; i <= m; ++i) b[i].n = i;
    sort(seq + 1, seq + n + 1, cmp2);
    sort(b + 1, b + m + 1, cmp);
    
    int l = 0, r = n + 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    
    if (r == n + 1) printf("NO\n");
    else {
        printf("YES\n");
        check(l);
        for (int i = 1; i < n; ++i) printf("%d ", ans[i]);
        printf("%d\n", ans[n]);
    }
    
    return 0;
}