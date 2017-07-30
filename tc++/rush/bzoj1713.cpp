#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=(LL)1<<60;
const int maxn=1010;
LL A[maxn],B[maxn],sumA[maxn],sumB[maxn];
int n;
LL f[maxn][maxn];
int Q[maxn][maxn];
int h[maxn],t[maxn];

LL FX(int x){return 2*sumA[x];}
LL FY(int x,int j){return f[x][j-1]-sumA[x]*sumA[x];}
LL FK(int i) {return sumA[i-1];}
LL FC(int i,int j) {return A[i]*B[j]-sumA[i-1]*sumA[i-1];}

bool FSlope(int a,int b,int c,int j){//Kab>Kbc
	return (FY(b,j)-FY(a,j))*(FX(c)-FX(b))>(FY(c,j)-FY(b,j))*(FX(b)-FX(a));
}

LL GX(int x) {return 2*sumB[x];}
LL GY(int i,int x) {return f[i-1][x]-sumB[x]*sumB[x];}
LL GK(int j) {return sumB[j-1];}
LL GC(int i,int j) {return A[i]*B[j]-sumB[j-1]*sumB[j-1];}

bool GSlope(int a,int b,int c,int i){
	return (GY(i,b)-GY(i,a))*(GX(c)-GX(b))>(GY(i,c)-GY(i,b))*(GX(b)-GX(a));
}

int main(){
	scanf("%d",&n);
	sumA[0]=0;sumB[0]=0;
	for(int i=1;i<=n;i++)
		scanf("%lld",&A[i]),sumA[i]=sumA[i-1]+A[i];
	for(int i=1;i<=n;i++)
		scanf("%lld",&B[i]),sumB[i]=sumB[i-1]+B[i],Q[i][0]=0;
	memset(t,-1,sizeof(t));
	memset(h,0,sizeof(h));
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=-INF;
	for(int i=1;i<=n;i++){
		f[i][1]=A[i]*B[1]-sumA[i-1]*sumA[i-1];
		while(t[1]>h[1]&&!FSlope(Q[1][t[1]-1],Q[1][t[1]],i,2)) t[1]--;
		Q[1][++t[1]]=i;
	}
	
	for(int j=1;j<=n;j++){
		f[1][j]=A[1]*B[j]-sumB[j-1]*sumB[j-1];
		if(j!=1) Q[j][++t[j]]=1;
	}
	
	for(int i=2;i<=n;i++){
		t[0]=-1;h[0]=0;
		for(int j=2;j<=n;j++){
			while(t[0]>h[0]&&!GSlope(Q[0][t[0]-1],Q[0][t[0]],j-1,i)) t[0]--;
			Q[0][++t[0]]=j-1;
			while(h[0]<t[0]&&GX(Q[0][h[0]])*GK(j)+GY(i,Q[0][h[0]])<GX(Q[0][h[0]+1])*GK(j)+GY(i,Q[0][h[0]+1])) h[0]++;
			f[i][j]=max(f[i][j],GX(Q[0][h[0]])*GK(j)+GY(i,Q[0][h[0]])+GC(i,j));
		}
		for(int j=2;j<=n;j++){
			while(h[j-1]<t[j-1]&&FX(Q[j-1][h[j-1]])*FK(i)+FY(Q[j-1][h[j-1]],j)<FX(Q[j-1][h[j-1]+1])*FK(i)+FY(Q[j-1][h[j-1]+1],j)) h[j-1]++;
			f[i][j]=max(f[i][j],FX(Q[j-1][h[j-1]])*FK(i)+FY(Q[j-1][h[j-1]],j)+FC(i,j));
		}
		for(int j=2;j<n;j++){
			while(t[j]>h[j]&&!FSlope(Q[j][t[j]-1],Q[j][t[j]],i,j+1)) t[j]--;
			Q[j][++t[j]]=i;
		}
	}
	LL ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,f[i][n]-(sumA[n]-sumA[i])*(sumA[n]-sumA[i]));
	for(int i=1;i<=n;i++)
		ans=max(ans,f[n][i]-(sumB[n]-sumB[i])*(sumB[n]-sumB[i]));
	printf("%lld\n",ans);
	return 0;
}
