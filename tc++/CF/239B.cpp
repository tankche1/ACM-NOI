#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1010;
const int mod=1000000007;
typedef long long LL;
int to[maxn];
LL f[maxn],g[maxn];
int n;
int stack[maxn],top=-1;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&to[i]);
	f[1]=0;
	g[1]=1;
	for(int i=2;i<=n;i++){
		f[i]=g[i-1]+1;f[i]%=mod;
		if(to[i]==i) g[i]=f[i]+1,g[i]%=mod;
		else{
			int x=i;LL ans;top=-1;
			while(to[x]!=x){
				stack[++top]=x;
				x=to[x];
			}
			stack[++top]=x;
			ans=f[i]+top+1;
			for(int j=0;j<top;j++) ans+=f[stack[j]];
				for(int j=1;j<=top;j++) ans-=g[stack[j]];
			ans%=mod;
			g[i]=(ans+mod)%mod;
		}
		//printf("f[%d]:%lld g:%lld\n",i,f[i],g[i]);
	}
	printf("%lld\n",(g[n]+1)%mod);
	return 0;
}
