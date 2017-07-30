# include<stdio.h>
# include<string.h>
# include<algorithm>
# define lowbit(x) (x&(-x))
using namespace std;
int C[303][303][102];
int a[303][303];
int x1,y1,x2,y2,op,c;
int n,m;

void add(int x,int y,int c,int val){
	int yy=y;
	while(x<=n){
		y=yy;
		while(y<=m){
			C[x][y][c]+=val;y+=lowbit(y);
		}
		x+=lowbit(x);
	}
}

int sum_1D(int x,int y,int c){
	int ans=0;
	while(y>=1){
		ans+=C[x][y][c];
		y-=lowbit(y);
	}
	return ans;
}

int sum_2D(int x,int c){
	int ans=0;
	while(x>=1){
		ans+=sum_1D(x,y2,c)-sum_1D(x,y1-1,c);
		x-=lowbit(x);
	}
	return ans;
}



int main(){
	int val,q;
	scanf("%d%d",&n,&m);
	memset(C,0,sizeof(C));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&val);
			a[i][j]=val;
			add(i,j,val,1);
		}
	scanf("%d",&q);
	while(q--){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d%d",&x1,&y1,&c);
			add(x1,y1,a[x1][y1],-1);
			add(x1,y1,c,1);a[x1][y1]=c;
		}
		else{
			scanf("%d%d%d%d%d",&x1,&x2,&y1,&y2,&c);
			int ans=sum_2D(x2,c)-sum_2D(x1-1,c);
			printf("%d\n",ans);
		}
	}
	return 0;
}
/*
3 3
1 2 3
3 2 1
2 1 3
3
2 1 2 1 2 1
1 2 3 2
2 2 3 2 3 2

*/
