# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=110;
int tcase;
char s[maxn];
int dp[maxn][2],n,cnt=0;
int main(){
    //freopen("B-large.in","r",stdin);
    //freopen("output2.txt","w",stdout);
    scanf("%d",&tcase);
    dp[1][1]=0;dp[1][0]=1;
    for(int i=2;i<=100;i++){
        for(int j=0;j<2;j++){
            if(((i&1)&&j==0)||(((i&1)==0)&&j==1)){
                dp[i][j]=dp[i-1][j^1]+1;
            }
            else dp[i][j]=dp[i-1][j];
        }
    }
    for(int Tcase=1;Tcase<=tcase;Tcase++){
        scanf("%s",s);
        n=strlen(s);
        cnt=1;
        for(int i=1;i<n;i++){
            if(s[i]!=s[i-1]) s[cnt++]=s[i];
        }
        printf("Case #%d: ",Tcase);
        printf("%d\n",dp[cnt][s[0]=='+']);
    }
    return 0;
}
