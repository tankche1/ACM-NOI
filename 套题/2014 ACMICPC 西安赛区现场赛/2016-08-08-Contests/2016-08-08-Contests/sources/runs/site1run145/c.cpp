#include <bits/stdc++.h>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define eps 1e-8

using namespace std;

const int maxn = 100005;
const int maxm = 200005;
int n,m,A[maxn],link[maxn][2],deg[maxn];
int a[maxn],b[maxm],c[maxm],source,sink,tot;
double d[maxm];
int lab[maxn],Q[maxn];

bool bfs()
{
	int st,en;
	Q[st=en=1] = source;
	fo(i,1,sink) lab[i] = -1;
	lab[source] = 0;
	while (st <= en)
	{
		int x = Q[st];
		for (int i = a[x];i;i = c[i])
			if (d[i] > eps && lab[b[i]] == -1)
			{
				lab[b[i]] = lab[x] + 1;
				Q[++en] = b[i];
			}
		st ++;
	}
	return lab[sink] > -1;
}

double dfs(int x,double flow)
{
	if (x == sink) return flow;
	double ret = 0.0;
	for (int i = a[x];i;i = c[i])
		if (d[i] > eps && lab[b[i]] == lab[x] + 1)
		{
			double now = dfs(b[i],min(flow,d[i]));
			d[i] -= now, d[i^1] += now;
			flow -= now, ret += now;
			if (flow < eps) return ret;
		} 
	lab[x] = -1;
	return ret;
}

void Add(int x,int y,double lim)
{
	tot ++;
	b[tot] = y;
	c[tot] = a[x];
	d[tot] = lim;
	a[x] = tot;
	tot ++;
	b[tot] = x;
	c[tot] = a[y];
	d[tot] = 0.0;
	a[y] = tot;
}

bool Check(double mid)
{
	source = n+1, sink = n+2;
	fo(i,1,sink) a[i] = 0;
	tot = 1;
	fo(i,1,m)
	{
		Add(link[i][0],link[i][1],1);
		Add(link[i][1],link[i][0],1);
	}
	fo(i,1,n) Add(source,i,m);
	fo(i,1,n) Add(i,sink,m+2*mid-deg[i]);
	double maxflow = 0.0;
	while (bfs()) maxflow += dfs(source,1e100);
	if ((double)m*n-maxflow > eps) return 1;
	return 0;
}

int T;

int main()
{
	//freopen("c.in","r",stdin);
	//freopen("c.out","w",stdout);
	scanf("%d",&T);
	for (int cas = 1;cas <= T;cas ++)
	{
		scanf("%d",&n);
		fo(i,1,n) scanf("%d",&A[i]);
		m = 0;
		fo(i,1,n) deg[i] = 0;
		fo(i,1,n)
			fo(j,i+1,n)
				if (A[i] > A[j])
				{
					m ++;
					link[m][0] = i, link[m][1] = j;
					deg[i] ++, deg[j] ++;
				}
		double L = 0.0, R = m;
		while (R - L > eps)
		{
			double mid = (L + R) * 0.5;
			if (Check(mid)) L = mid;
			else R = mid;
		}
		printf("Case #%d: %.8lf\n",cas,L);
	}
	return 0;
}
