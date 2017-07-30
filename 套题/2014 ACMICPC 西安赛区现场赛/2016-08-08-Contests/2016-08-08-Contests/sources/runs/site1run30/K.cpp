#include<bits/stdc++.h>
using namespace std;
long long A,B;
void init(){cin>>A>>B;}
vector<long long> e;
long long solve(long long A,long long B){
//    cout<<A<<' '<<B<<endl;
    bool xx=0;
    for (int i=0;i<e.size();++i) if (e[i]==A) xx=1;
    if (A==B){
        long long ans=A?2:1;
        if (xx) --ans; return ans;
    }
    if (A<B){
        if (!xx) e.push_back(A);
        return solve(B,B-A)+1;
    }
    if (!B) return 2;
    if (A>2*B){
        long long k=(A-1)/(2*B),C=(A-1)%(2*B)+1,tmp=0;
        for (int i=0;i<e.size();++i) if (e[i]>C && e[i]%B==C%B) ++tmp;
        return k*2+solve(C,B)-tmp;
    }
    return solve(B,A-B)+(xx?0:1);
}
void work(){
    e.clear(); cout<<solve(A,B)<<endl;
}
int main(){
    int T; scanf("%d",&T);
    for (int t=1;t<=T;++t) init(),printf("Case #%d: ",t),work();
    return 0;
}
