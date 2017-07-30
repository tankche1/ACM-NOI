# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=90;
int n,m;
bool g[maxn][maxn];
int sum[maxn];

int p1[maxn*maxn],p2[maxn*maxn];
bool vis[maxn*maxn];

void _make(int a,int b,int c){
    vis[c]=1;
    p1[c]=a;p2[c]=b;
    g[a][b]=1;
}

int main(){
    int Case;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d%d",&n,&m);
        memset(g,0,sizeof(g));sum[1]=0;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<n;i++) {_make(i,i+1,i);sum[i+1]=sum[i]+i;}
        if(n%3==1) _make(n,1,n+2);
        else if(n%3==2) _make(n,1,n);
        else if(n%3==0) _make(n,1,n);

        int ans=0;

        bool ok;
        for(int i=n;i<=m;i++){
            if(vis[i]) continue;
            ok=false;
            for(int a=1;a<n-1;a++){
                for(int b=a+2;b<=n;b++){
                    if(a==1&&b==n) continue;
                    //if((!g[b][a])&&((sum[b]-sum[a]+i)%3==0)) {_make(b,a,i);ok=true;break;}
                    if((!g[a][b])&&(((sum[b]-sum[a])%3)==i%3)) {_make(a,b,i);ok=true;break;}
                }
                if(ok) break;
            }

            if(!ok) {ans=-1;break;}
        }

        printf("Case #%d:\n",Tcase);
        if(ans==-1) puts("-1");
        else{
            for(int i=1;i<=m;i++){
                printf("%d %d %d\n",p1[i],p2[i],i);
            }
        }
    }
    return 0;
}
