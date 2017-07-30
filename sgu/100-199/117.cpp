# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
int n,m,k;
int a[maxn];
int prime[maxn],p_cnt=0,num[maxn];

bool check(int x){
	int tmp;
	for(int i=1;i<=p_cnt;i++){
		tmp=0;
		while(x%prime[i]==0) tmp++,x/=prime[i];
		if(tmp*m<num[i]) return false;
	}
	return true;
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=2;i*i<=k;i++){
		if(k%i==0){
			prime[++p_cnt]=i;num[p_cnt]=0;
			while(k%i==0) k/=i,num[p_cnt]++;
		}
	}
	if(k>1) prime[++p_cnt]=k,num[p_cnt]=1;
	
	int ans=0;
	for(int i=1;i<=n;i++)
		if(check(a[i])) ans++;
	printf("%d\n",ans);
	return 0;
}
