# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int INF=maxn*maxn;
int n,m;
char a[maxn][maxn];
int qx[maxn*maxn],qy[maxn*maxn];
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};

struct Bfs{
    int d[maxn][maxn];
    int dcol[4];
    void BFS(int col){
        int front=0,rear=0,x,y,nx,ny;
        dcol[1]=dcol[2]=dcol[3]=INF;
        dcol[col]=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                d[i][j]=INF;
                if(a[i][j]-'0'==col) qx[rear]=i,qy[rear++]=j,d[i][j]=0;
            }
        while(front<rear){
            x=qx[front];y=qy[front++];
            if(a[x][y]>='1'&&a[x][y]<='3'&&((a[x][y]-'0')!=col)) dcol[a[x][y]-'0']=min(dcol[a[x][y]-'0'],d[x][y]-1);
            for(int e=0;e<4;e++){
                nx=x+dx[e];ny=y+dy[e];
                if(a[nx][ny]=='#') continue;
                if(nx>=1&&nx<=n&&ny>=1&&ny<=m){
                    if(d[nx][ny]==INF){
                        d[nx][ny]=d[x][y]+1;
                        qx[rear]=nx;qy[rear++]=ny;
                    }
                }
            }
        }
        /*printf("col:%d\n",col);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
            printf("%d ",d[i][j]);puts("");
        }*/
    }
}bfs[4];

int main(){
    char t;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            while((t=getchar())&&t!='.'&&t!='#'&&(t<'1'||t>'3'));a[i][j]=t;
        }
    }
    for(int i=1;i<=3;i++) bfs[i].BFS(i);
    int ans=n*m+1,res;
    for(int i=1;i<=3;i++){
        res=0;
        for(int j=1;j<=3;j++) res+=bfs[i].dcol[j];res-=bfs[i].dcol[i];
        ans=min(ans,res);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]!='.') continue;
            if(bfs[1].d[i][j]+bfs[2].d[i][j]+bfs[3].d[i][j]-2<ans) ans=bfs[1].d[i][j]+bfs[2].d[i][j]+bfs[3].d[i][j]-2;
        }
    }
    if(ans>n*m) puts("-1");
    else printf("%d\n",ans);
    return 0;
}
