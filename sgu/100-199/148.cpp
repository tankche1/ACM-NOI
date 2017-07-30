# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
# define lowbit(x) ((x)&(-x))
const int maxn=15010;
int n,W[maxn],L[maxn],P[maxn];
//vector<int> print;

struct FenwickTree{
	int C[maxn],n;
	void init(int nn){
		n=nn;memset(C,0,sizeof(C));
	}
	
	void add(int x,int val){
		while(x<=n){
			C[x]+=val;x+=lowbit(x);
		}
	}
	
	int sum(int x){
		int res=0;
		while(x>0){
			res+=C[x];x-=lowbit(x);
		}return res;
	}
	
};
FenwickTree fwt;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&W[i],&L[i],&P[i]);
	fwt.init(n);
	for(int i=1;i<=n;i++){
		int left=1,R=i-1;
		fwt.add(i,W[i]);
		while(left<=R){
			int M=(left+R)>>1;
			if((fwt.sum(i)-fwt.sum(M-1))>L[i]) left=M+1;
				else R=M-1;
		}
		int from=left-1;
		if(from)
			P[from]-=P[i];
	}
	int cost=INF,ans,sum=0;
	for(int i=n;i>=1;i--){
		//printf("p[%d]:%d\n",i,P[i]);
		sum+=P[i];if(sum<cost) cost=sum,ans=i;
	}sum=0;
	for(int i=ans;i<=n;i++){
		sum+=W[i];
		if(sum>L[i]) continue;
		else printf("%d\n",i);
	}
	return 0;
}
