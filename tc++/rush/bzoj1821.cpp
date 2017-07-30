# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=1005;
int n,k;
int x[maxn],y[maxn],p[maxn];
int u[maxn*maxn/2],v[maxn*maxn/2],dist[maxn*maxn/2],edge=0,bh[maxn*maxn>>1];

bool cmp(int a,int b){
	return dist[a]<dist[b];
}

/*int find(int x){
	if(x==p[x]) return x;
	int xx=x;
	while(p[xx]!=xx){
		xx=p[xx];
	}
	int now;
	while(p[now]!=xx){
		int t=now;now=p[now];p[t]=xx;
	}
	return p[x];
}*/

int find(int x){
	if(p[x]==x) return x;
		return p[x]=find(p[x]);
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			u[edge]=i;v[edge]=j;
			dist[edge++]=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
		}
	for(int i=0;i<edge;i++) bh[i]=i;
	sort(bh,bh+edge,cmp);
	for(int i=1;i<=n;i++) p[i]=i;
	int kuai=n;double ans;
	for(int i=0;i<edge;i++){
		int e=bh[i];
		int px=find(u[e]),py=find(v[e]);
		if(px==py) continue;
		if(kuai==k) {
			ans=sqrt(dist[e]);break;
		}
		p[py]=px;kuai--;
	}
	printf("%.2lf\n",ans);
	return 0;
}
