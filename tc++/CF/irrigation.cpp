#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=2010;
const int maxm=maxn*maxn/2;
int n,C,m=0;
int x[maxn],y[maxn];
int u[maxm],v[maxm],w[maxm],bh[maxm];
int p[maxn];
int find(int x){
	if(x==p[x]) return x;return p[x]=find(p[x]);
}

bool cmp(int a,int b) {return w[a]<w[b];}

int main(){
	freopen("irrigation.in","r",stdin);
	freopen("irrigation.out","w",stdout);
	scanf("%d%d",&n,&C);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x[i],&y[i]);
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			u[++m]=i;v[m]=j;w[m]=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);if(w[m]<C) m--;
		}
	for(int i=1;i<=m;i++) bh[i]=i;
	for(int i=1;i<=n;i++) p[i]=i;
	sort(bh+1,bh+m+1,cmp);
	int ans=0,now=n;
	for(int i=1;i<=m;i++){
		int e=bh[i];
		int px=find(u[e]),py=find(v[e]);
		if(px!=py){
			p[px]=py;ans+=w[e];now--;
		}
	}
	if(now>1) puts("-1");
		else printf("%d\n",ans);
	return 0;
}
