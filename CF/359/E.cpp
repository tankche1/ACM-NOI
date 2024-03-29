# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxm=200010;
const int INF=2000000;
int n,m,q;
int u[maxm],v[maxm];
int ans[maxm];

struct Query{
    int l,r,s,t,bh;
    Query() {}
}Q[maxm];

bool cmp(Query A,Query B){
    return A.l<B.l;
}

int dp[maxn][maxn];

int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u[i],&v[i]);
    }

    for(int i=1;i<=q;i++){
        scanf("%d%d%d%d",&Q[i].l,&Q[i].r,&Q[i].s,&Q[i].t);Q[i].bh=i;
    }

    sort(Q+1,Q+q+1,cmp);
    int now=q;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=INF;
        }
    }

    for(int i=1;i<=n;i++) dp[i][i]=0;

    for(int l=m;l>=1;l--){
        //for(int i=1;i<=n;i++) dp[i][i]=l;

        //for(int i=1;i<=n;i++) dp[i][u[l]]=dp[i][v[l]]=min(dp[i][u[l]],dp[i][v[l]]);
        dp[u[l]][v[l]]=dp[v[l]][u[l]]=l;
        for(int i=1;i<=n;i++) {
            if(i!=u[l]&&i!=v[l])
                dp[u[l]][i]=dp[v[l]][i]=min(dp[u[l]][i],dp[v[l]][i]);
        }


        while(now>0&&Q[now].l==l){
            //printf("bh:%d dp:%d\n",Q[now].bh,dp[Q[now].s][Q[now].t]);
            ans[Q[now].bh]=dp[Q[now].s][Q[now].t]<=Q[now].r;now--;
        }
    }

    for(int i=1;i<=q;i++){
        if(ans[i]) puts("Yes");
        else puts("No");
    }
    return 0;
}
