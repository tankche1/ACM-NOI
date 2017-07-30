# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL n,ans,nn;
int r;
int prime[40]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};
int prime_cnt=19;
int val[600];
int pri[600];
int cnt=0;

void prepare(){
    int tt;cnt=0;
    for(int i=0;prime[i]<=r;i++){
        //printf("prime[%d]:%d\n",i,prime[i]);
        tt=cnt;
        for(int j=0;j<tt;j++){
               // printf("pri[%d]:%d\n",j,pri[j]);
            if(pri[j]*prime[i]<=63)
                pri[cnt]=pri[j]*prime[i],val[cnt++]=-val[j];
        }
        pri[cnt]=prime[i],val[cnt++]=-1;
    }
}

LL solve(LL n){
    LL res=n-1;
    for(int i=0;i<cnt;i++){
        if(val[i]==1)
            res+=(LL)pow((double)n+0.5,(double)1/(pri[i]*1.0))-1;
        else if(val[i]==-1) res-=(LL)pow((double)n+0.5,(double)1/(pri[i]*1.0))-1;
    }
    //printf("n:%I64d res:%I64d\n",n,res);
    return res;
}

int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int tcase;
    scanf("%d",&tcase);

    while(tcase--){
        scanf("%I64d%d",&n,&r);
        prepare();
        ans=0;nn=n;
        while(ans<nn){
            ans=solve(n);
            n+=nn-ans;
        }
        printf("%I64d\n",n);
    }
    return 0;
}
