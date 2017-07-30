# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
# define mp(a,b) make_pair(a,b)
using namespace std;
const int maxn=100010;
int n,m;
struct Edge{
    int u,v,l,r;
    Edge(){}
    Edge(int u,int v,int l,int r):u(u),v(v),l(l),r(r){}
}edges[maxn*3];
int edge=0;
bool ans[maxn];
int p[maxn],s[maxn*40],sp[maxn*40],top=-1,re[maxn],size[maxn];
int sre[maxn*40];
pair<int,int> ssize[maxn*40];

char t;
void read(int &x){
    while((t=getchar())&&(t<'0'||t>'9'));
    x=t-'0';
    while((t=getchar())&&(t>='0'&&t<='9'))
        x=x*10+t-'0';
}

int root,xx,rr;
int find(int x){
    root=x;rr=0;
    while(p[root]!=root) rr=rr^re[root],root=p[root];
    while(x!=root){
        ++top;sp[top]=p[x];s[top]=x;sre[top]=re[x];ssize[top]=mp(0,0);
        xx=p[x];p[x]=root;re[x]=rr;x=xx;rr=rr^sre[top];
    }
    return root;
}

bool merge(int a,int b){
    int pa=find(a),pb=find(b);
    if(pa==pb){
           // printf("hei a:%d b:%d \n",a,b);
        return ((re[a]+re[b])&1);
    }
    if(size[pa]>size[pb]) swap(pa,pb),swap(a,b);
    top++;s[top]=pa;sp[top]=p[pa];sre[top]=re[pa];ssize[top]=mp(pb,size[pb]);
    p[pa]=pb;re[pa]=re[a]^1^re[b];size[pb]+=size[pa];
    return true;
}

void recover(int lim){
    while(top>lim){
        if(ssize[top].first!=0) size[ssize[top].first]=ssize[top].second;
        re[s[top]]=sre[top];
        p[s[top]]=sp[top];top--;
    }
    return;
}

void solve(int L,int R,int l,int r){
    //printf("L:%d R:%d\n",L,R);
    int nows=top,r0,mid=(L+R)>>1;
    bool ok=true;
    for(int i=l;i<=r;i++){
       // printf("a:%d b:%d l:%d r:%d\n",edges[i].u,edges[i].v,edges[i].l,edges[i].r);
        if(edges[i].l<=L&&edges[i].r>=R){
            if(!merge(edges[i].u,edges[i].v)) //printf("attention\n%d %d\n\n",edges[i].u,edges[i].v),
                ok=false;
        }
    }
    if(!ok){
        //puts("shit");
        for(int i=L;i<=R;i++) ans[i]=0;
        recover(nows);
        return;
    }
    if(L<R){
        r0=l;
        for(int i=l;i<=r;i++){
            if(edges[i].l<=mid&&(!(edges[i].l<=L&&edges[i].r>=R))) swap(edges[i],edges[r0]),r0++;
        }
        if(l<=r0-1)
            solve(L,mid,l,r0-1);
        r0=l;
        for(int i=l;i<=r;i++){
            if(edges[i].r>mid&&(!(edges[i].l<=L&&edges[i].r>=R))) swap(edges[i],edges[r0]),r0++;
        }
        if(l<=r0-1)
            solve(mid+1,R,l,r0-1);
    }
    recover(nows);
    return;
}

int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int a,b;
    int tcase;
    read(tcase);
    while(tcase--){
        edge=0;
        read(n);read(m);
        for(int i=1;i<=m;i++){
            read(a);read(b);
            if(a>b) swap(a,b);
            if(1<a) edges[edge++]=Edge(a,b,1,a-1);
            if(a+1<b) edges[edge++]=Edge(a,b,a+1,b-1);
            if(b<n) edges[edge++]=Edge(a,b,b+1,n);
        }
        for(int i=1;i<=n;i++) p[i]=i,re[i]=0,ans[i]=1;
        solve(1,n,0,edge-1);
        for(int i=1;i<=n;i++)
            printf("%d",ans[i]);
        puts("");
    }
    return 0;
}
