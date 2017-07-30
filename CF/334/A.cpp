# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n;
char s[maxn];
int dp[maxn][3];
int main(){
    int zero,one;
    int n;
    scanf("%d",&n);
    scanf("%s",s+1);
    zero=0;one=0;dp[0][0]=0;dp[0][1]=-n-10;dp[0][2]=-n-10;
    int ans=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='0'){
            dp[i][0]=dp[one][0]+1;
            dp[i][1]=dp[zero][0]+1;
            dp[i][1]=max(dp[i][1],dp[one][1]+1);
            dp[i][2]=dp[one][2]+1;
            dp[i][2]=max(dp[i][2],dp[zero][1]+1);
            zero=i;
        }
        else{
            dp[i][0]=dp[zero][0]+1;
            dp[i][1]=dp[one][0]+1;
            dp[i][1]=max(dp[i][1],dp[zero][1]+1);
            dp[i][2]=dp[zero][2]+1;
            dp[i][2]=max(dp[i][2],dp[one][


                         1]+1);
            one=i;
        }
        ans=max(ans,max(dp[i][1],dp[i][2]));
    }
    if(dp[n][0]==n){
        printf("%d\n",ans);
    }
    else printf("%d\n",ans);
    return 0;
}
