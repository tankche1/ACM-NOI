# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
int n;
char s[maxn];
int sum[maxn];
int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    sum[0]=0;
    for(int i=1;i<=n;i++)
        sum[i]=sum[i-1]+((s[i]=='(')?1:-1);
    bool ok=false;
    for(int i=n;i>=1;i--){
        if(s[i]=='('){
            if(sum[i]>=2){
                ok=true;
                s[i]=')';
                for(int j=i+1;j<=(n-i-sum[i]+2)/2+i;j++) s[j]='(';
                for(int j=(n-i-sum[i]+2)/2+i+1;j<=n;j++) s[j]=')';
                break;
            }
        }
    }
    if(!ok) puts("No solution");
    else puts(s+1);
    return 0;
}
