# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=210;
const int INF=1000;
int n,be[maxn],en[maxn],T[maxn<<1],cnt=0;
int pre[maxn<<1][maxn],num[maxn<<1][maxn<<1],suc[maxn<<1][maxn],ans[maxn<<1][maxn<<1];

void get_pre(){
	pre[0][0]=0;
	for(int i=1;i<=cnt;i++)
		for(int j=0;j<=n;j++){
			for(int k=0;k<i;k++){
				pre[i][j]=max(pre[i][j],pre[k][j]+num[k][i]);//B
				if(j>=num[k][i]) pre[i][j]=max(pre[i][j],pre[k][j-num[k][i]]);//A
				pre[i][j]=max(pre[i][j],pre[k][j]);//C
			}
			//printf("pre[%d][%d]:%d\n",i,j,pre[i][j]);
		}
	int ans=0;
	for(int j=0;j<=n;j++)
		ans=max(ans,min(j,pre[cnt][j]));
	printf("%d\n",ans);
}

void get_suc(){
	suc[cnt+1][0]=0;
	for(int i=cnt;i>=1;i--)
		for(int j=0;j<=n;j++)
			for(int k=i+1;k<=cnt+1;k++){
				suc[i][j]=max(suc[i][j],suc[k][j]+num[i][k]);//B
				if(j>=num[i][k]) suc[i][j]=max(suc[i][j],suc[k][j-num[i][k]]);//A
				suc[i][j]=max(suc[i][j],suc[k][j]);//C
			}
}

int main(){
	int a,b;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&be[i],&en[i]);en[i]+=be[i];
		T[cnt++]=be[i];T[cnt++]=en[i];
	}
	sort(T,T+cnt);
	cnt=unique(T,T+cnt)-T;
	for(int i=1;i<=n;i++)
		be[i]=lower_bound(T,T+cnt,be[i])-T+1,en[i]=lower_bound(T,T+cnt,en[i])-T+1,num[be[i]][en[i]]++;//,printf("be:%d en:%d\n",be[i],en[i]);
	for(int len=2;len<=cnt;len++)
		for(int i=1;i+len-1<=cnt;i++)
			num[i][i+len-1]+=num[i+1][i+len-1]+num[i][i+len-2]-num[i+1][i+len-2];
	
		/*for(int i=1;i<=cnt;i++)
			for(int j=i;j<=cnt;j++)
				printf("num[%d][%d]:%d\n",i,j,num[i][j]);*/
	for(int i=0;i<=cnt+1;i++)
		for(int j=0;j<=n;j++)
			pre[i][j]=suc[i][j]=-INF;
	get_pre();
	get_suc();
	for(int i=1;i<=cnt;i++)
		for(int j=i;j<=cnt;j++){
			int y=num[j][cnt];
			for(int x=0;x<=num[1][i];x++){
				while(y>=0&&min(num[i][j]+pre[i][x]+suc[j][y],x+y)<=min(num[i][j]+pre[i][x]+suc[j][y-1],x+y-1)) y--;
				ans[i][j]=max(ans[i][j],min(num[i][j]+pre[i][x]+suc[j][y],x+y));
			}
		}
	for(int i=1;i<=n;i++){
		int res=0;
		for(int j=1;j<=be[i];j++)
			for(int k=en[i];k<=cnt;k++)
				res=max(res,ans[j][k]);
		printf("%d\n",res);
	}
	return 0;
}
