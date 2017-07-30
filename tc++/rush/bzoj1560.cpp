# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxm=1010;
const int maxn=200010;
const int INF=~0U>>1;
int C[maxm],R[maxm];
int n,m;
struct state{
	int x,y,num;
	bool operator < (const state &rhs)const{
		if(x==rhs.x) return y<rhs.y;
		return x<rhs.x;
	}
};
state a[maxn];

inline int dist(int x,int y,int a,int b){
	return (a-x)*(a-x)+(y-b)*(y-b);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].num);
	}
	sort(a+1,a+n+1);
	memset(R,-1,sizeof(R));
	for(int i=1;i<=m;i++) C[i]=-INF;
	R[1]=1;C[1]=a[1].num;
	for(int i=2;i<=n;i++){
		int x=a[i].x,y=a[i].y;
		int res=-INF;
		for(int j=1;j<=y;j++){
			if((R[j]!=-1)&&C[j]-dist(x,y,R[j],j)>res) res=C[j]-dist(x,y,R[j],j);
		}
		C[y]=res+a[i].num;
		R[y]=x;
				//printf("x:%d y:%d C:%d\n",x,y,C[y]);
	}
	printf("%d\n",C[m]);
	return 0;
}
