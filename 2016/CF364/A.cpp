# include<stdio.h>
# include<string.h>
# include<iostream>
# include<algorithm>
using namespace std;
typedef double LD;
int n,k;
LD l,v1,v2;
LD bus;
const LD eps=1e-8;

bool check(LD T){
    bus=(l-T*v1)/((v2-v1)*1.0);
    LD dis=0;int cnt=n;
    LD step=v1*(bus+bus*(v2-v1)/(v2+v1));
    int tmp=cnt/k;if(cnt%k) tmp++;tmp--;
    dis+=step*tmp;
    /*while(cnt>0){
        cnt-=k;if(cnt>0) dis+=step;
    }*/
    if(dis+bus*v2>l) return false;
    return true;
}

int main(){
    int a,b,c;
    scanf("%d%d%d%d%d",&n,&a,&b,&c,&k);l=a*1.0;v1=b*1.0;v2=c*1.0;
    //puts("fuck");
    LD L=0,R=l/(v1*1.0),M;
    for(int i=1;i<=10000;i++) {
        M=(L+R)/2.0;
        //printf("%.3llf %.3llf %.3llf\n",L,R,M);

        if(check(M)) R=M;
        else L=M;
    }
    //cout << R <<endl;
    printf("%.10lf\n",R);
    return 0;
}
