# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
//const int maxp=30000010;
const int INF=~0U>>1;
typedef long long LL;
int n,K;
int x[maxn<<1],cnt=0;
pair<int,int> p[maxn];

struct Line{
    int l,r,y,op;
    Line() {}
    Line(int _l,int _r,int _y,int _op):l(_l),r(_r),y(_y),op(_op) {}
}L[maxn<<1];
int lcnt=0;

bool cmp(Line A,Line B){
    return A.y<B.y;
}

int last[maxn<<1],num[maxn<<1];
LL ans[maxn];

int main(){
    int a,b;
    scanf("%d%d",&n,&K);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a,&b);p[i]=make_pair(a,b);
        x[cnt++]=a-K+1;x[cnt++]=a+1;
    }

    sort(x,x+cnt);
    cnt=unique(x,x+cnt)-x;

    for(int i=1;i<=n;i++){
        //p[i].first=lower_bound(x,x+cnt,p[i].first)-x;
        L[lcnt++]=Line(lower_bound(x,x+cnt,p[i].first-K+1)-x,lower_bound(x,x+cnt,p[i].first+1)-x-1,p[i].second+1,-1);
        L[lcnt++]=Line(lower_bound(x,x+cnt,p[i].first-K+1)-x,lower_bound(x,x+cnt,p[i].first+1)-x-1,p[i].second-K+1,1);
    }

    sort(L,L+lcnt,cmp);

    /*for(int i=0;i<lcnt;i++){
        printf("x:%d y:%d op:%d\n",x[L[i].x],L[i].y,L[i].op);
    }*/

    for(int i=0;i<cnt;i++) last[i]=-INF;

    for(int i=0,j;i<lcnt;i++){
        j=i;
        while(j<lcnt-1&&L[j+1].y==L[j].y) j++;

        //printf("I:%d j:%d\n",i,j);
        for(int k=i;k<=j;k++){
            for(int tx=L[k].l;tx<=L[k].r;tx++){
                if(last[tx]!=-INF){
                    ans[num[tx]]+=(L[i].y-last[tx])*(x[tx+1]-x[tx]);
                    //printf("x:%d num:%d +:%d\n",x[tx],num[tx],L[i].y-last[tx]);
                }last[tx]=L[i].y;
            }
        }

        for(int k=i;k<=j;k++){
            for(int tx=L[k].l;tx<=L[k].r;tx++){
                num[tx]+=L[k].op;
               // printf("x:%d num:%d\n",x[tx],num[tx]);
            }
        }
        i=j;
    }

    for(int i=1;i<n;i++){
        printf("%lld ",ans[i]);
    }
    printf("%lld\n",ans[n]);

    return 0;
}
