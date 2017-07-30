# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=2000000000;
const int maxs=60;
typedef long long LL;
LL n;
bool vis[maxs];
int prime[maxs];

void get_prime(int m){
	memset(vis,false,sizeof(vis));prime[0]=0;
	for(int i=2;i<=m;i++){
		if(!vis[i]){
			prime[++prime[0]]=i;
			for(int j=i*i;j<=m;j+=i)
				vis[j]=true;
		}
	}
	//printf("%d\n",prime[0]);
}

inline LL fastpow(LL a,LL x){
	if(x==0) return 1;
	LL half=fastpow(a,x/2);
	if(x%2==1) return half*half*a;
		else return half*half;
}
LL ans,Max=0;

void dfs(LL num,LL lastnum,LL now,LL cnt){
	//printf("num:%lld lastnum:%lld now:%lld cnt:%lld\n",num,lastnum,now,cnt);
	if(num>prime[0]||lastnum==0){
		if(cnt>Max||(cnt==Max&&ans>now)) {Max=cnt,ans=now;}
		return;
	}
	//LL shit=fastpow(prime[num],lastnum);
	LL shit=1;
	for(LL i=0;i<=lastnum;i++){
		if(shit*now<=n){
			dfs(num+1,i,shit*now,cnt*(i+1));
		}else break;shit*=prime[num];
	}
}

int main(){
	scanf("%lld",&n);
	get_prime(40);
	dfs(1,25,1,1);
	printf("%lld\n",ans);
	//printf("%lld\n",Max);
	return 0;
}
