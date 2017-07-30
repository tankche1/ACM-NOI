# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int dp[300];
int x1,x2,x3;
bool used[300];
int a[300];
int cnt=0;

void dfs(int dep){
    int tmp;
    if(dep>=10) return;
    //printf("dep:%d cnt:%d\n",dep,cnt);
    for(int i=0;i<cnt;i++){
        for(int j=i;j<cnt;j++){
            tmp=0;
            for(int k=0;k<8;k++){
                if((((a[i]>>k)&1)&((a[j]>>k)&1))==0) tmp^=1<<k;
            }
            if(used[tmp]) continue;
            used[tmp]=1;
            if(dp[tmp]==-1||dp[tmp]>dep) dp[tmp]=dep;
            a[cnt++]=tmp;
            dfs(dep+1);
            used[tmp]=0;
            cnt--;
        }
    }
}
int ans[M] = { 1, 5, 6, 3, 6, 3, 7, 4, 7, 8, 4, 5, 4, 5, 4, 1, 6, 3, 7, 4, 7, 4,
		9, 7, 8, 8, 7, 5, 7, 5, 7, 4, 7, 8, 4, 5, 8, 8, 7, 5, 8, 9, 5, 6, 8, 8,
		5, 5, 4, 5, 4, 1, 7, 5, 7, 4, 8, 8, 5, 5, 5, 7, 6, 4, 7, 8, 8, 8, 4, 5,
		7, 5, 8, 9, 8, 8, 5, 6, 5, 5, 4, 5, 7, 5, 4, 1, 7, 4, 8, 8, 5, 7, 5, 5,
		6, 4, 8, 9, 8, 8, 8, 8, 5, 7, 11, 9, 8, 9, 8, 9, 8, 8, 5, 6, 5, 5, 5, 5,
		6, 4, 8, 9, 8, 8, 8, 8, 8, 7, 8, 9, 9, 9, 9, 9, 10, 9, 5, 7, 6, 6, 6, 6,
		7, 6, 9, 9, 10, 9, 10, 9, 10, 10, 7, 6, 7, 7, 7, 7, 9, 7, 5, 7, 6, 6, 7,
		6, 7, 7, 5, 6, 2, 3, 6, 6, 4, 3, 6, 6, 7, 6, 7, 7, 9, 7, 6, 6, 4, 3, 7,
		7, 7, 6, 5, 7, 7, 6, 6, 6, 7, 7, 5, 6, 6, 6, 2, 3, 4, 3, 6, 6, 7, 7, 7,
		6, 9, 7, 6, 6, 7, 7, 4, 3, 7, 6, 5, 6, 6, 6, 6, 6, 7, 7, 8, 9, 5, 6, 5,
		6, 2, 5, 2, 3, 4, 3, 4, 3, 7, 6, 5, 6, 2, 5, 2, 5, 4, 1 };
int main(){
    /*freopen("output.txt","w",stdout);
    int x1,x2,x3;
    memset(dp,-1,sizeof(dp));
    memset(used,false,sizeof(used));
    x1=15;x2=51;x3=85;
    dp[0]=dp[255]=1;
    dp[x1]=dp[x2]=dp[x3]=1;
    a[cnt++]=0;a[cnt++]=255;a[cnt++]=x1;a[cnt++]=x2;a[cnt++]=x3;
    used[0]=used[255]=used[x1]=used[x2]=used[x3]=1;
    dfs(2);
    for(int i=0;i<256;i++){
        printf("%d,",dp[i]);
    }*/
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        printf("%d\n",ans[n]);
    }
    return 0;
}
