# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
typedef long long LL;
const int mod=1000000007;

struct Node{
	int s[6],pre;
	void u(int *a,int pr){
		for(int i=1;i<=5;i++) s[i]=a[i];pre=pr;
	}
};
int n,K;
int c[20];
int s[6];
int a[6];
LL dp[16][16][16][16][16][6];
queue<Node> q;
Node node;
int main(){
	scanf("%d",&K);
	n=0;
	memset(s,0,sizeof(s));
	for(int i=1;i<=K;i++){
		scanf("%d",&c[i]);n+=c[i];s[c[i]]++;
	}
	node.u(s,0);
	memset(dp,0,sizeof(dp));
	dp[s[5]][s[4]][s[3]][s[2]][s[1]][0]=1;
	q.push(node);
	Node nx;
	while(!q.empty()){
		Node x=q.front();q.pop();
		//printf("%d %d %d %d %d %d dp:%d\n",x.s[5],x.s[4],x.s[3],x.s[2],x.s[1],x.pre,dp[x.s[5]][x.s[4]][x.s[3]][x.s[2]][x.s[1]][x.pre]);
		for(int i=5;i>=1;i--){
			if(x.s[i]-(i==x.pre)>0){
				//memcpy(a,x.s,sizeof(x.s));
				for(int j=1;j<=5;j++) a[j]=x.s[j];
				a[i]--;
				a[i-1]++;
				//printf("to: %d %d %d %d %d %d add:%d\n",a[5],a[4],a[3],a[2],a[1],i-1,(x.s[i]-(i==x.pre))*dp[x.s[5]][x.s[4]][x.s[3]][x.s[2]][x.s[1]][x.pre]);
				nx.u(a,i-1);
				if(dp[a[5]][a[4]][a[3]][a[2]][a[1]][i-1]==0) q.push(nx);
				dp[a[5]][a[4]][a[3]][a[2]][a[1]][i-1]+=(x.s[i]-(i==x.pre))*dp[x.s[5]][x.s[4]][x.s[3]][x.s[2]][x.s[1]][x.pre];
				dp[a[5]][a[4]][a[3]][a[2]][a[1]][i-1]%=mod;
			}
		}
	}
	printf("%lld\n",dp[0][0][0][0][0][0]);
	return 0;
}
