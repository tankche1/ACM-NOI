# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int aa[60][60];
int l[60],r[60];

bool vis[60];
int left[60],right[60];
bool del[60];

int n,m1,m2;
bool dfs(int x){
    for(int i=1;i<=n;i++){
        if(aa[x][i]==0) continue;
        if(del[i]) continue;
        if(vis[i]) continue;vis[i]=1;
        if(left[i]==-1||dfs(left[i])){
            left[i]=x;return true;
        }
    }
    return false;
}

int main(){

    int a,b,c;
    while(scanf("%d%d%d",&n,&m1,&m2)!=EOF){
        for(int i=1;i<=n;i++) l[i]=1,r[i]=n;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) aa[i][j]=1;
        for(int i=1;i<=m1;i++){
            scanf("%d%d%d",&a,&b,&c);for(int j=a;j<=b;j++) for(int k=1;k<c;k++) aa[j][k]=0;
            for(int k=1;k<=n;k++) if(!(k>=a&&k<=b)) aa[k][c]=0;
        }
        for(int i=1;i<=m2;i++){
            scanf("%d%d%d",&a,&b,&c);for(int j=a;j<=b;j++) for(int k=c+1;k<=n;k++) aa[j][k]=0;
            for(int k=1;k<=n;k++) if(!(k>=a&&k<=b)) aa[k][c]=0;
        }

        memset(del,0,sizeof(del));
        int num=0;

        memset(left,-1,sizeof(left));
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) num++;
        }


        if(num<n) puts("-1");
        else{
            //puts("fuck");
            for(int x=1;x<=n;x++){
                for(int j=1;j<=n;j++){
                    if(!aa[x][j]) continue;
                    if(del[j]==1) continue;
                    del[j]=1;

                    memset(left,-1,sizeof(left));
                    bool ok=true;
                    for(int i=x+1;i<=n;i++){
                        memset(vis,0,sizeof(vis));
                        if(!dfs(i)) {ok=false;break;}
                    }

                    if(ok){
                        right[x]=j;break;
                    }
                    del[j]=0;
                }
            }
            for(int i=1;i<n;i++) printf("%d ",right[i]);printf("%d\n",right[n]);
        }
    }
    return 0;
}
