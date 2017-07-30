# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=30;
char a[maxn][maxn],t;
int n;
int f[maxn][maxn];
int pos(int x,int y){
    return (x-1)*n+y;
}

int p[maxn*maxn];

int find(int x){
    if(p[x]==x) return x;
    return p[x]=find(p[x]);
}

bool check(int stx,int sty,int edx,int edy){
    //printf("stx:%d sty:%d edx:%d edy:%d\n",stx,sty,edx,edy);

    memset(f,0,sizeof(f));
    f[stx][sty]^=1;f[edx][edy]^=1;
    for(int i=1;i<=n*n;i++) p[i]=i;
    int x,px,py,y;
    for(int s=2;s<=n+n;s++){
    for(x=1;x<=n;x++){
        y=s-x;
        if(y<1||y>n) continue;
        if(a[x][y]=='.') continue;
        while(y>=1&&x<=n){
            if(a[x][y]=='W'){
                //if(edx==1&&edy==2) printf("x:%d y:%d\n",x,y);
                if(f[x-1][y-1]==1){
                   // if(edx==1&&edy==2) printf("(%d,%d)-(%d,%d)\n",x-1,y-1,x+1,y+1);
                    f[x-1][y-1]^=1;f[x+1][y+1]^=1;
                    if(a[x+1][y+1]!='_'||a[x-1][y-1]!='_') return false;
                    if(!(x+1<=n&&y+1<=n)) return false;
                    px=find(pos(x-1,y-1));py=find(pos(x+1,y+1));
                    p[px]=py;
                }
                else{
                   // if(edx==1&&edy==2) printf("(%d,%d)-(%d,%d)\n",x-1,y+1,x+1,y-1);
                    f[x-1][y+1]^=1;f[x+1][y-1]^=1;
                    if(a[x+1][y-1]!='_'||a[x-1][y+1]!='_') return false;
                    if(!(x+1<=n&&y-1>=1)) return false;
                    if(!(x-1>=1&&y+1<=n)) return false;

                    px=find(pos(x+1,y-1));py=find(pos(x-1,y+1));
                    p[px]=py;
                }
            }
            x++;y--;
        }
    }
    }
    //if(edx==1&&edy==2) puts("ehi");
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            if(f[i][j]==1) {
                    //if(edx==1&&edy==2) printf("!!i:%d j:%d\n",i,j);
            return false;}
    }

    //if(edx==1&&edy==2) puts("fuck");

    if(find(pos(stx,sty))!=find(pos(edx,edy))) return false;
   // if(edx==1&&edy==2) puts("fssuck");
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            px=find(pos(i,j));
            if(px!=pos(i,j)&&px!=find(pos(stx,sty))) {//printf("i:%d j:%d\n",i,j);
            return false;}
        }
    }

    return true;
}

vector< pair<int,int> > ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            while((t=getchar())&&t!='.'&&t!='_'&&t!='W'&&t!='B');
            a[i][j]=t;
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]=='B'){
                a[i][j]='_';
                //printf("i:%d j:%d\n",i,j);
                for(int edx=1;edx<=n;edx++){
                    for(int edy=1;edy<=n;edy++){
                        if(a[edx][edy]=='_'){
                              //  printf("edx:%d edy:%d\n",edx,edy);
                            if(check(i,j,edx,edy)) {ans.push_back(make_pair(i,j));goto Loop;}
                        }
                    }
                }
                Loop:
                a[i][j]='B';
            }
        }
    }

    if((int)ans.size()>1) puts("Multiple");
    else if((int)ans.size()==0) puts("None");
    else{
        printf("%c%d\n",ans[0].second+'a'-1,n-ans[0].first+1);
    }
    return 0;
}
