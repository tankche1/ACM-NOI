# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
int n;
int p[1000010];
char op;

int get(LL x){
    int j=0,res=0;
    while(x>0){
        if(x&1) res+=(1<<j);
        j++;x/=10;
    }
    return res;
}
char s[30];

int main(){
    int id,len,res;LL x;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        while((op=getchar())&&op!='+'&&op!='-'&&op!='?');
        if(op!='?'){
            scanf("%lld",&x);
            id=get(x);
            if(op=='+') p[id]++;else p[id]--;
        }
        else{
            scanf("%s",s);len=strlen(s);res=0;
            for(int i=len-1;i>=0;i--){
                if(s[i]=='1') res+=1<<(len-1-i);
            }
            printf("%d\n",p[res]);
        }
    }
    return 0;
}
