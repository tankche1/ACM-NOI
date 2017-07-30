#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
# include<algorithm>
using namespace std;
typedef	long long LL;

const int maxn = 20006 * 4, mod = 1004535809, G = 3;

LL x1[maxn], x2[maxn];
LL qpow (LL a, LL b) {
    LL ret=1;
    while (b) {
        if (b&1) ret = (ret*a)%mod;
        a = (a*a)%mod;
        b >>= 1;
    }
    return ret;
}

void change (LL *y, int len) {
    int i, j, k;
    for(i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j) swap(y[i], y[j]);
        k = len / 2;
        while (j >= k) {
            j -= k;
            k /= 2;
        }
        if (j < k) j += k;
    }
}

void ntt (LL *y, int len, int on) {
    change (y, len);
    int id = 0;
    for(int h = 2; h <= len; h <<= 1) {
        id++;
        LL wn = qpow (G, (mod - 1) / (1<<id));
        for(int j = 0; j < len; j += h) {
            LL w = 1;
            for(int k = j; k < j + h / 2; k++) {
                LL u = y[k] % mod;
                LL t = w * (y[k + h / 2] % mod) % mod;
                y[k] = (u + t) % mod;
                y[k + h / 2] = ((u - t) % mod + mod) % mod;
                w = w * wn % mod;
            }
        }
    }
    if (on == -1) {
        for (int i = 1; i < len / 2; i++)
            swap (y[i], y[len - i]);
        LL inv = qpow(len, mod - 2);
        for(int i = 0; i < len; i++)
            y[i] = y[i] % mod * inv % mod;
    }
}
int n;
const int maxm=20010;

LL inv[maxm],jie[maxm];
LL tree[maxm],g[maxm];
LL A[maxm],B[maxm];

LL a[maxn],b[maxn],c[maxn];

void solve(int L,int R){
    if(L==R){
        A[L]=(A[L]+tree[L])%mod;return;
    }
    int M=(L+R)>>1;
    solve(L,M);

    for(int i=L;i<=M;i++) a[i-L]=A[i]*inv[i]%mod;
    for(int i=1;i<=R-L;i++) b[i-1]=B[i];
    int t=M-L+1+R-L-1,l=0,len=1;
    while((1<<l)<=t) l++;
    len=1<<l;
    for(int i=M-L+1;i<len;i++) a[i]=0;
    for(int i=R-L;i<len;i++) b[i]=0;
    ntt(a,len,1);
    ntt(b,len,1);
    for(int i=0;i<len;i++) c[i]=a[i]*b[i]%mod;
    ntt(c,len,-1);

    for(int i=M+1;i<=R;i++){
        A[i]=(A[i]+(LL)c[i-L-1]*jie[i-1])%mod;
    }

    solve(M+1,R);
    return;
}

LL fast_pow(LL a,LL b){
    LL res=1,tmp=a;
    while(b>0){
        if(b&1) res=res*tmp%mod;
        b>>=1;tmp=tmp*tmp%mod;
    }
    return res;
}

void prepare(){
    int N=20000;
    jie[0]=1;
    for(int i=1;i<=N;i++) jie[i]=jie[i-1]*i%mod;
    inv[N]=fast_pow(jie[N],mod-2);
    for(int i=N-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;

    tree[1]=tree[2]=1;for(int i=3;i<=N;i++) tree[i]=fast_pow(i,i-2);
    for(int i=1;i<=N;i++) B[i]=tree[i]*inv[i-1]%mod;

    for(int i=1;i<=N;i++) g[i]=fast_pow(2,i*(i-1)/2);

}

int main(){
   int Case;
   prepare();
   scanf("%d",&Case);
   for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) A[i]=0;
        solve(1,n);
        //printf("A[n]:%I64d\n",A[n]);
        printf("%I64d\n",(g[n]+mod-A[n])%mod);
   }
}
