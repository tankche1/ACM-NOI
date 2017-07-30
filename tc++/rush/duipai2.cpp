# include <cstdio>
# include <algorithm>
# include <cstring>
# include <cmath>
# define MAX_N 100010
# define mod 99997
# define rep(i,j,k) for(int i=j; i<=k; i++)
using namespace std;
struct State {
    int a[40];
    void Ordered() { sort(a+1,a+a[0]+1); }
    friend bool operator== (State x, State y) {
        rep(i,0,x.a[0])
            if (x.a[i] != y.a[i]) return 0;
        return 1;
    }
} Start, Map  [MAX_N];
int        f        [MAX_N];
int        num  [MAX_N];
double    dp  [MAX_N];
int        N, M, a, b, total;

int Root(int i)
{ return (f[i]==i)?i:f[i]=Root(f[i]); }

void Union(int x, int y)
{ x = Root(x), y = Root(y), f[x] = y; }

int Get_hash(State a) {
    int ret = 0;
    rep(i,1,a.a[0])
        ret = (ret + a.a[i]+a.a[i]*a.a[i]*a.a[i]*i*i) % mod;
    while (Map[ret].a[0] && !(Map[ret]==a)) ret++;
    if (Map[ret].a[0] == 0) Map[ret] = a;
    return ret;
}

double Dp(State now) {
    int st = Get_hash(now);
    if (dp[st] || now.a[0] == 1) return dp[st];
    dp[st] = 0;
    double same = 0;
    rep(i,1,now.a[0]) rep(j,1,i)
        if (i==j) same += (double)now.a[i]*(now.a[i]-1)/total/2;
        else {
            State go = now;
            go.a[i] += go.a[j], swap(go.a[j],go.a[go.a[0]]);
            go.a[0] --, go.Ordered();
            dp[st] += (double) now.a[i]*now.a[j]*Dp(go)/total;
        }
    dp[st] = (dp[st]+1) / (1-same);
    return dp[st];
}

int main() {
    scanf("%d%d",&N,&M);
    total = N*(N-1)/2;
    memset(num, 0, sizeof(num));
    rep(i,1,N) f[i] = i;
    rep(i,1,M) scanf("%d%d",&a,&b), Union(a,b);
    rep(i,1,N) num[Root(i)] ++;
    rep(i,1,N) if (Root(i)==i)
        Start.a[++Start.a[0]] = num[i];
    memset(dp, 0, sizeof(dp));
    if (Dp(Start)<1e-10) printf("0\n");
    else printf("%.6lf\n",Dp(Start));
    return 0;
}