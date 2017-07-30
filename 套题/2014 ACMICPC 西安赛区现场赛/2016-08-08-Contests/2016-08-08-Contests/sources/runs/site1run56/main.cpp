#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
LL n,m,ans,TEST;
void gcd(LL a,LL b){
    if (b>a) swap(a,b);
    if (b==0)return;
    if (a%b!=0) {ans+=a/b;gcd(b,a%b);}
    else {ans+=a/b-1;return;}
}
void work(){
    cin>>n>>m;
    if (n!=m) ans=2;
    else ans=1;
    gcd(n,m);
    cout<<ans<<endl;
}
int main(){
    cin>>TEST;
    for (int i=1;i<=TEST;++i){
        cout<<"Case #"<<i<<": ";
        work();
    }
}
