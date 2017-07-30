# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=(LL)1<<60;
const int maxn=1000010;
LL ans=INF;
int n,a,b;
int p[maxn];
int prime[100],cnt=0;

void give(int i){
    bool ok=false;
    for(int j=1;j<=cnt;j++){
        if(prime[j]==i) ok=true;
    }
    if(!ok) prime[++cnt]=i;
}

void insert(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            give(i);
            while(x%i==0) x/=i;
        }
    }
    if(x>1) give(x);
}

LL cost[maxn],spend[maxn];

void solve(){
    int L,R,gcd,tmp,pos;
    for(int t=1;t<=cnt;t++){
        gcd=prime[t];
        //printf("gcd:%d\n",gcd);
        spend[0]=0;
        for(int i=1;i<=n;i++){
            spend[i]=spend[i-1];tmp=p[i]%gcd;
            if(!tmp) {}
            else if(tmp==1||tmp==(gcd-1)) spend[i]+=b;
            else spend[i]=INF;
//printf("spend[%d]:%I64d\n",i,spend[i]);
        }
        ans=min(ans,spend[n]);

        cost[n+1]=0;pos=n+1;
        for(int i=n;i>=1;i--){
            cost[i]=cost[i+1];tmp=p[i]%gcd;
            if(!tmp) {}
            else if(tmp==1||tmp==(gcd-1)) cost[i]+=b;
            else cost[i]=INF;
            //printf("cost[%d]:%I64d pos:%d\n",i,cost[i],pos);
            ans=min(ans,(LL)(pos-i)*a+cost[pos]+spend[i-1]);
            if((LL)i*a+cost[i]<(LL)pos*a+cost[pos]) pos=i;
        }

    }
}

int main(){
    scanf("%d%d%d",&n,&a,&b);
    for(int i=1;i<=n;i++){
        scanf("%d",&p[i]);
    }

    if(n==1){
        if(p[1]==1) printf("%d\n",b);
        else printf("0\n");
        return 0;
    }
    insert(p[1]);insert(p[1]+1);insert(p[1]-1);insert(p[n]);insert(p[n]+1);insert(p[n]-1);

    solve();
    printf("%I64d\n",ans);
    return 0;
}
