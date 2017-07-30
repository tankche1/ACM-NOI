#include <bits/stdc++.h>

using namespace std;

const int N = 3400;
const int MOD = int(1e9) + 7;

inline int add(int a, int b) { return (a + b >= MOD) ? (a + b - MOD) : (a + b); }
inline int sub(int a, int b) { return (a - b < 0) ? (a - b + MOD) : (a - b); }
inline void inc(int &a, int b) { a = add(a, b); }
inline int mul(int a, int b) { return (a * 1ll * b) % MOD; }

char s[N];
vector <int> a;
int p, alpha;
int dp[N][N][2][2];

int div(const vector <int> &a, const int b, vector <int> &c) {
    c.clear();
    long long r = 0;
    for (int i = 0; i < a.size(); ++i) {
        r = r * 10ll + a[i];
        if (c.size() || r >= b) c.push_back(r / b);
        r %= b;
    }
    return r;
}

inline int calc_w(int c, int rm, int nrm) {
    if (rm) return p - calc_w(c, !rm, nrm);
    return c + 1 - nrm;
}

inline int calc_W(int c, int rm, int nrm) {//>=c
    if (rm) return sub(mul(p, c + 1), calc_W(c, !rm, nrm));
    if (c & 1) return sub(mul(c + 2, (c + 1) >> 1), nrm * (c + 1));
    return sub(mul(c + 1, (c + 2) >> 1), nrm * (c + 1));
}

int main() {
    freopen("output.txt","w",stdout);
    assert(scanf("%d %d", &p, &alpha) == 2);
    assert(scanf("%s", s) == 1);
    a.resize(strlen(s));
    for (int i = 0; i < a.size(); ++i) a[i] = s[i] - '0';

    vector <int> b, c;
    while (a.size()) {
        c.push_back(div(a, p, b));
        a = b;
    }
    reverse(c.begin(), c.end());
    if (alpha > c.size()) { puts("0"); return 0; }

    dp[0][0][1][0] = 1;
    int n = c.size();
    for (int i = 0; i <= n; ++i)
        for (int pw = 0; pw <= alpha; ++pw)
            for (int eq = 0; eq < 2; ++eq)
                for (int rm = 0; rm < 2; ++rm) {
                    int &cur = dp[i][pw][eq][rm];
                    if(cur>0)  printf("dp[%d][%d][%d][%d]:%d\n",i,pw,eq,rm,dp[i][pw][eq][rm]);
                    if(i==n) continue;
                    if (cur == 0) continue;
                    for (int nrm = 0; nrm < 2; ++nrm) {
                        int npw = min(pw + nrm, alpha);
                        if (!eq){
                            inc(dp[i + 1][npw][eq][nrm], mul(calc_W(p - 1, rm, nrm), cur));
printf("dp[%d][%d][%d][%d]:%d goto dp[%d][%d][%d][%d]:%d by %d\n",i,pw,eq,rm,dp[i][pw][eq][rm],i+1,npw,eq,nrm,dp[i+1][npw][eq][nrm],mul(calc_W(p - 1, rm, nrm), cur));
                        }
                        else {
                            if (c[i] != 0){
                                inc(dp[i + 1][npw][!eq][nrm], mul(calc_W(c[i] - 1, rm, nrm), cur));
printf("dp[%d][%d][%d][%d]:%d goto dp[%d][%d][%d][%d]:%d by %d\n",i,pw,eq,rm,dp[i][pw][eq][rm],i+1,npw,0,nrm,dp[i+1][npw][0][nrm],mul(calc_W(c[i] - 1, rm, nrm), cur));

                            }
                            inc(dp[i + 1][npw][eq][nrm], mul(calc_w(c[i], rm, nrm), cur));
printf("dp[%d][%d][%d][%d]:%d goto dp[%d][%d][%d][%d]:%d by %d\n",i,pw,eq,rm,dp[i][pw][eq][rm],i+1,npw,1,nrm,dp[i+1][npw][1][nrm],mul(calc_w(c[i], rm, nrm), cur));

                        }
                    }
                }

    int res = 0;
    for (int eq = 0; eq < 2; ++eq)
        inc(res, dp[n][alpha][eq][0]);
    printf("%d\n", res);

    return 0;
}
