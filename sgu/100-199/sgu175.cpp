# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n,q;
int ans;

void dfs(int pos,int n){
    int half=n>>1;
    if(n==1) {ans++;return;}
    if(pos>half) dfs(n-pos+1,n-half);
    else{
        ans+=n-half;dfs(half-pos+1,half);
    }
}

int main(){
    scanf("%d%d",&n,&q);
    ans=0;
    dfs(q,n);
    printf("%d\n",ans);
    return 0;
}
