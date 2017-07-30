#include<stdio.h>
# include<iostream>
# include<queue>
# include<map>
# include<vector>
# include<string>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=32;
const int INF=~0U>>1;
int n,m,ans;
map<string,int> id;
string s;
int g[maxn][maxn];
vector<int> Code[maxn];

struct state{
	int at,code;
	
	void encode(int go){
		int res=code;
		for(int i=0;i<Code[go].size();i++)
			res=res|(1<<Code[go][i]);
		code=res;
	}
	
	bool isfree(){
		for(int i=0;i<4;i++){
			int a=(code>>(i*2))&3;
			if(a!=0&&a!=3) return false;
		}
		return true;
	}
	
};

struct HeapNode{
	int d;state u;
	HeapNode(){}
	HeapNode(int d,state u):d(d),u(u) {}
	bool operator < (const HeapNode &rhs)const{
		return d>rhs.d;
	}
};

bool used[maxn][1<<8];
int Dist[maxn][1<<8];


void dijkstra(){
	memset(used,false,sizeof(used));
	memset(Dist,-1,sizeof(Dist));
	priority_queue<HeapNode> Q;
	for(int i=1;i<=n;i++){
		state now;now.at=i;now.code=0;now.encode(i);
		Dist[now.at][now.code]=0;
		Q.push(HeapNode(0,now));
	}
	
	while(!Q.empty()){
		state now=Q.top().u;Q.pop();
		if(used[now.at][now.code]) continue;
		if(now.code==(1<<8)-1) {ans=Dist[now.at][now.code];break;}
		used[now.at][now.code]=1;
		//printf("Dist[%d][%d]:%d\n",now.at,now.code,Dist[now.at][now.code]);
		for(int go=1;go<=n;go++){
			if(g[now.at][go]!=INF){
				state next=now;
				next.encode(go);next.at=go;
				int w=now.isfree()?0:g[now.at][go];
				if(Dist[next.at][next.code]==-1||Dist[next.at][next.code]>Dist[now.at][now.code]+w){
					Dist[next.at][next.code]=Dist[now.at][now.code]+w;
					Q.push(HeapNode(Dist[next.at][next.code],next));
				}
			}
		}
		for(int code=0;code<(1<<8);code++){
			if(Dist[now.at][code]!=-1){
				state next=now;
				next.code=next.code|code;
				if(Dist[next.at][next.code]==-1||Dist[next.at][next.code]>Dist[now.at][now.code]+Dist[now.at][code]){
					Dist[next.at][next.code]=Dist[now.at][now.code]+Dist[now.at][code];
					Q.push(HeapNode(Dist[next.at][next.code],next));
				}
			}
		}
	}
	
}

int main(){
	int a,b,c;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		cin>>s,id[s]=i;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) g[i][j]=INF;
	for(int i=1;i<=m;i++){
		cin>>s;a=id[s];cin>>s;b=id[s];
		scanf("%d",&c);
		g[a][b]=g[b][a]=min(g[a][b],c);
	}
	for(int i=0;i<8;i++){
		cin>>s;a=id[s];
		Code[a].push_back(i);
	}
	dijkstra();
	printf("%d\n",ans);
	return 0;
}
