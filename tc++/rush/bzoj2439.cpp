#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
const LL INF=(LL)1<<60;
int n;
int A[maxn],d[maxn];LL sum1[maxn],sum2[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	d[1]=0;
	for(int i=2;i<=n;i++) d[i]=A[i]-A[i-1];
	sum1[1]=0;
	for(int i=2;i<=n;i++)
		sum1[i]=sum1[i-1]+(d[i]>0?0:1-d[i]);
	sum2[1]=0;
	for(int i=2;i<=n;i++)
		sum2[i]=sum2[i-1]+(d[i]<0?0:d[i]+1);
	//for(int i=1;i<=n;i++)
	//	printf("i:%d sum1:%lld sum2:%lld\n",i,sum1[i],sum2[i]);
	LL res=INF;
	for(int y=3;y<=n-2;y++){
		int L=2,R=y-1;
		while(L<=R){
			int M=(L+R)>>1;
			if(sum1[M]>=sum2[y]-sum2[M]) R=M-1;
				else L=M+1;
		}
		LL ans=INF;
		if(R>=2) ans=min(ans,max(sum1[R],sum2[y]-sum2[R]));
		if(R!=y-1) ans=min(ans,max(sum1[R+1],sum2[y]-sum2[R+1]));
		LL tt=ans;
		
		L=y+1,R=n-1;
		while(L<=R){
			int M=(L+R)>>1;
			if(sum1[M]-sum1[y]>=sum2[n]-sum2[M]) R=M-1;
			else L=M+1;
		}
		ans=INF;//printf("R:%d\n",R);
		if(R>=y+1) ans=min(ans,max(sum1[R]-sum1[y],sum2[n]-sum2[R]));
		if(R!=n-1) ans=min(ans,max(sum1[R+1]-sum1[y],sum2[n]-sum2[R+1]));
		res=min(res,tt+ans);
		//printf("y:%d tt+ans:%lld tt:%lld ans:%lld\n",y,tt+ans,tt,ans);
	}
	printf("%lld\n",res);
	return 0;
}
