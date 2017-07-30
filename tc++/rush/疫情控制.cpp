# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=50010;
const int maxk=20;
int maxj;
typedef long long LL;
int first[maxn],_next[maxn<<1],v[maxn<<1],dist[maxn<<1],edge;
int fa[maxn],w[maxn],son[maxn],now_son[maxn];
int n,m,army[maxn];
int which[maxn];
bool control[maxn];
struct state{
	int to;LL dis;
	state() {}
	state(int to,LL dis):to(to),dis(dis) {}
};
state dp[maxn][maxk];

struct Brave{
	LL left;
	int from;
	Brave() {}
	Brave(LL left,int from):left(left),from(from) {}
	bool operator < (Brave rhs)const{
		return left<rhs.left;
	}
};
Brave brave[maxn];
int attop;
int bh[maxn];

bool cmp(int a,int b){
	return dist[a]<dist[b];
}

void add_edge(int from,int to,int dis){
	_next[edge]=first[from];
	v[edge]=to;
	dist[edge]=dis;
	first[from]=edge++;
}

void dfs(int x,int Fa){
	son[x]=0;
	if(x!=1) which[x]=which[0];
	for(int e=first[x];e!=-1;e=_next[e]){
		if(v[e]==Fa) continue;
		w[v[e]]=dist[e];
		son[x]++;
		fa[v[e]]=x;
		if(x==1) which[0]=v[e];
		dfs(v[e],x);
	}
}

void cal_dp(){
	for(int i=1;i<=n;i++){
		//printf("fa[%d]:%d w:%d which:%d son:%d\n",i,fa[i],w[i],which[i],son[i]);
		dp[i][0]=state(fa[i],w[i]);
	}
	for(int j=1;;j++){
		bool ok=true;
		for(int i=1;i<=n;i++){
			dp[i][j]=state(dp[dp[i][j-1].to][j-1].to,dp[i][j-1].dis+dp[dp[i][j-1].to][j-1].dis);
			if(dp[i][j].to!=1) ok=false;
		}
		if(ok) {maxj=j;break;}
	}
	bh[0]=0;
	for(int e=first[1];e!=-1;e=_next[e]){
		bh[++bh[0]]=e;
	}
	sort(bh+1,bh+bh[0]+1,cmp);
}

void climb(int x,LL T){
	int now=x;LL TT=T;
	for(int j=maxj;j>=0;j--){
		if(TT>=dp[now][j].dis){
			TT-=dp[now][j].dis;
			now=dp[now][j].to;
		}
	}
	if(now==1) brave[++attop]=Brave(TT,which[x]);
	else if(!control[now]){
		control[now]=1;
		while(now!=1&&--now_son[fa[now]]==0){
			control[fa[now]]=1;
			now=fa[now];
		}
	}
}

bool check(LL Ti){
	memset(control,false,sizeof(control));
	for(int i=1;i<=n;i++)
		now_son[i]=son[i];
	attop=0;
	for(int i=1;i<=m;i++)
		climb(army[i],Ti);
	sort(brave+1,brave+attop+1);
	int nowj=1;
	for(int i=1;i<=attop;i++){
		while(control[v[bh[nowj]]]&&nowj<=bh[0]) nowj++;
		if(nowj>bh[0]) break;
		if(!control[brave[i].from]) control[brave[i].from]=1,--now_son[1];
		else if(brave[i].left>=dist[bh[nowj]])
			control[v[bh[nowj]]]=1,--now_son[1];
	}
	if(now_son[1]==0) return true;
		else return false;
}

int main(){
	int a,b,c;
	scanf("%d",&n);
	memset(first,-1,sizeof(first));edge=0;
	LL sum=0;
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);sum+=c;
		add_edge(a,b,c);add_edge(b,a,c);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&army[i]);
	fa[1]=1;w[1]=0;
	dfs(1,0);
	if(m<son[1]) {puts("-1");return 0;}
	cal_dp();
	LL L=0,R=sum;
	while(L<=R){
		LL M=(L+R)>>1;
		//printf("M:%lld\n",M);
		if(check(M)) R=M-1;
			else L=M+1;
	}
	printf("%lld\n",R+1);
	return 0;
}
