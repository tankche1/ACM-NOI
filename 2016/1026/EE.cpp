# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=10000010;
typedef long long LL;
int N=5000000;
bool vis[maxn];
int op[maxn];
int n,m;

void prepare(){
    LL t;
    for(int i=1;i<=N;i++) op[i]=1;
    for(int i=2;i<=N;i++){
        //printf("i:%d\n",i);
        if(!vis[i]){//printf("i:%d\n",i);
            op[i]=-1;
            for(int j=i+i;j<=N;j+=i) op[j]=-op[j],vis[j]=1;
            t=(LL)i*i;if(t>N) continue;
            for(LL j=t;j<=N;j=j+t) op[j]=0;
        }
    }
    //for(int i=1;i<=100;i++) printf("%d:%d\n",i,op[i]);
}

LL solve1(int n){
    LL res=0;
    for(int i=1;i<=n;i++){
        if(!op[i]) continue;
        int t=n/i;
        res+=(LL)(t*(t-1)/2)*op[i];
    }
    res--;
    printf("res:%lld\n",res);
    return res;
}

LL solve2(int n){
    LL res=0;
    for(int i=1;i<=n;i+=2){
        if(!op[i]) continue;
        int t=n/i;
        if(t&1) t--;
        int f=(t-2)/2;
        res+=((LL)(f+1)*(f+2)/2)*op[i];
    }
    res--;
    printf("res:%lld\n",res);
    return res;
}

int main(){
    prepare();
    int Case;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d%d",&n,&m);if(n>m) swap(n,m);
        LL ans=0;
        ans=solve1(n)/2-solve2(n)/2;

       //printf("%lld\n",ans);
        printf("%lld\n",ans);
    }
    return 0;
}
