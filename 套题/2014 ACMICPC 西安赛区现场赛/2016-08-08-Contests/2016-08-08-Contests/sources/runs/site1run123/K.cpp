#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,tot,tt;
ll a,b,ans,hm[1000010];
ll find(ll x)
{
  int l=1,r=tot,res=0;
  while(l<=r)
  {
    int mid=(l+r)>>1;
    if(hm[mid]<=x)
    {
      res=mid;
      l=mid+1;
    }
    else r=mid-1;
  }
  return res;
}
int main()
{
   scanf("%d",&T);
   while(T--)
   {
     scanf("%lld%lld",&a,&b);
     if(a<b) swap(a,b);
     tot=2;hm[1]=a;hm[2]=b;ans=0;
     while(b>1)
     {
       ll t=a-b;
       hm[++tot]=t;
       if(t>b) swap(b,t);
       a=b;b=t;
       if(tot>100000) break;
     }
     sort(hm+1,hm+tot+1);
     tot=unique(hm+1,hm+tot+1)-(hm+1);
     ans=tot;
     if(b==1)
       ans+=a-find(a);
     tt++;cout<<"Case #"<<tt<<": ";
     printf("%lld\n",ans);
  }
  return 0;
}
