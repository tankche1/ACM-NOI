# include<stdio.h>
# include<string.h>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=50010;
typedef long long LL;
int n,t;
int p[maxn],minp[maxn];
int d[maxn];
LL ti[maxn];
multiset<LL> s;
multiset<LL> ::iterator it;

bool check(int r){
    s.clear();
    for(int i=1;i<=r+1;i++) ti[i]=d[i],s.insert(ti[i]);
    for(int i=r+2;i<=n;i++){
        it=s.find(ti[i-r-1]);
        s.erase(it);
        it=s.begin();
        ti[i]=(*it)+d[i];
        s.insert(ti[i]);
    }
    if(ti[n]+n-1<=t) return true;
    else return false;
}

int main(){
    freopen("journey.in","r",stdin);
    freopen("journey.out","w",stdout);
    scanf("%d%d",&n,&t);
    for(int i=1;i<n;i++) scanf("%d",&p[i]);
    for(int i=2;i<n;i++) scanf("%d",&d[i]);
    d[1]=d[n]=0;
    minp[n-1]=p[n-1];
    for(int i=n-2;i>=1;i--) minp[i]=min(minp[i+1],p[i]);
    int L=1,R=n-1,M;
    while(L<=R){
        M=(L+R)>>1;
        if(check(M)) R=M-1;
        else L=M+1;
    }
    printf("%d\n",minp[R+1]);
    return 0;
}
