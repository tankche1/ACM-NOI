# include<stdio.h>
# include<string.h>
# include<algorithm>
//# define range(a,b) (b-a+1)
using namespace std;
const int maxn=210;
const int INF=1000000000;
int n;
int t[maxn],d[maxn];
int ans;
int dp[maxn][maxn][2],solve[maxn][maxn][2];
int a[maxn],b[maxn];
void print(int L,int R,int now){
	if(L==R) {printf("%d ",now);puts("");return;}
	printf("%d ",now);
	if(L==now&&solve[L][R][L==now]==L) print(L+1,R,L+1);
	else if(L==now&&solve[L][R][L==now]==R) print(L+1,R,R);
	else if(R==now&&solve[L][R][L==now]==R) print(L,R-1,R-1);
	else print(L,R-1,L);
}

int dfs(int L,int R,int now){
	int ti;
	//printf("L:%d R:%d now:%d\n",L,R,now);
	if(dp[L][R][L==now]!=-1) return dp[L][R][L==now];
	int &tmp=dp[L][R][L==now];tmp=INF;
	if(L==R) {return tmp=0;}
	if(L==now){
		if(dfs(L+1,R,L+1)+d[L+1]-d[L]<t[L]) {
			if(dfs(L+1,R,L+1)+d[L+1]-d[L]<tmp) tmp=dfs(L+1,R,L+1)+d[L+1]-d[L],solve[L][R][L==now]=L;
		}
		if(L+1!=R){
			ti=dfs(L+1,R,R);
				if(ti+d[R]-d[L]<t[L]){
			if(ti+d[R]-d[L]<tmp) tmp=ti+d[R]-d[L],solve[L][R][L==now]=R;
			}
		}
	}
	else{
		if(dfs(L,R-1,R-1)+d[R]-d[R-1]<t[R]){
			if(dfs(L,R-1,R-1)+d[R]-d[R-1]<tmp) tmp=dfs(L,R-1,R-1)+d[R]-d[R-1],solve[L][R][L==now]=R;//,a[n-(R-L+1)+1]=R;
		}
		if(L+1!=R){
			ti=dfs(L,R-1,L);
			if(ti+d[R]-d[L]<t[R]){
				if(ti+d[R]-d[L]<tmp) tmp=ti+d[R]-d[L],solve[L][R][L==now]=L;//,a[n-(R-L+1)+1]=L;
			}
		}
	}
	//printf("L:%d R:%d now:%d tmp:%d\n",L,R,now,tmp);
	return tmp;
}

int main(){
	int ans,ok;
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++)
			scanf("%d",&t[i]);
		for(int i=1;i<=n;i++)
			scanf("%d",&d[i]);
		memset(dp,-1,sizeof(dp));
		
		ans=dfs(1,n,1);ok=1;
		if(ans>dfs(1,n,n)) ans=dfs(1,n,n),ok=n;
		if(ans==INF) puts("Mission Impossible");
		else{
			print(1,n,ok);//puts("");
		}
		/*if(dfs(1,n,1)==INF&&dfs(1,n,n)==INF)puts("Mission Impossible");
		else
		{
			if(dfs(1,n,n)<INF)ok=n;
			else ok=1;
			print(1,n,ok);
		}*/
	}
	return 0;
}
