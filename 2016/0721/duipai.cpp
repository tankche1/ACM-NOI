#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

const int N = 100010,M = 200010,mod = 1e9+7;
int color,tot,p,n,m,start;
int dfn[N],low[N],spot[M*2],nex[M*2],head[N],c[N];
long long all,mul,a[N],f[N],size[N],chmul[N];
bool v[N],is[N];

vector<int> have[N];

void add(int x,int y) {
    nex[++p] = head[x]; head[x] = p; spot[p] = y;
    nex[++p] = head[y]; head[y] = p; spot[p] = x;
}

long long mypow(long long a,int b)
{
    long long c = 1;
    for(; b; b>>=1) {
        if(b&1) c = c*a%mod;
        a = a*a%mod;
    }
    return c;
}

long long ni(long long x)
{
    return mypow(x, mod-2);
}

void tarjan(int x)
{
    low[x] = dfn[x] = ++tot;
    v[x] = 1;
    c[x] = color;
    have[color].push_back(x);
    mul = mul*a[x]%mod;
    long long mem;
    int tp,y,cnt = 0;
    for(tp = head[x]; tp; tp = nex[tp])
    {
        y = spot[tp];
        if(!dfn[y])
        {
            mem = mul;
            tarjan(y);
            low[x] = min(low[x], low[y]);
            if(low[y]>=dfn[x]) {
                cnt++;
                long long temp = mul*ni(mem)%mod;
                f[x] = (f[x]+temp)%mod;
                (chmul[x] *= temp ) %= mod;
            }
        }
        else if(v[y])
            low[x] = min(low[x], dfn[y]);
    }
    if(start==x && cnt>1 || start!=x && cnt)
        is[x] = 1;
}

long long cal(int x)
{
    long long temp,ret;
    temp = (all-size[c[x]])%mod;
    if(!is[x]) {
        if(have[c[x]].size()==1)
            ret = temp;
        else
            ret = (temp+size[c[x]]*ni(a[x]))%mod;
    }
    else ret = temp+f[x];
    return (ret%mod+mod)%mod;
}

int main()
{    freopen("1006.in","r",stdin);
    freopen("output.b","w",stdout);
    int test,i,j,x,y;
    int t=0;
    for(cin >> test; test--; ) {
        cin >> n >> m;
        for(i = 1; i<=n; i++)
            scanf("%I64d", &a[i]);

        for(i = 1; i<=n; i++)
            head[i] = 0;
        p = 0;

        for(i = 1; i<=m; i++) {
            scanf("%d%d", &x,&y);
            add(x,y);
        }

        for(i = 1; i<=n; i++) {
            f[i] = 0, chmul[i] = 1;
            is[i] = 0;
            dfn[i] = low[i] = v[i] = c[i] = 0;
        }

        tot = all = color = 0;
        for(i = 1; i<=n; i++)
            have[i].clear();
        for(i = 1; i<=n; i++)
            if(!dfn[i]) {
                color++;
                mul = 1; start = i; tarjan(i);
                all = (all+mul)%mod;
                size[color] = mul;
                for(j = 0; j<have[color].size(); j++)
                {
                    x = have[color][j];
                    if(x!=start) {
                        (f[x] += mul*ni(chmul[x]*a[x]%mod)) %= mod;
                    }
                }
            }
        long long ans = 0;
        for(i = 1; i<=n; i++) {
            ans = (ans+i*cal(i))%mod;
            //printf("i:%d is:%d ans:%I64d\n",i,is[i],cal(i));

        }
        printf("Case %d:%I64d\n", ++t,ans);
    }
    return 0;
}
