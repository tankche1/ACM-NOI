# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=30;
const LL INF=(LL)1<<60;
char s[maxn];

LL d[maxn][maxn];

int main(){
    int Case;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%s",s+1);
        int n=strlen(s+1);
        //printf("%d\n",n);

        for(int i=1;i<=n;i++){
            d[i][i]=s[i]-'0';
            for(int j=i+1;j<=n;j++){
                d[i][j]=d[i][j-1]*10+s[j]-'0';
            }
        }

        LL ans=-INF;
        for(int a=2;a<=n-3;a++){
            ans=max(ans,d[1][1]+d[2][a]-d[a+1][a+1]*d[a+2][a+2]/d[a+3][n]);
            ans=max(ans,d[1][a-1]+d[a][a]-d[a+1][a+1]*d[a+2][a+2]/d[a+3][n]);
        }
        printf("Case #%d: ",Tcase);
        printf("%lld\n",ans);
    }
    return 0;
}
