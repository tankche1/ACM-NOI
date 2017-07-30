# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int mod=1000000007;
typedef long long LL;
int n,a[maxn];
int pos[10010];
vector<int> num[10010];
int L[maxn],R[maxn];
int main(){
    for(int i=1;i<=10000;i++){
            for(int j=1;j*j<=i;j++){
                if(i%j==0){
                    num[i].push_back(j);
                    if(j*j!=i) num[i].push_back(i/j);
                }
            }
        }
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=10000;i++) pos[i]=0;
        int tmp;
        for(int i=1;i<=n;i++){
            tmp=0;
            for(int j=0;j<(int)num[a[i]].size();j++){
                tmp=max(tmp,pos[num[a[i]][j]]);
            }
            L[i]=tmp;//printf("L[%d]:%d\n",i,L[i]);
            pos[a[i]]=i;
        }
        for(int i=1;i<=10000;i++) pos[i]=n+1;
        for(int i=n;i>=1;i--){
            tmp=n+1;
            for(int j=0;j<(int)num[a[i]].size();j++){
                tmp=min(tmp,pos[num[a[i]][j]]);
            }
            R[i]=tmp;//printf("R[%d]:%d\n",i,R[i]);
            pos[a[i]]=i;
        }
        LL ans=0;
        for(int i=1;i<=n;i++) {ans+=(i-L[i])*(R[i]-i);}
        ans%=mod;
        printf("%I64d\n",ans);
    }

    return 0;
}
