# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=211;
const int mod=1000000007;
typedef long long LL;
LL dp[2][maxn*maxn*2];
int tcase,n;
int a[maxn];
LL face[maxn*maxn*2],back[maxn*maxn*2];
inline int code(int j) {return j+41000;}

inline LL get(LL x){
    if(x<0) return x+mod;
    else if(x>=mod) return x-mod;
    return x;
}
int main(){
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        memset(dp,0,sizeof(dp));dp[0][code(0)]=1;
        LL now;
        int _now,nex;
        for(int i=0;i<n;i++){
            _now=i&1;nex=_now^1;
            int half=(a[i+1])/2;
            face[code(-40000)]=face[code(-39999)]=0;
            for(int k=-40000;k<=-40000+half*2;k+=2)
                face[code(-40000)]+=dp[_now][code(k)];
            for(int k=-39999;k<=-39999+half*2;k+=2)
                face[code(-39999)]+=dp[_now][code(k)];
            face[code(-40000)]%=mod;face[code(-39999)]%=mod;
            for(int k=-40000+2;k<=40000;k++){
                face[code(k)]=get(face[code(k-2)]-dp[_now][code(k-2)]+dp[_now][code(k+half*2)]);
                //if(dp[_now][code(k+half*2)]) printf("%d %lld\n",code(k+half*2),dp[_now][code(k+half*2)]);
            }

            back[code(40000)]=back[code(39999)]=0;
            for(int k=40000;k>=40000-half*2;k-=2)
                back[code(40000)]+=dp[_now][code(k)];
            back[code(40000)]%=mod;back[code(39999)]%=mod;
            for(int k=39999;k>=39999-half*2;k-=2)
                back[code(39999)]+=dp[_now][code(k)];
            for(int k=40000-2;k>=-40000;k--)
                back[code(k)]=get(back[code(k+2)]-dp[_now][code(k+2)]+dp[_now][code(k-half*2)]);

            /*for(int k=-40000;k<=40000;k++){
                if(face[code(k)]>0) printf("face[%d]:%lld\n",k,face[k]);
            }*/
            if(a[i+1]&1){
                int x=(a[i]/2+1);
                now=0;
                for(int k=-40000;k<=-40000+a[i];k++) {
                    now+=x*dp[_now][code(k)];
                    if((k-(-40000))&1) x--;
                }
                now%=mod;
                dp[nex][code(-40000)]=now;
                for(int j=-39999;j<=40000;j++){
                    dp[nex][code(j)]=get(dp[nex][code(j-1)]+face[code(j+1)]-back[code(j-2)]);
                }
            }
            else{
                int x=(a[i]/2+1);
                now=0;
                for(int k=-40000;k<=-40000+a[i];k++) {
                    now+=x*dp[_now][code(k)];
                    if(!((k-(-40000))&1)) x--;
                }
                now%=mod;
                dp[nex][code(-40000)]=now;
                for(int j=-39999;j<=40000;j++){
                    dp[nex][code(j)]=get(dp[nex][code(j-1)]+face[code(j)]-back[code(j-1)]);
                }
            }
        }
        _now=n&1;
        printf("%lld\n",dp[_now][code(0)]);
    }
    return 0;
}
