# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxm=50*50;
int m,n,q;
char s[50][50];
int p[maxm];
bool vis[maxm];
bool nec[2010];
bool ban[maxm];
vector<int> ans;
inline int pos(int x,int y) {return (x-1)*n+y;}
int first[maxm],next[maxm<<2],v[maxm<<2],edge=0;
void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

bool dfs(int x){
	if(ban[x]) return false;
	for(int e=first[x];e!=-1;e=next[e]){
		if(vis[v[e]]||ban[v[e]]) continue;vis[v[e]]=true;
		if(!p[v[e]]||dfs(p[v[e]])){
			p[v[e]]=x,p[x]=v[e];return true;
		}
	}
	return false;
}

int main(){
	char t;
	int sx,sy;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			while((t=getchar())&&t!='X'&&t!='O'&&t!='.');
			s[i][j]=t;
			if(s[i][j]=='.') s[i][j]='X',sx=i,sy=j;
		}
	memset(first,-1,sizeof(first));
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			//if(s[i][j]=='.') s[i][j]='X',sx=i,sy=j;
			if(i!=m&&s[i+1][j]!=s[i][j]) add_edge(pos(i,j),pos(i+1,j)),add_edge(pos(i+1,j),pos(i,j));//add_edge(printf("%d %d %d %d\n",i,j,i+1,j);
			if(j!=n&&s[i][j]!=s[i][j+1]) add_edge(pos(i,j),pos(i,j+1)),add_edge(pos(i,j+1),pos(i,j));//printf("%d %d %d %d\n",i,j,i,j+1);
		}
	memset(p,0,sizeof(p));memset(ban,0,sizeof(ban));
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(!p[pos(i,j)]) memset(vis,false,sizeof(vis)),dfs(pos(i,j));
	scanf("%d",&q);
	//for(int i=1;i<=m*n;i++)
	//	printf("p[%d]:%d\n",i,p[i]);
	for(int i=1;i<=2*q;i++){
		ban[pos(sx,sy)]=1;
		if(p[pos(sx,sy)]){
			//puts("fuck");
			int x=p[pos(sx,sy)];p[x]=p[pos(sx,sy)]=0;//printf("x:%d\n",x);
			memset(vis,false,sizeof(vis));
			nec[i]=!dfs(x);//printf("nec:%d\n",nec[i]);
		}
		else nec[i]=0;
		scanf("%d%d",&sx,&sy);
	}
	for(int i=1;i<=q;i++)
		if(nec[2*i-1]&&nec[2*i])
			ans.push_back(i);
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++)
		printf("%d\n",ans[i]);
	return 0;
}
