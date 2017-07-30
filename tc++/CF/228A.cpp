# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=110;
int A[maxn],n;
int num[maxn];

bool check(int pile){
	memset(num,0,sizeof(num));
	for(int i=1;i<=n;i++){
		int j;
		for(j=1;j<=pile;j++)
			if(num[j]<=A[i]) {num[j]++;break;}
		if(j>pile) return false;
	}
	return true;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	sort(A+1,A+n+1);
	int L=1,R=n;
	while(L<=R){
		int M=(L+R)>>1;
		if(check(M)) R=M-1;
			else L=M+1;
	}
	printf("%d\n",R+1);
	return 0;
}
