#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
int n,m;
int C[maxn],w[maxn];
int num[maxn],cnt=0;
int A[34];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&C[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&w[i]),num[++cnt]=w[i];
	sort(num+1,num+cnt+1);
	sort(w+1,w+m+1);
	cnt=unique(num+1,num+cnt+1)-(num+1);
	for(int i=1;i<=n;i++){
		for(int j=cnt;j>=1;j--){
			A[j]+=C[i]/num[j];C[i]-=C[i]/num[j]*num[j];
		}
	}
//	for(int j=cnt;j>=1;j--) printf("A[%d]:%d\n",j,A[j]);
	int ans=0,j;
	for(int i=1;i<=m;i++){
		w[i]=lower_bound(num+1,num+cnt+1,w[i])-num;
		//printf("i:%d w:%d\n",i,w[i]);
		//for(int j=cnt;j>=1;j--) printf("A[%d]:%d\n",j,A[j]);
		j=w[i];
		if(A[w[i]]) {A[w[i]]--,ans++;continue;}
		while(j<cnt&&A[j]==0) A[j]=num[j+1]/num[j]-1,j++;
		if(A[j]==0) break;
		else A[j]--;
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}
