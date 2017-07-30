# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=1000010;
int n,m;
int a,k,v;
vector<int> G[maxn];
int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=1000000;i++) G[i].clear();
        for(int i=1;i<=n;i++){
            scanf("%d",&a);G[a].push_back(i);
        }
        for(int i=1;i<=m;i++){
            scanf("%d%d",&k,&v);
            if(G[v].size()<k) puts("0");
            else printf("%d\n",G[v][k-1]);
        }
    }
	return 0;
}
