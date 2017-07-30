# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=110;
int a[maxn][maxn],bh[maxn][maxn];
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
int breakti[maxn];
int r,c,n,T;
struct Drop{
    int x,y,dir;
    Drop(){}
    Drop(int x,int y,int dir):x(x),y(y),dir(dir) {}
}drop[2][510];
int cnt=0;
vector<int> col;

void solve(int ti){
    int now=ti&1;int last=now^1;col.clear();
    int x,y,nx,ny,ncnt=0;
    for(int i=0;i<cnt;i++){
        nx=drop[last][i].x+dx[drop[last][i].dir];ny=drop[last][i].y+dy[drop[last][i].dir];
        if(!(nx>=1&&nx<=r&&ny>=1&&ny<=c)) continue;
        if(a[nx][ny]!=0){
            a[nx][ny]++;
            if(a[nx][ny]==5) col.push_back(nx*10000+ny);
        }
        else{
            drop[now][ncnt++]=Drop(nx,ny,drop[last][i].dir);
        }
    }

    for(int i=0;i<col.size();i++){
        x=col[i]/10000;y=col[i]%10000;
        a[x][y]=0;breakti[bh[x][y]]=ti;
        for(int j=0;j<4;j++)
            drop[now][ncnt++]=Drop(x,y,j);
    }
    cnt=ncnt;
    return;
}
pair<int,int> ini[maxn];

int main(){
    int x,y,size;
    while(scanf("%d%d%d%d",&r,&c,&n,&T)!=EOF){
    memset(a,0,sizeof(a));cnt=0;
    memset(breakti,-1,sizeof(breakti));
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&x,&y,&size);bh[x][y]=i;
        ini[i].first=x;ini[i].second=y;
        a[x][y]=size;
        if(size>4){
            a[x][y]=0;breakti[i]=0;
            for(int j=0;j<4;j++)
                drop[0][cnt++]=Drop(x,y,i);
        }
    }
    scanf("%d%d",&x,&y);
    for(int i=0;i<4;i++)
        drop[0][cnt++]=Drop(x,y,i);

    for(int i=1;i<=T;i++){
        solve(i);
    }
    for(int i=1;i<=n;i++){
        if(breakti[i]==-1){
            printf("1 %d\n",a[ini[i].first][ini[i].second]);
        }
        else printf("0 %d\n",breakti[i]);
    }
    }
    return 0;
}
