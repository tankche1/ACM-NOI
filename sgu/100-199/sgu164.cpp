# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=205;
const int INF=100;
typedef pair<int,int> pi;
vector<pi> G[maxn*maxn];
int n,m;
int d[maxn][maxn];
int main(){
    int x;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        scanf("%d",&x);
        if(x!=0) G[x].push_back(make_pair(i,j));
    }

    int half=(m+1)/2;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        d[i][j]=INF;
    for(int i=1;i<=n;i++) d[i][i]=0;
    for(int i=1;i<=half;i++){
        for(int j=0;j<(int)G[i].size();j++){
            d[G[i][j].first][G[i][j].second]=1;
           // printf("%d %d\n",G[i][j].second,G[i][j].first);
        }
    }

    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        if(d[i][k]<d[i][j]-d[k][j]) d[i][j]=d[i][k]+d[k][j];

    bool ok=true;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        if(d[i][j]>3) {ok=false;}
    if(ok){
        printf("%d\n",half);
        for(int i=1;i<=half;i++){
            printf("%d",i);
            if(i!=half) printf(" ");
        }
        puts("");
    }
    else{
        printf("%d\n",m-half);
        for(int i=half+1;i<=m;i++){
            printf("%d",i);
            if(i!=m) printf(" ");
        }
        puts("");
    }
    return 0;
}
