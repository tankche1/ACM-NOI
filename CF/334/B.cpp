# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int mod=1000000007;
const int maxn=1000010;
int p,k;
bool vis[maxn];
int len;
int main(){
    scanf("%d%d",&p,&k);
    LL x=1;len=0;
    while(!vis[x]){
        vis[x]=1;len++;x=x*k%p;
    }
    //printf("len:%d\n",len);
    LL ans=1;
    if(k==0) len=1;
    if(k==1) len=1,ans*=p;
    for(int i=1;i<=(p-1)/len;i++){
        ans=ans*p%mod;
    }
    printf("%I64d\n",ans);
    return 0;
}
