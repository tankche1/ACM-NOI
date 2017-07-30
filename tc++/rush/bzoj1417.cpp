# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=35;
const int maxs=100010;
const int mod=99997;
const int seed=37;
typedef unsigned int ull;
int n,m;
int p[maxn];
double dp[maxs];
	
int find(int x){if(x==p[x]) return x;return p[x]=find(p[x]);}

struct state{
	int len;
	int a[maxn];
	state(){len=0;}
	void sorted(){
		sort(a+1,a+len+1);
	}
	bool operator == (const state &rhs)const{
		if(len!=rhs.len) return false;
		for(int i=1;i<=len;i++)
			if(a[i]!=rhs.a[i]) return false;
		return true;
	}
};
state Map[maxs];

int getCode(state now){
		int res=0;
		for(int i=1;i<=now.len;i++){
			res=res*seed+now.a[i];if(res>=mod) res%=mod;
		}
		while(Map[res].len>0&&(!(Map[res]==now))) {res++;if(res>=mod) res-=mod;}
		if(Map[res].len==0) Map[res]=now;
		return res;
}
bool vis[maxs];
int total;

double dfs(state now){
	int key=getCode(now);//printf("key:%d \n",key);
	if(vis[key]) return dp[key];
	vis[key]=true;
	if(now.len==1) return dp[key]=0;
	//puts("fuck");
	double &res=dp[key];res=0;
	int same=0;
	for(int i=1;i<=now.len;i++){
		for(int j=i;j<=now.len;j++){
			if(i==j) same+=now.a[i]*(now.a[i]-1)/2;
			else{
			state go=now;
			go.a[i]+=go.a[j];
			swap(go.a[j],go.a[go.len]);go.len--;go.sorted();
			res+=(double)(now.a[i]*now.a[j])/(total*1.0)*(dfs(go)+1);
			}
		}
	}
	double sa=same/(total*1.0);
	//	for(int i=1;i<=now.len;i++) printf("%d ",now.a[i]);
	//		printf("\n%.6lf\n",res);
	return res=(double)(res+sa)/(1-sa);
}

int main(){
	int a,b;
	scanf("%d%d",&n,&m);total=n*(n-1)/2;
	for(int i=1;i<=n;i++) p[i]=i;
		int kuai=n;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		int px=find(a),py=find(b);
		if(px!=py) p[py]=px,kuai--;
	}
	state first;
	for(int i=1;i<=n;i++)
		if(!vis[find(i)]){
			vis[find(i)]=1;
			int tot=1;
			for(int j=i+1;j<=n;j++)
				if(find(j)==p[i]) tot++;
			first.a[++first.len]=tot;
		}
	first.sorted();
	//	printf("len:%d\n",first.len);
	//memset(dp,-1,sizeof(dp));//printf("%d\n",dp[1]);
	memset(vis,false,sizeof(vis));
	printf("%.6lf\n",dfs(first));
	return 0;
}
