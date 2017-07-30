#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>
using namespace std;
#define LL long long

int Test,N,M,pt,last;
bool ans[100010];
int st[1000010],ne[8000010],go[8000010];
void Add(int x,int y){ne[++pt]=st[x];st[x]=pt;go[pt]=y;}
class line{public:int x,y;}P[100010];
class hisnode{public:int pos,x,c;}his[5000010];
class UnionFind{
	public:
	int x;
	bool c;
	void getdata(int xx,int cc){x=xx;c=cc;}
}f[100010];

int getop(int x){
	if (f[x].x==x)return x;
	++last;
	his[last].pos=x;
	his[last].x=f[x].x;
	his[last].c=f[x].c;
	int t=f[x].x;
	f[x].x=getop(f[x].x);
	f[x].c^=f[t].c;
	return f[x].x;
}

void Union(int x,int y){
	int xx=getop(x);
	int yy=getop(y);
	++last;
	his[last].pos=yy;
	his[last].x=f[yy].x;
	his[last].c=f[yy].c;
	f[yy].x=xx;
	f[yy].c=1^f[x].c^f[y].c;
}

void build(int x,int l,int r){
	st[x]=0;
	if (l==r)return;
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build((x<<1)+1,mid+1,r);
}

void cover(int x,int l,int r,int ll,int rr,int data){
	if (l==ll&&r==rr){
		Add(x,data);
		return;
	}
	int mid=(l+r)>>1;
	if (rr<=mid)cover(x<<1,l,mid,ll,rr,data);
	else if (ll>mid)cover((x<<1)+1,mid+1,r,ll,rr,data);
	else cover(x<<1,l,mid,ll,mid,data),cover((x<<1)+1,mid+1,r,mid+1,rr,data);
}

void work(int x,int l,int r){
	int ll=last;
	for (int i=st[x];i;i=ne[i]){
		int y=go[i];
		if (getop(P[y].x)!=getop(P[y].y))
			Union(P[y].x,P[y].y);
			else
				if (f[P[y].x].c==f[P[y].y].c){
					for (int i=last;i>ll;i--){
						int x=his[i].pos;
						f[x].x=his[i].x;
						f[x].c=his[i].c;
					}
					last=ll;
					for (int j=l;j<=r;j++)ans[j]=0;
					return;
				}
	}
	if (l<r){
		int mid=(l+r)>>1;
		work(x<<1,l,mid);
		work((x<<1)+1,mid+1,r);
	}

	for (int i=last;i>ll;i--){
		int x=his[i].pos;
		f[x].x=his[i].x;
		f[x].c=his[i].c;
	}
	last=ll;
}

int main(){
	//freopen("e.in","r",stdin);
	//freopen("std.out","w",stdout);
	scanf("%d",&Test);
	while (Test--){
		scanf("%d%d",&N,&M);
		build(1,1,N);pt=0;
		for (int i=1;i<=M;i++){
			scanf("%d%d",&P[i].x,&P[i].y);
			if (P[i].x>P[i].y)swap(P[i].x,P[i].y);
			if (P[i].x>1)cover(1,1,N,1,P[i].x-1,i);
			if (P[i].x+1<P[i].y)cover(1,1,N,P[i].x+1,P[i].y-1,i);
			if (P[i].y<N)cover(1,1,N,P[i].y+1,N,i);
		}
		for (int i=1;i<=N;i++)f[i].getdata(i,0);
		for (int i=1;i<=N;i++)ans[i]=1;
		last=0;
		work(1,1,N);
		for (int i=1;i<=N;i++)if (ans[i])printf("1");else printf("0");
		printf("\n");
	}
}
