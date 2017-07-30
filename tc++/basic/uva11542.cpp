# include<stdio.h>
# include<string.h>
# include<iostream>
# include<algorithm>
using namespace std;
const int maxn=510;
typedef bool matrix[510][510];

int prime[510],prime_cnt=0;
	bool vis[510];
void get_prime(){
	memset(vis,false,sizeof(vis));
	for(int i=2;i<=500;i++)
		if(!vis[i]){
			for(int j=i*i;j<=500;j+=i){
				vis[j]=true;
			}
			prime[prime_cnt++]=i;
	}
	return;
}


int gaoss(matrix A,int n,int m){//m个方程 n个变量
	/*for(int i=0;i<m;i++){
		for(int j=0;j<=n;j++)
			printf("%d ",A[i][j]);printf("\n");}*/
	int i=0,j=0;
	while(i<n&&j<m){
		int r=j;
		for(int k=j;k<m;k++) if(A[k][i]) {r=k;break;}
		if(A[r][i]){
			if(r!=j)
			for(int k=0;k<=n;k++)
				swap(A[j][k],A[r][k]);
			for(int k=j+1;k<m;k++){
				if(A[k][i]){
					for(int l=i;l<=n;l++)
						A[k][l]^=A[j][l];
				}
			}
			j++;
		}
		i++;
	}
	return n-j;
}

long long a[maxn];
matrix  A;
int main(){
	int T,n;
	get_prime();
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=0;i<n;i++) scanf("%lld",&a[i]);
		int maxp=0;
		memset(A,0,sizeof(A));
		for(int i=0;i<n;i++){
			long long s=a[i];
			for(int j=0;prime[j]<=s;j++){
				if(s%prime[j]==0){
					maxp=max(maxp,j);
					A[j][i]^=1;
					s/=prime[j];j--;
				}
			}
		}
		maxp++;//printf("maxp:%d\n",maxp);
		
		long long ans=(long long)gaoss(A,n,maxp);
		//long long ans_sum=(long long)1<<ans;
		//printf("%lld\n",ans_sum-1);
		cout<<((1LL<<ans)-1)<<endl;
	}
	return 0;
}
