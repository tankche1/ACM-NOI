#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define maxn 100010
const int mod = (1e9+7);
int n = 0,m = 0,k = 0;
LL  fac[maxn];
inline LL QuickPow(LL a,LL b) {
    LL res = 1;
    while(b > 0) {
        if(b & 1) res = (res * a) % mod;
        a = (a * a) % mod; b >>= 1;
    }
    return res;
} 
int main() {
    int T = 0; scanf("%d",&T);
    fac[0] = 1;
    for(int i = 1;i <= 100000;++ i) {
        fac[i] = (fac[i-1] * (LL)(i)) % mod;
    }
    for(int Case = 1;Case <= T;++ Case) {
        scanf("%d%d%d",&n,&m,&k);
        LL A = fac[k]; A = QuickPow(A,mod-2);
        LL B = 1;
        for(int i = m;i >= (m-k+1);-- i)
            B = (B * LL(i)) % mod;
        A = (A * B) % mod;
        LL T1 =  ( QuickPow((LL)(k-1),n-1) * (LL)k ) % mod;
        LL T2 =  ( QuickPow((LL)(k-2),n-1) * (LL)(k-1) ) % mod;
        T1 = ( (T1 - T2) % mod + mod) % mod;
        printf("Case #%d: ",Case);
        cout << (T1 * A) % mod << endl;
    }
    return 0;
}
