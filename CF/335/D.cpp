# include<stdio.h>
# include<string.h>
# include<set>
# include<queue>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=200010;
const int INF=1000010;
typedef pair<int,int> pi;
# define mp(a,b) make_pair(a,b)

struct Node{
    int a,b,c,d;
    Node() {}
}card[maxn];

int n;
int x[maxn],y[maxn],cnt,xcnt,ycnt;
pi init;

struct SegmenTree{
    pi minv[maxn<<2];
    set<pi> s[maxn];

    void build(int o,int L,int R){
        minv[o]=init;
        if(L==R) return;
        int M=(L+R)>>1;
        build(o<<1,L,M);build(o<<1|1,M+1,R);
    }

    void insert(int o,int L,int R,int pos,pi v){
        if(L==R){
            s[L].insert(v);minv[o]=*s[L].begin();
            return;
        }
        int M=(L+R)>>1;
        if(pos<=M) insert(o<<1,L,M,pos,v);
        else insert(o<<1|1,M+1,R,pos,v);
        minv[o]=min(minv[o<<1],minv[o<<1|1]);
    }

    pi query(int o,int L,int R,int r){
        if(R<=r) return minv[o];
        int M=(L+R)>>1;
        if(r<=M) return query(o<<1,L,M,r);
        else return min(minv[o<<1],query(o<<1|1,M+1,R,r));
    }

    void erase(int o,int L,int R,int pos,pi v){
        if(L==R){
            s[L].erase(v);
            if(s[L].empty()) minv[o]=init;
            else minv[o]=*s[L].begin();
            return;
        }
        int M=(L+R)>>1;
        if(pos<=M) erase(o<<1,L,M,pos,v);
        else erase(o<<1|1,M+1,R,pos,v);
        minv[o]=min(minv[o<<1],minv[o<<1|1]);
    }

}seg;

queue<int> q;
int d[maxn];
pi tmp;
int last[maxn];

void bfs(){
    int bh,x,y;
    memset(d,-1,sizeof(d));
    q.push(0);d[0]=0;
    while(!q.empty()){
        bh=q.front();q.pop();
       // printf("bh:%d\n",bh);
        x=card[bh].c;y=card[bh].d;
        //printf("x:%d y:%d\n",x,y);
        while(1){
             tmp=seg.query(1,1,xcnt,x);
            // printf("tmp.sec:%d\n",tmp.second);
             if(tmp.first>y) break;
             seg.erase(1,1,xcnt,card[tmp.second].a,tmp);
             d[tmp.second]=d[bh]+1;last[tmp.second]=bh;
             q.push(tmp.second);
        }
    }
}
vector<int> print;

int main(){
    init=mp(INF,0);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&card[i].a,&card[i].b,&card[i].c,&card[i].d);
        x[++xcnt]=card[i].a;x[++xcnt]=card[i].c;
        y[++ycnt]=card[i].b,y[++ycnt]=card[i].d;
    }
    x[++xcnt]=0;y[++ycnt]=0;
    sort(x+1,x+xcnt+1);
    sort(y+1,y+ycnt+1);
    xcnt=unique(x+1,x+xcnt+1)-x-1;
    ycnt=unique(y+1,y+ycnt+1)-y-1;

    for(int i=1;i<=n;i++){
        card[i].a=lower_bound(x+1,x+xcnt+1,card[i].a)-x;
        card[i].c=lower_bound(x+1,x+xcnt+1,card[i].c)-x;
        card[i].b=lower_bound(y+1,y+ycnt+1,card[i].b)-y;
        card[i].d=lower_bound(y+1,y+ycnt+1,card[i].d)-y;
    }
    card[0].c=card[0].d=1;
    //if(x[1]>0||y[1]>0) {puts("-1");return 0;}

    seg.build(1,1,xcnt);
    for(int i=1;i<=n;i++){
        seg.insert(1,1,xcnt,card[i].a,mp(card[i].b,i));
    }

    bfs();
    printf("%d\n",d[n]);
    if(d[n]!=-1){
        while(n!=0){
            print.push_back(n);n=last[n];
        }
        for(int e=(int)print.size()-1;e>0;e--){
            printf("%d ",print[e]);
        }printf("%d\n",print[0]);
    }
    return 0;
}
