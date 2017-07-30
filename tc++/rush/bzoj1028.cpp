#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=405;
const int maxm=3010;
int n,m;
int A[maxn],start[maxn];
int main(){
	memset(A,0,sizeof(A));
	int x;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=3*m+1;i++){
		scanf("%d",&x);A[x]++;
	}
	memcpy(start,A,sizeof(A));
	bool first=true;
	for(int i=1;i<=n;i++){
		bool ok;
		for(int j=1;j<=n;j++){
			if((start[j]+(j==i))>=2) {memcpy(A,start,sizeof(start));A[i]++;A[j]-=2;}
			else continue;
			//if(i==7)	{for(int i=1;i<=n;i++) printf("A[%d] :%d ",i,A[i]);puts("");}
			ok=true;
			for(int k=1;k<=n;k++){
				A[k]=A[k]%3;
				if(A[k+1]<A[k]||A[k+2]<A[k]) {ok=false;break;}
				A[k+1]-=A[k];A[k+2]-=A[k];A[k]=0;
			}
			if(ok) break;
		}
		if(ok) {if(first) printf("%d",i);else printf(" %d",i);first=false;}
	}//puts("");
	if(first) puts("NO");
		else puts("");
	return 0;
}
