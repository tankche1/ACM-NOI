# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=50010;
const int INF=~0U>>1;
struct cow{
	int a,b;
	bool operator < (const cow &rhs)const{
		return a+b<rhs.a+rhs.b;
	}
};
cow C[maxn];
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&C[i].a,&C[i].b);
	sort(C+1,C+n+1);
	int sum=0,ans=-INF;
	for(int i=1;i<=n;i++){
		ans=max(ans,sum-C[i].b);
		sum+=C[i].a;
	}
	printf("%d\n",ans);
	return 0;
}
