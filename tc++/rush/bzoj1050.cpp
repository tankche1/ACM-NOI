# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxm=5010;
const int maxn=510;
struct Edge{
	int from,to,dist;
	bool operator < (const Edge &rhs)const{
		return dist<rhs.dist;
	}
};
Edge edges[maxm];
int p[maxn];
int find(int x){
	if(x==p[x]) return x;
		return p[x]=find(p[x]);
}

void Union(int x,int y){
	int px=find(x),py=find(y);
	p[px]=py;
}

int gcd(int a,int b){
	if(b==0) return a;
	return gcd(b,a%b);
}

int n,m;
int main(){
	scanf("%d%d",&n,&m);
	int S,T;
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&edges[i].from,&edges[i].to,&edges[i].dist);
	}
	scanf("%d%d",&S,&T);
	sort(edges,edges+m);
	int ans_max=-1,ans_min;
	for(int l=0;l<m;l++){
		for(int i=1;i<=n;i++) p[i]=i;
		for(int r=l;r<m;r++){
			Union(edges[r].from,edges[r].to);
			if(find(S)==find(T)){
				if(ans_max==-1||(edges[r].dist*ans_min)<(edges[l].dist*ans_max)){
					ans_max=edges[r].dist;
					ans_min=edges[l].dist;
				}
				break;
			}
		}
	}
	if(ans_max==-1) puts("IMPOSSIBLE");
	else{
		int g=gcd(ans_max,ans_min);
		if(ans_max%ans_min==0) printf("%d\n",ans_max/ans_min);
			else
		printf("%d/%d\n",ans_max/g,ans_min/g);
	}
	return 0;
}
