# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<queue>
# include<bitset>
# include<algorithm>
using namespace std;

const int maxn=110;
int INF=1000000000;
int g[maxn][maxn];
int on[maxn][maxn];
int n,m,C,E;

inline int pos(int x,int y){
    return (x-1)*m+y;
}

struct character{
    int  HP, AT, MV, AD1, AD2, STx, STy, GR,die;
    character() {die=0;}
}p[maxn];

char op[30];

int Dis(int a,int b){
    return abs(p[a].STx-p[b].STx)+abs(p[a].STy-p[b].STy);
}

struct HeapNode{
    int x,y,cost;
    HeapNode() {}
    HeapNode(int x,int y,int cost):x(x),y(y),cost(cost) {}
    bool operator < (const HeapNode &rhs)const{
        return cost>rhs.cost;
    }
};

priority_queue<HeapNode> Q;
HeapNode now,to;
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};

bool in(int a,int b) {return a>=1&&a<=n&&b>=1&&b<=m;}

bool check(int x,int y,int c){
    for(int d=0;d<4;d++){
        if(on[x+dx[d]][y+dy[d]]==(c^1)) return false;
    }
    return true;
}

bool used[maxn][maxn];

int Dist(int bh,int EDx,int EDy){
    memset(used,false,sizeof(used));
    while(!Q.empty()) Q.pop();
    Q.push(HeapNode(p[bh].STx,p[bh].STy,0));

    int nx,ny;
    //puts("*************");

    while(!Q.empty()){
        now=Q.top();Q.pop();
        if(used[now.x][now.y]) continue;
        used[now.x][now.y]=1;
        //printf("x:%d y:%d cost:%d\n",now.x,now.y,now.cost);
        if(now.cost>p[bh].MV) return INF;
        if(now.x==EDx&&now.y==EDy) return now.cost;

        for(int d=0;d<4;d++){
            nx=now.x+dx[d];ny=now.y+dy[d];
            if(!in(nx,ny)) continue;
            if(on[nx][ny]!=-1) continue;
            if(now.cost+g[nx][ny]>p[bh].MV) continue;
            if(!check(nx,ny,p[bh].GR)){
                Q.push(HeapNode(nx,ny,p[bh].MV));
            }
            else Q.push(HeapNode(nx,ny,now.cost+g[nx][ny]));
        }
    }
    return INF;
}

int main(){
    int x,dis,EDx,EDy,want;
    char tt;
    while(scanf("%d%d%d%d",&n,&m,&C,&E)!=EOF){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf("%d",&g[i][j]);
            }
        }
        memset(on,-1,sizeof(on));

        for(int i=1;i<=C;i++){
            scanf("%d%d%d%d%d%d%d%d",&p[i].HP,&p[i].AT,&p[i].MV,&p[i].AD1,&p[i].AD2,&p[i].STx,&p[i].STy,&p[i].GR);
            on[p[i].STx][p[i].STy]=p[i].GR;p[i].die=0;
        }

        x=-1;
        for(int i=1;i<=E;i++){
            scanf("%s",op);
            if(op[0]=='R') scanf("%s%d",op,&x),x=-1;
            else if(op[0]=='A'&&op[1]=='c') scanf("%s%s%d",op,op,&x);
            else if(op[0]=='M') {
                while((tt=getchar())&&tt!='(');scanf("%d",&EDx);
                tt=getchar();scanf("%d",&EDy);tt=getchar();

                if(x==-1||p[x].die) {puts("INVALID");continue;}

                dis=Dist(x,EDx,EDy);
                if(dis>p[x].MV) puts("INVALID");
                else{
                    //p[x].MV-=dis;
                    on[p[x].STx][p[x].STy]=-1;
                    on[p[x].STx=EDx][p[x].STy=EDy]=p[x].GR;
                    printf("%d\n",p[x].MV-dis);
                }
            }
            else if(op[0]=='A'&&op[1]=='t'){
                scanf("%d",&want);
                if(x==-1||p[want].die||p[x].die) {puts("INVALID");continue;}
                if(p[want].GR==p[x].GR||p[want].HP<=p[x].AT) {puts("INVALID");continue;}
                if((Dis(x,want)<p[x].AD1)||(Dis(x,want)>p[x].AD2)) {puts("INVALID");continue;}
                p[want].HP-=p[x].AT;
                printf("%d\n",p[want].HP);
            }
            else{
                scanf("%s%d",op,&want);
                if(x==-1||p[want].die||p[x].die) {puts("INVALID");continue;}
                if(p[want].GR==p[x].GR||p[want].HP>p[x].AT) {puts("INVALID");continue;}
                if((Dis(x,want)<p[x].AD1)||(Dis(x,want)>p[x].AD2)) {puts("INVALID");continue;}
                p[want].HP-=p[x].AT;
                printf("%d\n",p[want].HP);
                p[want].die=1;
                on[p[want].STx][p[want].STy]=-1;
            }

        }
    }
    return 0;
}
