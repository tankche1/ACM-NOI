# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
LL INF=1LL<<60;
int dx[5]={0,1,-1,1,-1},dy[5]={0,1,1,-1,-1};
struct state{
    int x,y,dir;LL dis;
    state(int x=0,int y=0,int dir=0,LL dis=0):x(x),y(y),dir(dir),dis(dis) {}

    void go(int a){
        x+=dx[dir]*a;y+=dy[dir]*a;dis+=a;
    }

}q[maxn<<2];

int n,m,k;

int id(int x,int y){

    if(x==0) return y;
    if(x==n) return m+2+y;
    if(y==0) return m+2+m+2+x;
    if(y==m) return m+2+m+2+n+2+x;
}

bool vis[4*maxn][5];
LL d[4*maxn][5];


int px[maxn],py[maxn];

state now,to;

int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;i++){
        scanf("%d%d",&px[i],&py[i]);
    }

    q[0]=state(0,0,1,0);
    int tail=0;
    memset(d,-1,sizeof(d));
    while(1){
        to=now=q[tail];
        //printf("%d %d %d id:%d \n",now.x,now.y,now.dir,id(now.x,now.y));
        d[id(now.x,now.y)][now.dir]=now.dis;
        vis[id(now.x,now.y)][now.dir]=1;
        if(now.dir==1){
            to.go(min(n-to.x,m-to.y));
            if(to.y==m) to.dir=3;
            else to.dir=2;
        }
        else if(now.dir==2){
            to.go(min(to.x,m-to.y));
            if(to.y==m) to.dir=4;
            else to.dir=1;
        }
        else if(now.dir==3){
            to.go(min(n-to.x,to.y));
            if(to.y==0) to.dir=1;
            else to.dir=4;
        }
        else{
            to.go(min(to.x,to.y));
            if(to.x==0) to.dir=3;
            else to.dir=2;
        }
        if(to.x==0&&to.y==0) break;
        if(to.x==n&&to.y==0) break;
        if(to.x==0&&to.y==m) break;
        if(to.x==n&&to.y==m) break;
        if(vis[id(to.x,to.y)][to.dir]) break;
        q[++tail]=to;
    }

    LL ans;
    for(int i=1;i<=k;i++){
        ans=INF;
        to=state(px[i],py[i],4,0);to.go(min(to.x,to.y));
        //printf("%d %d %d d:%d\n",to.x,to.y,1,d[id(to.x,to.y)][1]);printf("id:%d\n",id(to.x,to.y));
        if(d[id(to.x,to.y)][1]!=-1&&d[id(to.x,to.y)][1]+to.dis<ans) ans=d[id(to.x,to.y)][1]+to.dis;

        to=state(px[i],py[i],1,0);to.go(min(n-to.x,m-to.y));
        //printf("%d %d %d d:%d \n",to.x,to.y,4,d[id(to.x,to.y)][4]);printf("id:%d\n",id(to.x,to.y));
        if(d[id(to.x,to.y)][4]!=-1&&d[id(to.x,to.y)][4]+to.dis<ans) ans=d[id(to.x,to.y)][4]+to.dis;

        to=state(px[i],py[i],2,0);to.go(min(to.x,m-to.y));
        //printf("%d %d %d d:%d \n",to.x,to.y,3,d[id(to.x,to.y)][3]);printf("id:%d\n",id(to.x,to.y));
        if(d[id(to.x,to.y)][3]!=-1&&d[id(to.x,to.y)][3]+to.dis<ans) ans=d[id(to.x,to.y)][3]+to.dis;

        to=state(px[i],py[i],3,0);to.go(min(n-to.x,to.y));
        //printf("%d %d %d d:%d \n",to.x,to.y,2,d[id(to.x,to.y)][2]);printf("id:%d\n",id(to.x,to.y));
        if(d[id(to.x,to.y)][2]!=-1&&d[id(to.x,to.y)][2]+to.dis<ans) ans=d[id(to.x,to.y)][2]+to.dis;

        if(ans==INF) puts("-1");
        else printf("%I64d\n",ans);
    }
    return 0;
}
