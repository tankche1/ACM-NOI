#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=3010;
int n,m;
int A[maxn],B[maxn];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&B[i]);
	sort(A+1,A+n+1);
	sort(B+1,B+m+1);
	int pos=m;
	int ans=0;
	B[0]=-1;
	for(int i=n;i>=1;i--){
		if(B[pos]>=A[i])
		{pos--;continue;}
		else ans++;
	}
	printf("%d\n",ans);
	return 0;
}
