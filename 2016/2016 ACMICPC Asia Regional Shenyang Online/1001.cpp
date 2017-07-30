# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=3010;
typedef long long LL;
int n,m;
char op;
int _x1,_x2,_y1,_y2;

inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
    LL C[maxn][maxn];
    int n;

    void init(int nn){
        n=nn;for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) C[i][j]=0;
    }

    void update(int x,int y,LL val){
        for(int i=x;i<=n;i+=lowbit(i)){
            for(int j=y;j<=n;j+=lowbit(j)){
                C[i][j]^=val;
            }
        }
    }

    LL sum(int x,int y){
        LL res=0;
        for(int i=x;i>0;i-=lowbit(i)){
            for(int j=y;j>0;j-=lowbit(j)){
                res^=C[i][j];
            }
        }
        return res;
    }

}fwt[4];

void _update(int x,int y,LL val){
    //if(x==0||y==0) return;
    int op=0;
    if(x&1) op+=2;
    if(y&1) op++;

    fwt[op].update(x,y,val);
}

LL query(int x,int y){
    //if(x==0||y==0) return 0;
    int op=0;
    if(x&1) op+=2;
    if(y&1) op++;
    return fwt[op].sum(x,y);
}

int main(){
    //printf("%d\n");
    LL tmp=0;
    LL ans;
    int k,a,b;
    scanf("%d%d",&n,&m);
    for(int k=0;k<4;k++) fwt[k].init(n);

    for(int i=1;i<=m;i++){
        while((op=getchar())&&op!='P'&&op!='Q');
        if(op=='P'){
            scanf("%d%d%d%d",&_x1,&_y1,&_x2,&_y2);
            scanf("%d",&k);tmp=0;
            for(int t=1;t<=k;t++){
                scanf("%d%d",&a,&b);if(!(b&1)) continue;
                tmp^=((LL)1<<(a-1));
            }
            _update(_x1,_y1,tmp);
            _update(_x1,_y2+1,tmp);
            _update(_x2+1,_y1,tmp);
            _update(_x2+1,_y2+1,tmp);
        }
        else{
            scanf("%d%d%d%d",&_x1,&_y1,&_x2,&_y2);
            ans=query(_x2,_y2)^query(_x2,_y1-1)^query(_x1-1,_y2)^query(_x1-1,_y1-1);
            for(int i=1;i<=50;i++){
                if((ans>>(i-1))&1) printf("2");
                else printf("1");
                //if(i!=50)
                printf(" ");
            }puts("");
        }
    }

    return 0;
}
