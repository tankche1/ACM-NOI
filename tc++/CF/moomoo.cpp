#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=110;
const int maxb=25;
const int maxv=100010;
int dp[maxv];
int n,b,v[maxb];
int a[maxn];

void update(int &x,int y){
	if(x==-1) x=y;
	else x=min(x,y);
}

int main(){
	freopen("mooomoo.in","r",stdin);
	freopen("mooomoo.out","w",stdout);
	scanf("%d%d",&n,&b);
	for(int i=1;i<=b;i++)
		scanf("%d",&v[i]);
	int maxa=0;
	a[0]=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),maxa=max(maxa,a[i]);
	memset(dp,-1,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<=b;i++){
		for(int j=v[i];j<=maxa;j++)
			if(dp[j-v[i]]!=-1)
			update(dp[j],dp[j-v[i]]+1);
	}
	int ans=0;bool ok=true;
	for(int i=1;i<=n;i++){
		int now=a[i]-max(a[i-1]-1,0);
		ans+=dp[now];if(dp[now]==-1) {ok=false;break;}
	}
	if(!ok) puts("-1");
		else printf("%d\n",ans);
	return 0;
}
