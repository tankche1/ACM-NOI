# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=55;

vector<int> G[maxn];
int n,A,B;
char s[maxn][maxn];
int dfn[maxn],cnt,sccno[maxn],sccno_cnt[maxn];
bool g[maxn][maxn];
int value[maxn],Min[maxn],Max[maxn];
int in[maxn],out[maxn];

void dfs(int i,int col){
	dfn[i]=col;
	sccno[i]=col;sccno_cnt[col]++;
	for(int j=0;j<G[i].size();j++)
		if(!dfn[G[i][j]]) dfs(G[i][j],col);
	return;
}

int main(){
	scanf("%d%d%d",&n,&A,&B);
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
			if(i!=j&&s[i][j]=='=') {G[i].push_back(j);G[j].push_back(i);}
	}
	memset(dfn,0,sizeof(dfn));
	cnt=0;
	for(int i=1;i<=n;i++)
		if(!dfn[i]) dfs(i,++cnt);
	memset(g,false,sizeof(g));
	memset(in,false,sizeof(in));
	memset(out,false,sizeof(out));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(s[i][j]=='+') {g[sccno[i]][sccno[j]]=true;}//printf("%d %d\n",i,j);}
		}
	for(int i=1;i<=cnt;i++)
		for(int j=1;j<=cnt;j++){
			if(g[i][j]) out[i]=true,in[j]=true;
	}
	/*for(int i=1;i<=n;i++){
		printf("sccno[%d]:%d\n",i,sccno[i]);
	}*/
	memset(value,-1,sizeof(value));
	for(int i=1;i<=cnt;i++){
		if(out[i]&&in[i]){
			value[i]=2;Min[i]=Max[i]=2;
			for(int j=1;j<=cnt;j++)
				if(g[i][j]) value[j]=1,Min[j]=Max[j]=1;
					else if(g[j][i]) value[j]=3,Min[j]=Max[j]=3;
		}
	}
	for(int i=1;i<=cnt;i++) if(value[i]==-1){
		Min[i]=out[i]==1?2:1;
		Max[i]=in[i]==1?2:3;
	}
	int c1=0,c2=0,c3=0;
	for(int i=1;i<=n;i++){
		if(i==A||i==B) continue;
		for(int j=i+1;j<=n;j++){
			if(j==A||j==B||i==j) continue;
			if(value[sccno[A]]!=-1&&value[sccno[B]]!=-1&&value[sccno[i]]!=-1&&value[sccno[j]]!=-1)
				c2+=(value[sccno[A]]+value[sccno[B]]==value[sccno[i]]+value[sccno[j]]);
			if(Max[sccno[i]]+Max[sccno[j]]<Min[sccno[A]]+Min[sccno[B]])
			{c1++;}//printf("i:%d j:%d Max[i]:%d Max[j]:%d\n",i,j,Max[sccno[i]],Max[sccno[j]]);}
			if(Min[sccno[i]]+Min[sccno[j]]>Max[sccno[A]]+Max[sccno[B]])
				c3++;
		}
	}
	printf("%d %d %d\n",c1,c2,c3);
	return 0;
}
/*
5 2 3
?++++
-?+?=
--?=?
-?=??
-=???
*/
