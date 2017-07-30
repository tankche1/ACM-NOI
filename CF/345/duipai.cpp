#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <ctime>
#define ll long long
#define maxn 1000010
#define maxm 400010
#define modd 1000000007
#define inf 0x7fffffff
#define eps 1e-7
#define imax(x,y)(x>y)?x:y
#define imin(x,y)(x<y)?x:y

using namespace std;

int n,m,a[maxm],num=0,sor[maxm+maxm],fn[maxm],fp[maxm],fl[maxm],fr[maxm];

struct node
{
    int a,b,l,r,max,mid,sum;
};

struct par
{
    int max,sum;
};

class ftree
{
    public:
	node t[maxn];
	int rootnum,root[maxm],tot;
	int build(int l,int r)
	{
	    int now=tot++;
	    t[now].a=l;t[now].b=r;
	    t[now].max=t[now].sum=0;
	    if (l+1==r)return now;
	    t[now].mid=(l+r)/2;
	    t[now].l=build(l,t[now].mid);
	    t[now].r=build(t[now].mid,r);
	    return now;
	}
	void Build(int l,int r)
	{
	    root[0]=build(l,r);
	    rootnum=1;
	}
	int insert(int pos,int c,int sum,int x)
	{
	    int now=tot++;
	    t[now]=t[x];
	    if (t[x].a+1==t[x].b)
	    {
		if (t[x].max==c)t[now].sum+=sum;else t[now].sum=sum;
		if (t[now].sum>=modd)t[now].sum%=modd;
		t[now].max=c;
		return now;
	    }
	    if (t[x].mid<=pos)t[now].r=insert(pos,c,sum,t[x].r);else t[now].l=insert(pos,c,sum,t[x].l);
	    t[now].max=max(t[t[now].l].max,t[t[now].r].max);
	    t[now].sum=0;
	    if (t[now].max==t[t[now].l].max)t[now].sum+=t[t[now].l].sum;
	    if (t[now].max==t[t[now].r].max)t[now].sum+=t[t[now].r].sum;
	    if (t[now].sum>=modd)t[now].sum%=modd;
	    return now;
	}
	void Insert(int pos,int c,int sum)
	{
	    root[rootnum]=insert(pos,c,sum,root[rootnum-1]);
	    rootnum++;
	}
	par query(int l,int r,int x)
	{
	    par tmp;
	    if (t[x].a>=l&&t[x].b<=r)
	    {
		tmp.max=t[x].max;
		tmp.sum=t[x].sum;
		return tmp;
	    }
	    int ans=0,sum=0;
	    if (t[x].mid>l)
	    {
		tmp=query(l,r,t[x].l);
		if (tmp.max==ans)sum+=tmp.sum;
		if (tmp.max>ans)sum=tmp.sum,ans=tmp.max;
	    }
	    if (t[x].mid<r)
	    {
		tmp=query(l,r,t[x].r);
		if (tmp.max==ans)sum+=tmp.sum;
		if (tmp.max>ans)sum=tmp.sum,ans=tmp.max;
	    }
	    if (sum>=modd)sum%=modd;
	    tmp.max=ans;
	    tmp.sum=sum;
	    return tmp;
	}
	par Query(int l,int r)
	{
	    return query(l,r,root[rootnum-1]);
	}
	par Query(int l,int r,int num)
	{
	    return query(l,r,root[num]);
	}
};

struct que
{
    int a,b;
}q[maxm];


map <int,int>ind;

int main()
{
    scanf("%d %d",&n,&m);
    for (int i=0;i<n;i++)
    {
	scanf("%d",&a[i]);
	sor[i]=a[i];
    }
    for (int i=0;i<m;i++)
    {
	scanf("%d%d",&q[i].a,&q[i].b);
	sor[i+n]=q[i].b;
	--q[i].a;
    }
    sort(sor,sor+n+m);
    for (int i=0;i<n+m-1;i++)
	if (sor[i]!=sor[i+1])
	{
	    ind[sor[i]]=num;
	    sor[num++]=sor[i];
	}
    if (n+m>1&&sor[n+m-1]!=sor[n+m-2])
    {
	ind[sor[n+m-1]]=num;
	sor[num++]=sor[n+m-1];
    }
    ftree nex,pre;
    nex.Build(0,num);
    pre.Build(0,num);
    nex.Insert(ind[a[0]],fn[0]=1,fr[0]=1);
    int ans=1;par tmp;
    for (int i=1;i<n;i++)
    {
	int pos=ind[a[i]];
	if (pos)
	{
	    tmp=nex.Query(0,pos);
	    fn[i]=tmp.max+1;
	    fr[i]=tmp.sum;
	}
	else
	    fn[i]=fr[i]=1;
	nex.Insert(pos,fn[i],fr[i]);
	ans=max(ans,fn[i]);
    }
    pre.Insert(ind[a[n-1]],fp[n-1]=1,fl[n-1]=1);
    int pos;
    for (int i=n-2;i>=0;i--)
    {
	pos=ind[a[i]];
	if (pos!=num-1)
	{
	    tmp=pre.Query(pos+1,num);
	    fp[i]=tmp.max+1;
	    fl[i]=tmp.sum;
	}
	else
	    fp[i]=fl[i]=1;
	pre.Insert(pos,fp[i],fl[i]);
    }
    int cnt=0;
    for (int i=0;i<n;i++)
	if (fn[i]==ans)
	{
	    cnt+=fr[i];
	    if (cnt>=modd)cnt%=modd;
	}
    int anss;
    par tmp1,tmp2;
    for (int i=0;i<m;i++)
    {
	int id=ind[q[i].b];
	if (q[i].a!=0&&id!=0)tmp1=nex.Query(0,id,q[i].a);else tmp1.max=0;
	if (q[i].a!=n-1&&id!=num-1)tmp2=pre.Query(id+1,num,n-1-q[i].a);else tmp2.max=0;
	anss=tmp1.max+tmp2.max+1;
	if (anss>=ans){printf("%d\n",anss);continue;}
	if (fp[q[i].a]+fn[q[i].a]!=ans+1)printf("%d\n",ans);
	else
	{
	    ll tmpp=((ll)fl[q[i].a]*(ll)fr[q[i].a])%modd;
	    if (tmpp==cnt)printf("%d\n",ans-1);
	    	     else printf("%d\n",ans);
	}
    }
    return 0;
}
