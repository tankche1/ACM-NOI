# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
LL inf=1LL<<60;
int n,k;
LL A[maxn];

struct tank{
	LL val;int pos;
	tank (LL val=0,int pos=0) :val(val),pos(pos) {}
	bool operator < (const tank &rhs)const{
		return val>rhs.val;
	}
};
priority_queue<tank> q;
int L[maxn],R[maxn];
bool use[maxn];

int main(){
	int a,lasta;
	scanf("%d%d",&n,&k);
	scanf("%d",&lasta);
	for(int i=1;i<n;i++){
		scanf("%d",&a);
		A[i]=a-lasta;
		L[i]=i-1;R[i]=i+1;
		lasta=a;
		q.push(tank(A[i],i));
	}
	LL ans=0;A[0]=A[n]=inf;
	for(int i=1;i<=k;i++){
		int x;
		while(1){x=q.top().pos;//printf("pos:%d val:%lld\n",x,q.top().val);
			q.pop();if(!use[x]) break;}
		ans+=A[x];
	//	printf("%lld x:%d\n",ans,x);
		use[L[x]]=1;use[R[x]]=1;A[x]=A[L[x]]-A[x]+A[R[x]];
		R[L[L[x]]]=x;L[R[R[x]]]=x;
		L[x]=L[L[x]];R[x]=R[R[x]];
		q.push(tank(A[x],x));
	}
	printf("%lld\n",ans);
	return 0;
}
