# include<stdio.h>
# include<vector>
# include<stack>
# include<math.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=110;
const double eps=1e-9;
typedef double matrix[maxn][maxn];
bool f[maxn][maxn];

void floyed(int n){
	for(int k=0;k<n;k++)
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
				if(f[i][k]&&f[k][j]) f[i][j]=true;
		}
}


void gaoss(matrix A,int n){
	for(int i=0;i<n;i++){
		int r=i;
		for(int j=i+1;j<n;j++){
			if(fabs(A[j][i])>fabs(A[r][i])) r=j;
		}
		if(r!=i) for(int j=0;j<=n;j++) swap(A[i][j],A[r][j]);
		for(int j=i+1;j<n;j++){
			double ff=A[j][i]/A[i][i];
			for(int k=i;k<=n;k++){
				A[j][k]-=ff*A[i][k];
			}
		}
	}
		/*	for(int i=0;i<n;i++)
		{for(int j=0;j<=n;j++) printf("%.3lf ",A[i][j]);printf("\n");}*/
		for(int i=n-1;i>=0;i--){
			for(int j=i+1;j<n;j++){
				A[i][n]-=A[i][j]*A[j][n];
			}
			A[i][n]/=A[i][i];
		}
	/*for(int i=0;i<n;i++)
		{for(int j=0;j<=n;j++) printf("%.3lf ",A[i][j]);printf("\n");}*/
}

vector<int> prev[maxn],next[maxn];
int inf[maxn],zero[maxn];
int pre[maxn],low[maxn],sccno[maxn],scc_out[maxn],scc_num[maxn],scc_cnt,dfs_clock;
stack<int> S;
bool zihuan[maxn];

void dfs(int u){
	pre[u]=low[u]=++dfs_clock;
	S.push(u);
	for(int e=0;e<next[u].size();e++){
		int v=next[u][e];
		if(!pre[v]) {
			dfs(v);low[u]=min(low[u],low[v]);
		}
		else if(!sccno[v]) 
			low[u]=min(low[u],pre[v]);
	}
	if(low[u]==pre[u]){
		int j;scc_cnt++;scc_num[scc_cnt]=0;
		do{
			j=S.top();S.pop();
			sccno[j]=scc_cnt;
			scc_num[scc_cnt]++;
		}while(j!=u);
	}
}

void tarjan(int n){
	//S.clear();
	memset(low,0,sizeof(low));
	memset(pre,0,sizeof(pre));
	memset(sccno,0,sizeof(sccno));
	memset(scc_out,0,sizeof(scc_out));
	memset(scc_num,0,sizeof(scc_num));
	scc_cnt=dfs_clock=0;
	for(int i=0;i<n;i++){
		if(!zero[i]&&!pre[i]) dfs(i);
	}
	for(int i=0;i<n;i++){
		if(!zero[i]){
			for(int j=0;j<next[i].size();j++){
				if(sccno[next[i][j]]!=sccno[i])
				scc_out[sccno[i]]++;
			}
		}
	}
	for(int i=0;i<n;i++)
		if(!zero[i])
			if((!scc_out[sccno[i]])&&(scc_num[sccno[i]]>1||zihuan[i])) inf[i]=1;
}

int out[maxn],rank[maxn];
matrix A;
int main(){
	//freopen("out.txt","w",stdout);
	int n,a,b,kase=0;
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		memset(f,0,sizeof(f));
		for(int i=0;i<maxn;i++) {
			prev[i].clear();
			next[i].clear();
			out[i]=0;
			inf[i]=0;
			zero[i]=0;
			zihuan[i]=false;
		}
		memset(A,0,sizeof(A));
			memset(zero,0,sizeof(zero));
			memset(inf,0,sizeof(inf));memset(rank,-1,sizeof(rank));
			memset(out,0,sizeof(out));
		
		while(scanf("%d%d",&a,&b)!=EOF){
			if((!a)&&(!b)) break;
				if(kase+1==18) printf("%d %d\n",a,b);
				a--;b--;//printf("a:%d b:%d\n",a,b);
			if(a==b) zihuan[a]=true;
			prev[b].push_back(a);
			next[a].push_back(b);
			f[a][b]=true;
			out[a]++;
		}
		for(int i=0;i<n;i++) {
			f[i][i]=true;
		}
		floyed(n);
		//find inf and zero
		for(int i=0;i<maxn;i++){
			for(int j=0;j<maxn;j++){
				A[i][j]=0.0;
			}
			A[i][i]=1;
			zero[i]=!f[0][i];
		}
		tarjan(n);
		
		int num=0;
		for(int i=0;i<n;i++){
			if((!zero[i])&&(!inf[i])) {
				rank[i]=num++;//printf("rank[%d]:%d\n",i,rank[i]);
			}
			else rank[i]=-1;
		}
		for(int i=0;i<n;i++){
			if(rank[i]!=-1){
				for(int j=0;j<prev[i].size();j++){
					if(!zero[prev[i][j]]){
						A[rank[i]][rank[prev[i][j]]]-=(double)1.0/out[prev[i][j]];
					}
				}
			}
		}A[0][num]=1;
	/*	for(int i=0;i<num;i++)
		{for(int j=0;j<=num;j++) printf("%.3lf ",A[i][j]);printf("\n");}*/
		if(rank[0]!=-1)
		gaoss(A,num);
		
		int q;scanf("%d",&q);
		printf("Case #%d:\n",++kase);
		while(q--){
			scanf("%d",&a);a--;
			if(zero[a]) printf("0.000\n");
			else if(inf[a]) printf("infinity\n");
				else{
					printf("%.3lf\n",A[rank[a]][num] <eps ?0.0 :A[rank[a]][num]);
				}
		}
	}
	return 0;
}

/*
11
1 2
1 3
1 4
3 4
4 2
1 5
5 6
6 5
6 7
7 8
8 9
9 7
9 1
1 10
10 11
11 10
11 1
0 0
11 1 2 3 4 5 6 7 8 9 10 11
*/
