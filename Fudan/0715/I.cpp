# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
int INF=~0U>>1;
int n;
pair<int,int> p[100010];
int bmax[100010];
int main(){
	int Tcase,t=0;
	scanf("%d",&Tcase);
	while(Tcase--){
		int ans=INF;
		printf("Case %d: ",++t);
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&p[i].first,&p[i].second);
		sort(p+1,p+n+1);bmax[n+1]=0;
		for(int i=n;i>=1;i--) bmax[i]=max(bmax[i+1],p[i].second);
		for(int i=1;i<=n;i++){
			ans=min(ans,p[i].first+bmax[i+1]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
