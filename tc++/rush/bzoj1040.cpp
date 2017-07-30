# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=1000010;

struct StateTree{
	LL A[2];
	
	StateTree(int val=0){//不赋值的话为0
		A[0]=0;A[1]=val;
	}
	
	void Renew(StateTree &x){
		A[0]+=max(x.A[0],x.A[1]);
		A[1]+=x.A[0];
	}
	
};
StateTree dp[maxn];

struct StateCircle{
	LL A[2][2];
	StateCircle(StateTree &x){
		memset(A,0,sizeof(A));
		A[0][0]=x.A[0];
		A[1][1]=x.A[1];
	}
	
	void Renew(StateTree &x){
		LL ans[2][2];
		for(int i=0;i<2;i++){
			ans[i][0]=max(A[i][0],A[i][1])+x.A[0];
			ans[i][1]=x.A[1]+A[i][0];
		}
		memcpy(A,ans,sizeof(A));
	}
};

int n,next[maxn],fight[maxn],in[maxn];
int main(){
	scanf("%d",&n);
	memset(in,0,sizeof(in));
	for(int i=0;i<n;i++){
		scanf("%d%d",&fight[i],&next[i]);in[--next[i]]++;
		dp[i]=StateTree(fight[i]);
	}
	queue<int> Q;
	for(int i=0;i<n;i++) 
		if(!in[i]) Q.push(i);
	while(!Q.empty()){
		int i=Q.front();Q.pop();
		dp[next[i]].Renew(dp[i]);
		if(--in[next[i]]==0) Q.push(next[i]);
	}
	LL ans=0;
	for(int i=0;i<n;i++)
		if(in[i]){
			in[i]=0;int t=i;
			StateCircle x=StateCircle(dp[t]);
			t=next[t];
			while(t!=i){
				x.Renew(dp[t]);
				in[t]=0;
				t=next[t];
			}
			ans+=max(x.A[0][0],max(x.A[0][1],x.A[1][0]));
		}
		printf("%lld\n",ans);
	return 0;
}
