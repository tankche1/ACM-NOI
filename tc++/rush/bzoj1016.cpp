# include<stdio.h>
# include<string.h>
# include<algorithm>
# define FUCK printf("fuck\n");
using namespace std;
const int maxn=105;
const int maxm=1005;
const int mod=31011;

struct Edge{
	int from,to,dist;
	const bool operator < (const Edge &rhs)const{
		return dist<rhs.dist;
	}
};
Edge edges[maxm];
int n,m;

int find(int *p,int x){
	int fa=x;
	while(p[fa]!=fa) fa=p[fa];
	int pa=x,y;
	while(p[pa]!=pa){
		y=p[pa];
		p[pa]=fa;
		pa=y;
	}
	return p[x];
}

bool p_union(int *p,int x,int y){
	int px=find(p,x),py=find(p,y);
	if(px==py) return false;
	p[px]=py;
	return true;
}

int end[maxn],vis[maxm],pp[maxn];
int p[maxn];
int num;
int dfs(int now,int first,int end){
	if(now==end+1){
		for(int i=1;i<=n;i++) pp[i]=p[i];
			int cnt=0;
		//for(int i=now;i<=end;i++) printf("vis[%d]:%d\n",i,vis[i]);
		for(int i=first;i<=end;i++)
			if(vis[i]){
			//	printf("i:%d ",i);
				if(!p_union(pp,edges[i].from,edges[i].to)) return 0;
				cnt++;
			}
		//for(int i=1;i<=n;i++) printf("pp[%d]:%d\n",i,pp[i]);
		//printf("cnd:%d num:%d\n",cnt,num);
		return cnt==num?1:0;
	}
	vis[now]=0;
	int ans=dfs(now+1,first,end);
	vis[now]=1;
	ans+=dfs(now+1,first,end);
	return ans;
}


int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&edges[i].from,&edges[i].to,&edges[i].dist);
	sort(edges+1,edges+m+1);
	for(int i=1;i<=n;i++) p[i]=i;
	int ans=1;
	for(int i=1;i<=m;i++){
		int L=i,R;
		for(int j=1;j<=n;j++) end[j]=p[j];
		//for(int j=1;j<=n;j++) printf("p[%d]:%d\n",j,p[j]);
		num=0;
		for(R=i;R<=m;R++){
			if(edges[R].dist!=edges[i].dist) {R--;break;}
			if(p_union(end,edges[R].from,edges[R].to)==true) num++;
		}memset(vis,false,sizeof(vis));
		//printf("num:%d\n",num);
	//	for(int j=1;j<=n;j++) printf("end[%d]:%d\n",j,end[j]);
		ans=(ans*dfs(L,L,R))%mod;//printf("ans:%d\n",ans);
		for(int j=1;j<=n;j++) p[j]=end[j];
		i=R;
	}
	for(int i=1;i<n;i++) if(find(p,i)!=find(p,i+1)) {ans=0;}
	printf("%d\n",ans);
	return 0;
}
