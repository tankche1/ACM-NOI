# include<stdio.h>
# include<string.h>
# include<math.h>
# include<map>
# include<algorithm>
using namespace std;
const int maxn=50010;
const int maxl=300;
int n;
int dp[maxn],col[maxn];
int cnum;
int last[maxn];
int a[maxn];
map<int,int> id;
int cnt;
int main(){
    while(scanf("%d",&n)!=EOF){
        id.clear();cnt=0;
        cnum=sqrt(n)+1;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);if(!id.count(a[i])) id[a[i]]=++cnt;
        }
        int nn;nn=0;a[0]=-1;
        for(int i=1;i<=n;i++){
            if(a[i]!=a[nn]) {a[++nn]=a[i];}
        }
        n=nn;
        for(int i=1;i<=n;i++) a[i]=id[a[i]];

        memset(col,-1,sizeof(col));
        for(int i=1;i<=n;i++){
            last[i]=col[a[i]];col[a[i]]=i;
        }
        for(int i=1;i<=cnum;i++) col[i]=1;
        dp[1]=1;dp[0]=0;
        for(int i=2;i<=n;i++){
            dp[i]=dp[i-1]+1;
            for(int j=cnum;j>=1;j--){
                if(last[i]>=col[j]) col[j]=col[j];
                else col[j]=(j==1)?i:col[j-1];
                dp[i]=min(dp[i],dp[col[j]-1]+j*j);
            }
        }
        printf("%d\n",dp[n]);
    }
    return 0;
}
