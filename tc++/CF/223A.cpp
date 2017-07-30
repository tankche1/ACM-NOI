#include <cstdio>

#ifdef WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

typedef long long ll;

#define N 100000
struct oper {
    int op, x, l, c;
    inline void read() {
        scanf("%d", &op);
        if (op == 1) scanf("%d", &x);
        else scanf("%d%d", &l, &c);
    }
} p[N + 1];
int n, m, a[N + 1], ans[N + 1];
ll q[N + 1];

int main(int argc, char *argv[]) {
    
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) p[i].read();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf(LLD, q + i);
    
    int cnt = 0, pos = 1;
    ll len = 0LL;
    for (int i = 1; i <= m; ++i)
        if (p[i].op == 1) {
            ++len;
            if (cnt < N) a[++cnt] = p[i].x;
            while (pos <= n && q[pos] == len)
                ans[pos++] = p[i].x;
        } else {
            ll nl = len + (ll)p[i].l * p[i].c;
            while (pos <= n && q[pos] <= nl)
                ans[pos++] = a[(q[pos] - len - 1) % p[i].l + 1];
            for (int t = p[i].c; cnt < N && t > 0; --t)
                for (int j = 1; cnt < N && j <= p[i].l; ++j)
                    a[++cnt] = a[j];
            len = nl;
        }
    
    for (int i = 1; i < n; ++i) printf("%d ", ans[i]);
    printf("%d\n", ans[n]);
    
    return 0;
}