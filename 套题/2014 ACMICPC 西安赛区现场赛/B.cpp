# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;

int pathx[15],pathy[15],op[15];
char c[10][10],s[10][10];
bool vis[10][10];
int n=5,m=6;
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
char dir[4]={'U','D','L','R'};

bool Disx(int x,int y){
    if(s[x][y]==s[x][y-1]&&s[x][y]==s[x][y+1]) return true;
    if(y>2&&s[x][y]==s[x][y-1]&&s[x][y]==s[x][y-2]) return true;
    if(y<5&&s[x][y]==s[x][y+1]&&s[x][y]==s[x][y+2]) return true;
    return false;
}

bool Disy(int x,int y){
    if(s[x][y]==s[x-1][y]&&s[x][y]==s[x+1][y]) return true;
    if(x>2&&s[x][y]==s[x-1][y]&&s[x][y]==s[x-2][y]) return true;
    if(x<4&&s[x][y]==s[x+1][y]&&s[x][y]==s[x+2][y]) return true;
    return false;
}
int T[10][10],stamp=0;

void DFS(int x,int y){
    T[x][y]=stamp;
    int nx,ny;
    for(int d=0;d<4;d++){
        nx=x+dx[d];ny=y+dy[d];
        if(vis[nx][ny]&&T[nx][ny]!=stamp&&s[nx][ny]==s[x][y]){
            DFS(nx,ny);
        }
    }
}

void update_combo(int &combo){
    stamp++;
    for(int i=1;i<=5;i++){
        for(int j=1;j<=6;j++){
            if(vis[i][j]&&T[i][j]!=stamp){
                DFS(i,j);combo++;
            }
        }
    }
}

struct Ans{
    int combo,block;
    int len;
    int stx,sty,op[15];
    Ans() {}
}ans;
/*bool check(){
    char tank[20];
    for(int i=1;i<=9;i++)
        tank[i-1]=dir[op[i]];
    tank[9]='\0';
    if(strcmp(tank,"RURURDLDD")==0) return true;
    return false;
}*/

void Disappear(int len){
    int combo=0,block=0;
    //if(len==9&&pathx[0]==4&&pathy[0]==3&&check()) puts("**************");
    while(1){
        /*if(len==9&&pathx[0]==4&&pathy[0]==3&&check()){
            for(int i=1;i<=5;i++){
                for(int j=1;j<=6;j++){
                    if(s[i][j]==0) printf(" ");
                    else printf("%c",s[i][j]);
                }puts("");
            }
            puts("");
        }*/
        bool ok=true;
        for(int i=0;i<=6;i++) for(int j=0;j<=7;j++) vis[i][j]=0;
        for(int i=1;i<=5;i++){
            for(int j=1;j<=6;j++){
                if(s[i][j]!=0&&(Disx(i,j)||Disy(i,j))){
                    vis[i][j]=1;block++;ok=false;
                }
            }
        }
        if(ok) break;

        update_combo(combo);
        for(int i=1;i<=5;i++) for(int j=1;j<=6;j++) if(vis[i][j]) s[i][j]=0;

        for(int j=1;j<=6;j++){
            for(int i=5;i>=1;i--){
                if(s[i][j]==0){
                    for(int k=i-1;k>=1;k--){
                        if(s[k][j]!=0) {swap(s[i][j],s[k][j]);break;}
                    }
                }
            }
        }
    }
    if(combo>ans.combo||(combo==ans.combo&&block>ans.block)||(combo==ans.combo&&block==ans.block&&len<ans.len)){
        ans.combo=combo;ans.block=block;
        ans.stx=pathx[0];ans.sty=pathy[0];
        ans.len=len;
        for(int i=1;i<=len;i++) ans.op[i]=op[i];
    }
}

void solve(int len){
    //if(pathx[0]>pathx[len]||(pathx[0]==pathx[len]&&pathy[0]>pathy[len])) return;
    for(int i=1;i<=5;i++)
        for(int j=1;j<=6;j++)
            s[i][j]=c[i][j];

    for(int i=0;i<len;i++){
        s[pathx[i]][pathy[i]]=s[pathx[i+1]][pathy[i+1]];
    }
    s[pathx[len]][pathy[len]]=c[pathx[0]][pathy[0]];

    Disappear(len);
}

void dfs(int x,int y,int dep){
    if(dep>1) {solve(dep-1);}
    if(dep>9) return;
    int nx,ny;
    for(int d=0;d<4;d++){
        nx=x+dx[d];ny=y+dy[d];
        if(nx>=1&&nx<=5&&ny>=1&&ny<=6){
            op[dep]=d;
            pathx[dep]=nx;pathy[dep]=ny;
            dfs(nx,ny,dep+1);
        }
    }
}
int main(){
    int T;
    char t;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        ans.combo=-1;
        memset(s,0,sizeof(s));
        for(int i=1;i<=5;i++){
            for(int j=1;j<=6;j++){
                while((t=getchar())&&t!='F'&&t!='W'&&t!='P'&&t!='L'&&t!='D'&&t!='C');
                c[i][j]=t;
            }
        }

        pathx[0]=1;pathy[0]=1;
        solve(0);
        for(int stx=1;stx<=5;stx++){
            for(int sty=1;sty<=6;sty++){
                pathx[0]=stx;pathy[0]=sty;
                dfs(stx,sty,1);
            }
        }
        printf("Case #%d:\n",Tcase);
        printf("Combo:%d Length:%d\n",ans.combo,ans.len);
        printf("%d %d\n",ans.stx,ans.sty);
        for(int i=1;i<=ans.len;i++){
            printf("%c",dir[ans.op[i]]);
        }puts("");
    }
    return 0;
}
