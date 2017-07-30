#include <bits/stdc++.h>
using namespace std;
const int maxn=20;
typedef long long LL;
LL pre[1<<20];
LL mod=(LL)1<<32;
int g[1<<maxn],f[1<<20];
int n;
int num[1<<20];

void prepare(){
    num[0]=0;
    for(int i=1;i<(1<<18);i++){
        num[i]=1+num[i^(i&(-i))];
        //if(i<=20) printf("num[%d]:%d\n",i,num[i]);
    }
    pre[0]=1;
    for(int i=1;i<(1<<18);i++) pre[i]=pre[i-1]*233%mod;
}

bool is[1<<20],cho[1<<20];
int dp[1<<20];

void check(int st){
    is[st]=1;
    for(int i=1;i<=n;i++) if((st>>(i-1))&1){
        if((g[i]&st)!=st)  {is[st]=false;break;}
    }
    dp[st]=0;
    if(is[st]) dp[st]=num[st];
    else{
        for(int i=1;i<=n;i++) if((st>>(i-1))&1) dp[st]=max(dp[st^(1<<(i-1))],dp[st]);
    }
}

int main(){
    int T;
    char tt;
    scanf("%d",&T);
    prepare();
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            g[i]=0;
            for(int j=1;j<=n;j++){
                while((tt=getchar())&&tt!='0'&&tt!='1');
                if(tt=='1') g[i]=g[i]+(1<<(j-1));
                //g[i]+=1<<(i-1);
            }
            //g[i]+=(1<<(i-1));
        }
        cho[0]=true;
        for (int i=1;i<(1<<n);i++)
        {
            for (int j=0;j<n;j++)
                if (i>>j&1)
                {
                    if (!cho[i^(1<<j)]||(i&g[j+1])) cho[i]=false;
                    else cho[i]=true;
                    break;
                }
        }
        f[0]=0;
        for (int i=1;i<(1<<n);i++)
        {
            f[i]=INT_MAX;
            for (int s0=i;s0;s0=(s0-1)&i)
            {
                if (!cho[s0]) continue;
                f[i]=min(f[i],f[i^s0]+1);
            }
        }
        LL ans=0;
        int _max;
        for(int st=1;st<(1<<n);st++){
            _max=f[st];
            ans=(ans+(LL)_max*pre[st])%mod;//printf("st:%d _max:%d ans:%lld\n",st,_max,ans);
        }

        printf("%I64d\n",ans);
    }
    return 0;
}
