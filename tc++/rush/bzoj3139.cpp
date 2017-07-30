#include<stdio.h>
#include<string.h>
# include<map>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=15;
const int seed=29;
const LL mod=1000000007;
LL seeds[maxn];
map<LL,LL> hash[maxn];
int n;
int score[maxn];

struct state{
	int A[maxn];
	state() {}
	LL getcode(){
		LL res=0;
		for(int i=1;i<=A[0];i++) res+=seeds[i]*A[i];
		return res;
	}
	void _sort(){sort(A+1,A+A[0]+1);}
};

LL dfs(int step,state now){
	LL *res;LL B;res=&B;
	//for(int i=0;i<=now.A[0];i++) printf("A[%d]:%d ",i,now.A[i]);printf("step:%d \n",step);//puts("");
	if(step==2){
		LL key=now.getcode();
		if(hash[now.A[0]].count(key)) {//printf("%d\n",key);
			return hash[now.A[0]][key];}
		res=&hash[now.A[0]][key];
	}
	*res=0;
	if(now.A[0]==1){return *res=0;}
	if(step>now.A[0]){
		if(now.A[1]!=0) return *res=0;
		step=2;
		now.A[1]=now.A[now.A[0]];now.A[0]--;
		now._sort();
		return *res=dfs(step,now);
	}
	if((now.A[0]-step+1)*3<now.A[1]) return *res=0;
	
	if(now.A[1]&&now.A[step]){
		now.A[1]--;now.A[step]--;
		*res+=dfs(step+1,now);
		now.A[1]++;now.A[step]++;
	}
	
	if(now.A[1]>=3){
		now.A[1]-=3;
		*res+=dfs(step+1,now);
		now.A[1]+=3;
	}
	
	if(now.A[step]>=3){
		now.A[step]-=3;
		*res+=dfs(step+1,now);
		now.A[step]+=3;
	}
	(*res)%=mod;
	return *res;
}

int main(){
	seeds[1]=1;
	for(int i=2;i<=10;i++) seeds[i]=seeds[i-1]*seed;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&score[i]);
	sort(score+1,score+n+1);
	state start;
	start.A[0]=n;for(int i=1;i<=n;i++) start.A[i]=score[i];
	hash[1][0]=1;
	printf("%lld\n",dfs(2,start));
	return 0;
}
