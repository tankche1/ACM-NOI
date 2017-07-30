# include<stdio.h>
# include<string.h>
# include<queue>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;

struct Crush{
    LL T;int u,v;
    Crush() {}
    Crush(LL T,int u,int v):T(T),u(u),v(v) {}
    bool operator < (const Crush &rhs)const{
        return T>rhs.T;
    }
};
priority_queue<Crush> Q;

LL st[maxn];
int n;
LL T;

struct Robot{
    LL x,y;char type;
    int bh;
    Robot() {}
}robot[maxn];
int rank[maxn];

struct cmpx {
    bool operator () (const Robot &A,const Robot &B)const{
        if(A.x==B.x) return A.y<B.y;
        return A.x<B.x;
    }
};

struct cmpy {
    bool operator () (const Robot &A,const Robot &B)const{
        if(A.y==B.y) return A.x<B.x;
        return A.y<B.y;
    }
};

set<Robot,cmpx> rx;
set<Robot,cmpx>:: iterator it1;
set<Robot,cmpy>:: iterator it2;
set<Robot,cmpy> ry;

inline LL tank(LL a){
    if(a>0) return a;
    return -a;
}

void start(int u){
    if(robot[u].type=='U'){
        it1=rx.lower_bound(robot[u]);if(it1==rx.end()) return;
        if(it1->x==robot[u].x){
            Q.push(Crush(tank(it1->y-robot[u].y)+st[u],u,it1->bh));
        }
    }
    else if(robot[u].type=='D'){
        it1=rx.lower_bound(robot[u]);if(it1==rx.begin()) return;it1--;
        if(it1->x==robot[u].x){
            Q.push(Crush(tank(it1->y-robot[u].y)+st[u],u,it1->bh));
        }
    }
    else if(robot[u].type=='L'){
        it2=ry.lower_bound(robot[u]);if(it2==ry.begin()) return;it2--;
        if(it2->y==robot[u].y){
            Q.push(Crush(tank(it2->x-robot[u].x)+st[u],u,it2->bh));
        }
    }
    else if(robot[u].type=='R'){
        it2=ry.lower_bound(robot[u]);if(it2==ry.end()) return;
        if(it2->y==robot[u].y){
            Q.push(Crush(tank(it2->x-robot[u].x)+st[u],u,it2->bh));
        }
    }
}

int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    char tc;
    scanf("%d%lld",&n,&T);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&robot[i].x,&robot[i].y);robot[i].bh=i;
        while((tc=getchar())&&tc!='U'&&tc!='D'&&tc!='L'&&tc!='R');
        robot[i].type=tc;
        rx.insert(robot[i]);
        ry.insert(robot[i]);
    }
    //sort(robot+1,robot+n+1,cmpx);
    //for(int i=1;i<=n;i++) rank[robot[i].bh]=i;
    memset(st,-1,sizeof(st));

    Q.push(Crush(0,0,1));
    Crush now;
    int u,v;
    while(1){
        if(Q.empty()) break;
        now=Q.top();Q.pop();
        if(now.T>=T) break;
        u=now.u;
        if(st[now.v]==-1){
            rx.erase(robot[now.v]);ry.erase(robot[now.v]);
            st[now.v]=now.T;
            start(now.v);
        }
        if(robot[now.v].type!=robot[now.u].type) start(now.u);
    }

    for(int i=1;i<=n;i++){
        if(st[i]==-1) printf("%lld %lld\n",robot[i].x,robot[i].y);
        else{
            if(robot[i].type=='R'){
                printf("%lld %lld\n",robot[i].x+T-st[i],robot[i].y);
            }
            else if(robot[i].type=='L'){
                printf("%lld %lld\n",robot[i].x-(T-st[i]),robot[i].y);
            }
            else if(robot[i].type=='U'){
                printf("%lld %lld\n",robot[i].x,robot[i].y+T-st[i]);
            }
            else if(robot[i].type=='D'){
                printf("%lld %lld\n",robot[i].x,robot[i].y-(T-st[i]));
            }
        }
    }
    return 0;
}
