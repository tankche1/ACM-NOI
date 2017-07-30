#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define LL long long
using namespace std;
char ch;
int N,M,m,Test,Q,len,l,r,x,y,ans;
int q[12];
int a[10010];
class rec{
	public:
	LL a[12],rest;
	void get(int x){
		memset(a,0,sizeof(a));rest=0;
		if (!x)return;
		for (int i=0;i<len;i++)
		while (x%q[i]==0)a[i]++,x/=q[i];
		rest=x;
	}
}num,res;
class segleaf{
	public:
	rec s,mark;
}seg[200010];
inline int exgcd(int a,int b,int &x,int &y){
	if (!b){
		x=1;y=0;
		return a;
	}
	int xx,yy;
	int d=exgcd(b,a%b,xx,yy);
	x=yy%b;
	if (x<0)x+=b;
	y=((LL)d-(LL)a*x)/b;
	return d;
}
inline int quick(int x,LL y){
	if (x==1)return 1;
	if (x==0)return 0;
	int s=1,t=x;
	for (;y;y>>=1){
		if (y&1)s=(LL)s*t%M;
		t=(LL)t*t%M;
	}
	return s;
}
inline void build(int x,int l,int r){
	if (l==r){
		seg[x].s.get(a[l]);
		seg[x].mark.get(1);
	}else{
		int mid=(l+r)>>1;
		build(x<<1,l,mid);
		build((x<<1)+1,mid+1,r);
		for (int i=0;i<len;i++)seg[x].s.a[i]=seg[x<<1].s.a[i]+seg[(x<<1)+1].s.a[i];
		seg[x].s.rest=(LL)seg[x<<1].s.rest*seg[(x<<1)+1].s.rest%M;
		seg[x].mark.get(1);
	}
}
inline void make(int x,int l,int r){
	int mid=(l+r)>>1;
	for (int i=0;i<len;i++)
	if (seg[x].mark.a[i]){
		if (l<r){
			seg[x<<1].s.a[i]+=seg[x].mark.a[i]*(mid-l+1);
			seg[x<<1].mark.a[i]+=seg[x].mark.a[i];
			seg[(x<<1)+1].s.a[i]+=seg[x].mark.a[i]*(r-mid);
			seg[(x<<1)+1].mark.a[i]+=seg[x].mark.a[i];
		}
		seg[x].mark.a[i]=0;
	}
	if (seg[x].mark.rest!=1){
		if (l<r){
			seg[x<<1].s.rest=(LL)seg[x<<1].s.rest*quick(seg[x].mark.rest,mid-l+1)%M;
			seg[x<<1].mark.rest=(LL)seg[x<<1].mark.rest*seg[x].mark.rest%M;
			seg[(x<<1)+1].s.rest=(LL)seg[(x<<1)+1].s.rest*quick(seg[x].mark.rest,r-mid)%M;
			seg[(x<<1)+1].mark.rest=(LL)seg[(x<<1)+1].mark.rest*seg[x].mark.rest%M;
		}
		seg[x].mark.rest=1;
	}
}
inline void Init(int x,int l,int r,int ll,int rr,const rec &t){
	make(x,l,r);
	if (l==ll&&r==rr){
		seg[x].mark=t;
		for (int i=0;i<len;i++)
			seg[x].s.a[i]+=t.a[i]*(r-l+1);
		seg[x].s.rest=(LL)seg[x].s.rest*quick(t.rest,r-l+1)%M;
		return;
	}
	int mid=(l+r)>>1;
	if (rr<=mid)Init(x<<1,l,mid,ll,rr,t);
	else if (ll>mid)Init((x<<1)+1,mid+1,r,ll,rr,t);
	else Init(x<<1,l,mid,ll,mid,t),Init((x<<1)+1,mid+1,r,mid+1,rr,t);
	for (int i=0;i<len;i++)seg[x].s.a[i]=seg[x<<1].s.a[i]+seg[(x<<1)+1].s.a[i];
	seg[x].s.rest=(LL)seg[x<<1].s.rest*seg[(x<<1)+1].s.rest%M;
}
inline void ask(int x,int l,int r,int ll,int rr){
	make(x,l,r);
	if (l==ll&&r==rr){
		res.rest=(LL)res.rest*seg[x].s.rest%M;
		for (int i=0;i<len;i++)
			res.a[i]+=seg[x].s.a[i];
		return;
	}
	int mid=(l+r)>>1;
	if (rr<=mid)ask(x<<1,l,mid,ll,rr);
	else if (ll>mid)ask((x<<1)+1,mid+1,r,ll,rr);
	else ask(x<<1,l,mid,ll,mid),ask((x<<1)+1,mid+1,r,mid+1,rr);
}
int main(){
    scanf("%d",&Test);
    for (int tt=1;tt<=Test;tt++){
    	printf("Case #%d: \n",tt);
    	scanf("%d",&N);scanf("%d",&M);
    	len=0;m=M;
    	for (int j=2;j*j<=M;j++)
    	if (m%j==0){
    		q[len++]=j;
    		while (m%j==0)m/=j;
    	}
    	if (m>1)q[len++]=m;
    	for (int i=1;i<=N;i++)scanf("%d",&a[i]);
    	build(1,1,N);
    	scanf("%d",&Q);
    	for (int i=1;i<=Q;i++){
    		scanf("\n%c",&ch);
    		if (ch=='Q'){
    			scanf("%d",&l);scanf("%d",&r);
    			res.get(1);
    			ask(1,1,N,l,r);
    			ans=res.rest;
				if (ans){
					for (int i=0;i<len;i++)
					ans=(LL)ans*quick(q[i],res.a[i])%M;
				}
    			printf("%d\n",ans);
    		}else if (ch=='M'){
    			scanf("%d",&l),scanf("%d",&r),scanf("%d",&x);
    			num.get(x);
    			Init(1,1,N,l,r,num);
    		}else if (ch=='D'){
    			scanf("%d",&l),scanf("%d",&r),scanf("%d",&x);
    			num.get(x);
    			for (int j=0;j<len;j++)num.a[j]=-num.a[j];
    			exgcd(num.rest,M,x,y);
    			num.rest=x;
    			Init(1,1,N,l,r,num);
    		}
    	}
    }
}
