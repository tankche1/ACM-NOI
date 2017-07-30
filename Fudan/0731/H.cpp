# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<queue>
# include<string>
# include<map>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=3*5010;
const int maxm=5010*4;

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[maxn],nnext[maxm<<1],edge;
	Edge edges[maxm<<1];
	int n,s,t;
	int cur[maxn],d[maxn];

	void init(int nn){
		n=nn;
		edge=0;
		memset(first,-1,sizeof(first));
	}

	void add_edge(int from,int to,int cap){
		nnext[edge]=first[from];
		edges[edge]=Edge(from,to,0,cap);
		first[from]=edge++;
		nnext[edge]=first[to];
		edges[edge]=Edge(to,from,0,0);
		first[to]=edge++;
	}

	bool BFS(){
		for(int i=0;i<n;i++) d[i]=INF;
			d[s]=0;
		queue<int> q;q.push(s);
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int e=first[x];e!=-1;e=nnext[e]){
				if(edges[e].cap>edges[e].flow&&d[edges[e].to]>d[x]+1){
					d[edges[e].to]=d[x]+1;
					q.push(edges[e].to);
				}
			}
		}
		return d[t]!=INF;
	}

	int DFS(int x,int a){
		if(x==t||a==0) return a;
			int flow=0,f;
		for(int &e=cur[x];e!=-1;e=nnext[e]){
			if(d[edges[e].to]==d[x]+1&&(f=DFS(edges[e].to,min(edges[e].cap-edges[e].flow,a)))>0){
				flow+=f;
				a-=f;
				edges[e].flow+=f;
				edges[e^1].flow-=f;
				if(a==0) break;
			}
		}
		return flow;
	}

	int maxflow(int ss,int tt){
		s=ss;t=tt;
		int flow=0;
		while(BFS()){
			for(int i=0;i<n;i++) cur[i]=first[i];
			flow+=DFS(s,INF);
		}
		return flow;
	}
}dinic;

int n,k,len;
int belong[maxn];
string ss;
map<string,int> id1,id2;
int cnt1=0,cnt2=0;
int pre[maxn],suf[maxn],prebh[maxn],sufbh[maxn];
char s[650];
bool vis[maxn];
vector<int> print[maxn];
bool visS[maxn],visT[maxn];
int main(){
    freopen("heavy.in","r",stdin);
    freopen("heavy.out","w",stdout);
    int bh;
    scanf("%d%d",&n,&k);getchar();
    int S=0,T=2*n+1;
    dinic.init(T+1);
    for(int i=1;i<=n;i++){
        gets(s);
        ss="";len=strlen(s);
        for(int j=0;j<k;j++){
            ss+=s[j];
        }
        if(!id1.count(ss)) id1[ss]=++cnt1;
        bh=id1[ss];prebh[i]=bh;
        ss="";
        for(int j=len-k;j<len;j++)
            ss=ss+s[j];
        if(!id2.count(ss)) id2[ss]=++cnt2;
        bh=id2[ss];sufbh[i]=bh;
        dinic.add_edge(prebh[i],sufbh[i]+n,INF);
    }
    int eedge=dinic.edge;
    for(int i=1;i<=cnt1;i++){
        dinic.add_edge(S,i,1);
    }
    for(int i=1;i<=cnt2;i++){
        dinic.add_edge(n+i,T,1);
    }
        //printf("hei");
    int ans=dinic.maxflow(S,T);
    printf("%d\n",ans);
    dinic.BFS();for(int i=0;i<=T;i++) visS[i]=dinic.d[i]!=INF;
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=cnt1;i++){
        if(!visS[i]) vis[i]=1;
    }

    for(int i=1;i<=n;i++){
        if(vis[prebh[i]]) belong[i]=prebh[i];
        else belong[i]=n+sufbh[i];
        print[belong[i]].push_back(i);
    }
    for(int i=1;i<=2*n;i++){
        if(print[i].size()){
            printf("%d",print[i].size());
            for(int j=0;j<print[i].size();j++)
                printf(" %d",print[i][j]);
            puts("");
        }
    }
    return 0;
}
