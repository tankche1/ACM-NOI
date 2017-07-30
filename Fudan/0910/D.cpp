# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
char s[1010];
int n;
int star,num;
int ans=0;

int main(){
    int tcase;
    scanf("%d\n",&tcase);
    while(tcase--){
        num=0;star=0;
        scanf("%s",s);
        n=strlen(s);
        for(int i=0;i<n;i++){
            if(s[i]=='*') star++;
            else num++;
        }
        int l=0,r=0;

        int tank=0;
        ans=0;
        if(num<=star){
            ans+=star+1-num;r=ans;
        }
        tank=ans;
        int pos=n-1;
        if(s[n-1]!='*'){
            for(int i=0;i<n;i++)
                   if(s[i]=='*'){
                       tank++;swap(s[i],s[n-1]);break;
                   }
        }
        for(int i=0;i<n;i++){
            if(s[i]=='*'){
                if(r>1){
                    if(l>0) l--;
                    r--;
                }
                else{
                    while(s[pos]=='*') pos--;
                    swap(s[pos],s[i]);i--;
                    tank++;
                }
            }else{
                if((i==0&&ans==0)||s[i-1]=='*') l++,r++;
                else r++;
            }
        }
        printf("%d\n",tank);
    }
    return 0;
}
