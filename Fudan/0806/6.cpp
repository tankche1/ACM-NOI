# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
int step=33;
int n;
int a[maxn];
LL sum[maxn];
int dp[40][maxn];
LL two[40];
LL sum2[maxn];
char c;
void read(int &a)
{
    a=0;
    c=getchar();
    for(;c<'0'||c>'9';c=getchar());
    for(;c>='0'&&c<='9';c=getchar())
        a=a*10+c-'0';
    return;
}
int main(){
    int tcase;
    int pos,R,lastR;
    LL ans;
    read(tcase);
    two[0]=1;
    for(int i=1;i<=36;i++) two[i]=two[i-1]<<1;
    //puts("fuck");
    sum2[0]=0;
    for(int i=1;i!=100001;i++) {
            sum2[i]=sum2[i-1]+i;
    }
    while(tcase--){
        read(n);sum[0]=0;

        for(int i=1;i!=n+1;i++)
           read(a[i]),sum[i]=sum[i-1]+a[i];
        for(int i=1;;i++)
            if(two[i]>sum[n]) {step=i;break;}
        for(int j=0;j!=step+1;j++){
            for(int k=1;k!=n+2;k++){
                if((sum[k]>=two[j])||(k==n+1)) {dp[j][1]=k-1;break;}
            }
            for(int i=2;i!=n+1;i++){
                for(int k=dp[j][i-1]+1;k!=n+2;k++){
                     if((sum[k]-sum[i-1]>=two[j])||(k==n+1)) {dp[j][i]=k-1;break;}
                }
            }
        }
        ans=0;
        for(int L=1;L!=n+1;L++){
            lastR=L-1;
            for(int j=1;j!=step+1;j++){
                R=dp[j][L];
                ans+=j*((LL)L*(R-lastR)+sum2[R]-sum2[lastR]);
                lastR=R;
                if(R==n) break;
            }
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
