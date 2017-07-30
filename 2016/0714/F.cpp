# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=21;
int n,m;

struct rect{
    int x1,x2,y1,y2;
    rect() {}
};
rect squ[maxn],ask[maxn];

int xx[maxn<<1],yy[maxn<<1];

int num[maxn<<1];

struct Line{
    int y,x1,x2,val;
    Line(int _y=0,int _x1=0,int _x2=0,int _val=0):y(_y),x1(_x1),x2(_x2),val(_val) {}
    bool operator < (Line tps)const {
        return y<tps.y;
    }
}L[maxn<<2];

//bool cmp()

int solve(int nn){
    int ans=0;
    int cnt=0,cntx,cnty;
    for(int i=1;i<=nn;i++) {xx[cnt]=ask[i].x1;yy[cnt++]=ask[i].y1;xx[cnt]=ask[i].x2;yy[cnt++]=ask[i].y2;}
    sort(xx,xx+cnt);sort(yy,yy+cnt);
    cntx=unique(xx,xx+cnt)-xx;cnty=unique(yy,yy+cnt)-yy;

    int ln=0;
    for(int i=1;i<=nn;i++){
        L[ln++]=Line(ask[i].y1,lower_bound(xx,xx+cntx,ask[i].x1)-xx,lower_bound(xx,xx+cntx,ask[i].x2)-xx,1);
        L[ln++]=Line(ask[i].y2,lower_bound(xx,xx+cntx,ask[i].x1)-xx,lower_bound(xx,xx+cntx,ask[i].x2)-xx,-1);
    }
    sort(L,L+ln);

    memset(num,0,sizeof(num));
    int now=0;
    for(int i=0;i<ln;i++){
        if(i>0&&L[i].y>L[i-1].y){
            ans+=now*(L[i].y-L[i-1].y);
        }
        for(int j=L[i].x1;j<L[i].x2;j++){
            if(L[i].val>0&&(++num[j]==1)) now+=xx[j+1]-xx[j];
            if(L[i].val<0&&(--num[j]==0)) now-=xx[j+1]-xx[j];
        }
    }
    return ans;
}

int main(){
    int t,Tcase=0,x;
    while(scanf("%d%d",&n,&m)!=0){
        if(n==0&&m==0) break;printf("Case %d:\n",++Tcase);
        for(int i=1;i<=n;i++){
            scanf("%d%d%d%d",&squ[i].x1,&squ[i].y1,&squ[i].x2,&squ[i].y2);
        }
        for(int i=1;i<=m;i++){
            scanf("%d",&t);
            for(int j=1;j<=t;j++){
                scanf("%d",&x);ask[j]=squ[x];
            }
            printf("Query %d: %d\n",i,solve(t));
        }puts("");
    }
    return 0;
}
