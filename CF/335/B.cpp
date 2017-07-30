# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
int n,m;
LL tot;

struct Edge{
    int w,use,bh;
    Edge() {}
}edges[maxn];
bool cmp(Edge A,Edge B) {if(A.w==B.w) return A.use>B.use;return A.w<B.w;}

int u[maxn],v[maxn];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&edges[i].w,&edges[i].use);edges[i].bh=i;
    }
    tot=1;
    int nouse=0;
    int st=1,ed=3;
    sort(edges+1,edges+m+1,cmp);

    for(int i=1;i<=m;i++){
        if(edges[i].use==0){
            nouse++;
            if(nouse+(tot-1)>(tot)*(tot-1)/2){
                puts("-1");return 0;
            }
            u[edges[i].bh]=st;v[edges[i].bh]=ed;
            st++;
            if(st+1>=ed) st=1,ed++;
        }
        else{
            u[edges[i].bh]=tot;v[edges[i].bh]=++tot;
        }
    }

    for(int i=1;i<=m;i++){
        printf("%d %d\n",u[i],v[i]);
    }
    return 0;
}
