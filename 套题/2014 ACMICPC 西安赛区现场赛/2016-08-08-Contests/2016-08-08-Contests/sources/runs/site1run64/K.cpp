# include<stdio.h>
# include<string.h>
# include<algorithm>
#include<iostream>
#include<bits/stdc++.h>
#define rep(i,a,b) for (int i = (a); i <= (b); i++)
using namespace std;
typedef long long ll;


ll A, B;
ll GCD(ll A, ll B){
    return B == 0 ? A : GCD(B, A % B);
}
ll Calc(ll A,ll B){
    if (A == 0 && B == 0) return 1;
    else if (A == 0) return 2;
    else if (B == 0) return 2;
    else{
        ll G = GCD(A,B);
        A/=G; B/=G;
        if (A < B) swap(A, B);
        if (A == B) return 3;
        else if (A % B == 0) return A / B;
        else{
            ll AA, BB;
            ll ret = A / B + 1;
            AA = A % B;
            BB = B - AA;
            return ret + Calc(AA,BB);
        }
    }
}
int main(){
    int T;
    cin>>T;
    rep(TT, 1, T){
        scanf("%lld%lld", &A, &B);
        printf("Case #%d: %lld\n", TT, Calc(A,B) + 1);
    }
    return 0;
}
