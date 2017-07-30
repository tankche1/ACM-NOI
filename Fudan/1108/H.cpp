# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
int n;
char s[maxn];
int main(){
    freopen("hash.in","r",stdin);
    freopen("hash.out","w",stdout);
    //printf("%d %d %d %d\n",'a','z','A','Z');
    //printf("%d %d %d %d\n",31*'b'+'C',31*'a'+'b',31*'C'+'b',31*'D'+'C');
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        if(i&1) s[i]='b';else s[i]='C';
    }s[n+1]='\0';
    puts(s+1);
    for(int i=2;i<=n;i++){
        if(s[i-1]=='b'){
            s[i-1]='a';s[i]='b';
            puts(s+1);
            s[i-1]='b';s[i]='C';
        }
        else{
            s[i-1]='D';s[i]='C';
            puts(s+1);
            s[i-1]='C';s[i]='b';
        }
    }
    return 0;
}
