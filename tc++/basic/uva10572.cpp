# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
int m,n;
bool has_sol;
char partial[8][10];
char grid[8][8];
char ans[8][8];

struct State{
	int color[8];
	int comp[8];
	int up_left;
	int ncolor_comp[2];
	int ncomp;
	
	void nomalsize(){
		int rep[10];
		memset(rep,-1,sizeof(rep));
		ncomp=ncolor_comp[0]=ncolor_comp[1]=0;
		for(int i=0;i<n;i++){
			if(rep[comp[i]]==-1){
				rep[comp[i]]=ncomp++;
				ncolor_comp[color[i]]++;
			}
			comp[i]=rep[comp[i]];
		}
	}
	
	void merge(int a,int b){
		if(a==b) return;
		for(int i=0;i<n;i++)
			if(comp[i]==b) comp[i]=a;
	}
	
	unsigned int encode(){
		unsigned int ans=0;
		for(int i=0;i<n;i++)
			ans=ans*16+color[i]*8+comp[i];
		return ans;
	}
};

map<unsigned int,int> memo[8][8][2];
char ch[2]={'o','#'};
int shit=0;

int rec(int row,int col,State S,int must_color){
	if(col==n) {col=0;row++;}
	S.nomalsize();
	if(row==m){
		if(S.ncolor_comp[0] > 1 || S.ncolor_comp[1] > 1) return 0;
		if(!has_sol){
			for(int i=0;i<m;i++) for(int j=0;j<n;j++) ans[i][j]=grid[i][j];
			has_sol=true;
		}
		printf("%d\n",++shit);
		for(int i=0;i<m;i++){
				for(int j=0;j<n;j++)
					printf("%c",grid[i][j]);
				puts("");
			}puts("");
		return 1;
	}
	
	 if (row > 0 && col > 0 && S.color[col] != S.color[col-1])
    S.up_left = 0;
	
	unsigned int key=S.encode();
	int res=0;
	if(must_color==-1){
		//if(memo[row][col][S.up_left].count(key))
		//	return memo[row][col][S.up_left][key];
	}
	for(int color=0;color<=1;color++){
		if(color==1-must_color) continue;
		if(col&&row&&color==S.color[col]&&color==S.up_left&&color==S.color[col-1]) continue;
		if(ch[1-color]==partial[row][col]) continue;
		grid[row][col]=ch[color];
		State T=S;
		T.up_left=S.color[col];
		T.color[col]=color;
		
		T.comp[col]=(row>0&&S.color[col]==color)?S.comp[col]:S.ncomp;
		if(col>0&&S.color[col-1]==color) T.merge(T.comp[col-1],T.comp[col]);
		
		if(row>0&&S.color[col]!=color){
		bool split=true;
		for(int i=0;i<n;i++){
			if(T.comp[i]==S.comp[col]) split=false;
		}
		if(split){
			if(S.ncolor_comp[1-color]>1||m-row>2) continue;
			res+=rec(row,col+1,T,color);
			continue;
		}
	}
	res+=rec(row,col+1,T,must_color);
	}
	if(must_color<0)
		memo[row][col][S.up_left][key]=res;
	return res;
}

int main(){
	int T;
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++){
		if(kase>1) printf("\n");
		scanf("%d%d",&m,&n);
		for(int i=0;i<m;i++)
			scanf("%s",partial[i]);
		State S;
		memset(&S,0,sizeof(S));
		has_sol=0;
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
			{memo[i][j][0].clear();memo[i][j][1].clear();}
		printf("%d\n",rec(0,0,S,-1));
		if(has_sol){
			for(int i=0;i<m;i++)
			{for(int j=0;j<n;j++) printf("%c",ans[i][j]);printf("\n");}
		}
	}
	return 0;
}
