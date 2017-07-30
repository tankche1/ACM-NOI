#include<iostream>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
const int maxn=2600,inf=~0U>>1;
typedef long long ll;
ll Dp[maxn],M[maxn];
int n;
int main()
{
    //freopen("in","r",stdin);
    cin>>n;cin>>M[0];
    rep(i,n)cin>>M[i+1],M[i+1]+=M[i];
    Dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        ll&x=Dp[i]=inf;
        for(int j=1;j<=i;j++)
			if(x>Dp[i-j]+M[j]+M[0]) x=Dp[i-j]+M[j]+M[0];
            //x<?=Dp[i-j]+M[j]+M[0];
    }
    cout<<Dp[n]-M[0]<<endl;
}