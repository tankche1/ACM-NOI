# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=60;
const int mod=1000000009;
int n,m,Q;

int q[maxn];
LL num[maxn],two[maxn];//<(1<<i+1)

void prepare(){
    num[0]=1;
    for(int i=1;i<=51;i++){
        num[i]=num[i-1]*2+(1LL<<(i));
        num[i]%=mod;
    }

    two[0]=1;
    for(int i=1;i<=50;i++){
        two[i]=two[i-1]<<1;
        two[i]%=mod;
    }
}

LL sum(LL x){
    int tail=0;
    LL xx=x;
    while(xx>0){
        q[tail++]=xx&1;xx>>=1;
    }

    LL ans=0;xx=x;
    for(int i=tail-1;i>=0;i--){
        if(q[i]==1){
            if(i) ans+=num[i-1];
            ans+=(xx+1-two[i]);
            xx^=(1LL<<i);
        }
    }
    return ans%mod;
}

LL square(LL x,LL y){
    if(x==0||y==0) return 0;
    LL ret=0;
    if(y==(1LL<<m)) ret=square(x,y-1);
    else{
        ret+=sum(y)*x%mod;
        ret+=sum(x-1)*y%mod;
    }
    if(y==(1LL<<m)){
        ret+=sum(x);
    }
    return ret%mod;
}

LL query_sum(LL x1,LL y1,LL x2,LL y2){
    return (square(x2,y2)-square(x1-1,y2)-square(x2,y1-1)+square(x1-1,y1-1)+mod+mod)%mod;
}

char op[20];
int main(){
    LL x1,y1,x2,y2;
    scanf("%d%d%d",&n,&m,&Q);
    for(int t=1;t<=Q;t++){
        scanf("%s",op);
        if(op[0]=='M'){

        }
        else{
            scanf("%I64d%I64d%I64d%I64d",&x1,&y1,&x2,&y2);
            printf("%I64d\n",query_sum(x1,y1,x2,y2));
        }
    }
    return 0;
}
