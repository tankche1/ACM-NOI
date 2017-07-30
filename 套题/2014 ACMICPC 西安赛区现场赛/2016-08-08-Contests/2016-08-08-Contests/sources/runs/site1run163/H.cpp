#include <bits/stdc++.h>
using namespace std;

const int MaxN = 107;
const int MaxM = 20007;

int T,id,n,m,out[MaxN],cnt[MaxN][MaxN][2];
bool g[MaxN][MaxN];
int f[MaxN][MaxN][2],l,r,q[MaxM][3];

inline void Updata(int a,int b,int c,int d)
{
	r++; f[a][b][c] = d;
	q[r][0] = a; q[r][1] = b; q[r][2] = c;
}

void Init()
{
	int i,j,a,b;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) out[i] = 0;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			g[i][j] = false, f[i][j][0] = f[i][j][1] = -1,
			cnt[i][j][0] = cnt[i][j][1] = 0;
	l = 1; r = 0;
	for(i=1;i<=m;i++)
		scanf("%d%d",&a,&b),
		out[a]++,g[a][b] = true;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
		{
			if(i==j)
			{
				Updata(i,j,0,1); Updata(i,j,1,1);
				continue;
			}
			if(out[i]==0) Updata(i,j,0,1);
			if(out[j]==0) Updata(i,j,1,0);
		}
}

void Solve()
{
	int x,y,flg,u;
	while(l<=r)
	{
		x = q[l][0]; y = q[l][1]; flg = q[l][2];
		//printf("%d %d %d  %d \n",x,y,flg,f[x][y][flg]);
		if(flg==0)
		{
			if(f[x][y][0]==1)
			{
				for(u=1;u<=n;u++)
					if(g[u][y] && f[x][u][1] == -1) Updata(x,u,1,1);
			}
			else
			{
				for(u=1;u<=n;u++)
					if(g[u][y] && f[x][u][1] == -1)
					{
						cnt[x][u][1]++;
						if(cnt[x][u][1]==out[u]) Updata(x,u,1,0);
					}
			}
		}
		else
		{
			if(f[x][y][1]==0)
			{
				for(u=1;u<=n;u++)
					if(g[u][x] && f[u][y][0] == -1) Updata(u,y,0,0);
			}
			else
			{
				for(u=1;u<=n;u++)
					if(g[u][x] && f[u][y][0] == -1)
					{
						cnt[u][y][0]++;
						if(cnt[u][y][0]==out[u]) Updata(u,y,0,1);
					}
			}
		}
		l++;
	}
	scanf("%d%d",&x,&y);
	if(f[x][y][0] == 1) printf("No\n");
	else printf("Yes\n");
}

int main()
{
//	freopen("H.in","r",stdin);
//	freopen("H.out","w",stdout);
	
	scanf("%d",&T);
	for(id=1;id<=T;id++)
	{
		printf("Case #%d: ",id);
		Init();
		Solve();
	}
	return 0;
}
