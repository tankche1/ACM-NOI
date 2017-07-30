# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000010;
int a[maxn],m,n;
int ans[maxn];
int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        int now=0,tmax,tmin,tt,tmp;
        memset(ans,0,sizeof(ans));
        for(int i=1;i<=n;i++){
            now+=a[i];tt=now;
            if(now>m||now<0){
                tmin=0;tmax=m;tmp=0;
                now=tmin;ans[i]=now-tt;
                for(int j=i+1;j<=n;j++){
                    tmp+=a[j];
                    tmax=min(tmax,m-tmp);
                    tmin=max(tmin,0-tmp);
                    if(tmin>tmax) {break;}
                    now=tmin;ans[i]=now-tt;
                }
            }
        }
        printf("%d",ans[1]);
        for(int i=2;i<=n;i++) printf(" %d",ans[i]);puts("");
    }
    return 0;
}
