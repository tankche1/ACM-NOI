# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=205;
const int INF=maxn*1000;
int n;
int w[maxn][maxn];

struct KM{
	int Lx[maxn],Ly[maxn],slack[maxn];
	bool S[maxn],T[maxn];
	int left[maxn];
	
	bool match(int x){
		S[x]=1;
		for(int j=1;j<=n;j++)
			if(!T[j]){
			if(Lx[x]+Ly[j]-w[x][j]==0){
				T[j]=1;
				if(!left[j]||match(left[j]))
				{left[j]=x;return true;}
			}
			else slack[j]=min(slack[j],Lx[x]+Ly[j]-w[x][j]);
		}
		return false;
	}
	
	void update(){
		int d=INF;
		for(int i=1;i<=n;i++)
			if(!T[i]) d=min(d,slack[i]);
		for(int i=1;i<=n;i++){
			if(S[i]) Lx[i]-=d;
			if(T[i]) Ly[i]+=d;
				else slack[i]-=d;
		}
	}
	
	void km(){
		for(int i=1;i<=n;i++){
			Lx[i]=-INF;
			for(int j=1;j<=n;j++)
				Lx[i]=max(Lx[i],w[i][j]);
		}
		memset(Ly,0,sizeof(Ly));memset(left,0,sizeof(left));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++) slack[j]=INF;
			for(;;){
				memset(S,0,sizeof(S));memset(T,0,sizeof(T));
				if(match(i)) break;
				else update();
			}
		}
	}
	
};KM solve;

int main(){
	scanf("%d",&n);
	int sch,a,b,cost;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			w[i][j]=-INF;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&sch,&a,&b,&cost);
		for(int j=a;j<=b;j++)
			w[i][j]=-cost*abs(j-sch);
	}
	solve.km();
	int ans=0;
	for(int i=1;i<=n;i++){
		ans-=w[solve.left[i]][i];
		if(w[solve.left[i]][i]==-INF) {puts("NIE");return 0;}
	}
	printf("%d\n",ans);
	return 0;
}
