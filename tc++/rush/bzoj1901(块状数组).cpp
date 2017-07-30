# include<stdio.h>
# include<string.h>
# include<string>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int BLOCKSIZE=100;
const int INF=~0U>>1;
const int MAXBLOCK=maxn/BLOCKSIZE+20;
int Count[MAXBLOCK],next[MAXBLOCK],num[MAXBLOCK][BLOCKSIZE];
int n,m;
int A[maxn];
int small,big;

void build(){
	int b=0,i;
	for(i=1;i+BLOCKSIZE-1<n;i+=BLOCKSIZE){
		Count[b]=BLOCKSIZE;next[b]=b+1;
	/*	for(int j=i;j<=i+Count[b]-1;j++)
			printf("%d ",A[j]);puts("");*/
		memcpy(num[b]+1,A+i,Count[b]*4);/*for(int j=1;j<=Count[b];j++)
				printf("%d ",num[b][j]);puts("");*/
		sort(num[b]+1,num[b]+BLOCKSIZE+1);
		/*for(int j=1;j<=Count[b];j++)
				printf("%d ",num[b][j]);puts("");*/
		b=next[b];
	}
		Count[b]=n-i+1;
		memcpy(num[b]+1,A+i,(Count[b])*4);
		sort(num[b]+1,num[b]+n-i+2);
	next[b]=-1;
}

void find(int qL,int qR,int val){
	int b=(qL-1)/BLOCKSIZE,i=qL,pos=qL-b*BLOCKSIZE;
	//printf("qL:%d qR:%d val:%d b:%d pos:%d\n",qL,qR,val,b,pos);
	for(;pos<=Count[b]&&i<=qR;i++,pos++)
		small+=A[i]<val,big+=A[i]>val;
	//printf("%d %d\n",small,big);
	b=next[b];
	if(b==-1) return;
	for(;i+Count[b]-1<qR;i+=Count[b],b=next[b]){
		small+=lower_bound(num[b]+1,num[b]+Count[b]+1,val)-(num[b])-1;
		//if(val==6) {printf("i:%d %d b:%d %d\n",i,i+Count[b]-1,b,lower_bound(num[b]+1,num[b]+Count[b]+1,val)-num[b]-1);
		//	for(int j=1;j<=Count[b];j++)
			//	printf("%d ",num[b][j]);puts("");
		//}
		big+=Count[b]-(upper_bound(num[b]+1,num[b]+Count[b]+1,val)-num[b])+1;
	}
	for(;i<=qR;i++)
		small+=A[i]<val,big+=A[i]>val;
//	printf("qL:%d qR:%d val:%d small:%d big:%d\n",qL,qR,val,small,big);
}

void change(int pos,int val){
	int b=(pos-1)/BLOCKSIZE,i=lower_bound(num[b]+1,num[b]+Count[b]+1,A[pos])-num[b];
	
	num[b][i]=val;sort(num[b]+1,num[b]+Count[b]+1);
	A[pos]=val;
}

int main(){
	int pos,val;
	int qL,qR,k,L,R,M;
	char op[20];
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	build();
	for(int i=1;i<=m;i++){
		scanf("%s",op);
		if(op[0]=='Q'){
			scanf("%d%d%d",&qL,&qR,&k);
			L=0,R=INF;
			while(L<=R){
				M=(L+R)>>1;small=big=0;
				find(qL,qR,M);
				if(small<k&&big<=(qR-qL+1-k)) break;
				else if(small>=k) R=M-1;
					else L=M+1;
			}
			printf("%d\n",M);
		}
		else{
			scanf("%d%d",&pos,&val);
			change(pos,val);
		}
	}
	return 0;
}
/*
10 10000
1 2 3 4 5 6 7 8 9 10
Q 3 10 4

*/
