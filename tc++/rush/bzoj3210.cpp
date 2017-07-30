#include<stdio.h>
#include<string.h>
# include<math.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
int n;
int x[maxn],y[maxn];
int X,Y;
double x2[maxn],y2[maxn];
int dx[8]={-1,-1,-1,0,0,1,1,1},dy[8]={-1,0,1,-1,1,-1,0,1};
	
LL calc(int X,int Y){
	LL ans=0;
	for(int i=1;i<=n;i++)
		ans+=max(abs(X-x[i]),abs(Y-y[i]));
	return ans;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&x[i],&y[i]),x2[i]=(x[i]+y[i])/2.0,y2[i]=(x[i]-y[i])/2.0;
	sort(x2,x2+n+1);sort(y2,y2+n+1);
	int mid=(n+1)/2;
	X=(int)(x2[mid]+y2[mid]);
	Y=(int)(x2[mid]-y2[mid]);
	long long ans=calc(X,Y);
	for(int i=0;i<8;i++){
		ans=min(ans,calc(X+dx[i],Y+dy[i]));
	}
	printf("%lld\n",ans);
	return 0;
}
