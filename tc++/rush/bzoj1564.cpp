# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=75;
int n,K;
int f[maxn][maxn][maxn];
int sum[maxn];

struct node{
	int data,val,cost;
}tree[maxn];

int dfs(int l,int r,int k){//l到r 最大的祖先节点是k
	if(l>r) return 0;
	if(f[l][r][k]!=-1) return f[l][r][k];
	int &res=f[l][r][k];res=INF;
	for(int x=l;x<=r;x++){
		if(tree[x].val>tree[k].val)
			res=min(res,dfs(l,x-1,x)+dfs(x+1,r,x)+sum[r]-sum[l-1]);
		res=min(res,dfs(l,x-1,k)+dfs(x+1,r,k)+sum[r]-sum[l-1]+K);
	}
	//printf("f[%d][%d][%d]:%d\n",l,r,k,res);
	return res;
}

bool cmp(node A,node B){
	return A.data<B.data;
}

int main(){
	freopen("treapmod.in","r",stdin);
	freopen("treapmod.out","w",stdout);
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++)
		scanf("%d",&tree[i].data);
	for(int i=1;i<=n;i++)
		scanf("%d",&tree[i].val);
	for(int i=1;i<=n;i++)
		scanf("%d",&tree[i].cost);
	sort(tree+1,tree+n+1,cmp);
	sum[0]=0;
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+tree[i].cost;
	memset(f,-1,sizeof(f));tree[0].val=-1000;
	printf("%d\n",dfs(1,n,0));
	return 0;
}
