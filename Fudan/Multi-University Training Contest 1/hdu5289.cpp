# include<stdio.h>
# include<string.h>
# include<queue>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=1000000100;
typedef long long LL;
LL ans;
int n,k;

multiset<int>::iterator it;
multiset<int> s;
int R[maxn];
int a[maxn];
int main(){
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
       scanf("%d%d",&n,&k);
       for(int i=1;i<=n;i++) scanf("%d",&a[i]);
       R[0]=0;s.clear();a[0]=0;s.insert(a[0]);
       int _max,_min;ans=0;
       for(int i=1;i<=n;i++){
            it=s.lower_bound(a[i-1]);s.erase(it);
            if(s.empty()) _min=INF,_max=-INF;
            else {it=s.begin();_min=*it;it=s.end();it--;_max=*it;}
            R[i]=R[i-1];
            for(int j=R[i-1]+1;j<=n;j++){
                if(s.empty()||(abs(a[j]-_min)<k&&abs(a[j]-_max)<k)){
                       // printf("insert:%d\n",j);
                    s.insert(a[j]);_min=min(_min,a[j]);_max=max(_max,a[j]);
                    R[i]=j;
                }
                else break;
            }
            //printf("R[%d]:%d\n",i,R[i]);
            ans+=R[i]-i+1;
       }
       printf("%I64d\n",ans);
    }
    return 0;
}
