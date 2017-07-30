# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=110;
int w,n,m;
int p[maxn],sum[maxn];

void find(int x){
	if(x==p[x]) return;
	int cc=sum[x];
	find(p[x]);
	sum[x]=sum[p[x]]+cc;
	p[x]=p[p[x]];
	return;
}

int main(){
	scanf("%d",&w);
	for(int ww=1;ww<=w;ww++){
		scanf("%d%d",&n,&m);
		for(int i=0;i<=n;i++) p[i]=i,sum[i]=0;
		bool ok=true;
		for(int i=1;i<=m;i++){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			if(!ok) continue;
			a--;
			find(a);find(b);
			int px=p[a],py=p[b];
			if(px==py){
				if(sum[b]-sum[a]!=c)
					ok=false;
			}
			else{
				p[py]=px;sum[py]=-(sum[b]-c-sum[a]);
			}
		}
		if(ok) puts("true");
			else puts("false");
	}
	return 0;
}
