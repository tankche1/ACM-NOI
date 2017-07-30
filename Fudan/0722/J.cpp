# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int gem[40][8][8];
int n,m,k;
int ans;
int c[7];
int qx[40],qy[40],front,rear;
bool vis[50][10][10];
const int dx[8]={1,0,-1,0,1,1,-1,-1};
const int dy[8]={0,1,0,-1,1,-1,1,-1};

int floodfill(int cur,int stx,int sty){
    qx[front=rear=0]=stx;qy[0]=sty;vis[cur][stx][sty]=1;
    int c=gem[cur][stx][sty],res=0,x,y,nx,ny;
    while(front<=rear){
        x=qx[front],y=qy[front];res++;front++;
        for(int i=0;i<8;i++){
            nx=x+dx[i];ny=y+dy[i];
            if(!((nx>=0&&nx<n)&&(ny>=0&&ny<m))) continue;
            if(gem[cur][nx][ny]!=c) continue;
            if(vis[cur][nx][ny]) continue;
            vis[cur][nx][ny]=1;
            qx[++rear]=nx;qy[rear]=ny;
        }
    }
    return res;
}

void getfall(int cur){
    int l=0;
    for(int j=0;j<m;j++){
      l=0;
      for(int i=0;i<n;i++){
          if(gem[cur][i][j]) gem[cur][l++][j]=gem[cur][i][j];
      }
      for(int i=l;i<n;i++) gem[cur][i][j]=0;
    }

    l=0;
    for(int j=0;j<m;j++){
        if(gem[cur][0][j]){
            for(int k=0;k<n;k++)
                gem[cur][k][l]=gem[cur][k][j];
            l++;
        }
    }
    for(int i=0;i<n;i++)
        for(int j=l;j<m;j++)
            gem[cur][i][j]=0;
}

void dfs(int cur,int s){
    if(s>ans) ans=s;
    for(int ii=0;ii<n;ii++)
                for(int jj=0;jj<m;jj++)
                    gem[cur][ii][jj]=gem[cur-1][ii][jj];

    memset(c,0,sizeof(c));
    int tot=s,sum;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            c[gem[cur][i][j]]++;
    for(int i=1;i<=k;i++) if(c[i]>2) tot+=c[i]*c[i];
    if(tot<=ans) return;

    memset(vis[cur],false,sizeof(vis[cur]));
    for(int j=0;j<m;j++){
        for(int i=0;i<n;i++){
          if(gem[cur][i][j]){
            if(vis[cur][i][j]) continue;
            sum=floodfill(cur,i,j);
            if(sum<3) continue;
            for(int k=0;k<=rear;k++)
                gem[cur][qx[k]][qy[k]]=0;
            getfall(cur);
            dfs(cur+1,s+sum*sum);
            for(int ii=0;ii<n;ii++)
                for(int jj=0;jj<m;jj++)
                    gem[cur][ii][jj]=gem[cur-1][ii][jj];
          }
        }
    }
    return;
}
int main(){
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        for(int i=n-1;i>=0;i--)
            for(int j=0;j<m;j++)
            scanf("%d",&gem[0][i][j]);
        ans=0;
        dfs(1,0);
        printf("%d\n",ans);
    }
	return 0;
}
