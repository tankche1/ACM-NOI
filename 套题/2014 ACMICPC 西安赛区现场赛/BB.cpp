# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
char ss[10][10];
char s[10][10];
char changes[10][10];
int n=5,m=6;
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
char c[4]={'U','D','L','R'};

struct Ans{
    int combo,drop,length;
    int stx,sty,a[10];
    Ans() {}
    bool operator < (Ans B)const{
        if(B.combo!=combo) return combo<B.combo;
        if(drop!=B.drop) return drop<B.drop;
        return length>B.length;
    }
}ans,now;

bool vis[7][7];
bool vis2[7][7];

void dfs2(int x,int y){
    int nx,ny;
    for(int d=0;d<4;d++){
        nx=x+dx[d];ny=y+dy[d];
        if((!vis2[nx][ny])&&vis[nx][ny]>0&&s[nx][ny]==s[x][y]){
            vis2[nx][ny]=1;dfs2(nx,ny);
        }
    }
}

void Erase(){
    memset(vis2,0,sizeof(vis2));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(vis[i][j]>0&&(!vis2[i][j])){
                dfs2(i,j);now.combo++;
            }
        }
    }

    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(vis[i][j]>0) s[i][j]=0,now.drop++;

    for(int j=1;j<=m;j++){
        for(int i=n;i>=1;i--){
            if(s[i][j]==0){
                for(int k=i-1;k>=1;k--){
                    if(s[k][j]!=s[i][j]) {swap(s[k][j],s[i][j]);break;}
                }
            }
        }
    }
}

void solve(){
    int t=0,k,nx,ny;
    bool newcombo;
    now.combo=0;now.drop=0;

    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) s[i][j]=changes[i][j];

    while(1){
        t++;memset(vis,0,sizeof(vis));
        bool ok=true;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m-2;j++){
                if(s[i][j]!=0&&s[i][j]==s[i][j+1]&&s[i][j]==s[i][j+2]){
                    ok=false;
                    k=j;t++;
                    while(s[i][k]==s[i][j]&&k<=m) {
                            vis[i][k]=t;
                            k++;
                    }
                }
            }
        }

        for(int j=1;j<=m;j++){
            for(int i=1;i<=n-2;i++){
                if(s[i][j]!=0&&s[i][j]==s[i+1][j]&&s[i][j]==s[i+2][j]){
                    ok=false;
                    k=i;t++;
                    while(k<=n&&s[k][j]==s[i][j]){
                        vis[k][j]=t;
                        k++;
                    }
                }
            }
        }

        Erase();
        if(ok) break;
    }

    if(ans<now) ans=now;
    /*if(now.combo==7){
            puts("***************");
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                printf("%c",changes[i][j]);puts("");
        }
    puts("****************");
    }*/
}

void dfs(int x,int y,int cur,int len){
    if(cur==len) {solve();return;}
    for(int i=0;i<4;i++){
        if(cur>0&&(i+now.a[cur-1]==1||i+now.a[cur-1]==5)) continue;
        int nx=x+dx[i],ny=y+dy[i];
        if(nx>=1&&nx<=5&&ny>=1&&ny<=6){
            now.a[cur]=i;
            swap(changes[x][y],changes[nx][ny]);
            dfs(nx,ny,cur+1,len);
            swap(changes[x][y],changes[nx][ny]);
        }
    }
    return;
}

int main(){
    freopen("B.in","r",stdin);
    freopen("output.txt","w",stdout);
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        for(int i=1;i<=5;i++)
            scanf("%s",ss[i]+1);
        ans.combo=-1;

        /*now.length=0;now.stx=1;now.sty=1;
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) changes[i][j]=ss[i][j];
        solve();*/

        for(int length=1;length<=9;length++){
            for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) changes[i][j]=ss[i][j];
            for(int stx=1;stx<=n;stx++){
                for(int sty=1;sty<=m;sty++){
                    now.length=length;now.stx=stx;now.sty=sty;
                    dfs(stx,sty,0,length);
                }
            }
        }

        printf("Case #%d:\n",Tcase);
        printf("Combo:%d Length:%d\n",ans.combo,ans.length);
        printf("%d %d\n",ans.stx,ans.sty);
        for(int i=0;i<ans.length;i++){
            printf("%c",c[ans.a[i]]);
        }
        puts("");
    }
    return 0;
}
