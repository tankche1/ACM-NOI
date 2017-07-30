# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n,a,b,gcd;
const int maxn=50010;
int d[maxn];
bool prime[maxn];
int sumd[maxn];
typedef long long LL;
void pre(){
	memset(prime,true,sizeof(prime));
	for(int i=1;i<maxn;i++) prime[i]=d[i]=1;
	sumd[0]=0;sumd[1]=1;
	for(int i=2;i<maxn;i++){
		if(prime[i]){
			for(int j=i+i;j<maxn;j+=i){
				prime[j]=false;
				if(j%(i*i)==0) d[j]=0;
				d[j]=-d[j];
			}
			d[i]=-1;
		}
		sumd[i]=sumd[i-1]+d[i];//printf("%d\n",sumd[i]);
	}
}

int getNext(int c,int d){
	int L=1,R=min(a,b);
	while(L<=R){
		int M=(L+R)>>1;
		if(d/M>=c) L=M+1;
			else R=M-1;
	}
	return L-1;
}

int main(){
	pre();
	scanf("%d",&n);
	while(n--){
		LL ans=0;
		scanf("%d%d%d",&a,&b,&gcd);
		a/=gcd;b/=gcd;//printf("%d %d\n",a,b);
		for(int i=1;i<=min(a,b);i++){
			int j=min(a/(a/i),b/(b/i));
			//printf("i:%d j:%d %d\n",i,j,sumd[j]-sumd[i-1]);
			ans+=(LL)(a/i)*(b/i)*(sumd[j]-sumd[i-1]);
			i=j;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
// 1 39879 23345 223