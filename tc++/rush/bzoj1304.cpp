# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxm=10010;
int c[maxm];
int m,n;int root;
int first[maxm],next[maxm<<1],v[maxm<<1],edge=0;
int f[maxm][3];

void add_edge(int x,int y){
	next[edge]=first[x];v[edge]=y;
	first[x]=edge++;
}
//0 全部搞定 1是有可能有白色没满足 2是有可能有黑色没满足 时的最小染色次数
void dfs(int x,int fa){
	int tmp0=0,tmp2=0,tmp1=0;
	if(x<=n){
		f[x][0]=1;f[x][1]=c[x]==0?0:1;f[x][2]=!f[x][1];
		//printf("x:%d f[0]:%d f[1]:%d f[2]:%d\n",x,f[x][0],f[x][1],f[x][2]);
		return;
	}
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa) continue;
		dfs(v[e],x);
		tmp0+=f[v[e]][0];
		tmp1+=min(f[v[e]][0],f[v[e]][1]);
		tmp2+=min(f[v[e]][0],f[v[e]][2]);
	}
	f[x][0]=min(min(tmp0,tmp1+1),tmp2+1);
	f[x][1]=min(tmp0,min(tmp1,tmp2+1));
	f[x][2]=min(tmp0,min(tmp2,tmp1+1));
	//printf("x:%d f[0]:%d f[1]:%d f[2]:%d\n",x,f[x][0],f[x][1],f[x][2]);
	return;
}

int main(){
	int x,y;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	memset(first,-1,sizeof(first));
	for(int i=1;i<m;i++){
		scanf("%d%d",&x,&y);
		add_edge(x,y);add_edge(y,x);
	}
	root=n+1;
	dfs(n+1,0);
	printf("%d\n",f[root][0]);
	return 0;
}
/*
7 4
1 0 1 0
7 5
7 6
5 1
5 2
3 6
4 6

5 1
1
5 4
4 3
3 2
2 1

6 3
1 1 0
6 1
6 5
5 4
5 3
4 2


*/
