# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=1000100;
int p[1010],p_cnt=0;
bool vis[1010];
void get_prime(){
    memset(vis,false,sizeof(vis));
    for(int i=2;i<=1000;i++){
        if(!vis[i]) {
            p[++p_cnt]=i;
            for(int j=i+i;j<=1000;j+=i){
                vis[j]=1;
            }
        }
    }
}
int sum[maxn][8];

void get_sum(){
    int t,num;
    for(int k=1;k<=7;k++) sum[0][k]=sum[1][k]=0;
    for(int i=2;i<=1000000;i++){
        t=i;num=0;
        for(int j=1;j<=p_cnt&&p[j]*p[j]<=t;j++){
            if(t%p[j]==0){
                num++;while(t%p[j]==0) t/=p[j];
            }
        }
        if(t>1) num++;
        for(int k=1;k<=7;k++)
            sum[i][k]=sum[i-1][k];
        sum[i][num]++;
    }
}

inline int gcd(int a,int b){
    if(a==0) return b;
    return gcd(b%a,a);
}

int a[8];
int main(){
    get_prime();
    get_sum();
    int tcase,L,R,ans;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d",&L,&R);
        for(int i=1;i<=7;i++) a[i]=sum[R][i]-sum[L-1][i];
        ans=0;
        for(int i=1;i<=7;i++){
            if(!a[i]) continue;
            a[i]--;
            for(int j=1;j<=7;j++){
                if(!a[j]) continue;
                ans=max(ans,gcd(i,j));
            }a[i]++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
