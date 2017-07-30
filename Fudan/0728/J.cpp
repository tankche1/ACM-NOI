# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=500010;
int w[maxn],n;
int first[maxn],nnext[maxn],edge=0,v[maxn];
int size[maxn],ans;

void add_edge(int a,int b){
    nnext[edge]=first[a];v[edge]=b;first[a]=edge++;
}
int q[maxn],front,rear;
int in[maxn];

int main(){
    int a,b;
    while(scanf("%d",&n)!=EOF){
        edge=0;memset(first,-1,sizeof(first));memset(in,0,sizeof(in));
        for(int i=1;i<=n;i++)
            scanf("%d",&w[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            if(w[a]<w[b]) swap(a,b);
            add_edge(a,b);in[b]++;
        }
        ans=0;front=0;rear=-1;
        for(int i=1;i<=n;i++){
            size[i]=1;
            if(in[i]==0) q[++rear]=i;
        }
        int x;
        while(front<=rear){
            x=q[front++];
            for(int e=first[x];e!=-1;e=nnext[e]){
                size[v[e]]+=size[x];if(--in[v[e]]==0) q[++rear]=v[e];
            }
        }
        for(int i=1;i<=n;i++)
            ans=max(ans,size[i]);
        printf("%d\n",ans);
    }
    return 0;
}
