//#pragma comment(linker, "/STACK:102400000,102400000")
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include <cctype>
#include <cmath>
#include <queue>
#define ls rt<<1
#define rs rt<<1|1
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define mem(a,n) memset(a,n,sizeof(a))
#define rep(i,n) for(int i=0;i<(int)n;i++)
#define rep1(i,x,y) for(int i=x;i<=(int)y;i++)
using namespace std;
typedef long long ll;
const ll oo = 1e12;
const double pi = acos(-1.0);
const int inf = 0x3f3f3f3f;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const int N = 205;
int gcd(int a,int b){return b==0 ? a:gcd(b,a%b);}
int cnt[N][N],c[N][N];
void init(){
   mem(cnt,0);
   rep1(i,1,N-1) rep1(j,1,N-1){
       int te = 0;
       rep1(k,1,j) te+=(gcd(i,k)==1);
       cnt[i][j] = cnt[i-1][j]+(c[i][j] = te);
   }
}
bool vis[N][N];
int u[N][N],r[N][N],n,cr[N][N];
int main()
{
    //freopen("input.txt","r",stdin);
   init();
   int T,kase=1;
   scanf("%d",&T);
   while(T--){
      scanf("%d",&n);
      mem(vis,false);
      rep1(i,1,n) {
         int x,y; scanf("%d %d",&x,&y);
         vis[x][y] = true;
      }
      ll ans1 = 0;
      mem(u,0); mem(r,0); mem(cr,0);
      int tem[N];
      for(int i=200;i>=1;i--)
        for(int j=200;j>=1;j--)if(vis[i][j]){
         u[i][j]=u[i+1][j]+vis[i+1][j];
         r[i][j]=r[i][j+1]+vis[i][j+1];
         ans1+=cnt[u[i][j]][r[i][j]];
         mem(tem, 0);
         for(int k=u[i][j];k>=1;k--)
            tem[k] = c[k][r[i][j]];
         for(int k=u[i][j];k>=1;k--)
            tem[k-1]+=tem[k];
         for(int k=0;k<=u[i][j];k++)
            cr[i+k][j] += tem[k];
      }
      ll ans2 = 0;
       for(int i=200;i>=1;i--)
        for(int j=200;j>=1;j--)if(vis[i][j]){
            ll te = cnt[u[i][j]][r[i][j]];
            ll yu = 0;
            for(int k = 1; k<=r[i][j];k++){
                yu += cr[i][j+k];
                ans2 += yu*c[k][u[i][j]]*2;
            }
            ans2+=te*te + (ll)(cr[i][j]- te)*te*2;
        }
       // printf("ans1:%I64d\n",ans1);
      printf("Case #%d: %I64d\n",kase++,ans1*ans1-ans2);
   }
   return 0;
}
