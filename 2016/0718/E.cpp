# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=75;
char s[maxn];
int n;
int num[10];

bool judge(){
    bool ok=false;
    memset(num,0,sizeof(num));
    for(int i=0;i+1<n;i++){
        if(s[i+1]>s[i]){
            //printf("i:%d\n",i);
            for(int j=s[i]-'0'+1;j<=9;j++){
                if(num[j]>0) ok=true;
            }
        }
        num[s[i]-'0']++;
    }
    if(ok) {puts("-1");return false;}
    return true;
}
long long ans;
LL dp[maxn][10][2];
int op;

void dfs(int x){
    if(x>n) return;


    for(int k=0;k<s[x-1]-'0';k++){
        int oop=op;
        if(x>1&&op==1&&k>s[x-2]-'0') continue;
        if(x>1&&op==0&&k<s[x-2]-'0') oop=1;
        if(n-x==0) ans++;
        else ans+=dp[n-x][k][oop];
    }

    if(op==0){
        if(x>1&&s[x-1]-'0'<s[x-2]-'0') op=1;
    }
    dfs(x+1);
}

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%s",s);
        n=strlen(s);

        if(!judge()) continue;

        ans=0;
        memset(dp,0,sizeof(dp));
        for(int j=0;j<=9;j++){
            dp[1][j][0]=10;
            dp[1][j][1]=j+1;
           // printf("x:%d j:%d 0:%I64d 1:%I64d\n",1,j,dp[1][j][0],dp[1][j][1]);
        }

        for(int x=2;x<n;x++){
            for(int j=0;j<=9;j++){
                for(int k=j;k<=9;k++) dp[x][j][0]+=dp[x-1][k][0];
                for(int k=0;k<j;k++) dp[x][j][0]+=dp[x-1][k][1];

                for(int k=0;k<=j;k++) dp[x][j][1]+=dp[x-1][k][1];
               // printf("x:%d j:%d 0:%I64d 1:%I64d\n",x,j,dp[x][j][0],dp[x][j][1]);
            }
        }

        //printf("dp[%d][%d][%d]:%d \n",3,0,0,dp[3][0][0]);

        op=0;
        dfs(1);

        printf("%I64d\n",ans);
    }
    return 0;
}
