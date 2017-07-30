# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n,m;
int x1[110],y1[110],x2[110],y2[110];
int dp[17][17][17][17];
int p[4];
bool bad[17][17][17][17];
int mod=100000;
int main(){
	int tcase,tnum=0;
	scanf("%d",&tcase);
	while(tcase--){
		printf("Case %d: ",++tnum);
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
			scanf("%d%d%d%d",&x1[i],&y1[i],&x2[i],&y2[i]);
			x1[i]--;x2[i]--;//y1[i]--;y2[i]--;
		}
		memset(bad,false,sizeof(bad));
		memset(dp,0,sizeof(dp));
		dp[0][0][0][0]=1;
		for(p[0]=0;p[0]<=n;p[0]++)
			for(p[1]=0;p[1]<=n;p[1]++)
				for(p[2]=0;p[2]<=n;p[2]++)
					for(p[3]=0;p[3]<=n;p[3]++){
						//dp[p[0]][p[1]][p[2]][p[3]]=1;
						for(int j=1;j<=m;j++){
							if((p[x1[j]]>=y1[j])^(p[x2[j]]>=y2[j])){
								bad[p[0]][p[1]][p[2]][p[3]]=1;//,dp[p[0]][p[1]][p[2]][p[3]]=0;break;
							}
						}
					}
		for(int k=1;k<=256;k++){
			for(int num=0;num<4;num++)
				for(p[0]=0;p[0]<=n;p[0]++)
					for(p[1]=0;p[1]<=n;p[1]++)
						for(p[2]=0;p[2]<=n;p[2]++)
							for(p[3]=0;p[3]<=n;p[3]++){
								int &tmp=dp[p[0]][p[1]][p[2]][p[3]];
								if(p[num]){
									p[num]--;tmp+=dp[p[0]][p[1]][p[2]][p[3]];
									if(tmp>=mod) tmp-=mod;
									p[num]++;
								}
							}
			for(p[0]=0;p[0]<=n;p[0]++)
					for(p[1]=0;p[1]<=n;p[1]++)
						for(p[2]=0;p[2]<=n;p[2]++)
							for(p[3]=0;p[3]<=n;p[3]++){
								if(bad[p[0]][p[1]][p[2]][p[3]]) dp[p[0]][p[1]][p[2]][p[3]]=0;
							}
		}
		printf("%05d\n",dp[n][n][n][n]);
	}
	return 0;
}
