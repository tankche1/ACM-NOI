#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1010;
int A[maxn][maxn];
int n,q;
int C[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&A[i][j]);
	int ans=0;
	for(int i=1;i<=n;i++) C[i]=A[i][i],ans+=C[i];
	scanf("%d",&q);
	int op,x;
	for(int i=1;i<=q;i++){
		scanf("%d",&op);
		if(op==3) printf("%d",ans&1);
		else{
			scanf("%d",&x);
			ans-=C[x];C[x]^=1;ans+=C[x];
		}
	}puts("");
	return 0;
}
