# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10;
const int mod=(1e+9)+7;
typedef long long LL;
int n,sz,state;
LL dp[10][5120];
int block[10];
LL ans[10];

int num[10];

void get_num(int j){
    for(int i=n-sz+1;i>=1;i--){
        num[i]=j%(sz);
        j/=sz;
    }
}

int code(){
    int j=0;
    for(int i=1;i<=n+1-sz;i++){
        j=j*(sz);
        j=j+num[i];
    }
    return j;
}

int main(){
    int T,tt;
    char c;
    bool ok;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        ans[n]=1;
        for(int i=1;i<=n;i++){
            block[i]=0;
            for(int j=1;j<=n;j++){
                while((c=getchar())&&c!='o'&&c!='*');
                block[i]<<=1;
                block[i]^=(c=='o');
            }
            if(block[i]!=((1<<n)-1)) ans[n]=0;
        }

        ans[0]=1;
        memset(dp[0],0,sizeof(dp[0]));dp[0][0]=1;
        for(sz=2;sz<=n;sz++){
            state=1;
            for(int i=1;i<=n+1-sz;i++) state*=sz;
            //printf("state:%d\n",state);
            for(int i=0;i<n;i++){
                //printf("i:%d ",i);
                for(int j=0;j<state;j++) dp[i+1][j]=0;
                for(int j=0;j<state;j++){
                    if(!dp[i][j]) continue;
                    //printf("j:%d ",j);
                    //get_num(j);
                    //for(int ta=1;ta<=n+1-sz;ta++) printf("num[%d]:%d ",ta,num[ta]);printf("dp: %I64d\n",dp[i][j]);
                    for(int k=0;k<(1<<n);k++){
                        if((k&block[i+1])!=k) continue;
                        //printf("k:%d\n",k);
                        get_num(j);ok=true;
                        for(int l=1;l<=n-sz+1;l++){
                            if(((k>>(n+1-(l+sz)))&((1<<sz)-1))==((1<<sz)-1)){
                                num[l]++;
                            }
                            else num[l]=0;
                            if(num[l]>=sz) {ok=false;break;}
                        }
                        //for(int ta=1;ta<=n+1-sz;ta++) printf("num[%d]:%d ",ta,num[ta]);puts("");
                        if(!ok) continue;
                        tt=code();
                        //printf("tt:%d\n",tt);
                        dp[i+1][tt]+=dp[i][j];
                        while(dp[i+1][tt]>=mod) dp[i+1][tt]-=mod;
                    }

                }
            }

            ans[sz-1]=0;
            for(int j=0;j<state;j++){
                ans[sz-1]+=dp[n][j];
            }
            ans[sz-1]%=mod;
        }
        ans[n]=ans[n]+ans[n-1];
        printf("1\n");
        for(int i=1;i<=n;i++){
            printf("%I64d\n",(ans[i]-ans[i-1]+mod)%mod);
        }
    }
    return 0;
}
