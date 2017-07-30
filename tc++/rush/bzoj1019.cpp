# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
char s[6];
int operate[6][2];
int num[3][100];
int find(int n){
	memset(num,0,sizeof(num));
	num[0][0]=n;
	for(int i=1;i<=n;i++) num[0][i]=n-i+1;
	int ans=0,last=-1;
	while(1){
		if(num[1][0]==n||num[2][0]==n) break;
		for(int i=0;i<6;i++){
			int x=operate[i][0],y=operate[i][1];
			if(x!=last){
				if(num[x][0]>0&&(num[y][0]==0||num[x][num[x][0]]<num[y][num[y][0]])){
				num[y][++num[y][0]]=num[x][num[x][0]--];
					ans++;
					last=y;
					break;
				}
			}
		}
	}
	return ans;
}
int n;
int dp[40];
int main(){
	scanf("%d",&n);
	for(int i=0;i<6;i++){
		scanf("%s",s);
		operate[i][0]=s[0]-'A';
		operate[i][1]=s[1]-'A';
	}
	for(int i=2;i<=5;i++){
		dp[i]=find(i);
		//printf("dp[%d]:%d\n",i,dp[i]);
	}
	int A,B;
	for(A=1;A<=dp[2];A++){
		B=dp[2]-A;
		//printf("%d %d\n",A,B);
		bool can=true;
		for(int i=3;i<=5;i++)
			if(dp[i-1]*A+B!=dp[i]) {can=false;break;}
		if(can) break;
	}
		//rintf("%d %d\n",A,B);
	long long ans=1;
	for(int i=1;i<n;i++)
		ans=ans*A+B;
	printf("%lld\n",ans);
	return 0;
}
/*
1
BC BA AC CB AB CA
*/
