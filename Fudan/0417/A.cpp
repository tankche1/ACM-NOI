# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=1010;
LL a[maxn][maxn];
int n;
LL x[maxn];
LL money[maxn];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%I64d",&a[i][j]);
        }
    }
    for(int i=1;i<=n;i++){
        money[i]=0;
        for(int j=1;j<=n;j++)
            money[i]-=a[i][j];
        for(int j=1;j<=n;j++)
            money[i]+=a[j][i];
    }
    memset(a,0,sizeof(a));
    int now1=1,now2=1;
    LL t;
    while(1){
        while(now1<=n&&money[now1]<=0) now1++;
        if(now1>n) break;
        while(now2<=n&&money[now2]>=0) now2++;
        if(now2>n) break;
        t=min(money[now1],-money[now2]);
        a[now2][now1]+=t;
        money[now1]-=t;money[now2]+=t;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(j>1) printf(" ");
            printf("%I64d",a[i][j]);
        }puts("");
    }
    return 0;
}
