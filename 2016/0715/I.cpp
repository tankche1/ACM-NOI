# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=~0U>>1;
const int maxm=10*maxn;
typedef pair<int,int> pi;
typedef long long LL;
pi road[maxm];
int n,m,a,b;
vector<int> G[maxn];
int d[maxn];
queue<int> Q;
int l[maxn],r[maxn];

void del(int x){
    r[l[x]]=r[x];l[r[x]]=l[x];
}

int main(){
   // freopen("input.txt","r",stdin);
    int x,y;
    while(scanf("%d%d%d%d",&n,&m,&a,&b)!=EOF){
        bool in=false;
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1;i<=m;i++){
            scanf("%d%d",&x,&y);
            road[i]=make_pair(x,y);G[x].push_back(y);G[y].push_back(x);
            road[m+i]=make_pair(y,x);
            if((x==1&&y==n)||(x==n&&y==1)) in=true;
        }

        if(a<=b&&in) {printf("%d\n",a);continue;}
        if(b<=a&&(!in)) {printf("%d\n",b);continue;}

        if(a<b){
            Q.push(1);memset(d,-1,sizeof(d));d[1]=0;
            while(!Q.empty()){
                int x=Q.front();Q.pop();
                if(d[x]>=b) continue;
                for(int e=0;e<(int)G[x].size();e++){
                    if(d[G[x][e]]==-1) {d[G[x][e]]=d[x]+a;Q.push(G[x][e]);}
                }
            }
            if(d[n]==-1) d[n]=INF;
            printf("%d\n",min(d[n],b));
        }
        else{
            sort(road+1,road+2*m+1);
            road[2*m+1]=make_pair(-1,-1);
            Q.push(1);memset(d,-1,sizeof(d));d[1]=0;
            l[0]=0;r[n+1]=n+1;
            for(int i=1;i<=n+1;i++) l[i]=i-1;for(int i=0;i<n+1;i++) r[i]=i+1;del(1);
            while(!Q.empty()){
                int x=Q.front();Q.pop();
                if(d[x]>=a) continue;
                int now=lower_bound(road+1,road+2*m+1,make_pair(x,0))-road;
                for(int i=r[0];i!=n+1;i=r[i]){
                    while(road[now].first==x&&road[now].second<i) now++;
                    if(road[now].first==x&&road[now].second==i) continue;
                    d[i]=d[x]+b;
                    del(i);
                    Q.push(i);
                }
            }
            if(d[n]==-1) d[n]=INF;
            printf("%d\n",min(a,d[n]));
        }
    }
    return 0;
}
