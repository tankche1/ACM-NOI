#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cstring>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
using namespace std;
const int inf=~0U>>1;
const int maxn=100+1,maxd=16;
int n,d;
long long dp[maxd][maxn]={0};
int main()
{
cin>>n>>d;
rep(i,n+1)dp[1][i]=i*2;dp[1][0]=1;
for(int i=2;i<=d;i++)
{
dp[i][0]=1;
for(int j=1;j<=n;j++)
dp[i][j]=dp[i][j-1]+dp[i-1][j-1];
}
cout<<dp[d][n]<<endl;
}
