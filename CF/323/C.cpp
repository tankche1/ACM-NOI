# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
int n,a[maxn];
int g[maxn],c[maxn];
bool can[maxn];

int gcd(int a,int b){
    if(a==0) return b;
    return gcd(b%a,a);
}

int next(int x) {if(x+1==n) return 0;return x+1;}

long long ans=0;
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    for(int i=1;i<n;i++){
        g[i]=gcd(i,n);
    }

    for(int x=1;x<n;x++){
        if(n%x!=0) continue;
        for(int i=0;i<n;i++) can[i]=0,c[i]=0;
        for(int i=0;i<x;i++){
            int big=0;
            for(int j=i;j<n;j+=x)
                big=max(big,a[j]);
            for(int j=i;j<n;j+=x)
                if(a[j]==big) can[j]=1;
        }

        bool all=1;
        //for(int i=0;i<n;i++) printf("can[%d]:%d\n",i,can[i]);
        for(int i=0;i<n;){
            if(can[i]) {i++;continue;}
            all=0;
            int j=next(i),len=0;
            while(can[j]) len++,j=next(j);
            for(int i=len;i>=1;i--) c[i]+=len-i+1;
            if(j<=i) break;
            i=j;
        }
        //printf("all:%d\n",all);
        if(all) for(int i=1;i<=n;i++) c[i]+=n;
        for(int i=1;i<n;i++){
            if(g[i]==x) ans+=c[i];
        }
    }
    printf("%I64d\n",ans);
    return 0;
}
