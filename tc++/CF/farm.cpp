#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=10010;
int p[maxn],l[maxn],r[maxn];
int n,m;

int find(int x){
	if(p[x]==x) return x;
	int fa=p[x];
	p[x]=find(p[x]);
	l[x]=l[x]+l[fa];r[x]=r[x]+r[fa];
	return p[x];
}

int main(){
	int op,a,b,c;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		p[i]=i,l[i]=0,r[i]=0;
	bool ok;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&op,&a,&b);
		if(op<3) scanf("%d",&c);
		if(op==1){
			int px=find(a),py=find(b);
			p[px]=py;
			l[px]=l[b]+c-r[a];
			if(px==py){
				if(l[px]>r[px])
				{ok=false;break;}
			}
			else{
				r[px]=INF;
			}
		}
		else if(op==2){
			int px=find(a),py=find(b);
			p[px]=py;r[px]=r[b]+c-l[a];
			if(px==py){
				if(r[px]<l[px])
				{ok=false;break;}
			}
			else{
				l[px]=-INF;
			}
		}
		else{
			int px=find(a),py=find(b);
			p[px]=py;
			l[px]=l[b]-r[a];r[px]=r[b]-l[a];
			if(px==py)
				if(r[px]<l[px])
				{ok=false;break;}
		}
	}
	if(ok) puts("Yes");
		else puts("No");
	return 0;
}
