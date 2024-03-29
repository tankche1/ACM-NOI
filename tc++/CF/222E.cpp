#include<stdio.h>
#include<string.h>
# include<math.h>
# include<stack>
#include<algorithm>
using namespace std;
typedef long long LL;
typedef pair<int,int> pi;
const int maxn=200010;
const int INF=~0U>>1;
int n;
LL s;
pi maker[maxn],h[maxn];
LL px[maxn],py[maxn];
int k[maxn];LL b[maxn];
int q[maxn];

int main(){
	scanf("%d%lld",&n,&s);
	for(int i=0;i<n;i++)
		scanf("%d%d",&maker[i].second,&maker[i].first);
	sort(maker,maker+n);
	int m=1;h[0]=maker[0];
	for(int i=1;i<n;i++){
		if(maker[i].second>h[m-1].second){
			h[m++]=maker[i];
		}
	}
	n=m;int tot=1;px[tot-1]=py[tot-1]=0;k[0]=h[0].second;b[0]=0;
	q[tot-1]=0;//puts(" shit");
	//for(int i=0;i<n;i++) printf("%d %d\n",h[i].second,h[i].first);
	for(int i=1;i<n;i++){
		int pos=upper_bound(py,py+tot,h[i].first)-py;pos--;
		LL nx,ny;
		k[i]=h[i].second;//pos=q[pos];
		nx=ceil((h[i].first-b[q[pos]])/(k[q[pos]]*1.0));ny=nx*k[q[pos]]+b[q[pos]];
		if(pos+1<tot&&(nx>=px[pos+1])) nx=px[pos+1],ny=nx*k[q[pos+1]]+b[q[pos+1]];
		b[i]=ny-h[i].first-nx*k[i];
		while(tot>0&&k[i]*px[tot-1]+b[i]>=py[tot-1]){
			tot--;
		}
		q[tot]=i;px[tot]=ceil((b[i]-b[q[tot-1]])/((k[q[tot-1]]-k[i])*1.0));py[tot]=px[tot]*k[i]+b[i];tot++;
		//printf("px:%lld py:%lld k:%d b:%lld\n",px[tot-1],py[tot-1],k[i],b[i]);
	}
	int pos=upper_bound(py,py+tot,s)-py;pos--;//pos=q[pos];
	LL ans=ceil((s-b[q[pos]])/(k[q[pos]]*1.0));
	if(pos+1<tot) ans=min(ans,px[pos+1]);
	printf("%lld\n",ans);
	return 0;
}
