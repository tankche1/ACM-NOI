# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int INF=10000010;

struct people{
    int pos,idx;
}p[maxn];
int n,s,k;
int seat[maxn][8];
int num[maxn][maxn];

inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
    int c[maxn];
    void init() {memset(c,0,sizeof(c));}

    void add(int x,int v){
        while(x<=n){
            c[x]+=v;x+=lowbit(x);
        }
    }

    int sum(int x){
        int res=0;
        while(x>0) {res+=c[x];x-=lowbit(x);}
        return res;
    }
}fwt;
int dp[maxn][maxn];

int main(){
    freopen("flight.in","r",stdin);
    freopen("flight.out","w",stdout);
    scanf("%d%d%d",&n,&s,&k);
    for(int i=1;i<=n;i++){
        p[i].idx=i;
        scanf("%d",&p[i].pos);
        seat[p[i].pos][++seat[p[i].pos][0]]=i;
    }
    for(int l=1;l<=s;l++){
        fwt.init();
        for(int r=l;r<=s;r++){
            num[l][r]=(l==r?0:num[l][r-1]);
            for(int i=1;i<=seat[r][0];i++){
                num[l][r]+=fwt.sum(seat[r][i]-1);
            }
            for(int i=1;i<=seat[r][0];i++)
                fwt.add(seat[r][i],1);
        }
    }

    for(int i=1;i<=s;i++)
        dp[i][1]=num[1][i];
    for(int j=2;j<=k;j++){
        dp[j][j]=0;
        for(int i=j+1;i<=s;i++){
            dp[i][j]=INF;
            for(int t=j-1;t<i;t++)
                dp[i][j]=min(dp[i][j],dp[t][j-1]+num[t+1][i]);
        }
    }
    printf("%d\n",dp[s][k]);
    return 0;
}
