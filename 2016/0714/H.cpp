# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int maxm=1000010;
int n,m;
pair<int,int> p[maxm];
int fa[maxn],size[maxn];

int find(int x){
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}

int main(){
    int Tcase=0;
    while(scanf("%d%d",&n,&m)!=EOF){
        if(n==0&&m==0) break;
        for(int i=1;i<=m;i++){
            scanf("%d%d",&p[i].first,&p[i].second);
            if(p[i].first>p[i].second) swap(p[i].first,p[i].second);
        }
        for(int i=1;i<=n;i++) fa[i]=i,size[i]=1;
        sort(p+1,p+m+1);
        int now=1,px,py;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(p[now].first==i&&p[now].second==j) {now++;continue;}
                px=find(i);py=find(j);
                if(px==py) continue;
                else{
                    if(size[px]>size[py]) swap(px,py);
                    fa[px]=py;size[py]+=size[px];
                }
            }
        }
        printf("Case %d: ",++Tcase);
        printf("%d\n",size[find(1)]-1);
    }
    return 0;
}
