#include<cstdio>

#include<iostream>

#include<algorithm>

 

using namespace std;

 

const int MaxN=1<<20;

 

int n,c,m;

int a[MaxN];

 

struct task

{

int L,R,p,ans;

}query[MaxN];

 

struct range

{

int L,R;

}color[MaxN];

 

bool cmp_task_L(task A,task B)

{

return A.L<B.L;

}

 

bool cmp_task_p(task A,task B)

{

return A.p<B.p;

}

 

int tree[MaxN<<1];

 

void init()

{

cin>>n>>c>>m;

for (int i=1;i<=n;++i)

scanf("%d",&a[i]);

for (int i=1;i<=m;++i)

{

scanf("%d%d",&query[i].L,&query[i].R);

query[i].p=i;

}

sort(query+1,query+m+1,cmp_task_L);

}

 

void add(int x,int p)

{

for (int k=x+MaxN-1;k;k>>=1)

tree[k]+=p;

}

 

int get(int k,int L,int R,int x,int y)

{

if (L==x&&R==y)

return tree[k];

int mid=(L+R)>>1;

if (y<=mid)

return get(k<<1,L,mid,x,y);

if (x>mid)

return get(k<<1|1,mid+1,R,x,y);

return get(k<<1,L,mid,x,mid)+get(k<<1|1,mid+1,R,mid+1,y);

}

 

void work()

{

for (int i=1;i<=c;++i)

color[i].L=color[i].R=n+1;

int deal=m;

for (int i=n;i>=1;--i)

{

add(color[a[i]].R,-1);

color[a[i]].R=color[a[i]].L;

color[a[i]].L=i;

add(color[a[i]].R,1);

while (query[deal].L==i)

{

query[deal].ans=get(1,1,MaxN,query[deal].L,query[deal].R);

--deal;

}

}

sort(query+1,query+m+1,cmp_task_p);

for (int i=1;i<=m;++i)

printf("%d\n",query[i].ans);

}

 

int main()

{


init();

work();

return 0;

}
