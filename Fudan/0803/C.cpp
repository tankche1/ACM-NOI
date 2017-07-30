# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
struct tank{
    LL g;
    int r;
    tank(LL g=0,int r=0):g(g),r(r) {}
};
tank t[2][maxn];int cnt[2];


inline LL gcd(LL a,LL b){
    if(a==0) return b;return gcd(b%a,a);
}
int n;
LL a[maxn];

int main(){
    LL ans;
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%I64d",&a[i]);
        ans=a[n];
        cnt[0]=cnt[1]=0;
        t[0][++cnt[0]]=tank(a[n],n);
        int now=0;
        for(int i=n-1;i>=1;i--){
            now=now^1;cnt[now]=0;
            for(int j=1;j<=cnt[now^1];j++)
                t[now^1][j].g=gcd(t[now^1][j].g,a[i]);
            t[now^1][++cnt[now^1]]=tank(a[i],i);
            for(int j=1;j<=cnt[now^1];j++){
                if(j==1||t[now^1][j].g!=t[now^1][j-1].g){
                    t[now][++cnt[now]]=t[now^1][j];
                    ans=max(ans,t[now^1][j].g*(t[now^1][j].r-i+1));
                }
            }
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
