# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int INF=50000;
int n,m;

struct State{
	int up[9],left;
	
	int get_num() const{
		int ans=left;
		for(int i=0;i<m;i++)
		{ans=(ans*3)+up[i];}
		return ans;
	}
	
	bool next(int row,int col,int U,int D,int L,int R,State& T){
	//	printf("row:%d co;%d U:%d D:%d L:%d R:%d \n",row,col,U,D,L,R);
		if(col==m-1&&R) return false;
		if(row==n-1&&D) return false;
		
		if((L!=left)||(U!=up[col])) return false;
		if(left&&up[col]&&(left!=up[col])) return false;
		for(int i=0;i<m;i++) T.up[i]=up[i];
		T.up[col]=D;
		T.left=R;
		return true;
	}
	
	void put_s(){
		printf("%d ",left);
		for(int i=0;i<m;i++)
			printf("%d ",up[i]);
		printf("\n");
	}
};

int G[10][10];

int d[10][10][59049];

int rec(int row,int col,State S){
	//printf("row:%d col:%d\n",row,col);
	if(col==m) {col=0;row++;}
	if(row==n) return 0;
	//S.put_s();
	int state=S.get_num();//printf("%d\n",state);
	if(d[row][col][state]!=-1) return d[row][col][state];
		int& res=d[row][col][state];
	res=INF;
	State T;
	if(G[row][col]<=1){
		if(S.next(row,col,0,0,0,0,T)) res=min(res,rec(row,col+1,T));
		if(G[row][col]==0){
			for(int t=1;t<=2;t++){
				if(S.next(row,col,t,0,t,0,T)) res=min(res,rec(row,col+1,T)+2);
				if(S.next(row,col,t,t,0,0,T)) res=min(res,rec(row,col+1,T)+2);
				if(S.next(row,col,t,0,0,t,T)) res=min(res,rec(row,col+1,T)+2);
				if(S.next(row,col,0,t,t,0,T)) res=min(res,rec(row,col+1,T)+2);
				if(S.next(row,col,0,0,t,t,T)) res=min(res,rec(row,col+1,T)+2);
				if(S.next(row,col,0,t,0,t,T)) res=min(res,rec(row,col+1,T)+2);
			}
		}
	}
		else{
			int t=G[row][col]-1;
			if(S.next(row,col,t,0,0,0,T)) res=min(res,rec(row,col+1,T)+1);
			if(S.next(row,col,0,t,0,0,T)) res=min(res,rec(row,col+1,T)+1);
			if(S.next(row,col,0,0,t,0,T)) res=min(res,rec(row,col+1,T)+1);
			if(S.next(row,col,0,0,0,t,T)) res=min(res,rec(row,col+1,T)+1);
		}
		//printf("row:%d col:%d res:%d\n",row,col,res);
	return res;
}

int main(){
	while(scanf("%d%d",&n,&m)!=EOF){
		if((!n)&&(!m)) break;
		memset(d,-1,sizeof(d));
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				scanf("%d",&G[i][j]);
		State T;
		memset(T.up,0,sizeof(T.up));
		T.left=0;
		int ans=rec(0,0,T);
		if(ans==INF) printf("0\n");
			else printf("%d\n",ans/2);
	}
	return 0;
}
