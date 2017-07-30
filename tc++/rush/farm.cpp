# include<stdio.h>
# include<string.h>
# include<stack>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int maxm=10010;
int n,m;
stack<int> S;
bool instack[maxn];
int cnt[maxn],dist[maxn];
int first[maxn],next[maxm<<1],v[maxm<<1],edge,w[maxm<<1];

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	w[edge]=c;
	v[edge]=b;
	first[a]=edge++;
}

bool spfa(){
	memset(instack,false,sizeof(instack));
	//memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++)
		S.push(i),instack[i]=true,cnt[i]=1,dist[i]=0;
	while(!S.empty()){
		int x=S.top();S.pop();
		for(int e=first[x];e!=-1;e=next[e]){
			if(dist[v[e]]<dist[x]+w[e]){
				dist[v[e]]=dist[x]+w[e];
				if(++cnt[v[e]]>n) return false;
				if(!instack[v[e]])
					S.push(v[e]),instack[v[e]]=1;
			}
		}
	}
	return true;
}

int main(){
	int op,a,b,c;
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&op,&a,&b);
		if(op==3)
			add_edge(a,b,0),add_edge(b,a,0);
		else if(op==1)
			scanf("%d",&c),add_edge(a,b,-c);
		else
			scanf("%d",&c),add_edge(b,a,c);
	}
	if(!spfa()) puts("No");
		else puts("Yes");
	return 0;
}
