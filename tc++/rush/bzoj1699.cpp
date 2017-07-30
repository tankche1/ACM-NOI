#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cstring>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
using namespace std;
const int inf=~0U>>1,maxn=50000;
struct info
{
    int Max,Min;
    info(int x=0,int y=0):Max(x),Min(y){}
};
info T[maxn*3],none(-inf,inf);
info operator+(const info&l,const info&r)
{
    return info(max(l.Max,r.Max),min(l.Min,r.Min));
}
int A[maxn],n,q;
void build(int t,int l,int r)
{
    if(l+1==r){T[t]=info(A[l],A[l]);return;}
    build(t*2,l,(l+r)/2);
    build(t*2+1,(l+r)/2,r);
    T[t]=T[t*2]+T[t*2+1];
}
info ask(int t,int l,int r,int a,int b)
{
    if(a>=r||b<=l)return none;
    if(l>=a&&r<=b)return T[t];
    return ask(t*2,l,(l+r)/2,a,b)+ask(t*2+1,(l+r)/2,r,a,b);
}
int main()
{
    //freopen("in","r",stdin);
    scanf("%d %d",&n,&q);
    rep(i,n) scanf("%d",A+i);
    build(1,0,n);int l,r;info a;
    rep(i,q)scanf("%d %d",&l,&r),a=ask(1,0,n,l-1,r),printf("%d\n",a.Max-a.Min);
}
