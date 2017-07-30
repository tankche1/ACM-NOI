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
stack<int> s;
int n,num[1000008],l[1000008],r[1000008],ans;
void Work()
{
    scanf("%d",&n);
    rep(i,1,n)scanf("%d",&num[i]);  
    num[0]=num[n+1]=oo;s.push(0);
    rep(i,1,n)
    {
        while(num[i]>num[s.top()])s.pop();
        l[i]=s.top()+1;
        s.push(i);
    }
    while(!s.empty())s.pop();
    s.push(n+1);
    drep(i,n,1)
    {
        while(num[i]>num[s.top()])s.pop();
        r[i]=s.top()-1; 
        s.push(i);
    }
    rep(i,1,n)
    {
        if(r[i]-l[i]+1>=num[i])
            ans=max(ans,num[i]);
    }
    printf("%d\n",ans);
}
int main()
{
//  freopen((name+in).c_str(),"r",stdin);
//  freopen((name+out).c_str(),"w",stdout);
//  Init();
	1
    Work();
    return 0;
}