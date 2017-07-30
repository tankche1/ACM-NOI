# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n;
int left[maxn];

struct Bacon{
    int p,b;
    Bacon(){}
    Bacon(int p,int b):p(p),b(b) {}
    bool operator < (const Bacon &rhs)const{
        if(p==rhs.p) return b<rhs.b;
        return p<rhs.p;
    }
}A[maxn];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&A[i].p,&A[i].b);
    }
    sort(A+1,A+n+1);
    left[1]=0;
    left[0]=0;
    for(int i=2;i<=n;i++){
        int j=lower_bound(A+1,A+i+1,Bacon(A[i].p-A[i].b,0))-A;
        left[i]=left[j-1]+i-j;
    }
    int ans=0;
    for(int i=n;i>=1;i--){
        ans=max(ans,i-left[i]);
    }
    printf("%d\n",n-ans);
    return 0;
}
