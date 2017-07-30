#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
# define lowbit(x) (x&(-x))
const int maxn=20005;
int pos[maxn][6];
int A[maxn*5],B[maxn*5];
int n,m;

struct FenwickTree{
	int n;
	int C[maxn*5];
	void init(int nn){
		n=nn;
		memset(C,0,sizeof(C));
	}
	
	int query(int x){
		int res=0;
		while(x){
			//printf("x:%d ",x);
			res=max(res,C[x]);
			x-=lowbit(x);
		}//puts("");
		return res;
	}
	
	void Renew(int x,int val){
		//printf("x:%d val:%d\n",x,val);
			while(x<=n){
				C[x]=max(C[x],val);
				//printf("C[%d]:%d\n",x,C[x]);
				x+=lowbit(x);
			}
	}
}fwt;
int main(){
	scanf("%d",&n);
	m=5*n;
	for(int i=1;i<=m;i++)
		scanf("%d",&A[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&B[i]);
	memset(pos,0,sizeof(pos));
	for(int i=1;i<=m;i++)
		pos[B[i]][++pos[B[i]][0]]=i;
	fwt.init(m);
	for(int i=1;i<=m;i++){
		for(int j=5;j>=1;j--){
			int _max=fwt.query(pos[A[i]][j]-1);
			fwt.Renew(pos[A[i]][j],_max+1);
			//printf("dp[%d] [%d]:%d\n",i,pos[A[i]][j],_max+1);
		}
	}
	int _max=fwt.query(m);
	printf("%d\n",_max);
	return 0;
}
