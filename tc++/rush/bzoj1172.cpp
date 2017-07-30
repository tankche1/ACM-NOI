# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=205;
const int maxm=10005;
const int maxk=200010;
const int maxw=1000000;
int n,m,k,l;
int p[305];
int Div[maxw+5];
int dp[2][305];
int c1[305],c2[305];
int next[305][305];
inline void Add(int &x,int a){
	x+=a;if(x>=l) x%=l;
}
int main(){
	int x;
	scanf("%d%d%d%d",&n,&m,&k,&l);
	p[0]=0;
	for(int i=1;i<=k;i++)
		if(k%i==0) p[++p[0]]=i;
	//sort(p+1,p+p[0]+1);//puts("shit");
	for(int i=1;i<=p[0];i++){
		int x=p[i];//printf("%d\n",p[i]);
		for(int j=x;j<=maxw;j+=x) Div[j]=i;
	}//puts("shit");
	for(int i=1;i<=p[0];i++)
		for(int j=1;j<=i;j++){
			for(int ll=p[0];ll>=1;ll--)
				if((long long)(p[i])*p[j]%p[ll]==0)
				{next[i][j]=next[j][i]=ll;break;}
		}
	memset(dp,0,sizeof(dp));
	for(int j=1;j<=m;j++)
		scanf("%d",&x),Add(dp[0][Div[x]],1);
	int now=1,nex;
	for(int i=2;i<=n;i++){
		now=!now;nex=!now;memset(dp[nex],0,sizeof(dp[nex]));
		memset(c1,0,sizeof(c1));memset(c2,0,sizeof(c2));
		for(int j=0;j<m;j++)
			scanf("%d",&x),Add(c1[Div[x]],1);
		memcpy(c2,c1,sizeof(c1));
		if(i!=n)
			for(int a=1;a<=p[0];a++)
				for(int b=1;b<=a;b++)
					if(a!=b) Add(c2[next[a][b]],c1[a]*c1[b]*2);
						else Add(c2[next[a][b]],c1[a]*(c1[a]-1));
		for(int a=1;a<=p[0];a++)
		for(int b=1;b<=p[0];b++)
			Add(dp[nex][next[a][b]],dp[now][a]*c2[b]);
	}
	printf("%d\n",dp[nex][p[0]]);
	return 0;
}
