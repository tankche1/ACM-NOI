# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
char s[maxn];
int sum[maxn],d[maxn];
int n;

int get(char c) {if(c=='a') return 1;else return -1;}
int main(){
    int tcase,tnum=0;
    scanf("%d\n",&tcase);
    while(tcase--){
        scanf("%s",s+1);
        for(n=1;;n++) if(s[n]=='\0') break;
        n--;
        //printf("%d\n",n);
        sum[0]=0;
        for(int i=1;i<=n;i++){
            sum[i]=sum[i-1]+get(s[i]);
        }
        d[n]=sum[n];
        for(int i=n-1;i>=1;i--)
            d[i]=min(d[i+1],sum[i]);
        int now=0,ans=0;
        for(int i=1;i<=n;i++){
           if(s[i]=='a') {now++;continue;}
           if(s[i]=='+'){
                if(now>=2) now--;
                else{
                    if(s[i+1]=='+') now++,ans++,i--;
                    else{
                        if(s[i+1]=='a'&&((d[i+2]>=sum[i+1])||(i+2>n))){
                            swap(s[i],s[i+1]);ans++;i--;
                        }
                        else{
                            now++,ans++,i--;
                        }
                    }
                }
            }
        }
        printf("Case %d: ",++tnum);
        printf("%d\n",ans+now-1);
    }
    return 0;
}
