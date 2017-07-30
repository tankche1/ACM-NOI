# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
int m,n;
char partial[8][9],grid[8][8],sol[8][8];
bool has_sol;

map<unsigned,int> memo[8][8][2];

struct State{
	int up_left,col[8],comp[8],ncomp_col[2],ncomp;
	
	void normalsize(){
		int rep[10];
		memset(rep,-1,sizeof(rep));
		ncomp=ncomp_col[0]=ncomp_col[1]=0;
		for(int i=0;i<n;i++){
			if(rep[comp[i]]==-1){
				rep[comp[i]]=ncomp++;
				ncomp_col[col[i]]++;
			}
			comp[i]=rep[comp[i]];
		}
	}
	
	void merge(int a,int b){
		if(a==b) return;
		for(int i=0;i<n;i++)
			if(comp[i]==a) comp[i]=b;
	}
	
	unsigned int encode(){
		unsigned int key=0;
		for(int i=0;i<n;i++)
			key=key*16+col[i]*8+comp[i];//一开始col和comp的位置写错了。。。
		return key;
	}
};
char ch[2]={'o','#'};int shit=0;

int rec(int r,int c,State &S,int forcecol){
	if(c==n) r++,c=0;
			S.normalsize();
	/*printf("r:%d c:%d force:%d ",r,c,forcecol);
	for(int i=0;i<n;i++)
		printf("comp[%d]:%d ",i,S.comp[i]);printf("col[0]:%d col[1]:%d",S.ncomp_col[0],S.ncomp_col[1]);puts("");
	for(int i=0;i<r;i++){
		for(int j=0;j<n;j++)
			printf("%c",grid[i][j]);puts("");}
	for(int j=0;j<c;j++)
		printf("%c",grid[r][j]);puts("");*/
	if(r==m) {
		if(S.ncomp_col[0]>1||S.ncomp_col[1]>1) {//printf("r:%d c:%d res:%d\n",r,c,0);
			return 0;}
		if(!has_sol) {
			has_sol=1;
			for(int i=0;i<m;i++) for(int j=0;j<n;j++) sol[i][j]=grid[i][j];
		}
		/*printf("%d\n",++shit);
		for(int i=0;i<m;i++){
				for(int j=0;j<n;j++)
					printf("%c",grid[i][j]);
				puts("");
			}puts("");*/
			//printf("r:%d c:%d res:%d\n",r,c,1);
		return 1;
	}
	if((r&&c&&S.col[c-1]!=S.col[c])) S.up_left=0;
	unsigned int key;
	if(forcecol==-1){
		key=S.encode();
		if(memo[r][c][S.up_left].count(key)!=0){
			//printf("r:%d c:%d res:%d\n",r,c,memo[r][c][S.up_left][key]);
			return memo[r][c][S.up_left][key];
		}
	}
	int res=0;
	for(int color=0;color<2;color++){
		if(partial[r][c]!='.'&&partial[r][c]!=ch[color]) continue;
		if(r&&c&&S.col[c]==S.up_left&&S.col[c]==S.col[c-1]&&S.col[c]==color) continue;
		if(forcecol!=-1&&color!=forcecol) continue;
		//	printf("r:%d c:%d col:%d forcecol:%d %d\n",r,c,color,forcecol,S.ncomp_col[S.comp[c]]);
		State T=S;
		grid[r][c]=ch[color];
		T.up_left=S.col[c];
		T.col[c]=color;
		T.comp[c]=T.ncomp;
		if(r&&color==S.col[c]) T.comp[c]=S.comp[c];
		if(c&&color==S.col[c-1]) T.merge(T.comp[c],T.comp[c-1]);
		//if(!r) gone=false;
		if(r&&S.col[c]!=color){
			bool gone=true;
			for(int i=0;i<n;i++) if(T.comp[i]==S.comp[c]) gone=false;//一开始漏了S.comp[c]被同化的情况
			if(gone){
				if(S.ncomp_col[S.col[c]]>1||r+2<m) continue;//一开始写成S.ncomp_col[S.comp[c]] 查到我飞起
				res+=rec(r,c+1,T,color);
				continue;
			}
		}
		res+=rec(r,c+1,T,forcecol);
	}
//	printf("r:%d c:%d res:%d\n",r,c,res);
//	int fuck;
//	scanf("%d",&fuck);
	if(forcecol<0)
		return memo[r][c][S.up_left][key]=res;
	return res;
}

int main(){
	State S;
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&m,&n);
		for(int i=0;i<m;i++)
			scanf("%s",partial[i]);
		memset(&S,0,sizeof(S));
		has_sol=false;
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				for(int k=0;k<2;k++)
		memo[i][j][k].clear();
		int ans=rec(0,0,S,-1);
		printf("%d\n",ans);
		if(has_sol)
			for(int i=0;i<m;i++){
				for(int j=0;j<n;j++)
					printf("%c",sol[i][j]);
				puts("");
			}
			puts("");
	}
	return 0;
}
/*
1
2 3
...
...
*/
