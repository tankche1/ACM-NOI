# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n,q;

int get(int x){
    int now=0;
    while(x){
        now+=x/5;
        x/=5;
    }
    //printf("now:%d\n",now);
    return now;
}

int main(){
    scanf("%d",&q);
    int L=1,R=5*q,M;
    while(L<=R){
        M=(L+R)>>1;
        //printf("L:%d R:%d M:%d\n",L,R,M);
        if(get(M)>=q) R=M-1;
        else L=M+1;
    }
    if(get(R+1)!=q) puts("No solution");
    else
    printf("%d\n",R+1);
    return 0;
}
