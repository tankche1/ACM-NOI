#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=2010;
const int INF=1000000010;
int T,MaxP,W;
int q[maxn],head,tail;
int ap[maxn],bp[maxn],as[maxn],bs[maxn];
int f[maxn][maxn];
int main(){
	scanf("%d%d%d",&T,&MaxP,&W);
	for(int i=1;i<=T;i++)
		scanf("%d%d%d%d",&ap[i],&bp[i],&as[i],&bs[i]),as[i]=min(as[i],MaxP),bs[i]=min(bs[i],MaxP);
	f[0][0]=0;for(int j=1;j<=MaxP;j++) f[0][j]=-INF;
	for(int i=1;i<=T;i++){
		int last=i<=W+1?0:i-W-1;
		head=0;tail=-1;
		for(int j=0;j<=MaxP;j++)
			f[i][j]=f[i-1][j];
		for(int j=1;j<=MaxP;j++){
			while(tail>=head&&f[last][q[tail]]+q[tail]*ap[i]<=f[last][j-1]+(j-1)*ap[i]) tail--;
			q[++tail]=j-1;
			while(head<=tail&&q[head]+as[i]<j) head++;
				//printf("i:%d j:%d q[head]:%d val:%d\n",i,j,q[head],f[last][q[head]]-ap[i]*(j-q[head]));
			f[i][j]=max(f[i][j],f[last][q[head]]-ap[i]*(j-q[head]));
		}
		head=0;tail=-1;
		for(int j=MaxP-1;j>=0;j--){
			while(tail>=head&&f[last][q[tail]]+bp[i]*q[tail]<=f[last][j+1]+bp[i]*(j+1)) tail--;
			q[++tail]=j+1;
			while(head<=tail&&q[head]-bs[i]>j) head++;
			f[i][j]=max(f[i][j],f[last][q[head]]+bp[i]*(q[head]-j));
		}
		//for(int j=0;j<=MaxP;j++) printf("f[%d][%d]:%d\n",i,j,f[i][j]);
	}
	printf("%d\n",f[T][0]);
	return 0;
}
