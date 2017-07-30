# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=5010;
char s1[maxn],s2[maxn];
int n;
int main(){
    scanf("%s",s1);
    scanf("%s",s2);
    n=strlen(s1);
    int ans=0,j;
    for(int i=0;i<n;i++){
        if(s1[i]==s2[i]) continue;
        for(j=1;j<n;j++){
            if(s1[i+j]==s2[i]){
                ans+=j;swap(s1[i+j],s1[i]);break;
            }
        }
        if(j==n) {puts("-1");return 0;}
    }
    printf("%d\n",ans);
    return 0;
}
