# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000010;
int mod=10007;
int n;
char s1[maxn],s2[maxn];
unsigned int hash1[maxn],hash2[maxn];
unsigned int key=10007;

char tank(char c){
    if(c=='N') return 'S';
    if(c=='S') return 'N';
    if(c=='E') return 'W';
    if(c=='W') return 'E';
}
int main(){
    scanf("%d",&n);n--;
    scanf("%s",s1+1);scanf("%s",s2+1);
    hash1[n]=s1[n];
    for(int i=n-1;i>=1;i--){
        hash1[i]=s1[i]*key+hash1[i+1];key=key*mod;
    }
    hash2[n]=tank(s2[n]);
    for(int i=n-1;i>=1;i--){
        hash2[i]=hash2[i+1]*mod+tank(s2[i]);
    }

    /*for(int i=1;i<=n;i++){
        printf("i:%d hash1:%u hash2:%u\n",i,hash1[i],hash2[i]);
    }*/

    bool ok=true;
    for(int i=n;i>=1;i--){
        if(hash1[i]==hash2[i]) ok=false;
    }
    if(ok) puts("YES");
    else puts("NO");
    return 0;
}
