# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
LL a[maxn],aa[maxn];
int n;
vector< pair<int,int> >ans;

void give(int x,int y){
    a[x]--;a[y]++;ans.push_back(make_pair(x,y));
}
int main(){
    int tcase;
    bool ok;
    scanf("%d",&tcase);
    while(tcase--){
            LL sum=0,need;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%I64d",&aa[i]),sum+=aa[i];
        if(sum%n) {puts("NO");continue;}
        need=sum/n;
        for(int t=0;t<=2;t++){
            for(int i=1;i<=n;i++) a[i]=aa[i]-need;
            ans.clear();ok=true;
            if(t==1) give(1,n);
            else if(t==2) give(n,1);
            for(int i=1;i<n;i++){
                if(a[i]<-1) {ok=false;break;}
                if(a[i]>1) {ok=false;break;}
                if(a[i]==1) give(i,i+1);
                else if(a[i]==-1) give(i+1,i);
            }
            if(a[n]!=0) ok=false;
            if(ok){
                    break;
            }
        }
        if(!ok) puts("NO");
        else{
            puts("YES");
            printf("%d\n",(int)ans.size());
            for(int i=0;i<(int)(ans.size());i++){
                printf("%d %d\n",ans[i].first,ans[i].second);
            }
        }
    }
    return 0;
}
