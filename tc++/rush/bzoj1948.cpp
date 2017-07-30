# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
const int INF=100000;
const int maxn=85;
const int maxr=26;
char s[maxn][maxn];
int n,m;
map<int,int> memo[maxn][maxr];
struct State{
	int up[maxr];
	int left;
	
	unsigned int encode(){
		unsigned int key=left;
		for(int i=0;i<n;i++)
			key=(key<<1)|up[i];
		return key;
	}
	
	bool next(int row,int col,int U,int D,int L,int R,State &T){
		if(up[col]!=U) return false;
		if(left!=L) return false;
		if(D&&row==m-1) return false;
		if(R&&col==n-1) return false;
		//if(L&&col==0) return false;
		//if(U&&row==0) return false;
		for(int i=0;i<n;i++) T.up[i]=up[i];
		T.up[col]=D;T.left=R;
		//if(U==1) printf("U ");if(D==1) printf("D ");if(L==1) printf("L ");if(R==1) printf("R ");puts("");
		return true;
	}
	
};
State T;

int rec(int row,int col,State S){
	if(col==n) row++,col=0;
	if(row==m) return 0;
		//printf("row:%d col:%d\n",row,col);
	unsigned key=S.encode();
	if(memo[row][col].count(key)) return memo[row][col][key];
	int &res=memo[row][col][key];res=INF;
	for(int i=1;i<=1;i++){
		if(s[row][col]!='X'&&S.next(row,col,0,0,0,0,T)) res=min(res,rec(row,col+1,T));
		if(s[row][col]=='+'||s[row][col]=='|'||s[row][col]=='-') break;
		if(s[row][col]=='X'){
			if(S.next(row,col,1,0,0,0,T)) res=min(res,rec(row,col+1,T)+1);
			if(S.next(row,col,0,1,0,0,T)) res=min(res,rec(row,col+1,T)+1);
			if(S.next(row,col,0,0,1,0,T)) res=min(res,rec(row,col+1,T)+1);
			if(S.next(row,col,0,0,0,1,T)) res=min(res,rec(row,col+1,T)+1);
		}
		else{
			//if(row==1&&col==0) printf("fuck:%d\n",S.next(row,col,1,0,0,1,T));
			if(S.next(row,col,1,1,0,0,T)) res=min(res,rec(row,col+1,T)+2);
			if(S.next(row,col,1,0,1,0,T)) res=min(res,rec(row,col+1,T)+2);
			if(S.next(row,col,1,0,0,1,T)) res=min(res,rec(row,col+1,T)+2);
			if(S.next(row,col,0,1,1,0,T)) res=min(res,rec(row,col+1,T)+2);
			if(S.next(row,col,0,1,0,1,T)) res=min(res,rec(row,col+1,T)+2);
			if(S.next(row,col,0,0,1,1,T)) res=min(res,rec(row,col+1,T)+2);
		}
	}
	//printf("backrow:%d col:%d\n",row,col-1);
	return res;
}
char news[maxn][maxn];
int main(){
	State S;
	memset(S.up,0,sizeof(S.up));S.left=0;
	scanf("%d %d\n",&n,&m);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			scanf("%c",&s[i][j]);
		}getchar();}
	//swap(n,m);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			news[m-j-1][i]=s[i][j];
		for(int i=0;i<m;i++) for(int j=0;j<n;j++) s[i][j]=news[i][j];
	//for(int i=0;i<m;i++) puts(s[i]);
	printf("%d\n",rec(0,0,S)/2);
	return 0;
}
/*
3 5
X+  X
   ++
++XX+
2 5
X+  X
   ++
+++++
2 5
X+ X 
   ++
2 4
X+ X
   +
*/
