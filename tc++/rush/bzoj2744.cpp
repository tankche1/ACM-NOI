#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxA=210,maxB=3010;
int tcase;
int nA,nB,m;
int A[maxA],B[maxB];
int ans;
int graph[maxB][maxB];
int G[maxA][maxB];
int bh[maxB];
int num[2];
int left[maxB];
int ref[maxB];
bool used[maxB];
bool vis[maxA];

bool dfs(int x){
	for(int i=1;i<=num[0];i++){
		if(graph[x][i]&&used[ref[i]]&&(!vis[i])){
			vis[i]=1;
			if(left[i]==-1||dfs(left[i])){
				left[i]=x;return true;
			}
		}
	}
	return false;
}

int main(){
	//freopen("input.txt","r",stdin);
	int a,b;
	scanf("%d",&tcase);
	while(tcase--){
		ans=0;
		scanf("%d%d%d",&nA,&nB,&m);
		for(int i=1;i<=nA;i++)
			scanf("%d",&A[i]);
		num[0]=num[1]=0;
		for(int i=1;i<=nB;i++){
			scanf("%d",&B[i]),bh[i]=++num[B[i]&1];
			if((B[i]&1)==0) ref[bh[i]]=i;
		}
		
		memset(graph,0,sizeof(graph));memset(G,0,sizeof(G));
		for(int i=1;i<=m;i++){
			scanf("%d%d",&a,&b);G[a][b]=1;
		}
		
		for(int i=1;i<=nB;i++)
			if(B[i]&1){
				for(int j=1;j<=nB;j++)
					if((B[j]&1)==0){
						int cnum=0;
						for(int k=0;k<=31;k++){
							cnum+=((B[i]>>k)&1)|((B[j]>>k)&1);
						}
						//printf("i:%d j:%d cnum:%d\n",i,j,cnum);
						if((cnum&1)==0) {graph[bh[i]][bh[j]]=1;;}
					}
			}
		
		for(int i=1;i<=nA+1;i++){
			for(int j=(i==nA+1)?i:i+1;j<=nA+1;j++)
				if((i==nA+1||j==nA+1)||((A[i]&1)!=(A[j]&1))){
					//printf("i:%d j:%d\n",i,j);
					for(int k=1;k<=nB;k++) used[k]=false;
					if(i>nA&&j>nA) for(int e=1;e<=nB;e++) used[e]=1;
					else if(i>nA||j>nA){
						if(i<=nA) for(int e=1;e<=nB;e++) if(G[i][e]) used[e]=1;
						if(j<=nA) for(int e=1;e<=nB;e++) if(G[j][e]) used[e]=1;
					}
					else{
						for(int e=1;e<=nB;e++) if(G[i][e]&&G[j][e]) used[e]=1;
					}
					int sum=0,res=0;
					memset(left,-1,sizeof(left));
					for(int ii=1;ii<=nB;ii++) if(used[ii]) sum++;
					for(int ii=1;ii<=nB;ii++){
						if((used[ii])&&(B[ii]&1)){
							for(int k=1;k<=num[0];k++) vis[k]=false;res+=dfs(bh[ii]);//printf("ii:%d\n",ii)
						}
					}
					ans=max(ans,sum-res+(i<=nA)+(j<=nA));
					//printf("ans:%d\n",sum-res+(i<=nA)+(j<=nA));
				}
		}
		printf("%d\n",ans);
	}
	return 0;
}
