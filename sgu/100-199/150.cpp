# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
long long x1,y1,x2,y2,n;
long long ansx,ansy;

int calc(){
    long long k1,k2,tx,ty,now;
    long long num=0;
    tx=x2-x1;ty=y2-y1;
    int dx=tx>0?1:-1,dy=ty>0?1:-1;
    if(tx<0) tx=-tx;
    if(ty<0) ty=-ty;
    for(int x=0;x<tx;x++){
        k1=ty*x/tx;k2=ty*(x+1)/tx;
        if(ty*(x+1)%tx==0)
            now=k2-k1;
        else now=k2-k1+1;
        num+=now;
        if(num>=n){
            ansx=x;ansy=k2-(num-n);
            if(ty*(x+1)%tx==0) ansy--;
            if(dx==-1) ansx=-ansx-1;
            if(dy==-1) ansy=-ansy-1;
            printf("%I64d %I64d\n",x1+ansx,y1+ansy);
            return 0;
        }
    }
    puts("no solution");
}

int main(){
   scanf("%I64d%I64d%I64d%I64d%I64d",&x1,&y1,&x2,&y2,&n);
    if(x1==x2||y1==y2){
        puts("no solution");
        return 0;
    }

    calc();
    return 0;
}
