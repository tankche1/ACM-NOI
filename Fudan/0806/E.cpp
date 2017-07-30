# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=1000010;
const int mod=1000000007;
typedef long long LL;
int match[maxn],L[maxn],R[maxn],up[maxn];
int n;
char s[maxn];
int sta[maxn],top;
LL ans[maxn];

int main(){
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%s",s+1);
        n=strlen(s+1);
        top=-1;
        for(int i=0;i<=n+5;i++) match[i]=0,up[i]=0,ans[i]=0,R[i]=L[i]=0;
        for(int i=1;i<=n;i++){
            if(s[i]=='('){
                sta[++top]=i;
               }
            else{
                if(top<0) continue;
                match[sta[top]]=i;match[i]=sta[top];up[sta[top]]=top==0?0:sta[top-1];
                top--;
            }
        }

        for(int i=n;i>=1;i--){
            if(s[i]=='('&&match[i]>0){
                if(s[match[i]+1]=='(') R[i]=R[match[i]+1]+1;
                else R[i]=1;
               }
        }

        for(int i=1;i<=n;i++){
            if(s[i]==')'&&match[i]>0){
                if(s[match[i]-1]==')') L[i]=L[match[i]-1]+1;
                else L[i]=1;
            }
        }

        ans[0]=0;
        for(int i=1;i<=n;i++){
            if(s[i]=='('&&match[i]>0){
                ans[i]=ans[up[i]]+(LL)R[i]*L[match[i]];
                ans[match[i]]=ans[i];
               }
            if(ans[i]>=mod) ans[i]%=mod;
            //printf("i:%d match:%d up:%d L:%d R:%d ans:%d\n",i,match[i],up[i],L[i],R[i],ans[i]);
        }


        LL res=0;
        for(int i=1;i<=n;i++){
            res=(res+((LL)i*ans[i]%mod));
            //if(res>=mod) res%=mod;
        }
        printf("%I64d\n",res);
    }
    return 0;
}
