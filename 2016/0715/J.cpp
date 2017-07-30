# include<stdio.h>
# include<string.h>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=1010;
int n;
int x[maxn],y[maxn];

typedef pair<int,int> pi;
set<pi> row,line;
set<pi> ::iterator it,it2;

int main(){
    while(scanf("%d",&n)!=EOF){
            row.clear();line.clear();
        for(int i=1;i<=n;i++){
            scanf("%d%d",&x[i],&y[i]);
            row.insert(make_pair(x[i],y[i]));
            line.insert(make_pair(y[i],x[i]));
        }

        int ans=0;
        int px=0,py=0,dir=3;
        for(int i=1;i<=5*n;i++){
            if(dir==3){
                it=line.lower_bound(make_pair(py,px));
                if(it==line.end()) break;
                if(it->first!=py) break;
                ans++;px=it->second-1;
                dir=1;
            }
            else if(dir==2){
                it=line.lower_bound(make_pair(py,px));
                if(it==line.begin()) break;it--;
                if(it->first!=py) break;
                ans++;px=it->second+1;
                dir=0;
            }
            else if(dir==0){
                it=row.lower_bound(make_pair(px,py));
                if(it==row.end()) break;
                if(it->first!=px) break;
                ans++;py=it->second-1;
                dir=3;
            }
            else if(dir==1){
                it=row.lower_bound(make_pair(px,py));
                if(it==row.begin()) break;it--;
                if(it->first!=px) break;
                ans++;py=it->second+1;
                dir=2;
            }
        }
        if(ans>4*n) puts("-1");
        else printf("%d\n",ans);
    }
    return 0;
}
