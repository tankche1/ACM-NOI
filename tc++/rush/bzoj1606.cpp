#include<iostream>
using namespace std;
const int maxn=50000+10;
bool D[maxn]={1};
int main()
{
    int C,H,x;cin>>C>>H;
    while(H--)
    {
        cin>>x;
        for(int i=C;i>=x;i--)
            if(D[i-x]) D[i]=true;
    }
    for(int i=C;;i--)if(D[i]){cout<<i<<endl;return 0;}
}