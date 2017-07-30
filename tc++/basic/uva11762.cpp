# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000010;
const int max_n=1000009;//1000003是质数 一开始取1000000 极限数据会爆 因为prime[prime_cnt+1]=0 < 1000000
double f[maxn];
bool vis[maxn];
int prime[maxn],prime_cnt=0;

void init(){
	memset(vis,false,sizeof(vis));
	prime_cnt=0;
	for(int i=2;i<=max_n;i++){
	//	if(i%1000==0) printf("%d\n",i);
		if(!vis[i]){
			prime[prime_cnt++]=i;
			 if(i <= max_n/i)//防止溢出。。。
			for(int j=i*i;j<=max_n;j+=i)
				vis[j]=true;
		}
	}
	//prime[prime_cnt++]=~0U>>1;
//	for(int i=1;i<=prime_cnt;i++)
	//	printf("%d\n",prime[i]);
	//printf("%d\n",prime[prime_cnt-2]);
	memset(vis,false,sizeof(vis));
}

double dp(int x){
	//printf("x:%d\n",x);
	if(vis[x]) return f[x];
	vis[x]=true;
	int g=0,p=0;
	double sum=0.0;
	for(int i=0;prime[i]<=x;i++){
		//printf("c %d %d ",prime[i],x);
		//if(x==32)
		//printf("prime[i]:%d\n",prime[i]);
		if(x%prime[i]==0){
			p++;//printf("a");
			sum+=dp(x/prime[i]);//printf("b");
		}g++;
	}
	 f[x]=(g+sum)/(p*1.0);
	//printf("f[%d]:%.5f\n",x,f[x]);
	return f[x];
}

int main(){
	//freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	init();
	int T,n;
	scanf("%d",&T);
	f[1]=0.0;vis[1]=true;
	for(int kase=1;kase<=T;kase++) {
		scanf("%d",&n);
		printf("Case %d: %.10f\n",kase,dp(n));
	}
	return 0;
}
