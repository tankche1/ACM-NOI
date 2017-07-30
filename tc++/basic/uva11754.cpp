# include<stdio.h>
# include<string.h>
# include<vector>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=12,maxk=110;
const int limit=10000;

typedef long long LL;

//a,b is int but x,y can be longlong
void gcd(LL a,LL b,LL &d,LL &x,LL &y){
	if(!b) {x=1;y=0;d=a;return;
		}
	gcd(b,a%b,d,y,x);y-=(a/b)*x;
}
 
LL china(int n,int *a,int *m){//solve X%m[i]=a[i] (1<=i<=n)
	LL x=0,y=0,M=1,ans=0,d;
	for(int i=1;i<=n;i++) M=M*m[i];
	for(int i=1;i<=n;i++){
		//printf("!");
		gcd(M/m[i],m[i],d,x,y);
		ans=(ans+x*M/m[i]*a[i])%M;
	}
	return (ans+M)%M;
}


int C;
int X[maxn],Y[maxn][maxk],k[maxn];
int a[maxn];
vector<LL> sol;

void dfs(int depth){
	//printf("depth:%d\n",depth);
	if(depth==C+1){
		sol.push_back(china(C,a,X));
	}
	else{
		for(int i=1;i<=k[depth];i++)
		{a[depth]=Y[depth][i];dfs(depth+1);}
	}
}

void china_solve(int S){
	sol.clear();
	dfs(1);
	//for(int i=0;i<sol.size();i++) printf("%lld\n",sol[i]);
	sort(sol.begin(),sol.end());
	LL M=1;
	for(int i=1;i<=C;i++) M*=X[i];
	for(LL T=0;;T+=M){
		for(int j=0;j<sol.size();j++){
			LL ans=sol[j]+T;
			if(ans) {
				printf("%lld\n",ans);
				if(--S==0) return;
			}
		}
	}
}

set<int> value[maxn];

void enum_solve(int S,int bc){
	for(int i=1;i<=C;i++) 
	if(i!=bc){
		value[i].clear();
		for(int j=1;j<=k[i];j++) value[i].insert(Y[i][j]);
	}
	LL ans=0;
	for(LL T=0;;T+=X[bc]){
		for(int i=1;i<=k[bc];i++){
			ans=T+Y[bc][i];
			if(!ans) continue;
			bool ok=true;
			for(int j=1;j<=C;j++) if(j!=bc){
				if(!value[j].count(ans%X[j])) {ok=false;break;}
			}
			if(ok){
				printf("%lld\n",ans);
				if(--S==0) return;
			}
		}
	}
}

int main(){
	//freopen("in.txt","r",stdin);
	int S,bestc=1;
	while(scanf("%d%d",&C,&S)!=EOF){
		if(!C&&!S) break;
		LL tot=1;
		for(int i=1;i<=C;i++){
			scanf("%d%d",&X[i],&k[i]);
			tot*=k[i];
			for(int j=1;j<=k[i];j++)
				scanf("%d",&Y[i][j]);
			sort(Y[i]+1,Y[i]+k[i]+1);
			if(k[bestc]*X[i]>k[i]*X[bestc]) bestc=i;
		}
		if(tot<limit) china_solve(S);
			else 
				enum_solve(S,bestc);
			printf("\n");
	}
	return 0;
}
