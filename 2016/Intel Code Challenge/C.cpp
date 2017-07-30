# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;

int n;
int a[maxn],order[maxn];

int p[maxn];
LL sum[maxn];
LL print[maxn];

int find(int x){
    if(x==p[x]) return x;
    return p[x]=find(p[x]);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&order[i]);

    for(int i=1;i<=n;i++) p[i]=-1;
    LL ans=0;
    for(int t=n;t>=1;t--){
        print[t]=ans;
        int i=order[t];
        p[i]=i;sum[i]=a[i];
        if(p[i-1]!=-1){
            p[i-1]=i;sum[i]+=sum[i-1];
        }
        if(i!=n&&p[i+1]!=-1){
            int y=find(i+1);
            //printf("y:%d\n",y);
            sum[y]+=sum[i];p[i]=y;
        }
        //printf("find(i):%d\n",find(i));
        ans=max(ans,sum[find(i)]);

        //printf("i:%d ans:%I64d\n",i,ans);

    }
    for(int i=1;i<=n;i++) printf("%I64d\n",print[i]);
    return 0;
}
