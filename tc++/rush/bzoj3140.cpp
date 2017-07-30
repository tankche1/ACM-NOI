#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=5010;
const int INF=~0U>>1;
int a,b,c;
bool choose[20];

struct Point{
	int x,y,z;
	Point(){}
	Point(int x,int y,int z):x(x),y(y),z(z) {
		if(b<=a&&b<=c)
			swap(x,y);
		else if(c<=a&&c<=b)
			swap(y,z);
	}
};
Point P[maxn];
int num;
int ans=INF;
int first[maxn],next[maxn<<1],v[maxn<<1],edge;
bool vis[maxn];int left[maxn];
int g[maxn];

void add_edge(int a,int b){
	//printf("a:%d b:%d\n",a,b);
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

bool match(int x){
	if(vis[x]) return false;
	vis[x]=1;
	//printf("x:%d\n",x);
	for(int e=first[x];e!=-1;e=next[e]){//printf("v:%d ",v[e]);
		if(left[v[e]]==-1||match(left[v[e]]))
		{left[v[e]]=x;return true;}
	}
	return false;
}

void dfs(int step){
	if(step>a){
		for(int i=1;i<=b;i++) first[i]=-1;edge=0;
		int res=0;
		for(int i=1;i<=a;i++) res+=choose[i];
		memset(g,0,sizeof(g));
		for(int i=0;i<num;i++)
			if(!choose[P[i].x]) if(!g[(P[i].y-1)*c+P[i].z]) g[(P[i].y-1)*c+P[i].z]=1,add_edge(P[i].y,P[i].z);
				
		for(int i=1;i<=c;i++) left[i]=-1;
		for(int i=1;i<=b;i++){
			for(int j=1;j<=b;j++) vis[j]=0;
			res+=match(i);
		}
		ans=min(ans,res);
		//printf("res:%d\n",res);
		//puts("");puts("");
	}
	else{
		for(int i=0;i<2;i++)
			choose[step]=i,dfs(step+1);
	}
	return;
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int tcase,x;
	scanf("%d",&tcase);
	while(tcase--){
		num=0;
		scanf("%d%d%d",&a,&b,&c);
		for(int i=1;i<=a;i++)
			for(int j=1;j<=b;j++)
				for(int k=1;k<=c;k++){
					scanf("%d",&x);
					if(x) P[num++]=Point(i,j,k);
				}
		if(b<=a&&b<=c)
			swap(a,b);
		else if(c<=a&&c<=b)
			swap(a,c);
		ans=INF;
		dfs(1);
		printf("%d\n",ans);
	}
	return 0;
}
