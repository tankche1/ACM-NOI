# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=50010;
const int maxm=1010;
const int mod=10007;
int n,m;
int a[maxn];

bool can(int len){
	int cnt=0,now=0;
	for(int i=1;i<=n;i++){
		now+=a[i];
		if(now>len){
			now=a[i];
			if(++cnt>m+1) return false;
		}
	}
	++cnt;
	return cnt<=m+1;
}

int erfen(){
	int L=1,R=1000*50000;
	for(int i=1;i<=n;i++) L=max(L,a[i]);
	while(L<=R){
		int M=(L+R)>>1;
		if(can(M)) R=M-1;
			else L=M+1;
	}
	return R+1;
}

int g[2][maxn];

int main(){
	//freopen("input.txt","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	int maxlen=erfen();
	//printf("%d\n",maxlen);
	/*for(int j=1;j<=n;j++) g[0][j]=1;
	g[0][0]=0;*/
	memset(g,0,sizeof(g));
	int sum=0;
	g[1][0]=0;
	int i;
	for(i=1;sum+a[i]<=maxlen&&i<=n;i++)
	{g[1][i]=g[1][i-1]+1;sum+=a[i];}
	for(;i<=n;i++)
		g[1][i]=g[1][i-1];
	//for(int i=0;i<=n;i++) printf("g[1][%d]:%d\n",i,g[1][i]);
	int pre=a[1],ans=g[1][n]-g[1][n-1];
	for(int i=2;i<=m+1;i++){
		int now=i%2;int last=now^1;
		memset(g[now],0,sizeof(g[now]));
		//printf("i:%d\n",i);
		int sum=pre,len=i-1;
		for(int j=i;j<=n;j++){
			sum+=a[j];len++;
			while(sum>maxlen) {sum-=a[j-len+1];len--;}
			//printf("j:%d sum:%d len:%d\n",j,sum,len);
			g[now][j]=(g[now][j-1]+g[last][j-1]-g[last][j-len-1]+mod)%mod;
			//if(g[now][j]) printf("%d - %d\n",g[last][j-1],g[last][j-len-1]);
			//if(g[now][j]==g[now][j-1]) {g[now][j]=0;break;}
		}
		pre+=a[i];
		//for(int j=i;j<=n;j++)
		//	if(g[now][j]) printf("g[%d][%d]:%d\n",i,j,g[now][j]);
		ans=(ans+g[now][n]-g[now][n-1]+mod)%mod;
	}
	printf("%d %d\n",maxlen,ans%mod);
	return 0;
}
