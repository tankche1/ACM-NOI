# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;

typedef long long LL;
LL L,R;
int K;
LL tot;
int a[20];
int n;
LL dp[20],sumdp[20];
bool ok;
LL tmp;

void dfs(int cur){
    //printf("cur:%d\n",cur);
    if(cur>n) {tot++;return;}

    if(cur==1) {//printf("sum:%I64d\n",sumdp[n-1]);
            tot+=sumdp[n-1];}
    for(int i=(cur==1)?1:0;i<a[cur];i++){
        ok=true;
        for(int j=cur-1;j>=1&&j>=cur-(K-1);j--){
            if(a[j]==i) ok=false;
        }
        if(!ok) continue;

        tmp=1;
        int ii;
        for(ii=cur+1;ii<=K&&ii<=n;ii++) tmp*=(10-(ii-1));
        for(;ii<=n;ii++) tmp*=(10-(K-1));
        tot+=tmp;
    }

    for(int i=cur-1;i>=1&&i>=cur-K+1;i--){
        if(a[i]==a[cur]) return;
    }
    dfs(cur+1);
}

LL solve(LL x){
    LL xx=x;
    int num=0;
    while(xx>0) {num++;a[num]=xx%10;xx/=10;}
    n=num;
    for(int i=1;i<num-i+1;i++) swap(a[i],a[num-i+1]);
    tot=0;
    dfs(1);
    return tot;
}

int main(){
    while(scanf("%I64d%I64d%I64d",&L,&R,&K)!=EOF){
        dp[0]=1;
        dp[1]=9;
        for(int i=2;i<=K;i++) dp[i]=dp[i-1]*(10-(i-1));
        for(int i=K+1;i<=18;i++) dp[i]=dp[i-1]*(10-(K-1));
        sumdp[0]=1;
        for(int i=1;i<=18;i++) sumdp[i]=sumdp[i-1]+dp[i];

        LL ans=solve(R)-solve(L-1);
        printf("%I64d\n",ans);
    }
    return 0;
}
