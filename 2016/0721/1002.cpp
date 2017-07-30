#pragma comment(linker, "/STACK:1024000000,1024000000")
#include<cmath>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<stack>
using namespace std;
const int P=1000000007;
const int maxn=(1<<16)+10;
const int S=1<<8;
unsigned Tr[maxn+S+10][S];int cnt=0;
unsigned *new_array(int size,unsigned *scr=NULL)
{
	if(scr==NULL)
	{
		memset(Tr[cnt],-1,sizeof(unsigned)*size);
	}
	else
	{
		memcpy(Tr[cnt],scr,sizeof(unsigned)*size);
	}
	return Tr[cnt++];
}
int op;
unsigned f[maxn];
bool vis[maxn];
int n,w[maxn];
unsigned *dp[S+10],*backup[maxn];
char s[10];
int head[maxn],tail=0;
struct E
{
	int v,next;
}e[maxn];
void add(int u,int v)
{
	e[tail].v=v;
	e[tail].next=head[u];
	head[u]=tail++;
}
int opt(int a,int b)
{
	if(op==2)return a&b;
	else if(op==1)return a|b;
	return a^b;
}
stack<int>q;
void dfs(int x)
{
	while(!q.empty())q.pop();
	q.push(x);
	while(!q.empty())
	{
		int u=q.top();q.pop();
		int a=w[u]>>8,b=w[u]&255;
		if(!vis[u])
		{
			vis[u]=true;
			q.push(u);
			f[u]=0;
			for(int i=0;i<S;i++)
			{
				//if(cnt==18829)cerr<<"#"<<(&dp[i][0]-&Tr[0][0])/S<<endl;
				if(dp[i][a]==-1)continue;
				if(dp[i][a]+opt(i,b)>f[u])f[u]=dp[i][a]+opt(i,b);
			}
			//printf("dp[%d]:%u\n",u,f[u]);
			backup[u]=dp[b];
			dp[b]=new_array(S,dp[b]);
			for(int i=0;i<S;i++)
			{
				if(dp[b][i]==-1||dp[b][i]<f[u]+(opt(a,i)<<8))dp[b][i]=f[u]+(opt(a,i)<<8);
			}
			for(int i=head[u];i!=-1;i=e[i].next)
			{
				int v=e[i].v;
				q.push(v);
			}
		}
		else
			dp[b]=backup[u];
	}
}
int main()
{
	freopen("1002.in","r",stdin);
	freopen("output.a","w",stdout);
	int T;scanf("%d",&T);
	int TT=0;
	while(T--)
	{
		cnt=0;
		scanf("%d",&n);
		scanf("%s",s);
		op=(s[0]=='A')?2:(s[0]=='O');
		for(int i=1;i<=n;i++)scanf("%d",&w[i]);
		memset(head,-1,sizeof(head));tail=0;
		for(int i=2;i<=n;i++)
		{
			int u;scanf("%d",&u);
			add(u,i);
		}
		for(int i=0;i<S;i++)dp[i]=new_array(S);
		memset(vis,0,sizeof(vis));
		dfs(1);
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			//cerr<<i<<":"<<f[i]<<endl;
			f[i]+=w[i];f[i]%=P;//cerr<<i<<":"<<f[i]<<endl;
			ans=(ans+1LL*f[i]*i%P)%P;
		}
		printf("%d:%d\n",++TT,ans);
	}
	return 0;
}
