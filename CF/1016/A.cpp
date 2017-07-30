# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000010;
int n;
int w[maxn];
int two[30];

int solve(int x){
    //printf("x:%d\n",x);
    int res=0;
    while(x){
        if(x&1) res++;
        x>>=1;
    }
    return res;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&w[i]);
    two[0]=1;
    for(int i=1;i<=20;i++) two[i]=two[i-1]<<1;
    sort(w+1,w+n+1);
    int j;
    int now=0,last=-1,ans=0;
    for(int i=1;i<=n;i++){
        for(j=i;j<n&&w[j+1]==w[j];j++);
        now=now+(j-i+1);
        //printf("i:%d now:%d ans:%d\n",i,now,ans);
        if(j<n&&(w[j+1]-w[j]<=20&&two[w[j+1]-w[j]]<=now)) ans+=solve(now%two[w[j+1]-w[j]]),now=now/two[w[j+1]-w[j]];
        else ans+=solve(now),now=0;
        i=j;
    }
    //ans+=solve(now);
    printf("%d\n",ans);
    return 0;
}
