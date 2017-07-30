# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int INF=10010;
const int mod=1000000007;
int n,p;
int first[maxn],fa[maxn],up[maxn],down[maxn];
int nex[maxn<<1],v[maxn<<1],edge=0;
int w[maxn];
bool vis[maxn];

void dfs_down(int x){
    down[x]=0;
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa[x]) continue;
        fa[v[e]]=x;
        dfs_down(v[e]);
        down[x]=max(down[x],down[v[e]]+1);
    }
}

void dfs_up(int x){
    int dis1=up[x]+1,dis2=-1,bh1=-1,bh2=-1;
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa[x]) continue;
        if(down[v[e]]+1>dis1) dis2=dis1,bh2=bh1,dis1=down[v[e]]+1,bh1=v[e];
        else if(down[v[e]]+1>dis2) dis2=down[v[e]]+1,bh2=v[e];
    }
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa[x]) continue;
        if(v[e]==bh1) up[v[e]]=dis2+1;
        else up[v[e]]=dis1+1;
        dfs_up(v[e]);
    }
}

struct State{
    int x,dis,_rank,anc;
    int prerank;
    bool operator < (const State &rhs)const{
        if(dis!=rhs.dis) return dis<rhs.dis;
        if(w[x]!=w[rhs.x]) return w[x]>w[rhs.x];
        return prerank<rhs.prerank;
    }
};
State que[maxn];

void add_edge(int a,int b){
    nex[edge]=first[a];v[edge]=b;first[a]=edge++;
}
vector<int> mid;
int st;

void find_st(int u){
    memset(vis,false,sizeof(vis));
    int front=0,rear=1,x,nowdis=0;
    que[front].x=u;que[front].dis=0;que[front]._rank=1;que[front].prerank=0;que[front].anc=u;
    while(front<rear){
        if(que[front].dis!=nowdis){
            nowdis=que[front].dis;
            sort(que+front,que+rear);que[front]._rank=1;
            for(int i=front+1;i<rear;i++){
                if(w[que[i].x]==w[que[i-1].x]&&que[i].prerank==que[i-1].prerank) que[i]._rank=que[i-1]._rank;
                else que[i]._rank=que[i-1]._rank+1;
            }
            //if(nowdis==ans) break;
        }
        x=que[front].x;vis[x]=1;
        for(int e=first[x];e!=-1;e=nex[e]){
            if(vis[v[e]]) continue;
            if(x==u) que[rear].anc=v[e];
            else que[rear].anc=que[front].anc;
            que[rear].dis=nowdis+1;que[rear].x=v[e];que[rear].prerank=que[front]._rank;rear++;
        }
        front++;
    }
    //st.clear();
    sort(que,que+rear);st=rear;
    //for(int i=0;i<rear;i++)
     //   printf("x:%d dist:%d anc:%d\n",que[i].x,que[i].dis,que[i].anc);
    //for(int i=front;i<rear;i++)
        //if(que[i]._rank==1)
       //     st.push_back(que[i]);
}

struct State2{
    int x,dis,_rank,anc;
    int prerank;
    bool operator < (const State2 &rhs)const{
        if(dis!=rhs.dis) return dis<rhs.dis;
        if(prerank!=rhs.prerank) return prerank<rhs.prerank;
        return w[x]>w[rhs.x];
    }
};
State2 que2[maxn];

int ed;

void find_ed(int u){
    memset(vis,false,sizeof(vis));
    int front=0,rear=1,x,nowdis=0;
    que2[front].x=u;que2[front].dis=0;que2[front]._rank=1;que2[front].prerank=0;que2[front].anc=u;
    while(front<rear){
        if(que2[front].dis!=nowdis){
            nowdis=que2[front].dis;
            sort(que2+front,que2+rear);que2[front]._rank=1;
            for(int i=front+1;i<rear;i++){
                if(w[que2[i].x]==w[que2[i-1].x]&&que2[i].prerank==que2[i-1].prerank) que2[i]._rank=que2[i-1]._rank;
                else que2[i]._rank=que2[i-1]._rank+1;
            }
        }
        x=que2[front].x;vis[x]=1;
        for(int e=first[x];e!=-1;e=nex[e]){
            if(vis[v[e]]) continue;
            if(x==u) que2[rear].anc=v[e];
            else que2[rear].anc=que2[front].anc;
            que2[rear].dis=nowdis+1;que2[rear].x=v[e];que2[rear].prerank=que[front]._rank;rear++;
        }
        front++;
    }
    ed=rear;
    //puts("ed");
    //for(int i=0;i<rear;i++)
     //   printf("x:%d dist:%d anc:%d\n",que2[i].x,que2[i].dis,que2[i].anc);
}

int q[maxn];
int last[maxn];
vector<int> print;
void BFS(int s,int t){
    memset(vis,false,sizeof(vis));
    int front=0,rear=1,x;
    q[0]=s;
    while(front<rear){
        x=q[front];vis[x]=1;
        if(x==t) break;
        for(int e=first[x];e!=-1;e=nex[e]){
            if(vis[v[e]]) continue;
            q[rear]=v[e];last[rear++]=front;
        }front++;
    }
    x=t;
    print.clear();
    while(x!=s){
        x=q[front];
        print.push_back(x);
        front=last[front];
    }
    long long ans2=0,tp2=1;
    for(int i=0;i<(int)print.size();i++){
        ans2=(ans2+w[print[i]]*tp2)%mod;
        tp2=tp2*p%mod;
    }
    printf("%I64d\n",ans2);
    for(int i=(int)print.size()-1;i>0;i--)
        printf("%d ",w[print[i]]);
    printf("%d\n",w[print[0]]);
}

int main(){
    int tcase,a,b,tnum=0;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d",&n,&p);
        memset(first,-1,sizeof(first));edge=0;
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            add_edge(a,b);add_edge(b,a);
        }
        for(int i=1;i<=n;i++)
            scanf("%d",&w[i]);
        fa[1]=1;dfs_down(1);
        up[1]=0;dfs_up(1);
        int ans=INF,_max;
        for(int i=1;i<=n;i++){
            _max=max(up[i],down[i]);
            if(_max<ans){
                mid.clear();mid.push_back(i);ans=_max;
            }
            else if(_max==ans) mid.push_back(i);
        }
        //printf("mid:%d\n",mid[0]);

            find_st(mid[0]);
            find_ed(mid[0]);
            ans=0;int _st,_ed;
            for(int i=0;i<st;i++){
                if(i>0&&que[i].anc==que[0].anc) continue;
                if(w[que[i].x]==0) continue;
                for(int j=1;j<ed;j++){
                    if(que2[j].anc==que[i].anc) continue;
                    if(que2[j].dis+que[i].dis+1>ans) ans=que2[j].dis+que[i].dis+1,_st=que[i].x,_ed=que2[j].x;
                }
                if(i>0) break;
            }
        //printf("ans:%d st:%d ed:%d\n",ans,_st,_ed);
        printf("Case #%d: ",++tnum);
        BFS(_st,_ed);
    }
    return 0;
}
