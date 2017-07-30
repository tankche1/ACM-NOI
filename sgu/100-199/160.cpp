# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int maxm=1010;
int n,m;
int a[maxn];
int dp[maxm],pre[maxm];
vector<int> print;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=0;i<m;i++) dp[i]=-1;
    dp[1]=0;
    for(int i=1;i<=n;i++){
            //printf("i:%d\n",i);
        for(int j=0;j<m;j++){
            if(dp[j]==-1||dp[j]==i) continue;
            if(dp[a[i]*j%m]==-1){
               // printf("to:%d\n",a[i]*j%m);
                dp[a[i]*j%m]=i;pre[a[i]*j%m]=j;
            }
        }
    }
    int ans;
    for(ans=m-1;ans>=0;ans--){
        if(dp[ans]!=-1) break;
    }
    printf("%d\n",ans);
    while(ans!=1){
        print.push_back(dp[ans]);ans=pre[ans];
    }

    if((int)print.size()>=1) printf("%d",print[(int)print.size()-1]);
    for(int i=(int)print.size()-2;i>=0;i--)
        printf(" %d",print[i]);puts("");
    return 0;
}
