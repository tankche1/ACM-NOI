# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;

struct State{
    int len;
    State *par,*go[10];
    State(){
    }
};
State *root,*last;
State seq[maxn*2*20];int seq_cnt;
State *New(int _len){
    State *o=&seq[seq_cnt++];
    memset(o->go,0,sizeof(o->go));o->par=0;o->len=_len;
    return o;
}

State* extend(State *p,int w){
    State *np=New(p->len+1);
    while(p&&p->go[w]==0) p->go[w]=np,p=p->par;
    if(p==0) np->par=root;
    else{
        State *q=p->go[w];
        if(q->len==p->len+1){
            np->par=q;
        }
        else{
            State *nq=New(p->len+1);
            memcpy(nq->go,q->go,sizeof(q->go));
            nq->par=q->par;
            q->par=nq;
            np->par=nq;
            while(p&&p->go[w]==q)
                p->go[w]=nq,p=p->par;
        }
    }
    return np;
}


void init(){
    seq_cnt=0;root=New(0);last=root;
}
int n,c;
int leaf[21];
int col[maxn];
int first[maxn],v[maxn<<1],nex[maxn<<1],edge=0;
int du[maxn];

void add_edge(int a,int b){
    nex[edge]=first[a];v[edge]=b;first[a]=edge++;
}

void dfs(int x,int fa,State *pre){
    State *p=extend(pre,col[x]);
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa) continue;
        dfs(v[e],x,p);
    }
}

int main(){
    int a,b;
    init();
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++){
        scanf("%d",&col[i]);
    }
    memset(first,-1,sizeof(first));edge=0;
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);add_edge(a,b);add_edge(b,a);du[a]++;du[b]++;
    }
    for(int i=1;i<=n;i++)
        if(du[i]==1){
            dfs(i,0,root);
        }
    long long ans=0;
    for(int i=1;i<seq_cnt;i++)
        ans+=seq[i].len-seq[i].par->len;
    printf("%lld\n",ans);
    return 0;
}
