# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=200010;
int n,m;
int x;
LL sum[maxn];
int last[maxn];
LL y[maxn];

int main(){
    scanf("%d",&n);
    sum[0]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&x);sum[i]=sum[i-1]+x;
        y[i]=sum[i];
    }
    memset(last,-1,sizeof(last));
    y[m=n+1]=0;
    sort(y+1,y+m+1);
    int cnt=unique(y+1,y+m+1)-y-1;
    for(int i=0;i<=n;i++){
        sum[i]=lower_bound(y+1,y+cnt+1,sum[i])-y;
        //printf("sum[%d]:%d\n",i,sum[i]);
    }
    int ans=n+10,pos;

    for(int i=0;i<=n;i++){
        if(last[sum[i]]!=-1){
            if(i-last[sum[i]]<ans){
                ans=i-last[sum[i]];pos=last[sum[i]]+1;
            }
        }
        last[sum[i]]=i;
    }
    if(ans>n) puts("-1");
    else{
        printf("%d %d\n",pos,ans);
    }
    return 0;
}
