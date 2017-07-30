# include<stdio.h>
# include<string.h>
# include<vector>
# include<map>
# include<algorithm>
using namespace std;
typedef pair<int,int> pi;
const int maxn=500010;
int n;
vector<pi> G[maxn];
vector<pair<pi,int> > edges[maxn];
int u[maxn<<1],vv[maxn<<1];
int p[maxn];
bool stay[maxn];
bool used[maxn];
#define find _find
# define mp make_pair
int find(int x){
    if(x==p[x]) return x;
    return p[x]=find(p[x]);
}

map<pi,int> id;

void Union(int x,int y){
    int px=find(x),py=find(y);
    if(px==py) return;
    p[px]=py;
    if((int)edges[px].size()>(int)edges[py].size())
        swap(edges[px],edges[py]);
    for(int e=0;e<(int)edges[px].size();e++){
        edges[py].push_back(edges[px][e]);
    }
}

void dfs(int x,int fa){
    //printf("x:%d fa:%d\n",x,fa);
    int v;
    for(int e=0;e<(int)G[x].size();e++){
        v=G[x][e].first;

        if(v==fa) continue;
        dfs(v,x);// printf("v:%d\n",v);
        if(stay[G[x][e].second]){
               // puts("fuck");
            Union(v,x);continue;
        }

        int t=(int)edges[v].size()-1;//printf("t:%d\n",t);
        while(used[edges[v][t].second]){
                //printf("heu");
            edges[v].pop_back();t--;
        }
        used[edges[v][t].second]=1;
        printf("%d %d %d %d\n",u[G[x][e].second],vv[G[x][e].second],u[n-1+edges[v][t].second],vv[n-1+edges[v][t].second]);
        edges[v].pop_back();
        Union(v,edges[v][t].first.second);

    }
}

int main(){
    int a,b;
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);u[i]=a;vv[i]=b;if(a>b) swap(a,b);
        id[make_pair(a,b)]=i;
        stay[i]=false;
        G[a].push_back(mp(b,i));G[b].push_back(mp(a,i));
    }

    int ans=n-1;
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);u[n-1+i]=a;vv[n-1+i]=b;if(a>b) swap(a,b);
        if(id.count(make_pair(a,b))) {stay[id[mp(a,b)]]=true;ans--;continue;}
        edges[a].push_back(mp(mp(a,b),i));edges[b].push_back(mp(mp(b,a),i));
        used[i]=false;
    }

    for(int i=1;i<=n;i++) p[i]=i;

    printf("%d\n",ans);
    dfs(1,0);
    return 0;
}
