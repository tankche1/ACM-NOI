#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
LL p,q;
LL two[50];


inline LL Calc(LL a,int b){
    a-=b;
    if(a<0) return 0;
    return a;
}


LL dfs(LL up,LL down,int r,int n){
    if(up==down) return -1;
    if(up==down+1) return 1;
    while(n>0&&two[n+1]-1>(up-down)) n--;
    LL res=n+2 +Calc(down+(two[n+2]-1)-up,r);

    res=min(res,dfs(up-(two[n+1]-1),down,r+1,n)+n+1+1);
    res=min(res,n+2+Calc(down,r));
   /* if(up-down<50&&n>2){
    }*/
    //printf("up:%d down:%d r:%d n:%d res:%d\n",up,down,r,n,res);
    return res;
}

int main()
{
    //freopen("out2.txt","w",stdout);
    two[0]=1;
    for(int i=1;i<50;i++) two[i]=two[i-1]<<1;
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%I64d%I64d",&p,&q);
            if(p<=q) printf("%I64d\n",q-p);
            else{
                int n=0;while(two[n+1]-1<=p-q) n++;
                LL ans=dfs(p,q,0,n);
                printf("%I64d\n",ans);
            }
    }
    //}
    return 0;
}
