# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<math.h>
# include<bitset>
# include<algorithm>
using namespace std;
typedef long long LL;
int A2,L;


int main(){
    scanf("%d%d",&A2,&L);
    if(A2&1) {puts("Flag");return 0;}
    double want=A2*A2/4.0;
    for(int a=1;a<=L;a++){
        for(int b=1;b<=L;b++){
            int c=L-a-b;
            if(!(a+b>c&&a+c>b&&b+c>a) )  continue;
            if((LL)4*A2*A2!=(LL)L*(L-2*a)*(L-2*b)*(L-2*c)) continue;
            for(int x=1;x<a;x++){
                int y=sqrt(a*a-x*x);
                if(x*x+y*y==a*a){
                    double rad=acos((a*a+b*b-c*c)/(2.0*a*b));
                    double ax=x/(a*1.0),ay=y/(a*1.0);
                    double bx=ax*cos(rad)-ay*sin(rad),by=ax*sin(rad)+ay*cos(rad);
                    bx=bx*b;by=by*b;
                    int bbx=(int)(bx+0.1),bby=(int)(by+0.1);
                    if(bbx*bbx+bby*bby==b*b){
                        printf("Dream\n");
                        printf("0 0\n%d %d\n%d %d\n",x,y,bbx,bby);
                        return 0;
                    }
                    //A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad)
                }
            }
        }
    }
    puts("Flag");
    return 0;
}
