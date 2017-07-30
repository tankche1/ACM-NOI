# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
int n;
int a[110];
char s[110];

bool is[26];

int main(){
    scanf("%d\n",&n);
    memset(is,false,sizeof(is));
    is['a'-'a']=is['e'-'a']=is['i'-'a']=is['o'-'a']=is['u'-'a']=is['y'-'a']=1;

    for(int i=1;i<=n;i++) scanf("%d",&a[i]);getchar();
    bool flag=true;
    for(int i=1;i<=n;i++){
        gets(s);//puts(s);
        int m=strlen(s);
        int l=0,r=0;
        int small=0,big=0;
        bool ok;
        while(l<m){
            r=l;
            while(r+1<m&&s[r+1]>='a'&&s[r+1]<='z') r++;ok=false;
            for(int i=l;i<=r;i++) if(is[s[i]-'a']) big++,ok=true;
            small+=ok;
            //printf("l:%d r:%d\n",l,r);
            l=r+1;
            while(l<m&&(s[l]<'a'||s[l]>'z')) l++;
        }
        //printf("small:%d big:%d\n",small,big);
        if(a[i]!=big) flag=false;
    }
    if(flag) puts("YES");
    else puts("NO");
    return 0;
}
