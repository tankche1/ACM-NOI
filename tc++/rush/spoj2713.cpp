#include<iostream>  
#include<cstdio>  
#include<map>  
#include<cstring>  
#include<cmath>  
#include<vector>  
#include<queue>  
#include<algorithm>  
#include<set>  
#define inf (1ull<<63)-1  
#define N 100005  
#define maxn 100005  
#define Min(a,b) ((a)<(b)?(a):(b))  
#define Max(a,b) ((a)>(b)?(a):(b))  
#define pb(a) push_back(a)  
#define mem(a,b) memset(a,b,sizeof(a))  
#define eps 1e-9  
#define zero(a) fabs(a)<eps  
#define LL long long  
#define ULL unsigned long long  
#define lson (step<<1)  
#define rson (step<<1|1)  
#define MOD 1000000007  
#define mp(a,b) make_pair(a,b)  
using namespace std;  
struct Node{  
    int left,right;  
    LL sum;  
}L[N*5];  
int n,q;  
LL a[N];  
void Push_Up(int step){  
    L[step].sum=L[lson].sum+L[rson].sum;  
}  
void Bulid(int step,int l,int r){  
    L[step].left=l;L[step].right=r;  
    if(l==r) {L[step].sum=a[l];return ;}  
    int m=(l+r)/2;  
    Bulid(lson,l,m);  
    Bulid(rson,m+1,r);  
    Push_Up(step);  
}  
void Update(int step,int l,int r){  
    if(L[step].right-L[step].left+1==L[step].sum) return;  
    if(L[step].left==L[step].right){      
        L[step].sum=(LL)sqrt(L[step].sum+0.0);  
        return;  
    }  
    int m=(L[step].left+L[step].right)/2;  
    if(r<=m) Update(lson,l,r);  
    else if(l>m) Update(rson,l,r);  
    else{  
        Update(lson,l,m);  
        Update(rson,m+1,r);  
    }  
    Push_Up(step);  
}  
LL Query(int step,int l,int r){  
    if(L[step].left==l&&L[step].right==r)  
        return L[step].sum;  
    int m=(L[step].left+L[step].right)/2;  
    if(r<=m) return Query(lson,l,r);  
    else if(l>m) return Query(rson,l,r);  
    else return Query(lson,l,m)+Query(rson,m+1,r);  
}  
int main(){  
    int cas=0;  
    while(scanf("%d",&n)!=EOF){  
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);  
        Bulid(1,1,n);  
        scanf("%d",&q);  
        printf("Case #%d:\n",++cas);  
        while(q--){  
            int k,l,r;  
            scanf("%d%d%d",&k,&l,&r);  
            if(l>r) swap(l,r);  
            if(k==0) Update(1,l,r);  
            else printf("%lld\n",Query(1,l,r));  
        }  
        printf("\n");  
    }  
    return 0;  
}  