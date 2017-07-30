/*
100*500*100
100*500*100
*/
# include<stdio.h>
# include<string.h>
# include<math.h>
# include<queue>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=103;

struct HeapNode{
    bool vis[maxn];
    int last[maxn];
    int x,d;
    HeapNode() {}
    bool operator < (const HeapNode &rhs)const{
        return rhs.d<d||(rhs.d==d);
    }
};
priority_queue<HeapNode> Q;

int n,m,k;
int inq[maxn];
int dis[maxn][maxn];
int st,ed;
HeapNode now,ans;
vector<int> print;
int main(){
    int a,b,c;
    memset(inq,0,sizeof(inq));
    memset(dis,0,sizeof(dis));
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&a,&b,&c);dis[a][b]=dis[b][a]=c;
    }
    scanf("%d%d",&st,&ed);
    now.x=st;now.d=0;for(int i=1;i<=n;i++) now.vis[i]=0;now.vis[st]=1;
    Q.push(now);
    int x;
    while(!Q.empty()){
        now=Q.top();Q.pop();
        x=now.x;
        if(++inq[x]>k) continue;
        if(x==ed&&inq[x]==k) {ans=now;goto loop;}
        //printf("x:%d d:%d\n",now.x,now.d);
        for(int v=1;v<=100;v++)
            if(!now.vis[v]&&dis[x][v]!=0&&inq[v]<k){
                now.vis[v]=1;now.last[v]=x;now.x=v;now.d+=dis[x][v];
                Q.push(now);
                now.vis[v]=0;now.last[v]=0;now.x=x;now.d-=dis[x][v];
            }
    }
    loop:
   // puts("fuck");
    x=ed;
    while(x!=st) print.push_back(x),x=ans.last[x];
    printf("%d %d\n",ans.d,(int)print.size()+1);
    printf("%d",st);
    for(int i=(int)print.size()-1;i>=0;i--)
        printf(" %d",print[i]);
    printf("\n");
    return 0;
}
