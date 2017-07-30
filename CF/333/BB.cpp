# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
LL ans;
int n,q;
int h[maxn];
int x[maxn];
int dp[maxn][18];
int dp_pos[maxn][18];
int step=17;

int query(int L,int R){
    int j=log(R-L+1)/log(2);
    //printf("L:%d R:%d j:%d\n",L,R,j);
    if(dp[L][j]>dp[R-(1<<j)+1][j]) return dp_pos[L][j];
    else return dp_pos[R-(1<<j)+1][j];
}

void solve(int L,int R){
    if(L>=R) return;
    int pos=query(L,R-1);
   // printf("L:%d R:%d pos:%d\n",L,R,pos);
    ans+=(LL)x[pos]*(pos-L+1)*(R-pos);
    solve(L,pos);solve(pos+1,R);
}

int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",&h[i]);
    for(int i=1;i<n;i++)
        x[i]=abs(h[i]-h[i+1]);
    for(int i=1;i<n;i++)
        dp[i][0]=x[i],dp_pos[i][0]=i;
    for(int j=1;j<=step;j++){
        for(int i=1;i<n;i++){
             dp[i][j]=dp[i][j-1];dp_pos[i][j]=dp_pos[i][j-1];
             if(i+(1<<(j-1))<n){
                 if(dp[i][j]<dp[i+(1<<(j-1))][j-1]){
                         dp[i][j]=dp[i+(1<<(j-1))][j-1];dp_pos[i][j]=dp_pos[i+(1<<(j-1))][j-1];
                 }
             }
             //if(j<=2) printf("dp_pos[%d][%d]:%d\n",i,j,dp_pos[i][j]);
        }
    }

    int L,R;
    for(int i=1;i<=q;i++){
        scanf("%d%d",&L,&R);
        ans=0;
        solve(L,R);
        printf("%I64d\n",ans);
    }

    return 0;
}
