# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
int n,m,k;
int w[maxn],c[maxn],sumw[maxn],sumc[maxn];
int ans=0,tail,head;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	sumw[0]=sumc[0]=0;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&w[i],&c[i]),sumw[i]=sumw[i-1]+w[i],sumc[i]=sumc[i-1]+c[i];
	int tailsum=0,L,R,M;
	for(int i=0;n-i-m>0;i++){//从尾端拿走i个
		//printf("i:%d tailsum:%d\n",i,tailsum);
		if(sumw[n-i]-sumw[n-i-m]>k*sumw[n-i-m]) break;//太重了
		L=1,R=n-i-m;
		while(L<=R){
			M=(L+R)>>1;
			if(sumw[n-i]-sumw[n-i-m]<=k*(sumw[n-i-m]-sumw[M])) L=M+1;
			else R=M-1;
		}
		if(tailsum+sumc[L-1]>ans){
			ans=tailsum+sumc[L-1];tail=i;head=L-1;
			//printf("ans:%d i:%d L-1:%d tailsum:%d\n",ans,i,L-1,tailsum);
		}
		tailsum+=c[n-i];
	}
	if(!ans) {printf("0 0\n");return 0;}
	printf("%d %d\n",head+tail,ans);
	for(int i=1;i<=tail;i++) printf("H");
	for(int i=1;i<=head;i++) printf("T");puts("");
	//printf("sumc[11-20]:%d \n",sumc[20]-sumc[10]);
	return 0;
}
