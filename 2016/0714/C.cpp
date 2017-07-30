# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=210;
int link[maxn][maxn];
int G,B,m;
int left[maxn];
bool T[maxn];

bool dfs(int x){
    for(int i=1;i<=B;i++){
        if(link[x][i]&&!T[i]){
            T[i]=true;
            if(left[i]==-1||dfs(left[i])){
                left[i]=x;return true;
            }
        }
    }
    return false;
}

int main(){
    int tcase=0;
    int x,y;
    while(scanf("%d%d%d",&G,&B,&m)!=EOF){
        if(G==0&&B==0) break;
        for(int i=1;i<=G;i++) for(int j=1;j<=B;j++) link[i][j]=1;
        for(int i=1;i<=m;i++){
            scanf("%d%d",&x,&y);link[x][y]=0;
        }
        int ans=G+B;
        memset(left,-1,sizeof(left));
        for(int i=1;i<=G;i++){
            memset(T,0,sizeof(T));
            ans-=dfs(i);
        }
        printf("Case %d: %d\n",++tcase,ans);
    }

    return 0;
}
