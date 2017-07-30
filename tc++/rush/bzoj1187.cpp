# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
const int maxn=105;
const int maxm=6;
const int INF=100*6*1000+10;
map<int,int> memo[maxn][maxm];

int n,m;
int A[maxn][maxm];
bool finish;

struct State{
	int up[maxm],left;
	
	int encode(){
		int res=left;
		for(int i=1;i<=m;i++)
			res*=3,res+=up[i];
		return res;
	}
	
	bool expand(int x,int y,int u,int d,int l,int r,State &T){
		//finish=0;
		if((u&&!up[y])||(up[y]&&!u)) return false;
		if((l&&!left)||(left&&!l)) return false;
		if(u&&!x) return false; if(l&&!y) return false;if(r&&y==m-1) return false;if(d&&x==n-1) return false;
		for(int i=0;i<m;i++) T.up[i]=up[i];
		if(d&&r){
			T.up[y]=1;T.left=2;
			return true;
		}
		if(u&&l){
			if(up[y]==1&&left==1){//((
				T.up[y]=0;T.left=0;
				for(int i=y+1;i<m;i++) if(T.up[i]==2) {T.up[i]=1;break;}
				return true;
			}
			if(up[y]==2&&left==2){//))
				T.up[y]=T.left=0;
				for(int i=y-1;i>=0;i--) if(T.up[i]==1) {T.up[i]=2;break;}
				return true;
			}
			if(left==1&&up[y]==2){//()
				T.left=0;T.up[y]=0;
				for(int i=0;i<m;i++) if(T.up[i]) return false;
					finish=1;
				return true;
			}
			if(left==2&&up[y]==1){//)(
				T.left=T.up[y]=0;return true;
			}
		}
		if(u&&d){
			T.up[y]=up[y];T.left=0;return true;
		}
		if(u&&r){
			T.up[y]=0;T.left=up[y];return true;
		}
		if(l&&d){
			T.up[y]=left;T.left=0;return true;
		}
		if(l&&r){
			T.up[y]=0;T.left=left;return true;
		}
		//不放东西
		T.left=0;return true;
	}
	
};

bool start;

int rec(int x,int y,State &S){
	if(finish){ finish=false;return 0;}
	int key=S.encode();
	if(y==m) x++,y=0;
	if(x==n) return start==1?0:-INF;
	if(memo[x][y].count(key)) return memo[x][y][key];
	int &ans=memo[x][y][key];ans=-INF;//printf("%d\n",ans);
	State T;
	if(S.expand(x,y,0,0,0,0,T)) ans=max(rec(x,y+1,T),ans);
	if(S.expand(x,y,1,1,0,0,T)) ans=max(rec(x,y+1,T)+A[x][y],ans);
	if(S.expand(x,y,1,0,1,0,T)) ans=max(rec(x,y+1,T)+A[x][y],ans);
	if(S.expand(x,y,1,0,0,1,T)) ans=max(rec(x,y+1,T)+A[x][y],ans);
	if(S.expand(x,y,0,1,1,0,T)) ans=max(rec(x,y+1,T)+A[x][y],ans);
	if(S.expand(x,y,0,0,1,1,T)) ans=max(rec(x,y+1,T)+A[x][y],ans);
	if(S.expand(x,y,0,1,0,1,T)) {bool last=start;start=true;ans=max(rec(x,y+1,T)+A[x][y],ans);start=last;}
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			scanf("%d",&A[i][j]);
	State S;
	memset(&S,0,sizeof(S));
		start=false;
	printf("%d\n",rec(0,0,S));
	return 0;
}
