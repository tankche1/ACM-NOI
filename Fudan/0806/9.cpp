# include<stdio.h>
# include<string.h>
# include<math.h>
# include<queue>
# include<algorithm>
#include<stack>
using namespace std;
const int maxn=200010;
typedef long long LL;
LL INF=(LL)200000000010000;
int n;
int l[maxn],r[maxn],c[maxn];
LL d[maxn];
int p[maxn];

struct HeapNode{
    int x;
    LL val;
    HeapNode(int x=0,LL val=0):x(x),val(val) {}
    bool operator < (const HeapNode &rhs)const{
        return rhs.val<val;
    }
};

int root,tt;
int find(int x){
   root=x;
   while(p[root]!=root) root=p[root];
   while(x!=root){
     tt=p[x];p[x]=root;x=tt;
   }
   return root;
}

priority_queue<HeapNode> q;
int main(){
    int tcase,x,L,R;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&l[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&r[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&c[i]);
        for(int i=1;i<=n;i++) d[i]=INF;
        d[1]=0;
        for(int i=1;i<=n+5;i++)
            p[i]=i;
        q.push(HeapNode(1,d[1]+c[1]));
        p[1]=2;
        while(!q.empty()){
            x=q.top().x;q.pop();
            L=max(1,x-r[x]);R=x-l[x];if(L<=R) L=find(L);
            while(L<=R){
                d[L]=d[x]+c[x];
                q.push(HeapNode(L,d[L]+c[L]));
                p[L]=find(L+1);
                L=p[L];
            }
            L=x+l[x];R=min(n,x+r[x]);if(L<=R) L=find(L);
            while(L<=R){
                d[L]=d[x]+c[x];
                q.push(HeapNode(L,d[L]+c[L]));
                p[L]=find(L+1);
                L=p[L];
            }
        }
        printf("%I64d",d[1]);
        for(int i=2;i<=n;i++){
                if(d[i]!=INF)
            printf(" %I64d",d[i]);
        else printf(" -1");
            }puts("");
    }
    return 0;
}
