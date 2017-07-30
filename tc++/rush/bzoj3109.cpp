#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int releft[10][10];
int reup[10][10];
int pos[7]={0,2,3,5,6,8,9};
int a[10][10];
int col[10],row[10],square[10];
int To[10];
int n=9;
int Bit=(1<<9)-1;
int to[514];

inline int belong(int x,int y){return (x-1)/3*3+(y-1)/3+1;}

bool dfs(int x,int y){
	if(y>n) x++,y=1;
	if(x>n){
		for(int i=1;i<=9;i++){
			for(int j=1;j<=9;j++) printf("%d%c",a[i][j],j!=9?' ':'\n');
		}
		return true;
	}
	int key=col[y]|row[x]|square[belong(x,y)];
	key=key^Bit;
	while(key!=0){
		int num=to[(key&(-key))];
		//printf("key:%d num:%d\n",key,num);int dd;scanf("%d",&dd);
		key^=1<<(num-1);
		a[x][y]=num;
		if(releft[x][y]!=-1&&((num>a[x][y-1])!=releft[x][y])) continue;
		if(reup[x][y]!=-1&&((num>a[x-1][y])!=reup[x][y])) continue;
		col[y]^=1<<(num-1);
		row[x]^=1<<(num-1);
		square[belong(x,y)]^=1<<(num-1);
		//printf("a[%d][%d]:%d\n",x,y,a[x][y]);
		if(dfs(x,y+1)) return true;
		col[y]^=1<<(num-1);
		row[x]^=1<<(num-1);
		square[belong(x,y)]^=1<<(num-1);
	}
	return false;
}

char Get(){
	char t;
	while((t=getchar())&&t!='<'&&t!='>'&&t!='v'&&t!='^');
	return t;
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	for(int i=0;i<=8;i++)
		to[1<<i]=i+1;
	char t;
	memset(releft,-1,sizeof(releft));
	memset(reup,-1,sizeof(reup));
	for(int s=1;s<=3;s++){
		for(int i=1;i<=6;i++)
			t=Get(),releft[(s-1)*3+1][pos[i]]=t=='<';
		for(int i=1;i<=9;i++)
			t=Get(),reup[(s-1)*3+2][i]=t=='^';
		for(int i=1;i<=6;i++)
			t=Get(),releft[(s-1)*3+2][pos[i]]=t=='<';
		for(int i=1;i<=9;i++)
			t=Get(),reup[(s-1)*3+3][i]=t=='^';
		for(int i=1;i<=6;i++)
			t=Get(),releft[(s-1)*3+3][pos[i]]=t=='<';
	}
	memset(row,0,sizeof(row));
	memset(col,0,sizeof(col));
	memset(square,0,sizeof(square));
	dfs(1,1);
	return 0;
}
