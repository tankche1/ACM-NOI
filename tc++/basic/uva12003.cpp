# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=300010;
const int maxn_sqrt=1000;
int A[maxn],block[maxn_sqrt][maxn_sqrt],size;

void change(int p,int x){
	int bp=(p-1)/size+1,pos=1;
	while(block[bp][pos]<A[p]) pos++;
	if(A[p]<x){
		A[p]=x;
		block[bp][pos]=x;
		while(pos<size&&block[bp][pos+1]<block[bp][pos]) {swap(block[bp][pos+1],block[bp][pos]);pos++;}
	}
	else{
		A[p]=x;
		block[bp][pos]=x;
		while(pos>1&&block[bp][pos-1]>block[bp][pos]) {swap(block[bp][pos-1],block[bp][pos]);pos--;}
	}
}

int n,m,u;
int L,R,v,p;
int main(){
	scanf("%d%d%d",&n,&m,&u);
	int num=1;size=(int)sqrt(n);
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);
		block[num][(i-1)%size+1]=A[i];
		if(i%size==0){
			sort(block[num]+1,block[num]+size+1);num++;
		}
	}
	if(n%size){
		sort(block[num]+1,block[num]+n%size+1);
		num++;
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d",&L,&R,&v,&p);
		int k=0,bL=((L-1)/size)+1,bR=((R-1)/size)+1;
		if(bL==bR){
			for(int j=L;j<=R;j++) if(A[j]<v) k++;
		}
		else{
			for(int j=L;j<=bL*size;j++)
				if(A[j]<v) k++;
					//printf("k:%d\n",k);
			for(int j=(bR-1)*size+1;j<=R;j++)
				if(A[j]<v) k++;
					//printf("k:%d\n",k);
			for(int b=bL+1;b<bR;b++)
			k+=lower_bound(block[b]+1,block[b]+size+1,v)-block[b]-1;	//printf("k:%d\n",k);
		}
		change(p,(long long)u*k/(R-L+1));
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",A[i]);
	return 0;
}
/*
8 1 8
3
7
7
7
1
3
3
5
1 8 8 7
*/