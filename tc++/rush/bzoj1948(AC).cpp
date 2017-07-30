# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxr=14,maxc=42;
const int INF=100000;
char s[maxr<<1][maxc<<1];
int r,c;
int memo[maxr][maxc][1<<12][2];
//char ans[50][100][6];
//int len[50][100];

struct State{
	int mask,up;
	
	bool next(int row,int col,int U,int D,int L,int R,State &T){
		if(up!=U) return false;
		if(s[2*row+1][2*col+2]!=' '&&R) return false;
		if(s[2*row+2][2*col+1]!=' '&&D) return false;
		int left=(mask>>row)&1;
		if(L!=left) return false;
		if(row==r-1&&D) return false;
		if(col==c-1&&R) return false;
		T.mask=(R==left)?mask:mask^(1<<row);
		T.up=D;//len[row][col]=0;
		//if(U==1) ans[row][col][len[row][col]++]='U';if(D==1) ans[row][col][len[row][col]++]='D';
		//	if(L==1) ans[row][col][len[row][col]++]='L';if(R==1) ans[row][col][len[row][col]++]='R';
		//ans[row][col][0]=U;ans[row][col][1]=D;
		//	ans[row][col][2]=L; ans[row][col][3]=R;
		//		if(U==1) printf("U ");if(D==1) printf("D ");if(L==1) printf("L ");if(R==1) printf("R ");puts("");
		return true;
	}
	
};
State T;
int rec(int row,int col,State S){//
	if(row==r) col++,row=0;
	if(col==c) return 0;
	//	printf("row:%d col:%d\n",row,col);
	int &res=memo[row][col][S.mask][S.up];
	if(res>=0) return res;
	res=INF;
	if(s[2*row+1][2*col+1]=='X'){
		//puts("fuck");
		if(S.next(row,col,1,0,0,0,T)) res=min(res,1+rec(row+1,col,T));
		if(S.next(row,col,0,1,0,0,T)) res=min(res,1+rec(row+1,col,T));
		if(S.next(row,col,0,0,1,0,T)) res=min(res,1+rec(row+1,col,T));
		if(S.next(row,col,0,0,0,1,T)) res=min(res,1+rec(row+1,col,T));
	}
	else{
		if(S.next(row,col,0,0,0,0,T)) res=min(res,rec(row+1,col,T));
		if(S.next(row,col,1,1,0,0,T)) res=min(res,2+rec(row+1,col,T));
		if(S.next(row,col,1,0,1,0,T)) res=min(res,2+rec(row+1,col,T));
		if(S.next(row,col,1,0,0,1,T)) res=min(res,2+rec(row+1,col,T));
		if(S.next(row,col,0,1,1,0,T)) res=min(res,2+rec(row+1,col,T));
		if(S.next(row,col,0,1,0,1,T)) res=min(res,2+rec(row+1,col,T));
		if(S.next(row,col,0,0,1,1,T)) res=min(res,2+rec(row+1,col,T));
	}
	//printf("backrow:%d col:%d\n",row-1,col);
	//if(res!=INF) printf("row:%d col:%d res:%d\n",row,col,res);
	return res;
}

int main(){
	scanf("%d %d\n",&r,&c);
	for(int i=0;i<r;i++)
		gets(s[i]);
	//for(int i=0;i<r;i++)
	//	puts(s[i]);
	r/=2;c/=2;
	memset(memo,-1,sizeof(memo));
	State S;S.up=S.mask=0;
	printf("%d\n",rec(0,0,S));
	/*for(int row=0;row<r*2+1;row++){
		for(int col=0;col<c*2+1;col++)
			ans[row][col][len[row][col]]='\0',printf("row:%d col:%d %s\n",row,col,ans[row][col]);
	}*/
	/*char result[100][100];
	for(int i=0;i<r*2+1;i++){
		for(int j=0;j<c*2+1;j++){
			if(s[i][j]!=' ') {result[i][j]=s[i][j];continue;}
			if(i%2==0&&j%2==1) {result[i][j]=ans[i/2][j/2][1]==1?'.':' ';if(i>0&&result[i][j]=='.') result[i-1][j]=s[i-1][j]=='X'?'X':'.';}
			if(j%2==0&&i%2==1) {result[i][j]=ans[i/2][j/2][3]==1?'.':' ';if(j>0&&result[i][j]=='.') result[i][j-1]=s[i][j-1]=='X'?'X':'.';}// printf("%c",ans[i/2][j/2][3]==1?'.':' ');
			if(i%2==1&&j%2==1) result[i][j]=(i>=1&&j>=1&&(result[i-1][j]=='.'||result[i][j-1]=='.')&&s[i][j]!='X')?'.':' ';
			//ans[i][j][len[i][j]]='\0',printf("row:%d col:%d %s\n",i,j,ans[i][j]);
		}result[i][c*2+1]='\0';
	}
	for(int i=0;i<r*2+1;i++) puts(result[i]);*/
	return 0;
}
/*
17 15
+-+-+-+-+-+-+-+
|             |
+ + + + + + + +
|X  |   |     |
+ + + + + + + +
|   |   |  X  |
+-+ + + + + + +
|       |     |
+ + + +-+-+-+-+
|             |
+ + +-+-+-+-+ +
|             |
+ + + + + + + +
|   |         |
+ + + + + + + +
|   |         |
+-+-+-+-+-+-+-+
*/