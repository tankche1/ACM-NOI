# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10;
const int maxd=1000;
typedef long long LL;

char s[maxn+10];
LL dp[1<<maxn][maxd];
int num[maxn];

inline int suk(int a){
	int ans=1;
	for(int i=1;i<=a;i++)
		ans*=i;
	return ans;
}

int T,d;
int main(){
	scanf("%d",&T);
	while(T--){//s[0]='a';
		scanf(" %s%d",s,&d);
		int n=strlen(s),ans=1;
		memset(num,0,sizeof(num));
		for(int i=0;i<n;i++)
			num[s[i]-'0']++;
		for(int i=0;i<10;i++)
			if(num[i])
			ans=ans*suk(num[i]);
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		for(int i=1;i<(1<<n);i++){
			for(int j=0;j<n;j++)
				if(i&(1<<j)){
					int last=i^(1<<j);
					for(int k=0;k<d;k++)
						if(dp[last][k])
							dp[i][(k*10+(s[j]-'0'))%d]+=dp[last][k];
				}
		}
		printf("%d\n",(int)(dp[(1<<n)-1][0]/ans));
	}
	return 0;
}
//75618198 388