# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int INF=1000;

int n,m;
int G[10][10];
int memo[10][10][59050];

struct State{
	int up[10],left;
	
	void init(){
		memset(up,0,sizeof(up));left=0;
	}
	
	int encode(){
		int ans=left;
		for(int i=1;i<=n;i++)
			ans=ans*3+up[i];
		return ans;
	}
	
	bool next(int row,int col,int U,int D,int L,int R,State &T){
		if(row==1&&U) return false;
		if(row==m&&D) return false;
		if(col==1&&L) return false;
		if(col==n&&R) return false;
		if(up[col]!=U) return false;
		if(left!=L) return false;
		for(int i=1;i<=n;i++) T.up[i]=up[i];
		T.up[col]=D;T.left=R;
		return true;
	}
};

int rec(int row,int col,State &S){
	if(col>n) row++,col=1;
	if(row>m) return 0;
	int& res=memo[row][col][S.encode()];
	if(res>=0) return res;
	res=INF;
	State T;
	if(G[row][col]<=1){
		if(S.next(row,col,0,0,0,0,T)) res=min(res,rec(row,col+1,T));
		if(!G[row][col])
		for(int t=1;t<=2;t++){
			if(S.next(row,col,t,t,0,0,T)) res=min(res,rec(row,col+1,T)+2);
			if(S.next(row,col,t,0,t,0,T)) res=min(res,rec(row,col+1,T)+2);
			if(S.next(row,col,t,0,0,t,T)) res=min(res,rec(row,col+1,T)+2);
			if(S.next(row,col,0,t,t,0,T)) res=min(res,rec(row,col+1,T)+2);
			if(S.next(row,col,0,t,0,t,T)) res=min(res,rec(row,col+1,T)+2);
			if(S.next(row,col,0,0,t,t,T)) res=min(res,rec(row,col+1,T)+2);
		}
	}
	else{
		int t=G[row][col]-1;
		if(S.next(row,col,t,0,0,0,T)) res=min(res,rec(row,col+1,T)+1);
		if(S.next(row,col,0,t,0,0,T)) res=min(res,rec(row,col+1,T)+1);
		if(S.next(row,col,0,0,t,0,T)) res=min(res,rec(row,col+1,T)+1);
		if(S.next(row,col,0,0,0,t,T)) res=min(res,rec(row,col+1,T)+1);
	}
	return res;
}

int main(){
	State S;
	while(scanf("%d%d",&m,&n)!=EOF){
		if((!m)&&(!n)) break;
		for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++)
				scanf("%d",&G[i][j]);
		memset(memo,-1,sizeof(memo));
		S.init();
		int ans=rec(1,1,S);
			if(ans==INF) ans=0;
				printf("%d\n",ans/2);
	}
	return 0;
}
