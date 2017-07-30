#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<ctime>
 
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<set>
#include<map>
using namespace std;
//Macro
#define rep(i,a,b)  for(int i=a,tt=b;i<=tt;++i)
#define drep(i,a,b) for(int i=a,tt=b;i>=tt;--i)
#define erep(i,e,x) for(int i=x;i;i=e[i].next)
#define irep(i,x)   for(__typeof(x.begin()) i=x.begin();i!=x.end();i++)
#define read()  (strtol(ipos,&ipos,10))
#define sqr(x)  ((x)*(x))
#define pb  push_back
#define PS  system("pause");
typedef long long   ll;
typedef pair<int,int> pii;
const int oo=~0U>>1;
const double inf=1e100;
const double eps=1e-6;
string name="", in=".in", out=".out";
//Var
int n,l,m,tmp,cnt,ans,p[1000008],f[1000008];
void Work()
{
    scanf("%d%d",&n,&l);
    rep(i,1,n)
    {
        scanf("%d",&m);cnt=0;tmp=0;
        rep(i,1,(int)sqrt((double)m))if(m%i==0)
        {
            if(i>=l)p[++cnt]=i;
            if(m/i>=l)p[++cnt]=m/i;
        }
        rep(i,1,cnt)tmp=max(f[p[i]],tmp);tmp++;
        rep(i,1,cnt)f[p[i]]=tmp;
    }
    rep(i,1,100000)ans=max(ans,f[i]);
    cout<<ans<<endl;
}
int main(){
//  freopen((name+in).c_str(),"r",stdin);
//  freopen((name+out).c_str(),"w",stdout);
//  Init();
    Work();
    return 0;
}
