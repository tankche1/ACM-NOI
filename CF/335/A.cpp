#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<map>
#include<set>
#include<vector>
#define REP(i,n) for(int i=0; i<n; i++)
#define FOR(i,n) for(int i=1; i<=n; i++)

typedef long long LL;
using namespace std;
#define N 100010

int L[N],R[N],a[N],p[N],n;
int main(){
#ifdef QWERTIER
  freopen("in.txt","r",stdin);
#endif
  scanf("%d",&n);
  FOR(i,n){
    scanf("%d",&a[i]);
    p[a[i]] = i;
  }
  FOR(i,n){
    if(i>1 && p[i-1]<p[i])
      L[i] = L[i-1] + 1;
    if(i<n && p[i+1]>p[i])
      R[i] = R[i+1] + 1;
  }
  int ans=1<<30;
  FOR(i,n){
    ans = min(ans,n-(L[i]+R[i]+1));
  }
  printf("%d\n",ans);
  return 0;
}
