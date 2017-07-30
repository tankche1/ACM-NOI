# include<stdio.h>
# include<string.h>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=100010<<1;
int n;
int a[maxn];
int dpl[maxn],dpr[maxn],ansl[maxn],ansr[maxn];

inline int lowbit(int x){return x&(-x);}

struct FenwickTree{
    int C[10010];
    int n;

    void init(int nn){n=nn;memset(C,0,sizeof(C));}

    void insert(int x,int v){
        while(x<=n){
            C[x]=max(C[x],v);
            x+=lowbit(x);
        }
    }

    int query(int x){
        int res=0;
        while(x>0){
            res=max(res,C[x]);
            x-=lowbit(x);
        }
        return res;
    }

}fwt;

int main(){
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);a[n+i]=a[i];
        }
        int ans=0,t;
        for(int i=1;i<=2*n;i++) if(a[i]!=10000) a[i]=10000-a[i];

        for(int M=1;M<=2*n;M++){
            if(a[M]==10000){
                ans=max(ans,10000);ansl[0]=0;

                t=1;fwt.init(10000);
                for(int i=1;M-i>=1&&i<n;i++){
                    t=i;
                    if(a[M-i]==10000) {ansl[i]=ansl[i-1];continue;}

                    dpl[i]=fwt.query(a[M-i])+10000-a[M-i];
                    fwt.insert(a[M-i],dpl[i]);
                    ansl[i]=max(ansl[i-1],dpl[i]);
                    t=i+1;
                }

                for(;t<n;t++) ansl[t]=ansl[t-1];

                ansr[0]=0;
                ans=max(ans,ansl[n-1]+10000);fwt.init(10000);
                for(int i=1;M+i<=2*n&&i<n;i++){
                    if(a[M+i]==10000) {ansr[i]=ansr[i-1];continue;}

                    dpr[i]=fwt.query(a[M+i])+10000-a[M+i];
                    fwt.insert(a[M+i],dpr[i]);

                    ansr[i]=max(ansr[i-1],dpr[i]);
                    ans=max(ans,10000+ansr[i]+ansl[n-1-i]);
                }
               // printf("M:%d ans:%d\n",M,ans);
            }
        }

        printf("%d\n",ans);
    }
    return 0;
}
