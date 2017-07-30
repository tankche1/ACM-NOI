#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=60000+10,inf=~0U>>2;
int D[maxn];
int main()
{
    //freopen("in","r",stdin);
    fill(D,D+maxn,inf);D[0]=0;
    int N,H,p,c;cin>>N>>H;
    for(int i=0;i<N;i++)
    {
        cin>>p>>c;
        for(int j=p;j<maxn;j++)
			if(D[j]>D[j-p]+c) D[j]=D[j-p]+c;
    }
    int ans=inf;
    for(int j=maxn-1;j>=H;j--)
      if(D[j]<ans) ans=D[j];
    cout<<ans<<endl;
}