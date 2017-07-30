# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=410;
int rail[maxn][maxn];
int bus[maxn][maxn];
int n,m;
int q[maxn],d[maxn];

void BFSrail(){
    q[0]=1;
    int front=0,rear=0;memset(d,-1,sizeof(d));d[1]=0;
    while(front<=rear){
        int x=q[front];front++;
        for(int i=1;i<=n;i++){
            if(rail[x][i]&&d[i]==-1){
                d[i]=d[x]+1;q[++rear]=i;
            }
        }
    }
}

void BFSbus(){
    q[0]=1;
    int front=0,rear=0;memset(d,-1,sizeof(d));
    while(front<=rear){
        int x=q[front];front++;
        for(int i=1;i<=n;i++){
            if(bus[x][i]&&d[i]==-1){
                d[i]=d[x]+1;q[++rear]=i;
            }
        }
    }
}

int main(){
    int a,b;
    memset(rail,0,sizeof(rail));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);rail[a][b]=rail[b][a]=1;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) bus[i][j]=rail[i][j]^1;

    if(rail[1][n]==1){
        BFSbus();
    }
    else BFSrail();
    printf("%d\n",d[n]);
    return 0;
}
