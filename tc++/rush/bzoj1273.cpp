#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int Step=15;
const int mod=1<<16;
int n,m;
int A[maxn];
int pre[Step+1][1<<16];

int Query(int x,int L,int R){
	if(L<0) L+=1<<(x+1);
	if(R<0) R+=1<<(x+1);
	//printf("L:%d R:%d\n",L,R);
	if(L<=R) return L==0?pre[x][R]:pre[x][R]-pre[x][L-1];
	return n-pre[x][L-1]+pre[x][R];
}

int main(){
	long long ans=0;
	int j,x,delta=0;
	char op;
	memset(pre,0,sizeof(pre));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);
		for(int j=0;j<=Step;j++)
			pre[j][A[i]&((1<<(j+1))-1)]++;
	}
	for(int i=0;i<=Step;i++)
		for(int j=1;j<1<<16;j++) 
			pre[i][j]+=pre[i][j-1];
	for(int t=1;t<=m;t++){
		while((op=getchar())&&op!='A'&&op!='Q');
		scanf("%d",&x);
		if(op=='A'){
			//for(int j=0;j<=Step;j++) if(x&(1<<j)) delta+=1<<(Step-j);
			delta+=x;
			delta%=mod;
		}
		else{
			//x--;
			int d=delta&((1<<(x+1))-1);
			int tt=Query(x,(1<<x)-d,(1<<(x+1))-1-d);ans+=tt;
		//	printf("%d\n",tt);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
/*
3 5
1 2 4
Q 1
Q 2
A 1
Q 1
Q 2

*/
