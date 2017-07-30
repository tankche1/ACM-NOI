#include<stdio.h>
# include<map>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100;
typedef unsigned long long ull;
const int seed=131;
int n;
int A[maxn];
map<ull,bool> id;
ull pow[maxn+1];
bool ok;

void dfs(ull code,int p,bool used){
	if(id.count(code)) return;
	id[code]=true;
	while(p<maxn&&A[p]==0) p++;
	if(p==maxn) {if(used) ok=true;return;}
	if((!used)&&A[p]>=2){
		code=code-2*pow[p];code-=pow[maxn];A[p]-=2;dfs(code,p,1);if(ok) return;
		code+=2*pow[p]+pow[maxn];A[p]+=2;
	}
	if(p+2<maxn&&A[p+1]>=1&&A[p+2]>=1){
		code=code-pow[p]-pow[p+1]-pow[p+2];A[p]--;A[p+1]--;A[p+2]--;dfs(code,p,used);if(ok) return;
		code+=pow[p]+pow[p+1]+pow[p+2];A[p]++;A[p+1]++;A[p+2]++;
	}
	if(A[p]>=3){
		code-=pow[p]*3;A[p]-=3;dfs(code,p,used);if(ok) return;
		code+=pow[p]*3;A[p]+=3;
	}
	if(A[p]>=4){
		code-=pow[p]*4;A[p]-=4;dfs(code,p,used);if(ok) return;
		code+=pow[p]*4;A[p]+=4;
	}
	return;
}

int main(){
	scanf("%d",&n);
	pow[0]=1;
	for(int i=1;i<=maxn;i++)
		pow[i]=pow[i-1]*seed;
	while(n--){
		id.clear();
		ull ret=pow[maxn];
		for(int i=0;i<maxn;i++)
			scanf("%d",&A[i]),ret+=(ull)A[i]*pow[i];
		ok=false;
		dfs(ret,0,false);
		if(ok) puts("Yes");
			else puts("No");
	}
	return 0;
}
