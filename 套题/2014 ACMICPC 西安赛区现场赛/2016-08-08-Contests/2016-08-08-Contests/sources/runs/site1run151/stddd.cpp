
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
inline long long get_LL() {
    LL res, t = 1; char c;
    while(!isdigit(c = getchar())) if(c == '-') t = -1;
    for(res = c - '0'; isdigit(c = getchar()); )
        res = res * 10 + c - '0';
    return res * t;
}

LL gcd(LL a, LL b) {
    LL t;
    while(b) {
        t = a;
        a = b;
        b = t % b;
    }
    return a;
}

int main() {
/*
    LL a, b;
    cin >> a >> b;

    int c;
    while(1) {
        c = getchar();
        LL t = a;
        a = b;
        b = abs(t - b);
        cout << b << endl;
    }
*/
    int T = get_int();
    for(int kase = 1; kase <= T; kase++) {
        printf("Case #%d: ", kase);

        LL a = get_LL(), b = get_LL();
        LL g;
        LL ans = 0;

        if(a == 0 || b == 0) {
            if(a == b) ans = 1;
            else ans = 2;
        }
        else if(a == b) {
            ans = 2;
        }
        else {
            if(a < b) {
                LL t = a;
                a = b;
                b = b - t;
            }
            g = gcd(a, b);
            a /= g; b /= g;

            while(b != 1) {
                ans += (a - b - 1) / b + 1;
                LL t = a;
                a = b;
                b = t % b;
            }
            ans += a + 1;
        }

        cout << ans << endl;
    }

    return 0;
}
