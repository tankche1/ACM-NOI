# include<stdio.h>
# include<string.h>
typedef long long LL;
const int maxm=100010;
const int maxn=10010;
int n,m;
int a[maxn],b[maxn];
LL ans=0;
int main()
{
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	int x,y;
	memset(a,0,sizeof(a));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&x,&y),a[x]++,a[y]++;
	ans=m*2;
	for(int i=1;i<=n;i++)
		ans=ans+(LL)a[i]*(a[i]-1);
	printf("%I64d\n",ans);
	return 0;
}
