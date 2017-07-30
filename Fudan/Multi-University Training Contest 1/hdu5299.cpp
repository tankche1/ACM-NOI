# include<stdio.h>
# include<string.h>
# include<math.h>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=20010;
const int INF=1000000;
int tcase;
int n;

struct Point{
    int x,y;
    Point(int x=0,int y=0):x(x),y(y){}
};

struct Circle{
    Point c;int r;
    Circle() {}
    Circle(Point c,int r=0):c(c),r(r) {}
    bool operator < (const Circle &rhs)const{
        if(c.x==rhs.c.x&&c.y==rhs.c.y) return r<rhs.r;
        return (c.x==rhs.c.x)?(c.y<rhs.c.y):c.x<rhs.c.x;
    }
};
Circle C[maxn];

bool cmp(Circle A,Circle B){
    return A.r<B.r;
}

int first[maxn],nex[maxn<<1],v[maxn<<1],edge=0;
void add_edge(int a,int b){
    nex[edge]=first[a];v[edge]=b;first[a]=edge++;
}
int sg[maxn];
void dfs(int x){
    for(int e=first[x];e!=-1;e=nex[e])
        dfs(v[e]);
    sg[x]=0;
    for(int e=first[x];e!=-1;e=nex[e]){
        sg[x]=sg[x]^(sg[v[e]]+1);
    }
}

set<Circle> s;
int main(){
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d",&n);

        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&C[i].c.x,&C[i].c.y,&C[i].r);
        }
        int root=n+1;
        bool ok;
        memset(first,-1,sizeof(first));edge=0;
        s.clear();
        s.insert(Circle(Point(0,0),INF));
        for(int i=n;i>=1;i--){
            ok=true;

        }
        dfs(root);
        if(sg[root]>0) puts("Alice");
        else puts("Bob");
    }
    return 0;
}
