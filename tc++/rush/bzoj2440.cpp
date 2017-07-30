#include<stdio.h>
#include<string.h>
# include<math.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=50010;
int miu[maxn];
bool vis[maxn];
int p[maxn],cnt=0;

void getprime(){
	for(int i=2;i<maxn;i++) miu[i]=-1;
	for(int i=2;i<maxn;i++){
		if(!vis[i]){
			p[cnt++]=i;
			miu[i]=1;//printf("i:%d",i);
			for(int j=i*2;j<maxn;j+=i){
				//printf("j:%d ",j);
				vis[j]=1;
				if((j%(i*i))==0) miu[j]=0;
				else miu[j]=-miu[j];
			}
			//puts("");
			//printf("i:%d miu:%d\n",i,miu[i]);
		}
	}
	//for(int i=1;i<=100;i++) printf("i:%d %d\n",i,miu[i]);
}

int calc(int n){
	int ans=n;int t=sqrt(n);
	for(int i=2;i<=t;i++){
		ans=ans-miu[i]*n/(i*i);
	}
	//printf("n:%d ans:%d\n",n,ans);int dd;scanf("%d",&dd);
	return ans;
}

int main(){
	getprime();
	int T,n;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		int L=1,R=2000000000;
		while(L<=R){
			int M=((LL)L+R)>>1;//printf("L:%d R:%d M:%d\n",L,R,M);
			if(calc(M)<n) L=M+1;
			else R=M-1;
		}
		printf("%d\n",R+1);
	}
	return 0;
}
// 10 1000000000