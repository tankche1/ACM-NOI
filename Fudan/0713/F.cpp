/*
1.枚举queen和king之间的点
2.计算子问题-每颗子树满足条件后取得的点权最大值
3.len是奇数就枚举边 是偶数就枚举点
*/

# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
# define mp(a,b) make_pair(a,b)
using namespace std;
const int maxn=410;
typedef pair<int,int> pi;
int INF=1000000000;
pair<int,int> inf=mp(-INF,-INF);
int n,d[2],c[2];
int cost[maxn];
int first[maxn],next[maxn<<1],v[maxn<<1],avail[maxn<<1],edge=0;
bool choose[maxn];

void add_edge(int a,int b){
	next[edge]=first[a];v[edge]=b;first[a]=edge++;
	next[edge]=first[b];v[edge]=a;first[b]=edge++;
}

pair<pi,pair<pi,pi> > ans;//ans.first 1:和 2.dot ans.second 1.king 2.queen
int top,stack[maxn];
int fa[maxn];
void dfs(int x){
	stack[++top]=x;
	for(int e=first[x];e!=-1;e=next[e])
		if(avail[e]&&fa[x]!=v[e])
			fa[v[e]]=x,dfs(v[e]);
}

vector<int> List;
vector<int>::iterator it;
int q[maxn],tail,head,belong[maxn],deep[maxn];

void add(int &tmp,int x,bool cho){
	tmp+=cost[x];if(cho) choose[x]=1;
}
bool cmp(int a,int b){return cost[a]>cost[b];}
int Set(int dot,int len,int k,bool cho){
	//printf("SET dot:%d len:%d k:%d cho:%d\n",dot,len,k,cho);
	List.clear();
	head=1;tail=0;q[++tail]=dot;belong[dot]=0;
	int tmp=0,x,limit=len>>1;
	memset(deep,-1,sizeof(deep));deep[dot]=0;
	if(len&1){
		q[++tail]=fa[dot];
		deep[fa[dot]]=0;belong[fa[dot]]=fa[dot];belong[dot]=dot;
	}
	while(head<=tail){
		x=q[head++];//printf("x:%d\n",x);
		if(deep[x]==limit){List.push_back(x);continue;}
		add(tmp,x,cho);
		for(int e=first[x];e!=-1;e=next[e])
			if(avail[e]&&deep[v[e]]==-1){
				deep[v[e]]=deep[x]+1;q[++tail]=v[e];
				if(belong[x]) belong[v[e]]=belong[x];else belong[v[e]]=v[e];
			}
	}
	//printf("gone");
	sort(List.begin(),List.end(),cmp);
	//for(int i=0;i<List.size();i++) printf("List[%d]:%d\n",i,List[i]);
	int cnt=0;int same=belong[List[0]],another=0;it=List.begin();
	while(it!=List.end()&&cnt<k-1){//一边
		if(belong[*it]!=same) break;
		cnt++;add(tmp,*it,cho);
		it++;
	}
	//printf("gd");
	//另一边
	while(it!=List.end()&&belong[*it]==same) it++;
	while(it!=List.end()&&cnt<k){
		cnt++;add(tmp,*it,cho);it++;another++;
	}
	if(cnt<2) return -INF;
	if(!another) return -INF;
	return tmp;
}

int Calc(int dot,int len,int k,bool cho){
	if(k==1&&len!=0) return -INF;
	memset(fa,-1,sizeof(fa));
	top=0;dfs(dot);pi ret=inf;//printf("dfs good\n");
	if(len==0){
		for(int i=1;i<=top;i++){
			ret=max(ret,mp(cost[stack[i]],stack[i]));
		}
		if(cho) choose[ret.second]=1;
		return ret.first;
	}
	for(int i=(len&1)+1;i<=top;i++){
		int tmp=Set(stack[i],len,k,0);
		ret=max(ret,mp(tmp,stack[i]));
	}
	if(cho) Set(ret.second,len,k,1);
	return ret.first;
}

int main(){
	ans.first.first=ans.first.second=ans.second.first.first=ans.second.first.second=ans.second.second.first=ans.second.second.second=0;
	int e1,e2,S=0;
	memset(first,-1,sizeof(first));
	scanf("%d%d%d%d%d",&n,&d[0],&c[0],&d[1],&c[1]);
	for(int i=1;i<=n;i++)
		scanf("%d",&cost[i]),S+=cost[i];
	for(int i=1;i<n;i++)
		scanf("%d%d",&e1,&e2),add_edge(e1,e2);
	
	memset(avail,1,sizeof(avail));
	pi a[2],b[2],f1,f2;
	int t1,t2;
	for(int dot=1;dot<=n;dot++){//枚举queen和king之间的点
		//printf("dot:%d\n",dot);
		a[0]=a[1]=b[0]=b[1]=inf;
		for(int e=first[dot];e!=-1;e=next[e]){
			avail[e]=avail[e^1]=0;
		//	printf("v[e]:%d\n",v[e]);
			t1=Calc(v[e],d[0],c[0],0);//printf("hei");
			t2=Calc(v[e],d[1],c[1],0);
			//printf("v[e]:%d t1:%d t2:%d\n",v[e],t1,t2);
			f1=mp(t1,v[e]);f2=mp(t2,v[e]);
			if(f1>a[0]) a[1]=a[0],a[0]=f1;else if(f1>a[1]) a[1]=f1;
			if(f2>b[0]) b[1]=b[0],b[0]=f2;else if(f2>b[1]) b[1]=f2;
			avail[e]=avail[e^1]=1;
		}
		if(a[0].second!=b[0].second){
			ans=max(ans,mp(mp(a[0].first+b[0].first,dot),mp(a[0],b[0])));
		}
		else{
			ans=max(ans,mp(mp(a[0].first+b[1].first,dot),mp(a[0],b[1])));
			ans=max(ans,mp(mp(a[1].first+b[0].first,dot),mp(a[1],b[0])));
		}
	}
	//找哪些点
	memset(choose,false,sizeof(choose));
	int dot=ans.first.second;
	for(int e=first[dot];e!=-1;e=next[e]){
		if(ans.second.first.second==v[e]){
			avail[e]=avail[e^1]=0;
			t1=Calc(v[e],d[0],c[0],1);
			avail[e]=avail[e^1]=1;
		}
		else if(ans.second.second.second==v[e]){
			avail[e]=avail[e^1]=0;
			t2=Calc(v[e],d[1],c[1],1);
			avail[e]=avail[e^1]=1;
		}
	}
	
	//输出
	if(ans.first.first<=0){
		puts("-1");return 0;
	}
	printf("%d\n",S-ans.first.first);
	for(int i=1;i<=n;i++)
		if(!choose[i]) printf("%d ",i);puts("");
	return 0;
}
