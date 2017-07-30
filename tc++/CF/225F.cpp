#include <cstdio>

using namespace std;

typedef long long llint;
const int MAXN = 1010, MAXV = 10100, OFF = MAXV - 50, MOD = 1000000007;

int a[MAXN], dp[2][2*MAXV], n;

int add (int &x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
    return x;
}

int main ()
{
    scanf ("%d", &n);
    for (int i = 0; i < n; ++i) scanf ("%d", a + i);

    int ans = 0;
    int curr = 0, next = 1;

    dp[0][OFF] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2 * MAXV; ++j) dp[next][j] = 0;
        for (int j = 0; j < 2 * MAXV; ++j) {
            if (!dp[curr][j]) continue;
            add (dp[next][j+a[i]], dp[curr][j]);
            add (dp[next][j-a[i]], dp[curr][j]);
        }
        add (ans, dp[next][OFF]);
        ++dp[next][OFF];
        curr ^= 1, next ^= 1;
    }

    printf ("%d\n", ans);

    return 0;
}