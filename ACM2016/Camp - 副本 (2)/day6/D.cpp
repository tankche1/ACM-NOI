# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL INF=(LL)1<<60;
const int maxn=100010;
int n;
struct Item{
    int a,b;
}item[maxn];

int dp[2][maxn];

bool cmp(item A,item B){
    if(A.a==B.a) return A.b>B.b;
    return A.a>B.a;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&item[i].a,&item[i].b);
    }
    sort(item+1,item+n+1,cmp);
    for(int i=0;i<=n;i++) dp[0][i]=dp[1][i]=-INF;
    int now,last;
    int two=n/2,one=n-two;
    dp[1][0]=0;
    for(int i=2;i<=n;i++){
        now=i&1;last=now^1;
        for(int )
        for(int j=max(0,two-(n-i));j<=i/2;j++){
            dp[now][j]=
        }
    }
    return 0;
}
