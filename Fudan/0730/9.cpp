# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=1010;
int n,m;
int a[maxn][maxn];
bool vis[maxn][maxn];
int q[maxn*maxn],front,rear;
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
int maxlen;
vector<int> st;

void BFS1(){
    int x,y,nx,ny;
    maxlen=n*m+10;memset(vis,0,sizeof(vis));
    vis[1][1]=1;
    front=rear=0;q[0]=1*10000+1;
    st.clear();
    while(front<=rear){
        x=q[front]/10000;y=q[front]%10000;front++;

        if(a[x][y]==1) {
            if(n-x+m-y<maxlen){
                maxlen=n-x+m-y;st.clear();
            }
            if(n-x+m-y==maxlen) st.push_back(x*10000+y);
            continue;
        }
        if(x==n&&y==m) {st.clear();break;}
        for(int i=0;i<4;i++){
            nx=x+dx[i];ny=y+dy[i];
            if(!(nx>=1&&nx<=n&&ny>=1&&ny<=m)) continue;
            if(!vis[nx][ny]){
                vis[nx][ny]=1;q[++rear]=nx*10000+ny;
            }
        }
    }
}
int step[maxn*maxn];
int path[maxn*2];

void BFS2(){
    memset(vis,0,sizeof(vis));
    int x,y,nx,ny;
    if(!st.size()) {puts("0");return;}
    for(int i=0;i<(int)st.size();i++){
            //printf("st:%d %d\n",st[i]/10000,st[i]%10000);
        q[i]=st[i];step[i]=1;vis[st[i]/10000][st[i]%10000]=1;
    }
    rear=st.size()-1;front=0;
    int nowstep=0,t;
    while(front<=rear){
        if(step[front]!=nowstep){
            t=2;
            for(int i=front;i<=rear;i++)
                t=min(t,a[q[i]/10000][q[i]%10000]);
            nowstep++;
    //printf("nowstep:%d t:%d\n",t);
            path[nowstep]=t;
        }
        x=q[front]/10000;y=q[front]%10000;front++;
        if(x==n&&y==m) break;
        if(a[x][y]!=t) continue;
        for(int i=0;i<2;i++){
            nx=x+dx[i];ny=y+dy[i];
            if(!(nx>=1&&nx<=n&&ny>=1&&ny<=m)) continue;
            if(!vis[nx][ny]){
                vis[nx][ny]=1;
                q[++rear]=nx*10000+ny;step[rear]=nowstep+1;
            }
        }
    }
    for(int i=1;i<=nowstep;i++)
        printf("%d",path[i]);puts("");
}


int main(){
    int tcase;char tt;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            while((tt=getchar())&&tt!='0'&&tt!='1');
            a[i][j]=tt-'0';
        }
        BFS1();
        BFS2();
    }
    return 0;
}
