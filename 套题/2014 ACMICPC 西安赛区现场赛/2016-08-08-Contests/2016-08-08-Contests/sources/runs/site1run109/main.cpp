#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<cctype>
#include<climits>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<bitset>
#include<complex>

using namespace std;

typedef pair<int, int> pii;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long LL;
typedef long double ld;

#define rep(i, x) for(int i = 0; i < (int)(x); i++)
#define outint(x) printf("%d\n", (x))

const int INF = 0x3f3f3f3f;
const double EPS = 1e-8;
const double PI = 3.1415926535897932384626433832795;

inline int get_int() {
    int res, t = 1; char c;
    while(!isdigit(c = getchar())) if(c == '-') t = -1;
    for(res = c - '0'; isdigit(c = getchar()); )
        res = res * 10 + c - '0';
    return res * t;
}

const int MOD = 1000000000 + 7;
const int MAXK = 1000000;

int Pow(int a, int n) {
    int res = 1;
    while(n) {
        if(n & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        n >>= 1;
    }
    return res;
}

int inv[MAXK + 10];

int C(int n, int m) {
    int now = 1;
    for(int k = 1; k <= m; k++) {
        now = 1LL * now * (n - k + 1) % MOD * inv[k] % MOD;
    }
    return now;
}
///#include <assert.h>
int main() {
    for(int i = 1; i <= MAXK; i++) inv[i] = Pow(i, MOD - 2);
    /*for (int i = 1; i <= MAXK; ++i)
        assert(1LL * i * inv[i] % MOD == 1);*/
    int T = get_int();
    for(int kase = 1; kase <= T; kase++) {
        int n = get_int(), m = get_int(), k = get_int();

        int ans = 0;
        if(k == 1) {
            if(n == 1) ans = 1;
            else ans = 0;
        }
        else {
            ans = 1LL * k * Pow(k - 1, n - 1) % MOD;
            ans = (1LL * ans - 1LL * k * (k - 1) % MOD * Pow(k - 2, n - 1) ) % MOD;
            ans = (ans + MOD) % MOD;
        }
        printf("Case #%d: ", kase);
        cout << 1LL * ans * C(m, k) % MOD << endl;
    }

    return 0;
}
