#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<queue>
#include<math.h>
#include<string>
#include<stdio.h>
#define rep(a,b) for (int i=a;i<=b;i++)
#define repp(a,b) for (int j=a;j<=b;j++)
#define reppp(a,b) for (int h=a;h<=b;h++)
using namespace std;
const int maxn = 55,maxt = (1<<10)+50;
int DP[maxn][maxt],D[maxn][maxn];
int bit_count[maxt],fact[10];
int N,K;
struct dp{
	int num,val;
	dp(){}
	dp(int _num,int _val):num(_num),val(_val){}
}New[maxn];
bool change[maxn];
bool operator<(dp a,dp b){
	return a.val<b.val;
}
void GetDP(){
	rep(1,N){
		repp(0,K-1)
			DP[i][1<<j]=D[i][j+1];
		repp(K,K+K-1)
			DP[i][1<<j]=D[i][N-K*2+j+1];
	}
	reppp(2,K+K){
		repp(1,(1<<(K+K))-1){
			if (bit_count[j]!=h) continue;
			rep(1,N){
				for (int k=(j-1)&j;k;k=(k-1)&j){
					int o=j^k;
					DP[i][j]=min(DP[i][j],DP[i][o]+DP[i][k]);
				}
				New[i]=dp(i,DP[i][j]);
			}
			sort(New+1,New+N+1);
			memset(change,0,sizeof(change));
			rep(1,N){
				int now=New[i].num,v=New[i].val;
				if (change[now]) continue;
				for (int k=1;k<=N;k++){
					if (v+D[now][k]<DP[k][j]){
						DP[k][j]=v+D[now][k];
						change[k]=1;
					}
				}
			}
		}
	}
}
int Ans[maxt];
int p[5];
int Get(int ret){
	rep(0,K-1)
		if (ret&(1<<i)) ret^=1<<p[i];
	return ret;
}
void _work(){
	memset(DP,63,sizeof(DP));
	memset(D,63,sizeof(D));
	int m;
	scanf("%d%d%d",&N,&m,&K);
	rep(1,N)
		D[i][i]=0;
	rep(1,m){
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		if (c<D[u][v])
			D[u][v]=D[v][u]=c;
	}
	rep(1,N)
		repp(1,N)
			reppp(j+1,N)
				if (D[j][i]+D[i][h]<D[j][h])
					D[j][h]=D[h][j]=D[j][i]+D[i][h];
	GetDP();
	rep(0,K-1)
		p[i]=i+K;
	int ANS=DP[0][0],times=fact[K];
	reppp(1,times){
		memset(Ans,63,sizeof(Ans));
		repp(1,(1<<K)-1){
			int k=Get(j);
			rep(1,N)
				Ans[j]=min(Ans[j],DP[i][k]);
		}
		repp(2,K){
			rep(1,(1<<K)-1){
				if (bit_count[i]!=j) continue;
				for (int k=(i-1)&i;k;k=(k-1)&i){
					int o=i^k;
					Ans[i]=min(Ans[i],Ans[o]+Ans[k]);
				}
			}
		}
		ANS=min(ANS,Ans[(1<<K)-1]);
		next_permutation(p,p+K);
	}
	if (ANS<DP[0][0]) printf("%d\n",ANS);
	else printf("No solution\n");
}
int main(){
	int t;
	cin>>t;
	rep(1,(1<<10)-1)
		bit_count[i]=bit_count[i>>1]+(i&1);
	fact[0]=1;
	rep(1,5)
		fact[i]=fact[i-1]*i;
	while (t--){
		_work();
	}
//	system("pause");
	return 0;
}