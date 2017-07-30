# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;

struct edge{
	int from,to,score;
	bool operator<(edge rhs)const{
		return score<rhs.score;
	}
};
edge edges[90010];
int p[310];
int n,m;

int find(int x){
	if(x==p[x]) return x;
		return p[x]=find(p[x]);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&edges[i].from,&edges[i].to,&edges[i].score);
	sort(edges+1,edges+m+1);
	for(int i=1;i<=n;i++) p[i]=i;
	int cnt=n;
	for(int i=1;i<=m;i++){
		int px=find(edges[i].from),py=find(edges[i].to);
		if(px!=py){
			p[px]=py;
			if(--cnt==1) {
				printf("%d %d\n",n-1,edges[i].score);break;
			}
		}
	}
	return 0;
}
