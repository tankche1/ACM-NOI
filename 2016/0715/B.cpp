# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
int n;
int a[maxn],b[maxn];
int num[10];
int t[10];

int main(){
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        int tmp=1,L,R,M;
        LL ans=0;
        for(int bit=1;bit<=9;bit++){
            tmp*=10;
            for(int i=1;i<=n;i++) b[i]=a[i]%tmp;
            sort(b+1,b+n+1);
            for(int i=1;i<=n;i++){
                L=i+1,R=n;
                while(L<=R){
                    M=(L+R)>>1;
                    if(b[M]+b[i]>=tmp) R=M-1;
                    else L=M+1;
                }
                ans+=n+1-(R+1);
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
