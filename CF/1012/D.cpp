# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
int n;
int a[26][3];
struct Tank{
    int a0,a1;
    Tank(int a0=0,int a1=0):a0(a0),a1(a1) {}
    bool operator < (const Tank &rhs){
        return a0==rhs.a0?(a1<rhs.a1):(a0<rhs.a0);
    }
};
map<Tank,int> id;
int now[3];
void dfs1(int x,int cur){
    if(x>cur){
        if(!id.count(Tank(now[2]-now[0],now[2]-now[1]))) id[Tank(now[2]-now[0],now[2]-now[1])]=now[3];
        else id[Tank(now[2]-now[0],now[2]-now[1])]=max(id[Tank(now[2]-now[0],now[2]-now[1])],now[3]);
        return;
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i==j) continue;
            now[j]+=a[x][j];
        }
        dfs(x+1,cur);
        for(int j=0;j<3;j++){
            if(i==j) continue;
            now[j]-=a[x][j];
        }
    }
}
int ans=-INF;


void dfs2(int x,int cur){
    if(x>cur){
        if(id.find(Tank(-(now[2]-now[0]),-(now[2]-now[1])))
        return;
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i==j) continue;
            now[j]+=a[x][j];
        }
        dfs(x+1,cur);
        for(int j=0;j<3;j++){
            if(i==j) continue;
            now[j]-=a[x][j];
        }
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&a[i][0],&a[i][1],&a[i][2]);
    }
    int half=n/2;
    dfs1(1,half);
    memset(now,0,sizeof(now));
    dfs2(half+1,n);
    return 0;
}
