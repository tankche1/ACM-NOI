#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#define lowbit(x) x&-x;
#define mn 50000
using namespace std;
 
int n,ans,x,pos[mn],v[mn<<1];
 
void Modify(int x,int val){
    while(x<=n<<1) v[x]+=val,x+=lowbit(x);
}
 
int Get(int x){
    int sum=0;
    while(x>0) sum+=v[x],x-=lowbit(x);
    return sum;
}
 
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n<<1;i++){
        scanf("%d",&x);
        if(!pos[x]){
            pos[x]=i;
            Modify(i,1);
        }else{
            ans+=Get(i)-Get(pos[x]-1)-1;
            Modify(pos[x],-1);
        }
    }
    printf("%d\n",ans);
    return 0;
}