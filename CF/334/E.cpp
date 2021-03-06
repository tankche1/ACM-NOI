# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=300010;
int n,m,odd;
int ans[maxm];

struct Edge{
    int u,v,w;
    int bh,rank;
    Edge() {}
};
Edge ori[maxm],sorted[maxm];

struct Node{
    int a,b,sz_b;
    Node(){}
    Node(int a,int b,int sz_b):a(a),b(b),sz_b(sz_b) {}
};
Node S[maxn];
int top;

bool cmp(Edge A,Edge B) {return A.w<B.w;}

int p[maxn],sz[maxn];

void Union(int a,int b){
    int pa=a;
    while(p[pa]!=pa) pa=p[pa];
    int pb=b;
    while(p[pb]!=pb) pb=p[pb];
    if(pa==pb) return;
    if(sz[pa]>sz[pb]) swap(pa,pb);
    odd=odd-(sz[pa]&1)-(sz[pb]&1);
    S[++top]=Node(pa,pb,sz[pb]);
    p[pa]=pb;sz[pb]+=sz[pa];
    odd+=sz[pb]&1;
}

void Backup(int pos){
    while(top>pos){
        odd-=sz[S[top].b]&1;
        p[S[top].a]=S[top].a;sz[S[top].b]=S[top].sz_b;
        odd+=sz[S[top].a]&1;odd+=sz[S[top].b]&1;
        top--;
    }
}

void solve(int L,int R,int LL,int RR){
    //printf("L:%d R:%d LL:%d RR:%d\n",L,R,LL,RR);
    if(L>R) return;
    int pos=top,mid=(L+R)>>1,nmid=0;

    for(int i=L;i<=mid;i++){
        if(ori[i].rank<LL) Union(ori[i].u,ori[i].v);
    }

    for(int i=LL;i<=RR;i++){
        if(sorted[i].bh<=mid){
            Union(sorted[i].u,sorted[i].v);
            if(odd==0){
                nmid=i;break;
            }
        }
    }
    ans[mid]=nmid;
    Backup(pos);

    if(nmid==0){
        for(int i=L;i<=mid;i++){
            if(ori[i].rank<LL) Union(ori[i].u,ori[i].v);
        }
        for(int i=L;i<=mid;i++) ans[i]=0;
        solve(mid+1,R,LL,RR);
        Backup(pos);
        return;
    }

    for(int i=LL;i<nmid;i++){
        if(sorted[i].bh<L) Union(sorted[i].u,sorted[i].v);
    }

    solve(L,mid-1,nmid,RR);
    Backup(pos);

    for(int i=L;i<=mid;i++){
        if(ori[i].rank<LL) Union(ori[i].u,ori[i].v);
    }

    solve(mid+1,R,LL,nmid);
    Backup(pos);
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&ori[i].u,&ori[i].v,&ori[i].w);ori[i].bh=i;
        sorted[i]=ori[i];
    }
    if(n%2==1) {for(int i=1;i<=m;i++) puts("-1");return 0;}
    sort(sorted+1,sorted+m+1,cmp);odd=n;
    for(int i=1;i<=m;i++) sorted[i].rank=i,ori[sorted[i].bh].rank=i;

    for(int i=1;i<=n;i++) p[i]=i,sz[i]=1;
    top=-1;
    solve(1,m,1,m);

    sorted[0].w=-1;
    for(int i=1;i<=m;i++)
        printf("%d\n",sorted[ans[i]].w);
    return 0;
}
