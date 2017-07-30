# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=502;
int n,m;
int A[maxn][maxn];

struct IntervalTree2D{
	int Min[maxn<<2][maxn<<2],Max[maxn<<2][maxn<<2],x,y,x1,y1,x2,y2;
	
	void build1D(int x,int o,int L,int R){
		if(L==R){
		}
	}
	
	void build2D(int o,int L,int R){
		if(L==R){
			build1D(o,1,1,m);
		}
		build2D(o,L,(L+R)>>1);
		build2D(o,((L+R)>>1)+1,R);
		return;
	}
	
	void build(){
		build2D(1,1,n);
	}
};

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&A[i][j]);
	IntervalTree2D t;
	t.build();
	return 0;
}
